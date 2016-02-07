package mapeditor.mainwindow.customobject;

import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.util.LinkedList;
import java.util.List;

import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JLayeredPane;
import javax.swing.JScrollPane;

import mapeditor.mapapi.MapApi;
import mapeditor.themesapi.CustomMapObject;
import mapeditor.themesapi.MapObjectProperty;

public class CustomObjectPane {

	private JLayeredPane pane;

	private JScrollPane scrollPane;

	private JLabel lastLabel;

	private List<ObjectPropertyControl> propertyControlList;

	private CustomMapObject customMapObject;

	public CustomObjectPane(MapApi mapApi) {
		super();

		propertyControlList = new LinkedList<ObjectPropertyControl>();
		// createPanes(actionListener);

		pane = new JLayeredPane();
		pane.setLayout(new GridBagLayout());

		// /////////////////////////
		// activateLayers(mapApi);

		GridBagConstraints c = new GridBagConstraints();
		c.fill = GridBagConstraints.BOTH;
		c.weightx = 1.0;
		c.weighty = 0.0;
		c.gridx = 0;

		lastLabel = new JLabel("CUSTOM MAP OBJECT PANE");

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
		for (ObjectPropertyControl propertyControl : propertyControlList) {
			pane.remove(propertyControl.getPane());

		}
		propertyControlList.clear();
		pane.remove(lastLabel);
	}

	private void activateProperties(CustomMapObject customMapObject) {
		this.customMapObject = customMapObject;
		GridBagConstraints c = new GridBagConstraints();
		c.fill = GridBagConstraints.BOTH;
		c.weightx = 1.0;
		c.weighty = 0.0;
		c.gridx = 0;
		c.gridy = 0;

		ObjectPropertyControl propertyControl = new ObjectPropertyControl(
				customMapObject.getObjectName());

		propertyControlList.add(propertyControl);
		pane.add(propertyControl.getPane(), c);

		for (MapObjectProperty property : customMapObject
				.getMapObjectProperties()) {
			propertyControl = new ObjectPropertyControl(property.getName());
			propertyControlList.add(propertyControl);
			c.gridy++;
			pane.add(propertyControl.getPane(), c);

		}

		lastLabel = new JLabel("CUSTOM MAP OBJECT PANE LAST LABEL");

		c.weighty = 1.0;
		c.gridx = 0;
		c.gridy++;
		pane.add(lastLabel, c);

	}

}
