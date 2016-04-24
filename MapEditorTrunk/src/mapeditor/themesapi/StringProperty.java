package mapeditor.themesapi;

import java.util.logging.Level;
import java.util.logging.Logger;

import mapeditor.logger.MapLogger;

public class StringProperty extends MapObjectProperty {

	private static final Logger logger = Logger.getLogger(StringProperty.class
			.getName());

	private String value;

	public StringProperty(String name, String value) {
		super(name);
		if (value != null) {
			this.value = value;
		} else {
			this.value = "";
		}

	}

	@Override
	public void describeYourself() {
		logger.log(Level.FINE, MapLogger.DESCRIBE_DEFAULT_MAP_OBJECT_PROPERTY,
				new String[] { getClass().getSimpleName(), name, value });
	}

	@Override
	public void setValue(String value) {
		this.value = value;
	}

	public String getValue() {
		return value;
	}

	@Override
	public Type getType() {
		return Type.String;
	}

	@Override
	public String getValueAsString() {
		return value;
	}
}
