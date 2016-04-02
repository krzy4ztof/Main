package mapeditor.themesapi;

public class LongProperty extends MapObjectProperty {

	private Long value;

	public LongProperty(String name, String value) {
		super(name);
		this.value = Long.valueOf(value);
	}

	@Override
	public void describeYourself() {
		System.out
				.println("LongProperty name: " + name + "; default: " + value);
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
