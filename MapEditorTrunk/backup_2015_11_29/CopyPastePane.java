package mapeditor.mainwindow;

import mapeditor.themesapi.MapObject;

public class CopyPastePane extends GridPane {

	@Override
	protected int getGridApiColumnsSize() {
		return 0;
	}

	@Override
	protected int getGridApiRowsSize() {
		return 0;
	}

	@Override
	protected MapObject getMapObject(int row, int col) {
		return null;
	}

}
