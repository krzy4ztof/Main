package mapeditor.mainwindow;

import java.awt.Point;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import mapeditor.mapapi.MapApi;
import mapeditor.themesapi.MapObject;
import mapeditor.themesapi.ThemesManager;

public class MapPanelMouseListener implements MouseListener {

	private MapPanel mapPanel;
	// private GraphicsSystem graphicsSystem;
	private MapApi mapApi;
	private ThemesManager mapThemesManager;

	MapPanelMouseListener(MapPanel mapPanel, ThemesManager mapThemesManager,
			MapApi mapApi) {
		this.mapPanel = mapPanel;
		this.mapThemesManager = mapThemesManager;
		this.mapApi = mapApi;
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
				// MapObject mapObject = graphicsSystem.getSelectedMapObject();
				// MapObject mapObject = bmpPanel.getSelectedMapObject();
				// MapObject mapObject = mapThemesManager.getSelectedTheme()
				// .getSelectedObject();

				MapObject mapObject = mapThemesManager.getSelectedMapObject();

				mapApi.getSegment(seg.y, seg.x).setMapObject(mapObject);

				mapPanel.refresh();
				// mapPanel.getPanel().repaint();
				// mapPanel.paint();

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
