package mapeditor.mainwindow;

import java.awt.Container;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.util.Iterator;

import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;

import mapeditor.config.Config;
import mapeditor.mapapi.MapApi;
import mapeditor.messages.MapMessages;
import mapeditor.themesapi.MapObjectsTheme;
import mapeditor.themesapi.MapThemesManager;

public class MainWindow {

	final static String ACTION_ZOOM_IN = "ACTION_ZOOM_IN";
	final static String ACTION_ZOOM_OUT = "ACTION_ZOOM_OUT";
	final static String ACTION_ZOOM_DEFAULT = "ACTION_ZOOM_DEFAULT";
	final static String ACTION_CENTER_MAP = "ACTION_CENTER_MAP";

	final static String ACTION_NEW = "ACTION_NEW";
	final static String ACTION_OPEN = "ACTION_OPEN";
	final static String ACTION_CLOSE = "ACTION_CLOSE";
	final static String ACTION_SAVE = "ACTION_SAVE";

	final static String ACTION_MAP_ATTRIBUTES_PANEL = "ACTION_MAP_ATTRIBUTES_PANEL";
	final static String ACTION_REFRESH = "ACTION_REFRESH";

	final static String ACTION_THEMES_SELECTION = "ACTION_THEMES_SELECTION_";

	public MainWindow(Config config, MapMessages messages,
			MapThemesManager mapThemesList) {
		activate(config, messages, mapThemesList);
	}

	private JMenu createFileMenu(MapMessages messages,
			MainMenuActionListener gsListener) {
		JMenu menu = new JMenu(messages.getMenuFile());
		JMenuItem menuItem = new JMenuItem(messages.getMenuNew());
		menuItem.setActionCommand(MainWindow.ACTION_NEW);
		menuItem.addActionListener(gsListener);
		menu.add(menuItem);

		menuItem = new JMenuItem(messages.getMenuOpen());
		menuItem.setActionCommand(MainWindow.ACTION_OPEN);
		menuItem.addActionListener(gsListener);
		menu.add(menuItem);

		menuItem = new JMenuItem(messages.getMenuClose());
		menuItem.setActionCommand(MainWindow.ACTION_CLOSE);
		menuItem.addActionListener(gsListener);
		menu.add(menuItem);

		menuItem = new JMenuItem(messages.getMenuSave());
		menuItem.setActionCommand(MainWindow.ACTION_SAVE);
		menuItem.addActionListener(gsListener);
		menu.add(menuItem);

		/* docelowo cos innego bedzie nasluchwialo menu plik */

		return menu;
	}

	private JMenu createEditMenu(MapMessages messages,
			MainMenuActionListener gsListener) {
		JMenu menu = new JMenu(messages.getMenuEdit());
		JMenuItem menuItem = new JMenuItem(messages.getMenuAttributes());
		menuItem.setActionCommand(MainWindow.ACTION_MAP_ATTRIBUTES_PANEL);
		menuItem.addActionListener(gsListener);
		menu.add(menuItem);

		menuItem = new JMenuItem(messages.getMenuRefresh());
		menuItem.setActionCommand(MainWindow.ACTION_REFRESH);
		menuItem.addActionListener(gsListener);
		menu.add(menuItem);

		return menu;
	}

	private JMenu createNavigationMenu(MapMessages messages,
			MainMenuActionListener gsListener) {
		JMenu menu = new JMenu(messages.getMenuNavigation());

		JMenuItem menuItem = new JMenuItem(messages.getMenuZoomIn());
		menuItem.setActionCommand(MainWindow.ACTION_ZOOM_IN);
		menuItem.addActionListener(gsListener);
		menu.add(menuItem);

		menuItem = new JMenuItem(messages.getMenuZoomOut());
		menuItem.setActionCommand(MainWindow.ACTION_ZOOM_OUT);
		menuItem.addActionListener(gsListener);
		menu.add(menuItem);

		menuItem = new JMenuItem(messages.getMenuDefaultZoom());
		menuItem.setActionCommand(MainWindow.ACTION_ZOOM_DEFAULT);
		menuItem.addActionListener(gsListener);
		menu.add(menuItem);

		menuItem = new JMenuItem(messages.getMenuCenterMap());
		menuItem.setActionCommand(MainWindow.ACTION_CENTER_MAP);
		menuItem.addActionListener(gsListener);
		menu.add(menuItem);

		return menu;
	}

	private JMenu createMenuObjects(MapMessages messages,
			MapThemesManager mapThemesList, BmpPanelActionListener bmpListener) {
		JMenu menu = new JMenu(messages.getMenuObjects());
		JMenuItem menuItem;
		String themeName;
		/*
		 * Tworzy menu do wyboru grup tematycznych na podstawie obiektu
		 * images_list. image_list[x][1] - nazwa tematu. Każdy JMenuItem
		 * odpowiada jednemu tematowi. Wybranie tematu spowoduje wyswietlenie
		 * bitmap nalezacych do tego tematu w BmpPanel.
		 */
		for (Iterator<MapObjectsTheme> it = mapThemesList.getThemesIterator(); it
				.hasNext();) {
			themeName = it.next().getName();
			menuItem = new JMenuItem(messages.getThemeName(themeName));
			menuItem.setActionCommand(MainWindow.ACTION_THEMES_SELECTION
					+ themeName);
			menuItem.addActionListener(bmpListener);
			menu.add(menuItem);
		}
		return menu;
	}

	private JMenuBar createMenuBar(MapMessages messages,
			MapThemesManager mapThemesList, MainMenuActionListener gsListener,
			BmpPanelActionListener bmpListener) {
		JMenuBar menuBar = new JMenuBar();
		menuBar.add(createFileMenu(messages, gsListener));
		menuBar.add(createEditMenu(messages, gsListener));
		menuBar.add(createNavigationMenu(messages, gsListener));
		menuBar.add(createMenuObjects(messages, mapThemesList, bmpListener));
		return menuBar;
	}

	private JPanel createRightSidePanel(ThemePanel themePanel,
			BmpPanel bmpPanel, BmpPanelActionListener bmpListener,
			MainMenuActionListener gsListener) {

		JPanel panel = new JPanel();
		panel.setLayout(new GridBagLayout());
		GridBagConstraints c = new GridBagConstraints();

		c.fill = GridBagConstraints.BOTH;
		c.weightx = 0.0;
		c.weighty = 1.0;
		c.gridx = 0;
		c.gridy = 0;
		panel.add(themePanel.getScrollPane(), c);

		c.weighty = 0.0;
		c.gridx = 0;
		c.gridy = 1;

		bmpPanel.activate(bmpListener);
		panel.add(bmpPanel, c);
		return panel;
	}

	private MapPanel createMapPanel(Config config, MapMessages messages,
			MapThemesManager mapThemesList, MapApi mapApi) {
		MapPanel mapPanel = new MapPanel(mapApi);

		return mapPanel;
	}

	private void activate(Config config, MapMessages messages,
			MapThemesManager mapThemesList) {
		JFrame frame = new JFrame();

		Container contentPane = frame.getContentPane();
		contentPane.setLayout(new GridBagLayout());
		GridBagConstraints c = new GridBagConstraints();

		c.fill = GridBagConstraints.BOTH;
		c.weightx = 1.0;
		c.weighty = 1.0;
		c.gridx = 0;
		c.gridy = 0;

		BmpPanel bmpPanel = new BmpPanel(mapThemesList);
		BmpPanelActionListener bmpListener = new BmpPanelActionListener(
				bmpPanel);

		MapApi mapApi = new MapApi(config);
		MapPanel mapPanel = createMapPanel(config, messages, mapThemesList,
				mapApi);
		MapPanelMouseListener mpMouseListener = new MapPanelMouseListener(
				mapPanel, mapThemesList, mapApi);
		MapPanelMouseMotionListener mpMouseMotionListener = new MapPanelMouseMotionListener(
				mapPanel, mapThemesList, mapApi);

		mapPanel.getPanel().addMouseListener(mpMouseListener);
		mapPanel.getPanel().addMouseMotionListener(mpMouseMotionListener);

		contentPane.add(mapPanel.getScrollPane(), c);

		ThemePanel themePanel = new ThemePanel(mapThemesList);
		ThemePanelMouseListener tpMouseListener = new ThemePanelMouseListener(
				themePanel);
		themePanel.getPanel().addMouseListener(tpMouseListener);

		MainWindowKeyListener gsKeyListener = new MainWindowKeyListener(
				mapPanel, themePanel);
		DialogsManager dialogsManager = new DialogsManager(mapPanel, mapApi,
				messages, mapThemesList, config);
		MainMenuActionListener gsListener = new MainMenuActionListener(
				dialogsManager, mapPanel, themePanel);

		c.weightx = 0.0;
		c.weighty = 1.0;
		c.gridx = 1;
		c.gridy = 0;
		contentPane.add(
				createRightSidePanel(themePanel, bmpPanel, bmpListener,
						gsListener), c);

		JMenuBar menu = createMenuBar(messages, mapThemesList, gsListener,
				bmpListener);
		frame.setJMenuBar(menu);

		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setSize(400, 400);
		frame.setVisible(true);
		frame.requestFocus();
		frame.addFocusListener(new MainWindowFocusListener());
		frame.addKeyListener(gsKeyListener);
	}
}
