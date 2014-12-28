package mapeditor.dialogs;

import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;

public class SegmentAttributesWindowListener implements WindowListener {
	@Override
	public void windowOpened(WindowEvent arg0) {
		// TODO Auto-generated method stub
		System.out.println("windowOpened okno atrybutow");
	}

	@Override
	public void windowClosing(WindowEvent arg0) {
		// TODO Auto-generated method stub
		System.out.println("windowClosing okno atrybutow");
	}

	@Override
	public void windowClosed(WindowEvent arg0) {
		System.out.println("windowClosed okno atrybutow");

	}

	@Override
	public void windowIconified(WindowEvent arg0) {
		// TODO Auto-generated method stub
		System.out.println("windowIconified okno atrybutow");
	}

	@Override
	public void windowDeiconified(WindowEvent arg0) {
		// TODO Auto-generated method stub
		System.out.println("windowDeiconified okno atrybutow");
	}

	@Override
	public void windowActivated(WindowEvent arg0) {
		// TODO Auto-generated method stub
		System.out.println("windowActivated okno atrybutow");
	}

	@Override
	public void windowDeactivated(WindowEvent arg0) {
		// TODO Auto-generated method stub
		System.out.println("windowDeactivated okno atrybutow");
	}
}
