package mapeditor.mainwindow.customobject;

import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;

public class StringPropertyDocumentListener implements DocumentListener {

	private CustomObjectPane customObjectPane;

	private StringPropertyControl stringPropertyControl;

	public StringPropertyDocumentListener(CustomObjectPane customObjectPane,
			StringPropertyControl stringPropertyControl) {
		this.customObjectPane = customObjectPane;
		this.stringPropertyControl = stringPropertyControl;
	}

	@Override
	public void changedUpdate(DocumentEvent event) {
		String value = stringPropertyControl.getComponent().getText();

		stringPropertyControl.setNewValue(value);
		customObjectPane.enableButtons();

	}

	@Override
	public void insertUpdate(DocumentEvent event) {
		String value = stringPropertyControl.getComponent().getText();
		stringPropertyControl.setNewValue(value);
		customObjectPane.enableButtons();

	}

	@Override
	public void removeUpdate(DocumentEvent event) {
		String value = stringPropertyControl.getComponent().getText();

		stringPropertyControl.setNewValue(value);
		customObjectPane.enableButtons();
	}

}
