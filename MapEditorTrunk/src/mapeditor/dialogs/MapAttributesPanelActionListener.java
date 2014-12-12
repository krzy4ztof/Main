package mapeditor.dialogs;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import mapeditor.config.Config;

public class MapAttributesPanelActionListener implements ActionListener {

	private MapAttributesPanel mapAttributesPanel;
	private Config config;

	MapAttributesPanelActionListener(MapAttributesPanel mapAttributesPanel,
			Config config) {
		this.mapAttributesPanel = mapAttributesPanel;
		this.config = config;
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		String action = e.getActionCommand();
		if (action.equals(MapAttributesPanel.ACTION_OK)) {
			mapAttributesPanel.on_ok();
		} else if (action.equals(MapAttributesPanel.ACTION_DEFAULT_SIZE)) {
			mapAttributesPanel.selectedMapAttributes.setColumns(config
					.getMapApiColumnsNumber());
			mapAttributesPanel.selectedMapAttributes.setRows(config
					.getMapApiRowsNumber());

			mapAttributesPanel.colItem.setText((new Integer(
					mapAttributesPanel.selectedMapAttributes.getColumns()))
					.toString());
			mapAttributesPanel.rowItem.setText(new Integer(
					mapAttributesPanel.selectedMapAttributes.getRows())
					.toString());
		} else if (action.equals(MapAttributesPanel.ACTION_PREVIOUS_SIZE)) {
			mapAttributesPanel.selectedMapAttributes
					.setColumns(mapAttributesPanel.initialMapAttributes
							.getColumns());
			mapAttributesPanel.selectedMapAttributes
					.setRows(mapAttributesPanel.initialMapAttributes.getRows());
			mapAttributesPanel.colItem.setText(new Integer(
					mapAttributesPanel.selectedMapAttributes.getColumns())
					.toString());
			mapAttributesPanel.rowItem.setText(new Integer(
					mapAttributesPanel.selectedMapAttributes.getRows())
					.toString());
		} else if (action.equals(MapAttributesPanel.ACTION_CANCEL)) {
			mapAttributesPanel.canceled = true;
			mapAttributesPanel.dispose();
		}

	}

}
