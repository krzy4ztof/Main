package mapeditor.mainwindow;

import java.awt.Component;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.LayoutManager;
import java.util.LinkedList;

import javax.swing.ButtonGroup;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JLayeredPane;
import javax.swing.JRadioButton;
import javax.swing.JScrollPane;

import mapeditor.mapapi.LayerAttributes;
import mapeditor.mapapi.MapApi;

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
		for (int i = 0; i < 10; i++) {
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

			System.out.println(layerControl);
			layerControl.setBackgroundVisible(layerAttributes
					.isBackgroundVisible());
			layerControl.setObjectsVisible(layerAttributes.isObjectsVisible());
			layerControl.setActivation(layerAttributes.isActive());

			c.gridy = (activeLayersNumber - 1 - layerIndex) * 2;
			System.out.println("Layer no: " + layerIndex + " name "
					+ layerControl.getName() + " y: " + c.gridy);

			pane.add(layerControl.getPane(), c);

			c.gridy = (activeLayersNumber - 1 - layerIndex) * 2 + 1;

			pane.add(layerControl.getSeparator(), c);

			System.out.println("grid y " + c.gridy + " layer " + layerIndex
					+ " / " + activeLayersNumber);

		}

		System.out.println("KONIEC");
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
		/*
		 * for (JLayeredPane layeredPane : layersPaneList) {
		 * pane.remove(layeredPane); }
		 * 
		 * for (JSeparator separator : separatorsList) { pane.remove(separator);
		 * }
		 */
		pane.remove(lastLabel);

	}

	private void paneInfo(JLayeredPane layeredPane) {
		LayoutManager layout = layeredPane.getLayout();

		System.out.println("layeredPane layout: " + layout.getClass());
		if (layout instanceof GridBagLayout) {
			GridBagLayout gbLayout = (GridBagLayout) layout;

			for (Component component : layeredPane.getComponents()) {
				System.out.println(component);

				GridBagConstraints gbConstraints = gbLayout
						.getConstraints(component);

				System.out.println(gbConstraints + " x: " + gbConstraints.gridx
						+ " y: " + gbConstraints.gridy + " wx: "
						+ gbConstraints.weightx + " wy: "
						+ gbConstraints.weighty);

				if (component instanceof JRadioButton) {
					JRadioButton radioButton = (JRadioButton) component;
					String text = radioButton.getText();
					System.out.println("radio " + radioButton.getText());
					radioButton.setText("Next " + text);
				}
			}

			System.out.println("----	++++	----");
		}

	}

	public JComponent getPane() {
		return pane;
	}

	public JScrollPane getScrollPane() {
		return scrollPane;
	}

}
