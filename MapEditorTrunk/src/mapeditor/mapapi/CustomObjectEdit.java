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
	// private int layer;
	// private Point point;
	private Point3D objectLocation;
	private Paint objectLocationPaint;
	private Stroke objectLocationStroke;

	private Paint pointPropertyPaint;
	private Stroke pointPropertyStroke;
	private Point3D pointPropertyLocation;

	private boolean active;

	public CustomObjectEdit() {
		active = false;

		objectLocationPaint = Color.ORANGE;
		pointPropertyPaint = Color.YELLOW;

		// paint = Color.ORANGE;
		float dash[] = { 5.0f };
		objectLocationStroke = new BasicStroke(3.0f, BasicStroke.CAP_ROUND,
				BasicStroke.JOIN_ROUND, 5.0f, dash, 0.0f);
		pointPropertyStroke = new BasicStroke(3.0f, BasicStroke.CAP_ROUND,
				BasicStroke.JOIN_ROUND, 5.0f, dash, 0.0f);
	}

	public Paint getPointPropertyPaint() {
		return pointPropertyPaint;
	}

	public Stroke getPointPropertyStroke() {
		return pointPropertyStroke;
	}

	public Paint getObjectLocationPaint() {
		return objectLocationPaint;
	}

	public Stroke getObjectLocationStroke() {
		return objectLocationStroke;
	}

	public void setCustomObject(CustomMapObject customMapObject,
			MapSegment mapSegment, int layer, Point point) {
		this.customMapObject = customMapObject;
		this.mapSegment = mapSegment;
		this.objectLocation = new Point3D(point.x, point.y, layer);
		active = true;

	}

	public Point3D getObjectLocation() {
		return objectLocation;
	}

	public Point3D getPointPropertyLocation() {

		// TODO: change
		return pointPropertyLocation;
	}

	public void setPointPropertyLocation(Point3D pointPropertyLocation) {

		// TODO: change
		this.pointPropertyLocation = pointPropertyLocation;
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

		this.customMapObject = null;
		this.mapSegment = null;
		this.objectLocation = null;

		active = false;
	}

	public void paint(Graphics graphics) {
		// selectedSegments.paint(graphics);
		// draggedSegments.paint(graphics);
		if (graphics instanceof Graphics2D) {
			Graphics2D g2 = (Graphics2D) graphics;
			g2.setStroke(objectLocationStroke);
			g2.setPaint(objectLocationPaint);
		}
		if (isActive()) {

			// drawRectangle(graphics, minPoint, maxPoint);
		}

	}

}
