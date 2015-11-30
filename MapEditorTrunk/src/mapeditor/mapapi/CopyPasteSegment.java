package mapeditor.mapapi;

import java.awt.Image;
import java.awt.Point;

import mapeditor.themesapi.MapObject;

public class CopyPasteSegment {
	private Point point;
	private MapObject mapObject;

	public CopyPasteSegment(MapObject mapObject, Point point) {
		this.point = point;
		this.mapObject = mapObject;
	}

	public void setMapObject(MapObject mapObject) {
		this.mapObject = mapObject;
	}

	public MapObject getMapObject() {
		return mapObject;
	}

	public Point getPoint() {
		return point;
	}

	public Image getImage() {
		return mapObject.getImageIcon().getImage();
	}

}
