package mapeditor.mainwindow;

import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

public class GraphicsSystemKeyListener implements KeyListener {

	private GraphicsSystem graphicsSystem;
	private MapPanel mapPanel;

	public GraphicsSystemKeyListener(GraphicsSystem grs, MapPanel mapPanel) {
		// TODO Auto-generated constructor stub
		graphicsSystem = grs;
		this.mapPanel = mapPanel;
	}

	@Override
	public void keyTyped(KeyEvent arg0) {
		// TODO Auto-generated method stub
		System.out.println("KeyEvent KeyTyped" + arg0);
	}

	@Override
	public void keyPressed(KeyEvent e) {
		int code = e.getKeyCode();
		if (code == KeyEvent.VK_DOWN)
			// graphicsSystem.MoveMapAction(0, 1);
			mapPanel.MoveMap(0, 1);
		else if (code == KeyEvent.VK_RIGHT)
			// graphicsSystem.MoveMapAction(1, 0);
			mapPanel.MoveMap(1, 0);
		else if (code == KeyEvent.VK_LEFT)
			// graphicsSystem.MoveMapAction(-1, 0);
			mapPanel.MoveMap(-1, 0);
		else if (code == KeyEvent.VK_UP)
			// graphicsSystem.MoveMapAction(0, -1);
			mapPanel.MoveMap(0, -1);
		else if (code == KeyEvent.VK_ADD)
			// graphicsSystem.ZoomMapInAction();
			mapPanel.ZoomMapIn();
		else if (code == KeyEvent.VK_SUBTRACT)
			// graphicsSystem.ZoomMapOutAction();
			mapPanel.ZoomMapOut();
	}

	@Override
	public void keyReleased(KeyEvent arg0) {
		// TODO Auto-generated method stub
		System.out.println("KeyEvent KeyReleased" + arg0);
	}

}
