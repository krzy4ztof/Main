package mapeditor.mainwindow.customobject;

import java.awt.Font;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.net.URL;
import java.util.LinkedList;
import java.util.List;

import javax.swing.ButtonGroup;
import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JLayeredPane;
import javax.swing.JScrollPane;
import javax.swing.JSeparator;

import mapeditor.mainwindow.CursorFactory;
import mapeditor.mainwindow.MainWindow;
import mapeditor.mainwindow.map.MapPane;
import mapeditor.mapapi.CustomObjectEdit;
import mapeditor.mapapi.MapApi;
import mapeditor.mapapi.Point3D;
import mapeditor.mapapi.Tools;
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
	private ButtonGroup buttonGroup;

	private List<ObjectPropertyControl> propertyControlList;

	private CustomMapObject customMapObject;
	private MapApi mapApi;
	private Tools tools;
	private CursorFactory cursorFactory;
	private MapPane mapPanel;
	private CustomObjectEdit customObjectEdit;

	final static String CONFIRM_BUTTON_16 = "confirm_button_16.png";
	final static String CANCEL_BUTTON_16 = "cancel_button_16.png";
	final static String ACTION_CUSTOM_OK = "ACTION_CUSTOM_OK";
	final static String ACTION_CUSTOM_CANCEL = "ACTION_CUSTOM_CANCEL";

	public CustomObjectPane(MapApi mapApi, MapMessages messages, Tools tools,
			CursorFactory cursorFactory, MapPane mapPanel,
			CustomObjectEdit customObjectEdit) {
		super();
		this.mapApi = mapApi;
		this.tools = tools;
		this.cursorFactory = cursorFactory;
		this.mapPanel = mapPanel;
		this.customObjectEdit = customObjectEdit;

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

	public List<ObjectPropertyControl> getPropertyControlList() {
		return propertyControlList;
	}

	public ButtonGroup getButtonGroup() {
		return buttonGroup;
	}

	public JComponent getPane() {
		return pane;
	}

	public JScrollPane getScrollPane() {
		return scrollPane;
	}

	public void deactivate() {
		removeAll();

		createEmptyPane();

		pane.revalidate();
	}

	private void createEmptyPane() {
		this.customMapObject = null;

		GridBagConstraints c = new GridBagConstraints();
		c.fill = GridBagConstraints.BOTH;
		c.weightx = 1.0;
		// c.weighty = 1.0;

		c.weighty = 0.0;
		c.gridx = 0;
		c.gridy = 0;

		lastLabel = new JLabel();

		c.weighty = 1.0;
		pane.add(lastLabel, c);

	}

	public void update(CustomMapObject customMapObject) {

		if (customMapObject != this.customMapObject) {
			removeAll();

			activateProperties(customMapObject);

			pane.revalidate();
		}

	}

	public void refresh() {
		for (ObjectPropertyControl propertyControl : propertyControlList) {
			propertyControl.refresh();
		}
		pane.revalidate();
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

		buttonGroup = new ButtonGroup();

		GridBagConstraints c = new GridBagConstraints();
		c.fill = GridBagConstraints.BOTH;
		c.weightx = 1.0;
		c.weighty = 0.0;
		c.gridx = 0;
		pane.add(titleSeparator, c);

		for (MapObjectProperty property : customMapObject
				.getMapObjectProperties()) {
			ObjectPropertyControl propertyControl = ObjectPropertyControl
					.getControlInstance(property, this, mapApi, tools,
							cursorFactory, mapPanel, customObjectEdit);

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
		// c.weighty = 1.0;

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

		URL url = ClassLoader
				.getSystemResource(MainWindow.TOOLBAR_ICONS_FOLDER_URL
						+ CONFIRM_BUTTON_16);
		Icon icon = new ImageIcon(url, messages.getString(MapMessages.ATTR_OK));

		okButton = new JButton(icon);
		okButton.addActionListener(actionListener);
		okButton.setActionCommand(ACTION_CUSTOM_OK);
		okButton.setEnabled(false);
		pane.add(okButton, c);

		c.gridx++;

		url = ClassLoader.getSystemResource(MainWindow.TOOLBAR_ICONS_FOLDER_URL
				+ CANCEL_BUTTON_16);
		icon = new ImageIcon(url, messages.getString(MapMessages.ATTR_CANCEL));

		cancelButton = new JButton(icon);
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
			updateCustomObjectEdit(propertyControl);
		}
		disableButtons();
		mapPanel.refresh();
	}

	public void updateCustomObjectEdit(ObjectPropertyControl propertyControl) {
		if (propertyControl instanceof PointPropertyControl) {
			PointPropertyControl pointPropertyControl = (PointPropertyControl) propertyControl;

			if (pointPropertyControl.isButtonActive()) {
				customObjectEdit.setPointPropertyLocation(pointPropertyControl
						.getPointProperty().getValue());
			}

		}
	}

	public void onCancelAction() {
		for (ObjectPropertyControl propertyControl : propertyControlList) {
			propertyControl.onCancelAction();
			updateCustomObjectEdit(propertyControl);
		}
		disableButtons();
		mapPanel.refresh();
	}

	public void updatePointPropertyControl(Point3D point) {

		for (ObjectPropertyControl propertyControl : propertyControlList) {
			if (propertyControl instanceof PointPropertyControl) {
				PointPropertyControl pointPropertyControl = (PointPropertyControl) propertyControl;

				if (pointPropertyControl.isButtonActive()) {
					pointPropertyControl.updateTextField(point);
				}
			}
		}
		enableButtons();
	}

}
