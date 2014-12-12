package mapeditor.dialogs;

import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;

public class SegmentAttributesWindowListener implements WindowListener {
	@Override
	public void windowOpened(WindowEvent arg0) {
		// TODO Auto-generated method stub
		System.out.println("windowOpened okno atrybut�w");
	}

	@Override
	public void windowClosing(WindowEvent arg0) {
		// TODO Auto-generated method stub
		System.out.println("windowClosing okno atrybut�w");
	}

	@Override
	public void windowClosed(WindowEvent arg0) {
		System.out.println("windowClosed okno atrybut�w");

	}

	@Override
	public void windowIconified(WindowEvent arg0) {
		// TODO Auto-generated method stub
		System.out.println("windowIconified okno atrybut�w");
	}

	@Override
	public void windowDeiconified(WindowEvent arg0) {
		// TODO Auto-generated method stub
		System.out.println("windowDeiconified okno atrybut�w");
	}

	@Override
	public void windowActivated(WindowEvent arg0) {
		// TODO Auto-generated method stub
		System.out.println("windowActivated okno atrybut�w");
	}

	@Override
	public void windowDeactivated(WindowEvent arg0) {
		// TODO Auto-generated method stub
		System.out.println("windowDeactivated okno atrybut�w");
	}
}
