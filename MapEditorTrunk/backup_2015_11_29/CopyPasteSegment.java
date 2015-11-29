package mapeditor.mapapi;

import java.awt.Image;
import java.awt.Point;

import javax.swing.ImageIcon;

import mapeditor.themesapi.MapObject;

public class CopyPasteSegment {
	private Point point;
	private Image image;
	private MapObject mapObject;

	/*
	 * enum CutCopyState { CUT, COPY }
	 * 
	 * protected CutCopyState cutCopyState = CutCopyState.COPY;
	 */
	/*
	 * public CopyPasteSegment(Point point) { this.point = point;
	 * 
	 * ImageIcon imageFile = new ImageIcon("images/frontwheelar.png"); image =
	 * imageFile.getImage();
	 * 
	 * }
	 */

	public CopyPasteSegment(MapObject mapObject, Point point) {
		this.point = point;
		this.mapObject = mapObject;

		ImageIcon imageFile = new ImageIcon("images/frontwheelar.png");
		image = imageFile.getImage();

	}

	/*
	 * public void setCutState() { cutCopyState = CutCopyState.CUT; }
	 * 
	 * public void setCopyState() { cutCopyState = CutCopyState.COPY; }
	 * 
	 * public boolean isCutState() { if (cutCopyState == CutCopyState.CUT) {
	 * return true; } else { return false; } }
	 */
	public void setMapObject(MapObject mapObject) {
		this.mapObject = mapObject;
	}

	public MapObject getMapObject() {
		return mapObject;
	}

	public Point getPoint() {
		return point;
	}

	public Image getImage() {

		// if (cutCopyState == CutCopyState.CUT) {
		// return null;
		// }

		if (mapObject != null) {
			return mapObject.getImageIcon().getImage();
		}

		return image;
	}

}
