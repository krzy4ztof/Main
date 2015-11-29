package mapeditor.mapapi;

import java.awt.Paint;
import java.awt.Point;
import java.awt.Stroke;
import java.util.Iterator;
import java.util.LinkedList;

import mapeditor.mainwindow.MapPane;

public class CopyPasteSegments {

	protected Paint paint;

	protected Stroke stroke;

	protected Point minPoint;

	protected Point maxPoint;

	protected LinkedList<LinkedList<CopyPasteSegment>> segments;

	// protected CopyPasteSegments() {

	// }

	CopyPasteSegments(MapPane mapPane, Point firstPoint, Point lastPoint) {
		minPoint = findMinPoint(firstPoint, lastPoint);
		maxPoint = findMaxPoint(firstPoint, lastPoint);

		// segments = mapPane.getSegmentPoints(firstPoint, lastPoint);
		segments = mapPane.getSegmentPoints(minPoint, maxPoint);
	}

	public Paint getPaint() {
		return paint;
	}

	public Stroke getStroke() {
		return stroke;
	}

	/*
	 * public void setSegments(LinkedList<LinkedList<Point>> segments) {
	 * this.segments = segments; }
	 */

	public LinkedList<LinkedList<CopyPasteSegment>> getSegments() {
		return segments;
	}

	public Point getMinPoint() {
		return minPoint;
	}

	public Point getMaxPoint() {
		return maxPoint;
	}

	protected Point findMinPoint(Point first, Point last) {
		Point point = new Point(Math.min(first.x, last.x), Math.min(first.y,
				last.y));
		return point;
	}

	protected Point findMaxPoint(Point first, Point last) {
		Point point = new Point(Math.max(first.x, last.x), Math.max(first.y,
				last.y));
		return point;
	}

	public boolean contains(Point point) {
		if (point.x >= minPoint.x && point.x <= maxPoint.x
				&& point.y >= minPoint.y && point.y <= maxPoint.y) {
			return true;
		} else {
			return false;
		}
	}

	public Iterator<CopyPasteSegment> iterator() {

		LinkedList<CopyPasteSegment> list = new LinkedList<CopyPasteSegment>();

		for (LinkedList<CopyPasteSegment> column : segments) {
			list.addAll(column);
		}

		return list.iterator();

	}

}
