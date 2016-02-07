package mapeditor.mainwindow.themes;

import java.awt.Component;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Image;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.HashMap;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JLayeredPane;
import javax.swing.JPanel;
import javax.swing.JTabbedPane;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import mapeditor.main.ApplicationManager;
import mapeditor.mainwindow.MainWindow;
import mapeditor.messages.MapMessages;
import mapeditor.themesapi.MapObject;
import mapeditor.themesapi.MapObjectFactory;
import mapeditor.themesapi.ThemeApi;
import mapeditor.themesapi.ThemesManager;

public class ThemesPane {
	// private MapThemesManager mapThemesManager;

	private JLayeredPane pane;

	private JTabbedPane tabbedPane;

	private SingleThemePane themePanel;

	private HashMap<String, SingleThemePane> themePanes;

	private JButton button;

	public ThemesPane(MapMessages messages, ThemesManager mapThemesManager) {
		super();
		// this.mapThemesManager = mapThemesManager;
		themePanes = new HashMap<String, SingleThemePane>();

		pane = new JLayeredPane();
		pane.setLayout(new GridBagLayout());
		GridBagConstraints c = new GridBagConstraints();
		c.fill = GridBagConstraints.BOTH;
		c.weightx = 1.0;
		c.weighty = 1.0;
		c.gridx = 0;
		c.gridy = 0;

		tabbedPane = createTabbedPane(messages, mapThemesManager);
		pane.add(tabbedPane, c);

		c.weightx = 1.0;
		c.weighty = 0.0;
		c.gridx = 0;
		c.gridy = 1;

		JPanel selectionPane = createSelectionPanel();
		pane.add(selectionPane, c);

		/*
		 * int minWidth = SingleThemePane.DEFAULT_SEGMENT_WIDTH
		 * config.getThemeApiColumnsNumber() + 30; minimumSize = new
		 * Dimension(minWidth, 0); panel.setPreferredSize(minimumSize);
		 */
		// pane.setPrefferedSize(new Dimension(300, 200));
	}

	public JComponent getPane() {
		return pane;
	}

	public SingleThemePane getActiveThemePanel() {
		return themePanel;
	}

	private JPanel createSelectionPanel() {
		JPanel selectionPane = new JPanel();

		button = new JButton();
		button.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent event) {
				// TODO Auto-generated method stub
				((JButton) event.getSource()).getTopLevelAncestor()
						.requestFocus();
			}

		});

		// button.setActionCommand(actionCommand);
		// button.setToolTipText(toolTipText);
		String imgLocation = ApplicationManager.THEMES_PATH
				+ MainWindow.ICON_NULL;

		Image image = new ImageIcon(imgLocation).getImage().getScaledInstance(
				MapObjectFactory.DEFAULT_SEGMENT_WIDTH,
				MapObjectFactory.DEFAULT_SEGMENT_HEIGHT, Image.SCALE_DEFAULT);

		button.setIcon(new ImageIcon(image));

		selectionPane.add(button);
		return selectionPane;
	}

	private JTabbedPane createTabbedPane(MapMessages messages,
			ThemesManager mapThemesManager) {
		JTabbedPane tabbedPane = new JTabbedPane();

		ThemePanelMouseListener tpMouseListener = new ThemePanelMouseListener(
				mapThemesManager, this);

		for (ThemeApi themeApi : mapThemesManager.getThemesApis()) {
			SingleThemePane themePanel = new SingleThemePane(themeApi);
			themePanel.getPanel().addMouseListener(tpMouseListener);

			if (themeApi == mapThemesManager.getSelectedThemeApi()) {
				this.themePanel = themePanel;
			}

			String name = messages.getString(MapMessages.THEMENAME
					+ themeApi.getName());

			themePanes.put(name, themePanel);
			tabbedPane.addTab(name, themePanel.getScrollPane());

		}

		// ImageIcon icon = createImageIcon("images/middle.gif");

		// JComponent panel1 = makeTextPanel("Panel #1");
		/*
		 * tabbedPane.addTab("Tab1", themePanel.getScrollPane());
		 * tabbedPane.setMnemonicAt(0, KeyEvent.VK_1); tabbedPane.addTab("Tab2",
		 * new JPanel()); tabbedPane.setMnemonicAt(1, KeyEvent.VK_2);
		 * tabbedPane.addTab("Tab3", new JPanel()); tabbedPane.setMnemonicAt(2,
		 * KeyEvent.VK_3); tabbedPane.addTab("Tab4", new JPanel());
		 * tabbedPane.setMnemonicAt(3, KeyEvent.VK_4); tabbedPane.addTab("Tab5",
		 * new JPanel()); tabbedPane.setMnemonicAt(4, KeyEvent.VK_5);
		 * tabbedPane.addTab("Tab6", new JPanel()); tabbedPane.setMnemonicAt(5,
		 * KeyEvent.VK_6);
		 */
		// tabbedPane.addTab("Tab 1", icon, panel1, "Does nothing");
		// tabbedPane.setMnemonicAt(0, KeyEvent.VK_1);
		//

		tabbedPane.addChangeListener(new ChangeListener() {

			@Override
			public void stateChanged(ChangeEvent changeEvent) {
				// TODO Auto-generated method stub
				JTabbedPane sourceTabbedPane = (JTabbedPane) changeEvent
						.getSource();
				int index = sourceTabbedPane.getSelectedIndex();
				Component component = sourceTabbedPane.getSelectedComponent();
				System.out.println("Tab changed to: " + component);
				String name = sourceTabbedPane.getTitleAt(index);

				System.out.println("Tab changed to: " + name);

				themePanel = themePanes.get(name);
				System.out.println("H: " + themePanel.getPanel().getHeight()
						+ "W: " + themePanel.getPanel().getWidth());

				sourceTabbedPane.getTopLevelAncestor().requestFocus();

				// System.out.println(changeEvent);
			}
		});

		return tabbedPane;
	}

	public void setSelectedMapObject(MapObject mapObject) {
		Image image = mapObject
				.getImageIcon()
				.getImage()
				.getScaledInstance(MapObjectFactory.DEFAULT_SEGMENT_WIDTH,
						MapObjectFactory.DEFAULT_SEGMENT_HEIGHT,
						Image.SCALE_DEFAULT);
		button.setIcon(new ImageIcon(image));
	}
}
