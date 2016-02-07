package mapeditor.themesapi;

public abstract class MapObjectProperty {

	enum Type {
		Integer, String, Text, Enum, Point
	}

	String name;

	public MapObjectProperty(String name) {
		this.name = name;
	}

	public String getName() {
		return name;
	}

	public void describeYourself() {
		System.out.println("Property name: " + name);
	}
}
