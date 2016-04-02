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
	}

	public void addLayers(int layersToAdd, MapObject blankMapObject) {
		for (int layerIndex = 0; layerIndex < layersToAdd; layerIndex++) {
			mapObjects.add(blankMapObject);
			customMapObjects.add(null);
		}
	}

	public void removeLayers(int layersToRemove) {
		for (int layerIndex = 0; layerIndex < layersToRemove; layerIndex++) {
			mapObjects.removeLast();
			customMapObjects.removeLast();
		}
	}

	public MapObject getMapObject(int layerIndex) {
		return mapObjects.get(layerIndex);
	}

	public CustomMapObject getCustomMapObject(int layerIndex) {
		return customMapObjects.get(layerIndex);
	}

	public void setMapObject(MapObject mapObject, int layerIndex) {
		if (mapObject instanceof CustomMapObject) {
			CustomMapObject custom = (CustomMapObject) mapObject;
			customMapObjects.set(layerIndex, custom.clone());
		} else {
			mapObjects.set(layerIndex, mapObject);
		}
	}
}
