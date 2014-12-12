package mapeditor.mainwindow;

import java.awt.event.FocusEvent;
import java.awt.event.FocusListener;

public class GraphicsSystemFocusListener implements FocusListener {

	@Override
	public void focusGained(FocusEvent arg0) {
		// TODO Auto-generated method stub
		System.out.println("focus Gained" + arg0);

	}

	@Override
	public void focusLost(FocusEvent arg0) {
		// TODO Auto-generated method stub
		System.out.println("focus Lost" + arg0);

	}

}
