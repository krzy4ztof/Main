package mapeditor.mainwindow;

import java.awt.Point;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionListener;

import mapeditor.mapapi.MapApi;
import mapeditor.themesapi.MapObject;
import mapeditor.themesapi.MapThemesManager;

public class MapPanelMouseMotionListener implements MouseMotionListener {

	private MapPanel mapPanel;
	private MapThemesManager mapThemesManager;
	private MapApi mapApi;

	MapPanelMouseMotionListener(MapPanel mapPanel,
			MapThemesManager mapThemesManager, MapApi mapApi) {
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
		Point seg = mapPanel.CursorAtSegment(e.getPoint());
		if (seg.x != -1) {
			// MapObject mapObject = bmpPanel.getSelectedMapObject();
			MapObject mapObject = mapThemesManager.getSelectedTheme()
					.getSelectedObject();
			mapApi.getSegment(seg.y, seg.x).setMapObject(mapObject);

			mapPanel.repaint();
		}
	}

	@Override
	public void mouseMoved(MouseEvent e) {
	}

}
