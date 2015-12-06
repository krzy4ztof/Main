package mapeditor.mapapi;

import java.util.LinkedList;

import mapeditor.themesapi.CustomMapObject;
import mapeditor.themesapi.MapObject;

public class MapSegment {

	private LinkedList<MapObject> mapObjects = null;

	private LinkedList<CustomMapObject> customMapObjects = null;

	public MapSegment(MapObject mapObject, int layersNumber) {
		mapObjects = new LinkedList<MapObject>();
		customMapObjects = new LinkedList<CustomMapObject>();

		for (int i = 0; i < layersNumber; i++) {
			mapObjects.add(null);
			customMapObjects.add(null);
		}

		mapObjects.set(0, mapObject);
		// this.mapObject = mapObject;
	}

	public MapObject getMapObject() {
		return mapObjects.get(0);
		// return mapObject;
	}

	public MapObject getCustomMapObject() {
		// return customMapObject
		return customMapObjects.get(0);
	}

	public void setMapObject(MapObject mapObject) {
		System.out.println("Dodanie map object!");
		if (mapObject instanceof CustomMapObject) {
			System.out.println("Dodanie custom!");
			customMapObjects.set(0, (CustomMapObject) mapObject);
			// customMapObject = (CustomMapObject) mapObject;
		} else {
			mapObjects.set(0, mapObject);
			// this.mapObject = mapObject;
		}
	}
}
