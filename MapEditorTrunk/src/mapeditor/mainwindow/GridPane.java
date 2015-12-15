package mapeditor.mainwindow;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.Paint;
import java.awt.Point;
import java.awt.Rectangle;
import java.awt.Stroke;

import javax.swing.JLayeredPane;
import javax.swing.JScrollPane;

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

	protected int getColumnNumberAt(int x) {
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

	protected int getRowNumberAt(int y, boolean evenColumn) {
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

	protected Point getMinPoint(Point first, Point last) {
		Point point = new Point(Math.min(first.x, last.x), Math.min(first.y,
				last.y));
		return point;
	}

	protected Point getMaxPoint(Point first, Point last) {
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

	public abstract void paint(Graphics graphics);

	public void refresh() {
		panel.repaint();
	}
}
