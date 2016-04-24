package mapeditor.mainwindow.themes;

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
		 * single click. e.getButton(): 1 - left button, 3 - right button
		 */
		SingleThemePane themePane = themesPane.getActiveThemePanel();

		Point seg = themePane.getSegmentPointAtCursor(event.getPoint());

		if (seg.x != -1) {
			if (event.getButton() == MouseEvent.BUTTON1) {
				MapObject mapObject = themePane.getTheme().getMapObject(seg.y,
						seg.x);

				if (mapObject != null) {
					themesPane.setSelectedMapObject(mapObject);
					themesManager.setSelectedMapObject(mapObject);
				}
			}
		}
	}

	@Override
	public void mouseEntered(MouseEvent arg0) {
	}

	@Override
	public void mouseExited(MouseEvent arg0) {
	}

	@Override
	public void mousePressed(MouseEvent arg0) {
	}

	@Override
	public void mouseReleased(MouseEvent arg0) {
	}

}
