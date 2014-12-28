package mapeditor.mapapi;

public class MapAttributes implements Cloneable {
	private int rows;
	private int columns;
	private MapLayout mapLayout;

	/**
	 * 
	 * @param rows
	 * @param columns
	 * @param mapLayout
	 */
	public MapAttributes(int rows, int columns, MapLayout mapLayout) {
		this.setRows(rows);
		this.setColumns(columns);
		this.setMapLayout(mapLayout);
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
