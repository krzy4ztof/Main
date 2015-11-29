package mapeditor.mainwindow;

import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

public class MainWindowKeyListener implements KeyListener {

	private MapPane mapPanel;
	private ThemesPane themesPane;

	public MainWindowKeyListener(MapPane mapPanel, ThemesPane themesPane) {
		this.mapPanel = mapPanel;
		this.themesPane = themesPane;
	}

	@Override
	public void keyTyped(KeyEvent arg0) {
	}

	@Override
	public void keyPressed(KeyEvent event) {
		int code = event.getKeyCode();
		// System.out.println("KEY CODE: " + code);

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

		if (event.isControlDown()) {
			if (code == KeyEvent.VK_X) {
				System.out.println("VK___CUT");
				mapPanel.onCutEvent();
			} else if (code == KeyEvent.VK_C) {
				mapPanel.onCopyEvent();
				System.out.println("VK___COPY");
			} else if (code == KeyEvent.VK_V) {
				System.out.println("VK___PASTE");
				mapPanel.onPasteEvent();
			}
		}
	}

	@Override
	public void keyReleased(KeyEvent arg0) {
	}

}
