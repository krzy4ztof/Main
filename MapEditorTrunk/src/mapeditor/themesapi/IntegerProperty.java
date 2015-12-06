package mapeditor.themesapi;

public class IntegerProperty extends MapObjectProperty {

	int defaultValue;

	public IntegerProperty(String name, String value) {
		super(name);
		defaultValue = Integer.valueOf(value);
	}

	@Override
	public void describeYourself() {
		System.out.println("IntegerProperty name: " + name + "; default: "
				+ defaultValue);
	}
}
