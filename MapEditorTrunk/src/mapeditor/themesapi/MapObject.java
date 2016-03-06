/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package mapeditor.themesapi;

import javax.swing.ImageIcon;

/**
 *
 * @author krzysztof
 */
public class MapObject implements Cloneable {

	private String objectName;
	private String imageName;
	private ImageIcon imageIcon;
	private int objectId;
	public final static String DEFAULT_OBJECT_ID = "000";

	@Override
	public MapObject clone() {
		MapObject clone = null;

		try {
			clone = (MapObject) super.clone();
		} catch (CloneNotSupportedException e) {
			e.printStackTrace();
		}

		return clone;
	}

	@Override
	public boolean equals(Object object) {
		if (object instanceof MapObject) {
			MapObject mapObject = (MapObject) object;

			if (objectName.equals(mapObject.objectName)
					&& imageName.equals(mapObject.imageName)
					&& objectId == mapObject.objectId) {
				return true;
			}
		}
		return false;
	}

	@Override
	public int hashCode() {
		return objectName.hashCode() + imageName.hashCode() + objectId;
	}

	public ImageIcon getImageIcon() {
		return imageIcon;
	}

	public void setImageIcon(ImageIcon imageIcon) {
		this.imageIcon = imageIcon;
	}

	public String getImageName() {
		return imageName;
	}

	public void setImageName(String imageName) {
		this.imageName = imageName;
	}

	public String getObjectName() {
		return objectName;
	}

	public Integer getObjectId() {
		return objectId;
	}

	public void setObjectId(Integer objectId) {
		this.objectId = objectId;
	}

	public MapObject(String objectName) {
		this.objectName = objectName;
		imageName = "";
		objectId = 0;
	}

	public void describeYourself() {

		System.out.println("    Object name: " + objectName + "; Image name: "
				+ imageName + "; Object id: " + objectId);
	}

	public String getObjectIdString() {
		describeYourself();

		if ((objectId >= 0) && (objectId < 10)) {
			return "00" + objectId;
		} else if (objectId < 100) {
			return "0" + objectId;
		} else if (objectId < 1000) {
			return "" + objectId;
		} else {
			return MapObject.DEFAULT_OBJECT_ID;
		}
	}

}
