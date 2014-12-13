package mapeditor.mainwindow;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class GraphicsSystemActionListener implements ActionListener {

	MapPanel mapPanel;
	DialogsManager dialogsManager;
	GraphicsSystem graphicsSystem;

	GraphicsSystemActionListener(DialogsManager dialogsManager,
			MapPanel mapPanel, GraphicsSystem graphicsSystem) {
		this.mapPanel = mapPanel;
		this.dialogsManager = dialogsManager;
		this.graphicsSystem = graphicsSystem;
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
		if (str.equals(GraphicsSystem.ACTION_ROLL_RIGHT)) {
			mapPanel.MoveMap(1, 0);
		} else if (str.equals(GraphicsSystem.ACTION_ROLL_LEFT)) {
			mapPanel.MoveMap(-1, 0);
		} else if (str.equals(GraphicsSystem.ACTION_ROLL_UP)) {
			mapPanel.MoveMap(0, -1);
		} else if (str.equals(GraphicsSystem.ACTION_ROLL_DOWN)) {
			mapPanel.MoveMap(0, 1);
		} else if (str.equals(GraphicsSystem.ACTION_ZOOM_IN)) {
			mapPanel.ZoomMapIn();
		} else if (str.equals(GraphicsSystem.ACTION_ZOOM_OUT)) {
			mapPanel.ZoomMapOut();
		} else if (str.equals(GraphicsSystem.ACTION_ZOOM_DEFAULT)) {
			mapPanel.SetDefaultMapZoom();
		} else if (str.equals(GraphicsSystem.ACTION_NEW)) {
			dialogsManager.newMapAction();
		} else if (str.equals(GraphicsSystem.ACTION_OPEN)) {
			dialogsManager.loadMapAction();
		} else if (str.equals(GraphicsSystem.ACTION_CLOSE)) {
			dialogsManager.closeApplicationAction();
		} else if (str.equals(GraphicsSystem.ACTION_SAVE)) {
			dialogsManager.saveMapAction();
		} else if (str.equals(GraphicsSystem.ACTION_MAP_ATTRIBUTES_PANEL)) {
			dialogsManager.attributesMapAction();
		}
		mapPanel.repaint();
		graphicsSystem.getFrame().requestFocus();
	}

}
