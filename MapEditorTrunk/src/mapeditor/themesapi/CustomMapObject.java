package mapeditor.themesapi;

import java.util.LinkedList;
import java.util.List;

public class CustomMapObject extends MapObject {

	private LinkedList<MapObjectProperty> mapObjectProperties = null;

	private String externalName;

	public CustomMapObject(String objectName, String externalName) {
		super(objectName);
		this.externalName = externalName;
		mapObjectProperties = new LinkedList<MapObjectProperty>();
	}

	@Override
	public CustomMapObject clone() {
		CustomMapObject clone = (CustomMapObject) super.clone();

		clone.mapObjectProperties = new LinkedList<MapObjectProperty>();

		for (MapObjectProperty property : mapObjectProperties) {
			clone.addProperty(property.clone());
		}

		return clone;
	}

	public String getExternalName() {
		return externalName;
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

	public void setProperty(String name, String type, String value) {
		MapObjectProperty mapObjectProperty = getProperty(name, type);

		if (mapObjectProperty != null) {
			mapObjectProperty.setValue(value);
		}

	}

	private MapObjectProperty getProperty(String name, String type) {
		for (MapObjectProperty property : mapObjectProperties) {
			if (property.name.equals(name)) {
				if (property.getType().toString().equals(type)) {
					return property;
				}
			}
		}
		return null;
	}
}
