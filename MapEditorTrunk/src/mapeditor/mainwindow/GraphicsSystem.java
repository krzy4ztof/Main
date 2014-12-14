package mapeditor.mainwindow;

import java.awt.Color;
import java.awt.Container;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.util.Iterator;

import javax.swing.JButton;
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

public class GraphicsSystem {

	final static String ACTION_ZOOM_IN = "ACTION_ZOOM_IN";
	final static String ACTION_ZOOM_OUT = "ACTION_ZOOM_OUT";
	final static String ACTION_ZOOM_DEFAULT = "ACTION_ZOOM_DEFAULT";

	final static String ACTION_ROLL_RIGHT = "ACTION_ROLL_RIGHT";
	final static String ACTION_ROLL_LEFT = "ACTION_ROLL_LEFT";
	final static String ACTION_ROLL_UP = "ACTION_ROLL_UP";
	final static String ACTION_ROLL_DOWN = "ACTION_ROLL_DOWN";

	final static String ACTION_NEW = "ACTION_NEW";
	final static String ACTION_OPEN = "ACTION_OPEN";
	final static String ACTION_CLOSE = "ACTION_CLOSE";
	final static String ACTION_SAVE = "ACTION_SAVE";

	final static String ACTION_MAP_ATTRIBUTES_PANEL = "ACTION_MAP_ATTRIBUTES_PANEL";

	final static String ACTION_THEMES_SELECTION = "ACTION_THEMES_SELECTION_";

	JFrame jFrame;

	public GraphicsSystem(Config config, MapMessages messages,
			MapThemesManager mapThemesList) {
		activate(config, messages, mapThemesList);
	}

	private JMenu createFileMenu(MapMessages messages,
			GraphicsSystemActionListener gsListener) {
		JMenu menu = new JMenu(messages.getMenuFile());
		JMenuItem menuItem = new JMenuItem(messages.getMenuNew());
		menuItem.setActionCommand(GraphicsSystem.ACTION_NEW);
		menuItem.addActionListener(gsListener);
		menu.add(menuItem);

		menuItem = new JMenuItem(messages.getMenuOpen());
		menuItem.setActionCommand(GraphicsSystem.ACTION_OPEN);
		menuItem.addActionListener(gsListener);
		menu.add(menuItem);

		menuItem = new JMenuItem(messages.getMenuClose());
		menuItem.setActionCommand(GraphicsSystem.ACTION_CLOSE);
		menuItem.addActionListener(gsListener);
		menu.add(menuItem);

		menuItem = new JMenuItem(messages.getMenuSave());
		menuItem.setActionCommand(GraphicsSystem.ACTION_SAVE);
		menuItem.addActionListener(gsListener);
		menu.add(menuItem);

		/* docelowo cos innego bedzie nasluchwialo menu plik */

		return menu;
	}

	private JMenu createEditMenu(MapMessages messages,
			GraphicsSystemActionListener gsListener) {
		JMenu menu = new JMenu(messages.getMenuEdit());
		JMenuItem menuItem = new JMenuItem(messages.getMenuAttributes());
		menuItem.setActionCommand(GraphicsSystem.ACTION_MAP_ATTRIBUTES_PANEL);
		menuItem.addActionListener(gsListener);
		menu.add(menuItem);
		return menu;
	}

	private JMenu createZoomMenu(MapMessages messages,
			GraphicsSystemActionListener gsListener) {
		JMenu menu = new JMenu(messages.getMenuZoom());

		JMenuItem menuItem = new JMenuItem(messages.getMenuZoomIn());
		menuItem.setActionCommand(GraphicsSystem.ACTION_ZOOM_IN);
		menuItem.addActionListener(gsListener);
		menu.add(menuItem);

		menuItem = new JMenuItem(messages.getMenuZoomOut());
		menuItem.setActionCommand(GraphicsSystem.ACTION_ZOOM_OUT);
		menuItem.addActionListener(gsListener);
		menu.add(menuItem);

		menuItem = new JMenuItem(messages.getMenuDefaultZoom());
		menuItem.setActionCommand(GraphicsSystem.ACTION_ZOOM_DEFAULT);
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
			menuItem.setActionCommand(GraphicsSystem.ACTION_THEMES_SELECTION
					+ themeName);
			menuItem.addActionListener(bmpListener);
			menu.add(menuItem);
		}
		return menu;
	}

	private JMenuBar createMenuBar(MapMessages messages,
			MapThemesManager mapThemesList,
			GraphicsSystemActionListener gsListener,
			BmpPanelActionListener bmpListener) {
		JMenuBar menuBar = new JMenuBar();
		menuBar.add(createFileMenu(messages, gsListener));
		menuBar.add(createEditMenu(messages, gsListener));
		menuBar.add(createZoomMenu(messages, gsListener));
		menuBar.add(createMenuObjects(messages, mapThemesList, bmpListener));
		return menuBar;
	}

	private JPanel createButtonsPanel(GraphicsSystemActionListener gsListener) {
		JPanel panel = new JPanel();
		GridBagConstraints c = new GridBagConstraints();
		panel.setLayout(new GridBagLayout());
		panel.setBackground(Color.BLACK);

		c.fill = GridBagConstraints.BOTH;

		c.weightx = 1.0;
		c.weighty = 1.0;
		c.gridx = 1;
		c.gridy = 0;

		JButton button = new JButton("^");
		button.addActionListener(gsListener);
		button.setActionCommand(GraphicsSystem.ACTION_ROLL_UP);
		panel.add(button, c);

		c.gridx = 1;
		c.gridy = 1;
		button = new JButton("v");
		button.addActionListener(gsListener);
		button.setActionCommand(GraphicsSystem.ACTION_ROLL_DOWN);
		button.setBackground(Color.YELLOW);
		panel.add(button, c);

		c.gridx = 0;
		c.gridy = 1;
		button = new JButton("<");
		button.addActionListener(gsListener);
		button.setActionCommand(GraphicsSystem.ACTION_ROLL_LEFT);
		button.setBackground(Color.MAGENTA);
		panel.add(button, c);

		c.gridx = 2;
		c.gridy = 1;
		button = new JButton(">");
		button.addActionListener(gsListener);
		button.setActionCommand(GraphicsSystem.ACTION_ROLL_RIGHT);
		button.setBackground(Color.RED);
		panel.add(button, c);

		return panel;
	}

	private JPanel createRightSidePanel(BmpPanel bmpPanel,
			BmpPanelActionListener bmpListener,
			GraphicsSystemActionListener gsListener) {

		JPanel panel = new JPanel();
		panel.setLayout(new GridBagLayout());
		GridBagConstraints c = new GridBagConstraints();

		c.fill = GridBagConstraints.BOTH;
		c.weightx = 0.0;
		c.weighty = 1.0;
		c.gridx = 0;
		c.gridy = 0;

		bmpPanel.activate(bmpListener);
		panel.add(bmpPanel, c);

		c.weightx = 0.0;
		c.weighty = 0.0;
		c.gridx = 0;
		c.gridy = 1;
		panel.add(createButtonsPanel(gsListener), c);

		return panel;
	}

	private MapPanel createMapPanel(Config config, MapMessages messages,
			MapThemesManager mapThemesList, MapApi mapApi) {
		MapPanel mapPanel = new MapPanel(mapApi);

		mapPanel.setBackground(Color.ORANGE);

		return mapPanel;
	}

	private void activate(Config config, MapMessages messages,
			MapThemesManager mapThemesList) {
		jFrame = new JFrame();

		Container contentPane = jFrame.getContentPane();
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

		mapPanel.addMouseListener(mpMouseListener);
		mapPanel.addMouseMotionListener(mpMouseMotionListener);
		contentPane.add(mapPanel, c);

		GraphicsSystemKeyListener gsKeyListener = new GraphicsSystemKeyListener(
				mapPanel);
		DialogsManager dialogsManager = new DialogsManager(mapPanel, mapApi,
				messages, mapThemesList, config);
		GraphicsSystemActionListener gsListener = new GraphicsSystemActionListener(
				dialogsManager, mapPanel);

		c.weightx = 0.0;
		c.weighty = 1.0;
		c.gridx = 1;
		c.gridy = 0;
		contentPane.add(
				createRightSidePanel(bmpPanel, bmpListener, gsListener), c);

		JMenuBar menu = createMenuBar(messages, mapThemesList, gsListener,
				bmpListener);
		jFrame.setJMenuBar(menu);

		jFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		jFrame.setSize(400, 400);
		jFrame.setVisible(true);
		jFrame.requestFocus();
		jFrame.addFocusListener(new GraphicsSystemFocusListener());
		jFrame.addKeyListener(gsKeyListener);
	}

	public JFrame getFrame() {
		return jFrame;
	}
}
