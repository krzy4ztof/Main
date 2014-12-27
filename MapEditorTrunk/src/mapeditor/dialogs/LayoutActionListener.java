package mapeditor.dialogs;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JComboBox;

import mapeditor.mapapi.MapAttributes;

public class LayoutActionListener implements ActionListener {

	private MapAttributes mapAttributes;

	public LayoutActionListener(MapAttributes selectedMapAttributes) {
		// TODO Auto-generated constructor stub
		this.mapAttributes = mapAttributes;
	}

	@Override
	public void actionPerformed(ActionEvent event) {
		// TODO Auto-generated method stub
		System.out.println(event.getSource());
		System.out.println(event.getActionCommand());

		Object source = event.getSource();
		if (source instanceof JComboBox) {
			JComboBox<MapLayoutWrapper> combo = (JComboBox<MapLayoutWrapper>) source;
			System.out.println(combo.getSelectedItem().getClass().getName());
			// MapLayoutWrapper mapLayout = combo.getSelectedItem();
			MapLayoutWrapper mapLayout = (MapLayoutWrapper) combo
					.getSelectedItem();
			mapAttributes.setMapLayout(mapLayout.getMapLayout());

		}

	}
}
