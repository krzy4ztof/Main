package mapeditor.mapapi;

import java.awt.Graphics;
import java.awt.Point;
import java.util.LinkedList;

import mapeditor.mainwindow.MapPane;

public class CopyOfCopyPaste_backup {
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
		NEW, CUT, COPY, UNDO
	}

	private enum CopyPasteCursor {
		CROSS, HAND
	}

	public enum CursorChangeState {
		CHANGE_TO_CROSS, CHANGE_TO_HAND, NO_CHANGE
	}

	private enum EventCopyPaste {
		MOVE, LEFT_CLICK, LEFT_PRESS, DRAG, LEFT_RELEASE, DOUBLE_CLICK, VK_CUT, VK_COPY, VK_PASTE, VK_UNDO
	}

	private State state = State.NEW;

	private CutCopyState cutCopyState = CutCopyState.NEW;

	private CopyPasteCursor cursor = CopyPasteCursor.CROSS;

	private CursorChangeState cursorChangeState = CursorChangeState.NO_CHANGE;

	private MapApi mapApi;

	// If not null -> segments are being selected -> minPoinToCut is null,
	// firstDragPoint is null
	// If null segments are selected -> minPointToCut is not null
	private Point firstPointToCut;// desc

	// If not null -> segments are being selected
	private Point lastPointToCut;// desc

	// If not null -> segments are selected -> firstPointToCut is null
	// If null -> segments are being selected -> firstPointToCut is not null
	// private Point minPointToCut;// desc

	// If not null -> segments are selected
	// private Point maxPointToCut;// desc

	// If not null -> segments are selected -> firstPointToCut is null
	// If null -> segments are being selected -> firstPointToCut is not null
	// private Point minSegmentToCut;//UNUSED

	// If not null -> segments are selected
	// private Point maxSegmentToCut;// UNUSED

	// If not null -> segments are being dragged -> firstPointToCut is null,
	// minPointToCut is not null
	private Point firstDragPoint;// desc

	// If not null -> segments are being dragged
	private Point lastDragPoint;// desc

	// private Point minDraggedPoint;// desc

	// private Point maxDraggedPoint;// desc

	private MapPane mapPane;

	// private LinkedList<LinkedList<Point>> selectedSegments;// desc

	private CopyPasteSegments selectedSegments;

	// private LinkedList<LinkedList<Point>> draggedSegments;// desc
	private CopyPasteSegments draggedSegments;// desc

	public CopyOfCopyPaste_backup(MapApi mapApi) {
		this.mapApi = mapApi;
		// state = State.NEW;
	}

	public CopyPasteSegments getSelectedSegments() {
		return selectedSegments;
	}

	/*
	 * public LinkedList<LinkedList<Point>> getSelectedSegments() { return
	 * selectedSegments; }
	 */

	/*
	 * public LinkedList<LinkedList<Point>> getDraggedSegments() { return
	 * draggedSegments; }
	 */
	public CopyPasteSegments getDraggedSegments() {
		return draggedSegments;
	}

	public CursorChangeState getCursorState() {
		CursorChangeState previous = cursorChangeState;
		cursorChangeState = CursorChangeState.NO_CHANGE;

		return previous;
	}

	public void addGridPane(MapPane mapPane) {
		this.mapPane = mapPane;
	}

	public void onLeftButtonClick(Point point) {
		onEvent(EventCopyPaste.LEFT_CLICK, point);

		/*
		 * if (state == State.NEW) { firstPointToCut = point;
		 * System.out.println(point.x + " " + point.y); state =
		 * State.FIRSTPOINT; }
		 */
	}

	public void onLeftButtonDoubleClick(Point point) {
		onEvent(EventCopyPaste.DOUBLE_CLICK, point);

	}

	private void beginNewState() {
		state = State.NEW;
		cursor = CopyPasteCursor.CROSS;
		cursorChangeState = CursorChangeState.NO_CHANGE;
		cutCopyState = CutCopyState.NEW;

		selectedSegments = null;
		// minPointToCut = null;
		// maxPointToCut = null;

		draggedSegments = null;
		// minDraggedPoint = null;
		// maxDraggedPoint = null;

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
		// minPointToCut = null;
		// maxPointToCut = null;

		draggedSegments = null;
		// minDraggedPoint = null;
		// maxDraggedPoint = null;

		firstDragPoint = null;
		lastDragPoint = null;
	}

	private void beginDraggingState(Point point) {
		state = State.DRAGGING;

		firstDragPoint = point;
		lastDragPoint = point;
	}

	private void continueDraggingState(Point point) {
		state = State.DRAGGING;

		lastDragPoint = point;
	}

	private void beginSelectedState(Point point) {
		state = State.SELECTED;

		// if (firstPointToCut != null && lastPointToCut != null) {
		// minPointToCut = getMinPoint(firstPointToCut, lastPointToCut);
		// maxPointToCut = getMaxPoint(firstPointToCut, lastPointToCut);

		// Point min = mapPane.getSegmentPointAtCursor(minPointToCut);
		// Point max = mapPane.getSegmentPointAtCursor(maxPointToCut);

		// selectedSegments = mapPane.getSegmentPoints(firstPointToCut,
		// lastPointToCut);

		selectedSegments = new CopyPasteSegments(mapPane, firstPointToCut,
				lastPointToCut);
		// selectedSegments.setSegments(mapPane.getSegmentPoints(firstPointToCut,
		// lastPointToCut));

		// System.out.println(min + " - " + max);
		// }
		firstPointToCut = null;
		lastPointToCut = null;

	}

	private void beginDraggedState() {
		// if (firstDragPoint != null && lastDragPoint != null) {
		state = state.DRAGGED;

		changeCursor(CopyPasteCursor.CROSS);

		// System.out.println("CUT ");

		// System.out.println("PASTE HERE SELECTED SEGMENTS");

		// firstDragPoint = null;
		// lastDragPoint = null;

		// minPointToCut = minDraggedPoint;
		// maxPointToCut = maxDraggedPoint;

		// minDraggedPoint = null;
		// maxDraggedPoint = null;

		// }
	}

	private void beginDropState() {
		// if (firstDragPoint != null && lastDragPoint != null) {
		state = state.DROP;

		System.out.println("CUT ");

		System.out.println("PASTE HERE SELECTED SEGMENTS");

		changeCursor(CopyPasteCursor.CROSS);

		// mapPane.getPanel().setCursor(
		// Cursor.getPredefinedCursor(Cursor.CROSSHAIR_CURSOR));

		// cursor = CursorState.CHANGE_TO_CROSS;

		// firstDragPoint = null;
		// lastDragPoint = null;

		// }
	}

	public void onMousePressed(Point point) {
		onEvent(EventCopyPaste.LEFT_PRESS, point);
	}

	/**
	 * State NEW -> SELECTING; SELECTED -> SELECTING or DRAGGING; DRAGGED ->
	 * DRAGGING or (DROP and SELECTING)
	 * 
	 * @param point
	 */
	public void onMousePressed22(Point point) {

		System.out.println(point.x + " PRESSED " + point.y + " STATE " + state);

		if (state == State.NEW) {
			beginSelectingState(point);
		} else if (state == State.SELECTED) {
			// if (point.x >= minPointToCut.x && point.x <= maxPointToCut.x
			// && point.y >= minPointToCut.y && point.y <= maxPointToCut.y) {
			/*
			 * if (point.x >= selectedSegments.getMinPoint().x && point.x <=
			 * selectedSegments.getMaxPoint().x && point.y >=
			 * selectedSegments.getMinPoint().y && point.y <=
			 * selectedSegments.getMaxPoint().y) {
			 */
			if (selectedSegments != null && selectedSegments.contains(point)) {
				beginDraggingState(point);
			} else {
				beginSelectingState(point);
			}
		} else if (state == State.DRAGGED) {

			// if (point.x >= minPointToCut.x && point.x <= maxPointToCut.x
			// && point.y >= minPointToCut.y && point.y <= maxPointToCut.y) {

			/*
			 * if (point.x >= minDraggedPoint.x && point.x <= maxDraggedPoint.x
			 * && point.y >= minDraggedPoint.y && point.y <= maxDraggedPoint.y)
			 * {
			 */
			if (draggedSegments != null && draggedSegments.contains(point)) {
				continueDraggingState(point);
			} else {
				beginDropState();
				beginSelectingState(point);
			}
		}
	}

	public void onMouseReleased(Point point) {
		onEvent(EventCopyPaste.LEFT_RELEASE, point);
	}

	/**
	 * SELECTING -> SELECTED or NEW; DRAGGING -> DRAGGED
	 * 
	 * @param point
	 */
	public void onMouseReleased22(Point point) {

		System.out.println(point.x + " RELASE " + point.y + " STATE " + state);

		if (state == state.SELECTING) {

			if (firstPointToCut.equals(lastPointToCut)) {
				beginNewState();
			} else {
				beginSelectedState(point);
			}
			/*
			 * if (firstPointToCut != null && lastPointToCut != null) {
			 * minPointToCut = getMinPoint(firstPointToCut, lastPointToCut);
			 * maxPointToCut = getMaxPoint(firstPointToCut, lastPointToCut);
			 * 
			 * firstPointToCut = null; lastPointToCut = null; state =
			 * State.SELECTED;
			 * 
			 * }
			 */
		} else if (state == state.DRAGGING) {

			beginDraggedState();

			// beginDropState();
			// beginNewState();
		}

		/*
		 * if (lastPointToCut == null && state == State.CUT) { lastPointToCut =
		 * point; }
		 */

		/*
		 * if (state == State.NEW) { firstPointToCut = point;
		 * System.out.println(point.x + " " + point.y); state =
		 * State.FIRSTPOINT; }
		 */
	}

	public void onMouseDragged(Point point) {
		onEvent(EventCopyPaste.DRAG, point);
	}

	/**
	 * SELECTING, DRAGGING
	 * 
	 * @param point
	 */
	public void onMouseDragged22(Point point) {

		System.out.println(point.x + " DRAG " + point.y + " STATE " + state);

		if (state == State.DRAGGING) {
			lastDragPoint = point;

			/*
			 * if (minPointToCut != null && maxPointToCut != null) { if (point.x
			 * >= minPointToCut.x && point.x <= maxPointToCut.x && point.y >=
			 * minPointToCut.y && point.y <= maxPointToCut.y) {
			 * System.out.println("DRAGGED MOUSE"); lastDragPoint = point;
			 * 
			 * } }
			 */
		} else if (state == State.SELECTING) {
			// if (firstPointToCut != null) {// && state == State.CUT) {
			lastPointToCut = point;
			// }
		}

		/*
		 * if (firstPointToCut == null) { firstPointToCut = point; state =
		 * State.CUT; }
		 */
		/*
		 * if (state == State.NEW) { firstPointToCut = point;
		 * System.out.println(point.x + " " + point.y); state =
		 * State.FIRSTPOINT; }
		 */
	}

	private void changeCursor(CopyPasteCursor newCursor) {

		if (newCursor == CopyPasteCursor.CROSS) {
			if (cursor != newCursor) {
				cursor = newCursor;
				cursorChangeState = CursorChangeState.CHANGE_TO_CROSS;
			} else {
				cursorChangeState = CursorChangeState.NO_CHANGE;
			}
		} else if (newCursor == CopyPasteCursor.HAND) {
			if (cursor != newCursor) {
				cursor = newCursor;
				cursorChangeState = CursorChangeState.CHANGE_TO_HAND;
			} else {
				cursorChangeState = CursorChangeState.NO_CHANGE;
			}

		} else {
			cursorChangeState = CursorChangeState.NO_CHANGE;
		}

	}

	public void onMouseMoved(Point point) {
		onEvent(EventCopyPaste.MOVE, point);
		// return null;
	}

	public void onMouseMoved22(Point point) {

		System.out.println(point.x + " MOVED " + point.y + " STATE " + state);
		/*
		 * if (state == State.NEW) { return changeCursor(CursorState.CROSS);
		 * 
		 * } else
		 */
		if (state == State.SELECTED) {
			// if (point.x >= minPointToCut.x && point.x <= maxPointToCut.x
			// && point.y >= minPointToCut.y && point.y <= maxPointToCut.y) {
			/*
			 * if (point.x >= selectedSegments.getMinPoint().x && point.x <=
			 * selectedSegments.getMaxPoint().x && point.y >=
			 * selectedSegments.getMinPoint().y && point.y <=
			 * selectedSegments.getMaxPoint().y) {
			 */
			if (selectedSegments != null && selectedSegments.contains(point)) {
				System.out.println("CURSOR SELECTED");
				changeCursor(CopyPasteCursor.HAND);

				// beginDraggingState(point);
			} else {

				System.out.println("CURSOR NORM");
				changeCursor(CopyPasteCursor.CROSS);
			}

			// else {
			// beginSelectingState(point);
			// }
		} else if (state == State.DRAGGED) {

			// if (point.x >= minPointToCut.x && point.x <= maxPointToCut.x
			// && point.y >= minPointToCut.y && point.y <= maxPointToCut.y) {

			/*
			 * if (point.x >= minDraggedPoint.x && point.x <= maxDraggedPoint.x
			 * && point.y >= minDraggedPoint.y && point.y <= maxDraggedPoint.y)
			 * {
			 */
			if (draggedSegments != null && draggedSegments.contains(point)) {
				System.out.println("CURSOR DRAGGED");
				changeCursor(CopyPasteCursor.HAND);
			} else {
				System.out.println("CURSOR NORM");
				changeCursor(CopyPasteCursor.CROSS);
			}

			// else {
			// beginDropState();
			// beginSelectingState(point);
			// }
		} else {
			System.out.println("CURSOR NORM");
			changeCursor(CopyPasteCursor.CROSS);
		}

	}

	public void prePaint() {

		if (firstDragPoint != null && lastDragPoint != null) {

			int vectorX = lastDragPoint.x - firstDragPoint.x;
			int vectorY = lastDragPoint.y - firstDragPoint.y;
			/*
			 * minDraggedPoint = new Point(minPointToCut.x + vectorX,
			 * minPointToCut.y + vectorY); maxDraggedPoint = new
			 * Point(maxPointToCut.x + vectorX, maxPointToCut.y + vectorY);
			 */
			Point minDraggedPoint = new Point(selectedSegments.getMinPoint().x
					+ vectorX, selectedSegments.getMinPoint().y + vectorY);
			Point maxDraggedPoint = new Point(selectedSegments.getMaxPoint().x
					+ vectorX, selectedSegments.getMaxPoint().y + vectorY);

			if (minDraggedPoint != null && maxDraggedPoint != null) {
				draggedSegments = new CopyPasteSegments(mapPane,
						minDraggedPoint, maxDraggedPoint);

			}

			// if (minDraggedPoint != null && maxDraggedPoint != null) {
			// draggedSegments = new CopyPasteSegments(mapPane, minDraggedPoint,
			// maxDraggedPoint);

			// draggedSegments = mapPane.getSegmentPoints(minDraggedPoint,
			// maxDraggedPoint);
		}

	}

	public void paint(Graphics graphics) {

		// if (state == State.CUT) {

		if (firstPointToCut != null && lastPointToCut != null) {
			graphics.drawLine(firstPointToCut.x, firstPointToCut.y,
					firstPointToCut.x + 10, firstPointToCut.y + 10);
			drawRectangle(graphics, firstPointToCut, lastPointToCut);

			// graphics.drawRect(firstPointToCut.x, firstPointToCut.y,
			// lastPointToCut.x
			// - firstPointToCut.x, lastPointToCut.y - firstPointToCut.y);
		}

		// if (minPointToCut != null && maxPointToCut != null) {
		if (selectedSegments != null) {
			// if (selectedSegments.getMinPoint() != null
			// && selectedSegments.getMaxPoint() != null) {

			// graphics.drawLine(firstPointToCut.x, firstPointToCut.y,
			// firstPointToCut.x + 10, firstPointToCut.y + 10);

			// drawRectangle(graphics, minPointToCut, maxPointToCut);
			drawRectangle(graphics, selectedSegments.getMinPoint(),
					selectedSegments.getMaxPoint());

			// graphics.drawRect(firstPointToCut.x, firstPointToCut.y,
			// lastPointToCut.x
			// - firstPointToCut.x, lastPointToCut.y - firstPointToCut.y);
		}

		/*
		 * if (firstDragPoint != null && lastDragPoint != null) {
		 * 
		 * int vectorX = lastDragPoint.x - firstDragPoint.x; int vectorY =
		 * lastDragPoint.y - firstDragPoint.y; minDraggedPoint = new
		 * Point(minPointToCut.x + vectorX, minPointToCut.y + vectorY);
		 * maxDraggedPoint = new Point(maxPointToCut.x + vectorX,
		 * maxPointToCut.y + vectorY); }
		 */

		// if (minDraggedPoint != null && maxDraggedPoint != null) {
		if (draggedSegments != null) {
			// drawRectangle(graphics, minDraggedPoint, maxDraggedPoint);
			drawRectangle(graphics, draggedSegments.getMinPoint(),
					draggedSegments.getMaxPoint());

		}

		// }
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

	/*
	 * private Point getMinPoint(Point first, Point last) { Point point = new
	 * Point(Math.min(first.x, last.x), Math.min(first.y, last.y)); return
	 * point; }
	 * 
	 * private Point getMaxPoint(Point first, Point last) { Point point = new
	 * Point(Math.max(first.x, last.x), Math.max(first.y, last.y)); return
	 * point; }
	 */

	public boolean areSegmentsSame(
			LinkedList<LinkedList<Point>> selectedSegments,
			LinkedList<LinkedList<Point>> draggedSegments) {

		int selColNo = selectedSegments.size();
		int dragColNo = draggedSegments.size();

		if (selColNo != dragColNo) {

			// System.out.println(selColNo + " ? ColNo ? " + dragColNo);
			return false;
		}

		for (int i = 0; i < selColNo; i++) {
			int selRowNo = selectedSegments.get(i).size();
			int dragRowNo = draggedSegments.get(i).size();

			if (selRowNo != dragRowNo) {
				// System.out.println(selRowNo + " ? Col ? " + dragRowNo);

				return false;
			}

		}

		return true;
	}

	public void onCutEvent() {
		onEvent(EventCopyPaste.VK_CUT, null);
		cutCopyState = CutCopyState.CUT;
	}

	public void onCopyEvent() {
		cutCopyState = CutCopyState.COPY;
		onEvent(EventCopyPaste.VK_COPY, null);
	}

	public void onPasteEvent() {
		cutCopyState = CutCopyState.NEW;
		onEvent(EventCopyPaste.VK_PASTE, null);
	}

	public void onUndoEvent() {
		cutCopyState = CutCopyState.NEW;
		onEvent(EventCopyPaste.VK_UNDO, null);
	}

	private void onEvent(EventCopyPaste event, Point point) {
		System.out.println("Event: " + event + " during state: " + state);

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
			changeCursor(CopyPasteCursor.CROSS);
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
			break;
		case VK_COPY:
			break;
		case VK_PASTE:
			break;
		case VK_UNDO:
			break;
		default:
			break;
		}
	}

	private void onEventInStateSelecting(EventCopyPaste event, Point point) {
		switch (event) {
		case MOVE:
			changeCursor(CopyPasteCursor.CROSS);
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
			break;
		case VK_COPY:
			break;
		case VK_PASTE:
			break;
		case VK_UNDO:
			break;
		default:
			break;
		}
	}

	private void onEventInStateSelected(EventCopyPaste event, Point point) {
		switch (event) {
		case MOVE:
			// if (point.x >= minPointToCut.x && point.x <= maxPointToCut.x
			// && point.y >= minPointToCut.y && point.y <= maxPointToCut.y) {
			/*
			 * if (point.x >= selectedSegments.getMinPoint().x && point.x <=
			 * selectedSegments.getMaxPoint().x && point.y >=
			 * selectedSegments.getMinPoint().y && point.y <=
			 * selectedSegments.getMaxPoint().y) {
			 */
			if (selectedSegments != null && selectedSegments.contains(point)) {
				System.out.println("CURSOR SELECTED");

				changeCursor(CopyPasteCursor.HAND);

				// beginDraggingState(point);
			} else {

				System.out.println("CURSOR NORM");
				changeCursor(CopyPasteCursor.CROSS);
			}
			break;
		case LEFT_CLICK:
			break;
		case LEFT_PRESS:
			// if (point.x >= minPointToCut.x && point.x <= maxPointToCut.x
			// && point.y >= minPointToCut.y && point.y <= maxPointToCut.y) {

			/*
			 * if (point.x >= selectedSegments.getMinPoint().x && point.x <=
			 * selectedSegments.getMaxPoint().x && point.y >=
			 * selectedSegments.getMinPoint().y && point.y <=
			 * selectedSegments.getMaxPoint().y) {
			 */
			if (selectedSegments != null && selectedSegments.contains(point)) {
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
			break;
		case VK_COPY:
			break;
		case VK_PASTE:
			break;
		case VK_UNDO:
			break;
		default:
			break;
		}
	}

	private void onEventInStateDragging(EventCopyPaste event, Point point) {
		switch (event) {
		case MOVE:
			changeCursor(CopyPasteCursor.CROSS);
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
			break;
		case VK_CUT:
			break;
		case VK_COPY:
			break;
		case VK_PASTE:
			break;
		case VK_UNDO:
			break;
		default:
			break;
		}
	}

	private void onEventInStateDragged(EventCopyPaste event, Point point) {
		switch (event) {
		case MOVE:
			// if (point.x >= minDraggedPoint.x && point.x <= maxDraggedPoint.x
			// && point.y >= minDraggedPoint.y
			// && point.y <= maxDraggedPoint.y) {
			if (draggedSegments != null && draggedSegments.contains(point)) {

				System.out.println("CURSOR DRAGGED");
				changeCursor(CopyPasteCursor.HAND);
			} else {
				System.out.println("CURSOR NORM");
				changeCursor(CopyPasteCursor.CROSS);
			}
			break;
		case LEFT_CLICK:
			break;
		case LEFT_PRESS:
			/*
			 * if (point.x >= minDraggedPoint.x && point.x <= maxDraggedPoint.x
			 * && point.y >= minDraggedPoint.y && point.y <= maxDraggedPoint.y)
			 * {
			 */
			if (draggedSegments != null && draggedSegments.contains(point)) {
				continueDraggingState(point);
			} else {
				beginDropState();
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
			break;
		case VK_COPY:
			break;
		case VK_PASTE:
			break;
		case VK_UNDO:
			break;
		default:
			break;
		}
	}

	private void onEventInStateDrop(EventCopyPaste event) {
		switch (event) {
		case MOVE:
			changeCursor(CopyPasteCursor.CROSS);
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
			break;
		case VK_COPY:
			break;
		case VK_PASTE:
			break;
		case VK_UNDO:
			break;
		default:
			break;
		}
	}

}
