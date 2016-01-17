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
		if (attrs != null) {
			if (qName.equals(THEME_GROUP_TAG)) {
				startThemeGroupElement(attrs);
			} else if (qName.equals(MAP_THEME_TAG)) {
				startMapThemeElement(attrs);
			} else if (qName.equals(MAP_OBJECT_TAG)) {
				startMapObjectElement(attrs);
			} else if (qName.equals(OBJECT_PROPERTY_TAG)) {
				startObjectPropertyElement(attrs);
			}
		}
	}
}
