package mapeditor.mainwindow;

import java.io.File;
import java.util.logging.Level;
import java.util.logging.Logger;

import javax.swing.JFileChooser;
import javax.swing.JOptionPane;
import javax.xml.XMLConstants;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;
import javax.xml.transform.Source;
import javax.xml.transform.stream.StreamSource;
import javax.xml.validation.Schema;
import javax.xml.validation.SchemaFactory;
import javax.xml.validation.Validator;

import mapeditor.config.Config;
import mapeditor.dialogs.MapAttributesPanel;
import mapeditor.logger.MapLogger;
import mapeditor.main.ApplicationManager;
import mapeditor.mainwindow.layers.LayersControlPane;
import mapeditor.mainwindow.map.MapPane;
import mapeditor.mapapi.MapApi;
import mapeditor.mapapi.MapAttributes;
import mapeditor.messages.MapMessages;
import mapeditor.saveload.MapLoaderSAXHandler;
import mapeditor.saveload.MapSaver;
import mapeditor.themesapi.MapObjectFactory;
import mapeditor.themesapi.ThemesManager;

import org.xml.sax.SAXException;

import otherprods.ExampleFileFilter;

public class DialogsManager {

	private static final Logger logger = Logger.getLogger(DialogsManager.class
			.getName());

	private MapPane mapPanel;
	private MapApi mapApi;
	private MapMessages messages;
	private ThemesManager mapThemesList;
	private Config config;
	private MapObjectFactory mapObjectFactory;
	private LayersControlPane layersPane;

	DialogsManager(MapPane mapPanel, MapApi mapApi, MapMessages messages,
			ThemesManager mapThemesList, Config config,
			MapObjectFactory mapObjectFactory, LayersControlPane layersPane) {
		this.mapPanel = mapPanel;
		this.mapApi = mapApi;
		this.messages = messages;
		this.mapThemesList = mapThemesList;
		this.config = config;
		this.mapObjectFactory = mapObjectFactory;
		this.layersPane = layersPane;
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

			layersPane.update(mapApi);

		}
	}

	private void saveMapApi() {
		JFileChooser fileChooser = new JFileChooser();
		fileChooser
				.setCurrentDirectory(new File("." + File.separator + "Maps"));

		ExampleFileFilter filter = new ExampleFileFilter("xml", "XML Files");

		fileChooser.setFileFilter(filter);
		fileChooser.setSelectedFile(mapApi.getFile());

		int res = fileChooser.showSaveDialog(mapPanel.getPanel()
				.getTopLevelAncestor());
		if (res == JFileChooser.APPROVE_OPTION) {
			File rFile = fileChooser.getSelectedFile();
			MapSaver mapSaver = new MapSaver(messages, mapThemesList);
			MapApi mapApi = this.mapApi;

			try {
				mapSaver.saveMapToFile(mapApi, rFile);
			} catch (Exception e) {
				String msg = messages.getString(MapMessages.MSG_SAVING_FAILED)
						+ " " + e.getMessage();
				JOptionPane.showMessageDialog(fileChooser, msg);
				logger.log(Level.SEVERE, MapLogger.ERROR, e);
			}
		}
	}

	/**
	 * Loads new map
	 */
	private void loadMapApi() {
		JFileChooser fileChooser = new JFileChooser();
		fileChooser
				.setCurrentDirectory(new File("." + File.separator + "Maps"));

		ExampleFileFilter filter = new ExampleFileFilter("xml", "XML Files");

		fileChooser.setFileFilter(filter);
		fileChooser.setSelectedFile(mapApi.getFile());

		int res = fileChooser.showOpenDialog(mapPanel.getPanel()
				.getTopLevelAncestor());
		if (res == JFileChooser.APPROVE_OPTION) {
			File file = fileChooser.getSelectedFile();

			SAXParserFactory factory = SAXParserFactory.newInstance();

			try {
				SAXParser saxParser = factory.newSAXParser();

				Source schemaFile = new StreamSource(new File(
						ApplicationManager.XSD_FOLDER, "map.xsd"));
				SchemaFactory schemaFactory = SchemaFactory
						.newInstance(XMLConstants.W3C_XML_SCHEMA_NS_URI);
				Schema schema = schemaFactory.newSchema(schemaFile);

				Source xmlFile = new StreamSource(file);
				Validator validator = schema.newValidator();
				try {
					validator.validate(xmlFile);
					logger.log(Level.INFO, MapLogger.FILE_VALID,
							xmlFile.getSystemId());

					MapLoaderSAXHandler handler = new MapLoaderSAXHandler(
							mapApi, mapThemesList, mapObjectFactory);
					saxParser.parse(file, handler);

					mapPanel.setMapApi(mapApi);
					mapPanel.getPanel().repaint();
				} catch (SAXException e) {
					logger.log(Level.SEVERE, MapLogger.FILE_NOT_VALID,
							xmlFile.getSystemId());
					logger.log(Level.SEVERE, MapLogger.REASON, e);
				}
			} catch (Exception e) {
				String msg = messages.getString(MapMessages.MSG_LOADING_FAILED)
						+ e.getMessage();
				JOptionPane.showMessageDialog(fileChooser, msg);
				logger.log(Level.SEVERE, MapLogger.ERROR, e);
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
