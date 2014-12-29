package mapeditor.dialogs;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JComboBox;

import mapeditor.mapapi.MapAttributes;

public class LayoutActionListener implements ActionListener {

	private MapAttributes mapAttributes;

	public LayoutActionListener(MapAttributes mapAttributes) {
		this.mapAttributes = mapAttributes;
	}

	@Override
	public void actionPerformed(ActionEvent event) {
		Object source = event.getSource();
		if (source instanceof JComboBox) {
			JComboBox<?> combo = (JComboBox<?>) source;
			MapLayoutWrapper mapLayout = (MapLayoutWrapper) combo
					.getSelectedItem();
			mapAttributes.setMapLayout(mapLayout.getMapLayout());
		}

	}
}
