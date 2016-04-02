package mapeditor.themesapi;

import mapeditor.mapapi.Point3D;

public class PointProperty extends MapObjectProperty {

	private Point3D value;

	public PointProperty(String name, String value) {
		super(name);

		// this.value = new Point3D(value);
		setValue(value);
	}

	@Override
	public void describeYourself() {
		System.out.println("PointProperty name: " + name + "; default: "
				+ value);
	}

	public void setValue(Point3D value) {
		this.value = value;
	}

	public Point3D getValue() {
		return value;
	}

	@Override
	public Type getType() {
		return Type.Point;
	}

	@Override
	public String getValueAsString() {
		return value.asString();
	}

	@Override
	public void setValue(String value) {
		this.value = new Point3D(value);
	}

}
