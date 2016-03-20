package mapeditor.mainwindow.customobject;

import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.util.Map.Entry;

public class EnumPropertyItemListener implements ItemListener {

	private CustomObjectPane customObjectPane;

	private EnumPropertyControl enumPropertyControl;

	public EnumPropertyItemListener(CustomObjectPane customObjectPane,
			EnumPropertyControl enumPropertyControl) {
		this.customObjectPane = customObjectPane;
		this.enumPropertyControl = enumPropertyControl;
	}

	@Override
	public void itemStateChanged(ItemEvent event) {
		if (event.getStateChange() == ItemEvent.SELECTED) {
			Object item = event.getItem();

			if (item != null && item instanceof Entry<?, ?>) {
				Entry<String, String> entry = (Entry<String, String>) item;
				enumPropertyControl.setNewValue(entry.getKey());
				customObjectPane.enableButtons();
			}
		}
	}

}
