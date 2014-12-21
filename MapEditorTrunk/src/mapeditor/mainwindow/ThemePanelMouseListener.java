package mapeditor.mainwindow;

import java.awt.Point;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

public class ThemePanelMouseListener implements MouseListener {

	private ThemePanel themePanel;

	ThemePanelMouseListener(ThemePanel themePanel) {
		this.themePanel = themePanel;
	}

	@Override
	public void mouseClicked(MouseEvent e) {
		/*
		 * pojedyncze klikniecie. e.getButton(): 1 - dla lewego (rysuje ikone),
		 * 3 - dla prawego przycisku (menu atrybutow)
		 */
		Point seg = themePanel.getSegmentPointAtCursor(e.getPoint());

		if (seg.x != -1) {
			if (e.getButton() == MouseEvent.BUTTON1) {

				// MapObject mapObject = mapThemesManager.getSelectedTheme()
				// .getSelectedObject();
				// mapApi.getSegment(seg.y, seg.x).setMapObject(mapObject);

				themePanel.refresh();

			} else {

				// mapPanel.r_SegmentAttributesPanel.setVisible(true);
				System.out.println("menu atrybutow");
			}
		}
	}

	@Override
	public void mouseEntered(MouseEvent arg0) {
		// TODO Auto-generated method stub

	}

	@Override
	public void mouseExited(MouseEvent arg0) {
		// TODO Auto-generated method stub

	}

	@Override
	public void mousePressed(MouseEvent arg0) {
		// TODO Auto-generated method stub

	}

	@Override
	public void mouseReleased(MouseEvent arg0) {
		// TODO Auto-generated method stub

	}

}
