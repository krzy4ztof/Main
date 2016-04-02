package mapeditor.themesapi;

public class StringProperty extends MapObjectProperty {

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
		System.out
				.println("LongProperty name: " + name + "; default: " + value);
	}

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
