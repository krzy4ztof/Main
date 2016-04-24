package mapeditor.mainwindow.map;

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

import mapeditor.mainwindow.GridPane;
import mapeditor.mapapi.CopyPaste;
import mapeditor.mapapi.CopyPasteSegment;
import mapeditor.mapapi.CustomObjectEdit;
import mapeditor.mapapi.DraggedSegments;
import mapeditor.mapapi.LayerAttributes;
import mapeditor.mapapi.MapApi;
import mapeditor.mapapi.MapSegment;
import mapeditor.mapapi.Point3D;
import mapeditor.mapapi.SelectedSegments;
import mapeditor.themesapi.CustomMapObject;
import mapeditor.themesapi.MapObject;
import otherprods.ExampleFileFilter;

public class MapPane extends GridPane {

	protected static final Point DEFAULT_LAYER_OFFSET = new Point(5, 5);

	protected Point layerOffset = new Point(DEFAULT_LAYER_OFFSET);

	private Paint inactiveLayerPaint;

	ExampleFileFilter fe;

	private MapApi mapApi;
	private CopyPaste copyPaste;
	private CustomObjectEdit customObjectEdit;

	public MapPane(MapApi mapApi, CopyPaste copyPaste,
			CustomObjectEdit customObjectEdit) {
		super();
		this.mapApi = mapApi;
		this.copyPaste = copyPaste;
		inactiveLayerPaint = Color.LIGHT_GRAY;
		this.customObjectEdit = customObjectEdit;
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
		layerOffset = new Point(DEFAULT_LAYER_OFFSET);

		copyPaste.onZoomMapDefaultEvent();

		scrollMapToNewView(rectangle, oldMapWidth, oldMapHeight);
	}

	protected CustomMapObject getCustomMapObject(int row, int col,
			int layerIndex) {
		CustomMapObject mapObject = null;
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

	@Override
	public void paint(Graphics graphics) {

		int divider = 1;
		if (isLayoutHex()) {
			divider = 2;
		}

		for (LayerAttributes layerAttributes : mapApi.getLayersAttributes()) {

			drawLayer(graphics, layerAttributes, divider);

			if (customObjectEdit.isActive()) {
				paintCustomObjectEdit(graphics, layerAttributes, divider);
			}

			paintSelectedSegments(graphics, layerAttributes, divider);
			paintDraggedSegments(graphics, layerAttributes, divider);
		}

		int mapWidth = getGridWidth();
		int mapHeight = getGridHeight();

		panel.setPreferredSize(new Dimension(mapWidth, mapHeight));
		panel.revalidate();
	}

	private void paintCustomObjectEdit(Graphics graphics,
			LayerAttributes layerAttributes, int divider) {
		Point3D pointObjectLocation = customObjectEdit.getObjectLocation();

		if (pointObjectLocation.z == layerAttributes.getIndex()) {

			Paint paint = customObjectEdit.getObjectLocationPaint();
			Stroke stroke = customObjectEdit.getObjectLocationStroke();

			if (graphics instanceof Graphics2D) {
				Graphics2D g2 = (Graphics2D) graphics;
				g2.setPaint(paint);
				g2.setStroke(stroke);
			} else {
				graphics.setColor(Color.YELLOW);
			}

			if (((pointObjectLocation.x) % 2) == 0) {
				drawSegmentGrid(graphics, pointObjectLocation.x,
						pointObjectLocation.y, 1, layerAttributes);

			} else {
				drawSegmentGrid(graphics, pointObjectLocation.x,
						pointObjectLocation.y, divider, layerAttributes);
			}
		}

		Point3D pointPropertyLocation = customObjectEdit
				.getPointPropertyLocation();

		if (pointPropertyLocation != null
				&& pointPropertyLocation.z == layerAttributes.getIndex()) {

			Paint paint = customObjectEdit.getPointPropertyPaint();
			Stroke stroke = customObjectEdit.getPointPropertyStroke();

			if (graphics instanceof Graphics2D) {
				Graphics2D g2 = (Graphics2D) graphics;
				g2.setPaint(paint);
				g2.setStroke(stroke);
			} else {
				graphics.setColor(Color.YELLOW);
			}

			if (((pointPropertyLocation.x) % 2) == 0) {
				drawSegmentGrid(graphics, pointPropertyLocation.x,
						pointPropertyLocation.y, 1, layerAttributes);

			} else {
				drawSegmentGrid(graphics, pointPropertyLocation.x,
						pointPropertyLocation.y, divider, layerAttributes);
			}
		}

	}

	public void drawLayer(Graphics graphics, LayerAttributes layerAttributes,
			int divider) {

		int firstColumn = getFirstVisibleColumnNumber();// + 1;
		int lastColumn = getLastVisibleColumnNumber();// - 1;
		int firstRow = getFirstVisibleRowNumber();// + 1;
		int lastRow = getLastVisibleRowNumber();// - 1;

		Paint paint;
		if (layerAttributes.isActive()) {
			paint = getPaint();
		} else {
			paint = inactiveLayerPaint;
		}
		Stroke stroke = getStroke();

		if (graphics instanceof Graphics2D) {
			Graphics2D g2 = (Graphics2D) graphics;
			g2.setPaint(paint);
			g2.setStroke(stroke);
		} else {
			graphics.setColor(Color.YELLOW);
		}

		for (int column = firstColumn; column <= lastColumn; column++) {
			for (int row = firstRow; row <= lastRow; row++) {
				if (((column) % 2) == 0) {
					drawSegment(graphics, column, row, 1, layerAttributes);
				} else {
					drawSegment(graphics, column, row, divider, layerAttributes);
				}
			}
		}
	}

	private Point getOffsetForLayer(int layerIndex) {
		int size = mapApi.getLayerAttributesSize();
		int multiplier = size - 1 - layerIndex;

		Point point = new Point(layerOffset.x * multiplier, layerOffset.y
				* multiplier);

		return point;
	}

	private Point getOffsetForLayer(LayerAttributes layerAttributes) {
		int index = layerAttributes.getIndex();
		return getOffsetForLayer(index);
	}

	protected void drawSegmentImage(Graphics graphics, int column, int row,
			int divider, Image image, LayerAttributes layerAttributes) {

		Point offset = getOffsetForLayer(layerAttributes);

		int currentHeight = row * segmentHeight
				+ (segmentHeight - segmentHeight / divider);

		graphics.drawImage(image, column * segmentWidth + getLeftMarigin()
				+ offset.x, currentHeight + getTopMarigin() + offset.y,
				segmentWidth, segmentHeight, panel);
	}

	protected void drawSegmentGrid(Graphics graphics, int column, int row,
			int divider, LayerAttributes layerAttributes) {

		Point offset = getOffsetForLayer(layerAttributes);

		int currentHeight = row * segmentHeight
				+ (segmentHeight - segmentHeight / divider);

		if (graphics instanceof Graphics2D) {
			Graphics2D g2 = (Graphics2D) graphics;
			g2.drawRect(column * segmentWidth + getLeftMarigin() + offset.x,
					currentHeight + getTopMarigin() + offset.y, segmentWidth,
					segmentHeight);
		} else {
			for (int i = 0; i < 3; i++) {
				graphics.drawOval(column * segmentWidth + getLeftMarigin() + i
						+ offset.x, currentHeight + getTopMarigin() + i
						+ offset.y, segmentWidth - 2 * i, segmentHeight - 2 * i);
			}
		}
	}

	private void drawSegment(Graphics graphics, int column, int row,
			int divider, LayerAttributes layerAttributes) {

		if (layerAttributes.isBackgroundVisible()) {
			MapObject mapObject = getMapObject(row, column,
					layerAttributes.getIndex());
			if (mapObject != null) {
				Image image = mapObject.getImageIcon().getImage();
				drawSegmentImage(graphics, column, row, divider, image,
						layerAttributes);
			}
		}

		if (layerAttributes.isObjectsVisible()) {
			MapObject customMapObject = getCustomMapObject(row, column,
					layerAttributes.getIndex());
			if (customMapObject != null) {
				Image image = customMapObject.getImageIcon().getImage();
				drawSegmentImage(graphics, column, row, divider, image,
						layerAttributes);
			}
		}

		if (layerAttributes.isBackgroundVisible()
				|| layerAttributes.isObjectsVisible()) {
			drawSegmentGrid(graphics, column, row, divider, layerAttributes);
		}
	}

	protected void paintSelectedSegments(Graphics graphics,
			LayerAttributes layerAttributes, int divider) {
		SelectedSegments selectedSegments = copyPaste.getSelectedSegments();
		int layerIndex = layerAttributes.getIndex();

		if (selectedSegments.isActiveForLayer(layerIndex)) {

			Paint paint = selectedSegments.getPaint();
			Stroke stroke = selectedSegments.getStroke();
			if (graphics instanceof Graphics2D) {
				Graphics2D g2 = (Graphics2D) graphics;
				g2.setPaint(paint);
				g2.setStroke(stroke);
			} else {
				graphics.setColor(Color.YELLOW);
			}

			Iterator<CopyPasteSegment> iterator = selectedSegments
					.iteratorForDrawing();

			while (iterator.hasNext()) {
				CopyPasteSegment segment = iterator.next();

				if (((segment.getPoint().x) % 2) == 0) {
					// drawSegmentCopyPaste(graphics, segment.getPoint().x,
					// segment.getPoint().y, 1, segment.getImage(),
					// layerAttributes);

					drawSegmentGrid(graphics, segment.getPoint().x,
							segment.getPoint().y, 1, layerAttributes);

				} else {
					// drawSegmentCopyPaste(graphics, segment.getPoint().x,
					// segment.getPoint().y, divider, segment.getImage(),
					// layerAttributes);

					drawSegmentGrid(graphics, segment.getPoint().x,
							segment.getPoint().y, divider, layerAttributes);

				}

			}
		}

		copyPaste.paintSelectedRectangle(graphics);

	}

	public void paintDraggedSegments(Graphics graphics,
			LayerAttributes layerAttributes, int divider) {

		SelectedSegments selectedSegments = copyPaste.getSelectedSegments();
		int layerIndex = layerAttributes.getIndex();

		if (layerAttributes.isActive()) {

			DraggedSegments draggedSegments = copyPaste.getDraggedSegments();
			draggedSegments.tryToActivate(this, selectedSegments, layerIndex);

			if (draggedSegments.isActiveForLayer(layerIndex)) {

				Paint paint = draggedSegments.getPaint();
				Stroke stroke = draggedSegments.getStroke();
				if (graphics instanceof Graphics2D) {
					Graphics2D g2 = (Graphics2D) graphics;
					g2.setPaint(paint);
					g2.setStroke(stroke);
				} else {
					graphics.setColor(Color.YELLOW);
				}

				Iterator<CopyPasteSegment> iterator = draggedSegments
						.iterator();

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
							drawSegmentCopyPaste(graphics,
									segment.getPoint().x, segment.getPoint().y,
									1, segment.getImage(),
									segment.getCustomObjectImage(),
									layerAttributes);
						} else {
							drawSegmentCopyPaste(graphics,
									segment.getPoint().x, segment.getPoint().y,
									divider, segment.getImage(),
									segment.getCustomObjectImage(),
									layerAttributes);
						}
					}
				}
			}
		}

		copyPaste.paintDraggedRectangle(graphics);
	}

	protected void drawSegmentCopyPaste(Graphics graphics, int column, int row,
			int divider, Image image, Image customImage,
			LayerAttributes layerAttributes) {
		drawSegmentImage(graphics, column, row, divider, image, layerAttributes);
		if (customImage != null) {
			drawSegmentImage(graphics, column, row, divider, customImage,
					layerAttributes);
		}
		drawSegmentGrid(graphics, column, row, divider, layerAttributes);
	}

	public void onCutEvent() {
		copyPaste.onCutEvent();
	}

	public void onCopyEvent() {
		copyPaste.onCopyEvent();
	}

	public void onPasteEvent() {
		copyPaste.onPasteEvent();
	}

	public LinkedList<LinkedList<CopyPasteSegment>> getSegmentPoints(
			Point firstPoint, Point lastPoint, int layerIndex) {

		Point minPoint = getMinPoint(firstPoint, lastPoint);
		Point maxPoint = getMaxPoint(firstPoint, lastPoint);

		Point leftUpperCorner = new Point(minPoint.x, minPoint.y);
		Point rightUpperCorner = new Point(maxPoint.x, minPoint.y);

		LinkedList<Point> upperLine = getVerticalLineSegments(leftUpperCorner,
				rightUpperCorner, layerIndex);
		Point leftBottomCorner = new Point(minPoint.x, maxPoint.y);
		Point rightBottomCorner = new Point(maxPoint.x, maxPoint.y);
		LinkedList<Point> bottomLine = getVerticalLineSegments(
				leftBottomCorner, rightBottomCorner, layerIndex);
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

				CustomMapObject customMapObject = getCustomMapObject(row, col
						+ firstSegmentPoint.x, layerIndex);

				Point point = new Point(col + firstSegmentPoint.x, row);
				CopyPasteSegment copyPasteSegment = new CopyPasteSegment(
						mapObject, customMapObject, point);
				newColumn.add(copyPasteSegment);

			}

			segments.add(newColumn);

		}
		return segments;
	}

	protected LinkedList<Point> getVerticalLineSegments(Point leftPoint,
			Point rightPoint, int layerIndex) {
		LinkedList<Point> result = new LinkedList<Point>();

		if (leftPoint.y != rightPoint.y) {
			return result;
		}

		if (leftPoint.x > rightPoint.x) {
			return result;
		}

		int curX = leftPoint.x;

		while (curX <= rightPoint.x) {
			Point curPoint = new Point(curX, leftPoint.y);
			Point segPoint = getSegmentPointAtCursor(curPoint, layerIndex);
			result.add(segPoint);

			curX += segmentWidth;
		}

		Point segPoint = getSegmentPointAtCursor(rightPoint, layerIndex);
		if (!result.contains(segPoint)) {
			result.add(segPoint);
		}
		return result;

	}

	public Point getSegmentPointAtCursor(Point cur, int layerIndex) {
		/*
		 * cur - mouse cursor MapPanel coordinates. Returns number of segment
		 * column and row that cursor points. Returns Point(-1,-1) when cursor
		 * is out of map boundaries
		 */

		int column = getColumnNumberAt(cur.x, layerIndex);
		int row = 0;

		if (isLayoutHex() && column % 2 == 1) {
			// first column is 0!!
			// So column nr 1 is even column (parzysta)
			row = getRowNumberAt(cur.y, true, layerIndex); // even - parzysty
		} else {
			row = getRowNumberAt(cur.y, false, layerIndex); // odd - nieparzysty
		}

		if ((column >= getGridApiColumnsSize())
				|| (row >= getGridApiRowsSize()) || (column < 0) || (row < 0)) {
			return new Point(-1, -1);
		}

		return new Point(column, row);
	}

	protected int getColumnNumberAt(int x, int layerIndex) {

		Point offset = getOffsetForLayer(layerIndex);

		int column = x - getLeftMarigin() - offset.x;
		if (column < 0) {
			column = -1;
		} else {
			column = column / segmentWidth;
		}

		return column;
	}

	protected int getRowNumberAt(int y, boolean evenColumn, int layerIndex) {
		// even - parzysty - shifted down
		if (evenColumn && isLayoutHex()) {
			y = y - segmentHeight / 2;
		}

		Point offset = getOffsetForLayer(layerIndex);
		int row = y - getTopMarigin() - offset.y;

		if (row < 0) {
			row = -1;
		} else {
			row = row / segmentHeight;
		}

		return row;
	}
}
