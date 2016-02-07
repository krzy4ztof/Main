package mapeditor.mapapi;

import java.util.LinkedList;

import mapeditor.themesapi.CustomMapObject;
import mapeditor.themesapi.MapObject;

public class MapSegment {

	private LinkedList<MapObject> mapObjects = null;

	private LinkedList<CustomMapObject> customMapObjects = null;

	public MapSegment(MapObject blankMapObject, int layersNumber) {
		mapObjects = new LinkedList<MapObject>();
		customMapObjects = new LinkedList<CustomMapObject>();

		for (int i = 0; i < layersNumber; i++) {
			mapObjects.add(blankMapObject);
			customMapObjects.add(null);
		}

		// mapObjects.set(0, blankMapObject);
		// this.mapObject = mapObject;
	}

	public void addLayers(int layersToAdd, MapObject blankMapObject) {

		for (int layerIndex = 0; layerIndex < layersToAdd; layerIndex++) {
			mapObjects.add(blankMapObject);
			customMapObjects.add(null);
		}

		// int curSize = mapObjects.size();

	}

	public void removeLayers(int layersToRemove) {
		for (int layerIndex = 0; layerIndex < layersToRemove; layerIndex++) {
			mapObjects.removeLast();
			customMapObjects.removeLast();
		}
	}

	public MapObject getMapObject(int layerIndex) {
		// System.out.println("getMpaObject layerIndex: " + layerIndex);
		return mapObjects.get(layerIndex);
		// return mapObject;
	}

	public CustomMapObject getCustomMapObject(int layerIndex) {
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
