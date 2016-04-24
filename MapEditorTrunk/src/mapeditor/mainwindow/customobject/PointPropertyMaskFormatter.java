package mapeditor.mainwindow.customobject;

import java.awt.Point;
import java.text.ParseException;
import java.util.logging.Level;
import java.util.logging.Logger;

import javax.swing.text.MaskFormatter;

import mapeditor.logger.MapLogger;
import mapeditor.mapapi.MapApi;
import mapeditor.mapapi.Point3D;

public class PointPropertyMaskFormatter extends MaskFormatter {

	private static final Logger logger = Logger
			.getLogger(PointPropertyMaskFormatter.class.getName());

	private static final long serialVersionUID = 1L;

	private MapApi mapApi;

	public PointPropertyMaskFormatter(MapApi mapApi) {
		this.mapApi = mapApi;

		int x = mapApi.getColumnsSize();
		int y = mapApi.getRowsSize();
		int z = mapApi.getLayerAttributesSize();

		String mask = "(" + maskFor(x) + "," + maskFor(y) + "," + maskFor(z)
				+ ")";

		try {
			this.setMask(mask);
		} catch (ParseException e) {
			logger.log(Level.SEVERE, MapLogger.ERROR, e);
		}
	}

	private String maskFor(int number) {
		if (number > 999) {
			return "####";
		} else if (number > 99) {
			return "###";
		} else if (number > 9) {
			return "##";
		} else {
			return "#";
		}
	}

	private String toString(Integer number, int max) {

		int numberLength = maskFor(number).length();
		int maskLength = maskFor(max).length();

		int marigin = maskLength - numberLength;

		StringBuffer stringBuffer = new StringBuffer("");
		for (int i = 0; i < marigin; i++) {
			stringBuffer.append(" ");
		}

		stringBuffer.append(number.toString());
		return stringBuffer.toString();

	}

	@Override
	public Object stringToValue(String value) throws ParseException {
		Point3D point = new Point3D(value);
		return point;
	}

	@Override
	public String valueToString(Object value) throws ParseException {
		String string;
		if (value != null && value instanceof Point3D) {
			Point3D point = (Point3D) value;

			string = "(" + toString(point.x, mapApi.getColumnsSize()) + ","
					+ toString(point.y, mapApi.getRowsSize()) + ","
					+ toString(point.z, mapApi.getLayerAttributesSize()) + ")";
		} else {
			string = "(" + toString(0, mapApi.getColumnsSize()) + ","
					+ toString(0, mapApi.getRowsSize()) + ","
					+ toString(0, mapApi.getLayerAttributesSize()) + ")";
		}
		return string;
	}

	public String valueToString_33(Object value) throws ParseException {
		String string;
		if (value != null && value instanceof Point) {
			Point point = (Point) value;
			string = "(" + point.x + "  ," + point.y + "  ," + "   )";
		} else {
			string = "(   ,   ,   )";
		}
		return string;
	}

}