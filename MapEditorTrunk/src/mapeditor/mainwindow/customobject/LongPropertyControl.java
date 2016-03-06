package mapeditor.mainwindow.customobject;

import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.beans.PropertyChangeListener;
import java.text.NumberFormat;

import javax.swing.JFormattedTextField;
import javax.swing.JLabel;
import javax.swing.JLayeredPane;
import javax.swing.JSeparator;
import javax.swing.JTextField;
import javax.swing.SwingConstants;

import mapeditor.themesapi.LongProperty;

public class LongPropertyControl extends ObjectPropertyControl {

	private Long newLongValue;

	private LongProperty longProperty;

	private JFormattedTextField formattedTextField;

	protected LongPropertyControl(LongProperty longProperty,
			CustomObjectPane customObjectPane) {
		this.longProperty = longProperty;
		newLongValue = longProperty.getValue();

		pane = new JLayeredPane();
		pane.setLayout(new GridBagLayout());

		GridBagConstraints c = new GridBagConstraints();
		c.fill = GridBagConstraints.BOTH;
		c.weightx = 1.0;
		c.weighty = 0.0;
		c.gridx = 0;
		c.gridy = 0;

		label = new JLabel(longProperty.getName());
		// pane.add(label, c);

		c.gridx = 1;

		formattedTextField = new JFormattedTextField(
				NumberFormat.getIntegerInstance());
		formattedTextField.setValue(longProperty.getValue());
		PropertyChangeListener listener = new LongPropertyChangeListener(
				customObjectPane, this);
		formattedTextField.addPropertyChangeListener(listener);
		formattedTextField.setHorizontalAlignment(JTextField.RIGHT);
		// pane.add(formattedTextField, c);

		separator = new JSeparator(SwingConstants.HORIZONTAL);

	}

	public void setNewValue(Long newValue) {
		this.newLongValue = newValue;
	}

	@Override
	public void onOkAction() {
		longProperty.setValue(newLongValue);
	}

	@Override
	public void onCancelAction() {
		newLongValue = longProperty.getValue();
		formattedTextField.setValue(longProperty.getValue());
	}

	@Override
	public JTextField getTextField() {
		// TODO Auto-generated method stub
		return formattedTextField;
	}

}
