package mapeditor.mainwindow;

import java.awt.Point;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import mapeditor.mapapi.MapApi;
import mapeditor.themesapi.MapObject;
import mapeditor.themesapi.MapThemesManager;

public class MapPanelMouseListener implements MouseListener {

	private MapPanel mapPanel;
	// private GraphicsSystem graphicsSystem;
	private MapApi mapApi;
	private MapThemesManager mapThemesManager;

	MapPanelMouseListener(MapPanel mapPanel, MapThemesManager mapThemesManager,
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
		 * pojedyncze klikniecie. e.getButton(): 1 - dla lewego (rysuje
		 * ikon�), 3 - dla prawego przycisku (menu atrybut�w)
		 */
		Point seg = mapPanel.CursorAtSegment(e.getPoint());

		if (seg.x != -1) {
			if (e.getButton() == 1) {
				// MapObject mapObject = graphicsSystem.getSelectedMapObject();
				// MapObject mapObject = bmpPanel.getSelectedMapObject();
				MapObject mapObject = mapThemesManager.getSelectedTheme()
						.getSelectedObject();
				mapApi.getSegment(seg.y, seg.x).setMapObject(mapObject);

				mapPanel.repaint();
			} else {

				mapPanel.r_SegmentAttributesPanel.setVisible(true);
				System.out.println("menu atrybut�w");
			}
		}
	}

	@Override
	public void mousePressed(MouseEvent e) {
	}

}
