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
import javax.swing.JPanel;

import mapeditor.dialogs.SegmentAttributesPanel;
import mapeditor.mapapi.MapApi;
import mapeditor.themesapi.MapObject;
import otherprods.ExampleFileFilter;

public class MapPanel extends JPanel {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	private static int MARIGIN = 10;

	private static final int DEFAULT_SEGMENT_WIDTH = 40;

	private static final int DEFAULT_SEGMENT_HEIGHT = 40;

	ExampleFileFilter fe;

	private int segmentWidth = DEFAULT_SEGMENT_WIDTH;
	private int segmentHeight = DEFAULT_SEGMENT_HEIGHT;

	private ImageIcon blank = new ImageIcon("");
	/* pusta ikona - dla niewypelionych segmentow mapy */
	SegmentAttributesPanel r_SegmentAttributesPanel = new SegmentAttributesPanel();
	private MapApi mapApi;

	public MapPanel(MapApi mapApiParam) {
		super();
		mapApi = mapApiParam;
	}

	public void setMapApi(MapApi mapApi) {
		this.mapApi = mapApi;
	}

	public void centerMap() {
		Rectangle r = getVisibleRect();

		int centerX = this.getMapWidth() / 2;
		int centerY = this.getMapHeight() / 2;

		int newX = centerX - r.width / 2;
		int newY = centerY - r.height / 2;

		Rectangle newRectangle = new Rectangle(newX, newY, r.width, r.height);

		scrollRectToVisible(newRectangle);

		this.repaint();
	}

	public void zoomMapIn() {
		Rectangle rectangle = getVisibleRect();
		int oldMapWidth = this.getMapWidth();
		int oldMapHeight = this.getMapHeight();

		segmentHeight += 5;
		segmentWidth += 5;

		scrollMapToNewView(rectangle, oldMapWidth, oldMapHeight);
	}

	public void zoomMapOut() {
		Rectangle rectangle = getVisibleRect();
		int oldMapWidth = this.getMapWidth();
		int oldMapHeight = this.getMapHeight();

		segmentHeight -= 5;
		segmentWidth -= 5;
		if (segmentHeight < 5) {
			segmentHeight = 5;
		}
		if (segmentWidth < 5) {
			segmentWidth = 5;
		}
		scrollMapToNewView(rectangle, oldMapWidth, oldMapHeight);
	}

	private void scrollMapToNewView(Rectangle oldRectangle, int oldMapWidth,
			int oldMapHeight) {
		double resizeX = (double) getMapWidth() / oldMapWidth;
		double resizeY = (double) getMapHeight() / oldMapHeight;

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
		scrollRectToVisible(newRectangle);
		repaint();

	}

	public void setDefaultMapZoom() {
		Rectangle rectangle = getVisibleRect();
		int oldMapWidth = this.getMapWidth();
		int oldMapHeight = this.getMapHeight();

		segmentHeight = DEFAULT_SEGMENT_HEIGHT;
		segmentWidth = DEFAULT_SEGMENT_WIDTH;

		scrollMapToNewView(rectangle, oldMapWidth, oldMapHeight);
	}

	@Override
	public void paint(Graphics g) {
		super.paint(g);

		drawMap(g);
		int mapWidth = getMapWidth();
		int mapHeight = getMapHeight();

		setPreferredSize(new Dimension(mapWidth, mapHeight));
		revalidate();
	}

	private Image getImage(int row, int col) {
		/*
		 * zwraca ImageIcon danego segmentu mapy. Parametry: col - kolumna, row
		 * - rzad
		 */

		MapObject mapObject = null;

		mapObject = mapApi.getSegment(row, col).getMapObject();
		if (mapObject != null) {
			return mapObject.getImageIcon().getImage();
		} else {
			return this.blank.getImage();
		}
	}

	/**
	 * Draws Map
	 * 
	 * @param graphics
	 */
	private void drawMap(Graphics graphics) {

		int divider = 1;
		if (mapApi.isLayoutHex()) {
			divider = 2;
		}

		for (int column = 0; column < mapApi.getColumnsSize(); column++) {
			for (int row = 0; row < mapApi.getRowsSize(); row++) {
				if (((column) % 2) == 0) {
					drawSegment(graphics, column, row, 1);
				} else {
					drawSegment(graphics, column, row, divider);
				}
			}
		}
	}

	private int getMapWidth() {
		int width = mapApi.getColumnsSize() * segmentWidth + 2 * MARIGIN;
		return width;
	}

	private int getMapHeight() {
		int height = mapApi.getRowsSize() * segmentHeight + 2 * MARIGIN;

		if (mapApi.isLayoutHex()) {
			height = height + segmentHeight / 2;
		}

		return height;
	}

	private void drawSegment(Graphics graphics, int column, int row, int divider) {

		int currentHeight = row * segmentHeight
				+ (segmentHeight - segmentHeight / divider);

		graphics.setColor(Color.LIGHT_GRAY);
		graphics.drawRect(column * segmentWidth + MARIGIN, currentHeight
				+ MARIGIN, segmentWidth, segmentHeight);
		graphics.drawImage(getImage(row, column), column * segmentWidth
				+ MARIGIN, currentHeight + MARIGIN, segmentWidth,
				segmentHeight, getBackground(), this);

		if (graphics instanceof Graphics2D) {
			Graphics2D g2 = (Graphics2D) graphics;
			int firstX = column * segmentWidth + MARIGIN + 2;
			int firstY = currentHeight + MARIGIN + 2;
			int secondX = firstX + segmentWidth - 4;
			int secondY = firstY + segmentHeight - 4;

			g2.setPaint(new GradientPaint(firstX, firstY, Color.BLUE, secondX,
					secondY, Color.YELLOW));

			g2.setStroke(new BasicStroke(3.0f));
			g2.drawRect(column * segmentWidth + MARIGIN + 2, currentHeight
					+ MARIGIN + 2, segmentWidth - 4, segmentHeight - 4);

		} else {
			graphics.setColor(Color.YELLOW);

			for (int i = 0; i < 3; i++) {
				graphics.drawOval(column * segmentWidth + MARIGIN + i,
						currentHeight + MARIGIN + i, segmentWidth - 2 * i,
						segmentHeight - 2 * i);
			}
		}
	}

	Point CursorAtSegment(Point cur) {
		/*
		 * parametr cur - wspolrzedne kursora myszy na MapPanelu; zwraca kolumne
		 * i wiersz segmentu ktory wskazywany jest przez kursor. Zwraca
		 * Point(-1,-1) jezeli kursor wyjdzie poza mape
		 */
		int column = cur.x / segmentWidth;
		int row = cur.y / segmentHeight;
		int maxCol = mapApi.getColumnsSize();
		int maxRow = mapApi.getRowsSize();

		if (column % 2 == 1) {
			if (mapApi.isLayoutHex()) {
				row = (cur.y - segmentHeight / 2) / segmentHeight;
				System.out.println("row: " + row);
			} else {

			}
		}

		if (mapApi.isLayoutHex()) {
			if ((column % 2 == 1) && (cur.y < segmentHeight / 2)) {
				return new Point(-1, -1);// odd row, top marigin
			}
		}

		if ((column >= maxCol) || (row >= maxRow) || (column < 0) || (row < 0)) {
			return new Point(-1, -1);
		}

		System.out.println("col: " + column + " row: " + row);

		return new Point(column, row);
	}
}
