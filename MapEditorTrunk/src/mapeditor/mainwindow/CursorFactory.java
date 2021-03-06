package mapeditor.mainwindow;

import java.awt.Cursor;
import java.awt.Image;
import java.awt.Point;
import java.awt.Toolkit;
import java.net.URL;
import java.util.HashMap;

import mapeditor.mapapi.Tools.ToolsEnum;

public class CursorFactory {
	private final static String CURSOR_ICONS_FOLDER_URL = "resources/cursors/";

	public static final String CURSOR_BUCKET = "paint_bucket_32.png";
	public static final String CURSOR_BRUSH = "brush_32.png";
	public static final String CURSOR_PICKER = "colour_picker_48.png";
	public static final String CURSOR_ERASER = "package_purge_32.png";
	public static final String CURSOR_HAMMER = "technical_hammer_40.png";
	public static final String CURSOR_POINT_PROPERTY = "down_left_32.png";

	private HashMap<String, Cursor> cursors = null;

	private Toolkit toolkit;

	public CursorFactory() {
		cursors = new HashMap<String, Cursor>();
		toolkit = Toolkit.getDefaultToolkit();

		createCursor(CURSOR_BRUSH, new Point(0, 31));
		createCursor(CURSOR_BUCKET, new Point(0, 31));
		createCursor(CURSOR_PICKER, new Point(0, 31));
		createCursor(CURSOR_ERASER, new Point(0, 31));
		createCursor(CURSOR_HAMMER, new Point(0, 31));
		createCursor(CURSOR_POINT_PROPERTY, new Point(0, 31));
	}

	private URL getURL(String iconPath) {
		// Works for iconPath = "resources/cursors/brush_32.png"
		URL url = ClassLoader.getSystemResource(iconPath);
		if (url != null) {
			return url;
		}

		// Works for iconPath = "/resources/cursors/brush_32.png"
		url = getClass().getResource(iconPath);
		if (url != null) {
			return url;
		}

		return url;
	}

	private void createCursor(String iconName, Point point) {
		String iconPath = CURSOR_ICONS_FOLDER_URL + iconName;

		URL url = getURL(iconPath);
		Image image = toolkit.getImage(url);

		image = image.getScaledInstance(32, 32, Image.SCALE_DEFAULT);
		Cursor cursor = toolkit.createCustomCursor(image, point, iconName);
		cursors.put(iconName, cursor);
	}

	public Cursor getCursor(ToolsEnum toolsEnum) {
		switch (toolsEnum) {
		case ERASER:
			return cursors.get(CursorFactory.CURSOR_ERASER);
		case BRUSH:
			return cursors.get(CursorFactory.CURSOR_BRUSH);
		case BUCKET:
			return cursors.get(CursorFactory.CURSOR_BUCKET);
		case PICKER:
			return cursors.get(CursorFactory.CURSOR_PICKER);
		case SELECTION:
			return Cursor.getPredefinedCursor(Cursor.CROSSHAIR_CURSOR);
		case HAMMER:
			return cursors.get(CursorFactory.CURSOR_HAMMER);
		case POINT_PROPERTY:
			return cursors.get(CursorFactory.CURSOR_POINT_PROPERTY);
		default:
			return null;
		}
	}

}
