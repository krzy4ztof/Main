package mapeditor.config;

import java.util.ResourceBundle;

public class Config {

	private final String mapApiColumnsNumber = "mapapi.columns.number";

	private final String mapApiRowsNumber = "mapapi.rows.number";

	private final String mapApiLayout = "mapapi.layout";

	private final String guiLanguage = "gui.language";

	private final String themeApiColumnsNumber = "themeapi.columns.number";

	private final String toolBarIconsSize = "toolbar.icons.size";

	private ResourceBundle resourceBundle;

	public Config() {
		resourceBundle = ResourceBundle.getBundle("mapeditor.config.config");
	}

	public Integer getMapApiColumnsNumber() {
		String string = resourceBundle.getString(mapApiColumnsNumber);
		Integer integer = new Integer(string);
		return integer;
	}

	public Integer getMapApiRowsNumber() {
		String string = resourceBundle.getString(mapApiRowsNumber);
		Integer integer = new Integer(string);
		return integer;
	}

	public boolean isMapApiLayoutHex() {
		String string = resourceBundle.getString(mapApiLayout);
		if (string.equalsIgnoreCase("HEX")) {
			return true;
		}
		return false;
	}

	public boolean isMapApiLayoutSqr() {
		String string = resourceBundle.getString(mapApiLayout);
		if (string.equalsIgnoreCase("SQR")) {
			return true;
		}
		return false;
	}

	public String getLanguage() {
		String language = resourceBundle.getString(guiLanguage);
		return language;
	}

	public Integer getThemeApiColumnsNumber() {
		String string = resourceBundle.getString(themeApiColumnsNumber);
		Integer integer = new Integer(string);
		return integer;
	}

	public Integer getToolBarIconsSize() {
		String string = resourceBundle.getString(toolBarIconsSize);
		Integer integer = new Integer(string);
		return integer;
	}

}
