package mapeditor.mainwindow.customobject;

import java.awt.Font;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.util.LinkedList;
import java.util.List;

import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JLayeredPane;
import javax.swing.JScrollPane;
import javax.swing.JSeparator;

import mapeditor.mainwindow.MainWindow;
import mapeditor.mapapi.MapApi;
import mapeditor.messages.MapMessages;
import mapeditor.themesapi.CustomMapObject;
import mapeditor.themesapi.MapObjectProperty;

public class CustomObjectPane {

	private JLayeredPane pane;

	private JLayeredPane gridPane;

	private JLayeredPane buttonsPane;

	// private JLayeredPane titlePane;

	private JButton okButton;

	private JButton cancelButton;

	private JScrollPane scrollPane;

	private JLabel lastLabel;

	private JLabel titleLabel;
	private JSeparator titleSeparator;

	private List<ObjectPropertyControl> propertyControlList;

	private CustomMapObject customMapObject;

	final static String CONFIRM_BUTTON_16 = "confirm_button_16.png";
	final static String CANCEL_BUTTON_16 = "cancel_button_16.png";
	final static String ACTION_CUSTOM_OK = "ACTION_CUSTOM_OK";
	final static String ACTION_CUSTOM_CANCEL = "ACTION_CUSTOM_CANCEL";

	public CustomObjectPane(MapApi mapApi, MapMessages messages) {
		super();

		propertyControlList = new LinkedList<ObjectPropertyControl>();
		// createPanes(actionListener);

		pane = new JLayeredPane();

		/*
		 * pane = new JLayeredPane() { private static final long
		 * serialVersionUID = 6917006496243295424L;
		 * 
		 * @Override public void paint(Graphics g) {
		 * 
		 * GraphicsEnvironment env = GraphicsEnvironment
		 * .getLocalGraphicsEnvironment();
		 * 
		 * for (Font font : env.getAllFonts()) {
		 * System.out.println(font.getFontName());
		 * System.out.println(font.getStyle());
		 * 
		 * System.out.println(font.getSize());
		 * 
		 * System.out.println("-----------"); }
		 * 
		 * Font font = g.getFont();
		 * 
		 * System.out.println(font.getFontName());
		 * System.out.println(font.getStyle());
		 * 
		 * System.out.println(font.getSize());
		 * 
		 * } };
		 */
		pane.setLayout(new GridBagLayout());

		// /////////////////////////
		// activateLayers(mapApi);

		GridBagConstraints c = new GridBagConstraints();
		c.fill = GridBagConstraints.BOTH;
		c.weightx = 1.0;
		c.weighty = 0.0;
		c.gridx = 0;

		// titlePane = createTitlePane();
		titleLabel = new JLabel("", JLabel.CENTER);

		/*
		 * GraphicsEnvironment env = GraphicsEnvironment
		 * .getLocalGraphicsEnvironment();
		 * 
		 * for (Font font : env.getAllFonts()) {
		 * System.out.println(font.getFontName());
		 * System.out.println(font.getStyle());
		 * 
		 * System.out.println(font.getSize());
		 * 
		 * System.out.println("-----------"); }
		 */

		// 12 - default size
		titleLabel.setFont(new Font(null, Font.BOLD | Font.ITALIC, 16));
		titleSeparator = new JSeparator();

		buttonsPane = createButtonsPane(messages);

		lastLabel = new JLabel();

		c.weighty = 1.0;
		c.gridx = 0;
		c.gridy = 0;
		pane.add(lastLabel, c);

		// /////////////////////
		scrollPane = new JScrollPane(pane);

	}

	public JComponent getPane() {
		return pane;
	}

	public JScrollPane getScrollPane() {
		return scrollPane;
	}

	public void update(CustomMapObject customMapObject) {

		if (customMapObject == null) {
			return;
		}

		if (customMapObject != this.customMapObject) {
			removeAll();
			activateProperties(customMapObject);

			pane.revalidate();
		}

	}

	private void removeAll() {

		// if (titleLabel != null) {
		pane.remove(titleLabel);
		pane.remove(titleSeparator);

		// }

		// pane.remove(titlePane);

		/*
		 * for (ObjectPropertyControl propertyControl : propertyControlList) {
		 * pane.remove(propertyControl.getPane());
		 * pane.remove(propertyControl.getSeparator());
		 * 
		 * gridPane.remove(propertyControl.getLabel());
		 * gridPane.remove(propertyControl.getTextField()); }
		 */

		propertyControlList.clear();

		if (gridPane != null) {
			pane.remove(gridPane);
		}

		okButton.setEnabled(false);
		cancelButton.setEnabled(false);
		pane.remove(buttonsPane);
		pane.remove(lastLabel);

	}

	private JLayeredPane createPropertiesGrid() {

		gridPane = new JLayeredPane();
		gridPane.setLayout(new GridBagLayout());

		// /////////////////////////
		// activateLayers(mapApi);

		GridBagConstraints c = new GridBagConstraints();
		c.fill = GridBagConstraints.BOTH;
		c.weightx = 1.0;
		c.weighty = 0.0;
		c.gridx = 0;
		pane.add(titleSeparator, c);

		for (MapObjectProperty property : customMapObject
				.getMapObjectProperties()) {

			// ObjectPropertyControl propertyControl = new
			// ObjectPropertyControl(
			// property);

			ObjectPropertyControl propertyControl = ObjectPropertyControl
					.getControlInstance(property, this);

			if (propertyControl != null) {

				propertyControlList.add(propertyControl);
				c.gridy++;
				c.gridx = 0;

				// gridPane.add(propertyControl.getPane(), c);

				gridPane.add(propertyControl.getLabel(), c);

				c.gridx = 1;
				// c.gridx
				gridPane.add(propertyControl.getTextField(), c);

				// c.gridy++;
				// pane.add(propertyControl.getSeparator(), c);
			}

		}

		return gridPane;
	}

	private void activateProperties(CustomMapObject customMapObject) {
		this.customMapObject = customMapObject;
		GridBagConstraints c = new GridBagConstraints();
		c.fill = GridBagConstraints.BOTH;
		c.weightx = 1.0;
		c.weighty = 0.0;
		c.gridx = 0;
		c.gridy = 0;

		// titleLabel = new JLabel(customMapObject.getExternalName(),
		// JLabel.CENTER);

		titleLabel.setText(customMapObject.getExternalName());

		pane.add(titleLabel, c);

		c.gridy++;

		pane.add(createPropertiesGrid(), c);
		// c.gridy++;

		c.gridy++;
		pane.add(buttonsPane, c);

		lastLabel = new JLabel();

		c.weighty = 1.0;
		c.gridx = 0;
		c.gridy++;
		pane.add(lastLabel, c);

	}

	protected JLayeredPane createTitlePane() {
		JLayeredPane pane = new JLayeredPane();
		pane.setLayout(new GridBagLayout());

		GridBagConstraints c = new GridBagConstraints();
		c.fill = GridBagConstraints.BOTH;
		c.weightx = 1.0;
		c.weighty = 0.0;
		c.gridx = 0;
		c.gridy = 0;

		/*
		 * c.weightx = 0.33; pane.add(new JLabel("|"), c);
		 * 
		 * c.weightx = 0.34; c.gridx++;
		 */
		JLabel titleLabel = new JLabel("Title of", JLabel.CENTER);

		pane.add(titleLabel, c);
		/*
		 * c.weightx = 0.33; c.gridx++; pane.add(new JLabel("|"), c);
		 */
		return pane;
	}

	protected JLayeredPane createButtonsPane(MapMessages messages) {

		JLayeredPane pane = new JLayeredPane();
		pane.setLayout(new GridBagLayout());

		GridBagConstraints c = new GridBagConstraints();
		c.fill = GridBagConstraints.BOTH;
		c.weightx = 1.0;
		c.weighty = 0.0;
		c.gridx = 0;
		c.gridy = 0;

		// pane.add(new JLabel(), c);

		// c.weightx = 0.0;
		// c.gridx++;

		CustomPaneActionListener actionListener = new CustomPaneActionListener(
				this);

		String imgLocation = MainWindow.TOOLBAR_ICONS_FOLDER
				+ CONFIRM_BUTTON_16;
		Icon icon = new ImageIcon(imgLocation,
				messages.getString(MapMessages.ATTR_OK));

		// JButton button = new JButton();
		// button.setToolTipText(toolTipText);
		// button.setIcon(new ImageIcon(imgLocation, toolTipText));
		// buttonGroup.add(button);

		okButton = new JButton(icon);
		okButton.addActionListener(actionListener);
		okButton.setActionCommand(ACTION_CUSTOM_OK);
		okButton.setEnabled(false);
		pane.add(okButton, c);

		c.gridx++;
		// JFormattedTextField formattedTextField = new JFormattedTextField(
		// DateFormat.getDateInstance());

		String imgLocationReject = MainWindow.TOOLBAR_ICONS_FOLDER
				+ CANCEL_BUTTON_16;
		Icon iconReject = new ImageIcon(imgLocationReject,
				messages.getString(MapMessages.ATTR_CANCEL));

		cancelButton = new JButton(iconReject);
		cancelButton.addActionListener(actionListener);
		cancelButton.setActionCommand(ACTION_CUSTOM_CANCEL);

		cancelButton.setEnabled(false);
		pane.add(cancelButton, c);

		return pane;
	}

	public void enableButtons() {
		okButton.setEnabled(true);
		cancelButton.setEnabled(true);
		pane.revalidate();
	}

	private void disableButtons() {
		okButton.setEnabled(false);
		cancelButton.setEnabled(false);
		pane.revalidate();
	}

	public void onOkAction() {
		for (ObjectPropertyControl propertyControl : propertyControlList) {
			propertyControl.onOkAction();
		}
		disableButtons();
	}

	public void onCancelAction() {
		for (ObjectPropertyControl propertyControl : propertyControlList) {
			propertyControl.onCancelAction();
		}
		disableButtons();
	}

}
