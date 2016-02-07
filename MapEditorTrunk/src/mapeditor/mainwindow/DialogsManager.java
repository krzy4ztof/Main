package mapeditor.mainwindow;

import java.io.File;

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
import mapeditor.main.ApplicationManager;
import mapeditor.mainwindow.layers.LayersControlPane;
import mapeditor.mainwindow.map.MapPane;
import mapeditor.mapapi.MapApi;
import mapeditor.mapapi.MapAttributes;
import mapeditor.mapapi.Tools;
import mapeditor.messages.MapMessages;
import mapeditor.saveload.MapLoaderSAXHandler;
import mapeditor.saveload.MapSaver;
import mapeditor.themesapi.MapObjectFactory;
import mapeditor.themesapi.ThemesManager;

import org.xml.sax.SAXException;

import otherprods.ExampleFileFilter;

public class DialogsManager {

	private MapPane mapPanel;
	private MapApi mapApi;
	private MapMessages messages;
	private ThemesManager mapThemesList;
	private Config config;
	private Tools tools;
	private MapObjectFactory mapObjectFactory;
	private LayersControlPane layersPane;

	DialogsManager(MapPane mapPanel, MapApi mapApi, MapMessages messages,
			ThemesManager mapThemesList, Config config, Tools tools,
			MapObjectFactory mapObjectFactory, LayersControlPane layersPane) {
		this.mapPanel = mapPanel;
		this.mapApi = mapApi;
		this.messages = messages;
		this.mapThemesList = mapThemesList;
		this.config = config;
		this.tools = tools;
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
				p_MapSaver.saveMapToFile(p_MapApi, rFile);
			} catch (Exception e) {

				String msg = messages.getString(MapMessages.MSG_SAVING_FAILED)
						+ " " + e.getMessage();
				JOptionPane.showMessageDialog(FC, msg);
				e.printStackTrace();
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

		ExampleFileFilter rfilter = new ExampleFileFilter("xml", "XML Files");

		fileChooser.setFileFilter(rfilter);
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
					System.out.println(xmlFile.getSystemId() + " is valid");

					MapLoaderSAXHandler handler = new MapLoaderSAXHandler(
							mapApi, mapThemesList, mapObjectFactory);
					saxParser.parse(file, handler);

					mapPanel.setMapApi(mapApi);
					mapPanel.getPanel().repaint();
				} catch (SAXException e) {
					System.out.println(xmlFile.getSystemId() + " is NOT valid");
					System.out.println("Reason: " + e.getLocalizedMessage());
				}
			} catch (Exception e) {
				String msg = messages.getString(MapMessages.MSG_LOADING_FAILED)
						+ e.getMessage();
				JOptionPane.showMessageDialog(fileChooser, msg);
				e.printStackTrace();
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
