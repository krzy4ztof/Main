package mapeditor.dialogs;

import javax.swing.JList;
import javax.swing.ListSelectionModel;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

public class MapAttributesPanelListSelectionListener implements
		ListSelectionListener {

	@Override
	public void valueChanged(ListSelectionEvent e) {

		// e.getSource();
		JList<MapLayoutWrapper> list = (JList<MapLayoutWrapper>) e.getSource();
		System.out.println("VALUE: " + list.getSelectedValue());
		System.out.println("INDEX: " + list.getSelectedIndex());

		if (true) {
			return;
		}
		ListSelectionModel lsm = (ListSelectionModel) e.getSource();
		int firstIndex = e.getFirstIndex();
		int lastIndex = e.getLastIndex();
		boolean isAdjusting = e.getValueIsAdjusting();
		System.out.println("Event for indexes " + firstIndex + " - "
				+ lastIndex + "; isAdjusting is " + isAdjusting
				+ "; selected indexes:");

		if (lsm.isSelectionEmpty()) {
			System.out.println(" <none>");
		} else {
			// Find out which indexes are selected.
			int minIndex = lsm.getMinSelectionIndex();
			int maxIndex = lsm.getMaxSelectionIndex();
			for (int i = minIndex; i <= maxIndex; i++) {
				if (lsm.isSelectedIndex(i)) {
					System.out.println(" " + i);
				}
			}
		}
	}
}
