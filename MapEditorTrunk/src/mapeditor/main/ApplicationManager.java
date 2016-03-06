package mapeditor.main;

import java.io.File;
import java.io.IOException;

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
import mapeditor.mainwindow.MainWindow;
import mapeditor.messages.MapMessages;
import mapeditor.themesapi.ConfigurationSAXHandler;
import mapeditor.themesapi.MapObjectFactory;
import mapeditor.themesapi.ThemesManager;

import org.xml.sax.SAXException;

/**
 *
 * @author krzysztof
 */
public class ApplicationManager {

	private final static String RESOURCES_PATH = "resources" + File.separator;

	public final static String THEMES_PATH = RESOURCES_PATH + "themes"
			+ File.separator;
	public final static String THEMES_CONFIG_FILE_PATH = THEMES_PATH
			+ "configuration.xml";

	public final static String THEMES_IMAGES_PATH = RESOURCES_PATH
			+ "mapObjects" + File.separator;

	public final static String XSD_FOLDER = RESOURCES_PATH + "xsd"
			+ File.separator;

	public ApplicationManager() throws ParserConfigurationException,
			IOException, SAXException {

		Config config = new Config();
		MapMessages messages = new MapMessages(config);
		MapObjectFactory mapObjectFactory = new MapObjectFactory();
		ThemesManager mapThemesList = readConfigurationFile(config,
				mapObjectFactory, messages);
		new MainWindow(config, messages, mapThemesList, mapObjectFactory);

		mapThemesList.describeYourselfThemeApi();
	}

	public static void main(String[] args) throws ParserConfigurationException,
			IOException, SAXException {
		new ApplicationManager();
	}

	private ThemesManager readConfigurationFile(Config config,
			MapObjectFactory mapObjectFactory, MapMessages messages)
			throws ParserConfigurationException, SAXException, IOException {

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
			System.out.println(xmlFile.getSystemId() + " is valid");
			ConfigurationSAXHandler handler = new ConfigurationSAXHandler(
					config, mapThemesManager, messages, THEMES_IMAGES_PATH);
			saxParser.parse(file, handler);
		} catch (SAXException e) {
			System.out.println(xmlFile.getSystemId() + " is NOT valid");
			System.out.println("Reason: " + e.getLocalizedMessage());
			throw e;
		}

		return mapThemesManager;

	}
}
