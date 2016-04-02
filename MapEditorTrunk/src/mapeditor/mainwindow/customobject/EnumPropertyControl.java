package mapeditor.mainwindow.customobject;

import java.awt.GridBagLayout;
import java.awt.event.ItemListener;
import java.util.Map.Entry;

import javax.swing.ComboBoxModel;
import javax.swing.DefaultComboBoxModel;
import javax.swing.JComboBox;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JLayeredPane;
import javax.swing.JSeparator;
import javax.swing.ListCellRenderer;
import javax.swing.SwingConstants;

import mapeditor.themesapi.EnumProperty;

public class EnumPropertyControl extends ObjectPropertyControl {

	private String newKey;

	private EnumProperty enumProperty;

	private JComboBox<Entry<String, String>> comboBox;

	protected EnumPropertyControl(EnumProperty enumProperty,
			CustomObjectPane customObjectPane) {
		this.enumProperty = enumProperty;
		newKey = enumProperty.getKey();

		pane = new JLayeredPane();
		pane.setLayout(new GridBagLayout());

		/*
		 * GridBagConstraints c = new GridBagConstraints(); c.fill =
		 * GridBagConstraints.BOTH; c.weightx = 1.0; c.weighty = 0.0; c.gridx =
		 * 0; c.gridy = 0;
		 */

		label = new JLabel(enumProperty.getName());
		// c.gridx = 1;

		Entry<String, String>[] entryArray = enumProperty.getKeysEntrySet();

		ComboBoxModel<Entry<String, String>> comboBoxModel = new DefaultComboBoxModel<Entry<String, String>>(
				entryArray);

		comboBox = new JComboBox<Entry<String, String>>(comboBoxModel);
		comboBox.setSelectedItem(enumProperty.getCurrentEntry());

		ItemListener itlistener = new EnumPropertyItemListener(
				customObjectPane, this);
		comboBox.addItemListener(itlistener);

		ListCellRenderer<Entry<String, String>> renderer = new EnumListCellRenderer();
		comboBox.setRenderer(renderer);

		separator = new JSeparator(SwingConstants.HORIZONTAL);
	}

	public void setNewValue(String newKey) {
		this.newKey = newKey;
	}

	@Override
	public void onOkAction() {
		enumProperty.setKey(newKey);
	}

	@Override
	public void onCancelAction() {
		comboBox.setSelectedItem(enumProperty.getCurrentEntry());
	}

	@Override
	public JComponent getComponent() {
		return comboBox;
	}

}
