package mapeditor.saveload;

import java.util.Hashtable;

import mapeditor.mapapi.MapApi;
import mapeditor.mapapi.MapAttributes;
import mapeditor.mapapi.MapLayout;
import mapeditor.themesapi.CustomMapObject;
import mapeditor.themesapi.MapObject;
import mapeditor.themesapi.MapObjectFactory;
import mapeditor.themesapi.ThemesManager;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

public class MapLoaderSAXHandler extends DefaultHandler {

	private MapApi mapApi;
	private ThemesManager mapThemesList;
	private MapObjectFactory mapObjectFactory;
	private Hashtable<String, String> segmentsCode;
	private int activeLayerIndex;
	private CustomMapObject customMapObject;
	private int customMapObjectRow;
	private int customMapObjectCol;

	public MapLoaderSAXHandler(MapApi mapApi, ThemesManager mapThemesList,
			MapObjectFactory mapObjectFactory) {

		this.mapApi = mapApi;
		this.mapThemesList = mapThemesList;
		this.mapObjectFactory = mapObjectFactory;

		segmentsCode = new Hashtable<String, String>();
	}

	@Override
	public void startDocument() throws SAXException {
	}

	@Override
	public void startElement(String uri, String localName, String qName,
			Attributes attrs) throws SAXException {

		if (qName.equals(MapFileDefinitions.MAP_XML_ELEMENT)) {
			// Do nothing
		} else if (qName.equals(MapFileDefinitions.PROPERTIES_ELEMENT)) {
			startPropertiesElement(attrs);
		} else if (qName.equals(MapFileDefinitions.CODE_ELEMENT)) {
			startCodeElement(attrs);
		} else if (qName.equals(MapFileDefinitions.LAYER_ELEMENT)) {
			startLayerElement(attrs);
		} else if (qName.equals(MapFileDefinitions.ROW_ELEMENT)) {
			startRowElement(attrs);
		} else if (qName.equals(MapFileDefinitions.CUSTOM_OBJECT_ELEMENT)) {
			startCustomObjectElement(attrs);
		} else if (qName.equals(MapFileDefinitions.OBJECT_PROPERTY_ELEMENT)) {
			startObjectPropertyElement(attrs);
		}

	}

	@Override
	public void endElement(String uri, String localName, String qName)
			throws SAXException {

		if (qName.equals(MapFileDefinitions.OBJECT_PROPERTY_ELEMENT)) {
			endObjectPropertyElement();
		}

	}

	private void startPropertiesElement(Attributes attrs) {

		String atrCols = attrs.getValue(MapFileDefinitions.COLUMNS_ATTRIBUTE);

		String atrRows = attrs.getValue(MapFileDefinitions.ROWS_ATTRIBUTE);
		String atrLayers = attrs.getValue(MapFileDefinitions.LAYERS_ATTRIBUTE);

		String layout = attrs.getValue(MapFileDefinitions.LAYOUT_ATTRIBUTE);

		int cols = Integer.parseInt(atrCols);
		int rows = Integer.parseInt(atrRows);
		int layers = Integer.parseInt(atrLayers);

		MapLayout mapLayout = MapLayout.SQR;

		if (layout.equals(MapLayout.HEX.toString())) {
			mapLayout = MapLayout.HEX;
		}

		MapAttributes mapAttributes = new MapAttributes(rows, cols, layers,
				mapLayout);

		mapApi.resetMap(mapAttributes, mapObjectFactory.getBlankMapObject());
	}

	private void startCodeElement(Attributes attrs) {

		String id = attrs.getValue(MapFileDefinitions.ID_ATTRIBUTE);
		String image = attrs.getValue(MapFileDefinitions.IMAGE_ATTRIBUTE);

		if (segmentsCode.get(id) == null) {
			segmentsCode.put(id, image);
		}
	}

	private void startLayerElement(Attributes attrs) {
		String index = attrs.getValue(MapFileDefinitions.INDEX_ATTRIBUTE);
		activeLayerIndex = Integer.parseInt(index);
	}

	private void startObjectPropertyElement(Attributes attrs) {
		String nameAttr = attrs
				.getValue(MapFileDefinitions.PROPERTY_NAME_ATTRIBUTE);
		String typeAttr = attrs
				.getValue(MapFileDefinitions.PROPERTY_TYPE_ATTRIBUTE);
		String valueAttr = attrs
				.getValue(MapFileDefinitions.PROPERTY_VALUE_ATTRIBUTE);

		customMapObject.setProperty(nameAttr, typeAttr, valueAttr);

	}

	private void startCustomObjectElement(Attributes attrs) {
		String idAttr = attrs.getValue(MapFileDefinitions.ID_ATTRIBUTE);
		String colAttr = attrs.getValue(MapFileDefinitions.COL_ATTRIBUTE);
		String rowAttr = attrs.getValue(MapFileDefinitions.ROW_ATTRIBUTE);

		String name = segmentsCode.get(idAttr);
		MapObject mapObject = mapThemesList.getMapObjectApi(name);

		if (mapObject instanceof CustomMapObject) {
			customMapObject = ((CustomMapObject) mapObject).clone();
		}

		customMapObjectRow = Integer.parseInt(rowAttr);
		customMapObjectCol = Integer.parseInt(colAttr);

		// mapApi.getSegment(row, col).setMapObject(mapObject,
		// activeLayerIndex);
	}

	private void endObjectPropertyElement() {
		// TODO Auto-generated method stub
		mapApi.getSegment(customMapObjectRow, customMapObjectCol).setMapObject(
				customMapObject, activeLayerIndex);

	}

	private void startRowElement(Attributes attrs) {

		int rowNumber = -1;

		String rowNumberAttr = attrs
				.getValue(MapFileDefinitions.NUMBER_ATTRIBUTE);

		rowNumber = Integer.parseInt(rowNumberAttr);

		String segmentsAttr = attrs
				.getValue(MapFileDefinitions.SEGMENTS_ATTRIBUTE);

		String[] segments = segmentsAttr.split(";");
		int col = 0;
		for (String segment : segments) {
			String name = segmentsCode.get(segment);
			MapObject mapObject = mapThemesList.getMapObjectApi(name);

			mapApi.getSegment(rowNumber, col).setMapObject(mapObject,
					activeLayerIndex);
			col++;
		}

	}

}
