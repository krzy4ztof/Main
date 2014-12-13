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
		if (code == KeyEvent.VK_DOWN)
			mapPanel.MoveMap(0, 1);
		else if (code == KeyEvent.VK_RIGHT)
			mapPanel.MoveMap(1, 0);
		else if (code == KeyEvent.VK_LEFT)
			mapPanel.MoveMap(-1, 0);
		else if (code == KeyEvent.VK_UP)
			mapPanel.MoveMap(0, -1);
		else if (code == KeyEvent.VK_ADD)
			mapPanel.ZoomMapIn();
		else if (code == KeyEvent.VK_SUBTRACT)
			mapPanel.ZoomMapOut();
	}

	@Override
	public void keyReleased(KeyEvent arg0) {
	}

}
