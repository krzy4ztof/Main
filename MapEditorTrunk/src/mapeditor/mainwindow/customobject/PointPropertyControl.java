package mapeditor.mainwindow.customobject;

import java.awt.Color;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.event.ActionListener;
import java.beans.PropertyChangeListener;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JFormattedTextField;
import javax.swing.JLabel;
import javax.swing.JLayeredPane;
import javax.swing.JSeparator;
import javax.swing.SwingConstants;
import javax.swing.text.MaskFormatter;

import mapeditor.mainwindow.CursorFactory;
import mapeditor.mainwindow.MainWindow;
import mapeditor.mainwindow.map.MapPane;
import mapeditor.mapapi.CustomObjectEdit;
import mapeditor.mapapi.MapApi;
import mapeditor.mapapi.Point3D;
import mapeditor.mapapi.Tools;
import mapeditor.themesapi.PointProperty;

public class PointPropertyControl extends ObjectPropertyControl {

	private Point3D newPointValue;

	private PointProperty pointProperty;

	private JFormattedTextField formattedTextField;

	private JLayeredPane rightPane;

	private JButton button;

	private boolean isButtonActive;

	private CustomObjectEdit customObjectEdit;

	private MapApi mapApi;

	final static String ICON_ARROW_16 = "arrow_16.png";

	protected PointPropertyControl(PointProperty pointProperty,
			CustomObjectPane customObjectPane, MapApi mapApi, Tools tools,
			CursorFactory cursorFactory, MapPane mapPanel,
			CustomObjectEdit customObjectEdit) {
		this.pointProperty = pointProperty;
		newPointValue = pointProperty.getValue();
		this.customObjectEdit = customObjectEdit;
		this.mapApi = mapApi;

		pane = new JLayeredPane();
		pane.setLayout(new GridBagLayout());

		label = new JLabel(pointProperty.getName());

		rightPane = new JLayeredPane();
		rightPane.setLayout(new GridBagLayout());

		GridBagConstraints c = new GridBagConstraints();
		c.fill = GridBagConstraints.BOTH;
		c.weightx = 1.0;
		c.weighty = 0.0;
		c.gridx = 0;
		c.gridy = 0;

		/*
		 * pointer JLabel label = new JLabel();
		 * label.setText(pointProperty.getValue().toString());
		 * rightPane.add(label, c);
		 * 
		 * c.gridx++;
		 */

		// MaskFormatter maskFormatter = null;
		// try {
		// maskFormatter = new PointPropertyMaskFormatter("(###,###,###)");
		MaskFormatter maskFormatter = new PointPropertyMaskFormatter(mapApi);

		// } catch (ParseException e) {
		// TODO Auto-generated catch block
		// e.printStackTrace();
		// }

		formattedTextField = new JFormattedTextField(maskFormatter);
		// maskFormatter.setPlaceholder("(XXX,XXX,XXX)");

		// maskFormatter.setPlaceholderCharacter('1');

		// maskFormatter.install(formattedTextField);
		formattedTextField.setValue(pointProperty.getValue());
		// formattedTextField.setValue("123");
		// formattedTextField.setText("123");
		// formattedTextField.setText("123456");// -. (123,456, )
		maskFormatter.install(formattedTextField);
		PropertyChangeListener listener = new PointPropertyChangeListener(
				customObjectPane, this);
		formattedTextField.addPropertyChangeListener(listener);
		// formattedTextField.setText("(123,456, )");
		rightPane.add(formattedTextField, c);

		c.gridx++;
		button = new JButton();
		isButtonActive = false;

		// String imgLocation = MainWindow.TOOLBAR_ICONS_FOLDER
		// + "crosshair_8.png";
		String imgLocation = MainWindow.TOOLBAR_ICONS_FOLDER + ICON_ARROW_16;

		// imgLocation = MainWindow.TOOLBAR_ICONS_FOLDER + "arrow_sw_16.png";
		//
		// imgLocation = MainWindow.TOOLBAR_ICONS_FOLDER
		// + "arrow_medium_lower_left.png";

		// button.addActionListener(actionListener);
		// button.setActionCommand(actionCommand);
		// button.setToolTipText(toolTipText);

		String toolTipText = "XXX"; // messages.getString(MapMessages.TOOLBAR_HAMMER);

		button.setIcon(new ImageIcon(imgLocation, toolTipText));
		// buttonGroup.add(button);

		ActionListener buttonListener = new PointPropertyButtonActionListener(
				this, customObjectPane, tools, cursorFactory, mapPanel);
		button.addActionListener(buttonListener);

		rightPane.add(button, c);

		customObjectPane.getButtonGroup().add(button);

		// PropertyChangeListener listener = new LongPropertyChangeListener(
		// customObjectPane, this);
		// formattedTextField.addPropertyChangeListener(listener);

		separator = new JSeparator(SwingConstants.HORIZONTAL);

	}

	public boolean isButtonActive() {
		return isButtonActive;
	}

	public void setNewValue(Point3D newValue) {
		this.newPointValue = newValue;
	}

	public PointProperty getPointProperty() {
		return pointProperty;
	}

	@Override
	public void onOkAction() {
		if (newPointValue.x > mapApi.getColumnsSize()) {
			newPointValue.x = mapApi.getColumnsSize();
		}

		if (newPointValue.y > mapApi.getRowsSize()) {
			newPointValue.y = mapApi.getRowsSize();
		}

		if (newPointValue.z > mapApi.getLayerAttributesSize()) {
			newPointValue.z = mapApi.getLayerAttributesSize();
		}

		pointProperty.setValue(newPointValue);
		formattedTextField.setValue(newPointValue);
	}

	@Override
	public void onCancelAction() {
		newPointValue = pointProperty.getValue();
		formattedTextField.setValue(newPointValue);
		// formattedTextField.setText(pointProperty.getValue().toString());
	}

	@Override
	public JComponent getComponent() {
		return rightPane;
	}

	public void deactivateButton() {
		button.setBackground(null);
		button.setSelected(false);
		isButtonActive = false;
		customObjectEdit.setPointPropertyLocation(null);
	}

	public void activateButton() {
		button.setBackground(new Color(255, 211, 136));
		button.setSelected(true);
		isButtonActive = true;
		customObjectEdit.setPointPropertyLocation(newPointValue);
	}

	public void updateTextField(Point3D point) {
		formattedTextField.setValue(point);
	}
}
