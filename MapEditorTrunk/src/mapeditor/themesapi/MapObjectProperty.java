package mapeditor.themesapi;

import java.util.logging.Level;
import java.util.logging.Logger;

import mapeditor.logger.MapLogger;

public abstract class MapObjectProperty implements Cloneable {

	private static final Logger logger = Logger
			.getLogger(MapObjectProperty.class.getName());

	public enum Type {
		Long, String, Text, Enum, Point
	}

	String name;

	public MapObjectProperty(String name) {
		this.name = name;
	}

	@Override
	public MapObjectProperty clone() {
		MapObjectProperty clone = null;

		try {
			clone = (MapObjectProperty) super.clone();
		} catch (CloneNotSupportedException e) {
			logger.log(Level.SEVERE, MapLogger.ERROR, e);
		}

		return clone;
	}

	public String getName() {
		return name;
	}

	public void describeYourself() {
		logger.log(Level.FINE, MapLogger.DESCRIBE_MAP_OBJECT_PROPERTY,
				new String[] { getClass().getSimpleName(), name });
	}

	public abstract Type getType();

	public abstract String getValueAsString();

	public abstract void setValue(String value);

}
