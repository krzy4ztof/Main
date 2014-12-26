package mapeditor.mainwindow;

import java.awt.Image;

import mapeditor.themesapi.MapObject;
import mapeditor.themesapi.ThemeApi;

public class SingleThemePane extends GridPanel {

	private static int LEFT_MARIGIN = 10;
	private static int RIGHT_MARIGIN = 10;
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
	protected Image getImage(int row, int col) {

		MapObject mapObject = themeApi.getMapObject(row, col);

		if (mapObject != null) {
			return mapObject.getImageIcon().getImage();
		} else {
			return getBlankImage();
		}
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
