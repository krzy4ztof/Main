/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package mapeditor.main;

import java.io.File;
import java.io.IOException;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;

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

	public final static String THEMES_PATH = "resources" + File.separator
			+ "themes" + File.separator;
	public final static String THEMES_CONFIG_FILE_PATH = THEMES_PATH
			+ "configuration.xml";
	public final static String THEMES_IMAGES_PATH = "images" + File.separator;

	public ApplicationManager() throws ParserConfigurationException,
			IOException, SAXException {

		Config config = new Config();
		MapMessages messages = new MapMessages(config);
		MapObjectFactory mapObjectFactory = new MapObjectFactory();
		ThemesManager mapThemesList = readConfigurationFile(config,
				mapObjectFactory);
		new MainWindow(config, messages, mapThemesList, mapObjectFactory);

		mapThemesList.describeYourselfThemeApi();
	}

	public static void main(String[] args) throws ParserConfigurationException,
			IOException, SAXException {
		new ApplicationManager();
	}

	private ThemesManager readConfigurationFile(Config config,
			MapObjectFactory mapObjectFactory)
			throws ParserConfigurationException, SAXException, IOException {

		SAXParserFactory factory = SAXParserFactory.newInstance();
		SAXParser saxParser = factory.newSAXParser();

		ThemesManager mapThemesManager = new ThemesManager(mapObjectFactory);

		ConfigurationSAXHandler handler = new ConfigurationSAXHandler(config,
				mapThemesManager, THEMES_IMAGES_PATH);
		saxParser.parse(new File(THEMES_CONFIG_FILE_PATH), handler);

		return mapThemesManager;

	}
}
