package mapeditor.mainwindow.customobject;

import java.awt.Component;
import java.util.Map.Entry;

import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.ListCellRenderer;

public class EnumListCellRenderer implements
		ListCellRenderer<Entry<String, String>> {

	@Override
	public Component getListCellRendererComponent(
			JList<? extends Entry<String, String>> list,
			Entry<String, String> value, int index, boolean isSelected,
			boolean cellHasFocus) {

		JLabel label = new JLabel(value.getValue());
		return label;
	}

}
