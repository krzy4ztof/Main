package mapeditor.mainwindow;

import java.util.HashSet;
import java.util.Set;

public class BmpPanelIconButtonsManager {
	/**
	 * iconButtons - wskazniki do przyciskow z ikonami, symobole haszujace
	 * BmpPanel.ACTION_ICON_BUTTON+numer(1-8)
	 */
	// private Hashtable<String, JButton> iconButtons = new Hashtable<String,
	// JButton>();
	private Set<BmpPanelIconButton> iconButtons = new HashSet<BmpPanelIconButton>();

	public void addButton(BmpPanelIconButton button) {
		iconButtons.add(button);
	}

	public BmpPanelIconButton getIconButton(int number) {
		for (BmpPanelIconButton button : iconButtons) {
			if (button.getNumber() == number) {
				return button;
			}
		}
		return null;
	}

	public BmpPanelIconButton getIconButton(String name) {
		for (BmpPanelIconButton button : iconButtons) {
			if (button.getName() == name) {
				return button;
			}
		}
		return null;
	}
}
