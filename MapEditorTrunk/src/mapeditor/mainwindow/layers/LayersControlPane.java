package mapeditor.mainwindow.layers;

import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.util.LinkedList;

import javax.swing.ButtonGroup;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JLayeredPane;
import javax.swing.JScrollPane;

import mapeditor.mapapi.LayerAttributes;
import mapeditor.mapapi.MapApi;
import mapeditor.mapapi.MapAttributes;

public class LayersControlPane {

	final static String ACTION_LAYERS_BACKGROUND = "ACTION_LAYERS_BACKGROUND_";
	final static String ACTION_LAYERS_OBJECTS = "ACTION_LAYERS_OBJECTS_";
	final static String ACTION_LAYERS_ACTIVATION = "ACTION_LAYERS_ACTIVATION_";

	private JLayeredPane pane;

	private JScrollPane scrollPane;

	private LinkedList<LayerControl> layerControlList;

	private JLabel lastLabel;

	private int activeLayersNumber;

	public LayersControlPane(MapApi mapApi,
			LayersPaneActionListener actionListener) {
		super();
		createPanes(actionListener);

		pane = new JLayeredPane();
		pane.setLayout(new GridBagLayout());

		activateLayers(mapApi);

		scrollPane = new JScrollPane(pane);

	}

	private void createPanes(LayersPaneActionListener actionListener) {

		ButtonGroup buttonGroup = new ButtonGroup();

		layerControlList = new LinkedList<LayerControl>();
		for (int i = 0; i < MapAttributes.MAX_LAYERS_NUMBER; i++) {
			LayerControl layerControl = new LayerControl(i, buttonGroup,
					actionListener);
			layerControlList.add(layerControl);
		}

	}

	private void activateLayers(MapApi mapApi) {

		activeLayersNumber = mapApi.getLayerAttributesSize();

		GridBagConstraints c = new GridBagConstraints();
		c.fill = GridBagConstraints.BOTH;
		c.weightx = 1.0;
		c.weighty = 0.0;
		c.gridx = 0;

		for (int layerIndex = 0; layerIndex < activeLayersNumber; layerIndex++) {
			LayerControl layerControl = layerControlList.get(layerIndex);

			LayerAttributes layerAttributes = mapApi
					.getLayerAttributes(layerIndex);

			layerControl.setBackgroundVisible(layerAttributes
					.isBackgroundVisible());
			layerControl.setObjectsVisible(layerAttributes.isObjectsVisible());
			layerControl.setActivation(layerAttributes.isActive());

			c.gridy = (activeLayersNumber - 1 - layerIndex) * 2;
			pane.add(layerControl.getPane(), c);

			c.gridy = (activeLayersNumber - 1 - layerIndex) * 2 + 1;
			pane.add(layerControl.getSeparator(), c);
		}

		lastLabel = new JLabel();

		c.weighty = 1.0;
		c.gridx = 0;
		c.gridy = activeLayersNumber * 2;
		pane.add(lastLabel, c);

	}

	public void update(MapApi mapApi) {
		int newLayers = mapApi.getLayerAttributesSize();

		if (newLayers != activeLayersNumber) {
			removeAll();
			activateLayers(mapApi);
		}

		pane.revalidate();
	}

	private void removeAll() {

		for (LayerControl layerControl : layerControlList) {
			pane.remove(layerControl.getPane());
			pane.remove(layerControl.getSeparator());

		}
		pane.remove(lastLabel);

	}

	public JComponent getPane() {
		return pane;
	}

	public JScrollPane getScrollPane() {
		return scrollPane;
	}

}
