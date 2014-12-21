package mapeditor.mainwindow;

import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

public class MainWindowKeyListener implements KeyListener {

	private MapPanel mapPanel;
	private ThemePanel themePanel;

	public MainWindowKeyListener(MapPanel mapPanel, ThemePanel themePanel) {
		this.mapPanel = mapPanel;
		this.themePanel = themePanel;
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
			themePanel.refresh();
		}
	}

	@Override
	public void keyReleased(KeyEvent arg0) {
	}

}
