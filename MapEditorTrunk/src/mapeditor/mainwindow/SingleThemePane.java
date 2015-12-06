package mapeditor.mainwindow;

import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Image;

import mapeditor.themesapi.MapObject;
import mapeditor.themesapi.ThemeApi;

public class SingleThemePane extends GridPane {

	public static int LEFT_MARIGIN = 10;
	public static int RIGHT_MARIGIN = 10;
	private static int TOP_MARIGIN = 10;
	private static int BOTTOM_MARIGIN = 10;

	private ThemeApi themeApi;

	public SingleThemePane(ThemeApi themeApi) {
		super();
		this.themeApi = themeApi;
	}

	@Override
	protected int getGridApiColumnsSize() {
		return themeApi.getColumnsSize();
	};

	@Override
	protected int getGridApiRowsSize() {
		return themeApi.getRowsSize();
	};

	protected MapObject getMapObject(int row, int col) {

		MapObject mapObject = themeApi.getMapObject(row, col);

		return mapObject;

		/*
		 * if (mapObject != null) { return mapObject.getImageIcon().getImage();
		 * } else { // return getBlankImage(); return null; }
		 */
	}

	@Override
	protected int getLeftMarigin() {
		return LEFT_MARIGIN;
	}

	@Override
	protected int getRightMarigin() {
		return RIGHT_MARIGIN;
	}

	@Override
	protected int getTopMarigin() {
		return TOP_MARIGIN;
	}

	@Override
	protected int getBottomMarigin() {
		return BOTTOM_MARIGIN;
	}

	public ThemeApi getTheme() {
		return themeApi;
	}

	/*
	 * @Override protected MapObject getCustomMapObject(int row, int col) { //
	 * Co z tym zrobic? return null; }
	 */

	private void drawSegment(Graphics graphics, int column, int row, int divider) {
		MapObject mapObject = getMapObject(row, column);
		if (mapObject != null) {
			Image image = mapObject.getImageIcon().getImage();
			drawSegment(graphics, column, row, divider, image, getPaint(),
					getStroke());
		}

		/*
		 * MapObject customMapObject = getCustomMapObject(row, column); if
		 * (customMapObject != null) { Image image =
		 * customMapObject.getImageIcon().getImage(); drawSegment(graphics,
		 * column, row, divider, image, paint, stroke); }
		 */
	}

	// @Override
	@Override
	public void paint(Graphics graphics) {

		int divider = 1;
		if (isLayoutHex()) {
			divider = 2;
		}

		int firstColumn = getFirstVisibleColumnNumber();// + 1;
		int lastColumn = getLastVisibleColumnNumber();// - 1;
		int firstRow = getFirstVisibleRowNumber();// + 1;
		int lastRow = getLastVisibleRowNumber();// - 1;

		for (int column = firstColumn; column <= lastColumn; column++) {
			for (int row = firstRow; row <= lastRow; row++) {
				if (((column) % 2) == 0) {
					drawSegment(graphics, column, row, 1);
				} else {
					drawSegment(graphics, column, row, divider);
				}
			}
		}

		int mapWidth = getGridWidth();
		int mapHeight = getGridHeight();

		panel.setPreferredSize(new Dimension(mapWidth, mapHeight));
		panel.revalidate();

	}

}
