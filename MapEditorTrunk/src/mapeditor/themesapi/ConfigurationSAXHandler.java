package mapeditor.themesapi;

import javax.swing.ImageIcon;

import mapeditor.config.Config;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

public class ConfigurationSAXHandler extends DefaultHandler {

	public final static String TAG_THEME = "Theme";
	public final static String TAG_IMAGE = "Image";
	public final static String ATTR_NAME = "name";

	private MapObjectsTheme curMapObjectsTheme;
	private ThemeApi themeApi;
	private MapObject curMapObject;
	private ThemesManager mapThemesList;
	private String imagesPath;
	private int imageId;
	private Config config;

	public ConfigurationSAXHandler(Config config,
			ThemesManager mapThemesManager, String imagesPath) {
		this.config = config;
		mapThemesList = mapThemesManager;
		imageId = 0;
		this.imagesPath = imagesPath;
	}

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

				if (qName.equals(TAG_THEME)) {
					if (aName.equals(ATTR_NAME)) {
						curMapObjectsTheme = new MapObjectsTheme(aValue);// OK
						themeApi = new ThemeApi(aValue, config);
						curMapObject = null;
						mapThemesList.addTheme(curMapObjectsTheme);// OK
						mapThemesList.addThemeApi(themeApi);
					}
				} else if (qName.equals(TAG_IMAGE)) {
					if (aName.equals(ATTR_NAME)) {
						curMapObject = new MapObject(aValue);
					}
				}
			}
		}
	}

	@Override
	public void characters(char[] ch, int start, int length)
			throws SAXException {
		String curString = new String(ch, start, length).trim();
		/*
		 * if (curString.equals("*")) { this.curMapObject.setImageName("");
		 * ImageIcon imageFile = new ImageIcon(imagesPath + "");
		 * this.curMapObject.setImageIcon(imageFile);
		 * this.curMapObject.setObjectId(0);
		 * this.curMapObjectsTheme.addMapObject(curMapObject);// OK
		 * themeApi.addMapObject(curMapObject); } else
		 */
		if (!curString.trim().equals("")) {
			curMapObject.setImageName(curString);
			ImageIcon imageFile = new ImageIcon(imagesPath + curString);
			curMapObject.setImageIcon(imageFile);
			imageId++;
			curMapObject.setObjectId(imageId);
			curMapObjectsTheme.addMapObject(curMapObject);// OK
			themeApi.addMapObject(curMapObject);
		}
	}

}
