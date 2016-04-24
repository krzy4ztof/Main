package mapeditor.themesapi;

import java.util.logging.Level;
import java.util.logging.Logger;

import mapeditor.logger.MapLogger;

public class TextProperty extends MapObjectProperty {

	private static final Logger logger = Logger.getLogger(TextProperty.class
			.getName());

	private String value;

	public TextProperty(String name, String value) {
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
		return Type.Text;
	}

	@Override
	public String getValueAsString() {
		return value;
	}

}
