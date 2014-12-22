package mapeditor.themesapi;

import java.io.File;
import java.io.IOException;

import javax.swing.ImageIcon;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;

import mapeditor.config.Config;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

public class ImagesListFileReader extends DefaultHandler {

	private MapObjectsTheme curMapObjectsTheme;
	private ThemeApi themeApi;
	private MapObject curMapObject;
	private MapThemesManager mapThemesList;
	private String filePath;
	private int imageId;
	private Config config;

	@Override
	public void startDocument() throws SAXException {
	}

	@Override
	public void startElement(String uri, String localName, String qName,
			Attributes attrs) throws SAXException {
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
						this.curMapObjectsTheme = new MapObjectsTheme(aValue);// OK
						themeApi = new ThemeApi(aValue, config);
						this.curMapObject = null;
						this.mapThemesList.addTheme(curMapObjectsTheme);// OK
						mapThemesList.addThemeApi(themeApi);
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
	public void characters(char[] ch, int start, int length)
			throws SAXException {
		String curString = new String(ch, start, length).trim();
		if (curString.equals("*")) {
			this.curMapObject.setImageName("");
			ImageIcon imageFile = new ImageIcon(filePath + "");
			/*
			 * If there is no path+l_str file ImageFile will be blank.
			 */
			this.curMapObject.setImageIcon(imageFile);
			// This is blank image so id=0
			this.curMapObject.setObjectId(0);
			this.curMapObjectsTheme.addMapObject(curMapObject);// OK
			themeApi.addMapObject(curMapObject);
		} else if (curString.equals("") == false) {
			this.curMapObject.setImageName(curString);
			ImageIcon imageFile = new ImageIcon(filePath + curString);
			/*
			 * If there is no path+l_str file ImageFile will be blank.
			 */
			this.curMapObject.setImageIcon(imageFile);
			this.imageId++;
			this.curMapObject.setObjectId(this.imageId);
			this.curMapObjectsTheme.addMapObject(curMapObject);// OK
			themeApi.addMapObject(curMapObject);
		}
	}

	public MapThemesManager ReadConfigurationFile(Config config, String path,
			String file) throws ParserConfigurationException, SAXException,
			IOException {
		this.curMapObjectsTheme = null;// OK
		themeApi = null;
		this.curMapObject = null;
		this.config = config;
		mapThemesList = new MapThemesManager();
		imageId = 0;
		this.filePath = path + File.separator;

		// Use the default (non-validating) parser
		SAXParserFactory factory = SAXParserFactory.newInstance();
		SAXParser saxParser = factory.newSAXParser();
		saxParser.parse(new File(this.filePath + file), this);

		mapThemesList.setSelectedTheme(mapThemesList.getFirstTheme());
		return mapThemesList;
	}
}
