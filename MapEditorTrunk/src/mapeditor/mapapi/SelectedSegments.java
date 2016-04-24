package mapeditor.mapapi;

import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Point;
import java.util.Iterator;
import java.util.LinkedList;

import javax.swing.plaf.ColorUIResource;

import mapeditor.mainwindow.map.MapPane;
import mapeditor.themesapi.MapObjectFactory;

public class SelectedSegments extends CopyPasteSegments {

	enum CutCopyState {
		CUT, COPY
	}

	CutCopyState cutCopyState = CutCopyState.CUT;

	private MapObjectFactory mapObjectFactory;

	private LinkedList<CopyPasteSegment> blankSegments;

	// First point of selected region
	private Point firstPointToCut;

	// Last point of selected region
	private Point lastPointToCut;

	public void setFirstPointToCut(Point point) {
		firstPointToCut = point;
	}

	public void setLastPointToCut(Point point) {
		lastPointToCut = point;
	}

	public Point getFirstPointToCut() {
		return firstPointToCut;
	}

	public Point getLastPointToCut() {
		return lastPointToCut;
	}

	SelectedSegments(MapObjectFactory mapObjectFactory) {
		this.mapObjectFactory = mapObjectFactory;
		cutCopyState = CutCopyState.CUT;
		firstPointToCut = null;
		lastPointToCut = null;
		paint = new ColorUIResource(0, 128, 32);
	}

	public void activate(MapPane mapPane, int layerIndex) {
		super.activate(mapPane, firstPointToCut, lastPointToCut, layerIndex);
	}

	@Override
	public void deactivate() {
		super.deactivate();
		firstPointToCut = null;
		lastPointToCut = null;
		blankSegments = null;
	}

	public void setCutState() {
		cutCopyState = CutCopyState.CUT;
	}

	public void setCopyState() {
		cutCopyState = CutCopyState.COPY;
	}

	public boolean isCutState() {
		if (cutCopyState == CutCopyState.CUT) {
			return true;
		} else {
			return false;
		}
	}

	public Iterator<CopyPasteSegment> iteratorForDrawing() {
		if (cutCopyState == CutCopyState.COPY) {
			return super.iterator();
		}

		if (blankSegments == null) {
			blankSegments = new LinkedList<CopyPasteSegment>();
			for (LinkedList<CopyPasteSegment> column : segments) {
				for (CopyPasteSegment segment : column) {

					CopyPasteSegment newSegment = new CopyPasteSegment(
							mapObjectFactory.getBlankMapObject(), null,
							segment.getPoint());

					blankSegments.add(newSegment);
				}
			}
		}

		return blankSegments.iterator();
	}

	protected void paintRectangle(Graphics graphics) {

		boolean graphicsChanged = false;

		if (isActive()) {

			changeGraphics(graphics);
			graphicsChanged = true;

			drawRectangle(graphics, minPoint, maxPoint);
		}

		if (firstPointToCut != null && lastPointToCut != null) {
			if (!graphicsChanged) {
				changeGraphics(graphics);
			}

			drawRectangle(graphics, firstPointToCut, lastPointToCut);

		}
	}

	protected void changeGraphics(Graphics graphics) {
		if (graphics instanceof Graphics2D) {
			Graphics2D g2 = (Graphics2D) graphics;
			g2.setStroke(stroke);
			g2.setPaint(paintRectangle);
		}
	}

}
