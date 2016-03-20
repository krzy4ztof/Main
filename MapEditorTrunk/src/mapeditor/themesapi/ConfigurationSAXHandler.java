package mapeditor.themesapi;

import java.io.File;

import javax.swing.ImageIcon;

import mapeditor.config.Config;
import mapeditor.messages.MapMessages;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

public class ConfigurationSAXHandler extends DefaultHandler {

	public final static String THEME_GROUP_TAG = "themeGroup";
	public final static String MAP_THEME_TAG = "mapTheme";
	public final static String MAP_OBJECT_TAG = "mapObject";
	public final static String OBJECT_PROPERTY_TAG = "objectProperty";
	public final static String ENUM_VALUE_TAG = "enumValue";
	public final static String NAME_ATTR = "name";
	public final static String IMAGE_NAME_ATTR = "image";
	public final static String IMAGE_FOLDER_ATTR = "folder";
	public final static String TYPE_ATTR = "type";
	public final static String DEFAULT_ATTR = "default";

	private ThemeApi themeApi;
	private MapObject curMapObject;
	private CustomMapObject curCustomMapObject;
	private EnumProperty curEnumProperty;
	private ThemesManager mapThemesList;
	private String imagesPath;
	private int imageId;
	private Config config;
	private MapMessages mapMessages;

	public ConfigurationSAXHandler(Config config,
			ThemesManager mapThemesManager, MapMessages mapMessages,
			String imagesPath) {
		this.config = config;
		mapThemesList = mapThemesManager;
		imageId = 0;
		this.imagesPath = imagesPath;
		this.mapMessages = mapMessages;
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
		String imageFolder = attrs.getValue(IMAGE_FOLDER_ATTR);

		ImageIcon imageFile = null;
		if (imageFolder != null) {
			imageFile = new ImageIcon(imagesPath + imageFolder + File.separator
					+ imageName);

			name = imageFolder + File.separator + name;
		} else {
			imageFile = new ImageIcon(imagesPath + imageName);
		}

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
		String imageFolder = attrs.getValue(IMAGE_FOLDER_ATTR);
		String externalName = mapMessages.getString(MapMessages.THEMENAME
				+ name);

		ImageIcon imageFile = null;
		if (imageFolder != null) {
			imageFile = new ImageIcon(imagesPath + imageFolder + File.separator
					+ imageName);

			name = imageFolder + File.separator + name;
		} else {
			imageFile = new ImageIcon(imagesPath + imageName);
		}

		curCustomMapObject = new CustomMapObject(name, externalName);
		curCustomMapObject.setImageName(imageName);
		curCustomMapObject.setImageIcon(imageFile);
		imageId++;
		curCustomMapObject.setObjectId(imageId);

		themeApi.addMapObject(curCustomMapObject);
	}

	private void startObjectPropertyElement(Attributes attrs) {

		String name = mapMessages.getString(MapMessages.THEMENAME
				+ attrs.getValue(NAME_ATTR));

		String type = attrs.getValue(TYPE_ATTR);
		String defaultValue = attrs.getValue(DEFAULT_ATTR);

		MapObjectProperty property = null;
		if (type.equals(MapObjectProperty.Type.Long.toString())) {
			property = new LongProperty(name, defaultValue);
		} else if (type.equals(MapObjectProperty.Type.String.toString())) {
			property = new StringProperty(name, defaultValue);
		} else if (type.equals(MapObjectProperty.Type.Text.toString())) {
			property = new TextProperty(name, defaultValue);
		} else if (type.equals(MapObjectProperty.Type.Enum.toString())) {

			String defaultValueExternal = mapMessages
					.getString(MapMessages.THEMENAME + defaultValue);

			curEnumProperty = new EnumProperty(name, defaultValue,
					defaultValueExternal);
			property = curEnumProperty;
		} else if (type.equals(MapObjectProperty.Type.Point.toString())) {
			property = new PointProperty(name, defaultValue);
		}

		if (property != null) {
			curCustomMapObject.addProperty(property);
		}
	}

	private void startEnumValueElement(Attributes attrs) {

		String value = attrs.getValue(NAME_ATTR);
		String valueExternal = mapMessages.getString(MapMessages.THEMENAME
				+ value);

		curEnumProperty.addChoiceValue(value, valueExternal);

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
			} else if (qName.equals(ENUM_VALUE_TAG)) {
				startEnumValueElement(attrs);
			}
		}
	}
}
