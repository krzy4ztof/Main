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
		ThemesManager mapThemesList = readConfigurationFile(config);
		new MainWindow(config, messages, mapThemesList);

		mapThemesList.describeYourselfThemeApi();
	}

	public static void main(String[] args) throws ParserConfigurationException,
			IOException, SAXException {
		new ApplicationManager();
	}

	private ThemesManager readConfigurationFile(Config config)
			throws ParserConfigurationException, SAXException, IOException {

		// ImagesListFileReader imagesListFileReader = new
		// ImagesListFileReader();
		// MapThemesManager mapThemesList = imagesListFileReader
		// .ReadConfigurationFile(config, THEMES_CONFIG_FILE_PATH,
		// THEMES_IMAGES_PATH);

		// Use the default (non-validating) parser
		SAXParserFactory factory = SAXParserFactory.newInstance();
		SAXParser saxParser = factory.newSAXParser();

		ThemesManager mapThemesManager = new ThemesManager();

		ConfigurationSAXHandler handler = new ConfigurationSAXHandler(config,
				mapThemesManager, THEMES_IMAGES_PATH);
		saxParser.parse(new File(THEMES_CONFIG_FILE_PATH), handler);

		mapThemesManager.setSelectedTheme(mapThemesManager.getFirstTheme());
		return mapThemesManager;

	}
}
