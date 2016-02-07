package mapeditor.mapapi;

import java.awt.Graphics;
import java.awt.Point;
import java.util.Iterator;

import mapeditor.mainwindow.map.MapPane;
import mapeditor.themesapi.MapObject;
import mapeditor.themesapi.MapObjectFactory;

//TODO: review
public class CopyPaste {
	enum State {
		/*
		 * NEW - user just activated copyPaste action;
		 */
		/*
		 * 
		 * SELECTING - user is drawing selection
		 * rectangle;selectedSegments.firstPointToCut,
		 * selectedSegments.lastPointToCut - corners of selected rectangle;
		 * draggedSegments.isActive() = false
		 */
		/*
		 * SELECTED - user finished drawing selection rectangle;
		 * firstPointToCut, lastPointToCut - corners of selected rectangle;
		 * selectedSegments.getMinPoint(), selectedSegments.getMaxPoint() - min,
		 * max corners of selected map; initialized from
		 * selectedSegments.firstPointToCut, selectedSegments.lastPointToCut;
		 * selectedSegments - initialized to refer segments selected on map;
		 */
		/*
		 * DRAGGING - user is dragging selection rectangle;
		 * draggedSegments.firstDragPoint, draggedSegments.lastDragPoint are
		 * initialized;
		 * (draggedSegments.lastDragPoint-draggedSegments.firstDragPoint) -
		 * vector of drag movement
		 */
		/*
		 * DRAGGED - user is not dragging selection rectangle, but can continue
		 * to drag it. Mouse cursor is somewhere else on the map;
		 * (draggedSegments.lastDragPoint-draggedSegments.firstDragPoint) -
		 * vector of drag movement
		 */
		/*
		 * DROP - user pasted selection rectangle somewhere;
		 * (draggedSegments.lastDragPoint-draggedSegments.firstDragPoint) -
		 * vector of drag movement
		 */
		/*
		 * draggedSegments.minDraggedPoint, draggedSegments.maxDraggedPoint -
		 * are initialized during draggedSegments.tryToActivate() when
		 * draggedSegments.firstDragPoint and draggedSegments.lastDragPoint are
		 * not null; draggedSegments.minDraggedPoint,
		 * draggedSegments.maxDraggedPoint - corners of dragged rectangle;
		 */
		/*
		 * draggedSegments - refer to segments on map under dragged rectangle.
		 */
		NEW, SELECTING, SELECTED, DRAGGING, DRAGGED, DROP
	}

	public enum CopyPasteCursor {
		CROSS, HAND
	}

	private enum EventCopyPaste {
		MOVE, LEFT_CLICK, LEFT_PRESS, DRAG, LEFT_RELEASE, DOUBLE_CLICK, VK_CUT, VK_COPY, VK_PASTE
	}

	private State state = State.NEW;

	private CopyPasteCursor copyPasteCursor = CopyPasteCursor.CROSS;

	private MapApi mapApi;

	private MapPane mapPane;

	private SelectedSegments selectedSegments;

	private DraggedSegments draggedSegments;

	private MapObjectFactory mapObjectFactory;

	public CopyPaste(MapApi mapApi, MapObjectFactory mapObjectFactory) {
		this.mapApi = mapApi;
		this.mapObjectFactory = mapObjectFactory;

		selectedSegments = new SelectedSegments(mapObjectFactory);
		draggedSegments = new DraggedSegments();
	}

	public CopyPasteCursor getCopyPasteCursor() {
		return copyPasteCursor;
	}

	public SelectedSegments getSelectedSegments() {
		return selectedSegments;
	}

	public DraggedSegments getDraggedSegments() {
		return draggedSegments;
	}

	public void addGridPane(MapPane mapPane) {
		this.mapPane = mapPane;
	}

	public void onActionPerformed() {
		beginNewState();
		mapPane.refresh();
	}

	public void onLeftButtonClick(Point point) {
		onEvent(EventCopyPaste.LEFT_CLICK, point);
	}

	public void onLeftButtonDoubleClick(Point point) {
		onEvent(EventCopyPaste.DOUBLE_CLICK, point);

	}

	private void beginNewState() {
		state = State.NEW;
		copyPasteCursor = CopyPasteCursor.CROSS;

		selectedSegments.deactivate();
		draggedSegments.deactivate();
	}

	private void beginSelectingState(Point point) {
		state = State.SELECTING;

		selectedSegments.deactivate();
		selectedSegments.setFirstPointToCut(point);
		selectedSegments.setLastPointToCut(point);

		draggedSegments.deactivate();
	}

	private void beginDraggingState(Point point) {
		state = State.DRAGGING;

		draggedSegments.setFirstDragPoint(point);
		draggedSegments.setLastDragPoint(point);
	}

	private void beginDraggingStateFromPaste() {
		if (selectedSegments.isActive()) {
			state = State.DRAGGING;

			draggedSegments.setFirstDragPoint(selectedSegments.getMinPoint());
			draggedSegments.setLastDragPoint(selectedSegments.getMinPoint());
		}
	}

	private void continueDraggingState(Point point) {
		state = State.DRAGGING;
		draggedSegments.setLastDragPoint(point);
	}

	private void beginSelectedState(Point point, int layerIndex) {
		state = State.SELECTED;

		selectedSegments.activate(mapPane, layerIndex);
	}

	private void beginDraggedState() {
		state = State.DRAGGED;

		copyPasteCursor = CopyPasteCursor.CROSS;
	}

	private void continueAfterDrop() {
		if (selectedSegments.isCutState()) {
			beginNewState();
		} else {
			state = State.SELECTED;
			draggedSegments.deactivate();
		}
		mapPane.refresh();
	}

	private void beginDropState() {
		state = State.DROP;

		if (draggedSegments.isActive()) {
			if (selectedSegments.isActive() && selectedSegments.isCutState()) {

				Iterator<CopyPasteSegment> selectedIterator = selectedSegments
						.iterator();

				while (selectedIterator.hasNext()) {
					CopyPasteSegment segment = selectedIterator.next();
					int row = segment.getPoint().y;
					int col = segment.getPoint().x;

					mapApi.getSegment(row, col).setMapObject(
							mapObjectFactory.getBlankMapObject(),
							mapApi.getActiveLayerIndex());
				}
			}

			Iterator<CopyPasteSegment> draggedIterator = draggedSegments
					.iterator();

			while (draggedIterator.hasNext()) {
				CopyPasteSegment segment = draggedIterator.next();
				int row = segment.getPoint().y;
				int col = segment.getPoint().x;
				MapObject mapObject = segment.getMapObject();

				System.out.println("wklejam");
				mapObject.describeYourself();

				mapApi.getSegment(row, col).setMapObject(mapObject,
						mapApi.getActiveLayerIndex());
			}
		}

		copyPasteCursor = CopyPasteCursor.CROSS;
	}

	public void onMousePressed(Point point) {
		onEvent(EventCopyPaste.LEFT_PRESS, point);
	}

	public void onMouseReleased(Point point) {
		onEvent(EventCopyPaste.LEFT_RELEASE, point);
	}

	public void onMouseDragged(Point point) {
		onEvent(EventCopyPaste.DRAG, point);
	}

	public void onMouseMoved(Point point) {
		onEvent(EventCopyPaste.MOVE, point);
	}

	public void paint(Graphics graphics) {
		selectedSegments.paint(graphics);
		draggedSegments.paint(graphics);

	}

	public void onCutEvent() {
		onEvent(EventCopyPaste.VK_CUT, null);
		selectedSegments.setCutState();
		mapPane.refresh();
	}

	public void onCopyEvent() {
		onEvent(EventCopyPaste.VK_COPY, null);
		selectedSegments.setCopyState();
		mapPane.refresh();
	}

	public void onPasteEvent() {
		onEvent(EventCopyPaste.VK_PASTE, null);
		beginDraggingStateFromPaste();

		mapPane.refresh();
	}

	public void onZoomMapInEvent() {
		beginNewState();
		mapPane.refresh();
	}

	public void onZoomMapOutEvent() {
		beginNewState();
		mapPane.refresh();
	}

	public void onZoomMapDefaultEvent() {
		beginNewState();
		mapPane.refresh();
	}

	public void onCenterMapEvent() {
		beginNewState();
		mapPane.refresh();
	}

	private void onEvent(EventCopyPaste event, Point point) {
		switch (state) {
		case NEW:
			onEventInStateNew(event, point);
			break;
		case SELECTING:
			onEventInStateSelecting(event, point);
			break;
		case SELECTED:
			onEventInStateSelected(event, point);
			break;
		case DRAGGING:
			onEventInStateDragging(event, point);
			break;
		case DRAGGED:
			onEventInStateDragged(event, point);
			break;
		case DROP:
			onEventInStateDrop(event);
			break;
		default:
			break;
		}
	}

	private void onEventInStateNew(EventCopyPaste event, Point point) {

		switch (event) {
		case MOVE:
			copyPasteCursor = CopyPasteCursor.CROSS;
			break;
		case LEFT_CLICK:
			break;
		case LEFT_PRESS:
			beginSelectingState(point);
			break;
		case DRAG:
			break;
		case LEFT_RELEASE:
			break;
		case DOUBLE_CLICK:
			break;
		case VK_CUT:
			// Already implemented in onCutEvent()
			break;
		case VK_COPY:
			// Already implemented in onCopyEvent()
			break;
		case VK_PASTE:
			break;
		default:
			break;
		}
	}

	private void onEventInStateSelecting(EventCopyPaste event, Point point) {
		switch (event) {
		case MOVE:
			copyPasteCursor = CopyPasteCursor.CROSS;
			break;
		case LEFT_CLICK:
			break;
		case LEFT_PRESS:
			break;
		case DRAG:
			selectedSegments.setLastPointToCut(point);
			break;
		case LEFT_RELEASE:
			beginSelectedState(point, mapApi.getActiveLayerIndex());
			break;
		case DOUBLE_CLICK:
			break;
		case VK_CUT:
			// Already implemented in onCutEvent()
			break;
		case VK_COPY:
			// Already implemented in onCopyEvent()
			break;
		case VK_PASTE:
			break;
		default:
			break;
		}
	}

	private void onEventInStateSelected(EventCopyPaste event, Point point) {
		switch (event) {
		case MOVE:
			if (selectedSegments.isActive() && selectedSegments.contains(point)) {
				copyPasteCursor = CopyPasteCursor.HAND;
			} else {
				copyPasteCursor = CopyPasteCursor.CROSS;
			}
			break;
		case LEFT_CLICK:
			break;
		case LEFT_PRESS:
			if (selectedSegments.isActive() && selectedSegments.contains(point)) {
				beginDraggingState(point);
			} else {
				beginSelectingState(point);
			}
			break;
		case DRAG:
			break;
		case LEFT_RELEASE:
			break;
		case DOUBLE_CLICK:
			break;
		case VK_CUT:
			// Already implemented in onCutEvent()
			break;
		case VK_COPY:
			// Already implemented in onCopyEvent()
			break;
		case VK_PASTE:
			break;

		default:
			break;
		}
	}

	private void onEventInStateDragging(EventCopyPaste event, Point point) {
		switch (event) {
		case MOVE:
			if (selectedSegments.isActive() && selectedSegments.contains(point)) {
				copyPasteCursor = CopyPasteCursor.HAND;
			} else {
				copyPasteCursor = CopyPasteCursor.CROSS;
			}
			break;
		case LEFT_CLICK:
			break;
		case LEFT_PRESS:
			break;
		case DRAG:
			draggedSegments.setLastDragPoint(point);
			break;
		case LEFT_RELEASE:
			beginDraggedState();
			break;
		case DOUBLE_CLICK:
			beginDropState();
			continueAfterDrop();
			break;
		case VK_CUT:
			// Already implemented in onCutEvent()
			break;
		case VK_COPY:
			// Already implemented in onCopyEvent()
			break;
		case VK_PASTE:
			break;
		default:
			break;
		}
	}

	private void onEventInStateDragged(EventCopyPaste event, Point point) {
		switch (event) {
		case MOVE:
			if (draggedSegments.isActive() && draggedSegments.contains(point)) {
				copyPasteCursor = CopyPasteCursor.HAND;
			} else {
				copyPasteCursor = CopyPasteCursor.CROSS;
			}
			break;
		case LEFT_CLICK:
			break;
		case LEFT_PRESS:
			if (draggedSegments.isActive() && draggedSegments.contains(point)) {
				continueDraggingState(point);
			} else {
				beginDropState();
				continueAfterDrop();
			}
			break;
		case DRAG:
			break;
		case LEFT_RELEASE:
			break;
		case DOUBLE_CLICK:
			// Double Click drops segments and clears selection
			beginDropState();
			beginNewState();
			break;
		case VK_CUT:
			// Already implemented in onCutEvent()
			break;
		case VK_COPY:
			// Already implemented in onCopyEvent()
			break;
		case VK_PASTE:
			break;
		default:
			break;
		}
	}

	private void onEventInStateDrop(EventCopyPaste event) {
		switch (event) {
		case MOVE:
			copyPasteCursor = CopyPasteCursor.CROSS;
			break;
		case LEFT_CLICK:
			break;
		case LEFT_PRESS:
			break;
		case DRAG:
			break;
		case LEFT_RELEASE:
			break;
		case DOUBLE_CLICK:
			break;
		case VK_CUT:
			// Already implemented in onCutEvent()
			break;
		case VK_COPY:
			// Already implemented in onCopyEvent()
			break;
		case VK_PASTE:
			break;
		default:
			break;
		}
	}

}
