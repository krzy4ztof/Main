package mapeditor.mainwindow;

import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import mapeditor.themesapi.MapThemesList;

public class BmpPanelActionListener implements ActionListener {

	private BmpPanel bmpPanel;
	private GraphicsSystem graphicsSystem = null;
	private MapThemesList mapThemesList = null;

	BmpPanelActionListener(BmpPanel bmpPanel, MapThemesList mapThemesList,
			GraphicsSystem graphicsSystem) {
		this.bmpPanel = bmpPanel;
		this.mapThemesList = mapThemesList;
		this.graphicsSystem = graphicsSystem;
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		/**
		 * prowadzi nas�uch menu s�u��cego do wyboru grupy tematycznej.
		 * Powoduje wy�wietlenie ikon nale��cych do wybranego Tematu.
		 * Prowadzi te� nas�uch dw�ch przycisk�w przesuwaj�cych
		 * list� dost�pnych ikon.
		 */

		String Command = e.getActionCommand();
		if (Command.startsWith("MNU_")) {

			bmpPanel.curMapObjectsTheme = mapThemesList.getThemeByName(Command
					.substring(4));
			bmpPanel.curMapObjectsTheme.describeYourself();

			bmpPanel.SetAvailableIcons();
		} else if (Command.startsWith("SCR_")) {
			// nas�uch przycisk�w przesuwaj�cych list� ikon
			if (Command.substring(4).equals("up")) {
				bmpPanel.ChangeActualButton(Color.LIGHT_GRAY);
				bmpPanel.ImageNumber--;
				if (bmpPanel.ImageNumber < 0) {
					bmpPanel.ImageNumber = 0;
				}
				bmpPanel.ChangeActualButton(Color.RED);
			} else if (Command.substring(4).equals("down")) {
				bmpPanel.ChangeActualButton(Color.LIGHT_GRAY);
				bmpPanel.ImageNumber++;
				int maxNumber = bmpPanel.curMapObjectsTheme.getThemeSize();

				if (bmpPanel.ImageNumber > maxNumber - 1) {
					bmpPanel.ImageNumber = maxNumber - 1;
				}
				if (bmpPanel.ImageNumber < 0) {
					bmpPanel.ImageNumber = 0;
				}
				bmpPanel.ChangeActualButton(Color.RED);
			}
			bmpPanel.SetAvailableIcons();

		} else if (Command.startsWith("BMP_")) {
			// nas�uch przycisk�w ustawiaj�cych ikon� jako "p�dzel"
			int btn_number = Integer.parseInt(Command.substring(4));
			int maxNumber = bmpPanel.curMapObjectsTheme.getThemeSize();

			int sel = btn_number + bmpPanel.ImageNumber;
			if (sel < maxNumber) {
				for (int i = 0; i < 8; i++) {
					bmpPanel.Items.get("BMP_" + Integer.toString(i))
							.setBackground(Color.LIGHT_GRAY);
				}
				bmpPanel.Items.get(Command).setBackground(Color.RED);
				bmpPanel.SelectedImage = sel;
			}
		}
		graphicsSystem.getJFrame().requestFocus();
	}

}
