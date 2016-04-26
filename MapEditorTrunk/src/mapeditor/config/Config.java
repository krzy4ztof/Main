package mapeditor.config;

import java.io.File;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLClassLoader;
import java.util.Locale;
import java.util.ResourceBundle;

import mapeditor.mapapi.MapAttributes;
import mapeditor.mapapi.MapLayout;

public class Config {

	private final String mapApiColumnsNumber = "mapapi.columns.number";

	private final String mapApiRowsNumber = "mapapi.rows.number";

	private final String mapApiLayersNumber = "mapapi.layers.number";

	private final String mapApiLayout = "mapapi.layout";

	private final String guiLanguage = "gui.language";

	private final String themeApiColumnsNumber = "themeapi.columns.number";

	private final String toolBarIconsSize = "toolbar.icons.size";

	private ResourceBundle resourceBundle;

	public Config(String resourcesPath) throws MalformedURLException {
		File file = new File(resourcesPath);
		URL[] urls = new URL[] { file.toURI().toURL() };
		ClassLoader loader = new URLClassLoader(urls);

		resourceBundle = ResourceBundle.getBundle("config.config",
				Locale.getDefault(), loader);
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

	public Integer getMapApiLayersNumber() {
		String string = resourceBundle.getString(mapApiLayersNumber);
		Integer integer = new Integer(string);

		if (integer > MapAttributes.MAX_LAYERS_NUMBER) {
			return MapAttributes.MAX_LAYERS_NUMBER;
		} else {
			return integer;
		}
	}

	public boolean isMapApiLayoutHex() {
		String string = resourceBundle.getString(mapApiLayout);
		if (string.equalsIgnoreCase(MapLayout.HEX.toString())) {
			return true;
		}
		return false;
	}

	public boolean isMapApiLayoutSqr() {
		String string = resourceBundle.getString(mapApiLayout);
		if (string.equalsIgnoreCase(MapLayout.SQR.toString())) {
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
