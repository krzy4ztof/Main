package mapeditor.mainwindow.customobject;

import java.awt.GridBagLayout;

import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JLayeredPane;
import javax.swing.JScrollPane;
import javax.swing.JSeparator;
import javax.swing.JTextArea;
import javax.swing.SwingConstants;
import javax.swing.event.DocumentListener;

import mapeditor.themesapi.TextProperty;

public class TextPropertyControl extends ObjectPropertyControl {

	private String newStringValue;

	private TextProperty stringProperty;

	private JTextArea textArea;

	private JScrollPane scrollPane;

	private int rowsNumber;

	protected TextPropertyControl(TextProperty stringProperty,
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

		rowsNumber = 5;
		textArea = new JTextArea(stringProperty.getValue(), rowsNumber, 0);

		scrollPane = new JScrollPane(textArea);

		DocumentListener documentListener = new TextPropertyDocumentListener(
				customObjectPane, this);
		textArea.getDocument().addDocumentListener(documentListener);

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
		textArea.setText(stringProperty.getValue());
	}

	@Override
	public JComponent getComponent() {
		return scrollPane;
	}

	public String getText() {
		return textArea.getText();
	}

	public int getRowsNumber() {
		return rowsNumber;
	}

}
