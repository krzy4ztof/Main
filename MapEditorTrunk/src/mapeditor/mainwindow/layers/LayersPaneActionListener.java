package mapeditor.mainwindow.layers;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JToggleButton;

import mapeditor.mainwindow.map.MapPane;
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

		Object source = actionEvent.getSource();
		if (source instanceof JToggleButton) {
			JToggleButton button = (JToggleButton) source;
			boolean state = button.getModel().isSelected();
			String command = button.getActionCommand();

			if (command.startsWith(LayersControlPane.ACTION_LAYERS_OBJECTS)) {
				int number = getLayerNumber(command,
						LayersControlPane.ACTION_LAYERS_OBJECTS);

				LayerAttributes layerAttributes = mapApi
						.getLayerAttributes(number);

				layerAttributes.setObjectsVisible(state);

			} else if (command
					.startsWith(LayersControlPane.ACTION_LAYERS_BACKGROUND)) {
				int number = getLayerNumber(command,
						LayersControlPane.ACTION_LAYERS_BACKGROUND);

				LayerAttributes layerAttributes = mapApi
						.getLayerAttributes(number);

				layerAttributes.setBackgroundVisible(state);
			} else if (command
					.startsWith(LayersControlPane.ACTION_LAYERS_ACTIVATION)) {
				int number = getLayerNumber(command,
						LayersControlPane.ACTION_LAYERS_ACTIVATION);

				mapApi.setActiveLayerIndex(number);

			}
		}

		mapPane.refresh();

		// return focus to top frame. Focus allows GraphicsSystemKeyListener to
		// handle key events.
		mapPane.getPanel().getTopLevelAncestor().requestFocus();
	}

	private int getLayerNumber(String command, String prefix) {
		int number = 0;
		String suffix = command.substring(prefix.length());
		number = Integer.parseInt(suffix);

		return number;
	}
}