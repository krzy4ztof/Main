package mapeditor.mainwindow;

import java.awt.event.FocusEvent;
import java.awt.event.FocusListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

public class KeyboardManager implements KeyListener, FocusListener {
	
	private GraphicsSystem graphicsSystem;
	
	public KeyboardManager(GraphicsSystem grs) {
		// TODO Auto-generated constructor stub
		graphicsSystem = grs;
	}

	public void keyTyped(KeyEvent arg0) {
		// TODO Auto-generated method stub
		System.out.println("KeyEvent KeyTyped"+arg0);
	}

	public void keyPressed(KeyEvent e) {
		int code = e.getKeyCode();
		if (code == KeyEvent.VK_DOWN)
			graphicsSystem.MoveMapAction(0,1);
		else if (code == KeyEvent.VK_RIGHT)
			graphicsSystem.MoveMapAction(1,0);
		else if (code == KeyEvent.VK_LEFT)
			graphicsSystem.MoveMapAction(-1,0);
		else if (code == KeyEvent.VK_UP)
			graphicsSystem.MoveMapAction(0,-1);
		else if (code == KeyEvent.VK_ADD)
			graphicsSystem.ZoomMapInAction();
		else if (code == KeyEvent.VK_SUBTRACT)
			graphicsSystem.ZoomMapOutAction();
		
	}

	public void keyReleased(KeyEvent arg0) {
		// TODO Auto-generated method stub
		System.out.println("KeyEvent KeyReleased"+arg0);
	}

	public void focusGained(FocusEvent arg0) {
		// TODO Auto-generated method stub
		System.out.println("focus Gained"+arg0);
		
	}

	public void focusLost(FocusEvent arg0) {
		// TODO Auto-generated method stub
		System.out.println("focus Lost"+arg0);
		
	}

}
