package mapeditor.mapapi;

public class MapAttributes implements Cloneable {

	public static final int MAX_LAYERS_NUMBER = 10;

	private int rows;
	private int columns;
	private MapLayout mapLayout;
	private int layers;

	/**
	 * 
	 * @param rows
	 * @param columns
	 * @param mapLayout
	 */
	public MapAttributes(int rows, int columns, int layers, MapLayout mapLayout) {
		this.rows = rows;
		this.columns = columns;
		this.layers = layers;
		this.mapLayout = mapLayout;
	}

	public int getLayers() {
		return layers;
	}

	public void setLayers(int rows) {
		this.layers = rows;
	}

	public int getRows() {
		return rows;
	}

	public void setRows(int rows) {
		this.rows = rows;
	}

	public int getColumns() {
		return columns;
	}

	public void setColumns(int columns) {
		this.columns = columns;
	}

	public MapLayout getMapLayout() {
		return mapLayout;
	}

	public void setMapLayout(MapLayout mapLayout) {
		this.mapLayout = mapLayout;
	}

	@Override
	public MapAttributes clone() throws CloneNotSupportedException {
		return (MapAttributes) super.clone();
	}
}
