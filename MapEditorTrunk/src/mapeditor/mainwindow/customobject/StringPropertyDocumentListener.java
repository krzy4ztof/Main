package mapeditor.mainwindow.customobject;

import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;

public class StringPropertyDocumentListener implements DocumentListener {

	private CustomObjectPane customObjectPane;

	private StringPropertyControl stringPropertyControl;

	public StringPropertyDocumentListener(CustomObjectPane customObjectPane,
			StringPropertyControl stringPropertyControl) {
		// this.property = property;
		this.customObjectPane = customObjectPane;
		this.stringPropertyControl = stringPropertyControl;
	}

	@Override
	public void changedUpdate(DocumentEvent event) {

		String value = stringPropertyControl.getTextField().getText();

		System.out.println(event);
		System.out.println(value);
		System.out.println("changedUpdate");
		// TODO Auto-generated method stub

		stringPropertyControl.setNewValue(value);
		customObjectPane.enableButtons();

	}

	@Override
	public void insertUpdate(DocumentEvent event) {
		// TODO Auto-generated method stub

		String value = stringPropertyControl.getTextField().getText();

		System.out.println(event);
		System.out.println(stringPropertyControl.getTextField().getText());
		System.out.println("insertUpdate");
		stringPropertyControl.setNewValue(value);
		customObjectPane.enableButtons();

	}

	@Override
	public void removeUpdate(DocumentEvent event) {
		// TODO Auto-generated method stub

		String value = stringPropertyControl.getTextField().getText();

		System.out.println(event);
		System.out.println(stringPropertyControl.getTextField().getText());
		System.out.println("removeUpdate");

		stringPropertyControl.setNewValue(value);
		customObjectPane.enableButtons();

	}

}
