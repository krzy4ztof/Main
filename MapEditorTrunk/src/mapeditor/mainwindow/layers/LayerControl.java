package mapeditor.mainwindow.layers;

import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.net.URL;

import javax.swing.ButtonGroup;
import javax.swing.ImageIcon;
import javax.swing.JCheckBox;
import javax.swing.JLabel;
import javax.swing.JLayeredPane;
import javax.swing.JRadioButton;
import javax.swing.JSeparator;
import javax.swing.SwingConstants;

import mapeditor.mainwindow.MainWindow;

public class LayerControl {

	final static String ICON_OBJECT_16 = "hammer_16.png";
	final static String ICON_GRID_16 = "grid_16.png";

	private JLayeredPane pane;
	private JSeparator separator;
	private String name;
	private JCheckBox backgroundButton;
	private JCheckBox objectsButton;
	private JRadioButton activationButton;

	public void setBackgroundVisible(boolean isVisible) {
		backgroundButton.setSelected(isVisible);
	}

	public void setObjectsVisible(boolean isVisible) {
		objectsButton.setSelected(isVisible);
	}

	public void setActivation(boolean isActive) {
		activationButton.setSelected(isActive);
	}

	public String getName() {
		return name;
	}

	public JLayeredPane getPane() {
		return pane;
	}

	public JSeparator getSeparator() {
		return separator;
	}

	public LayerControl(int index, ButtonGroup buttonGroup,
			LayersPaneActionListener actionListener) {
		URL url = ClassLoader
				.getSystemResource(MainWindow.TOOLBAR_ICONS_FOLDER_URL
						+ ICON_GRID_16);
		ImageIcon gridIcon = new ImageIcon(url);

		url = ClassLoader.getSystemResource(MainWindow.TOOLBAR_ICONS_FOLDER_URL
				+ ICON_OBJECT_16);
		ImageIcon objectsIcon = new ImageIcon(url);

		pane = new JLayeredPane();
		pane.setLayout(new GridBagLayout());

		GridBagConstraints c = new GridBagConstraints();
		c.fill = GridBagConstraints.BOTH;
		c.weightx = 0.0;
		c.weighty = 0.0;
		c.gridx = 0;
		c.gridy = 0;

		objectsButton = new JCheckBox();
		objectsButton.setActionCommand(LayersControlPane.ACTION_LAYERS_OBJECTS
				+ index);

		objectsButton.addActionListener(actionListener);
		objectsButton.setSelected(true);

		pane.add(objectsButton, c);

		JLabel hammerIconLabel = new JLabel(objectsIcon);

		c.gridx = 1;
		pane.add(hammerIconLabel, c);

		c.gridx = 2;
		backgroundButton = new JCheckBox();
		backgroundButton
				.setActionCommand(LayersControlPane.ACTION_LAYERS_BACKGROUND
						+ index);

		backgroundButton.addActionListener(actionListener);
		backgroundButton.setSelected(true);

		// backgroundButton.setSelected(layerAttributes.isBackgroundVisible());
		pane.add(backgroundButton, c);

		JLabel gridIconLabel = new JLabel(gridIcon);

		c.gridx = 3;
		pane.add(gridIconLabel, c);
		name = getNameForLayer(index);
		activationButton = new JRadioButton("Layer " + name);
		activationButton
				.setActionCommand(LayersControlPane.ACTION_LAYERS_ACTIVATION
						+ index);
		activationButton.addActionListener(actionListener);

		if (index == 0) {
			activationButton.setSelected(true);
		}

		c.gridx = 4;

		pane.add(activationButton, c);
		buttonGroup.add(activationButton);

		JLabel label = new JLabel();
		c.weightx = 1.0;
		c.gridx = 5;
		pane.add(label, c);

		separator = new JSeparator(SwingConstants.HORIZONTAL);
	}

	private String getNameForLayer(int layer) {
		layer++;

		String[] list = new String[] { "0", "I", "II", "III", "IV", "V", "VI",
				"VII", "VIII", "IX", "X" };

		if (layer < list.length) {
			return list[layer];
		} else {
			return "-";
		}
	}
}
