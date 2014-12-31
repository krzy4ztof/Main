package mapeditor.saveload;

import java.io.File;
import java.io.FileInputStream;
import java.util.Hashtable;

import javax.xml.namespace.QName;
import javax.xml.stream.XMLEventReader;
import javax.xml.stream.XMLInputFactory;
import javax.xml.stream.events.Attribute;
import javax.xml.stream.events.EndElement;
import javax.xml.stream.events.StartElement;
import javax.xml.stream.events.XMLEvent;

import mapeditor.mapapi.MapApi;
import mapeditor.mapapi.MapAttributes;
import mapeditor.mapapi.MapLayout;
import mapeditor.themesapi.MapObject;
import mapeditor.themesapi.MapObjectFactory;
import mapeditor.themesapi.ThemesManager;

/**
 *
 * @author krzysztof
 */
public class MapLoader {

	private enum ProcessingElement {

		pre, in, post
	}

	private class InvalidXML extends Exception {

		/**
		 * 
		 */
		private static final long serialVersionUID = 1L;
	}

	private ProcessingElement processingMapXML = ProcessingElement.pre;
	private ProcessingElement processingGeneralParameters = ProcessingElement.pre;
	private ProcessingElement processingSegmentsCode = ProcessingElement.pre;
	private ProcessingElement processingMatrix = ProcessingElement.pre;

	/**
	 * Reinitializes itself
	 */
	private void reinitalize() {

		processingMapXML = ProcessingElement.pre;
		processingGeneralParameters = ProcessingElement.pre;
		processingSegmentsCode = ProcessingElement.pre;
		processingMatrix = ProcessingElement.pre;

	}

	/**
	 * 
	 * @param rFile
	 * @param mapThemesList
	 * @return
	 * @throws Exception
	 */
	public MapApi loadMapFromFile(MapApi mapApi, File rFile,
			ThemesManager mapThemesList, MapObjectFactory mapObjectFactory)
			throws Exception {

		reinitalize();
		XMLInputFactory factory = XMLInputFactory.newInstance();

		FileInputStream fileInputStream = null;

		try {
			fileInputStream = new FileInputStream(rFile);
			XMLEventReader reader = factory
					.createXMLEventReader(fileInputStream);

			Hashtable<String, String> segmentsCode = new Hashtable<String, String>();

			while (reader.hasNext()) {
				XMLEvent event = reader.nextEvent();

				processEvent(event, mapApi, segmentsCode, mapThemesList,
						mapObjectFactory);
			}
			mapApi.setFile(rFile);

		} finally {
			if (fileInputStream != null) {
				fileInputStream.close();
			}
		}
		return mapApi;
	}

	/**
	 * 
	 * @param xmlEvent
	 * @param mapApi
	 * @param segmentsCode
	 * @param mapThemesList
	 * @throws mapEditor.MapLoader.InvalidXML
	 */
	private void processEvent(XMLEvent xmlEvent, MapApi mapApi,
			Hashtable<String, String> segmentsCode,
			ThemesManager mapThemesList, MapObjectFactory mapObjectFactory)
			throws InvalidXML {

		if (xmlEvent.isStartElement()) {
			StartElement startElement = xmlEvent.asStartElement();
			String elementName = startElement.getName().toString();

			if (elementName.equals(MapFileDefinitions.MAP_XML_ELEMENT)) {
				startMapXmlElement();
			} else if (elementName
					.equals(MapFileDefinitions.GENERAL_PARAMETERS_ELEMENT)) {
				startGeneralParametersElement();
			} else if (elementName
					.equals(MapFileDefinitions.PROPERTIES_ELEMENT)) {
				readSizeElement(startElement, mapApi, mapObjectFactory);
			} else if (elementName
					.equals(MapFileDefinitions.SEGMENTS_CODE_ELEMENT)) {
				startSegmentsCodeElement();
			} else if (elementName.equals(MapFileDefinitions.CODE_ELEMENT)) {
				readCodeElement(startElement, segmentsCode);
			} else if (elementName.equals(MapFileDefinitions.MATRIX_ELEMENT)) {
				startMatrixElement();
			} else if (elementName.equals(MapFileDefinitions.ROW_ELEMENT)) {
				readRowElement(startElement, mapApi, segmentsCode,
						mapThemesList);
			}
		} else if (xmlEvent.isEndElement()) {
			EndElement endElement = xmlEvent.asEndElement();
			String elementName = endElement.getName().toString();

			if (elementName.equals(MapFileDefinitions.MAP_XML_ELEMENT)) {
				endMapXmlElement();
			} else if (elementName
					.equals(MapFileDefinitions.GENERAL_PARAMETERS_ELEMENT)) {
				endGeneralParametersElement();
			} else if (elementName
					.equals(MapFileDefinitions.PROPERTIES_ELEMENT)) {
				// DO NOTHING
			} else if (elementName
					.equals(MapFileDefinitions.SEGMENTS_CODE_ELEMENT)) {
				endSegmentsCodeElement();
			} else if (elementName.equals(MapFileDefinitions.CODE_ELEMENT)) {
				// DO NOTHING
			} else if (elementName.equals(MapFileDefinitions.MATRIX_ELEMENT)) {
				endMatrixElement();
			} else if (elementName.equals(MapFileDefinitions.ROW_ELEMENT)) {
			}

		}
	}

	/**
	 *
	 * @throws mapEditor.MapLoader.InvalidXML
	 */
	private void startMapXmlElement() throws InvalidXML {
		if (processingMapXML != ProcessingElement.pre) {
			throw new InvalidXML();
		}
		this.processingMapXML = ProcessingElement.in;
	}

	/**
	 *
	 * @throws mapEditor.MapLoader.InvalidXML
	 */
	private void endMapXmlElement() throws InvalidXML {
		if (processingMapXML != ProcessingElement.in) {
			throw new InvalidXML();
		}
		processingMapXML = ProcessingElement.post;
	}

	/**
	 *
	 * @throws mapEditor.MapLoader.InvalidXML
	 */
	private void startGeneralParametersElement() throws InvalidXML {
		if (processingGeneralParameters != ProcessingElement.pre) {
			throw new InvalidXML();
		}

		if (this.processingMapXML != ProcessingElement.in) {
			throw new InvalidXML();
		}

		processingGeneralParameters = ProcessingElement.in;
	}

	/**
	 *
	 * @throws mapEditor.MapLoader.InvalidXML
	 */
	private void endGeneralParametersElement() throws InvalidXML {
		if (processingGeneralParameters != ProcessingElement.in) {
			throw new InvalidXML();
		}

		if (processingMapXML != ProcessingElement.in) {
			throw new InvalidXML();
		}

		processingGeneralParameters = ProcessingElement.post;
	}

	/**
	 *
	 * @param startElement
	 * @param mapApi
	 * @throws mapEditor.MapLoader.InvalidXML
	 */
	private void readSizeElement(StartElement startElement, MapApi mapApi,
			MapObjectFactory mapObjectFactory) throws InvalidXML {

		if (processingGeneralParameters != ProcessingElement.in) {
			throw new InvalidXML();
		}

		if (processingMapXML != ProcessingElement.in) {
			throw new InvalidXML();
		}

		Attribute atrCols = startElement.getAttributeByName(new QName(
				MapFileDefinitions.COLUMNS_ATTRIBUTE));

		if (atrCols == null) {
			throw new InvalidXML();
		}

		Attribute atrRows = startElement.getAttributeByName(new QName(
				MapFileDefinitions.ROWS_ATTRIBUTE));

		if (atrRows == null) {
			throw new InvalidXML();
		}

		Attribute layout = startElement.getAttributeByName(new QName(
				MapFileDefinitions.LAYOUT_ATTRIBUTE));

		if (layout == null) {
			throw new InvalidXML();
		}

		int cols = Integer.decode(atrCols.getValue());
		int rows = Integer.decode(atrRows.getValue());

		MapLayout mapLayout = MapLayout.SQR;

		if (layout.getValue().equals(MapLayout.HEX.toString())) {
			mapLayout = MapLayout.HEX;
		}

		MapAttributes mapAttributes = new MapAttributes(rows, cols, mapLayout);

		mapApi.resetMap(mapAttributes, mapObjectFactory.getBlankMapObject());
	}

	/**
	 *
	 * @throws mapEditor.MapLoader.InvalidXML
	 */
	private void startSegmentsCodeElement() throws InvalidXML {

		if (processingSegmentsCode != ProcessingElement.pre) {
			throw new InvalidXML();
		}

		if (processingGeneralParameters != ProcessingElement.in) {
			throw new InvalidXML();
		}

		if (processingMapXML != ProcessingElement.in) {
			throw new InvalidXML();
		}

		processingSegmentsCode = ProcessingElement.in;

	}

	/**
	 *
	 * @throws mapEditor.MapLoader.InvalidXML
	 */
	private void endSegmentsCodeElement() throws InvalidXML {
		if (processingSegmentsCode != ProcessingElement.in) {
			throw new InvalidXML();
		}

		if (processingGeneralParameters != ProcessingElement.in) {
			throw new InvalidXML();
		}

		if (processingMapXML != ProcessingElement.in) {
			throw new InvalidXML();
		}

		processingSegmentsCode = ProcessingElement.post;
	}

	/**
	 *
	 * @param startElement
	 * @param segmentsCode
	 * @throws mapEditor.MapLoader.InvalidXML
	 */
	private void readCodeElement(StartElement startElement,
			Hashtable<String, String> segmentsCode) throws InvalidXML {
		if (processingSegmentsCode != ProcessingElement.in) {
			throw new InvalidXML();
		}

		if (processingGeneralParameters != ProcessingElement.in) {
			throw new InvalidXML();
		}

		if (processingMapXML != ProcessingElement.in) {
			throw new InvalidXML();
		}

		Attribute atrId = startElement.getAttributeByName(new QName(
				MapFileDefinitions.ID_ATTRIBUTE));

		if (atrId == null) {
			throw new InvalidXML();
		}

		Attribute atrImage = startElement.getAttributeByName(new QName(
				MapFileDefinitions.IMAGE_ATTRIBUTE));

		if (atrImage == null) {
			throw new InvalidXML();
		}

		String id = atrId.getValue();
		String image = atrImage.getValue();

		if (segmentsCode.get(id) == null) {
			segmentsCode.put(id, image);
		}
	}

	/**
	 *
	 * @throws mapEditor.MapLoader.InvalidXML
	 */
	private void startMatrixElement() throws InvalidXML {
		if (processingMatrix != ProcessingElement.pre) {
			throw new InvalidXML();
		}

		if (processingMapXML != ProcessingElement.in) {
			throw new InvalidXML();
		}

		processingMatrix = ProcessingElement.in;

	}

	/**
	 *
	 * @throws mapEditor.MapLoader.InvalidXML
	 */
	private void endMatrixElement() throws InvalidXML {
		if (processingMatrix != ProcessingElement.in) {
			throw new InvalidXML();
		}

		if (processingMapXML != ProcessingElement.in) {
			throw new InvalidXML();
		}

		processingMatrix = ProcessingElement.post;

	}

	/**
	 *
	 * @param startElement
	 * @param mapApi
	 * @param segmentsCode
	 * @param mapThemesList
	 * @throws mapEditor.MapLoader.InvalidXML
	 */
	private void readRowElement(StartElement startElement, MapApi mapApi,
			Hashtable<String, String> segmentsCode, ThemesManager mapThemesList)
			throws InvalidXML {
		if (processingMatrix != ProcessingElement.in) {
			throw new InvalidXML();
		}

		if (processingMapXML != ProcessingElement.in) {
			throw new InvalidXML();
		}

		int rowNumber = -1;
		Attribute atr = startElement.getAttributeByName(new QName(
				MapFileDefinitions.NUMBER_ATTRIBUTE));

		if (atr == null) {
			throw new InvalidXML();
		} else {
			rowNumber = new Integer(atr.getValue());
		}

		atr = startElement.getAttributeByName(new QName(
				MapFileDefinitions.SEGMENTS_ATTRIBUTE));

		if (atr == null) {
			throw new InvalidXML();
		} else {

			String[] segments = atr.getValue().split(";");
			int col = 0;
			for (String segment : segments) {
				String name = segmentsCode.get(segment);
				MapObject mapObject = mapThemesList.getMapObjectApi(name);

				mapApi.getSegment(rowNumber, col).setMapObject(mapObject);
				col++;
			}
		}
	}

	/**
	 *
	 * @param eventType
	 * @return
	 */
	public static final String getEventTypeString(int eventType) {
		switch (eventType) {
		case XMLEvent.START_ELEMENT:
			return "START_ELEMENT";

		case XMLEvent.END_ELEMENT:
			return "END_ELEMENT";

		case XMLEvent.PROCESSING_INSTRUCTION:
			return "PROCESSING_INSTRUCTION";

		case XMLEvent.CHARACTERS:
			return "CHARACTERS";

		case XMLEvent.COMMENT:
			return "COMMENT";

		case XMLEvent.START_DOCUMENT:
			return "START_DOCUMENT";

		case XMLEvent.END_DOCUMENT:
			return "END_DOCUMENT";

		case XMLEvent.ENTITY_REFERENCE:
			return "ENTITY_REFERENCE";

		case XMLEvent.ATTRIBUTE:
			return "ATTRIBUTE";

		case XMLEvent.DTD:
			return "DTD";

		case XMLEvent.CDATA:
			return "CDATA";

		case XMLEvent.SPACE:
			return "SPACE";
		}
		return "UNKNOWN_EVENT_TYPE " + "," + eventType;
	}
}
