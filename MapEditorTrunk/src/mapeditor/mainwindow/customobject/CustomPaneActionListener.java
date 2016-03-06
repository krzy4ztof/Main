package mapeditor.mainwindow.customobject;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class CustomPaneActionListener implements ActionListener {

	CustomObjectPane customObjectPane;

	public CustomPaneActionListener(CustomObjectPane customObjectPane) {
		this.customObjectPane = customObjectPane;
	}

	@Override
	public void actionPerformed(ActionEvent event) {
		String str = event.getActionCommand();

		if (str.equals(CustomObjectPane.ACTION_CUSTOM_OK)) {
			customObjectPane.onOkAction();
		} else if (str.equals(CustomObjectPane.ACTION_CUSTOM_CANCEL)) {
			customObjectPane.onCancelAction();
		}

	}

}
