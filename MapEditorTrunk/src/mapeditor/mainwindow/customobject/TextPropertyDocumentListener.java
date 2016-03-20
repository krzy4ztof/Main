package mapeditor.mainwindow.customobject;

import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;

public class TextPropertyDocumentListener implements DocumentListener {

	private CustomObjectPane customObjectPane;

	private TextPropertyControl textPropertyControl;

	public TextPropertyDocumentListener(CustomObjectPane customObjectPane,
			TextPropertyControl stringPropertyControl) {
		this.customObjectPane = customObjectPane;
		this.textPropertyControl = stringPropertyControl;
	}

	@Override
	public void changedUpdate(DocumentEvent event) {
		String value = textPropertyControl.getText();

		textPropertyControl.setNewValue(value);
		customObjectPane.enableButtons();

	}

	@Override
	public void insertUpdate(DocumentEvent event) {
		String value = textPropertyControl.getText();
		textPropertyControl.setNewValue(value);
		customObjectPane.enableButtons();
	}

	@Override
	public void removeUpdate(DocumentEvent event) {
		String value = textPropertyControl.getText();
		textPropertyControl.setNewValue(value);
		customObjectPane.enableButtons();
	}
}
