package mapeditor.mainwindow;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.Paint;
import java.awt.Point;
import java.awt.Rectangle;
import java.awt.Stroke;
import java.util.LinkedList;

import javax.swing.JLayeredPane;
import javax.swing.JScrollPane;

import mapeditor.mapapi.CopyPasteSegment;
import mapeditor.themesapi.MapObject;

public abstract class GridPane {

	private static int LEFT_MARIGIN = 70;
	private static int RIGHT_MARIGIN = 30;
	private static int TOP_MARIGIN = 80;
	private static int BOTTOM_MARIGIN = 60;

	protected static final int DEFAULT_SEGMENT_WIDTH = 40;
	protected static final int DEFAULT_SEGMENT_HEIGHT = 40;

	protected int segmentWidth = DEFAULT_SEGMENT_WIDTH;
	protected int segmentHeight = DEFAULT_SEGMENT_HEIGHT;

	protected JLayeredPane panel;

	protected JScrollPane scrollPane;

	private Paint paint;
	private Stroke stroke;

	public GridPane() {
		super();

		panel = new JLayeredPane() {

			private static final long serialVersionUID = 1L;

			@Override
			public void paint(Graphics g) {
				super.paint(g);
				GridPane.this.paint(g);
			}
		};

		// panel.setBackground(new Color(238, 238, 238));
		// TODO: skasowac kolor
		panel.setBackground(Color.PINK);

		scrollPane = new JScrollPane(panel);
		paint = Color.GRAY;
		stroke = new BasicStroke(1.0f);
	}

	protected Paint getPaint() {
		return paint;
	}

	protected Stroke getStroke() {
		return stroke;
	}

	protected Image getImage(int column, int row) {
		MapObject mapObject = getMapObject(row, column);
		if (mapObject == null) {
			return null;
		}

		Image image = mapObject.getImageIcon().getImage();
		return image;
	}

	private void drawSegment(Graphics graphics, int column, int row, int divider) {
		MapObject mapObject = getMapObject(row, column);
		if (mapObject != null) {
			Image image = mapObject.getImageIcon().getImage();
			drawSegment(graphics, column, row, divider, image, paint, stroke);
		}

		MapObject customMapObject = getCustomMapObject(row, column);
		if (customMapObject != null) {
			Image image = customMapObject.getImageIcon().getImage();
			// System.out.println(image.);
			drawSegment(graphics, column, row, divider, image, paint, stroke);
		}
	}

	protected void drawSegment(Graphics graphics, int column, int row,
			int divider, Image image) {
		drawSegment(graphics, column, row, divider, image, paint, stroke);
	}

	protected void drawSegment(Graphics graphics, int column, int row,
			int divider, Image image, Paint paint, Stroke stroke) {

		int currentHeight = row * segmentHeight
				+ (segmentHeight - segmentHeight / divider);

		// graphics.setColor(Color.LIGHT_GRAY);
		// TODO: skasowac PINK
		graphics.setColor(Color.PINK);

		graphics.drawRect(column * segmentWidth + getLeftMarigin(),
				currentHeight + getTopMarigin(), segmentWidth, segmentHeight);
		// graphics.drawImage(image, column * segmentWidth + getLeftMarigin(),
		// currentHeight + getTopMarigin(), segmentWidth, segmentHeight,
		// panel.getBackground(), panel);

		// customMapObject bedzie rysowany na mapObject
		graphics.drawImage(image, column * segmentWidth + getLeftMarigin(),
				currentHeight + getTopMarigin(), segmentWidth, segmentHeight,
				panel);

		if (graphics instanceof Graphics2D) {
			Graphics2D g2 = (Graphics2D) graphics;

			g2.setPaint(paint);
			g2.setStroke(stroke);
			g2.drawRect(column * segmentWidth + getLeftMarigin(), currentHeight
					+ getTopMarigin(), segmentWidth, segmentHeight);
		} else {
			graphics.setColor(Color.YELLOW);
			for (int i = 0; i < 3; i++) {
				graphics.drawOval(column * segmentWidth + getLeftMarigin() + i,
						currentHeight + getTopMarigin() + i, segmentWidth - 2
								* i, segmentHeight - 2 * i);
			}
		}
	}

	protected int getBottomMarigin() {
		return BOTTOM_MARIGIN;
	}

	private int getColumnNumberAt(int x) {
		int column = x - getLeftMarigin();
		if (column < 0) {
			column = -1;
		} else {
			column = column / segmentWidth;
		}

		return column;
	}

	protected int getFirstVisibleColumnNumber() {
		int x = panel.getVisibleRect().x;
		int column = getColumnNumberAt(x);
		column = Math.max(column, 0);
		return column;
	}

	protected int getFirstVisibleRowNumber() {
		int y = panel.getVisibleRect().y;
		int row = getRowNumberAt(y, false);
		row = Math.max(row, 0);
		return row;
	}

	protected abstract int getGridApiColumnsSize();

	protected abstract int getGridApiRowsSize();

	protected int getGridHeight() {
		int height = getGridApiRowsSize() * segmentHeight + getTopMarigin()
				+ getBottomMarigin();

		if (isLayoutHex()) {
			height = height + segmentHeight / 2;
		}

		return height;
	}

	protected int getGridWidth() {
		int width = getGridApiColumnsSize() * segmentWidth + getLeftMarigin()
				+ getRightMarigin();
		return width;
	}

	protected abstract MapObject getMapObject(int row, int col);

	protected abstract MapObject getCustomMapObject(int row, int col);

	protected int getLastVisibleColumnNumber() {
		Rectangle rectangle = panel.getVisibleRect();
		int x = rectangle.x + rectangle.width;
		int column = getColumnNumberAt(x);
		column = Math.min(column, getGridApiColumnsSize() - 1);
		return column;
	}

	protected int getLastVisibleRowNumber() {
		Rectangle rectangle = panel.getVisibleRect();
		int y = rectangle.y + rectangle.height;
		int row = getRowNumberAt(y, true);
		row = Math.min(row, getGridApiRowsSize() - 1);
		return row;
	}

	protected int getLeftMarigin() {
		return LEFT_MARIGIN;
	}

	public JLayeredPane getPanel() {
		return panel;
	}

	protected int getRightMarigin() {
		return RIGHT_MARIGIN;
	}

	private int getRowNumberAt(int y, boolean evenColumn) {
		// even - parzysty - shifted down
		if (evenColumn && isLayoutHex()) {
			y = y - segmentHeight / 2;
		}
		int row = y - getTopMarigin();

		if (row < 0) {
			row = -1;
		} else {
			row = row / segmentHeight;
		}

		return row;
	}

	public JScrollPane getScrollPane() {
		return scrollPane;
	}

	public Point getSegmentPointAtCursor(Point cur) {
		/*
		 * parametr cur - wspolrzedne kursora myszy na MapPanelu; zwraca kolumne
		 * i wiersz segmentu ktory wskazywany jest przez kursor. Zwraca
		 * Point(-1,-1) jezeli kursor wyjdzie poza mape
		 */

		int column = getColumnNumberAt(cur.x);
		int row = 0;

		if (isLayoutHex() && column % 2 == 1) {
			// first column is 0!!
			// So column nr 1 is even column (parzysta)
			row = getRowNumberAt(cur.y, true); // even - parzysty
		} else {
			row = getRowNumberAt(cur.y, false); // odd - nieparzysty
		}

		if ((column >= getGridApiColumnsSize())
				|| (row >= getGridApiRowsSize()) || (column < 0) || (row < 0)) {
			return new Point(-1, -1);
		}

		return new Point(column, row);
	}

	private LinkedList<Point> getVerticalLineSegments(Point leftPoint,
			Point rightPoint) {
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
			Point segPoint = this.getSegmentPointAtCursor(curPoint);
			result.add(segPoint);

			curX += segmentWidth;
		}

		Point segPoint = this.getSegmentPointAtCursor(rightPoint);
		if (!result.contains(segPoint)) {
			result.add(segPoint);
		}
		return result;

	}

	public LinkedList<LinkedList<CopyPasteSegment>> getSegmentPoints(
			Point firstPoint, Point lastPoint) {

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
						+ firstSegmentPoint.x);
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

	private Point getMinPoint(Point first, Point last) {
		Point point = new Point(Math.min(first.x, last.x), Math.min(first.y,
				last.y));
		return point;
	}

	private Point getMaxPoint(Point first, Point last) {
		Point point = new Point(Math.max(first.x, last.x), Math.max(first.y,
				last.y));
		return point;
	}

	protected int getTopMarigin() {
		return TOP_MARIGIN;
	}

	protected boolean isLayoutHex() {
		return false;
	}

	public void paint(Graphics graphics) {

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
					drawSegment(graphics, column, row, 1);
				} else {
					drawSegment(graphics, column, row, divider);
				}
			}
		}

		int mapWidth = getGridWidth();
		int mapHeight = getGridHeight();

		panel.setPreferredSize(new Dimension(mapWidth, mapHeight));
		panel.revalidate();

	}

	public void refresh() {
		panel.repaint();
	}
}
