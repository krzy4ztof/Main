package mapeditor.mapapi;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Paint;
import java.awt.Point;
import java.awt.Stroke;
import java.util.Iterator;
import java.util.LinkedList;

import mapeditor.mainwindow.MapPane;

public class CopyPasteSegments {

	protected Paint paint;

	protected Stroke stroke;

	protected Paint paintRectangle;

	protected Point minPoint;

	protected Point maxPoint;

	protected boolean active;

	protected LinkedList<LinkedList<CopyPasteSegment>> segments;

	CopyPasteSegments() {
		active = false;

		paintRectangle = Color.BLACK;
		float dash[] = { 5.0f };
		stroke = new BasicStroke(3.0f, BasicStroke.CAP_ROUND,
				BasicStroke.JOIN_ROUND, 5.0f, dash, 0.0f);
	}

	protected void activate(MapPane mapPane, Point firstPoint, Point lastPoint,
			int layerIndex) {
		minPoint = findMinPoint(firstPoint, lastPoint);
		maxPoint = findMaxPoint(firstPoint, lastPoint);

		// int layerIndex = 0; // TODO zmienic
		segments = mapPane.getSegmentPoints(minPoint, maxPoint, layerIndex);
		active = true;
	}

	public boolean isActive() {
		return active;
	}

	public void deactivate() {
		minPoint = null;
		maxPoint = null;
		segments = null;

		active = false;
	}

	public Paint getPaint() {
		return paint;
	}

	public Stroke getStroke() {
		return stroke;
	}

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

	protected void drawRectangle(Graphics graphics, Point first, Point last) {
		int minX = Math.min(first.x, last.x);
		int minY = Math.min(first.y, last.y);
		int maxX = Math.max(first.x, last.x);
		int maxY = Math.max(first.y, last.y);
		int width = maxX - minX;
		int height = maxY - minY;

		graphics.drawRect(minX, minY, width, height);

	}

	public void paint(Graphics graphics) {

		if (graphics instanceof Graphics2D) {
			Graphics2D g2 = (Graphics2D) graphics;
			g2.setStroke(stroke);
			g2.setPaint(paintRectangle);
		}
		if (isActive()) {

			drawRectangle(graphics, minPoint, maxPoint);
		}
	}
}
