package mapeditor.mainwindow;

import java.io.File;

import javax.swing.JFileChooser;
import javax.swing.JOptionPane;

import mapeditor.config.Config;
import mapeditor.dialogs.MapAttributesPanel;
import mapeditor.mapapi.MapApi;
import mapeditor.mapapi.MapAttributes;
import mapeditor.mapapi.Tools;
import mapeditor.messages.MapMessages;
import mapeditor.saveload.MapLoader;
import mapeditor.saveload.MapSaver;
import mapeditor.themesapi.MapObjectFactory;
import mapeditor.themesapi.ThemesManager;
import otherprods.ExampleFileFilter;

public class DialogsManager {

	private MapPane mapPanel;
	private MapApi mapApi;
	private MapMessages messages;
	private ThemesManager mapThemesList;
	private Config config;
	private Tools tools;
	private MapObjectFactory mapObjectFactory;

	DialogsManager(MapPane mapPanel, MapApi mapApi, MapMessages messages,
			ThemesManager mapThemesList, Config config, Tools tools,
			MapObjectFactory mapObjectFactory) {
		this.mapPanel = mapPanel;
		this.mapApi = mapApi;
		this.messages = messages;
		this.mapThemesList = mapThemesList;
		this.config = config;
		this.tools = tools;
		this.mapObjectFactory = mapObjectFactory;
	}

	/**
	 * Creates new map. Saves current and clears it.
	 */
	void newMapAction() {
		int res = JOptionPane.showConfirmDialog(mapPanel.getPanel()
				.getTopLevelAncestor(), messages
				.getString(MapMessages.MSG_SAVE_CHANGES), null,
				JOptionPane.YES_NO_OPTION);
		if (res == JOptionPane.YES_OPTION) {
			this.saveMapApi();
		}
		MapAttributesPanel mapAttributesPanel = new MapAttributesPanel(config,
				messages, mapPanel.getPanel().getTopLevelAncestor());

		mapAttributesPanel.activate(mapApi.getMapAttributes());

		if (!mapAttributesPanel.isCanceled()) {
			MapAttributes mapAttributes = mapAttributesPanel
					.getSelectedMapAttributes();

			mapApi.resetMap(mapAttributes, mapObjectFactory.getBlankMapObject());
		}

	}

	/**
	 * Loads new map from file.
	 */
	void loadMapAction() {
		int res = JOptionPane.showConfirmDialog(mapPanel.getPanel()
				.getTopLevelAncestor(), messages
				.getString(MapMessages.MSG_SAVE_CHANGES));

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
				messages, mapPanel.getPanel().getTopLevelAncestor());

		mapAttributesPanel.activate(mapApi.getMapAttributes());

		if (!mapAttributesPanel.isCanceled()) {
			MapAttributes mapAttributes = mapAttributesPanel
					.getSelectedMapAttributes();

			mapApi.changeAttributes(mapAttributes,
					mapObjectFactory.getBlankMapObject());
		}
	}

	private void saveMapApi() {
		/* zapisuje mape */
		JFileChooser FC = new JFileChooser();
		FC.setCurrentDirectory(new File("." + File.separator + "Maps"));

		ExampleFileFilter rfilter = new ExampleFileFilter("xml", "XML Files");

		FC.setFileFilter(rfilter);
		FC.setSelectedFile(mapApi.getFile());

		int res = FC.showSaveDialog(mapPanel.getPanel().getTopLevelAncestor());
		if (res == JFileChooser.APPROVE_OPTION) {
			File rFile = FC.getSelectedFile();
			MapSaver p_MapSaver = new MapSaver(messages, mapThemesList);
			MapApi p_MapApi = mapApi;

			try {
				p_MapSaver.SaveMapToFile(p_MapApi, rFile);
			} catch (Exception e) {

				String msg = messages.getString(MapMessages.MSG_SAVING_FAILED)
						+ " " + e.getMessage();
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

		int res = FC.showOpenDialog(mapPanel.getPanel().getTopLevelAncestor());
		if (res == JFileChooser.APPROVE_OPTION) {
			File rFile = FC.getSelectedFile();
			MapLoader p_MapLoader = new MapLoader();

			try {
				mapApi = p_MapLoader.loadMapFromFile(rFile, mapThemesList,
						mapObjectFactory);
				mapPanel.setMapApi(mapApi);
				mapPanel.getPanel().repaint();
				// gs.getJFrame().repaint();
			} catch (Exception e) {

				String msg = messages.getString(MapMessages.MSG_LOADING_FAILED)
						+ e.getMessage();
				JOptionPane.showMessageDialog(FC, msg);

			}
		}
	}

	/**
	 * Quits application
	 */
	void closeApplicationAction() {
		int res = JOptionPane.showConfirmDialog(mapPanel.getPanel()
				.getTopLevelAncestor(), messages
				.getString(MapMessages.MSG_SAVE_CHANGES));
		if (res == JOptionPane.YES_OPTION) {
			saveMapApi();
		}
		System.exit(0);
	}

}
