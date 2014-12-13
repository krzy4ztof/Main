package mapeditor.saveload;

import java.io.File;
import java.io.FileOutputStream;
import java.io.PrintStream;
import java.util.Iterator;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.OutputKeys;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import mapeditor.mapapi.MapApi;
import mapeditor.mapapi.MapObject;
import mapeditor.messages.MapMessages;
import mapeditor.themesapi.MapObjectsTheme;
import mapeditor.themesapi.MapThemesList;

import org.w3c.dom.Document;
import org.w3c.dom.Element;

public class MapSaver {

	private MapThemesList mapThemesList = null;
	private MapMessages messages = null;

	public MapSaver(MapMessages messages, MapThemesList mapThemesListParameter) {
		this.messages = messages;
		mapThemesList = mapThemesListParameter;
	}

	public String VerifyMapFileName(String pFilename) {
		System.out.println("ORIG: " + pFilename);
		int length = pFilename.length();

		if (length < 4) {
			if (pFilename.charAt(length - 1) == '.') {
				return pFilename + "xml";
			} else {
				return pFilename + ".xml";
			}
		} else {
			if (pFilename.substring(length - 4, length).equals(".xml")) {
				return pFilename;
			} else if (pFilename.charAt(length - 1) == '.') {
				return pFilename + "xml";
			} else {
				return pFilename + ".xml";
			}
		}
	}

	public boolean SaveMapToFile(MapApi rMapApi, File rFile) throws Exception {
		String CorrectName = VerifyMapFileName(rFile.getName());
		File rFileXml = new File(rFile.getParentFile() + File.separator
				+ CorrectName);
		Document rDocument = this.BuildDomFromMap(rMapApi);
		rMapApi.setFile(rFileXml);

		FileOutputStream FOP = null;
		TransformerFactory tFactory = TransformerFactory.newInstance();
		try {
			Transformer rTransformer = tFactory.newTransformer();
			rTransformer.setOutputProperty(OutputKeys.INDENT, "yes");
			DOMSource source = new DOMSource(rDocument);
			FOP = new FileOutputStream(rFileXml);
			PrintStream PS = new PrintStream(FOP);
			StreamResult result = new StreamResult(PS);
			rTransformer.transform(source, result);
		} finally {
			if (FOP != null) {
				FOP.close();
			}
		}
		return true;
	}

	private Element CreateMatrixTag(MapApi rMapApi, Document rDocument) {
		Element MatrixElement = null;
		Element BufElem = null;
		MatrixElement = rDocument
				.createElement(MapFileDefinitions.MATRIX_ELEMENT);
		String SegmentId = null;
		String Segments = "";
		MapObject mapObject = null;

		for (Integer i_row = 0; i_row < rMapApi.getRowsSize(); i_row++) {
			Segments = "";
			BufElem = rDocument.createElement(MapFileDefinitions.ROW_ELEMENT);
			BufElem.setAttribute(MapFileDefinitions.NUMBER_ATTRIBUTE,
					i_row.toString());
			for (int i_col = 0; i_col < rMapApi.getColumnsSize(); i_col++) {

				mapObject = rMapApi.getSegment(i_row, i_col).getMapObject();
				if (mapObject != null) {
					SegmentId = mapObject.getObjectIdString();
				} else {
					SegmentId = MapObject.defaultObjectIdString;
				}

				Segments = Segments + SegmentId + ';';
			}
			System.out.println(Segments);
			BufElem.setAttribute(MapFileDefinitions.SEGMENTS_ATTRIBUTE,
					Segments);
			MatrixElement.appendChild(BufElem);
		}
		return MatrixElement;
	}

	private Element CreateSegmentsCodesTag(MapApi rMapApi, Document rDocument) {
		Element segmCodeElement = null;
		Element bufElem = null;
		segmCodeElement = rDocument
				.createElement(MapFileDefinitions.SEGMENTS_CODE_ELEMENT);
		String objectIdString = null;

		MapObjectsTheme mapObjectsTheme = null;
		MapObject mapObject = null;

		for (Iterator<MapObjectsTheme> itTheme = mapThemesList
				.getThemesIterator(); itTheme.hasNext();) {
			mapObjectsTheme = itTheme.next();
			for (Iterator<MapObject> itObject = mapObjectsTheme
					.getObjectsIterator(); itObject.hasNext();) {
				mapObject = itObject.next();
				objectIdString = mapObject.getObjectIdString();

				if (!objectIdString
						.contentEquals(MapObject.defaultObjectIdString)) {
					bufElem = rDocument
							.createElement(MapFileDefinitions.CODE_ELEMENT);
					bufElem.setAttribute(MapFileDefinitions.ID_ATTRIBUTE,
							objectIdString);
					bufElem.setAttribute(MapFileDefinitions.IMAGE_ATTRIBUTE,
							mapObject.getObjectName());
					segmCodeElement.appendChild(bufElem);
				}
			}
		}

		return segmCodeElement;
	}

	private Element CreateGeneralPametersTag(MapApi rMapApi, Document rDocument) {
		Element GenParamElement = null;
		Element BufElem = null;

		GenParamElement = rDocument
				.createElement(MapFileDefinitions.GENERAL_PARAMETERS_ELEMENT);
		BufElem = rDocument.createElement(MapFileDefinitions.SIZE_ELEMENT);
		String rows_no = ((Integer) rMapApi.getRowsSize()).toString();
		BufElem.setAttribute(MapFileDefinitions.ROWS_ATTRIBUTE, rows_no);
		String cols_no = ((Integer) rMapApi.getColumnsSize()).toString();
		BufElem.setAttribute(MapFileDefinitions.COLUMNS_ATTRIBUTE, cols_no);
		GenParamElement.appendChild(BufElem);
		BufElem = this.CreateSegmentsCodesTag(rMapApi, rDocument);
		GenParamElement.appendChild(BufElem);

		return GenParamElement;
	}

	private Document BuildDomFromMap(MapApi rMapApi)
			throws ParserConfigurationException {
		DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
		Document rDocument = null;
		DocumentBuilder builder = factory.newDocumentBuilder();
		rDocument = builder.newDocument();
		// Create from whole cloth
		Element root = rDocument
				.createElement(MapFileDefinitions.MAP_XML_ELEMENT);
		root.setAttribute(MapFileDefinitions.MAP_NAME_ATTRIBUTE,
				messages.getMapName());
		rDocument.appendChild(root);

		root.appendChild(this.CreateGeneralPametersTag(rMapApi, rDocument));
		root.appendChild(this.CreateMatrixTag(rMapApi, rDocument));
		return rDocument;
	}
}
