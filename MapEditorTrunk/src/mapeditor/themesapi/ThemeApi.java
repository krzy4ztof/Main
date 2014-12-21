package mapeditor.themesapi;

import java.util.ArrayList;

import mapeditor.config.Config;

public class ThemeApi {

	private String name;

	/*
	 * Max number of columns. maxColumn = 3, means that
	 * column[0],column[1],column[2] are allowed
	 */
	private int maxColumn;

	private ArrayList<ArrayList<MapObject>> mapObjects;

	public ThemeApi(String name, Config config) {
		this.name = name;
		maxColumn = config.getMapApiColumnsNumber();
		mapObjects = new ArrayList<ArrayList<MapObject>>();
	}

	public void addMapObject(MapObject mapObject) {
		// System.out.println("LAST ROW: " + getRowsSize());
		// System.out.println("LAST COL: " + getLastColumnNumber());

		ArrayList<MapObject> row = null;
		if (mapObjects.isEmpty()) {
			row = new ArrayList<MapObject>();
			mapObjects.add(row);
		} else {
			row = mapObjects.get(mapObjects.size() - 1);
		}

		if (row.size() >= maxColumn) {
			row = new ArrayList<MapObject>();
			mapObjects.add(row);
		}

		row.add(mapObject);
	}

	/*
	 * private int getRowsSize() { return mapObjects.size(); }
	 * 
	 * private int getLastColumnNumber() { int rowNo = getRowsSize(); return
	 * mapObjects.get(rowNo).size(); }
	 */
}
