/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package mapeditor.themesapi;

import java.util.logging.Level;
import java.util.logging.Logger;

import javax.swing.ImageIcon;

import mapeditor.logger.MapLogger;

public class MapObject implements Cloneable {

	private static final Logger logger = Logger.getLogger(MapObject.class
			.getName());

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
			logger.log(Level.SEVERE, MapLogger.ERROR, e);
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
		logger.log(Level.FINE, MapLogger.DESCRIBE_MAP_OBJECT, new String[] {
				objectName, imageName, Integer.toString(objectId) });
	}

	public String getObjectIdString() {
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
