package mapeditor.themesapi;

import java.util.LinkedList;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;

import mapeditor.config.Config;
import mapeditor.logger.MapLogger;

public class ThemeApi {

	private static final Logger logger = Logger.getLogger(ThemeApi.class
			.getName());

	private String name;

	/*
	 * Max number of columns. maxColumn = 3, means that
	 * column[0],column[1],column[2] are allowed
	 */
	private int maxColumn;

	private LinkedList<LinkedList<MapObject>> mapObjects;

	public ThemeApi(String name, Config config) {
		this.name = name;
		maxColumn = config.getThemeApiColumnsNumber();
		mapObjects = new LinkedList<LinkedList<MapObject>>();
	}

	public List<MapObject> getAllMapObjects() {
		List<MapObject> list = new LinkedList<MapObject>();

		for (LinkedList<MapObject> row : mapObjects) {
			list.addAll(row);
		}
		return list;
	}

	public MapObject getMapObject(String name) {
		for (MapObject mapObject : getAllMapObjects()) {
			if (mapObject.getObjectName().equals(name)) {
				return mapObject;
			}
		}
		return null;
	}

	public void addMapObject(MapObject mapObject) {
		LinkedList<MapObject> row = null;
		if (mapObjects.isEmpty()) {
			row = new LinkedList<MapObject>();
			mapObjects.add(row);
		} else {
			row = mapObjects.getLast();
		}

		if (row.size() >= maxColumn) {
			row = new LinkedList<MapObject>();
			mapObjects.add(row);
		}

		row.add(mapObject);
	}

	public void describeYourself() {

		logger.log(Level.FINE, MapLogger.DESCRIBE_THEME, name);

		for (LinkedList<MapObject> row : mapObjects) {
			logger.log(Level.FINE, MapLogger.DESCRIBE_THEME_ROW);

			for (MapObject mapObject : row) {
				mapObject.describeYourself();
			}

		}
	}

	public MapObject getMapObject(int row, int col) {

		if (row >= mapObjects.size()) {
			return null;
		}

		LinkedList<MapObject> objectsRow = mapObjects.get(row);

		if (col >= objectsRow.size()) {
			return null;
		}

		MapObject mapObject = objectsRow.get(col);
		return mapObject;
	}

	public int getColumnsSize() {
		List<MapObject> list = mapObjects.getFirst();
		if (list != null) {
			return list.size();
		} else {
			return 0;
		}
	}

	public int getRowsSize() {
		return mapObjects.size();
	}

	public String getName() {
		return name;
	}
}
