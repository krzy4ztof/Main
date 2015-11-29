package mapeditor.mapapi;

import java.awt.BasicStroke;
import java.awt.Point;
import java.util.Iterator;
import java.util.LinkedList;

import javax.swing.plaf.ColorUIResource;

import mapeditor.mainwindow.MapPane;
import mapeditor.themesapi.MapObjectFactory;

public class SelectedSegments extends CopyPasteSegments {

	enum CutCopyState {
		CUT, COPY
	}

	CutCopyState cutCopyState = CutCopyState.COPY;

	private MapObjectFactory mapObjectFactory;

	private LinkedList<CopyPasteSegment> blankSegments;

	SelectedSegments(MapPane mapPane, Point firstPoint, Point lastPoint,
			MapObjectFactory mapObjectFactory) {
		super(mapPane, firstPoint, lastPoint);
		this.mapObjectFactory = mapObjectFactory;
		cutCopyState = CutCopyState.COPY;

		paint = new ColorUIResource(0, 128, 32);
		float dash[] = { 5.0f };
		stroke = new BasicStroke(3.0f, BasicStroke.CAP_ROUND,
				BasicStroke.JOIN_ROUND, 5.0f, dash, 0.0f);
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
		System.out.println("Itertor FOR Drawing START");
		if (cutCopyState == CutCopyState.COPY) {
			System.out.println("Itertor FOR Drawing COPY");

			return super.iterator();
		}

		if (blankSegments == null) {
			System.out.println("Iterator FOR Drawing BLANK");

			blankSegments = new LinkedList<CopyPasteSegment>();

			for (LinkedList<CopyPasteSegment> column : segments) {
				for (CopyPasteSegment segment : column) {

					CopyPasteSegment newSegment = new CopyPasteSegment(
							mapObjectFactory.getBlankMapObject(),
							segment.getPoint());

					blankSegments.add(newSegment);
				}
			}
		}

		return blankSegments.iterator();
	}
}
