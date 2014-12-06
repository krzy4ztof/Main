package mapeditor.themesapi;

import java.io.IOException;
import javax.xml.parsers.ParserConfigurationException;
import mapeditor.mapapi.MapObject;
import java.io.File;

import javax.swing.ImageIcon;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

public class ImagesListFileReader extends DefaultHandler {

    private MapObjectsTheme curMapObjectsTheme;
    private MapObject curMapObject;
    private MapThemesList mapThemesList;
    private ImageIcon ImageFile;
    private String FilePath;
    private int ImageId;

    @Override
    public void startDocument() throws SAXException {
    }

    @Override
    public void startElement(String uri, String localName, String qName, Attributes attrs) throws SAXException {
        String aName;
        String aValue;
        if (attrs != null) {
            for (int i = 0; i < attrs.getLength(); i++) {
                aName = attrs.getLocalName(i);

                if ("".equals(aName)) {
                    aName = attrs.getQName(i);
                }
                aValue = attrs.getValue(i);

                if (qName.equals("Theme")) {
                    if (aName.equals("name")) {
                        this.curMapObjectsTheme = new MapObjectsTheme(aValue);
                        this.curMapObject = null;
                        this.mapThemesList.addTheme(curMapObjectsTheme);
                    }
                } else if (qName.equals("Image")) {
                    if (aName.equals("name")) {
                        this.curMapObject = new MapObject(aValue);
                    }
                }
            }
        }
    }

    @Override
    public void characters(char[] ch, int start, int length) throws SAXException {
        String curString = new String(ch, start, length).trim();
        if (curString.equals("*")) {
            this.curMapObject.setImageName("");
            ImageFile = new ImageIcon(FilePath + "");
            /* If there is no path+l_str file ImageFile
            will be blank.*/
            this.curMapObject.setImageIcon(ImageFile);
            // This is blank image so id=0
            this.curMapObject.setObjectId(0);
            this.curMapObjectsTheme.addMapObject(curMapObject);
        } else if (curString.equals("") == false) {
            this.curMapObject.setImageName(curString);
            ImageFile = new ImageIcon(FilePath + curString);
            /* If there is no path+l_str file ImageFile
            will be blank.*/
            this.curMapObject.setImageIcon(ImageFile);
            this.ImageId++;
            this.curMapObject.setObjectId(this.ImageId);
            this.curMapObjectsTheme.addMapObject(curMapObject);
        }
    }

    public MapThemesList ReadConfigurationFile(String p_path, String p_file)
            throws ParserConfigurationException, SAXException, IOException {
        this.curMapObjectsTheme = null;
        this.curMapObject = null;
        mapThemesList = new MapThemesList();
        ImageFile = new ImageIcon();
        ImageId = 0;
        this.FilePath = p_path + File.separator;

        // Use the default (non-validating) parser
        SAXParserFactory factory = SAXParserFactory.newInstance();
        SAXParser saxParser = factory.newSAXParser();
        saxParser.parse(new File(this.FilePath + p_file), this);
        return mapThemesList;
    }
}
