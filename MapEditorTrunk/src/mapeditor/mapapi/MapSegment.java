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

	public MapObject getMapObject(int layerIndex) {
		return mapObjects.get(layerIndex);
		// return mapObject;
	}

	public MapObject getCustomMapObject(int layerIndex) {
		// return customMapObject
		return customMapObjects.get(layerIndex);
	}

	public void setMapObject(MapObject mapObject, int layerIndex) {
		System.out.println("Dodanie map object!");
		if (mapObject instanceof CustomMapObject) {
			System.out.println("Dodanie custom!");
			// customMapObjects.set(0, (CustomMapObject) mapObject);
			customMapObjects.set(layerIndex, (CustomMapObject) mapObject);
			// customMapObject = (CustomMapObject) mapObject;
		} else {
			// mapObjects.set(0, mapObject);
			mapObjects.set(layerIndex, mapObject);
			// this.mapObject = mapObject;
		}
	}
}
