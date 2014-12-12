package mapeditor.mainwindow;

import java.awt.Point;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionListener;

import mapeditor.mapapi.MapApi;
import mapeditor.mapapi.MapObject;

public class MapPanelMouseMotionListener implements MouseMotionListener {

	private MapPanel mapPanel;
	private GraphicsSystem graphicsSystem;
	private MapApi mapApi;

	MapPanelMouseMotionListener(MapPanel mapPanel,
			GraphicsSystem graphicsSystem, MapApi mapApi) {
		this.mapPanel = mapPanel;
		this.graphicsSystem = graphicsSystem;
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
			BmpPanel p_BmpPanel = graphicsSystem.bmpPanel;
			MapObject mapObject = p_BmpPanel.getSelectedMapObject();
			mapApi.getSegment(seg.y, seg.x).setMapObject(mapObject);

			mapPanel.repaint();
		}
	}

	@Override
	public void mouseMoved(MouseEvent e) {
	}

}
