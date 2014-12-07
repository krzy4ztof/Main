/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package mapeditor.main;

import java.io.IOException;
import java.util.Locale;
import java.util.ResourceBundle;

import javax.xml.parsers.ParserConfigurationException;

import mapeditor.config.Config;
import mapeditor.mainwindow.GraphicsSystem;
import mapeditor.themesapi.ImagesListFileReader;
import mapeditor.themesapi.MapThemesList;

import org.xml.sax.SAXException;

/**
 *
 * @author krzysztof
 */
public class ApplicationManager {

    public ApplicationManager() throws ParserConfigurationException, IOException, SAXException {

    	Config config = new Config();

        Locale currentLocale;
        currentLocale = new Locale(config.getLanguage());
        ResourceBundle messages = ResourceBundle.getBundle("mapeditor.messages.MessagesBundle", currentLocale);
        
        
        ImagesListFileReader imagesListFileReader = new ImagesListFileReader();
        MapThemesList mapThemesList = imagesListFileReader.ReadConfigurationFile("images", "configuration.xml");
        GraphicsSystem graphicsSystem = new GraphicsSystem(config, messages, mapThemesList);

        graphicsSystem.activate();

    }

    public static void main(String[] args) throws ParserConfigurationException,
            IOException, SAXException {
        new ApplicationManager();
    }
}
