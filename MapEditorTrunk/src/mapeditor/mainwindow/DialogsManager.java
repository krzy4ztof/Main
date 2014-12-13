package mapeditor.mainwindow;

import java.io.File;

import javax.swing.JFileChooser;
import javax.swing.JOptionPane;

import mapeditor.config.Config;
import mapeditor.dialogs.MapAttributesPanel;
import mapeditor.mapapi.MapApi;
import mapeditor.messages.MapMessages;
import mapeditor.saveload.MapLoader;
import mapeditor.saveload.MapSaver;
import mapeditor.themesapi.MapThemesList;
import otherprods.ExampleFileFilter;

public class DialogsManager {

	MapPanel mapPanel;
	MapApi mapApi;
	MapMessages messages;
	MapThemesList mapThemesList;
	Config config;

	DialogsManager(MapPanel mapPanel, MapApi mapApi, MapMessages messages,
			MapThemesList mapThemesList, Config config) {
		this.mapPanel = mapPanel;
		this.mapApi = mapApi;
		this.messages = messages;
		this.mapThemesList = mapThemesList;
		this.config = config;
	}

	/**
	 * Creates new map. Saves current and clears it.
	 */
	void newMapAction() {
		int res = JOptionPane.showConfirmDialog(mapPanel.getTopLevelAncestor(),
				messages.getMsgSaveChanges(), null, JOptionPane.YES_NO_OPTION);
		if (res == JOptionPane.YES_OPTION) {
			this.saveMapApi();
		}
		MapAttributesPanel MRP = new MapAttributesPanel(config, messages,
				mapPanel.getTopLevelAncestor());

		MRP.activate(mapApi.getMapAttributes());

		if (!MRP.isCanceled()) {
			int row = MRP.getSelectedMapAttributes().getRows();
			int col = MRP.getSelectedMapAttributes().getColumns();

			mapApi.resetMap(row, col);
		}

	}

	/**
	 * Loads new map from file.
	 */
	void loadMapAction() {
		int res = JOptionPane.showConfirmDialog(mapPanel.getTopLevelAncestor(),
				messages.getMsgSaveChanges());

		if (res == JOptionPane.YES_OPTION) {
			saveMapApi();
			loadMapApi();
		} else if (res == JOptionPane.NO_OPTION) {
			loadMapApi();
		}
	}

	/**
	 * Saves map to file.
	 */
	void saveMapAction() {
		saveMapApi();
	}

	/**
	 * Resizes map without removing current MapObjects
	 * 
	 * @throws CloneNotSupportedException
	 */
	void attributesMapAction() {
		/* otwiera okno ustawien wymiarow nowej mapy */
		// MapAttributesPanel mapAttributesPanel = new
		// MapAttributesPanel(config,
		// messages, mapPanel.getTopParent());

		MapAttributesPanel mapAttributesPanel = new MapAttributesPanel(config,
				messages, mapPanel.getTopLevelAncestor());

		mapAttributesPanel.activate(mapApi.getMapAttributes());

		if (!mapAttributesPanel.isCanceled()) {
			int row = mapAttributesPanel.getSelectedMapAttributes().getRows();
			int col = mapAttributesPanel.getSelectedMapAttributes()
					.getColumns();

			mapApi.changeSize(row, col);
		}
	}

	private void saveMapApi() {
		/* zapisuje mape */
		JFileChooser FC = new JFileChooser();
		FC.setCurrentDirectory(new File("." + File.separator + "Maps"));

		ExampleFileFilter rfilter = new ExampleFileFilter("xml", "XML Files");

		FC.setFileFilter(rfilter);
		FC.setSelectedFile(mapApi.getFile());

		int res = FC.showSaveDialog(mapPanel.getTopLevelAncestor());
		if (res == JFileChooser.APPROVE_OPTION) {
			File rFile = FC.getSelectedFile();
			MapSaver p_MapSaver = new MapSaver(messages, mapThemesList);
			MapApi p_MapApi = mapApi;

			try {
				p_MapSaver.SaveMapToFile(p_MapApi, rFile);
			} catch (Exception e) {

				String msg = messages.getMsgSavingFailed() + " "
						+ e.getMessage();
				JOptionPane.showMessageDialog(FC, msg);
			}
		}
	}

	/**
	 * Loads new map
	 */
	private void loadMapApi() {
		JFileChooser FC = new JFileChooser();
		FC.setCurrentDirectory(new File("." + File.separator + "Maps"));

		ExampleFileFilter rfilter = new ExampleFileFilter("xml", "XML Files");

		FC.setFileFilter(rfilter);
		FC.setSelectedFile(mapApi.getFile());

		int res = FC.showOpenDialog(mapPanel.getTopLevelAncestor());
		if (res == JFileChooser.APPROVE_OPTION) {
			File rFile = FC.getSelectedFile();
			MapLoader p_MapLoader = new MapLoader();

			try {
				mapApi = p_MapLoader.loadMapFromFile(rFile, mapThemesList);
				mapPanel.setMapApi(mapApi);
				mapPanel.repaint();
				// gs.getJFrame().repaint();
			} catch (Exception e) {

				String msg = messages.getMsgLoadingFailed() + e.getMessage();
				JOptionPane.showMessageDialog(FC, msg);

			}
		}
	}

	/**
	 * Quits application
	 */
	void closeApplicationAction() {
		int res = JOptionPane.showConfirmDialog(mapPanel.getTopLevelAncestor(),
				messages.getMsgSaveChanges());
		if (res == JOptionPane.YES_OPTION) {
			saveMapApi();
		}
		System.exit(0);
	}

}
