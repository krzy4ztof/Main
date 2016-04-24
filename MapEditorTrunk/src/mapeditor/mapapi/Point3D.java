package mapeditor.mapapi;

public class Point3D {

	public int x;
	public int y;
	public int z;

	public Point3D() {
		this(0, 0, 0);
	}

	public Point3D(int x, int y, int z) {
		this.x = x;
		this.y = y;
		this.z = z;
	}

	public Point3D(String value) {
		this();
		setCoordinates(value);
	}

	public void setCoordinates(String value) {
		value = value.replaceAll(" ", "");

		if (value.matches("\\(\\d+,\\d+,\\d+\\)")) {
			value = value.substring(1, value.length() - 1);

			String[] coord = value.split(",");

			if (coord.length > 2) {
				try {
					x = Integer.parseInt(coord[0]);
				} catch (NumberFormatException e) {
					x = 0;
				}

				try {
					y = Integer.parseInt(coord[1]);
				} catch (NumberFormatException e) {
					y = 0;
				}

				try {
					z = Integer.parseInt(coord[2]);
				} catch (NumberFormatException e) {
					z = 0;
				}

			}
		}
	}

	public String asString() {
		String string = "(" + x + "," + y + "," + z + ")";
		return string;
	}
}
