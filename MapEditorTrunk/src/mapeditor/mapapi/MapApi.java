package mapeditor.mapapi;

import java.io.File;
import java.util.LinkedList;

import mapeditor.config.Config;
import mapeditor.themesapi.MapObject;

public class MapApi {

	// private int Columns,Rows;
	/* ilosc kolumn i wierszy mapy */
	// private int Image_theme[10][10];//do zmiany na dynamiczne
	/*
	 * numer tematu do kt�rego nale�y obrazek na segmencie [x][y]
	 */
	// private int Image_no[10][10]//do zmiany na dynamiczne
	/* numer obrazeku na segmencie [x][y] */
	// private ImagesList p_ImagesList;// tego tu nnie b�dzie
	private LinkedList<LinkedList<MapSegment>> segments;

	private Config config;

	private MapLayout mapLayout;

	/**
	 * Stores reference to file from which map was loaded or to which it was
	 * saved
	 */
	private File file = null;

	/**
	 * Constructor. No number of rows nor columns is given. The next method to
	 * invoke should be setSize(col, row) method.
	 *
	 */
	public MapApi() {

	}

	public MapApi(Config configParam, Tools tools) {
		config = configParam;
		if (config.isMapApiLayoutHex()) {
			mapLayout = MapLayout.HEX;
		} else {
			mapLayout = MapLayout.SQR;
		}

		resetMap(config.getMapApiColumnsNumber(), config.getMapApiRowsNumber(),
				tools.getBlankMapObject());
	}

	/**
	 * Constructor
	 * 
	 * @param col
	 *            Number of columns. When col <= 0 then default number of
	 *            columns is set.
	 * @param row
	 *            Number of rows. When row <= then default number of rows is
	 *            set.
	 */
	public MapApi(int col, int row, MapObject blankMapObject) {
		this.resetMap(col, row, blankMapObject);
	}

	public boolean isLayoutHex() {
		if (mapLayout.equals(MapLayout.HEX)) {
			return true;
		}
		return false;
	}

	public boolean isLayoutSqr() {
		if (mapLayout.equals(MapLayout.SQR)) {
			return true;
		}
		return false;
	}

	/**
	 * Set size of MapApi. THe method should be invoked after MapApi()
	 * constructor
	 * 
	 * @param col
	 *            Number of columns. When col <= 0 then default number of
	 *            columns is set.
	 * @param row
	 *            Number of rows. When row <= then default number of rows is
	 *            set.
	 */
	public void resetMap(int cols, int rows, MapObject blankMapObject) {
		if (cols <= 0) {
			cols = config.getMapApiColumnsNumber();
		}
		if (rows <= 0) {
			rows = config.getMapApiRowsNumber();
		}

		segments = new LinkedList<LinkedList<MapSegment>>();
		LinkedList<MapSegment> newRow;
		MapSegment se;
		for (int i = 0; i < rows; i++) {
			newRow = new LinkedList<MapSegment>();
			segments.add(newRow);

			for (int j = 0; j < cols; j++) {
				se = new MapSegment(blankMapObject);
				newRow.add(se);
			}
		}
		file = null;
	}

	/**
	 * Increases or decreases map size without deleting already existing
	 * MapSegments
	 * 
	 * @param rows
	 * @param cols
	 */
	public void changeSize(int rows, int cols, MapObject blankMapObject) {
		if (rows > 0) {
			changeRowsSize(rows, blankMapObject);
		}

		if (cols > 0) {
			changeColumnsSize(cols, blankMapObject);
		}

	}

	/**
	 * Increases or decreases map rows size without deleting already existing
	 * MapSegments
	 * 
	 * @param rows
	 */
	private void changeRowsSize(int rows, MapObject blankMapObject) {
		int rowsSize = getRowsSize();
		int colsSize = getColumnsSize();
		LinkedList<MapSegment> newRow = null;
		MapSegment segment = null;

		if (rows > rowsSize) {
			for (int i = rowsSize; i < rows; i++) {
				newRow = new LinkedList<MapSegment>();
				segments.add(newRow);
				for (int j = 0; j < colsSize; j++) {
					segment = new MapSegment(blankMapObject);
					newRow.add(segment);
				}
			}
		} else if (rows < rowsSize) {
			for (int i = rows; i < rowsSize; i++) {
				segments.removeLast();
			}
		}
	}

	/**
	 * Increases or decreases map rows size without deleting already existing
	 * MapSegments
	 * 
	 * @param cols
	 */
	private void changeColumnsSize(int cols, MapObject blankMapObject) {
		int colsSize = getColumnsSize();
		MapSegment segment = null;

		if (cols > 0) {
			if (cols > colsSize) {
				for (LinkedList<MapSegment> row : segments) {
					for (int i = colsSize; i < cols; i++) {
						segment = new MapSegment(blankMapObject);
						row.add(segment);
					}
				}
			} else if (cols < colsSize) {
				for (LinkedList<MapSegment> row : segments) {
					for (int i = cols; i < colsSize; i++) {
						row.removeLast();
					}
				}
			}
		}
	}

	public MapSegment getSegment(int row, int col) {
		return segments.get(row).get(col);
	}

	/**
	 *
	 * @return Number of map columns
	 */
	public int getColumnsSize() {
		return segments.get(0).size();
	}

	/**
	 *
	 * @return number of map rows
	 */
	public int getRowsSize() {
		return segments.size();
	}

	/**
	 *
	 * @return File from which map was loaded or to which it was saved
	 */
	public File getFile() {
		return file;
	}

	/**
	 *
	 * @param file
	 *            File from which map was loaded or to which it was saved
	 */
	public void setFile(File file) {
		this.file = file;
	}

	public MapAttributes getMapAttributes() {
		MapAttributes mapAttributes = new MapAttributes(getRowsSize(),
				getColumnsSize(), mapLayout);
		return mapAttributes;
	}
}
