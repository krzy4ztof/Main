package mapeditor.mainwindow;

import java.awt.event.KeyEvent;

import javax.swing.JPanel;
import javax.swing.JTabbedPane;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import mapeditor.themesapi.MapThemesManager;

public class ThemesTabbedPane {
	private MapThemesManager mapThemesManager;

	private JTabbedPane pane;

	private ThemePanel themePanel;

	public ThemesTabbedPane(MapThemesManager mapThemesManager) {
		super();
		this.mapThemesManager = mapThemesManager;

		themePanel = new ThemePanel(mapThemesManager.getSelectedThemeApi());

		ThemePanelMouseListener tpMouseListener = new ThemePanelMouseListener(
				this);
		themePanel.getPanel().addMouseListener(tpMouseListener);

		pane = new JTabbedPane();
		// ImageIcon icon = createImageIcon("images/middle.gif");

		// JComponent panel1 = makeTextPanel("Panel #1");

		pane.addTab("Tab1", themePanel.getScrollPane());
		pane.setMnemonicAt(0, KeyEvent.VK_1);
		pane.addTab("Tab2", new JPanel());
		pane.setMnemonicAt(1, KeyEvent.VK_2);
		pane.addTab("Tab3", new JPanel());
		pane.setMnemonicAt(2, KeyEvent.VK_3);
		pane.addTab("Tab4", new JPanel());
		pane.setMnemonicAt(3, KeyEvent.VK_4);
		pane.addTab("Tab5", new JPanel());
		pane.setMnemonicAt(4, KeyEvent.VK_5);
		pane.addTab("Tab6", new JPanel());
		pane.setMnemonicAt(5, KeyEvent.VK_6);

		// tabbedPane.addTab("Tab 1", icon, panel1, "Does nothing");
		// tabbedPane.setMnemonicAt(0, KeyEvent.VK_1);
		//

		pane.addChangeListener(new ChangeListener() {

			@Override
			public void stateChanged(ChangeEvent changeEvent) {
				// TODO Auto-generated method stub
				JTabbedPane sourceTabbedPane = (JTabbedPane) changeEvent
						.getSource();
				int index = sourceTabbedPane.getSelectedIndex();
				System.out.println("Tab changed to: "
						+ sourceTabbedPane.getTitleAt(index));
				// System.out.println(changeEvent);
			}
		});

	}

	public JTabbedPane getPane() {
		return pane;
	}

	public ThemePanel getActiveThemePanel() {
		return themePanel;
	}

}
