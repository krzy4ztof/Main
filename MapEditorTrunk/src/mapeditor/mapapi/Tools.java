package mapeditor.mapapi;

import java.awt.Image;

import javax.swing.ImageIcon;

import mapeditor.main.ApplicationManager;
import mapeditor.mainwindow.MainWindow;
import mapeditor.themesapi.MapObject;

public class Tools {

	private ToolsEnum activeTool;

	private MapObject blankMapObject;

	public enum ToolsEnum {
		ERASER, BRUSH, BUCKET, PICKER, SELECTION
	}

	public Tools() {
		blankMapObject = new MapObject("");

		String imgLocation = ApplicationManager.THEMES_PATH
				+ MainWindow.ICON_NULL;

		Image image = new ImageIcon(imgLocation).getImage().getScaledInstance(
				40, 40, Image.SCALE_DEFAULT);

		blankMapObject.setImageIcon(new ImageIcon(image));
	}

	public void setActiveTool(ToolsEnum toolsEnum) {
		activeTool = toolsEnum;
	}

	public ToolsEnum getActiveTool() {
		return activeTool;
	}

	public MapObject getBlankMapObject() {
		return blankMapObject;
	}
}
