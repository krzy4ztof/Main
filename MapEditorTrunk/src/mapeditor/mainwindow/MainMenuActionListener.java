package mapeditor.mainwindow;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class MainMenuActionListener implements ActionListener {

	private MapPanel mapPanel;
	private DialogsManager dialogsManager;
	private ThemesTabbedPane themesPane;

	MainMenuActionListener(DialogsManager dialogsManager, MapPanel mapPanel,
			ThemesTabbedPane themesPane) {
		this.mapPanel = mapPanel;
		this.dialogsManager = dialogsManager;
		this.themesPane = themesPane;
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		/*
		 * prowadzi nasluch 1. przyciskow przesuwajacych mape 2. ??? menu plik
		 * (otwieranie/zamykanie nowych map - moze przeniesc to do
		 * graphics_systemu, otwieranie okien dialogowych do wyboru pliku
		 */

		String str = e.getActionCommand();
		System.out.println("MapPanel: " + e.getActionCommand());
		if (str.equals(MainWindow.ACTION_ZOOM_IN)) {
			mapPanel.zoomMapIn();
		} else if (str.equals(MainWindow.ACTION_ZOOM_OUT)) {
			mapPanel.zoomMapOut();
		} else if (str.equals(MainWindow.ACTION_ZOOM_DEFAULT)) {
			mapPanel.setDefaultMapZoom();
		} else if (str.equals(MainWindow.ACTION_CENTER_MAP)) {
			mapPanel.centerMap();
		} else if (str.equals(MainWindow.ACTION_NEW)) {
			dialogsManager.newMapAction();
		} else if (str.equals(MainWindow.ACTION_OPEN)) {
			dialogsManager.loadMapAction();
		} else if (str.equals(MainWindow.ACTION_CLOSE)) {
			dialogsManager.closeApplicationAction();
		} else if (str.equals(MainWindow.ACTION_SAVE)) {
			dialogsManager.saveMapAction();
		} else if (str.equals(MainWindow.ACTION_MAP_ATTRIBUTES_PANEL)) {
			dialogsManager.attributesMapAction();
		} else if (str.equals(MainWindow.ACTION_REFRESH)) {
			themesPane.getActiveThemePanel().refresh();
		}

		// mapPanel.getPanel().repaint();
		mapPanel.refresh();

		// return focus to top frame. Focus allows GraphicsSystemKeyListener to
		// handle key events.
		mapPanel.getPanel().getTopLevelAncestor().requestFocus();
	}
}
