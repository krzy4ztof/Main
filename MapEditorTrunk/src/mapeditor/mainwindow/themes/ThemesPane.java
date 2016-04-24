package mapeditor.mainwindow.themes;

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

	private JLayeredPane pane;

	private JTabbedPane tabbedPane;

	private SingleThemePane themePanel;

	private HashMap<String, SingleThemePane> themePanes;

	private JButton button;

	public ThemesPane(MapMessages messages, ThemesManager mapThemesManager) {
		super();
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
				((JButton) event.getSource()).getTopLevelAncestor()
						.requestFocus();
			}

		});

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

		tabbedPane.addChangeListener(new ChangeListener() {

			@Override
			public void stateChanged(ChangeEvent changeEvent) {
				JTabbedPane sourceTabbedPane = (JTabbedPane) changeEvent
						.getSource();
				int index = sourceTabbedPane.getSelectedIndex();
				String name = sourceTabbedPane.getTitleAt(index);
				themePanel = themePanes.get(name);
				sourceTabbedPane.getTopLevelAncestor().requestFocus();
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
