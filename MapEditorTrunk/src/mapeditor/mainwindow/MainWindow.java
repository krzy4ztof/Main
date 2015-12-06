package mapeditor.mainwindow;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.event.ActionListener;
import java.io.File;

import javax.swing.ButtonGroup;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.JSplitPane;
import javax.swing.JToolBar;

import mapeditor.config.Config;
import mapeditor.mapapi.CopyPaste;
import mapeditor.mapapi.MapApi;
import mapeditor.mapapi.Tools;
import mapeditor.messages.MapMessages;
import mapeditor.themesapi.MapObjectFactory;
import mapeditor.themesapi.ThemesManager;

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

	final static String ACTION_TOOLBAR_ERASER = "ACTION_TOOLBAR_ERASER";
	final static String ACTION_TOOLBAR_BRUSH = "ACTION_TOOLBAR_BRUSH";
	final static String ACTION_TOOLBAR_BUCKET = "ACTION_TOOLBAR_BUCKET";
	final static String ACTION_TOOLBAR_PICKER = "ACTION_TOOLBAR_PICKER";
	final static String ACTION_TOOLBAR_SELECTION = "ACTION_TOOLBAR_SELECTION";

	final static String TOOLBAR_ICONS_FOLDER = "resources" + File.separator
			+ "toolbar" + File.separator;

	final static String ICON_ERASER_16 = "package_purge_16.png";
	final static String ICON_BRUSH_16 = "brush_16.png";
	final static String ICON_BUCKET_16 = "construction_bucket_16.png";
	final static String ICON_PICKER_16 = "color_picker_16.png";
	final static String ICON_SELECTION_16 = "selection_16.png";

	final static String ICON_ERASER_32 = "package_purge_32.png";
	final static String ICON_BRUSH_32 = "brush_32.png";
	final static String ICON_BUCKET_32 = "construction_bucket_32.png";
	final static String ICON_PICKER_32 = "color_picker_32.png";
	final static String ICON_SELECTION_32 = "selection_32.png";

	public final static String ICON_NULL = "null.png";

	public MainWindow(Config config, MapMessages messages,
			ThemesManager mapThemesList, MapObjectFactory mapObjectFactory) {
		activate(config, messages, mapThemesList, mapObjectFactory);
	}

	private JMenu createFileMenu(MapMessages messages,
			MainMenuActionListener gsListener) {
		JMenu menu = new JMenu(messages.getString(MapMessages.MENU_FILE));
		JMenuItem menuItem = new JMenuItem(
				messages.getString(MapMessages.MENU_NEW));
		menuItem.setActionCommand(MainWindow.ACTION_NEW);
		menuItem.addActionListener(gsListener);
		menu.add(menuItem);

		menuItem = new JMenuItem(messages.getString(MapMessages.MENU_OPEN));
		menuItem.setActionCommand(MainWindow.ACTION_OPEN);
		menuItem.addActionListener(gsListener);
		menu.add(menuItem);

		menuItem = new JMenuItem(messages.getString(MapMessages.MENU_CLOSE));
		menuItem.setActionCommand(MainWindow.ACTION_CLOSE);
		menuItem.addActionListener(gsListener);
		menu.add(menuItem);

		menuItem = new JMenuItem(messages.getString(MapMessages.MENU_SAVE));
		menuItem.setActionCommand(MainWindow.ACTION_SAVE);
		menuItem.addActionListener(gsListener);
		menu.add(menuItem);

		/* docelowo cos innego bedzie nasluchwialo menu plik */

		return menu;
	}

	private JMenu createEditMenu(MapMessages messages,
			MainMenuActionListener gsListener) {
		JMenu menu = new JMenu(messages.getString(MapMessages.MENU_EDIT));
		JMenuItem menuItem = new JMenuItem(
				messages.getString(MapMessages.MENU_ATTRIBUTES));
		menuItem.setActionCommand(MainWindow.ACTION_MAP_ATTRIBUTES_PANEL);
		menuItem.addActionListener(gsListener);
		menu.add(menuItem);

		menuItem = new JMenuItem(messages.getString(MapMessages.MENU_REFRESH));
		menuItem.setActionCommand(MainWindow.ACTION_REFRESH);
		menuItem.addActionListener(gsListener);
		menu.add(menuItem);

		return menu;
	}

	private JMenu createNavigationMenu(MapMessages messages,
			MainMenuActionListener gsListener) {
		JMenu menu = new JMenu(messages.getString(MapMessages.MENU_NAVIGATION));

		JMenuItem menuItem = new JMenuItem(
				messages.getString(MapMessages.MENU_ZOOM_IN));
		menuItem.setActionCommand(MainWindow.ACTION_ZOOM_IN);
		menuItem.addActionListener(gsListener);
		menu.add(menuItem);

		menuItem = new JMenuItem(messages.getString(MapMessages.MENU_ZOOM_OUT));
		menuItem.setActionCommand(MainWindow.ACTION_ZOOM_OUT);
		menuItem.addActionListener(gsListener);
		menu.add(menuItem);

		menuItem = new JMenuItem(
				messages.getString(MapMessages.MENU_DEFAULT_ZOOM));
		menuItem.setActionCommand(MainWindow.ACTION_ZOOM_DEFAULT);
		menuItem.addActionListener(gsListener);
		menu.add(menuItem);

		menuItem = new JMenuItem(
				messages.getString(MapMessages.MENU_CENTER_MAP));
		menuItem.setActionCommand(MainWindow.ACTION_CENTER_MAP);
		menuItem.addActionListener(gsListener);
		menu.add(menuItem);

		return menu;
	}

	private JMenuBar createMenuBar(MapMessages messages,
			ThemesManager mapThemesList, MainMenuActionListener gsListener) {
		JMenuBar menuBar = new JMenuBar();
		menuBar.add(createFileMenu(messages, gsListener));
		menuBar.add(createEditMenu(messages, gsListener));
		menuBar.add(createNavigationMenu(messages, gsListener));
		return menuBar;
	}

	private JPanel createRightSidePanel(LayersPane layersPane,
			ThemesPane themesPane, MainMenuActionListener gsListener) {

		JPanel panel = new JPanel();
		panel.setLayout(new GridBagLayout());
		GridBagConstraints c = new GridBagConstraints();

		c.fill = GridBagConstraints.BOTH;
		c.weightx = 1.0;
		c.weighty = 1.0;
		c.gridx = 0;
		c.gridy = 0;

		JSplitPane splitPaneFirst = new JSplitPane(JSplitPane.VERTICAL_SPLIT,
				layersPane.getScrollPane(), themesPane.getPane());
		splitPaneFirst.setOneTouchExpandable(true);
		splitPaneFirst.setResizeWeight(0);

		JSplitPane splitPaneSec = new JSplitPane(JSplitPane.VERTICAL_SPLIT,
				splitPaneFirst, new JPanel());
		splitPaneSec.setOneTouchExpandable(true);
		// splitPane.setDividerLocation(200);
		splitPaneSec.setResizeWeight(1);

		Dimension minimumSize = new Dimension(0, 100);
		themesPane.getPane().setMinimumSize(minimumSize);
		panel.add(splitPaneSec, c);

		return panel;
	}

	private MapPane createMapPanel(Config config, MapMessages messages,
			ThemesManager mapThemesList, MapApi mapApi, CopyPaste copyPaste) {
		MapPane mapPanel = new MapPane(mapApi, copyPaste);

		return mapPanel;
	}

	private void activate(Config config, MapMessages messages,
			ThemesManager mapThemesList, MapObjectFactory mapObjectFactory) {
		JFrame frame = new JFrame();

		Container contentPane = frame.getContentPane();
		contentPane.setLayout(new BorderLayout());

		CursorFactory cursorFactory = new CursorFactory();
		Tools tools = new Tools();

		MapApi mapApi = new MapApi(config, mapObjectFactory);
		CopyPaste copyPaste = new CopyPaste(mapApi, mapObjectFactory);

		MapPane mapPanel = createMapPanel(config, messages, mapThemesList,
				mapApi, copyPaste);

		copyPaste.addGridPane(mapPanel);

		ThemesPane themesPane = new ThemesPane(messages, mapThemesList);

		MapPanelMouseListener mpMouseListener = new MapPanelMouseListener(
				mapPanel, mapThemesList, mapApi, tools, themesPane,
				mapObjectFactory, copyPaste);
		MapPanelMouseMotionListener mpMouseMotionListener = new MapPanelMouseMotionListener(
				mapPanel, mapThemesList, mapApi, tools, mapObjectFactory,
				copyPaste);

		mapPanel.getPanel().addMouseListener(mpMouseListener);
		mapPanel.getPanel().addMouseMotionListener(mpMouseMotionListener);

		JToolBar toolBar = createToolBar(config, messages, tools,
				cursorFactory, mapPanel, copyPaste);
		frame.add(toolBar, BorderLayout.PAGE_START);

		MainWindowKeyListener gsKeyListener = new MainWindowKeyListener(
				mapPanel, themesPane);
		DialogsManager dialogsManager = new DialogsManager(mapPanel, mapApi,
				messages, mapThemesList, config, tools, mapObjectFactory);
		MainMenuActionListener gsListener = new MainMenuActionListener(
				dialogsManager, mapPanel, themesPane);

		LayersPaneActionListener layersPaneActionListener = new LayersPaneActionListener(
				mapApi, mapPanel);
		LayersPane layersPane = new LayersPane(config, layersPaneActionListener);

		JPanel rightSidePanel = createRightSidePanel(layersPane, themesPane,
				gsListener);

		JSplitPane splitPane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT,
				mapPanel.getScrollPane(), rightSidePanel);
		splitPane.setOneTouchExpandable(true);

		splitPane.setResizeWeight(1);
		Dimension minimumSize = new Dimension(200, 0);
		mapPanel.getScrollPane().setPreferredSize(minimumSize);

		int minWidth = SingleThemePane.DEFAULT_SEGMENT_WIDTH
				* config.getThemeApiColumnsNumber()
				+ SingleThemePane.LEFT_MARIGIN + SingleThemePane.RIGHT_MARIGIN
				+ 10;
		minimumSize = new Dimension(minWidth, 0);
		rightSidePanel.setPreferredSize(minimumSize);

		// contentPane.add(splitPane, c);
		contentPane.add(splitPane, BorderLayout.CENTER);

		JMenuBar menu = createMenuBar(messages, mapThemesList, gsListener);
		frame.setJMenuBar(menu);

		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setSize(500, 400);
		frame.setVisible(true);
		frame.requestFocus();
		frame.addFocusListener(new MainWindowFocusListener());
		frame.addKeyListener(gsKeyListener);
	}

	private JToolBar createToolBar(Config config, MapMessages messages,
			Tools tools, CursorFactory cursorFactory, MapPane mapPanel,
			CopyPaste copyPaste) {
		JToolBar toolBar = new JToolBar(
				messages.getString(MapMessages.TOOLBAR_TITLE));
		ToolBarActionListener actionListener = new ToolBarActionListener(tools,
				cursorFactory, mapPanel, copyPaste);

		String iconEraser = ICON_ERASER_16;
		String iconBrush = ICON_BRUSH_16;
		String iconBucket = ICON_BUCKET_16;
		String iconPicker = ICON_PICKER_16;
		String iconSelection = ICON_SELECTION_16;

		if (config.getToolBarIconsSize() == 32) {
			iconEraser = ICON_ERASER_32;
			iconBrush = ICON_BRUSH_32;
			iconBucket = ICON_BUCKET_32;
			iconPicker = ICON_PICKER_32;
			iconSelection = ICON_SELECTION_32;
		}

		ButtonGroup buttonGroup = new ButtonGroup();

		JButton brushButton = createToolBarButton(iconBrush,
				ACTION_TOOLBAR_BRUSH,
				messages.getString(MapMessages.TOOLBAR_BRUSH), actionListener,
				buttonGroup);
		toolBar.add(brushButton);
		toolBar.add(createToolBarButton(iconBucket, ACTION_TOOLBAR_BUCKET,
				messages.getString(MapMessages.TOOLBAR_BUCKET), actionListener,
				buttonGroup));
		toolBar.add(createToolBarButton(iconEraser, ACTION_TOOLBAR_ERASER,
				messages.getString(MapMessages.TOOLBAR_ERASER), actionListener,
				buttonGroup));
		toolBar.add(createToolBarButton(iconPicker, ACTION_TOOLBAR_PICKER,
				messages.getString(MapMessages.TOOLBAR_PICKER), actionListener,
				buttonGroup));
		toolBar.add(createToolBarButton(iconSelection,
				ACTION_TOOLBAR_SELECTION,
				messages.getString(MapMessages.TOOLBAR_SELECTION),
				actionListener, buttonGroup));

		brushButton.doClick();
		return toolBar;
	}

	private JButton createToolBarButton(String imageName, String actionCommand,
			String toolTipText, ActionListener actionListener,
			ButtonGroup buttonGroup) {
		String imgLocation = TOOLBAR_ICONS_FOLDER + imageName;
		JButton button = new JButton();
		button.addActionListener(actionListener);
		button.setActionCommand(actionCommand);
		button.setToolTipText(toolTipText);
		button.setIcon(new ImageIcon(imgLocation, toolTipText));
		buttonGroup.add(button);

		return button;
	}
}
