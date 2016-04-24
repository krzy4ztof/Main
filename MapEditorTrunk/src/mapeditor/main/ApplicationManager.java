package mapeditor.main;

import java.io.File;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;

import javax.xml.XMLConstants;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;
import javax.xml.transform.Source;
import javax.xml.transform.stream.StreamSource;
import javax.xml.validation.Schema;
import javax.xml.validation.SchemaFactory;
import javax.xml.validation.Validator;

import mapeditor.config.Config;
import mapeditor.logger.MapLogger;
import mapeditor.mainwindow.MainWindow;
import mapeditor.messages.MapMessages;
import mapeditor.themesapi.ConfigurationSAXHandler;
import mapeditor.themesapi.MapObjectFactory;
import mapeditor.themesapi.ThemesManager;

import org.xml.sax.SAXException;

public class ApplicationManager {

	private static final Logger logger = Logger
			.getLogger(ApplicationManager.class.getName());

	private final static String RESOURCES_PATH = "resources" + File.separator;

	public final static String THEMES_PATH = RESOURCES_PATH + "themes"
			+ File.separator;
	public final static String THEMES_CONFIG_FILE_PATH = THEMES_PATH
			+ "configuration.xml";

	public final static String THEMES_IMAGES_PATH = RESOURCES_PATH
			+ "mapObjects" + File.separator;

	public final static String XSD_FOLDER = RESOURCES_PATH + "xsd"
			+ File.separator;

	private final static String CONFIG_PATH = RESOURCES_PATH + "config"
			+ File.separator;

	private final static String LOGGER_CONFIG_FILE_PATH = CONFIG_PATH
			+ "mapLogging.properties";

	public ApplicationManager() throws ParserConfigurationException,
			IOException, SAXException {

		MapLogger mapLogger = new MapLogger(LOGGER_CONFIG_FILE_PATH);

		logger.log(Level.INFO, MapLogger.APPLICATION_STARTUP);

		Config config = new Config(RESOURCES_PATH);
		MapMessages messages = new MapMessages(config);
		MapObjectFactory mapObjectFactory = new MapObjectFactory();
		ThemesManager mapThemesList = readConfigurationFile(config,
				mapObjectFactory, messages, mapLogger);
		new MainWindow(config, messages, mapThemesList, mapObjectFactory);

		mapThemesList.describeYourselfThemeApi();
	}

	public static void main(String[] args) throws ParserConfigurationException,
			IOException, SAXException {
		new ApplicationManager();
	}

	private ThemesManager readConfigurationFile(Config config,
			MapObjectFactory mapObjectFactory, MapMessages messages,
			MapLogger mapLogger) throws ParserConfigurationException,
			SAXException, IOException {

		SAXParserFactory factory = SAXParserFactory.newInstance();
		SAXParser saxParser = factory.newSAXParser();

		ThemesManager mapThemesManager = new ThemesManager(mapObjectFactory);
		File file = new File(THEMES_CONFIG_FILE_PATH);

		Source schemaFile = new StreamSource(new File(
				ApplicationManager.XSD_FOLDER, "themes.xsd"));
		SchemaFactory schemaFactory = SchemaFactory
				.newInstance(XMLConstants.W3C_XML_SCHEMA_NS_URI);
		Schema schema = schemaFactory.newSchema(schemaFile);

		Source xmlFile = new StreamSource(file);
		Validator validator = schema.newValidator();
		try {
			validator.validate(xmlFile);
			logger.log(Level.INFO, MapLogger.FILE_VALID, xmlFile.getSystemId());
			ConfigurationSAXHandler handler = new ConfigurationSAXHandler(
					config, mapThemesManager, messages, THEMES_IMAGES_PATH);
			saxParser.parse(file, handler);
		} catch (SAXException e) {
			logger.log(Level.SEVERE, MapLogger.FILE_NOT_VALID,
					xmlFile.getSystemId());
			logger.log(Level.SEVERE, MapLogger.REASON, e);
			throw e;
		}

		return mapThemesManager;

	}
}
