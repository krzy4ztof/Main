package mapeditor.mainwindow;

import java.awt.Point;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import mapeditor.themesapi.MapObject;
import mapeditor.themesapi.ThemesManager;

public class ThemePanelMouseListener implements MouseListener {

	private ThemesPane themesPane;
	private ThemesManager themesManager;

	ThemePanelMouseListener(ThemesManager themesManager, ThemesPane themesPane) {
		this.themesPane = themesPane;
		this.themesManager = themesManager;
	}

	@Override
	public void mouseClicked(MouseEvent event) {
		/*
		 * pojedyncze klikniecie. e.getButton(): 1 - dla lewego (rysuje ikone),
		 * 3 - dla prawego przycisku (menu atrybutow)
		 */
		Object component = event.getComponent();
		System.out.println("SEL !" + component.getClass().getName());

		if (component instanceof GridPane) {
			System.out.println("SEL !!!!" + component);
		}

		SingleThemePane themePane = themesPane.getActiveThemePanel();

		Point seg = themePane.getSegmentPointAtCursor(event.getPoint());

		if (seg.x != -1) {
			if (event.getButton() == MouseEvent.BUTTON1) {
				System.out.println("TP Mouse Listener");
				System.out.println(seg);
				MapObject mapObject = themePane.getTheme().getMapObject(seg.y,
						seg.x);

				if (mapObject != null) {
					themesPane.setSelectedMapObject(mapObject);
					themesManager.setSelectedMapObject(mapObject);
				}

				// MapObject mapObject = mapThemesManager.getSelectedTheme()
				// .getSelectedObject();
				// mapApi.getSegment(seg.y, seg.x).setMapObject(mapObject);

				// themesPane.getActiveThemePanel().refresh();

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
