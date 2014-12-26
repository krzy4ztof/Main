package mapeditor.mainwindow;

import java.awt.Point;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionListener;

import mapeditor.mapapi.MapApi;
import mapeditor.mapapi.Tools;
import mapeditor.themesapi.MapObject;
import mapeditor.themesapi.ThemesManager;

public class MapPanelMouseMotionListener implements MouseMotionListener {

	private MapPanel mapPanel;
	private ThemesManager mapThemesManager;
	private MapApi mapApi;
	private Tools tools;

	MapPanelMouseMotionListener(MapPanel mapPanel,
			ThemesManager mapThemesManager, MapApi mapApi, Tools tools) {
		this.mapPanel = mapPanel;
		this.mapThemesManager = mapThemesManager;
		this.mapApi = mapApi;
		this.tools = tools;
	}

	@Override
	public void mouseDragged(MouseEvent e) {
		/*
		 * przesuwanie myszy ze wcisni�tym przyciskiem e.getButton() - zawsze
		 * daje 0
		 */
		Point seg = mapPanel.getSegmentPointAtCursor(e.getPoint());
		if (seg.x != -1) {
			switch (tools.getActiveTool()) {
			case BRUSH:
				MapObject mapObject = mapThemesManager.getSelectedMapObject();
				mapApi.getSegment(seg.y, seg.x).setMapObject(mapObject);
				mapPanel.refresh();
				break;
			case ERASER:
				mapObject = tools.getBlankMapObject();
				mapApi.getSegment(seg.y, seg.x).setMapObject(mapObject);
				mapPanel.refresh();
				break;
			default:

			}
		}
	}

	@Override
	public void mouseMoved(MouseEvent e) {
	}

}
