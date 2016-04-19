package mapeditor.mainwindow.themes;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.Paint;
import java.awt.Point;
import java.awt.Stroke;

import mapeditor.mainwindow.GridPane;
import mapeditor.themesapi.MapObject;
import mapeditor.themesapi.ThemeApi;

public class SingleThemePane extends GridPane {

	public static int LEFT_MARIGIN = 10;
	public static int RIGHT_MARIGIN = 10;
	private static int TOP_MARIGIN = 10;
	private static int BOTTOM_MARIGIN = 10;

	private ThemeApi themeApi;

	public SingleThemePane(ThemeApi themeApi) {
		super();
		this.themeApi = themeApi;
	}

	@Override
	protected int getGridApiColumnsSize() {
		return themeApi.getColumnsSize();
	};

	@Override
	protected int getGridApiRowsSize() {
		return themeApi.getRowsSize();
	};

	protected MapObject getMapObject(int row, int col) {

		MapObject mapObject = themeApi.getMapObject(row, col);

		return mapObject;
	}

	@Override
	protected int getLeftMarigin() {
		return LEFT_MARIGIN;
	}

	@Override
	protected int getRightMarigin() {
		return RIGHT_MARIGIN;
	}

	@Override
	protected int getTopMarigin() {
		return TOP_MARIGIN;
	}

	@Override
	protected int getBottomMarigin() {
		return BOTTOM_MARIGIN;
	}

	public ThemeApi getTheme() {
		return themeApi;
	}

	private void drawSegment(Graphics graphics, int column, int row, int divider) {
		MapObject mapObject = getMapObject(row, column);
		if (mapObject != null) {
			Image image = mapObject.getImageIcon().getImage();
			drawSegment(graphics, column, row, divider, image);

			int currentHeight = row * segmentHeight
					+ (segmentHeight - segmentHeight / divider);

			if (graphics instanceof Graphics2D) {
				Graphics2D g2 = (Graphics2D) graphics;
				g2.drawRect(column * segmentWidth + getLeftMarigin(),
						currentHeight + getTopMarigin(), segmentWidth,
						segmentHeight);
			} else {
				for (int i = 0; i < 3; i++) {
					graphics.drawOval(column * segmentWidth + getLeftMarigin()
							+ i, currentHeight + getTopMarigin() + i,
							segmentWidth - 2 * i, segmentHeight - 2 * i);
				}
			}

		}
	}

	protected void drawSegment(Graphics graphics, int column, int row,
			int divider, Image image) {

		int currentHeight = row * segmentHeight
				+ (segmentHeight - segmentHeight / divider);

		graphics.drawRect(column * segmentWidth + getLeftMarigin(),
				currentHeight + getTopMarigin(), segmentWidth, segmentHeight);

		graphics.drawImage(image, column * segmentWidth + getLeftMarigin(),
				currentHeight + getTopMarigin(), segmentWidth, segmentHeight,
				panel);
	}

	@Override
	public void paint(Graphics graphics) {

		int divider = 1;
		if (isLayoutHex()) {
			divider = 2;
		}

		int firstColumn = getFirstVisibleColumnNumber();// + 1;
		int lastColumn = getLastVisibleColumnNumber();// - 1;
		int firstRow = getFirstVisibleRowNumber();// + 1;
		int lastRow = getLastVisibleRowNumber();// - 1;

		Paint paint = getPaint();
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

	public Point getSegmentPointAtCursor(Point cur) {
		/*
		 * cur - mouse cursor MapPanel coordinates. Returns number of segment
		 * column and row that cursor points. Returns Point(-1,-1) when cursor
		 * is out of map boundaries
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

}
