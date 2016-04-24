package mapeditor.mapapi;

import java.awt.Image;
import java.awt.Point;

import mapeditor.themesapi.CustomMapObject;
import mapeditor.themesapi.MapObject;

public class CopyPasteSegment {
	private Point point;
	private MapObject mapObject;
	private CustomMapObject customMapObject;

	public CopyPasteSegment(MapObject mapObject,
			CustomMapObject customMapObject, Point point) {
		this.point = point;
		this.mapObject = mapObject;

		if (customMapObject != null) {
			this.customMapObject = customMapObject.clone();
		}
	}

	public void setMapObject(MapObject mapObject) {
		this.mapObject = mapObject;
	}

	public MapObject getMapObject() {
		return mapObject;
	}

	public void setCustomMapObject(CustomMapObject customMapObject) {
		this.customMapObject = customMapObject;
	}

	public CustomMapObject getCustomMapObject() {
		return customMapObject;
	}

	public Point getPoint() {
		return point;
	}

	public Image getImage() {
		return mapObject.getImageIcon().getImage();
	}

	public Image getCustomObjectImage() {
		if (customMapObject != null) {
			return customMapObject.getImageIcon().getImage();
		} else {
			return null;
		}
	}

}
