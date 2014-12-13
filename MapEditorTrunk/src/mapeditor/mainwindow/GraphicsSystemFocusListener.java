package mapeditor.mainwindow;

import java.awt.event.FocusEvent;
import java.awt.event.FocusListener;

public class GraphicsSystemFocusListener implements FocusListener {

	@Override
	public void focusGained(FocusEvent arg0) {
		System.out.println("focus gained");
	}

	@Override
	public void focusLost(FocusEvent arg0) {
		System.out.println("focus lost");
	}

}
