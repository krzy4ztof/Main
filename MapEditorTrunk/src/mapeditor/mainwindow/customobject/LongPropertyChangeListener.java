package mapeditor.mainwindow.customobject;

import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;

public class LongPropertyChangeListener implements PropertyChangeListener {

	private CustomObjectPane customObjectPane;

	private LongPropertyControl longPropertyControl;

	public LongPropertyChangeListener(CustomObjectPane customObjectPane,
			LongPropertyControl longPropertyControl) {
		this.customObjectPane = customObjectPane;
		this.longPropertyControl = longPropertyControl;
	}

	@Override
	public void propertyChange(PropertyChangeEvent event) {
		Object valueObj = event.getNewValue();

		if (valueObj != null && valueObj instanceof Long) {
			longPropertyControl.setNewValue((Long) valueObj);
			customObjectPane.enableButtons();
		}
	}
}
