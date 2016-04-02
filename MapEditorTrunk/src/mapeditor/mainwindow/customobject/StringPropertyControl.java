package mapeditor.mainwindow.customobject;

import java.awt.GridBagLayout;

import javax.swing.JLabel;
import javax.swing.JLayeredPane;
import javax.swing.JSeparator;
import javax.swing.JTextField;
import javax.swing.SwingConstants;
import javax.swing.event.DocumentListener;
import javax.swing.text.JTextComponent;

import mapeditor.themesapi.StringProperty;

public class StringPropertyControl extends ObjectPropertyControl {

	private String newStringValue;

	private StringProperty stringProperty;

	private JTextField textField;

	protected StringPropertyControl(StringProperty stringProperty,
			CustomObjectPane customObjectPane) {
		this.stringProperty = stringProperty;
		newStringValue = stringProperty.getValue();

		pane = new JLayeredPane();
		pane.setLayout(new GridBagLayout());
		/*
		 * GridBagConstraints c = new GridBagConstraints(); c.fill =
		 * GridBagConstraints.BOTH; c.weightx = 1.0; c.weighty = 0.0; c.gridx =
		 * 0; c.gridy = 0;
		 */
		label = new JLabel(stringProperty.getName());

		// c.gridx = 1;
		textField = new JTextField(stringProperty.getValue());

		DocumentListener documentListener = new StringPropertyDocumentListener(
				customObjectPane, this);
		textField.getDocument().addDocumentListener(documentListener);
		textField.setHorizontalAlignment(JTextField.RIGHT);

		separator = new JSeparator(SwingConstants.HORIZONTAL);
	}

	public void setNewValue(String newStringValue) {
		this.newStringValue = newStringValue;
	}

	@Override
	public void onOkAction() {
		stringProperty.setValue(newStringValue);
	}

	@Override
	public void onCancelAction() {
		newStringValue = stringProperty.getValue();
		textField.setText(stringProperty.getValue());
	}

	@Override
	public JTextComponent getComponent() {
		return textField;
	}

}
