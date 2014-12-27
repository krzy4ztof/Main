package mapeditor.mainwindow;

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

	@Override
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

}
