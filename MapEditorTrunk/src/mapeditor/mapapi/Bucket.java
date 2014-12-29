package mapeditor.mapapi;

import java.awt.Point;
import java.util.HashMap;

import mapeditor.themesapi.MapObject;

public class Bucket {

	private HashMap<Point, Boolean> segments;
	private MapApi mapApi;

	public Bucket(MapApi mapApi) {
		this.mapApi = mapApi;
		segments = new HashMap<Point, Boolean>();
	}

	public void fill(MapObject mapObject, Point point) {

		if (point.x < 0 || point.x >= mapApi.getColumnsSize()) {
			return;
		}

		if (point.y < 0 || point.y >= mapApi.getRowsSize()) {
			return;
		}

		MapObject curMapObject = mapApi.getSegment(point.y, point.x)
				.getMapObject();

		if (segments.containsKey(point)) {
			return;
		}

		if (curMapObject.equals(mapObject)) {
			segments.put(point, true);
		} else {
			segments.put(point, false);
			return;
		}

		fill(mapObject, new Point(point.x, point.y + 1));
		fill(mapObject, new Point(point.x, point.y - 1));

		fill(mapObject, new Point(point.x + 1, point.y));
		fill(mapObject, new Point(point.x - 1, point.y));

		if (mapApi.isLayoutHex()) {

			if (point.x % 2 == 0) {
				fill(mapObject, new Point(point.x - 1, point.y - 1));
				fill(mapObject, new Point(point.x + 1, point.y - 1));
			} else {
				fill(mapObject, new Point(point.x - 1, point.y + 1));
				fill(mapObject, new Point(point.x + 1, point.y + 1));
			}
		}
	}

	public void paint(MapObject mapObject) {
		for (Point point : segments.keySet()) {

			Boolean value = segments.get(point);
			if (value) {
				mapApi.getSegment(point.y, point.x).setMapObject(mapObject);
			}
		}
	}

}
