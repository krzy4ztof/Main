package mapeditor.mainwindow;

import java.awt.Image;

import javax.swing.ImageIcon;
import javax.swing.JButton;

import mapeditor.themesapi.MapObject;

public class BmpPanelIconButton {

	private int number;
	private JButton button;
	private MapObject mapObject;

	BmpPanelIconButton(int number, BmpPanelActionListener bmpListener) {

		this.number = number;
		String actionName = createActionName(number);
		button = new JButton();
		button.addActionListener(bmpListener);
		button.setActionCommand(actionName);
	}

	public JButton getButton() {
		return button;
	}

	private String createActionName(int number) {
		String name = "";
		if (number < 10) {
			name = "0" + number;
		} else if (number < 100) {
			name = "" + number;
		}
		return BmpPanel.ACTION_ICON_BUTTON + name;
	}

	public String getName() {
		return button.getActionCommand();
	}

	public int getNumber() {
		return number;
	}

	public MapObject getMapObject() {
		return mapObject;
	}

	public void setMapObject(MapObject mapObject) {
		this.mapObject = mapObject;
		ImageIcon img = mapObject.getImageIcon();

		img = new ImageIcon(img.getImage().getScaledInstance(40, 40,
				Image.SCALE_DEFAULT));

		button.setIcon(img);
	}
}
