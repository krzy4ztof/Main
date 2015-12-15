package mapeditor.messages;

import java.util.Locale;
import java.util.MissingResourceException;
import java.util.ResourceBundle;

import mapeditor.config.Config;

public class MapMessages {

	public static String MENU_FILE = "mainwindow.file";
	public static String MENU_NEW = "mainwindow.new";
	public static String MENU_OPEN = "mainwindow.open";
	public static String MENU_CLOSE = "mainwindow.close";
	public static String MENU_SAVE = "mainwindow.save";
	public static String MENU_EDIT = "mainwindow.edit";
	public static String MENU_ATTRIBUTES = "mainwindow.attributes";
	public static String MENU_REFRESH = "mainwindow.refresh";
	public static String MENU_NAVIGATION = "mainwindow.navigation";
	public static String MENU_ZOOM_IN = "mainwindow.zoomin";
	public static String MENU_ZOOM_OUT = "mainwindow.zoomout";
	public static String MENU_DEFAULT_ZOOM = "mainwindow.defaultzoom";
	public static String MENU_OBJECTS = "mainwindow.objects";
	public static String MENU_CENTER_MAP = "mainwindow.centermap";

	public static String THEMENAME = "mainwindow.theme.";

	public static String MSG_SAVING_FAILED = "mainwindow.savingfailed";
	public static String MSG_SAVE_CHANGES = "mainwindow.savechanges?";
	public static String MSG_LOADING_FAILED = "mainwindow.loadingfailed";

	public static String MAPSAVER_MAP_NAME = "mapsaver.mapname";

	public static String ATTR_TITLE = "mapattributes.tile";
	public static String ATTR_ROW_NUMBER = "mapattributes.rownumber";
	public static String ATTR_COL_NUMBER = "mapattributes.colnumber";
	public static String ATTR_LAYERS_NUMBER = "mapattributes.layersnumber";
	public static String ATTR_LAYOUT = "mapattributes.layout";
	public static String ATTR_DEFAULT_SIZE = "mapattributes.defaultsize";
	public static String ATTR_PREVIOUS_SIZE = "mapattributes.previoussize";
	public static String ATTR_OK = "mapattributes.ok";
	public static String ATTR_CANCEL = "mapattributes.cancel";

	public static String LAY_HEX = "maplayout.hex";
	public static String LAY_SQR = "maplayout.sqr";

	public static String TOOLBAR_TITLE = "toolbar.title";
	public static String TOOLBAR_ERASER = "toolbar.eraser";
	public static String TOOLBAR_BRUSH = "toolbar.brush";
	public static String TOOLBAR_BUCKET = "toolbar.bucket";
	public static String TOOLBAR_PICKER = "toolbar.picker";
	public static String TOOLBAR_SELECTION = "toolbar.selection";

	ResourceBundle resourceBundle;

	public MapMessages(Config config) {
		Locale currentLocale;
		currentLocale = new Locale(config.getLanguage());
		resourceBundle = ResourceBundle.getBundle(
				"mapeditor.messages.MessagesBundle", currentLocale);
	}

	public String getString(String string) {
		String msg = string;

		try {
			msg = resourceBundle.getString(string);
		} catch (MissingResourceException e) {

		}
		return msg;
	}

}
