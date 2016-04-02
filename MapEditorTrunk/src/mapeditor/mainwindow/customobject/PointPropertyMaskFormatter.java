package mapeditor.mainwindow.customobject;

import java.awt.Point;
import java.text.ParseException;

import javax.swing.text.MaskFormatter;

import mapeditor.mapapi.MapApi;
import mapeditor.mapapi.Point3D;

public class PointPropertyMaskFormatter extends MaskFormatter {

	/**
	 * 
	 */
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
			e.printStackTrace();
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

		System.out.println("Str-to-val In: " + value);
		Point3D point = new Point3D(value);

		System.out.println("Str-to-val Out: " + point + " X: " + point.x
				+ " Y: " + point.y + " Z: " + point.z);

		return point;
	}

	@Override
	public String valueToString(Object value) throws ParseException {

		System.out.println("Val-to-str In:  " + value);

		// String string = super.valueToString(value);

		String string;
		if (value != null && value instanceof Point3D) {
			Point3D point = (Point3D) value;

			string = "(" + toString(point.x, mapApi.getColumnsSize()) + ","
					+ toString(point.y, mapApi.getRowsSize()) + ","
					+ toString(point.z, mapApi.getLayerAttributesSize()) + ")";

			System.out.println("TOSTR: " + string);

			System.out.println("TOSTR: " + point.toString());
		} else {
			string = "(" + toString(0, mapApi.getColumnsSize()) + ","
					+ toString(0, mapApi.getRowsSize()) + ","
					+ toString(0, mapApi.getLayerAttributesSize()) + ")";
		}

		System.out.println("Val-to-str Out: " + string);

		return string;
	}

	public String valueToString_33(Object value) throws ParseException {

		System.out.println("Val-to-str In:  " + value);

		// String string = super.valueToString(value);

		String string;
		if (value != null && value instanceof Point) {
			Point point = (Point) value;
			string = "(" + point.x + "  ," + point.y + "  ," + "   )";

			// string = "(" + point.x + "," + point.y + "," + ")";

		} else {
			string = "(   ,   ,   )";
		}

		System.out.println("Val-to-str Out: " + string);

		return string;
	}

}