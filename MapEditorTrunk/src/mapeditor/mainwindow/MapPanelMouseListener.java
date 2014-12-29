package mapeditor.mainwindow;

import java.awt.Point;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import mapeditor.mapapi.Bucket;
import mapeditor.mapapi.MapApi;
import mapeditor.mapapi.Tools;
import mapeditor.themesapi.MapObject;
import mapeditor.themesapi.MapObjectFactory;
import mapeditor.themesapi.ThemesManager;

public class MapPanelMouseListener implements MouseListener {

	private MapPane mapPanel;
	// private GraphicsSystem graphicsSystem;
	private MapApi mapApi;
	private ThemesManager mapThemesManager;
	private Tools tools;
	private ThemesPane themesPane;
	private MapObjectFactory mapObjectFactory;

	MapPanelMouseListener(MapPane mapPanel, ThemesManager mapThemesManager,
			MapApi mapApi, Tools tools, ThemesPane themesPane,
			MapObjectFactory mapObjectFactory) {
		this.mapPanel = mapPanel;
		this.mapThemesManager = mapThemesManager;
		this.mapApi = mapApi;
		this.tools = tools;
		this.mapObjectFactory = mapObjectFactory;
		this.themesPane = themesPane;
	}

	@Override
	public void mouseEntered(MouseEvent e) {
	}

	@Override
	public void mouseExited(MouseEvent e) {
	}

	@Override
	public void mouseReleased(MouseEvent e) {
	}

	@Override
	public void mouseClicked(MouseEvent e) {
		/*
		 * pojedyncze klikniecie. e.getButton(): 1 - dla lewego (rysuje ikone),
		 * 3 - dla prawego przycisku (menu atrybutow)
		 */
		Point seg = mapPanel.getSegmentPointAtCursor(e.getPoint());

		if (seg.x != -1) {
			if (e.getButton() == MouseEvent.BUTTON1) {

				switch (tools.getActiveTool()) {
				case BRUSH:
					MapObject mapObject = mapThemesManager
							.getSelectedMapObject();
					mapApi.getSegment(seg.y, seg.x).setMapObject(mapObject);
					mapPanel.refresh();
					break;
				case ERASER:
					mapObject = mapObjectFactory.getBlankMapObject();
					mapApi.getSegment(seg.y, seg.x).setMapObject(mapObject);
					mapPanel.refresh();
					break;
				case PICKER:
					mapObject = mapApi.getSegment(seg.y, seg.x).getMapObject();
					System.out.println(":::" + mapObject);

					mapThemesManager.setSelectedMapObject(mapObject);
					themesPane.setSelectedMapObject(mapObject);

				case BUCKET:
					mapObject = mapApi.getSegment(seg.y, seg.x).getMapObject();

					MapObject newObject = mapThemesManager
							.getSelectedMapObject();
					Bucket bucket = new Bucket(mapApi);
					bucket.fill(mapObject, seg);
					bucket.paint(newObject);
					mapPanel.refresh();

					// System.out.println(":::" + mapObject);

				default:

				}

			} else {

				mapPanel.r_SegmentAttributesPanel.setVisible(true);
				System.out.println("menu atrybutow");
			}
		}
	}

	@Override
	public void mousePressed(MouseEvent e) {
	}

}
