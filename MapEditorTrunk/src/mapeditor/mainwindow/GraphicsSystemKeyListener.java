package mapeditor.mainwindow;

import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

public class GraphicsSystemKeyListener implements KeyListener {

	private MapPanel mapPanel;

	public GraphicsSystemKeyListener(MapPanel mapPanel) {
		this.mapPanel = mapPanel;
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
		}
	}

	@Override
	public void keyReleased(KeyEvent arg0) {
	}

}
