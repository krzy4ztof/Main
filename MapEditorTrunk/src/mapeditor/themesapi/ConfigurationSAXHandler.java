package mapeditor.themesapi;

import javax.swing.ImageIcon;

import mapeditor.config.Config;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

public class ConfigurationSAXHandler extends DefaultHandler {

	public final static String THEME_GROUP_TAG = "ThemeGroup";
	public final static String MAP_THEME_TAG = "MapTheme";
	public final static String MAP_OBJECT_TAG = "MapObject";
	public final static String OBJECT_PROPERTY_TAG = "ObjectProperty";
	public final static String NAME_ATTR = "name";
	public final static String IMAGE_NAME_ATTR = "image";
	public final static String TYPE_ATTR = "type";
	public final static String DEFAULT_ATTR = "default";

	private ThemeApi themeApi;
	private MapObject curMapObject;
	private CustomMapObject curCustomMapObject;
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

	private void startThemeGroupElement(Attributes attrs) {
		String name = attrs.getValue(NAME_ATTR);
		themeApi = new ThemeApi(name, config);
		curMapObject = null;
		curCustomMapObject = null;

		mapThemesList.addThemeApi(themeApi);

		/*
		 * for (int i = 0; i < attrs.getLength(); i++) { aName =
		 * attrs.getLocalName(i);
		 * 
		 * if ("".equals(aName)) { aName = attrs.getQName(i); } aValue =
		 * attrs.getValue(i);
		 */

		/*
		 * if (aName.equals(NAME_ATTR)) { themeApi = new ThemeApi(aValue,
		 * config); curMapObject = null; // mapThemesList.addThemeApi(themeApi);
		 * }
		 */
	}

	private void startMapThemeElement(Attributes attrs) {
		String name = attrs.getValue(NAME_ATTR);
		String imageName = attrs.getValue(IMAGE_NAME_ATTR);
		ImageIcon imageFile = new ImageIcon(imagesPath + imageName);

		curMapObject = new MapObject(name);
		curMapObject.setImageName(imageName);
		curMapObject.setImageIcon(imageFile);
		imageId++;
		curMapObject.setObjectId(imageId);

		themeApi.addMapObject(curMapObject);

		/*
		 * if (aName.equals(NAME_ATTR)) { curMapObject = new MapObject(aValue);
		 * } else if (aName.equals(IMAGE_NAME_ATTR)) {
		 * curMapObject.setImageName(aValue); ImageIcon imageFile = new
		 * ImageIcon(imagesPath + aValue); curMapObject.setImageIcon(imageFile);
		 * imageId++; curMapObject.setObjectId(imageId); //
		 * themeApi.addMapObject(curMapObject); }
		 */
	}

	private void startMapObjectElement(Attributes attrs) {
		String name = attrs.getValue(NAME_ATTR);
		String imageName = attrs.getValue(IMAGE_NAME_ATTR);
		ImageIcon imageFile = new ImageIcon(imagesPath + imageName);

		curCustomMapObject = new CustomMapObject(name);
		curCustomMapObject.setImageName(imageName);
		curCustomMapObject.setImageIcon(imageFile);
		imageId++;
		curCustomMapObject.setObjectId(imageId);

		themeApi.addMapObject(curCustomMapObject);

		/*
		 * if (aName.equals(NAME_ATTR)) { curCustomMapObject = new
		 * CustomMapObject(aValue); } else if (aName.equals(IMAGE_NAME_ATTR)) {
		 * curCustomMapObject.setImageName(aValue); ImageIcon imageFile = new
		 * ImageIcon(imagesPath + aValue);
		 * curCustomMapObject.setImageIcon(imageFile); imageId++;
		 * curCustomMapObject.setObjectId(imageId); //
		 * themeApi.addMapObject(curCustomMapObject); }
		 */
	}

	private void startObjectPropertyElement(Attributes attrs) {
		String name = attrs.getValue(NAME_ATTR);
		String type = attrs.getValue(TYPE_ATTR);
		String defaultValue = attrs.getValue(DEFAULT_ATTR);

		MapObjectProperty property = null;
		if (type.equals(MapObjectProperty.Type.Integer.toString())) {
			property = new IntegerProperty(name, defaultValue);
		}
		if (property != null) {
			curCustomMapObject.addProperty(property);
		}
	}

	@Override
	public void startElement(String uri, String localName, String qName,
			Attributes attrs) throws SAXException {
		// String aName;
		// String aValue;
		if (attrs != null) {
			/*
			 * for (int i = 0; i < attrs.getLength(); i++) { aName =
			 * attrs.getLocalName(i);
			 * 
			 * if ("".equals(aName)) { aName = attrs.getQName(i); } aValue =
			 * attrs.getValue(i);
			 */
			if (qName.equals(THEME_GROUP_TAG)) {
				startThemeGroupElement(attrs);
				/*
				 * if (aName.equals(NAME_ATTR)) { themeApi = new
				 * ThemeApi(aValue, config); curMapObject = null; //
				 * mapThemesList.addThemeApi(themeApi); }
				 */
			} else if (qName.equals(MAP_THEME_TAG)) {
				startMapThemeElement(attrs);
				/*
				 * if (aName.equals(NAME_ATTR)) { curMapObject = new
				 * MapObject(aValue); } else if (aName.equals(IMAGE_NAME_ATTR))
				 * { curMapObject.setImageName(aValue); ImageIcon imageFile =
				 * new ImageIcon(imagesPath + aValue);
				 * curMapObject.setImageIcon(imageFile); imageId++;
				 * curMapObject.setObjectId(imageId); //
				 * themeApi.addMapObject(curMapObject); }
				 */
			} else if (qName.equals(MAP_OBJECT_TAG)) {
				startMapObjectElement(attrs);
				/*
				 * if (aName.equals(NAME_ATTR)) { curCustomMapObject = new
				 * CustomMapObject(aValue); } else if
				 * (aName.equals(IMAGE_NAME_ATTR)) {
				 * curCustomMapObject.setImageName(aValue); ImageIcon imageFile
				 * = new ImageIcon(imagesPath + aValue);
				 * curCustomMapObject.setImageIcon(imageFile); imageId++;
				 * curCustomMapObject.setObjectId(imageId); //
				 * themeApi.addMapObject(curCustomMapObject); }
				 */
			} else if (qName.equals(OBJECT_PROPERTY_TAG)) {
				startObjectPropertyElement(attrs);

			}
		}
		// }
	}

	/*
	 * @Override public void endElement(String uri, String localName, String
	 * qName) throws SAXException {
	 * 
	 * if (qName.equals(THEME_GROUP_TAG)) { mapThemesList.addThemeApi(themeApi);
	 * } else if (qName.equals(MAP_THEME_TAG)) {
	 * themeApi.addMapObject(curMapObject); } else if
	 * (qName.equals(MAP_OBJECT_TAG)) {
	 * themeApi.addMapObject(curCustomMapObject); } else if
	 * (qName.equals(OBJECT_PROPERTY_TAG)) {
	 * 
	 * } }
	 */

	/*
	 * @Override public void characters(char[] ch, int start, int length) throws
	 * SAXException { String curString = new String(ch, start, length).trim();
	 * 
	 * if (!curString.trim().equals("")) { curMapObject.setImageName(curString);
	 * ImageIcon imageFile = new ImageIcon(imagesPath + curString);
	 * curMapObject.setImageIcon(imageFile); imageId++;
	 * curMapObject.setObjectId(imageId); themeApi.addMapObject(curMapObject); }
	 * }
	 */
}
