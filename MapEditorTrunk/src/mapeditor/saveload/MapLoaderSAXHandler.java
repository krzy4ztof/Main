package mapeditor.saveload;

import java.util.Hashtable;

import mapeditor.mapapi.MapApi;
import mapeditor.mapapi.MapAttributes;
import mapeditor.mapapi.MapLayout;
import mapeditor.themesapi.MapObject;
import mapeditor.themesapi.MapObjectFactory;
import mapeditor.themesapi.ThemesManager;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

public class MapLoaderSAXHandler extends DefaultHandler {

	MapApi mapApi;
	ThemesManager mapThemesList;
	MapObjectFactory mapObjectFactory;
	Hashtable<String, String> segmentsCode;
	int activeLayerIndex;

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
			startMapXmlElement(attrs);
		} else if (qName.equals(MapFileDefinitions.PROPERTIES_ELEMENT)) {
			startPropertiesElement(attrs);
		} else if (qName.equals(MapFileDefinitions.CODE_ELEMENT)) {
			startCodeElement(attrs);
		} else if (qName.equals(MapFileDefinitions.LAYER_ELEMENT)) {
			startLayerElement(attrs);
		} else if (qName.equals(MapFileDefinitions.ROW_ELEMENT)) {
			startRowElement(attrs);
		}

	}

	private void startMapXmlElement(Attributes attrs) {
		String name = attrs.getValue(MapFileDefinitions.MAP_NAME_ATTRIBUTE);
		System.out.println("MapName: " + name);
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
		System.out.println("Index: " + index);
		activeLayerIndex = Integer.parseInt(index);
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
