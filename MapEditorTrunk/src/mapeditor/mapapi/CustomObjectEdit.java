package mapeditor.mapapi;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Paint;
import java.awt.Point;
import java.awt.Stroke;

import mapeditor.themesapi.CustomMapObject;

public class CustomObjectEdit {

	private CustomMapObject customMapObject;
	private MapSegment mapSegment;
	private int layer;
	private Point point;

	private Paint paint;
	private Stroke stroke;
	private boolean active;

	public CustomObjectEdit() {
		active = false;

		paint = Color.ORANGE;
		float dash[] = { 5.0f };
		stroke = new BasicStroke(3.0f, BasicStroke.CAP_ROUND,
				BasicStroke.JOIN_ROUND, 5.0f, dash, 0.0f);
	}

	public Paint getPaint() {
		return paint;
	}

	public Stroke getStroke() {
		return stroke;
	}

	public void setCustomObject(CustomMapObject customMapObject,
			MapSegment mapSegment, int layer, Point point) {
		this.customMapObject = customMapObject;
		this.mapSegment = mapSegment;
		this.layer = layer;
		this.point = point;
		active = true;

	}

	public Point getPoint() {
		return point;
	}

	public MapSegment getMapSegment() {
		return mapSegment;
	}

	public boolean isActive() {
		return active;
	}

	public void deactivate() {
		// minPoint = null;
		// maxPoint = null;
		// segments = null;

		active = false;
	}

	public void paint(Graphics graphics) {
		// selectedSegments.paint(graphics);
		// draggedSegments.paint(graphics);
		if (graphics instanceof Graphics2D) {
			Graphics2D g2 = (Graphics2D) graphics;
			g2.setStroke(stroke);
			g2.setPaint(paint);
		}
		if (isActive()) {

			// drawRectangle(graphics, minPoint, maxPoint);
		}

	}

}
