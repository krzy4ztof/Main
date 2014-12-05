/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package mapEditor.main;

import java.io.IOException;
import java.util.Locale;
import java.util.ResourceBundle;
import javax.xml.parsers.ParserConfigurationException;
import mapEditor.mainWindow.GraphicsSystem;
import mapEditor.themesApi.ImagesListFileReader;
import mapEditor.themesApi.MapThemesList;
import org.xml.sax.SAXException;

/**
 *
 * @author krzysztof
 */
public class ApplicationManager {

    public ApplicationManager(String[] args) throws ParserConfigurationException, IOException, SAXException {

        String language;
        String country;

        if (args.length != 2) {
            language = new String("en");
            country = new String("GB");
        } else {
            language = new String(args[0]);
            country = new String(args[1]);
        }
        Locale currentLocale;
        currentLocale = new Locale(language, country);
        ResourceBundle messages = ResourceBundle.getBundle("mapEditor.messages.MessagesBundle", currentLocale);
        ImagesListFileReader r_ImagesListFileReader = new ImagesListFileReader();
        MapThemesList mapThemesList = r_ImagesListFileReader.ReadConfigurationFile("Images", "Configuration.xml");
        GraphicsSystem p_GraphicsSystem = new GraphicsSystem(messages, mapThemesList);

        p_GraphicsSystem.activate();

    }

    public static void main(String[] args) throws ParserConfigurationException,
            IOException, SAXException {
        new ApplicationManager(args);
    }
}
