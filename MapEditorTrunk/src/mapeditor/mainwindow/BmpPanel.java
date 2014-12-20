package mapeditor.mainwindow;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JPanel;

import mapeditor.themesapi.MapObject;
import mapeditor.themesapi.MapObjectsTheme;
import mapeditor.themesapi.MapThemesManager;

public class BmpPanel extends JPanel {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	final static String ACTION_SCROLL_UP = "ACTION_SCROLL_ICONS_UP";
	final static String ACTION_SCROLL_DOWN = "ACTION_SCROLL_ICONS_DOWN";
	final static String ACTION_ICON_BUTTON = "ACTION_ICON_BUTTON_";

	private static final int COLUMNS = 2;
	private static final int ROWS = 3;

	private BmpPanelIconButtonsManager buttonsManager = new BmpPanelIconButtonsManager();
	/**
	 * ImageNumber - numer ikony znajdujacej sie na przycisku
	 * iconButtons.get(BmpPanel.ACTION_ICON_BUTTON+"1")
	 */
	private int ImageNumber = 0; // Do skasowania

	private int SelectedImage = 0; // Do skasowania

	private String selectedButtonName = "";

	private MapObject curMapObject = null; // W zamian za ImageNumber i
											// SelectedImage

	private MapThemesManager mapThemesManager = null;

	/**
	 * Numer w Ikony ktorej aktualnie wybrano przyciskiem
	 * iconButtons.get(BmpPanel.ACTION_ICON_BUTTON+"x"). UWAGA!! Jest to numer
	 * Ikony a nie numer przycisku!!!
	 */

	public BmpPanel(MapThemesManager mapThemesListParam) {
		super();
		mapThemesManager = mapThemesListParam;
	}

	public void activate(BmpPanelActionListener bmpListener) {
		GridBagConstraints c = new GridBagConstraints();
		setLayout(new GridBagLayout());

		c.fill = GridBagConstraints.BOTH;
		c.weightx = 1.0;
		c.weighty = 1.0;

		int row = 0;
		for (row = 0; row < ROWS; row++) {
			for (int col = 0; col < COLUMNS; col++) {
				int btnNr = col + COLUMNS * row;
				BmpPanelIconButton button = new BmpPanelIconButton(btnNr,
						bmpListener);
				/*
				 * button = new JButton();
				 * button.addActionListener(bmpListener);
				 * button.setActionCommand(getActionName(btnNr));
				 * iconButtons.put(getActionName(btnNr), button);
				 */
				c.gridy = row;
				c.gridx = col;
				add(button.getButton(), c);
				buttonsManager.addButton(button);
				// iconButtons.add(button);
			}
		}

		/*
		 * selectedButtonName = getActionName(0);
		 * activateSelectedIconButton(selectedButtonName); MapObjectsTheme
		 * curMapObjectsTheme = mapThemesList.getCurrentTheme();
		 * curMapObjectsTheme.setCurrentObject() img =
		 * curMapObjectsTheme.getMapObject(0).getImageIcon();
		 */

		MapObjectsTheme curMapObjectsTheme = mapThemesManager
				.getSelectedTheme();
		MapObject mapObject = curMapObjectsTheme.getMapObject(0);
		curMapObjectsTheme.setSelectedObject(mapObject);

		// iconButtons.get(selectedButtonName).setBackground(Color.RED);
		// iconButtons.get(getActionName(0)).setBackground(Color.RED);
		JButton button = new JButton("^");
		button.addActionListener(bmpListener);// zmieni sie na mapke
		button.setActionCommand(ACTION_SCROLL_UP);
		c.weightx = 1.0;
		c.weighty = 0.0;
		c.gridx = 0;
		c.gridy = row;
		add(button, c);

		button = new JButton("V");
		button.addActionListener(bmpListener);// zmieni sie na mapke
		button.setActionCommand(ACTION_SCROLL_DOWN);
		c.gridx = 1;
		c.gridy = row;
		add(button, c);

		updateAvailableIcons();
	}

	@Override
	public void paint(Graphics g) {
		super.paint(g);
	}

	void updateAvailableIcons() {
		/**
		 * Aktualizuje zbior dostepnych Ikon na przyciskach Items
		 */
		MapObjectsTheme curMapObjectsTheme = mapThemesManager
				.getSelectedTheme();
		int themeSize = curMapObjectsTheme.getThemeSize();

		int row = 0, col = 0;
		ImageIcon img;
		JButton btn;
		MapObject mapObject;

		for (row = 0; row < ROWS; row++) {
			for (col = 0; col < COLUMNS; col++) {
				int btnNr = col + row * COLUMNS;
				if (btnNr < themeSize) {
					mapObject = curMapObjectsTheme.getMapObject(btnNr);

					// img =
					// curMapObjectsTheme.getMapObject(btnNr).getImageIcon();
				} else {
					mapObject = curMapObjectsTheme.getNullObject();
					// img = new ImageIcon("../Images/" + "null.jpg");
				}
				buttonsManager.getIconButton(btnNr).setMapObject(mapObject);

				// img = new ImageIcon(img.getImage().getScaledInstance(40, 40,
				// Image.SCALE_DEFAULT));

				// btn = iconButtons.get(getActionName(btnNr));
				// btn.setIcon(img);
			}
		}
	}

	public MapObject getSelectedMapObject() {
		MapObject mapObject = null;
		mapObject = mapThemesManager.getSelectedTheme().getMapObject(
				this.SelectedImage);
		return mapObject;
	}

	public void activateSelectedIconButton(String name) {
		BmpPanelIconButton iconButton = buttonsManager.getIconButton(name);
		iconButton.getButton().setBackground(Color.RED);
		MapObject mapObject = iconButton.getMapObject();

		mapThemesManager.getSelectedTheme().setSelectedObject(mapObject);

		mapObject.describeYourself();
		// iconButtons.get(name).setBackground(Color.RED);
		// SelectedImage = selected;
	}

	public void deactivateSelectedIconButton(int number) {
		buttonsManager.getIconButton(number).getButton().setBackground(null);
		// .setBackground(Color.LIGHT_GRAY);

		// iconButtons.get(name).setBackground(Color.LIGHT_GRAY);
	}

	void ChangeActualButton(Color color) {

		// int nrInt = this.getActualButtonNumber();
		int nrInt = this.SelectedImage - this.ImageNumber;

		if ((nrInt >= 0) && (nrInt < (COLUMNS * ROWS))) {
			// Integer nr = new Integer(nrInt);
			// String command = ACTION_ICON_BUTTON + nr.toString();

			buttonsManager.getIconButton(nrInt).getButton()
					.setBackground(Color.RED);

			// String command = getActionName(nrInt);
			// iconButtons.get(command).setBackground(color);
		}
	}

	public void moveIconsUp() {
		moveIcons(-1);
	}

	public void moveIconsDown() {
		moveIcons(+1);
	}

	private void moveIcons(int direction) {

		/*
		 * ChangeActualButton(Color.LIGHT_GRAY); ImageNumber = ImageNumber +
		 * direction; int maxNumber =
		 * mapThemesList.getCurrentTheme().getThemeSize(); if (ImageNumber >
		 * maxNumber - 1) { ImageNumber = maxNumber - 1; }
		 * 
		 * if (ImageNumber < 0) { ImageNumber = 0; }
		 * ChangeActualButton(Color.RED); updateAvailableIcons();
		 */
	}

	public void changeCurrentTheme(String name) {
		mapThemesManager.setSelectedTheme(name);
		updateAvailableIcons();
	}

	public void changeSelectedIconButton(String name) {
		int length = BmpPanel.ACTION_ICON_BUTTON.length();

		int btn_number = Integer.parseInt(name.substring(length));
		// int maxNumber = bmpPanel.curMapObjectsTheme.getThemeSize();
		int maxNumber = mapThemesManager.getSelectedTheme().getThemeSize();
		int sel = btn_number + ImageNumber;
		if (sel < maxNumber) {
			for (int i = 0; i < (COLUMNS * ROWS); i++) {
				// String command = getActionName(i);
				deactivateSelectedIconButton(i);
			}
			activateSelectedIconButton(name);
		}
		System.out.println("selected: " + name);
	}
}
