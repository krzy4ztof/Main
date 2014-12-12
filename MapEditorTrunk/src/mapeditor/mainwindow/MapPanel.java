package mapeditor.mainwindow;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.Point;

import javax.swing.ImageIcon;
import javax.swing.JPanel;

import mapeditor.dialogs.SegmentAttributesPanel;
import mapeditor.mapapi.MapApi;
import mapeditor.mapapi.MapObject;
import otherprods.ExampleFileFilter;

public class MapPanel extends JPanel {

	ExampleFileFilter fe;
	private Point LUcornerMap = new Point(0, 0);
	/*
	 * Wsp�rz�dne punktu (segmentu) na mapie znajduj�cego si� w lewym
	 * g�rnym punkcie (segmencie) MapPanelu
	 */
	final int defaultSegmentWidth = 40;
	/* sta�a - domy�lna szeroko�� segmentu */
	private int SegmentWidth = defaultSegmentWidth;
	/* szerokosc segmentu mapy */
	final int defaultSegmentHeight = 40;
	/* sta�a - domy�lna wysoko�� segmentu */
	private int SegmentHeight = defaultSegmentHeight;
	/* wysoko�� segmentu mapy */
	private ImageIcon blank = new ImageIcon("");
	/* pusta ikona - dla niewype�nionych segment�w mapy */
	SegmentAttributesPanel r_SegmentAttributesPanel = new SegmentAttributesPanel();
	private GraphicsSystem graphicsSystem;
	private MapApi mapApi;

	private MapPanelMouseListener mpMouseListener;
	private MapPanelMouseMotionListener mpMouseMotionListener;

	public MapPanel(GraphicsSystem graphicsSystemParam, MapApi mapApiParam) {
		super();
		graphicsSystem = graphicsSystemParam;
		mapApi = mapApiParam;

		mpMouseListener = new MapPanelMouseListener(this, graphicsSystem,
				mapApi);
		mpMouseMotionListener = new MapPanelMouseMotionListener(this,
				graphicsSystem, mapApi);
		addMouseListener(mpMouseListener);
		addMouseMotionListener(mpMouseMotionListener);
	}

	public void setMapApi(MapApi mapApi) {
		this.mapApi = mapApi;
	}

	public void MoveMap(int x, int y) {
		LUcornerMap.x += 2 * x;
		LUcornerMap.y += y;
		this.repaint();
	}

	public void ZoomMapIn() {
		SegmentHeight += 5;
		SegmentWidth += 5;
		this.repaint();
	}

	public void ZoomMapOut() {
		SegmentHeight -= 5;
		SegmentWidth -= 5;
		if (SegmentHeight < 5) {
			SegmentHeight = 5;
		}
		if (SegmentWidth < 5) {
			SegmentWidth = 5;
		}
		this.repaint();
	}

	public void SetDefaultMapZoom() {
		SegmentHeight = defaultSegmentHeight;
		SegmentWidth = defaultSegmentWidth;
		this.repaint();
	}

	@Override
	public void paint(Graphics g) {
		/*
		 * Przechwytuje komunikat o zmianie wielko�ci okna
		 */
		super.paint(g);
		DrawMap(g);
	}

	private Image getImage(int row, int col) {
		/*
		 * zwraca ImageIcon danego segmentu mapy. Parametry: col - kolumna, row
		 * - rz�d
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
	private void DrawMap(Graphics graphics) {
		CorrectMap();// must be invoked as first

		graphics.setColor(Color.RED);

		int divider = 1;
		if (mapApi.isLayoutHex()) {
			divider = 2;
		}

		for (int column = 0; column < HowManyColumns(); column++) {
			for (int row = 0; row < HowManyRows(); row++) {
				if (((LUcornerMap.x + column) % 2) == 0) {
					drawSegment(graphics, column, row, 1);
				} else {
					drawSegment(graphics, column, row, divider);
				}
			}
		}
	}

	private void drawSegment(Graphics graphics, int column, int row, int divider) {
		// int currentHeight = (int) ((row + offset) * SegmentHeight);

		int currentHeight = row * SegmentHeight
				+ (SegmentHeight - SegmentHeight / divider);

		graphics.drawRect(column * SegmentWidth, currentHeight, SegmentWidth,
				SegmentHeight);
		graphics.drawImage(
				this.getImage(row + LUcornerMap.y, column + LUcornerMap.x),
				column * SegmentWidth, currentHeight, SegmentWidth,
				SegmentHeight, getBackground(), this);

		/*
		 * graphics.drawRect(column * SegmentWidth, row * SegmentHeight,
		 * SegmentWidth, SegmentHeight); graphics.drawImage(this.getImage(row +
		 * LUcornerMap.y, column + LUcornerMap.x), column * SegmentWidth, row *
		 * SegmentHeight, SegmentWidth, SegmentHeight, getBackground(), this);
		 */

	}

	private void CorrectMap() {
		/*
		 * koryguje warto�� zmiennej LUcornerMap; wa�ne podczas zmiany
		 * rozmiaru ekranu, te� przy wczytaniu nowej mapy z menu
		 */
		int hmc = HowManyColumns();
		int hmr = HowManyRows();
		int mxc = mapApi.getColumnsSize();
		int mxr = mapApi.getRowsSize();

		if (LUcornerMap.x > mxc - hmc) {
			LUcornerMap.x = mxc - hmc;
		}
		if (LUcornerMap.x < 0) {
			LUcornerMap.x = 0;
		}
		if (LUcornerMap.y > mxr - hmr) {
			LUcornerMap.y = mxr - hmr;
		}
		if (LUcornerMap.y < 0) {
			LUcornerMap.y = 0;
		}

	}

	private int HowManyColumns() {
		/*
		 * zwraca liczb� kolumn mapy jaka ma byc wyswietlona; zale�y od
		 * SegmentWidth i od wielkosci mapy
		 */
		int avCol = getWidth() / SegmentWidth;
		int maxCol = mapApi.getColumnsSize();

		if (avCol <= maxCol) {
			return avCol;
		} else {
			return maxCol;
		}
	}

	private int HowManyRows() {
		/*
		 * zwraca liczb� rz�d�w mapy jaka ma byc wyswietlona; zale�y od
		 * SegmentHeight i od wielkosci mapy
		 */
		int avRow = getHeight() / SegmentHeight;
		int maxRow = mapApi.getRowsSize();
		// System.out.println("avR= "+avRow+" maxR= "+maxRow);
		if (avRow <= maxRow) {
			return avRow;
		} else {
			return maxRow;
		}
	}

	Point CursorAtSegment(Point cur) {
		/*
		 * parametr cur - wsp�rz�dne kursora myszy na MapPanelu; zwraca
		 * kolumn� i wiersz segmentu kt�ry wskazywany jest przez kursor.
		 * Zwraca Point(-1,-1) je�eli kursor wyjdzie poza map�
		 */
		int column = cur.x / SegmentWidth;
		int row = cur.y / SegmentHeight;
		int maxCol = mapApi.getColumnsSize();
		int maxRow = mapApi.getRowsSize();

		column += LUcornerMap.x;
		if (column % 2 == 1) {

			if (mapApi.isLayoutHex()) {
				row = (cur.y - SegmentHeight / 2) / SegmentHeight;
				System.out.println("row: " + row);
				// row = (int) ((cur.y/SegmentHeight)-0.5);

				// row = (int) ()
				// row = cur.y / SegmentHeight - 0.5;
				// row = (cur.y /SegmentHeight - SegmentHeight / 2)

				// int currentHeight = row * SegmentHeight + (SegmentHeight -
				// SegmentHeight / divider);
			} else {

			}
		}
		row += LUcornerMap.y;

		if (mapApi.isLayoutHex()) {
			if ((column % 2 == 1) && (cur.y < SegmentHeight / 2)
					&& (LUcornerMap.y == 0)) {
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
