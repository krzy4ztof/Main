package mapeditor.themesapi;

public abstract class MapObjectProperty implements Cloneable {

	enum Type {
		Long, String, Text, Enum, Point
	}

	String name;

	public MapObjectProperty(String name) {
		this.name = name;
	}

	@Override
	public MapObjectProperty clone() {
		MapObjectProperty clone = null;

		try {
			clone = (MapObjectProperty) super.clone();
		} catch (CloneNotSupportedException e) {
			e.printStackTrace();
		}

		return clone;
	}

	public String getName() {
		return name;
	}

	public void describeYourself() {
		System.out.println("Property name: " + name);
	}
}
