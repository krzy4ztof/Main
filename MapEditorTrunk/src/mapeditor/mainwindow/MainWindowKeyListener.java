package mapeditor.mainwindow;

import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

public class MainWindowKeyListener implements KeyListener {

	private MapPanel mapPanel;
	private ThemesPane themesPane;

	public MainWindowKeyListener(MapPanel mapPanel, ThemesPane themesPane) {
		this.mapPanel = mapPanel;
		this.themesPane = themesPane;
	}

	@Override
	public void keyTyped(KeyEvent arg0) {
	}

	@Override
	public void keyPressed(KeyEvent event) {
		int code = event.getKeyCode();

		if (code == KeyEvent.VK_ADD) {
			mapPanel.zoomMapIn();
		} else if (code == KeyEvent.VK_SUBTRACT) {
			mapPanel.zoomMapOut();
		} else if (code == KeyEvent.VK_MULTIPLY) {
			mapPanel.centerMap();
		} else if (code == KeyEvent.VK_F5) {
			mapPanel.refresh();
			themesPane.getActiveThemePanel().refresh();
		}
	}

	@Override
	public void keyReleased(KeyEvent arg0) {
	}

}
