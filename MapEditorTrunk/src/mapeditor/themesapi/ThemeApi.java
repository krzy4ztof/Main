package mapeditor.themesapi;

import java.util.LinkedList;
import java.util.List;

import mapeditor.config.Config;

public class ThemeApi {

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

	public void addMapObject(MapObject mapObject) {
		// System.out.println("LAST ROW: " + getRowsSize());
		// System.out.println("LAST COL: " + getLastColumnNumber());

		LinkedList<MapObject> row = null;
		if (mapObjects.isEmpty()) {
			row = new LinkedList<MapObject>();
			mapObjects.add(row);
		} else {
			row = mapObjects.getLast();
			// row = mapObjects.get(mapObjects.size() - 1);
		}

		if (row.size() >= maxColumn) {
			row = new LinkedList<MapObject>();
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

	public void describeYourself() {

		System.out.println("***\tTheme name: " + name + "\t***");

		for (LinkedList<MapObject> row : mapObjects) {
			System.out.println("Row: ");
			for (MapObject mapObject : row) {
				mapObject.describeYourself();
			}

		}
	}

	public MapObject getMapObject(int row, int col) {

		if (row >= mapObjects.size()) {
			return null;
		}

		// System.out.println("ROW: " + row + " COL: " + col);
		// System.out.println("SIZE: " + mapObjects.size());

		LinkedList<MapObject> objectsRow = mapObjects.get(row);

		if (col >= objectsRow.size()) {
			return null;
		}
		// System.out.println("SIZE2: " + objectsRow.size());

		MapObject mapObject = objectsRow.get(col);

		// System.out.println("!!!");
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
