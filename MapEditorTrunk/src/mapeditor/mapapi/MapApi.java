package mapeditor.mapapi;

import java.io.File;
import java.util.LinkedList;

import mapeditor.config.Config;
import mapeditor.themesapi.MapObject;
import mapeditor.themesapi.MapObjectFactory;

public class MapApi {

	private LinkedList<LinkedList<MapSegment>> segments;

	private LinkedList<LayerAttributes> layersAttributes;

	// private int activeLayerIndex = 0;

	private MapLayout mapLayout;

	// private int layers;

	/**
	 * Stores reference to file from which map was loaded or to which it was
	 * saved
	 */
	private File file = null;

	public MapApi(Config config, MapObjectFactory mapObjectFactory) {
		MapLayout mapLayout;
		if (config.isMapApiLayoutHex()) {
			mapLayout = MapLayout.HEX;
		} else {
			mapLayout = MapLayout.SQR;
		}

		// layers = config.getMapApiLayersNumber();

		MapAttributes mapAttributes = new MapAttributes(
				config.getMapApiRowsNumber(), config.getMapApiColumnsNumber(),
				config.getMapApiLayersNumber(), mapLayout);

		resetMap(mapAttributes, mapObjectFactory.getBlankMapObject());

	}

	public LinkedList<LayerAttributes> getLayersAttributes() {
		return layersAttributes;
	}

	public int getActiveLayerIndex() {

		for (LayerAttributes layerAttributes : layersAttributes) {
			if (layerAttributes.isActive()) {
				return layerAttributes.getIndex();
			}
		}

		return LayerAttributes.NO_ACTIVE_LAYER;
	}

	public void setActiveLayerIndex(int activeLayerIndex) {

		for (LayerAttributes layerAttributes : layersAttributes) {
			if (layerAttributes.getIndex() == activeLayerIndex) {
				layerAttributes.setActive(true);
			} else {
				layerAttributes.setActive(false);
			}

		}

		// this.activeLayerIndex = activeLayerIndex;
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

	public MapLayout getMapLayout() {
		return mapLayout;
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
	public void resetMap(MapAttributes mapAttributes, MapObject blankMapObject) {
		int cols = mapAttributes.getColumns();
		int rows = mapAttributes.getRows();
		int layersNumber = mapAttributes.getLayers();
		mapLayout = mapAttributes.getMapLayout();

		layersAttributes = new LinkedList<LayerAttributes>();

		for (int i = 0; i < layersNumber; i++) {
			LayerAttributes layerAttributes = new LayerAttributes(i);

			// if (i == 0) {
			// layerAttributes.setActive(true);
			// }

			layersAttributes.add(layerAttributes);

		}

		setActiveLayerIndex(0);

		segments = new LinkedList<LinkedList<MapSegment>>();
		LinkedList<MapSegment> newRow;
		MapSegment se;
		for (int i = 0; i < rows; i++) {
			newRow = new LinkedList<MapSegment>();
			segments.add(newRow);

			for (int j = 0; j < cols; j++) {
				se = new MapSegment(blankMapObject, layersNumber);
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
	public void changeAttributes(MapAttributes mapAttributes,
			MapObject blankMapObject) {

		int rows = mapAttributes.getRows();
		int cols = mapAttributes.getColumns();
		int layers = mapAttributes.getLayers();
		mapLayout = mapAttributes.getMapLayout();

		if (layers > 0) {
			changeLayersSize(layers, blankMapObject);
		}

		if (rows > 0) {
			changeRowsSize(rows, blankMapObject);
		}

		if (cols > 0) {
			changeColumnsSize(cols, blankMapObject);
		}
	}

	/**
	 * Increases or decreases map layers number without deleting already
	 * existing layers
	 * 
	 * @param rows
	 */
	private void changeLayersSize(int layers, MapObject blankMapObject) {
		int layersSize = getLayerAttributesSize();

		if (layers > layersSize) {
			int addLayers = layers - layersSize;

			for (int layerIndex = layersSize; layerIndex < layers; layerIndex++) {
				layersAttributes.add(new LayerAttributes(layerIndex));
			}

			setActiveLayerIndex(0);

			for (LinkedList<MapSegment> row : segments) {
				for (MapSegment segment : row) {
					segment.addLayers(addLayers, blankMapObject);
				}
			}
		} else if (layers < layersSize) {

			int removeLayers = layersSize - layers;

			for (int i = 0; i < removeLayers; i++) {
				layersAttributes.removeLast();
			}

			setActiveLayerIndex(0);

			for (LinkedList<MapSegment> row : segments) {
				for (MapSegment segment : row) {

					segment.removeLayers(removeLayers);

				}
			}
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
					segment = new MapSegment(blankMapObject,
							getLayerAttributesSize());
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
						segment = new MapSegment(blankMapObject,
								getLayerAttributesSize());
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
		MapSegment segment = null;

		if (row < 0 || col < 0 || row >= segments.size()) {
			return null;
		}

		LinkedList<MapSegment> segmentRow = segments.get(row);
		if (segmentRow != null) {
			if (col >= segmentRow.size()) {
				return null;
			} else {
				segment = segmentRow.get(col);
			}

		}

		return segment;
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
	 * @return number of map rows
	 */
	public int getLayerAttributesSize() {
		return layersAttributes.size();
	}

	/**
	 *
	 * @return File from which map was loaded or to which it was saved
	 */
	public File getFile() {
		return file;
	}

	public LayerAttributes getLayerAttributes(int index) {
		return layersAttributes.get(index);
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
				getColumnsSize(), getLayerAttributesSize(), mapLayout);
		return mapAttributes;
	}
}
