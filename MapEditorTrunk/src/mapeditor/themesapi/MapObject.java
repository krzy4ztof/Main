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
public class MapObject {

	private String objectName;
	private String imageName;
	private ImageIcon imageIcon;
	private Integer objectId;
	public final static String DEFAULT_OBJECT_ID = "000";

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
	}

	public void describeYourself() {

		System.out.println("    Object name: " + objectName + "; Image name: "
				+ imageName + "; Object id: " + objectId);
	}

	public String getObjectIdString() {

		if ((objectId >= 0) && (objectId < 10)) {
			return "00" + objectId;

		} else if (objectId < 100) {
			return "0" + objectId;
		} else if (objectId < 1000) {
			return objectId.toString();
		} else {
			return MapObject.DEFAULT_OBJECT_ID;
		}
	}
}
