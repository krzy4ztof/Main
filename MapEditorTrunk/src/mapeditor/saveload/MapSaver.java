package mapeditor.saveload;

import java.io.File;
import java.io.FileOutputStream;
import java.io.PrintStream;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.OutputKeys;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import mapeditor.mapapi.LayerAttributes;
import mapeditor.mapapi.MapApi;
import mapeditor.messages.MapMessages;
import mapeditor.themesapi.CustomMapObject;
import mapeditor.themesapi.MapObject;
import mapeditor.themesapi.MapObjectProperty;
import mapeditor.themesapi.ThemeApi;
import mapeditor.themesapi.ThemesManager;

import org.w3c.dom.Document;
import org.w3c.dom.Element;

public class MapSaver {

	private ThemesManager mapThemesList = null;
	private MapMessages messages = null;

	public MapSaver(MapMessages messages, ThemesManager mapThemesListParameter) {
		this.messages = messages;
		mapThemesList = mapThemesListParameter;
	}

	public String verifyMapFileName(String filename) {
		int length = filename.length();

		if (length < 4) {
			if (filename.charAt(length - 1) == '.') {
				return filename + "xml";
			} else {
				return filename + ".xml";
			}
		} else {
			if (filename.substring(length - 4, length).equals(".xml")) {
				return filename;
			} else if (filename.charAt(length - 1) == '.') {
				return filename + "xml";
			} else {
				return filename + ".xml";
			}
		}
	}

	public boolean saveMapToFile(MapApi mapApi, File file) throws Exception {
		String name = verifyMapFileName(file.getName());
		File fileXml = new File(file.getParentFile() + File.separator + name);
		Document document = buildDomFromMap(mapApi);
		mapApi.setFile(fileXml);

		FileOutputStream fileInputStream = null;
		TransformerFactory factory = TransformerFactory.newInstance();
		try {
			Transformer transformer = factory.newTransformer();
			transformer.setOutputProperty(OutputKeys.INDENT, "yes");
			DOMSource source = new DOMSource(document);
			fileInputStream = new FileOutputStream(fileXml);
			PrintStream printStream = new PrintStream(fileInputStream);
			StreamResult result = new StreamResult(printStream);
			transformer.transform(source, result);
		} finally {
			if (fileInputStream != null) {
				fileInputStream.close();
			}
		}
		return true;
	}

	private Element createLayerTag(MapApi mapApi, Document document,
			LayerAttributes layerAttributes) {
		Element layerElement = document
				.createElement(MapFileDefinitions.LAYER_ELEMENT);
		layerElement.setAttribute(MapFileDefinitions.INDEX_ATTRIBUTE,
				layerAttributes.getIndex().toString());

		Element rowsElement = createRowsTag(mapApi, document, layerAttributes);
		layerElement.appendChild(rowsElement);

		Element customObjectsElement = createCustomObjectsTag(mapApi, document,
				layerAttributes);
		layerElement.appendChild(customObjectsElement);

		return layerElement;
	}

	private Element createCustomObjectsTag(MapApi mapApi, Document document,
			LayerAttributes layerAttributes) {
		Element customObjectsElement = document
				.createElement(MapFileDefinitions.CUSTOM_OBJECTS_ELEMENT);

		for (int row = 0; row < mapApi.getRowsSize(); row++) {
			for (int col = 0; col < mapApi.getColumnsSize(); col++) {

				CustomMapObject customMapObject = mapApi.getSegment(row, col)
						.getCustomMapObject(layerAttributes.getIndex());

				if (customMapObject != null) {
					Element customObjectElement = createCustomObjectTag(
							customMapObject, row, col, mapApi, document,
							layerAttributes);
					customObjectsElement.appendChild(customObjectElement);
				}

			}
		}

		return customObjectsElement;
	}

	private Element createCustomObjectTag(CustomMapObject customMapObject,
			int row, int col, MapApi mapApi, Document document,
			LayerAttributes layerAttributes) {
		Element customObjectElement = document
				.createElement(MapFileDefinitions.CUSTOM_OBJECT_ELEMENT);

		customObjectElement.setAttribute(MapFileDefinitions.ID_ATTRIBUTE,
				customMapObject.getObjectIdString());

		customObjectElement.setAttribute(MapFileDefinitions.ROW_ATTRIBUTE,
				Integer.toString(row));

		customObjectElement.setAttribute(MapFileDefinitions.COL_ATTRIBUTE,
				Integer.toString(col));

		for (MapObjectProperty property : customMapObject
				.getMapObjectProperties()) {
			Element objectPropertyElement = createObjectPropertyTag(property,
					document);
			customObjectElement.appendChild(objectPropertyElement);
		}

		return customObjectElement;
	}

	private Element createObjectPropertyTag(MapObjectProperty property,
			Document document) {
		Element objectPropertyElement = document
				.createElement(MapFileDefinitions.OBJECT_PROPERTY_ELEMENT);

		objectPropertyElement.setAttribute(
				MapFileDefinitions.PROPERTY_NAME_ATTRIBUTE, property.getName());
		objectPropertyElement.setAttribute(
				MapFileDefinitions.PROPERTY_TYPE_ATTRIBUTE, property.getType()
						.toString());
		objectPropertyElement.setAttribute(
				MapFileDefinitions.PROPERTY_VALUE_ATTRIBUTE,
				property.getValueAsString());

		return objectPropertyElement;
	}

	private Element createRowsTag(MapApi mapApi, Document document,
			LayerAttributes layerAttributes) {
		Element rowsElement = document
				.createElement(MapFileDefinitions.ROWS_ELEMENT);

		for (int row = 0; row < mapApi.getRowsSize(); row++) {
			Element rowElement = createRowTag(row, mapApi, document,
					layerAttributes);
			rowsElement.appendChild(rowElement);
		}

		return rowsElement;
	}

	private Element createRowTag(int row, MapApi mapApi, Document document,
			LayerAttributes layerAttributes) {

		Element rowElement = document
				.createElement(MapFileDefinitions.ROW_ELEMENT);
		rowElement.setAttribute(MapFileDefinitions.NUMBER_ATTRIBUTE,
				Integer.toString(row));

		String segments = "";
		MapObject mapObject = null;

		for (int col = 0; col < mapApi.getColumnsSize(); col++) {
			mapObject = mapApi.getSegment(row, col).getMapObject(
					layerAttributes.getIndex());
			String segmentId = null;
			if (mapObject != null) {
				segmentId = mapObject.getObjectIdString();
			} else {
				segmentId = MapObject.DEFAULT_OBJECT_ID;
			}

			segments = segments + segmentId + ';';
		}
		rowElement
				.setAttribute(MapFileDefinitions.SEGMENTS_ATTRIBUTE, segments);

		return rowElement;
	}

	private Element createMatrixTag(MapApi mapApi, Document document) {
		Element matrixElement = document
				.createElement(MapFileDefinitions.MATRIX_ELEMENT);
		for (LayerAttributes layerAttributes : mapApi.getLayersAttributes()) {
			Element layerElement = createLayerTag(mapApi, document,
					layerAttributes);
			matrixElement.appendChild(layerElement);
		}

		return matrixElement;
	}

	private Element createSegmentsCodesTag(MapApi mapApi, Document document) {
		Element segmCodeElement = null;
		segmCodeElement = document
				.createElement(MapFileDefinitions.SEGMENTS_CODE_ELEMENT);
		String objectIdString = null;

		for (ThemeApi themeApi : mapThemesList.getThemesApis()) {
			for (MapObject mapObject : themeApi.getAllMapObjects()) {
				objectIdString = mapObject.getObjectIdString();

				if (!objectIdString.contentEquals(MapObject.DEFAULT_OBJECT_ID)) {
					Element codeElem = document
							.createElement(MapFileDefinitions.CODE_ELEMENT);
					codeElem.setAttribute(MapFileDefinitions.ID_ATTRIBUTE,
							objectIdString);
					codeElem.setAttribute(MapFileDefinitions.IMAGE_ATTRIBUTE,
							mapObject.getObjectName());
					segmCodeElement.appendChild(codeElem);
				}
			}
		}

		return segmCodeElement;
	}

	private Element createGeneralPametersTag(MapApi mapApi, Document document) {

		Element genParamElement = document
				.createElement(MapFileDefinitions.GENERAL_PARAMETERS_ELEMENT);
		Element propElem = document
				.createElement(MapFileDefinitions.PROPERTIES_ELEMENT);
		String rows = Integer.toString(mapApi.getRowsSize());
		propElem.setAttribute(MapFileDefinitions.ROWS_ATTRIBUTE, rows);
		String cols = Integer.toString(mapApi.getColumnsSize());
		propElem.setAttribute(MapFileDefinitions.COLUMNS_ATTRIBUTE, cols);
		String layout = mapApi.getMapLayout().toString();
		propElem.setAttribute(MapFileDefinitions.LAYOUT_ATTRIBUTE, layout);

		String layers = Integer.toString(mapApi.getLayerAttributesSize());
		propElem.setAttribute(MapFileDefinitions.LAYERS_ATTRIBUTE, layers);

		genParamElement.appendChild(propElem);
		propElem = createSegmentsCodesTag(mapApi, document);
		genParamElement.appendChild(propElem);

		return genParamElement;
	}

	private Document buildDomFromMap(MapApi mapApi)
			throws ParserConfigurationException {
		DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
		Document document = null;
		DocumentBuilder builder = factory.newDocumentBuilder();
		document = builder.newDocument();
		Element root = document
				.createElement(MapFileDefinitions.MAP_XML_ELEMENT);
		root.setAttribute(MapFileDefinitions.MAP_NAME_ATTRIBUTE,
				messages.getString(MapMessages.MAPSAVER_MAP_NAME));
		document.appendChild(root);

		root.appendChild(createGeneralPametersTag(mapApi, document));
		root.appendChild(createMatrixTag(mapApi, document));
		return document;
	}
}
