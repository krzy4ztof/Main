package mapeditor.themesapi;

import java.util.logging.Level;
import java.util.logging.Logger;

import mapeditor.logger.MapLogger;
import mapeditor.mapapi.Point3D;

public class PointProperty extends MapObjectProperty {

	private static final Logger logger = Logger.getLogger(PointProperty.class
			.getName());

	private Point3D value;

	public PointProperty(String name, String value) {
		super(name);

		setValue(value);
	}

	@Override
	public void describeYourself() {
		logger.log(
				Level.FINE,
				MapLogger.DESCRIBE_DEFAULT_MAP_OBJECT_PROPERTY,
				new String[] { getClass().getSimpleName(), name,
						value.asString() });
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
