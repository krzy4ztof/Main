package mapeditor.mapapi;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Paint;
import java.awt.Point;
import java.awt.Stroke;

public class CustomObjectEdit {

	private MapSegment mapSegment;
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

	public void setMapSegment(MapSegment mapSegment, int layer, Point point) {
		this.mapSegment = mapSegment;
		this.objectLocation = new Point3D(point.x, point.y, layer);
		active = true;

	}

	public Point3D getObjectLocation() {
		return objectLocation;
	}

	public Point3D getPointPropertyLocation() {
		return pointPropertyLocation;
	}

	public void setPointPropertyLocation(Point3D pointPropertyLocation) {
		this.pointPropertyLocation = pointPropertyLocation;
	}

	public MapSegment getMapSegment() {
		return mapSegment;
	}

	public boolean isActive() {
		return active;
	}

	public void deactivate() {
		mapSegment = null;
		objectLocation = null;
		active = false;
	}
}
