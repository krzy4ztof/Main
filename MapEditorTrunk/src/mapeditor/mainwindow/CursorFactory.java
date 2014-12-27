package mapeditor.mainwindow;

import java.awt.Cursor;
import java.awt.Image;
import java.awt.Point;
import java.awt.Toolkit;
import java.io.File;
import java.util.HashMap;

import javax.swing.ImageIcon;

public class CursorFactory {

	private final static String CURSOR_ICONS_FOLDER = "resources"
			+ File.separator + "cursors" + File.separator;

	// public static final String CURSOR_BUCKET = "paintcan.png";

	// public static final String CURSOR_BUCKET = "bucket.ico";
	// public static final String CURSOR_BUCKET = "bucket.gif";
	// public static final String CURSOR_BUCKET = "dukeWaveRed.gif";

	// public static final String CURSOR_BUCKET = "construction_bucket_16.png";
	// public static final String CURSOR_BUCKET = "construction_bucket_32.png";
	// public static final String CURSOR_BUCKET = "construction_bucket_256.png";

	public static final String CURSOR_BUCKET = "paint_bucket_32.png";
	public static final String CURSOR_BRUSH = "brush_32.png";
	// public static final String CURSOR_PICKER = "color_picker_32.png";
	// public static final String CURSOR_PICKER = "gtk_color_picker_24.png";
	public static final String CURSOR_PICKER = "colour_picker_48.png";

	public static final String CURSOR_ERASER = "package_purge_32.png";

	private HashMap<String, Cursor> cursors = null;

	private Toolkit toolkit;

	public CursorFactory() {
		cursors = new HashMap<String, Cursor>();
		toolkit = Toolkit.getDefaultToolkit();

		createCursor(CURSOR_BRUSH, new Point(0, 31));
		createCursor(CURSOR_BUCKET, new Point(0, 31));
		createCursor(CURSOR_PICKER, new Point(0, 31));
		createCursor(CURSOR_ERASER, new Point(0, 31));

	}

	private void createCursor(String iconName, Point point) {
		String iconPath = CURSOR_ICONS_FOLDER + iconName;
		Image image = new ImageIcon(iconPath).getImage();
		// Image image = toolkit.getImage(iconPath);

		image = image.getScaledInstance(32, 32, Image.SCALE_DEFAULT);
		Cursor cursor = toolkit.createCustomCursor(image, point, iconName);
		cursors.put(iconName, cursor);
	}

	public Cursor getCursor(String name) {
		return cursors.get(name);
	}
}
