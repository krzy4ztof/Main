package mapeditor.mapapi;

import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Point;
import java.util.Iterator;
import java.util.LinkedList;

import javax.swing.plaf.ColorUIResource;

import mapeditor.mainwindow.map.MapPane;

public class DraggedSegments extends CopyPasteSegments {

	private boolean theSame;

	private Point firstDragPoint;

	private Point lastDragPoint;

	public Point getFirstDragPoint() {
		return firstDragPoint;
	}

	public void setFirstDragPoint(Point point) {
		firstDragPoint = point;
	}

	public Point getLastDragPoint() {
		return lastDragPoint;
	}

	public void setLastDragPoint(Point point) {
		lastDragPoint = point;
	}

	public DraggedSegments() {
		paint = new ColorUIResource(224, 0, 32);
		// paint = Color.BLUE;
		firstDragPoint = null;
		lastDragPoint = null;
	}

	@Override
	public void deactivate() {
		super.deactivate();
		firstDragPoint = null;
		lastDragPoint = null;
	}

	public void tryToActivate(MapPane mapPane,
			CopyPasteSegments selectedSegments, int layerIndex) {
		if (firstDragPoint != null && lastDragPoint != null) {
			activate(mapPane, selectedSegments, firstDragPoint, lastDragPoint,
					layerIndex);
		}

	}

	public void activate(MapPane mapPane, CopyPasteSegments selectedSegments,
			Point firstDragPoint, Point lastDragPoint, int layerIndex) {
		int vectorX = lastDragPoint.x - firstDragPoint.x;
		int vectorY = lastDragPoint.y - firstDragPoint.y;

		Point minDraggedPoint = new Point(selectedSegments.getMinPoint().x
				+ vectorX, selectedSegments.getMinPoint().y + vectorY);
		Point maxDraggedPoint = new Point(selectedSegments.getMaxPoint().x
				+ vectorX, selectedSegments.getMaxPoint().y + vectorY);

		super.activate(mapPane, minDraggedPoint, maxDraggedPoint, layerIndex);
		theSame = areSegmentsSame(selectedSegments.getSegments(), segments);

		if (theSame) {
			copySegments(selectedSegments.getSegments());
		}

		active = true;
	}

	private boolean areSegmentsSame(
			LinkedList<LinkedList<CopyPasteSegment>> selectedSegments,
			LinkedList<LinkedList<CopyPasteSegment>> draggedSegments) {

		int selColNo = selectedSegments.size();
		int dragColNo = draggedSegments.size();

		if (selColNo != dragColNo) {
			return false;
		}

		for (int i = 0; i < selColNo; i++) {
			int selRowNo = selectedSegments.get(i).size();
			int dragRowNo = draggedSegments.get(i).size();

			if (selRowNo != dragRowNo) {

				return false;
			}
		}
		return true;
	}

	private void copySegments(
			LinkedList<LinkedList<CopyPasteSegment>> selectedSegments) {

		int dragColNo = selectedSegments.size();

		for (int x = 0; x < dragColNo; x++) {
			LinkedList<CopyPasteSegment> dragRow = segments.get(x);
			LinkedList<CopyPasteSegment> selRow = selectedSegments.get(x);

			int rowNo = dragRow.size();
			for (int y = 0; y < rowNo; y++) {
				CopyPasteSegment dragSegment = dragRow.get(y);
				CopyPasteSegment selSegment = selRow.get(y);

				// dragSegment.setMapObject(selSegment.getMapObject().clone());
				dragSegment.setMapObject(selSegment.getMapObject());
				dragSegment.setCustomMapObject(selSegment.getCustomMapObject());

			}
		}
	}

	@Override
	public Iterator<CopyPasteSegment> iterator() {

		if (theSame) {
			return super.iterator();
		} else {

			LinkedList<CopyPasteSegment> list = new LinkedList<CopyPasteSegment>();
			return list.iterator();
		}
	}

	protected void paintRectangle(Graphics graphics) {
		if (isActive()) {
			if (graphics instanceof Graphics2D) {
				Graphics2D g2 = (Graphics2D) graphics;
				g2.setStroke(stroke);
				g2.setPaint(paintRectangle);
			}
			drawRectangle(graphics, minPoint, maxPoint);
		}
	}
}
