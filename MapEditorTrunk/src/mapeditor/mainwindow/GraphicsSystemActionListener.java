package mapeditor.mainwindow;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class GraphicsSystemActionListener implements ActionListener {

	MapPanel mapPanel;
	DialogsManager dialogsManager;

	GraphicsSystemActionListener(DialogsManager dialogsManager,
			MapPanel mapPanel) {
		this.mapPanel = mapPanel;
		this.dialogsManager = dialogsManager;
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
		}
		mapPanel.repaint();

		// return focus to top frame. Focus allows GraphicsSystemKeyListener to
		// handle key events.
		mapPanel.getTopLevelAncestor().requestFocus();
	}
}
