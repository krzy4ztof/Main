package mapeditor.mainwindow;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Image;
import java.util.Hashtable;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JPanel;

import mapeditor.mapapi.MapObject;
import mapeditor.themesapi.MapObjectsTheme;
import mapeditor.themesapi.MapThemesList;

public class BmpPanel extends JPanel {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	/**
	 * iconButtons - wskazniki do przyciskow z ikonami, symobole haszujace
	 * BmpPanel.ACTION_ICON_BUTTON+numer(1-8)
	 */
	private Hashtable<String, JButton> iconButtons = new Hashtable<String, JButton>();

	/**
	 * ImageNumber - numer ikony znajdujacej sie na przycisku
	 * iconButtons.get(BmpPanel.ACTION_ICON_BUTTON+"1")
	 */
	private int ImageNumber = 0; // Do skasowania

	private int SelectedImage = 0; // Do skasowania

	private MapObject curMapObject = null; // W zamian za ImageNumber i
											// SelectedImage

	private MapThemesList mapThemesList = null;

	/**
	 * Numer w Ikony ktorej aktualnie wybrano przyciskiem
	 * iconButtons.get(BmpPanel.ACTION_ICON_BUTTON+"x"). UWAGA!! Jest to numer
	 * Ikony a nie numer przycisku!!!
	 */

	final static String ACTION_SCROLL_UP = "ACTION_SCROLL_ICONS_UP";
	final static String ACTION_SCROLL_DOWN = "ACTION_SCROLL_ICONS_DOWN";
	final static String ACTION_ICON_BUTTON = "ACTION_ICON_BUTTON_";

	public BmpPanel(MapThemesList mapThemesListParam) {
		super();
		mapThemesList = mapThemesListParam;
	}

	public void activate(BmpPanelActionListener bmpListener) {
		JButton Btn;

		GridBagConstraints c = new GridBagConstraints();
		setLayout(new GridBagLayout());

		c.fill = GridBagConstraints.BOTH;
		c.weightx = 1.0;
		c.weighty = 1.0;

		int k = 0, i = 0;
		for (i = 0; i < 4; i++) {
			for (int j = 0; j < 2; j++) {
				Btn = new JButton();
				Btn.addActionListener(bmpListener);// zmieni sie na mapke
				Btn.setActionCommand(ACTION_ICON_BUTTON + Integer.toString(k));
				c.gridy = i;
				c.gridx = j;
				iconButtons.put(ACTION_ICON_BUTTON + Integer.toString(k), Btn);
				this.add(Btn, c);
				k++;
			}
		}

		iconButtons.get(ACTION_ICON_BUTTON + "0").setBackground(Color.RED);
		Btn = new JButton("^");
		Btn.addActionListener(bmpListener);// zmieni sie na mapke
		Btn.setActionCommand(ACTION_SCROLL_UP);
		c.weightx = 1.0;
		c.weighty = 0.0;
		c.gridx = 0;
		c.gridy = i;
		this.add(Btn, c);

		Btn = new JButton("V");
		Btn.addActionListener(bmpListener);// zmieni sie na mapke
		Btn.setActionCommand(ACTION_SCROLL_DOWN);
		c.gridx = 1;
		c.gridy = i;
		this.add(Btn, c);

		this.updateAvailableIcons();
	}

	@Override
	public void paint(Graphics g) {
		super.paint(g);
	}

	void updateAvailableIcons() {
		/**
		 * Aktualizuje zbior dostepnych Ikon na przyciskach Items
		 */
		MapObjectsTheme curMapObjectsTheme = mapThemesList.getCurrentTheme();
		int ThSize = curMapObjectsTheme.getThemeSize();

		int i = 0, k = 0;
		ImageIcon img, img_sc;
		JButton btn;
		for (i = this.ImageNumber; i < ThSize && k < 8; i++) {
			img = curMapObjectsTheme.getMapObject(i).getImageIcon();

			img_sc = new ImageIcon(img.getImage().getScaledInstance(40, 40,
					Image.SCALE_DEFAULT));

			btn = iconButtons.get(ACTION_ICON_BUTTON + Integer.toString(k));
			btn.setIcon(img_sc);
			k++;
		}

		for (i = k; i < 8; i++) {
			img = new ImageIcon("../Images/" + "null.jpg");
			img_sc = new ImageIcon(img.getImage().getScaledInstance(40, 40,
					Image.SCALE_DEFAULT));

			btn = iconButtons.get(ACTION_ICON_BUTTON + Integer.toString(i));
			btn.setIcon(img_sc);
		}
	}

	public MapObject getSelectedMapObject() {
		MapObject mapObject = null;
		mapObject = mapThemesList.getCurrentTheme().getMapObject(
				this.SelectedImage);
		return mapObject;
	}

	public void activateSelectedIconButton(String name, int selected) {
		iconButtons.get(name).setBackground(Color.RED);
		SelectedImage = selected;
	}

	public void deactivateSelectedIconButton(String name) {
		iconButtons.get(name).setBackground(Color.LIGHT_GRAY);
	}

	void ChangeActualButton(Color color) {

		// int nrInt = this.getActualButtonNumber();
		int nrInt = this.SelectedImage - this.ImageNumber;

		if ((nrInt >= 0) && (nrInt < 8)) {
			Integer nr = new Integer(nrInt);
			String command = ACTION_ICON_BUTTON + nr.toString();
			iconButtons.get(command).setBackground(color);
		}
	}

	public void moveIconsUp() {
		moveIcons(-1);
	}

	public void moveIconsDown() {
		moveIcons(+1);
	}

	private void moveIcons(int direction) {
		ChangeActualButton(Color.LIGHT_GRAY);
		ImageNumber = ImageNumber + direction;
		int maxNumber = mapThemesList.getCurrentTheme().getThemeSize();
		if (ImageNumber > maxNumber - 1) {
			ImageNumber = maxNumber - 1;
		}

		if (ImageNumber < 0) {
			ImageNumber = 0;
		}
		ChangeActualButton(Color.RED);
		updateAvailableIcons();

	}

	public void changeCurrentTheme(String name) {
		mapThemesList.setCurrentTheme(name);
		updateAvailableIcons();
	}

	public void changeSelectedIconButton(String name) {
		int length = BmpPanel.ACTION_ICON_BUTTON.length();

		int btn_number = Integer.parseInt(name.substring(length));
		// int maxNumber = bmpPanel.curMapObjectsTheme.getThemeSize();
		int maxNumber = mapThemesList.getCurrentTheme().getThemeSize();
		int sel = btn_number + ImageNumber;
		if (sel < maxNumber) {
			for (int i = 0; i < 8; i++) {

				deactivateSelectedIconButton(BmpPanel.ACTION_ICON_BUTTON
						+ Integer.toString(i));
			}
			activateSelectedIconButton(name, sel);
		}
	}
}
