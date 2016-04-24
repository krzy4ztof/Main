package mapeditor.themesapi;

import java.util.logging.Level;
import java.util.logging.Logger;

import mapeditor.logger.MapLogger;

public class LongProperty extends MapObjectProperty {

	private static final Logger logger = Logger.getLogger(LongProperty.class
			.getName());

	private Long value;

	public LongProperty(String name, String value) {
		super(name);
		this.value = Long.valueOf(value);
	}

	@Override
	public void describeYourself() {
		logger.log(
				Level.FINE,
				MapLogger.DESCRIBE_DEFAULT_MAP_OBJECT_PROPERTY,
				new String[] { getClass().getSimpleName(), name,
						value.toString() });
	}

	public void setValue(long value) {
		this.value = value;
	}

	@Override
	public void setValue(String value) {
		this.value = Long.parseLong(value);
	}

	public Long getValue() {
		return value;
	}

	@Override
	public Type getType() {
		return Type.Long;
	}

	@Override
	public String getValueAsString() {
		return value.toString();
	}

}
