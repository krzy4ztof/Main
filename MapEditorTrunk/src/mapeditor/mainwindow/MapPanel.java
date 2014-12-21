package mapeditor.mainwindow;

import java.awt.Image;
import java.awt.Rectangle;

import mapeditor.dialogs.SegmentAttributesPanel;
import mapeditor.mapapi.MapApi;
import mapeditor.themesapi.MapObject;
import otherprods.ExampleFileFilter;

public class MapPanel extends GridPanel {

	ExampleFileFilter fe;

	/* pusta ikona - dla niewypelnionych segmentow mapy */
	SegmentAttributesPanel r_SegmentAttributesPanel = new SegmentAttributesPanel();
	private MapApi mapApi;

	public MapPanel(MapApi mapApi) {
		super();
		this.mapApi = mapApi;
	}

	@Override
	boolean isLayoutHex() {
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
	protected Image getImage(int row, int col) {
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
}
