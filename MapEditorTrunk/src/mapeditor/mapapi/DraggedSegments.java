package mapeditor.mapapi;

import java.awt.BasicStroke;
import java.awt.Point;
import java.util.Iterator;
import java.util.LinkedList;

import javax.swing.plaf.ColorUIResource;

import mapeditor.mainwindow.MapPane;

public class DraggedSegments extends CopyPasteSegments {

	private boolean theSame;

	private static Point findMinDraggedPoint(
			CopyPasteSegments selectedSegments, Point firstDragPoint,
			Point lastDragPoint) {
		int vectorX = lastDragPoint.x - firstDragPoint.x;
		int vectorY = lastDragPoint.y - firstDragPoint.y;

		Point minDraggedPoint = new Point(selectedSegments.getMinPoint().x
				+ vectorX, selectedSegments.getMinPoint().y + vectorY);

		return minDraggedPoint;
	}

	private static Point findMaxDraggedPoint(
			CopyPasteSegments selectedSegments, Point firstDragPoint,
			Point lastDragPoint) {
		int vectorX = lastDragPoint.x - firstDragPoint.x;
		int vectorY = lastDragPoint.y - firstDragPoint.y;

		Point maxDraggedPoint = new Point(selectedSegments.getMaxPoint().x
				+ vectorX, selectedSegments.getMaxPoint().y + vectorY);

		return maxDraggedPoint;
	}

	public DraggedSegments(MapPane mapPane, CopyPasteSegments selectedSegments,
			Point firstDragPoint, Point lastDragPoint) {
		super(mapPane, findMinDraggedPoint(selectedSegments, firstDragPoint,
				lastDragPoint), findMaxDraggedPoint(selectedSegments,
				firstDragPoint, lastDragPoint));

		theSame = areSegmentsSame(selectedSegments.getSegments(), segments);

		if (theSame) {
			copySegments(selectedSegments.getSegments());
			paint = new ColorUIResource(224, 0, 32);
			float dash[] = { 5.0f };
			stroke = new BasicStroke(3.0f, BasicStroke.CAP_ROUND,
					BasicStroke.JOIN_ROUND, 5.0f, dash, 0.0f);
		}
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

				dragSegment.setMapObject(selSegment.getMapObject().clone());

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
}
