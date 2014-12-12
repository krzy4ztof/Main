package mapeditor.mainwindow;

import java.awt.Point;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import mapeditor.mapapi.MapApi;
import mapeditor.mapapi.MapObject;

public class MapPanelMouseListener implements MouseListener {

	private MapPanel mapPanel;
	private GraphicsSystem graphicsSystem;
	private MapApi mapApi;

	MapPanelMouseListener(MapPanel mapPanel, GraphicsSystem graphicsSystem,
			MapApi mapApi) {
		this.mapPanel = mapPanel;
		this.graphicsSystem = graphicsSystem;
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
				MapObject mapObject = graphicsSystem.getSelectedMapObject();
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
