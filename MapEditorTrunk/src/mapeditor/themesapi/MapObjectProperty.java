package mapeditor.themesapi;

public abstract class MapObjectProperty {

	enum Type {
		Integer
	}

	String name;

	public MapObjectProperty(String name) {
		this.name = name;
	}

	public void describeYourself() {
		System.out.println("Property name: " + name);
	}
}
