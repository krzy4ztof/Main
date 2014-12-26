package mapeditor.mainwindow;

import java.awt.Point;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionListener;

import mapeditor.mapapi.MapApi;
import mapeditor.themesapi.MapObject;
import mapeditor.themesapi.ThemesManager;

public class MapPanelMouseMotionListener implements MouseMotionListener {

	private MapPanel mapPanel;
	private ThemesManager mapThemesManager;
	private MapApi mapApi;

	MapPanelMouseMotionListener(MapPanel mapPanel,
			ThemesManager mapThemesManager, MapApi mapApi) {
		this.mapPanel = mapPanel;
		this.mapThemesManager = mapThemesManager;
		this.mapApi = mapApi;
	}

	@Override
	public void mouseDragged(MouseEvent e) {
		/*
		 * przesuwanie myszy ze wcisni�tym przyciskiem e.getButton() - zawsze
		 * daje 0
		 */
		Point seg = mapPanel.getSegmentPointAtCursor(e.getPoint());
		if (seg.x != -1) {
			// MapObject mapObject = bmpPanel.getSelectedMapObject();
			// MapObject mapObject = mapThemesManager.getSelectedTheme()
			// .getSelectedObject();

			MapObject mapObject = mapThemesManager.getSelectedMapObject();
			mapApi.getSegment(seg.y, seg.x).setMapObject(mapObject);

			mapPanel.getPanel().repaint();
		}
	}

	@Override
	public void mouseMoved(MouseEvent e) {
	}

}
