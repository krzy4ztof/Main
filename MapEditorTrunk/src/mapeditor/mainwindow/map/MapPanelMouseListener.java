package mapeditor.mainwindow.map;

import java.awt.Point;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.util.logging.Level;
import java.util.logging.Logger;

import mapeditor.logger.MapLogger;
import mapeditor.mainwindow.customobject.CustomObjectPane;
import mapeditor.mainwindow.themes.ThemesPane;
import mapeditor.mapapi.Bucket;
import mapeditor.mapapi.CopyPaste;
import mapeditor.mapapi.CustomObjectEdit;
import mapeditor.mapapi.MapApi;
import mapeditor.mapapi.Point3D;
import mapeditor.mapapi.Tools;
import mapeditor.mapapi.Tools.ToolsEnum;
import mapeditor.themesapi.CustomMapObject;
import mapeditor.themesapi.MapObject;
import mapeditor.themesapi.MapObjectFactory;
import mapeditor.themesapi.ThemesManager;

public class MapPanelMouseListener implements MouseListener {

	private static final Logger logger = Logger
			.getLogger(MapPanelMouseListener.class.getName());

	private MapPane mapPanel;
	private MapApi mapApi;
	private ThemesManager mapThemesManager;
	private Tools tools;
	private ThemesPane themesPane;
	private MapObjectFactory mapObjectFactory;
	private CopyPaste copyPaste;
	private CustomObjectPane customObjectPane;
	private CustomObjectEdit customObjectEdit;

	public MapPanelMouseListener(MapPane mapPanel,
			ThemesManager mapThemesManager, MapApi mapApi, Tools tools,
			ThemesPane themesPane, MapObjectFactory mapObjectFactory,
			CopyPaste copyPaste, CustomObjectPane customObjectPane,
			CustomObjectEdit customObjectEdit) {
		this.mapPanel = mapPanel;
		this.mapThemesManager = mapThemesManager;
		this.mapApi = mapApi;
		this.tools = tools;
		this.mapObjectFactory = mapObjectFactory;
		this.themesPane = themesPane;
		this.copyPaste = copyPaste;
		this.customObjectPane = customObjectPane;
		this.customObjectEdit = customObjectEdit;

	}

	@Override
	public void mouseEntered(MouseEvent e) {
	}

	@Override
	public void mouseExited(MouseEvent e) {
	}

	@Override
	public void mouseReleased(MouseEvent e) {
		Point seg = mapPanel.getSegmentPointAtCursor(e.getPoint(),
				mapApi.getActiveLayerIndex());

		if (seg.x != -1) {
			ToolsEnum activeTool = tools.getActiveTool();

			if (activeTool == ToolsEnum.SELECTION) {
				copyPaste.onMouseReleased(e.getPoint());

				mapPanel.refresh();
			}
		}
	}

	@Override
	public void mouseClicked(MouseEvent e) {
		/*
		 * single click e.getButton(): 1 - left button click (rysuje ikone), 3 -
		 * right button click dla prawego przycisku (menu atrybutow)
		 */
		Point seg = mapPanel.getSegmentPointAtCursor(e.getPoint(),
				mapApi.getActiveLayerIndex());

		if (seg.x != -1) {
			if (e.getButton() == MouseEvent.BUTTON1) {
				ToolsEnum activeTool = tools.getActiveTool();
				MapObject mapObject = null;
				CustomMapObject customMapObject = null;
				logger.log(Level.INFO, MapLogger.MOUSE_CLICKED, activeTool);

				if (activeTool == ToolsEnum.BRUSH) {
					mapObject = mapThemesManager.getSelectedMapObject();
					mapApi.getSegment(seg.y, seg.x).setMapObject(mapObject,
							mapApi.getActiveLayerIndex());

					mapPanel.refresh();
				} else if (activeTool == ToolsEnum.ERASER) {
					mapObject = mapObjectFactory.getBlankMapObject();
					mapApi.getSegment(seg.y, seg.x).setMapObject(mapObject,
							mapApi.getActiveLayerIndex());

					mapPanel.refresh();
				} else if (activeTool == ToolsEnum.PICKER) {
					mapObject = mapApi.getSegment(seg.y, seg.x).getMapObject(
							mapApi.getActiveLayerIndex());

					mapThemesManager.setSelectedMapObject(mapObject);
					themesPane.setSelectedMapObject(mapObject);

					// TODO: kopiowanie CustomMapObject
				} else if (activeTool == ToolsEnum.BUCKET) {
					mapObject = mapApi.getSegment(seg.y, seg.x).getMapObject(
							mapApi.getActiveLayerIndex());
					MapObject newObject = mapThemesManager
							.getSelectedMapObject();
					Bucket bucket = new Bucket(mapApi);
					bucket.fill(mapObject, seg, mapApi.getActiveLayerIndex());
					bucket.paint(newObject);

					mapPanel.refresh();
				} else if (activeTool == ToolsEnum.SELECTION) {

					if (e.getClickCount() == 2) {
						copyPaste.onLeftButtonDoubleClick(e.getPoint());
					} else {
						copyPaste.onLeftButtonClick(e.getPoint());
					}

					mapPanel.refresh();
				} else if (activeTool == ToolsEnum.HAMMER) {

					customMapObject = mapApi.getSegment(seg.y, seg.x)
							.getCustomMapObject(mapApi.getActiveLayerIndex());

					if (customMapObject == null) {
						customObjectPane.deactivate();
						customObjectEdit.deactivate();
					} else {

						customObjectPane.update(customMapObject);
						customObjectEdit.setMapSegment(
								mapApi.getSegment(seg.y, seg.x),
								mapApi.getActiveLayerIndex(), seg);
					}
					mapPanel.refresh();
				} else if (activeTool == ToolsEnum.POINT_PROPERTY) {
					Point3D point = new Point3D(seg.x, seg.y,
							mapApi.getActiveLayerIndex());

					customObjectPane.updatePointPropertyControl(point);
					customObjectEdit.setPointPropertyLocation(point);

					mapPanel.refresh();
				}
			}
		}
	}

	@Override
	public void mousePressed(MouseEvent e) {
		Point seg = mapPanel.getSegmentPointAtCursor(e.getPoint(),
				mapApi.getActiveLayerIndex());

		if (seg.x != -1) {
			ToolsEnum activeTool = tools.getActiveTool();

			if (activeTool == ToolsEnum.SELECTION) {
				copyPaste.onMousePressed(e.getPoint());

				mapPanel.refresh();

			}
		}
	}

}
