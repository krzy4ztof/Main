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

		pane = new JLayeredPane();
		pane.setLayout(new GridBagLayout());

		GridBagConstraints c = new GridBagConstraints();
		c.fill = GridBagConstraints.BOTH;
		c.weightx = 1.0;
		c.weighty = 0.0;
		c.gridx = 0;

		titleLabel = new JLabel("", JLabel.CENTER);

		// 12 - default size
		titleLabel.setFont(new Font(null, Font.BOLD | Font.ITALIC, 16));
		titleSeparator = new JSeparator();

		buttonsPane = createButtonsPane(messages);

		lastLabel = new JLabel();

		c.weighty = 1.0;
		c.gridx = 0;
		c.gridy = 0;
		pane.add(lastLabel, c);

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
		pane.remove(titleLabel);
		pane.remove(titleSeparator);

		propertyControlList.clear();

		if (gridPane != null) {
			pane.remove(gridPane);
		}

		okButton.setEnabled(false);
		cancelButton.setEnabled(false);
		pane.remove(buttonsPane);
		pane.remove(lastLabel);

	}

	private void createTextPropertyGrid(
			TextPropertyControl textPropertyControl, GridBagConstraints c) {
		c.gridy++;

		c.gridx = 1;
		c.gridheight = textPropertyControl.getRowsNumber();
		gridPane.add(textPropertyControl.getComponent(), c);

		// left side
		c.gridx = 0;
		c.gridheight = 1;
		gridPane.add(textPropertyControl.getLabel(), c);

		for (int i = 0; i < textPropertyControl.getRowsNumber() - 1; i++) {
			c.gridy++;
			gridPane.add(new JLabel(), c);
		}
	}

	private JLayeredPane createPropertiesGrid() {
		gridPane = new JLayeredPane();
		gridPane.setLayout(new GridBagLayout());

		GridBagConstraints c = new GridBagConstraints();
		c.fill = GridBagConstraints.BOTH;
		c.weightx = 1.0;
		c.weighty = 0.0;
		c.gridx = 0;
		pane.add(titleSeparator, c);

		for (MapObjectProperty property : customMapObject
				.getMapObjectProperties()) {
			ObjectPropertyControl propertyControl = ObjectPropertyControl
					.getControlInstance(property, this);

			if (propertyControl != null) {

				propertyControlList.add(propertyControl);

				if (propertyControl instanceof TextPropertyControl) {
					createTextPropertyGrid(
							(TextPropertyControl) propertyControl, c);
				} else {
					c.gridy++;
					c.gridx = 0;

					gridPane.add(propertyControl.getLabel(), c);

					c.gridx = 1;
					gridPane.add(propertyControl.getComponent(), c);
				}
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

		titleLabel.setText(customMapObject.getExternalName());
		pane.add(titleLabel, c);

		c.gridy++;
		pane.add(createPropertiesGrid(), c);

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

		JLabel titleLabel = new JLabel("Title of", JLabel.CENTER);
		pane.add(titleLabel, c);

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

		CustomPaneActionListener actionListener = new CustomPaneActionListener(
				this);

		String imgLocation = MainWindow.TOOLBAR_ICONS_FOLDER
				+ CONFIRM_BUTTON_16;
		Icon icon = new ImageIcon(imgLocation,
				messages.getString(MapMessages.ATTR_OK));

		okButton = new JButton(icon);
		okButton.addActionListener(actionListener);
		okButton.setActionCommand(ACTION_CUSTOM_OK);
		okButton.setEnabled(false);
		pane.add(okButton, c);

		c.gridx++;

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
