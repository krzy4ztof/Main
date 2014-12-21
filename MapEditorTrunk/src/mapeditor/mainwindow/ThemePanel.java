package mapeditor.mainwindow;

import java.awt.Image;

import mapeditor.themesapi.MapThemesManager;

public class ThemePanel extends GridPanel {

	private static int LEFT_MARIGIN = 10;
	private static int RIGHT_MARIGIN = 10;
	private static int TOP_MARIGIN = 10;
	private static int BOTTOM_MARIGIN = 10;

	private MapThemesManager mapThemesManager;

	public ThemePanel(MapThemesManager mapThemesManager) {
		super();
		this.mapThemesManager = mapThemesManager;
	}

	@Override
	protected int getGridApiColumnsSize() {
		return 10;
	};

	@Override
	protected int getGridApiRowsSize() {
		return 10;
	};

	@Override
	protected Image getImage(int row, int col) {
		return this.blank.getImage();
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

}
