package mapeditor.mainwindow;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JToggleButton;

import mapeditor.mapapi.LayerAttributes;
import mapeditor.mapapi.MapApi;

public class LayersPaneActionListener implements ActionListener {

	private MapApi mapApi;

	private MapPane mapPane;

	public LayersPaneActionListener(MapApi mapApi, MapPane mapPane) {
		this.mapApi = mapApi;
		this.mapPane = mapPane;

	}

	@Override
	public void actionPerformed(ActionEvent actionEvent) {
		System.out.println("actionEvent: " + actionEvent);

		Object source = actionEvent.getSource();
		// if (source instanceof JCheckBox) {
		if (source instanceof JToggleButton) {
			// JCheckBox button = (JCheckBox) source;
			JToggleButton button = (JToggleButton) source;
			// ' int state = itemEvent.getStateChange();
			boolean state = button.getModel().isSelected();
			String command = button.getActionCommand();

			System.out.println("Command: " + command);

			if (command.startsWith(LayersPane.ACTION_LAYERS_OBJECTS)) {

				int number = getLayerNumber(command,
						LayersPane.ACTION_LAYERS_OBJECTS);

				LayerAttributes layerAttributes = mapApi
						.getLayerAttributes(number);

				if (state == true) {

					// layerAttributes.setBackgroundVisible(state);
					System.out.println("OBJECTS layer: " + number
							+ " ACTION SELECTED");
				} else if (state == false) {
					System.out.println("OBJECTS layer: " + number
							+ " ACTION DESELECTED");

				}
				layerAttributes.setObjectsVisible(state);

			} else if (command.startsWith(LayersPane.ACTION_LAYERS_BACKGROUND)) {
				int number = getLayerNumber(command,
						LayersPane.ACTION_LAYERS_BACKGROUND);

				LayerAttributes layerAttributes = mapApi
						.getLayerAttributes(number);

				if (state == true) {
					System.out.println("BACKGROUND layer: " + number
							+ " ACTION SELECTED");
				} else if (state == false) {
					System.out.println("BACKGROUND layer: " + number
							+ " ACTION DESELECTED");
				}
				layerAttributes.setBackgroundVisible(state);

			} else if (command.startsWith(LayersPane.ACTION_LAYERS_ACTIVATION)) {
				int number = getLayerNumber(command,
						LayersPane.ACTION_LAYERS_ACTIVATION);

				if (state == true) {
					System.out.println("RADIO layer: " + number
							+ " ACTION SELECTED");
				} else if (state == false) {
					System.out.println("RADIO layer: " + number
							+ " ACTION DESELECTED");
				}

				mapApi.setActiveLayerIndex(number);

			}
		}

		// mapPanel.getPanel().repaint();
		mapPane.refresh();

		// return focus to top frame. Focus allows GraphicsSystemKeyListener to
		// handle key events.
		mapPane.getPanel().getTopLevelAncestor().requestFocus();
		System.out.println("----------------------");
	}

	private int getLayerNumber(String command, String prefix) {
		int number = 0;

		String suffix = command.substring(prefix.length());

		number = Integer.parseInt(suffix);

		System.out.println("Prefix: " + prefix + " number: " + number
				+ " suffix: " + suffix);
		return number;
	}
}