package mapeditor.themesapi;

import java.awt.Image;

import javax.swing.ImageIcon;

import mapeditor.main.ApplicationManager;
import mapeditor.mainwindow.MainWindow;

public class MapObjectFactory {

	public static final int DEFAULT_SEGMENT_WIDTH = 40;
	public static final int DEFAULT_SEGMENT_HEIGHT = 40;

	private MapObject blankMapObject;

	public MapObjectFactory() {
		blankMapObject = new MapObject("");

		String imgLocation = ApplicationManager.THEMES_PATH
				+ MainWindow.ICON_NULL;

		Image image = new ImageIcon(imgLocation).getImage().getScaledInstance(
				MapObjectFactory.DEFAULT_SEGMENT_WIDTH,
				MapObjectFactory.DEFAULT_SEGMENT_HEIGHT, Image.SCALE_DEFAULT);

		blankMapObject.setImageIcon(new ImageIcon(image));
	}

	public MapObject getBlankMapObject() {
		return blankMapObject;
	}
}
