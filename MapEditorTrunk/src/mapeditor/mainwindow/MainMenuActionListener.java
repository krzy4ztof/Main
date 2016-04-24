package mapeditor.mainwindow;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.logging.Level;
import java.util.logging.Logger;

import mapeditor.logger.MapLogger;
import mapeditor.mainwindow.map.MapPane;
import mapeditor.mainwindow.themes.ThemesPane;

public class MainMenuActionListener implements ActionListener {

	private static final Logger logger = Logger
			.getLogger(MainMenuActionListener.class.getName());

	private MapPane mapPanel;
	private DialogsManager dialogsManager;
	private ThemesPane themesPane;

	MainMenuActionListener(DialogsManager dialogsManager, MapPane mapPanel,
			ThemesPane themesPane) {
		this.mapPanel = mapPanel;
		this.dialogsManager = dialogsManager;
		this.themesPane = themesPane;
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		/*
		 * Listens to buttons that move, zoom in/out map
		 */

		String str = e.getActionCommand();
		logger.log(Level.INFO, MapLogger.ACTION_COMMAND, str);

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

		mapPanel.refresh();

		mapPanel.getPanel().getTopLevelAncestor().requestFocus();
	}
}
