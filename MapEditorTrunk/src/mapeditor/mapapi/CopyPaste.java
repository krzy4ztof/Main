package mapeditor.mapapi;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Paint;
import java.awt.Point;
import java.awt.Stroke;
import java.util.Iterator;

import mapeditor.mainwindow.MapPane;
import mapeditor.themesapi.MapObject;
import mapeditor.themesapi.MapObjectFactory;

public class CopyPaste {
	enum State {
		/*
		 * NEW - user just activated copyPaste action;
		 */
		/*
		 * 
		 * SELECTING - user is drawing selection rectangle;firstPointToCut,
		 * lastPointToCut - corners of selected rectangle; firstDragPoint,
		 * lastDragPoint are set to null; minDraggedPoint, maxDraggedPoint are
		 * set to null
		 */
		/*
		 * SELECTED - user finished drawing selection rectangle;
		 * firstPointToCut, lastPointToCut - corners of selected rectangle;
		 * minPointToCut, maxPointToCut - min, max corners of selected map;
		 * initialized from firstPointToCut, lastPointToCut; selectedSegments -
		 * initialized to refer segments selected on map;
		 */
		/*
		 * DRAGGING - user is dragging selection rectangle; firstDragPoint,
		 * lastDragPoint are initialized; (lastDragPoint-firstDragPoint) -
		 * vector of drag movement
		 */
		/*
		 * DRAGGED - user is not dragging selection rectangle, but can continue
		 * to drag it. Mouse cursor is somewhere else on the map;
		 * (lastDragPoint-firstDragPoint) - vector of drag movement
		 */
		/*
		 * DROP - user pasted selection rectangle somewhere;
		 * (lastDragPoint-firstDragPoint) - vector of drag movement
		 */
		/*
		 * minDraggedPoint, maxDraggedPoint - are initialized during prePaint()
		 * when firstDragPoint and lastDragPoint are not null; minDraggedPoint,
		 * maxDraggedPoint - corners of dragged rectangle;
		 */
		/*
		 * draggedSegments - refer to segments on map under dragged rectangle.
		 * Initialized during paint() when minDraggedPoin and maxDraggedPoint is
		 * not null;
		 */
		/*
		 * REFACTORING !!!!!!!!!!!! minPointToCut, maxPointToCut - now
		 * selectedSegments.getMinPoint(), selectedSegments.getMaxPoint();
		 * minDraggedPoint, maxDraggedPoint - now draggedSegments.getMinPoint(),
		 * draggedSegments.getMaxPoint()
		 */
		NEW, SELECTING, SELECTED, DRAGGING, DRAGGED, DROP
	}

	enum CutCopyState {
		CUT, COPY
	}

	public enum CopyPasteCursor {
		CROSS, HAND
	}

	private enum EventCopyPaste {
		MOVE, LEFT_CLICK, LEFT_PRESS, DRAG, LEFT_RELEASE, DOUBLE_CLICK, VK_CUT, VK_COPY, VK_PASTE
	}

	private State state = State.NEW;

	private CutCopyState cutCopyState = CutCopyState.CUT;

	private CopyPasteCursor copyPasteCursor = CopyPasteCursor.CROSS;

	private MapApi mapApi;

	// If not null -> segments are being selected -> minPoinToCut is null,
	// firstDragPoint is null
	// If null segments are selected -> minPointToCut is not null
	private Point firstPointToCut;

	// If not null -> segments are being selected
	private Point lastPointToCut;

	// If not null -> segments are being dragged -> firstPointToCut is null,
	// minPointToCut is not null
	private Point firstDragPoint;

	// If not null -> segments are being dragged
	private Point lastDragPoint;

	private MapPane mapPane;

	private SelectedSegments selectedSegments;

	private DraggedSegments draggedSegments;

	private MapObjectFactory mapObjectFactory;

	private Paint paint;
	private Stroke stroke;

	public CopyPaste(MapApi mapApi, MapObjectFactory mapObjectFactory) {
		this.mapApi = mapApi;
		this.mapObjectFactory = mapObjectFactory;

		paint = Color.BLACK;
		float dash[] = { 5.0f };
		stroke = new BasicStroke(2.0f, BasicStroke.CAP_ROUND,
				BasicStroke.JOIN_ROUND, 5.0f, dash, 0.0f);
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
		cutCopyState = CutCopyState.CUT;

		selectedSegments = null;
		draggedSegments = null;

		firstPointToCut = null;
		lastPointToCut = null;

		firstDragPoint = null;
		lastDragPoint = null;
	}

	private void beginSelectingState(Point point) {
		state = State.SELECTING;

		firstPointToCut = point;
		lastPointToCut = point;

		selectedSegments = null;
		draggedSegments = null;

		firstDragPoint = null;
		lastDragPoint = null;
	}

	private void beginDraggingState(Point point) {
		state = State.DRAGGING;

		firstDragPoint = point;
		lastDragPoint = point;
	}

	private void beginDraggingStateFromPaste() {

		if (selectedSegments != null) {
			state = State.DRAGGING;

			// firstDragPoint and lastDragPoint must be the same
			firstDragPoint = selectedSegments.getMinPoint();
			lastDragPoint = selectedSegments.getMinPoint();
		}
	}

	private void continueDraggingState(Point point) {
		state = State.DRAGGING;

		lastDragPoint = point;
	}

	private void beginSelectedState(Point point) {
		state = State.SELECTED;

		selectedSegments = new SelectedSegments(mapPane, firstPointToCut,
				lastPointToCut, mapObjectFactory);

		firstPointToCut = null;
		lastPointToCut = null;

	}

	private void beginDraggedState() {
		state = state.DRAGGED;

		copyPasteCursor = CopyPasteCursor.CROSS;
	}

	private void continueAfterDrop() {
		if (selectedSegments != null) {
			if (selectedSegments.isCutState()) {
				beginNewState();
			} else {
				// selectedSegments is in copy state
				state = State.SELECTED;

				firstDragPoint = null;
				lastDragPoint = null;
				draggedSegments = null;
			}
		}
		mapPane.refresh();
	}

	private void beginDropState() {
		state = state.DROP;

		System.out.println("CUT ");

		System.out.println("PASTE HERE SELECTED SEGMENTS");

		if (draggedSegments != null) {
			if (selectedSegments != null && selectedSegments.isCutState()) {

				Iterator<CopyPasteSegment> selectedIterator = selectedSegments
						.iterator();

				while (selectedIterator.hasNext()) {
					CopyPasteSegment segment = selectedIterator.next();
					int row = segment.getPoint().y;
					int col = segment.getPoint().x;

					mapApi.getSegment(row, col).setMapObject(
							mapObjectFactory.getBlankMapObject());
				}
			}

			Iterator<CopyPasteSegment> draggedIterator = draggedSegments
					.iterator();

			while (draggedIterator.hasNext()) {
				CopyPasteSegment segment = draggedIterator.next();
				int row = segment.getPoint().y;
				int col = segment.getPoint().x;
				MapObject mapObject = segment.getMapObject();

				mapApi.getSegment(row, col).setMapObject(mapObject);
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

	public void prePaint() {

		if (firstDragPoint != null && lastDragPoint != null) {
			draggedSegments = new DraggedSegments(mapPane, selectedSegments,
					firstDragPoint, lastDragPoint);

		}

	}

	public void paint(Graphics graphics) {

		if (graphics instanceof Graphics2D) {
			Graphics2D g2 = (Graphics2D) graphics;
			g2.setStroke(stroke);
			g2.setPaint(paint);
		}

		if (firstPointToCut != null && lastPointToCut != null) {
			drawRectangle(graphics, firstPointToCut, lastPointToCut);

		}

		if (selectedSegments != null) {
			drawRectangle(graphics, selectedSegments.getMinPoint(),
					selectedSegments.getMaxPoint());
		}

		if (draggedSegments != null) {
			drawRectangle(graphics, draggedSegments.getMinPoint(),
					draggedSegments.getMaxPoint());
		}

	}

	private void drawRectangle(Graphics graphics, Point first, Point last) {
		int minX = Math.min(first.x, last.x);
		int minY = Math.min(first.y, last.y);
		int maxX = Math.max(first.x, last.x);
		int maxY = Math.max(first.y, last.y);
		int width = maxX - minX;
		int height = maxY - minY;

		graphics.drawRect(minX, minY, width, height);

	}

	public void onCutEvent() {
		onEvent(EventCopyPaste.VK_CUT, null);
		cutCopyState = CutCopyState.CUT;
		if (selectedSegments != null) {
			selectedSegments.setCutState();
		}
		mapPane.refresh();
	}

	public void onCopyEvent() {
		cutCopyState = CutCopyState.COPY;
		onEvent(EventCopyPaste.VK_COPY, null);
		if (selectedSegments != null) {
			selectedSegments.setCopyState();
		}
		mapPane.refresh();
	}

	public void onPasteEvent() {
		onEvent(EventCopyPaste.VK_PASTE, null);
		beginDraggingStateFromPaste();

		mapPane.refresh();
	}

	private void onEvent(EventCopyPaste event, Point point) {
		System.out.println("Event: " + event + " during state: " + state);

		if (point != null) {
			System.out
					.println(" point x: " + point.x + "; point y: " + point.y);
		}

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

		System.out.println("Event: " + event + " switched to state: " + state);

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
			// changeCursor(CopyPasteCursor.CROSS);
			copyPasteCursor = CopyPasteCursor.CROSS;
			break;
		case LEFT_CLICK:
			break;
		case LEFT_PRESS:
			break;
		case DRAG:
			lastPointToCut = point;
			break;
		case LEFT_RELEASE:
			if (firstPointToCut.equals(lastPointToCut)) {
				beginNewState();
			} else {
				beginSelectedState(point);
			}
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
			if (selectedSegments != null && selectedSegments.contains(point)) {
				System.out.println("CURSOR SELECTED");
				copyPasteCursor = CopyPasteCursor.HAND;
			} else {
				System.out.println("CURSOR NORM");
				copyPasteCursor = CopyPasteCursor.CROSS;
			}
			break;
		case LEFT_CLICK:
			break;
		case LEFT_PRESS:
			if (selectedSegments != null && selectedSegments.contains(point)) {
				beginDraggingState(point);
				// it is possible to select CUT COPY sate before selecting all
				// elements
				if (cutCopyState == CutCopyState.COPY) {
					selectedSegments.setCopyState();
				} else {
					selectedSegments.setCutState();
				}

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
			if (selectedSegments != null && selectedSegments.contains(point)) {
				System.out.println("CURSOR SELECTED DRAGGsING");

				copyPasteCursor = CopyPasteCursor.HAND;
			} else {

				System.out.println("CURSOR NORM DRAGGING");
				copyPasteCursor = CopyPasteCursor.CROSS;
			}
			break;
		case LEFT_CLICK:
			break;
		case LEFT_PRESS:
			break;
		case DRAG:
			lastDragPoint = point;
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
			if (draggedSegments != null && draggedSegments.contains(point)) {

				System.out.println("CURSOR DRAGGED");
				copyPasteCursor = CopyPasteCursor.HAND;
			} else {
				System.out.println("CURSOR NORM");
				copyPasteCursor = CopyPasteCursor.CROSS;
			}
			break;
		case LEFT_CLICK:
			break;
		case LEFT_PRESS:
			if (draggedSegments != null && draggedSegments.contains(point)) {
				continueDraggingState(point);
			} else {
				beginDropState();
				continueAfterDrop();
				// beginSelectingState(point);
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
			// changeCursor(CopyPasteCursor.CROSS);
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
