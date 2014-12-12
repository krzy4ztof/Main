package mapeditor.mainwindow;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;

import javax.swing.JFileChooser;
import javax.swing.JOptionPane;

import mapeditor.config.Config;
import mapeditor.dialogs.MapAttributesPanel;
import mapeditor.mapapi.MapApi;
import mapeditor.messages.MapMessages;
import mapeditor.saveload.MapLoader;
import mapeditor.saveload.MapSaver;
import mapeditor.themesapi.MapThemesList;
import otherprods.ExampleFileFilter;

public class GraphicsSystemActionListener implements ActionListener {

	MapPanel mapPanel;

	GraphicsSystem gs;
	MapApi mapApi;
	MapMessages messages;
	MapThemesList mapThemesList;
	Config config;

	GraphicsSystemActionListener(GraphicsSystem gs, MapPanel mapPanel, MapApi mapApi,
			MapMessages messages, MapThemesList mapThemesList, Config config) {
		this.gs = gs;
		this.mapPanel = mapPanel;
		this.mapApi = mapApi;
		this.messages = messages;
		this.mapThemesList = mapThemesList;
		this.config = config;
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		/*
		 * prowadzi nas�uch 1. przycisk�w przesuwaj�cych map� 2. ???
		 * menu plik (otieranie/zamykanie nowych map - mo�e przenie�� to
		 * do graphics_systemu, otwieranie okien dialogowych do wyboru pliku
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
		gs.getJFrame().requestFocus();
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

	private void saveMapApi() {
		/* zapisuje map� */
		JFileChooser FC = new JFileChooser();
		FC.setCurrentDirectory(new File("." + File.separator + "Maps"));

		ExampleFileFilter rfilter = new ExampleFileFilter("xml", "XML Files");

		FC.setFileFilter(rfilter);
		FC.setSelectedFile(mapApi.getFile());

		int res = FC.showSaveDialog(gs.getJFrame());
		if (res == JFileChooser.APPROVE_OPTION) {
			File rFile = FC.getSelectedFile();
			MapSaver p_MapSaver = new MapSaver(messages, mapThemesList);
			MapApi p_MapApi = mapApi;

			try {
				p_MapSaver.SaveMapToFile(p_MapApi, rFile);
			} catch (Exception e) {

				String msg = messages.getMsgSavingFailed() + " "
						+ e.getMessage();
				JOptionPane.showMessageDialog(FC, msg);
			}
		}
	}

	/**
	 * Creates new map. Saves current and clears it.
	 */
	private void newMapAction() {
		JOptionPane dlg = new JOptionPane();
		int res = JOptionPane.showConfirmDialog(gs.getJFrame(),
				messages.getMsgSaveChanges(), null, JOptionPane.YES_NO_OPTION);
		if (res == JOptionPane.YES_OPTION) {
			this.saveMapApi();
		}
		MapAttributesPanel MRP = new MapAttributesPanel(config, messages,
				gs.getJFrame());

		MRP.activate(mapApi.getMapAttributes());

		if (!MRP.getCanceled()) {
			int row = MRP.getSelectedMapAttributes().getRows();
			int col = MRP.getSelectedMapAttributes().getColumns();

			mapApi.resetMap(row, col);
		}

	}

	/**
	 * Loads new map from file.
	 */
	private void loadMapAction() {
		int res = JOptionPane.showConfirmDialog(gs.getJFrame(),
				messages.getMsgSaveChanges());
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
	 * 
	 * @throws CloneNotSupportedException
	 */
	private void attributesMapAction() {
		/* otwiera okno ustawie� wymiar�w nowej mapy */
		MapAttributesPanel mapAttributesPanel = new MapAttributesPanel(config,
				messages, gs.getJFrame());

		mapAttributesPanel.activate(mapApi.getMapAttributes());

		if (!mapAttributesPanel.getCanceled()) {
			int row = mapAttributesPanel.getSelectedMapAttributes().getRows();
			int col = mapAttributesPanel.getSelectedMapAttributes()
					.getColumns();

			mapApi.changeSize(row, col);
		}
	}

	/**
	 * Quits application
	 */
	private void closeApplicationAction() {
		int res = JOptionPane.showConfirmDialog(gs.getJFrame(),
				messages.getMsgSaveChanges());
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

		int res = FC.showOpenDialog(gs.getJFrame());
		if (res == JFileChooser.APPROVE_OPTION) {
			File rFile = FC.getSelectedFile();
			MapLoader p_MapLoader = new MapLoader();

			try {
				mapApi = p_MapLoader.loadMapFromFile(rFile, mapThemesList);
				mapPanel.setMapApi(mapApi);
				gs.getJFrame().repaint();
			} catch (Exception e) {

				String msg = messages.getMsgLoadingFailed() + e.getMessage();
				JOptionPane.showMessageDialog(FC, msg);

			}
		}
	}

}
