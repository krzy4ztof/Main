package mapeditor.mapapi;

import mapeditor.themesapi.MapObject;

public class MapSegment {

	private MapObject mapObject = null;

	public MapSegment(MapObject mapObject) {
		this.mapObject = mapObject;
	}

	public MapObject getMapObject() {
		return mapObject;
	}

	public void setMapObject(MapObject mapObject) {
		this.mapObject = mapObject;
	}
}
