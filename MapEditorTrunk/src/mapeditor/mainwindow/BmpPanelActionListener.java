package mapeditor.mainwindow;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class BmpPanelActionListener implements ActionListener {

	private BmpPanel bmpPanel;

	BmpPanelActionListener(BmpPanel bmpPanel) {
		this.bmpPanel = bmpPanel;
	}

	@Override
	public void actionPerformed(ActionEvent event) {
		/**
		 * prowadzi nasluch menu sluzacego do wyboru grupy tematycznej. Powoduje
		 * wyswietlenie ikon nalezacych do wybranego Tematu. Prowadzi tez
		 * nasluch dwoch przyciskow przesuwajacych liste dostepnych ikon.
		 */

		String command = event.getActionCommand();
		if (command.startsWith(GraphicsSystem.ACTION_THEMES_SELECTION)) {
			int length = GraphicsSystem.ACTION_THEMES_SELECTION.length();
			String name = command.substring(length);
			bmpPanel.changeCurrentTheme(name);
		} else if (command.equals(BmpPanel.ACTION_SCROLL_UP)) {
			// nasluch przyciskow przesuwajacych liste ikon
			bmpPanel.moveIconsUp();
		} else if (command.equals(BmpPanel.ACTION_SCROLL_DOWN)) {
			bmpPanel.moveIconsDown();
		} else if (command.startsWith(BmpPanel.ACTION_ICON_BUTTON)) {
			// nasluch przyciskow ustawiajacych ikone jako "pedzel"
			bmpPanel.changeSelectedIconButton(command);
		}

		// return focus to top frame. Focus allows GraphicsSystemKeyListener to
		// handle key events.
		bmpPanel.getTopLevelAncestor().requestFocus();
	}
}
