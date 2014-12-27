package mapeditor.mainwindow;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.GradientPaint;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.Point;
import java.awt.Rectangle;

import javax.swing.ImageIcon;
import javax.swing.JLayeredPane;
import javax.swing.JScrollPane;

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

	private Image blankImage;

	public GridPane() {
		super();
		// this.mapApi = mapApi;
		panel = new JLayeredPane() {

			private static final long serialVersionUID = 1L;

			@Override
			public void paint(Graphics g) {
				super.paint(g);
				GridPane.this.paint(g);
			}
		};

		// panel.setBackground(Color.RED);
		// panel.setBackground(new Color(248, 250, 253));
		panel.setBackground(new Color(238, 238, 238));

		scrollPane = new JScrollPane(panel);

		blankImage = new ImageIcon("").getImage();
	}

	private void drawSegment(Graphics graphics, int column, int row, int divider) {

		MapObject mapObject = getMapObject(row, column);
		if (mapObject == null) {
			System.out.println(this.getClass() + " " + row + "  " + column);

			return;
		}

		Image image = mapObject.getImageIcon().getImage();

		int currentHeight = row * segmentHeight
				+ (segmentHeight - segmentHeight / divider);

		graphics.setColor(Color.LIGHT_GRAY);

		graphics.drawRect(column * segmentWidth + getLeftMarigin(),
				currentHeight + getTopMarigin(), segmentWidth, segmentHeight);
		graphics.drawImage(image, column * segmentWidth + getLeftMarigin(),
				currentHeight + getTopMarigin(), segmentWidth, segmentHeight,
				panel.getBackground(), panel);

		if (graphics instanceof Graphics2D) {
			Graphics2D g2 = (Graphics2D) graphics;
			int firstX = column * segmentWidth + getLeftMarigin() + 2;
			int firstY = currentHeight + getTopMarigin() + 2;
			int secondX = firstX + segmentWidth - 4;
			int secondY = firstY + segmentHeight - 4;

			g2.setPaint(new GradientPaint(firstX, firstY, Color.BLUE, secondX,
					secondY, Color.YELLOW));

			g2.setStroke(new BasicStroke(3.0f));
			g2.drawRect(column * segmentWidth + getLeftMarigin() + 2,
					currentHeight + getTopMarigin() + 2, segmentWidth - 4,
					segmentHeight - 4);

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

	private int getFirstVisibleColumnNumber() {
		int x = panel.getVisibleRect().x;
		int column = getColumnNumberAt(x);
		column = Math.max(column, 0);
		return column;
	}

	private int getFirstVisibleRowNumber() {
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

	private int getLastVisibleColumnNumber() {
		Rectangle rectangle = panel.getVisibleRect();
		int x = rectangle.x + rectangle.width;
		int column = getColumnNumberAt(x);
		column = Math.min(column, getGridApiColumnsSize() - 1);
		return column;
	}

	private int getLastVisibleRowNumber() {
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

		System.out.println("col: " + column + " row: " + row);

		return new Point(column, row);
	}

	protected int getTopMarigin() {
		return TOP_MARIGIN;
	}

	boolean isLayoutHex() {
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

		// System.out.println("FR: " + firstRow + " FC: " + firstColumn +
		// " LR: "
		// + lastRow + " LC: " + lastColumn);

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

	/*
	 * private static int LEFT_MARIGIN = 70; private static int RIGHT_MARIGIN =
	 * 30; private static int TOP_MARIGIN = 80; private static int
	 * BOTTOM_MARIGIN = 60;
	 */

	public void refresh() {
		panel.repaint();
	}

	// protected Image getBlankImage() {
	// return blankImage;
	// }

}
