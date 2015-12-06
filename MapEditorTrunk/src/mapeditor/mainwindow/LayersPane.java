package mapeditor.mainwindow;

import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.event.ActionListener;

import javax.swing.ButtonGroup;
import javax.swing.ImageIcon;
import javax.swing.JCheckBox;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JLayeredPane;
import javax.swing.JRadioButton;
import javax.swing.JScrollPane;
import javax.swing.JSeparator;
import javax.swing.SwingConstants;

import mapeditor.config.Config;

public class LayersPane {

	final static String ICON_OBJECT_16 = "hammer_16.png";
	final static String ICON_GRID_16 = "grid_16.png";
	final static String ACTION_LAYERS_BACKGROUND = "ACTION_LAYERS_BACKGROUND_";
	final static String ACTION_LAYERS_OBJECTS = "ACTION_LAYERS_OBJECTS_";
	final static String ACTION_LAYERS_ACTIVATION = "ACTION_LAYERS_ACTIVATION_";

	// private LayersPaneItemListener itemListener;

	// private LayersPaneActionListener actionListener;

	private JLayeredPane pane;

	private JScrollPane scrollPane;

	public LayersPane(Config config, LayersPaneActionListener actionListener) {
		super();

		// LayersPaneItemListener itemListener = new LayersPaneItemListener();
		// LayersPaneActionListener actionListener = new
		// LayersPaneActionListener();

		int layers = config.getMapApiLayersNumber();

		ImageIcon gridIcon = new ImageIcon(MainWindow.TOOLBAR_ICONS_FOLDER
				+ ICON_GRID_16);
		ImageIcon objectsIcon = new ImageIcon(MainWindow.TOOLBAR_ICONS_FOLDER
				+ ICON_OBJECT_16);
		ButtonGroup buttonGroup = new ButtonGroup();

		pane = new JLayeredPane();
		pane.setLayout(new GridBagLayout());

		GridBagConstraints c = new GridBagConstraints();
		c.fill = GridBagConstraints.BOTH;
		c.weightx = 1.0;
		c.weighty = 0.0;
		// c.insets = new Insets(0, 0, 0, 0);
		c.gridx = 0;

		for (int layer = 0; layer < layers; layer++) {
			// for (int layer = layers - 1; layer >= 0; layer--) {

			// c.gridy = layer * 2;

			c.gridy = (layers - 1 - layer) * 2;
			String layerText = getNameForLayer(layer);

			System.out.println("Layer no: " + layer + " name " + layerText
					+ " y: " + c.gridy);

			// for (int layer = 0; layer < layers; layer++) {
			// Layer no: 0 name I y: 0
			// Layer no: 1 name II y: 2
			// Layer no: 2 name III y: 4
			// Layer no: 3 name IV y: 6

			// for (int layer = layers - 1; layer >= 0; layer--) {
			// Layer no: 3 name IV y: 6
			// Layer no: 2 name III y: 4
			// Layer no: 1 name II y: 2
			// Layer no: 0 name I y: 0

			// JLayeredPane firstLayerPane = createLayerPane(layer, layerText,
			// gridIcon, objectsIcon, buttonGroup, itemListener,
			// actionListener);

			JLayeredPane firstLayerPane = createLayerPane(layer, layerText,
					gridIcon, objectsIcon, buttonGroup, actionListener);
			pane.add(firstLayerPane, c);

			c.gridy = layer * 2 + 1;
			pane.add(new JSeparator(SwingConstants.HORIZONTAL), c);

		}

		JLabel label = new JLabel();

		c.weighty = 1.0;
		c.gridx = 0;
		c.gridy = 6;
		pane.add(label, c);

		scrollPane = new JScrollPane(pane);
	}

	// private JLayeredPane createLayerPane(int layerNumber, String layerText,
	// ImageIcon gridIcon, ImageIcon hammerIcon, ButtonGroup buttonGroup,
	// ItemListener itemListener, ActionListener actionListener) {
	private JLayeredPane createLayerPane(int layerNumber, String layerText,
			ImageIcon gridIcon, ImageIcon hammerIcon, ButtonGroup buttonGroup,
			ActionListener actionListener) {
		JLayeredPane layerPane = new JLayeredPane();
		layerPane.setLayout(new GridBagLayout());

		GridBagConstraints c = new GridBagConstraints();
		c.fill = GridBagConstraints.BOTH;
		c.weightx = 0.0;
		c.weighty = 0.0;
		c.gridx = 0;
		c.gridy = 0;

		// JLayeredPane checkBoxPane = new JLayeredPane();
		// checkBoxPane.setLayout(new GridBagLayout());

		JCheckBox objectsButton = new JCheckBox(); // "O ", middleButtonIcon);
													// // new
		// objectsButton.setActionCommand(layerText +
		// " objects action command");
		objectsButton.setActionCommand(ACTION_LAYERS_OBJECTS + layerNumber);

		// objectsButton.addItemListener(itemListener);
		objectsButton.addActionListener(actionListener);// niepoprawne
		objectsButton.setSelected(true);
		// JCheckBox("O "
		// +
		// text);
		layerPane.add(objectsButton, c);

		JLabel hammerIconLabel = new JLabel(hammerIcon);

		c.gridx = 1;
		layerPane.add(hammerIconLabel, c);

		c.gridx = 2;
		JCheckBox backgroundButton = new JCheckBox(); // new JCheckBox("B " +
														// text);
		backgroundButton.setActionCommand(ACTION_LAYERS_BACKGROUND
				+ layerNumber);
		// backgroundButton.addItemListener(itemListener);
		backgroundButton.addActionListener(actionListener);// niepoprawne
		backgroundButton.setSelected(true);
		layerPane.add(backgroundButton, c);

		JLabel gridIconLabel = new JLabel(gridIcon);

		c.gridx = 3;
		layerPane.add(gridIconLabel, c);

		JRadioButton radioButton = new JRadioButton("Layer " + layerText);
		// radioButton.setActionCommand(layerText + " radio action command");

		radioButton.setActionCommand(ACTION_LAYERS_ACTIVATION + layerNumber);
		// radioButton.addItemListener(itemListener); // niepoprawne
		radioButton.addActionListener(actionListener);

		if (layerNumber == 0) {
			radioButton.setSelected(true);
		}

		c.gridx = 4;

		layerPane.add(radioButton, c);
		buttonGroup.add(radioButton);

		JLabel label = new JLabel();// new JLabel("L " + text);

		c.weightx = 1.0;
		c.gridx = 5;
		layerPane.add(label, c);

		return layerPane;
	}

	public JComponent getPane() {
		return pane;
	}

	public JScrollPane getScrollPane() {
		return scrollPane;
	}

	private String getNameForLayer(int layer) {
		layer++;

		// String[] list = new String[] { "0", "I", "II" };

		String[] list = new String[] { "0", "I", "II", "III", "IV", "V", "VI",
				"VII", "VIII", "IX", "X" };

		if (layer < list.length) {
			return list[layer];
		} else {
			return "-";
		}
	}
}
