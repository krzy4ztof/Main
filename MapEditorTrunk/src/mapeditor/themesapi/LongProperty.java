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

	public Long getValue() {
		return value;
	}
}
