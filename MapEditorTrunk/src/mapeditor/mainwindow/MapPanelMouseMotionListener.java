package mapeditor.mainwindow;

import java.awt.Cursor;
import java.awt.Point;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionListener;

import mapeditor.mapapi.CopyPaste;
import mapeditor.mapapi.CopyPaste.CopyPasteCursor;
import mapeditor.mapapi.MapApi;
import mapeditor.mapapi.Tools;
import mapeditor.mapapi.Tools.ToolsEnum;
import mapeditor.themesapi.MapObject;
import mapeditor.themesapi.MapObjectFactory;
import mapeditor.themesapi.ThemesManager;

public class MapPanelMouseMotionListener implements MouseMotionListener {

	private MapPane mapPanel;
	private ThemesManager mapThemesManager;
	private MapApi mapApi;
	private MapObjectFactory mapObjectFactory;
	private Tools tools;
	private CopyPaste copyPaste;

	MapPanelMouseMotionListener(MapPane mapPanel,
			ThemesManager mapThemesManager, MapApi mapApi, Tools tools,
			MapObjectFactory mapObjectFactory, CopyPaste copyPaste) {
		this.mapPanel = mapPanel;
		this.mapThemesManager = mapThemesManager;
		this.mapApi = mapApi;
		this.tools = tools;
		this.mapObjectFactory = mapObjectFactory;
		this.copyPaste = copyPaste;
	}

	@Override
	public void mouseDragged(MouseEvent e) {
		/*
		 * Moving mouse with pressed button. e.getButton() - is always 0
		 */
		Point seg = mapPanel.getSegmentPointAtCursor(e.getPoint(),
				mapApi.getActiveLayerIndex());
		if (seg.x != -1) {
			switch (tools.getActiveTool()) {
			case BRUSH:
				MapObject mapObject = mapThemesManager.getSelectedMapObject();
				mapApi.getSegment(seg.y, seg.x).setMapObject(mapObject,
						mapApi.getActiveLayerIndex());
				mapPanel.refresh();
				break;
			case ERASER:
				mapObject = mapObjectFactory.getBlankMapObject();
				mapApi.getSegment(seg.y, seg.x).setMapObject(mapObject,
						mapApi.getActiveLayerIndex());
				mapPanel.refresh();
				break;
			case SELECTION:
				ToolsEnum activeTool = tools.getActiveTool();
				if (activeTool == ToolsEnum.SELECTION) {
					copyPaste.onMouseDragged(e.getPoint());

					mapPanel.refresh();
				}
				break;
			default:

			}
		}
	}

	@Override
	public void mouseMoved(MouseEvent e) {
		Point seg = mapPanel.getSegmentPointAtCursor(e.getPoint(),
				mapApi.getActiveLayerIndex());
		if (seg.x != -1) {
			switch (tools.getActiveTool()) {
			case SELECTION:
				copyPaste.onMouseMoved(e.getPoint());

				CopyPasteCursor cursor = copyPaste.getCopyPasteCursor();
				int cursorType = mapPanel.getPanel().getCursor().getType();
				if (cursor == CopyPasteCursor.CROSS
						&& cursorType != Cursor.CROSSHAIR_CURSOR) {
					mapPanel.getPanel()
							.setCursor(
									Cursor.getPredefinedCursor(Cursor.CROSSHAIR_CURSOR));
				} else if (cursor == CopyPasteCursor.HAND
						&& cursorType != Cursor.HAND_CURSOR) {
					mapPanel.getPanel().setCursor(
							Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
				}
				mapPanel.refresh();
				break;
			default:

			}
		}
	}
}
