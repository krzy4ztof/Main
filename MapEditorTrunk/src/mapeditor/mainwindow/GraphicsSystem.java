package mapeditor.mainwindow;

import java.awt.Color;
import java.awt.Container;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.util.Iterator;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;

import mapeditor.config.Config;
import mapeditor.mapapi.MapApi;
import mapeditor.mapapi.MapObject;
import mapeditor.messages.MapMessages;
import mapeditor.themesapi.MapObjectsTheme;
import mapeditor.themesapi.MapThemesList;

public class GraphicsSystem {

	private GraphicsSystemKeyListener gsKeyListener;
	private MapPanel mapPanel;
	public BmpPanel bmpPanel;
	private JFrame jFrame;
	private MapMessages messages;
	private MapThemesList mapThemesList;
	private MapApi mapApi = null;
	private Config config;

	public final static String ACTION_ZOOM_IN = "ACTION_ZOOM_IN";
	public final static String ACTION_ZOOM_OUT = "ACTION_ZOOM_OUT";
	public final static String ACTION_ZOOM_DEFAULT = "ACTION_ZOOM_DEFAULT";

	public final static String ACTION_ROLL_RIGHT = "ACTION_ROLL_RIGHT";
	public final static String ACTION_ROLL_LEFT = "ACTION_ROLL_LEFT";
	public final static String ACTION_ROLL_UP = "ACTION_ROLL_UP";
	public final static String ACTION_ROLL_DOWN = "ACTION_ROLL_DOWN";

	public final static String ACTION_NEW = "ACTION_NEW";
	public final static String ACTION_OPEN = "ACTION_OPEN";
	public final static String ACTION_CLOSE = "ACTION_CLOSE";
	public final static String ACTION_SAVE = "ACTION_SAVE";

	public final static String ACTION_MAP_ATTRIBUTES_PANEL = "ACTION_MAP_ATTRIBUTES_PANEL";

	private GraphicsSystemActionListener gsListener;
	private BmpPanelActionListener bmpListener;
	private GraphicsSystemFocusListener gsFocusListener;

	public GraphicsSystem(Config configParam, MapMessages messages,
			MapThemesList mapThemesListParam) {
		config = configParam;
		this.messages = messages;
		mapThemesList = mapThemesListParam;
		System.out.println(gsKeyListener);
		bmpPanel = new BmpPanel(mapThemesListParam, this);
		System.out.println(this.gsKeyListener);
		mapApi = new MapApi(config);

		mapPanel = new MapPanel(this, mapApi);
		gsKeyListener = new GraphicsSystemKeyListener(this, mapPanel);
		gsFocusListener = new GraphicsSystemFocusListener();

		gsListener = new GraphicsSystemActionListener(this, mapPanel, mapApi,
				messages, mapThemesList, config);
		bmpListener = new BmpPanelActionListener(bmpPanel, mapThemesList, this);

	}

	private JMenu createFileMenu() {
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

	private JMenu createEditMenu() {
		JMenu menu = new JMenu(messages.getMenuEdit());
		JMenuItem menuItem = new JMenuItem(messages.getMenuAttributes());
		menuItem.setActionCommand(GraphicsSystem.ACTION_MAP_ATTRIBUTES_PANEL);
		menuItem.addActionListener(gsListener);
		menu.add(menuItem);
		return menu;
	}

	private JMenu createZoomMenu() {
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

	private JMenu createMenuObjects() {
		JMenu menu = new JMenu(messages.getMenuObjects());
		buildObjectMenu(menu);
		return menu;
	}

	private JMenuBar createMenuBar() {
		JMenuBar menuBar = new JMenuBar();
		menuBar.add(createFileMenu());
		menuBar.add(createEditMenu());
		menuBar.add(createZoomMenu());
		menuBar.add(createMenuObjects());
		return menuBar;
	}

	private JPanel createButtonsPanel() {
		JPanel Buttons_p = new JPanel();
		GridBagConstraints c = new GridBagConstraints();
		Buttons_p.setLayout(new GridBagLayout());
		c.fill = GridBagConstraints.BOTH;

		c.weightx = 1.0;
		c.weighty = 1.0;
		c.gridx = 1;
		c.gridy = 0;
		Buttons_p.setBackground(Color.BLACK);

		// gridbag.setConstraints(Buttons_p, c);
		// Buttons_p.setLayout(gridbag);

		JButton Up_button = new JButton("^");
		Up_button.addActionListener(gsListener);// zmieni si� na mapk�
		Up_button.setActionCommand(GraphicsSystem.ACTION_ROLL_UP);
		Buttons_p.add(Up_button, c);

		// Up_button.setBackground(Color.YELLOW);
		// gridbag.setConstraints(Up_button, c);

		Up_button.setMargin(new Insets(0, 0, 0, 0));// zmniejsza marginesy
		// Buttons_p.add(Up_button);

		JButton Down_button = new JButton("v");
		Down_button.addActionListener(gsListener);// zmieni si� na mapk�
		Down_button.setActionCommand(GraphicsSystem.ACTION_ROLL_DOWN);
		c.gridx = 1;
		c.gridy = 1;
		Down_button.setBackground(Color.YELLOW);

		// gridbag.setConstraints(Down_button, c);
		Down_button.setMargin(new Insets(0, 0, 0, 0));
		Buttons_p.add(Down_button, c);

		JButton Left_button = new JButton("<");
		Left_button.addActionListener(gsListener);// zmieni si� na mapk�
		Left_button.setActionCommand(GraphicsSystem.ACTION_ROLL_LEFT);
		c.gridx = 0;
		c.gridy = 1;
		Left_button.setBackground(Color.MAGENTA);
		// gridbag.setConstraints(Left_button, c);
		Left_button.setMargin(new Insets(0, 0, 0, 0));
		Buttons_p.add(Left_button, c);

		JButton Right_button = new JButton(">");
		Right_button.addActionListener(gsListener);// zmieni si� na mapk�
		Right_button.setActionCommand(GraphicsSystem.ACTION_ROLL_RIGHT);
		c.gridx = 2;
		c.gridy = 1;
		Right_button.setBackground(Color.RED);
		Right_button.setMargin(new Insets(0, 0, 0, 0));

		// gridbag.setConstraints(Right_button, c);
		Buttons_p.add(Right_button, c);

		return Buttons_p;
	}

	private JPanel createRightSidePanel() {
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
		panel.add(createButtonsPanel(), c);

		return panel;
	}

	private JPanel createMapPanel() {
		mapPanel.setBackground(Color.ORANGE);

		return mapPanel;
	}

	public void activate() {

		this.jFrame = new JFrame();

		JMenuBar menu = this.createMenuBar();
		this.jFrame.setJMenuBar(menu);

		Container contentPane = jFrame.getContentPane();
		contentPane.setLayout(new GridBagLayout());
		GridBagConstraints c = new GridBagConstraints();

		c.fill = GridBagConstraints.BOTH;
		c.weightx = 1.0;
		c.weighty = 1.0;
		c.gridx = 0;
		c.gridy = 0;
		contentPane.add(createMapPanel(), c);

		c.weightx = 0.0;
		c.weighty = 1.0;
		c.gridx = 1;
		c.gridy = 0;
		contentPane.add(createRightSidePanel(), c);

		jFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		jFrame.setSize(400, 400);
		jFrame.setVisible(true);
		jFrame.requestFocus();
		jFrame.addFocusListener(this.gsFocusListener);
		jFrame.addKeyListener(this.gsKeyListener);
	}

	private void buildObjectMenu(JMenu Obj_menu) {
		/*
		 * Tworzy menu do wyboru grup tematycznych na podstawie obiektu
		 * images_list. image_list[x][1] - nazwa tematu. Ka�dy JMenuItem
		 * odpowiada jednemu tematowi. Wybranie tematu spowoduje wy�wietlenie
		 * bitmap nale��cych do tego tematu w BmpPanel.
		 */

		JMenuItem menuItem;
		String themeName;

		for (Iterator<MapObjectsTheme> it = mapThemesList.getThemesIterator(); it
				.hasNext();) {
			themeName = it.next().getName();
			menuItem = new JMenuItem(messages.getThemeName(themeName));
			menuItem.setActionCommand("MNU_" + themeName);
			menuItem.addActionListener(bmpListener);
			Obj_menu.add(menuItem);

		}
	}

	public JFrame getJFrame() {
		return this.jFrame;
	}

	public MapObject getSelectedMapObject() {
		return bmpPanel.getSelectedMapObject();
	}
}
