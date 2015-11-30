package mapeditor.mainwindow;

import java.awt.Graphics;
import java.awt.Paint;
import java.awt.Point;
import java.awt.Rectangle;
import java.awt.Stroke;
import java.util.Iterator;

import mapeditor.dialogs.SegmentAttributesPanel;
import mapeditor.mapapi.CopyPaste;
import mapeditor.mapapi.CopyPasteSegment;
import mapeditor.mapapi.DraggedSegments;
import mapeditor.mapapi.MapApi;
import mapeditor.mapapi.MapSegment;
import mapeditor.mapapi.SelectedSegments;
import mapeditor.themesapi.MapObject;
import otherprods.ExampleFileFilter;

public class MapPane extends GridPane {

	ExampleFileFilter fe;

	SegmentAttributesPanel r_SegmentAttributesPanel = new SegmentAttributesPanel();
	private MapApi mapApi;
	private CopyPaste copyPaste;

	public MapPane(MapApi mapApi, CopyPaste copyPaste) {
		super();
		this.mapApi = mapApi;
		this.copyPaste = copyPaste;
	}

	@Override
	protected boolean isLayoutHex() {
		return mapApi.isLayoutHex();
	}

	@Override
	protected int getGridApiColumnsSize() {
		return mapApi.getColumnsSize();
	};

	@Override
	protected int getGridApiRowsSize() {
		return mapApi.getRowsSize();
	};

	public void setMapApi(MapApi mapApi) {
		this.mapApi = mapApi;
	}

	public void centerMap() {

		Rectangle r = panel.getVisibleRect();

		int centerX = this.getGridWidth() / 2;
		int centerY = this.getGridHeight() / 2;

		int newX = centerX - r.width / 2;
		int newY = centerY - r.height / 2;

		copyPaste.onCenterMapEvent();

		Rectangle newRectangle = new Rectangle(newX, newY, r.width, r.height);

		panel.scrollRectToVisible(newRectangle);

		panel.repaint();
	}

	public void zoomMapIn() {
		Rectangle rectangle = panel.getVisibleRect();
		int oldMapWidth = getGridWidth();
		int oldMapHeight = getGridHeight();

		segmentHeight += 5;
		segmentWidth += 5;

		copyPaste.onZoomMapInEvent();
		scrollMapToNewView(rectangle, oldMapWidth, oldMapHeight);
	}

	public void zoomMapOut() {
		Rectangle rectangle = panel.getVisibleRect();
		int oldMapWidth = getGridWidth();
		int oldMapHeight = getGridHeight();

		segmentHeight -= 5;
		segmentWidth -= 5;
		if (segmentHeight < 5) {
			segmentHeight = 5;
		}
		if (segmentWidth < 5) {
			segmentWidth = 5;
		}

		copyPaste.onZoomMapOutEvent();
		scrollMapToNewView(rectangle, oldMapWidth, oldMapHeight);
	}

	private void scrollMapToNewView(Rectangle oldRectangle, int oldMapWidth,
			int oldMapHeight) {
		double resizeX = (double) getGridWidth() / oldMapWidth;
		double resizeY = (double) getGridHeight() / oldMapHeight;

		int newX = 0;
		if (resizeX < 1) {
			newX = new Double(oldRectangle.x * resizeX
					- (oldRectangle.width - oldRectangle.width * resizeX) / 2)
					.intValue();
		} else {
			newX = new Double(oldRectangle.x * resizeX
					+ (oldRectangle.width * resizeX - oldRectangle.width) / 2)
					.intValue();
		}

		int newY = 0;
		if (resizeY < 1) {
			newY = new Double(oldRectangle.y * resizeY
					- (oldRectangle.height - oldRectangle.height * resizeY) / 2)
					.intValue();
		} else {
			newY = new Double(oldRectangle.y * resizeY
					+ (oldRectangle.height * resizeY - oldRectangle.height) / 2)
					.intValue();
		}

		Rectangle newRectangle = new Rectangle(newX, newY, oldRectangle.width,
				oldRectangle.height);
		panel.scrollRectToVisible(newRectangle);
		panel.repaint();
	}

	public void setDefaultMapZoom() {
		Rectangle rectangle = panel.getVisibleRect();
		int oldMapWidth = getGridWidth();
		int oldMapHeight = getGridHeight();

		segmentHeight = DEFAULT_SEGMENT_HEIGHT;
		segmentWidth = DEFAULT_SEGMENT_WIDTH;

		scrollMapToNewView(rectangle, oldMapWidth, oldMapHeight);
	}

	@Override
	protected MapObject getMapObject(int row, int col) {
		MapObject mapObject = null;
		MapSegment mapSegment = mapApi.getSegment(row, col);
		if (mapSegment != null) {
			mapObject = mapApi.getSegment(row, col).getMapObject();
		}
		return mapObject;
	}

	@Override
	public void paint(Graphics graphics) {
		super.paint(graphics);

		int divider = 1;
		if (isLayoutHex()) {
			divider = 2;
		}

		SelectedSegments selectedSegments = copyPaste.getSelectedSegments();
		if (selectedSegments.isActive()) {

			Paint paint = selectedSegments.getPaint();
			Stroke stroke = selectedSegments.getStroke();

			Iterator<CopyPasteSegment> iterator = selectedSegments
					.iteratorForDrawing();

			while (iterator.hasNext()) {
				CopyPasteSegment segment = iterator.next();

				if (((segment.getPoint().x) % 2) == 0) {
					drawSegment(graphics, segment.getPoint().x,
							segment.getPoint().y, 1, segment.getImage(), paint,
							stroke);
				} else {
					drawSegment(graphics, segment.getPoint().x,
							segment.getPoint().y, divider, segment.getImage(),
							paint, stroke);
				}

			}
		}

		DraggedSegments draggedSegments = copyPaste.getDraggedSegments();
		draggedSegments.tryToActivate(this, selectedSegments);

		if (draggedSegments.isActive()) {

			Paint paint = draggedSegments.getPaint();
			Stroke stroke = draggedSegments.getStroke();

			Iterator<CopyPasteSegment> iterator = draggedSegments.iterator();

			while (iterator.hasNext()) {
				CopyPasteSegment segment = iterator.next();

				int firstColumn = getFirstVisibleColumnNumber();// + 1;
				int lastColumn = getLastVisibleColumnNumber();// - 1;
				int firstRow = getFirstVisibleRowNumber();// + 1;
				int lastRow = getLastVisibleRowNumber();// - 1;

				Point point = segment.getPoint();
				if (point.x >= firstColumn && point.x <= lastColumn
						&& point.y >= firstRow && point.y <= lastRow) {

					if (((segment.getPoint().x) % 2) == 0) {
						drawSegment(graphics, segment.getPoint().x,
								segment.getPoint().y, 1, segment.getImage(),
								paint, stroke);
					} else {
						drawSegment(graphics, segment.getPoint().x,
								segment.getPoint().y, divider,
								segment.getImage(), paint, stroke);
					}
				}
			}
		}

		copyPaste.paint(graphics);
	}

	void onCutEvent() {
		copyPaste.onCutEvent();
	}

	void onCopyEvent() {
		copyPaste.onCopyEvent();
	}

	void onPasteEvent() {
		copyPaste.onPasteEvent();
	}

}
