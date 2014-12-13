package mapeditor.dialogs;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class MapAttributesPanelActionListener implements ActionListener {

	private MapAttributesPanel mapAttributesPanel;

	MapAttributesPanelActionListener(MapAttributesPanel mapAttributesPanel) {
		this.mapAttributesPanel = mapAttributesPanel;
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		String action = e.getActionCommand();
		if (action.equals(MapAttributesPanel.ACTION_OK)) {
			mapAttributesPanel.onOkAction();
		} else if (action.equals(MapAttributesPanel.ACTION_DEFAULT_SIZE)) {
			mapAttributesPanel.setDefaultSize();
		} else if (action.equals(MapAttributesPanel.ACTION_PREVIOUS_SIZE)) {
			mapAttributesPanel.setPreviousSize();
		} else if (action.equals(MapAttributesPanel.ACTION_CANCEL)) {
			mapAttributesPanel.onCancelAction();
		}

	}

}
