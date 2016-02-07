package mapeditor.themesapi;

import java.util.LinkedList;
import java.util.List;

public class CustomMapObject extends MapObject {

	private LinkedList<MapObjectProperty> mapObjectProperties = null;

	public CustomMapObject(String objectName) {
		super(objectName);
		mapObjectProperties = new LinkedList<MapObjectProperty>();
	}

	public void addProperty(MapObjectProperty mapObjectProperty) {
		mapObjectProperties.add(mapObjectProperty);
	}

	public List<MapObjectProperty> getMapObjectProperties() {
		return mapObjectProperties;
	}

	@Override
	public void describeYourself() {
		super.describeYourself();
		System.out.println("Properties are: ");
		for (MapObjectProperty property : mapObjectProperties) {
			property.describeYourself();
		}
		System.out.println("End");
	}
}
