package mapeditor.mainwindow;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.Paint;
import java.awt.Point;
import java.awt.Rectangle;
import java.awt.Stroke;
import java.util.Iterator;
import java.util.LinkedList;

import mapeditor.dialogs.SegmentAttributesPanel;
import mapeditor.mapapi.CopyPaste;
import mapeditor.mapapi.CopyPasteSegment;
import mapeditor.mapapi.DraggedSegments;
import mapeditor.mapapi.LayerAttributes;
import mapeditor.mapapi.MapApi;
import mapeditor.mapapi.MapSegment;
import mapeditor.mapapi.SelectedSegments;
import mapeditor.themesapi.MapObject;
import otherprods.ExampleFileFilter;

public class MapPane extends GridPane {

	protected static final Point DEFAULT_LAYER_OFFSET = new Point(5, 5);

	protected Point layerOffset = DEFAULT_LAYER_OFFSET;

	private Paint inactiveLayerPaint;

	ExampleFileFilter fe;

	SegmentAttributesPanel r_SegmentAttributesPanel = new SegmentAttributesPanel();
	private MapApi mapApi;
	private CopyPaste copyPaste;

	public MapPane(MapApi mapApi, CopyPaste copyPaste) {
		super();
		this.mapApi = mapApi;
		this.copyPaste = copyPaste;
		inactiveLayerPaint = Color.LIGHT_GRAY;
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
		layerOffset.x += 1;
		layerOffset.y += 1;

		copyPaste.onZoomMapInEvent();
		scrollMapToNewView(rectangle, oldMapWidth, oldMapHeight);
	}

	public void zoomMapOut() {
		Rectangle rectangle = panel.getVisibleRect();
		int oldMapWidth = getGridWidth();
		int oldMapHeight = getGridHeight();

		segmentHeight -= 5;
		segmentWidth -= 5;
		layerOffset.x -= 1;
		layerOffset.y -= 1;

		if (layerOffset.x < 1) {
			layerOffset.x = 1;
		}

		if (layerOffset.y < 1) {
			layerOffset.y = 1;
		}

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

	protected MapObject getCustomMapObject(int row, int col, int layerIndex) {
		MapObject mapObject = null;
		MapSegment mapSegment = mapApi.getSegment(row, col);
		if (mapSegment != null) {
			mapObject = mapApi.getSegment(row, col).getCustomMapObject(
					layerIndex);
		}
		return mapObject;
	}

	protected MapObject getMapObject(int row, int col, int layerIndex) {
		MapObject mapObject = null;
		MapSegment mapSegment = mapApi.getSegment(row, col);
		if (mapSegment != null) {
			mapObject = mapApi.getSegment(row, col).getMapObject(layerIndex);
		}
		return mapObject;
	}

	// @Override
	@Override
	public void paint(Graphics graphics) {
		// for (int i = 0; i < mapApi.getLayerAttributesSize(); i++) {

		// paint(graphics, i);
		// }

		for (LayerAttributes layerAttributes : mapApi.getLayersAttributes()) {
			paint(graphics, layerAttributes);

			if (layerAttributes.isActive()) {
				// graphics

				Paint tempPaint = null;
				Stroke tempStroke = null;
				if (graphics instanceof Graphics2D) {
					Graphics2D g2 = (Graphics2D) graphics;

					tempPaint = g2.getPaint();
					tempStroke = g2.getStroke();
					// g2.setPaint(paint);
					// g2.setStroke(stroke);
				}

				paintCopyPaste(graphics, layerAttributes);

				if (graphics instanceof Graphics2D) {
					Graphics2D g2 = (Graphics2D) graphics;

					if (tempPaint != null) {
						g2.setPaint(tempPaint);
					}
					if (tempStroke != null) {

						g2.setStroke(tempStroke);
					}
				}
			}

		}
	}

	public void paint(Graphics graphics, LayerAttributes layerAttributes) {

		int divider = 1;
		if (isLayoutHex()) {
			divider = 2;
		}

		int firstColumn = getFirstVisibleColumnNumber();// + 1;
		int lastColumn = getLastVisibleColumnNumber();// - 1;
		int firstRow = getFirstVisibleRowNumber();// + 1;
		int lastRow = getLastVisibleRowNumber();// - 1;

		for (int column = firstColumn; column <= lastColumn; column++) {
			for (int row = firstRow; row <= lastRow; row++) {
				if (((column) % 2) == 0) {
					drawSegment(graphics, column, row, 1, layerAttributes);
				} else {
					drawSegment(graphics, column, row, divider, layerAttributes);
				}
			}
		}

		int mapWidth = getGridWidth();
		int mapHeight = getGridHeight();

		panel.setPreferredSize(new Dimension(mapWidth, mapHeight));
		panel.revalidate();

	}

	private Point getOffsetForLayer(LayerAttributes layerAttributes) {
		// Point point = null;

		int size = mapApi.getLayerAttributesSize();
		int index = layerAttributes.getIndex();

		int multiplier = size - 1 - index;

		Point point = new Point(layerOffset.x * multiplier, layerOffset.y
				* multiplier);
		/*
		 * if (multiplier <== 0) { return layerOffset; }
		 * 
		 * for (int i = 1; i < multiplier; i++) {
		 * 
		 * } size = 4;
		 * 
		 * index = 0;
		 */
		return point;
	}

	protected void drawSegment(Graphics graphics, int column, int row,
			int divider, Image image, Paint paint, Stroke stroke,
			LayerAttributes layerAttributes) {

		Point offset = getOffsetForLayer(layerAttributes);

		int currentHeight = row * segmentHeight
				+ (segmentHeight - segmentHeight / divider);

		// graphics.setColor(Color.LIGHT_GRAY);
		// TODO: skasowac PINK
		graphics.setColor(Color.CYAN);// BACKGROUND

		// graphics.drawRect(column * segmentWidth + getLeftMarigin(),
		// currentHeight + getTopMarigin(), segmentWidth, segmentHeight);

		// customMapObject bedzie rysowany na mapObject
		graphics.drawImage(image, column * segmentWidth + getLeftMarigin()
				+ offset.x, currentHeight + getTopMarigin() + offset.y,
				segmentWidth, segmentHeight, panel);

		/*
		 * if (graphics instanceof Graphics2D) { Graphics2D g2 = (Graphics2D)
		 * graphics;
		 * 
		 * g2.setPaint(paint); g2.setStroke(stroke); g2.drawRect(column *
		 * segmentWidth + getLeftMarigin(), currentHeight + getTopMarigin(),
		 * segmentWidth, segmentHeight); } else {
		 * graphics.setColor(Color.YELLOW); for (int i = 0; i < 3; i++) {
		 * graphics.drawOval(column * segmentWidth + getLeftMarigin() + i,
		 * currentHeight + getTopMarigin() + i, segmentWidth - 2 i,
		 * segmentHeight - 2 * i); } }
		 */
	}

	protected void drawSegmentGrid(Graphics graphics, int column, int row,
			int divider, Paint paint, Stroke stroke,
			LayerAttributes layerAttributes) {

		Point offset = getOffsetForLayer(layerAttributes);

		int currentHeight = row * segmentHeight
				+ (segmentHeight - segmentHeight / divider);

		// graphics.setColor(Color.LIGHT_GRAY);

		/*
		 * if (layerAttributes.isActive()) { graphics.setColor(Color.GRAY); }
		 * else { graphics.setColor(Color.LIGHT_GRAY); }
		 */

		// TODO: skasowac PINK
		// graphics.setColor(Color.PINK);// ten kolor sprawia ze jest rozowy
		// graphics.setColor(Color.BLACK);

		graphics.drawRect(column * segmentWidth + getLeftMarigin() + offset.x,
				currentHeight + getTopMarigin() + offset.y, segmentWidth,
				segmentHeight);
		// graphics.drawImage(image, column * segmentWidth + getLeftMarigin(),
		// currentHeight + getTopMarigin(), segmentWidth, segmentHeight,
		// panel.getBackground(), panel);

		// customMapObject bedzie rysowany na mapObject
		// graphics.drawImage(image, column * segmentWidth + getLeftMarigin(),
		// currentHeight + getTopMarigin(), segmentWidth, segmentHeight,
		// panel);

		if (graphics instanceof Graphics2D) {
			Graphics2D g2 = (Graphics2D) graphics;

			g2.setPaint(paint);
			g2.setStroke(stroke);
			g2.drawRect(column * segmentWidth + getLeftMarigin() + offset.x,
					currentHeight + getTopMarigin() + offset.y, segmentWidth,
					segmentHeight);
		} else {
			graphics.setColor(Color.YELLOW);
			for (int i = 0; i < 3; i++) {
				graphics.drawOval(column * segmentWidth + getLeftMarigin() + i
						+ offset.x, currentHeight + getTopMarigin() + i
						+ offset.y, segmentWidth - 2 * i, segmentHeight - 2 * i);
			}
		}
	}

	private void drawSegment(Graphics graphics, int column, int row,
			int divider, LayerAttributes layerAttributes) {

		Paint paint;
		if (layerAttributes.isActive()) {
			paint = getPaint();
			// graphics.setColor(Color.GRAY);
		} else {

			paint = inactiveLayerPaint;
			// graphics.setColor(Color.LIGHT_GRAY);
		}

		if (layerAttributes.isBackgroundVisible()) {
			MapObject mapObject = getMapObject(row, column,
					layerAttributes.getIndex());
			if (mapObject != null) {
				Image image = mapObject.getImageIcon().getImage();
				drawSegment(graphics, column, row, divider, image, paint,
						getStroke(), layerAttributes);
			}
		}

		if (layerAttributes.isObjectsVisible()) {
			MapObject customMapObject = getCustomMapObject(row, column,
					layerAttributes.getIndex());
			if (customMapObject != null) {
				Image image = customMapObject.getImageIcon().getImage();
				// System.out.println(image.);
				drawSegment(graphics, column, row, divider, image, paint,
						getStroke(), layerAttributes);
			}
		}

		if (layerAttributes.isBackgroundVisible()
				|| layerAttributes.isObjectsVisible()) {
			drawSegmentGrid(graphics, column, row, divider, paint, getStroke(),
					layerAttributes);
		}
	}

	public void paint_old(Graphics graphics, LayerAttributes layerAttributes) {
		// super.paint(graphics);

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

	public void paintCopyPaste(Graphics graphics,
			LayerAttributes layerAttributes) {
		// super.paint(graphics);

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

	/*
	 * @Override protected MapObject getMapObject(int row, int col) { // TODO:
	 * REMOVE return getMapObject(row, col, 0); }
	 */

	/*
	 * @Override protected MapObject getCustomMapObject(int row, int col) { //
	 * TODO: remove return getCustomMapObject(row, col, 0); }
	 */

	public LinkedList<LinkedList<CopyPasteSegment>> getSegmentPoints(
			Point firstPoint, Point lastPoint, int layerIndex) {

		Point minPoint = getMinPoint(firstPoint, lastPoint);
		Point maxPoint = getMaxPoint(firstPoint, lastPoint);

		Point leftUpperCorner = new Point(minPoint.x, minPoint.y);
		Point rightUpperCorner = new Point(maxPoint.x, minPoint.y);

		LinkedList<Point> upperLine = getVerticalLineSegments(leftUpperCorner,
				rightUpperCorner);
		Point leftBottomCorner = new Point(minPoint.x, maxPoint.y);
		Point rightBottomCorner = new Point(maxPoint.x, maxPoint.y);
		LinkedList<Point> bottomLine = getVerticalLineSegments(
				leftBottomCorner, rightBottomCorner);
		LinkedList<LinkedList<CopyPasteSegment>> segments = new LinkedList<LinkedList<CopyPasteSegment>>();

		LinkedList<CopyPasteSegment> newColumn;

		int nrColumns = upperLine.size();
		Point firstSegmentPoint = upperLine.getFirst();

		for (int col = 0; col < nrColumns; col++) {

			Point upperPoint = upperLine.get(col);

			Point bottomPoint = bottomLine.get(col);

			newColumn = new LinkedList<CopyPasteSegment>();

			for (int row = upperPoint.y; row <= bottomPoint.y; row++) {

				MapObject mapObject = getMapObject(row, col
						+ firstSegmentPoint.x, layerIndex);
				if (mapObject != null) {
					mapObject = mapObject.clone();
					Point point = new Point(col + firstSegmentPoint.x, row);

					newColumn.add(new CopyPasteSegment(mapObject, point));
				}
			}

			segments.add(newColumn);

		}
		return segments;
	}
}
