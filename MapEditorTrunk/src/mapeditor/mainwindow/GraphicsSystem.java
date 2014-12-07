package mapeditor.mainwindow;

import java.awt.Color;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.util.Iterator;
import java.util.ResourceBundle;

import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

import mapeditor.config.Config;
import mapeditor.dialogs.MapAttributesPanel;
import mapeditor.mapapi.MapApi;
import mapeditor.mapapi.MapObject;
import mapeditor.saveload.MapLoader;
import mapeditor.saveload.MapSaver;
import mapeditor.themesapi.MapObjectsTheme;
import mapeditor.themesapi.MapThemesList;
import otherprods.ExampleFileFilter;

public class GraphicsSystem implements ActionListener {

    private KeyboardManager keyboardManager;
    private MapPanel mapPanel;
    public BmpPanel bmpPanel;
    private JFrame jFrame;
    private ResourceBundle messages;
    private MapThemesList mapThemesList;
    private MapApi mapApi = null;
    private Config config;
    
    private final static String ACTION_ZOOM_IN="ACTION_ZOOM_IN";
    private final static String ACTION_ZOOM_OUT="ACTION_ZOOM_OUT";
    private final static String ACTION_ZOOM_DEFAULT="ACTION_ZOOM_DEFAULT";
    
    private final static String ACTION_ROLL_RIGHT="ACTION_ROLL_RIGHT";
    private final static String ACTION_ROLL_LEFT="ACTION_ROLL_LEFT";
    private final static String ACTION_ROLL_UP="ACTION_ROLL_UP";
    private final static String ACTION_ROLL_DOWN="ACTION_ROLL_DOWN";
    
    private final static String ACTION_NEW="ACTION_NEW";
    private final static String ACTION_OPEN="ACTION_OPEN";
    private final static String ACTION_CLOSE="ACTION_CLOSE";
    private final static String ACTION_SAVE="ACTION_SAVE";
    
    private final static String ACTION_MAP_ATTRIBUTES_PANEL="ACTION_MAP_ATTRIBUTES_PANEL";
    
    
  
    public GraphicsSystem(Config configParam, ResourceBundle resourceBundle,
            MapThemesList mapThemesListParam) {
    	config = configParam;
        messages = resourceBundle;
        mapThemesList = mapThemesListParam;
        keyboardManager = new KeyboardManager(this);
        System.out.println(keyboardManager);
        bmpPanel = new BmpPanel(mapThemesListParam, this);
        System.out.println(this.keyboardManager);
        mapApi = new MapApi(config);

        mapPanel = new MapPanel(this, mapApi);
    }

    public void activate() {

        JMenuItem Buf_menu;
        this.jFrame = new JFrame();
        JMenuBar M_menu = new JMenuBar();

        JMenu File_menu = new JMenu(messages.getString("File"));
        Buf_menu = new JMenuItem(messages.getString("New"));
        Buf_menu.setActionCommand(GraphicsSystem.ACTION_NEW);
        Buf_menu.addActionListener(this);
        File_menu.add(Buf_menu);

        Buf_menu = new JMenuItem(messages.getString("Open"));
        Buf_menu.setActionCommand(GraphicsSystem.ACTION_OPEN);
        Buf_menu.addActionListener(this);
        File_menu.add(Buf_menu);

        Buf_menu = new JMenuItem(messages.getString("Close"));
        Buf_menu.setActionCommand(GraphicsSystem.ACTION_CLOSE);
        Buf_menu.addActionListener(this);
        File_menu.add(Buf_menu);

        Buf_menu = new JMenuItem(messages.getString("Save"));
        Buf_menu.setActionCommand(GraphicsSystem.ACTION_SAVE);
        Buf_menu.addActionListener(this);
        File_menu.add(Buf_menu);
        M_menu.add(File_menu);
        /* docelowo co� innego b�dzie nas�uchiwa�o menu plik*/

        JMenu Edit_menu = new JMenu(messages.getString("Edit"));
        Buf_menu = new JMenuItem(messages.getString("Attributes"));
        Buf_menu.setActionCommand(GraphicsSystem.ACTION_MAP_ATTRIBUTES_PANEL);
        Buf_menu.addActionListener(this);
        Edit_menu.add(Buf_menu);
        M_menu.add(Edit_menu);

        JMenu Zoom_menu = new JMenu(messages.getString("Zoom"));

        Buf_menu = new JMenuItem(messages.getString("ZoomIn"));
        Buf_menu.setActionCommand(GraphicsSystem.ACTION_ZOOM_IN);
        Buf_menu.addActionListener(this);
        Zoom_menu.add(Buf_menu);

        Buf_menu = new JMenuItem(messages.getString("ZoomOut"));
        Buf_menu.setActionCommand(GraphicsSystem.ACTION_ZOOM_OUT);
        Buf_menu.addActionListener(this);
        Zoom_menu.add(Buf_menu);

        Buf_menu = new JMenuItem(messages.getString("DefaultZoom"));
        Buf_menu.setActionCommand(GraphicsSystem.ACTION_ZOOM_DEFAULT);
        Buf_menu.addActionListener(this);
        Zoom_menu.add(Buf_menu);

        M_menu.add(Zoom_menu);

        JMenu Obj_menu = new JMenu(messages.getString("Objects"));
        this.buildObjectMenu(Obj_menu);
        M_menu.add(Obj_menu);
        this.jFrame.setJMenuBar(M_menu);


        GridBagLayout gridbag = new GridBagLayout();
        GridBagConstraints c = new GridBagConstraints();
        this.jFrame.getContentPane().setLayout(gridbag);

        c.fill = GridBagConstraints.BOTH;
        c.weightx = 10.0;//proporcje powi�kszania si�
        c.weighty = 1.0;//proporcje powi�kszania si�
        c.gridx = 0;
        c.gridy = 0;
        mapPanel.setBackground(Color.ORANGE);
        gridbag.setConstraints(mapPanel, c);
        this.jFrame.getContentPane().add(mapPanel);

        JPanel R_panel = new JPanel();
        c.weightx = 1.0;//proporcje powi�kszania si�
        c.weighty = 1.0;//proporcje powi�kszania si�
        c.gridx = 1;
        c.gridy = 0;
        gridbag.setConstraints(R_panel, c);
        this.jFrame.getContentPane().add(R_panel);
        R_panel.setLayout(gridbag);

        c.weightx = 1.0;
        c.weighty = 10.0;
        c.gridx = 0;
        c.gridy = 0;
        bmpPanel.activate();
        gridbag.setConstraints(bmpPanel, c);
        R_panel.add(bmpPanel);

        JPanel Buttons_p = new JPanel();
        c.weightx = 1.0;
        c.weighty = 1.0;
        c.gridx = 0;
        c.gridy = 1;
        Buttons_p.setBackground(Color.BLACK);
        gridbag.setConstraints(Buttons_p, c);
        Buttons_p.setLayout(gridbag);
        R_panel.add(Buttons_p);

        JButton Up_button = new JButton("^");
        Up_button.addActionListener(this);// zmieni si� na mapk�
        Up_button.setActionCommand(GraphicsSystem.ACTION_ROLL_UP);
        c.gridx = 1;
        c.gridy = 0;
        Up_button.setBackground(Color.YELLOW);
        gridbag.setConstraints(Up_button, c);

        Up_button.setMargin(new Insets(0, 0, 0, 0));//zmniejsza marginesy
        Buttons_p.add(Up_button);

        JButton Down_button = new JButton("v");
        Down_button.addActionListener(this);// zmieni si� na mapk�
        Down_button.setActionCommand(GraphicsSystem.ACTION_ROLL_DOWN);
        c.gridx = 1;
        c.gridy = 1;
        Down_button.setBackground(Color.YELLOW);
        gridbag.setConstraints(Down_button, c);
        Down_button.setMargin(new Insets(0, 0, 0, 0));
        Buttons_p.add(Down_button);

        JButton Left_button = new JButton("<");
        Left_button.addActionListener(this);// zmieni si� na mapk�
        Left_button.setActionCommand(GraphicsSystem.ACTION_ROLL_LEFT);
        c.gridx = 0;
        c.gridy = 1;
        Left_button.setBackground(Color.MAGENTA);
        gridbag.setConstraints(Left_button, c);
        Left_button.setMargin(new Insets(0, 0, 0, 0));
        Buttons_p.add(Left_button);
        
        JButton Right_button = new JButton(">");
        Right_button.addActionListener(this);// zmieni si� na mapk�
        Right_button.setActionCommand(GraphicsSystem.ACTION_ROLL_RIGHT);
        c.gridx = 2;
        c.gridy = 1;
        Right_button.setBackground(Color.RED);
        Right_button.setMargin(new Insets(0, 0, 0, 0));
        gridbag.setConstraints(Right_button, c);
        Buttons_p.add(Right_button);

        this.jFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.jFrame.setSize(400, 400);
        this.jFrame.setVisible(true);
        jFrame.requestFocus();
        this.jFrame.addFocusListener(this.keyboardManager);
        this.jFrame.addKeyListener(this.keyboardManager);
    }

    private void buildObjectMenu(JMenu Obj_menu) {
        /*
        Tworzy menu do wyboru grup tematycznych na podstawie
        obiektu images_list. image_list[x][1] - nazwa tematu.
        Ka�dy JMenuItem odpowiada jednemu tematowi. Wybranie
        tematu spowoduje wy�wietlenie bitmap nale��cych do
        tego tematu w BmpPanel.
         */

        JMenuItem menuItem;
        String themeName;

        for (Iterator<MapObjectsTheme> it = mapThemesList.getThemesIterator(); it.hasNext();) {
            themeName = it.next().getName();
            menuItem = new JMenuItem(messages.getString(themeName));
            menuItem.setActionCommand("MNU_" + themeName);
            menuItem.addActionListener(bmpPanel);
            Obj_menu.add(menuItem);

        }
    }

    public JFrame getJFrame() {
        return this.jFrame;
    }

    public void MoveMapAction(int x, int y) {
        mapPanel.MoveMap(x, y);
    }

    public void ZoomMapInAction() {
        mapPanel.ZoomMapIn();
    }

    public void ZoomMapOutAction() {
        mapPanel.ZoomMapOut();
    }

    public void SetDefaultMapZoomAction() {
        mapPanel.SetDefaultMapZoom();
    }

    public void actionPerformed(ActionEvent e) {
        /*
        prowadzi nas�uch
        1. przycisk�w przesuwaj�cych map�
        2. ??? menu plik (otieranie/zamykanie nowych map
        - mo�e przenie�� to do graphics_systemu, otwieranie
        okien dialogowych do wyboru pliku
         */
    	
        String str = e.getActionCommand();
        System.out.println("MapPanel: " + e.getActionCommand());
        if (str.equals(GraphicsSystem.ACTION_ROLL_RIGHT)) {
            MoveMapAction(1, 0);
        } else if (str.equals(GraphicsSystem.ACTION_ROLL_LEFT)) {
            MoveMapAction(-1, 0);
        } else if (str.equals(GraphicsSystem.ACTION_ROLL_UP)) {
            MoveMapAction(0, -1);
        } else if (str.equals(GraphicsSystem.ACTION_ROLL_DOWN)) {
            MoveMapAction(0, 1);
        } else if (str.equals(GraphicsSystem.ACTION_ZOOM_IN)) {
            ZoomMapInAction();
        } else if (str.equals(GraphicsSystem.ACTION_ZOOM_OUT)) {
            ZoomMapOutAction();
        } else if (str.equals(GraphicsSystem.ACTION_ZOOM_DEFAULT)) {
            SetDefaultMapZoomAction();
        } else if (str.equals(GraphicsSystem.ACTION_NEW)) {
            newMapAction();
        } else if (str.equals(GraphicsSystem.ACTION_OPEN)) {
            loadMapAction();
        } else if (str.equals(GraphicsSystem.ACTION_CLOSE)) {
            closeApplicationAction();
        } else if (str.equals(GraphicsSystem.ACTION_SAVE)) {
            saveMapAction();
        } else if (str.equals(GraphicsSystem.ACTION_MAP_ATTRIBUTES_PANEL)) {
            attributesMapAction();
        }
        mapPanel.repaint();
        getJFrame().requestFocus();
    }

    private void saveMapApi() {
        /*zapisuje map� */
        JFileChooser FC = new JFileChooser();
        FC.setCurrentDirectory(new File("." + File.separator + "Maps"));


        ExampleFileFilter rfilter = new ExampleFileFilter("xml", "XML Files");

        FC.setFileFilter(rfilter);
        FC.setSelectedFile(mapApi.getFile());


        int res = FC.showSaveDialog(getJFrame());
        if (res == JFileChooser.APPROVE_OPTION) {
            File rFile = FC.getSelectedFile();
            MapSaver p_MapSaver = new MapSaver(messages, mapThemesList);
            MapApi p_MapApi = mapApi;

            try {
                p_MapSaver.SaveMapToFile(p_MapApi, rFile);
            } catch (Exception e) {

                String msg = messages.getString("SavingFailed") + " " + e.getMessage();
                JOptionPane.showMessageDialog(FC, msg);
            }
        }
    }

    /**
     * Creates new map. Saves current and clears it.
     */
    private void newMapAction() {
        JOptionPane dlg = new JOptionPane();
        int res = JOptionPane.showConfirmDialog(this.jFrame, messages.getString("SaveChanges?"),
                null, JOptionPane.YES_NO_OPTION);
        if (res == JOptionPane.YES_OPTION) {
            this.saveMapApi();
        }
        MapAttributesPanel MRP = new MapAttributesPanel(config, messages, jFrame);

        MRP.activate(mapApi.getRowsSize(), mapApi.getColumnsSize());

        if (!MRP.getCanceled()) {
            int row = MRP.getSelectedRow();
            int col = MRP.getSelectedCol();

            mapApi.resetMap(row, col);
        }

    }

    /**
     * Loads new map from file.
     */
    private void loadMapAction() {
        int res = JOptionPane.showConfirmDialog(jFrame, messages.getString("SaveChanges?"));
        if (res == JOptionPane.YES_OPTION) {
            saveMapApi();
            loadMapApi();
        } else if (res == JOptionPane.NO_OPTION) {
            loadMapApi();
        }
    }

    /**
     * Saves map to file.
     */
    private void saveMapAction() {
        saveMapApi();
    }

    /**
     * Resizes map without removing current MapObjects
     */
    private void attributesMapAction() {
        /*otwiera okno ustawie� wymiar�w nowej mapy*/
        MapAttributesPanel mapAttrinbutesPanel = new MapAttributesPanel(config, messages, jFrame);

        mapAttrinbutesPanel.activate(mapApi.getRowsSize(), mapApi.getColumnsSize());

        if (!mapAttrinbutesPanel.getCanceled()) {
            int row = mapAttrinbutesPanel.getSelectedRow();
            int col = mapAttrinbutesPanel.getSelectedCol();

            mapApi.changeSize(row, col);
        }
    }

    /**
     * Quits application
     */
    private void closeApplicationAction() {
        int res = JOptionPane.showConfirmDialog(jFrame, messages.getString("SaveChanges?"));
        if (res == JOptionPane.YES_OPTION) {
            saveMapApi();
        }
        System.exit(0);
    }

    /**
     * Loads new map
     */
    private void loadMapApi() {
        JFileChooser FC = new JFileChooser();
        FC.setCurrentDirectory(new File("." + File.separator + "Maps"));

        ExampleFileFilter rfilter = new ExampleFileFilter("xml", "XML Files");

        FC.setFileFilter(rfilter);
        FC.setSelectedFile(mapApi.getFile());

        int res = FC.showOpenDialog(getJFrame());
        if (res == JFileChooser.APPROVE_OPTION) {
            File rFile = FC.getSelectedFile();
            MapLoader p_MapLoader = new MapLoader();

            try {
                mapApi = p_MapLoader.loadMapFromFile(rFile, mapThemesList);
                mapPanel.setMapApi(mapApi);
                getJFrame().repaint();
            } catch (Exception e) {

                String msg = messages.getString("LoadingFailed") + e.getMessage();
                JOptionPane.showMessageDialog(FC, msg);

            }
        }
    }

    public MapObject getSelectedMapObject() {
        return bmpPanel.getSelectedMapObject();
    }
}
