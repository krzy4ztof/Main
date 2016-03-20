package mapeditor.themesapi;

public class TextProperty extends MapObjectProperty {

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
		System.out
				.println("TextProperty name: " + name + "; default: " + value);
	}

	public void setValue(String value) {
		this.value = value;
	}

	public String getValue() {
		return value;
	}

}
