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
	public static String ATTR_LAYOUT = "mapattributes.layout";
	public static String ATTR_DEFAULT_SIZE = "mapattributes.defaultsize";
	public static String ATTR_PREVIOUS_SIZE = "mapattributes.previoussize";
	public static String ATTR_OK = "mapattributes.ok";
	public static String ATTR_CANCEL = "mapattributes.cancel";

	public static String LAY_HEX = "maplayout.hex";
	public static String LAY_SQR = "maplayout.sqr";

	ResourceBundle resourceBundle;

	public MapMessages(Config config) {
		Locale currentLocale;
		currentLocale = new Locale(config.getLanguage());
		resourceBundle = ResourceBundle.getBundle(
				"mapeditor.messages.MessagesBundle", currentLocale);
	}

	private String getString(String string) {
		String msg = string;

		try {
			msg = resourceBundle.getString(string);
		} catch (MissingResourceException e) {

		}
		return msg;
	}

	public String getMenuFile() {
		return getString(MENU_FILE);
	}

	public String getMenuNew() {
		return getString(MENU_NEW);
	}

	public String getMenuOpen() {
		return getString(MENU_OPEN);
	}

	public String getMenuClose() {
		return getString(MENU_CLOSE);
	}

	public String getMenuSave() {
		return getString(MENU_SAVE);
	}

	public String getMenuEdit() {
		return getString(MENU_EDIT);
	}

	public String getMenuAttributes() {
		return getString(MENU_ATTRIBUTES);
	}

	public String getMenuRefresh() {
		return getString(MENU_REFRESH);
	}

	public String getMenuNavigation() {
		return getString(MENU_NAVIGATION);
	}

	public String getMenuZoomIn() {
		return getString(MENU_ZOOM_IN);
	}

	public String getMenuZoomOut() {
		return getString(MENU_ZOOM_OUT);
	}

	public String getMenuDefaultZoom() {
		return getString(MENU_DEFAULT_ZOOM);
	}

	public String getMenuCenterMap() {
		return getString(MENU_CENTER_MAP);
	}

	public String getMenuObjects() {
		return getString(MENU_OBJECTS);
	}

	public String getThemeName(String name) {
		return getString(THEMENAME + name);
	}

	public String getMsgSavingFailed() {
		return getString(MSG_SAVING_FAILED);
	}

	public String getMsgSaveChanges() {
		return getString(MSG_SAVE_CHANGES);
	}

	public String getMsgLoadingFailed() {
		return getString(MSG_LOADING_FAILED);
	}

	public String getMapName() {
		return getString(MAPSAVER_MAP_NAME);
	}

	public String getAttrTitle() {
		return getString(ATTR_TITLE);
	}

	public String getAttrRowNumber() {
		return getString(ATTR_ROW_NUMBER);
	}

	public String getAttrColNumber() {
		return getString(ATTR_COL_NUMBER);
	}

	public String getAttrLayout() {
		return getString(ATTR_LAYOUT);
	}

	public String getAttrDefaultSize() {
		return getString(ATTR_DEFAULT_SIZE);
	}

	public String getAttrPreviousSize() {
		return getString(ATTR_PREVIOUS_SIZE);
	}

	public String getOk() {
		return getString(ATTR_OK);
	}

	public String getCancel() {
		return getString(ATTR_CANCEL);
	}

	public String getLayoutHex() {
		return getString(LAY_HEX);
	}

	public String getLayoutSqr() {
		return getString(LAY_SQR);
	}

}
