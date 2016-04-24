package mapeditor.mainwindow.customobject;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import mapeditor.mainwindow.CursorFactory;
import mapeditor.mainwindow.map.MapPane;
import mapeditor.mapapi.Tools;
import mapeditor.mapapi.Tools.ToolsEnum;

public class PointPropertyButtonActionListener implements ActionListener {

	private Tools tools;
	private MapPane mapPanel;
	private CursorFactory cursorFactory;
	private PointPropertyControl pointPropertyControl;
	private CustomObjectPane customObjectPane;

	public PointPropertyButtonActionListener(
			PointPropertyControl pointPropertyControl,
			CustomObjectPane customObjectPane, Tools tools,
			CursorFactory cursorFactory, MapPane mapPanel) {
		this.tools = tools;
		this.cursorFactory = cursorFactory;
		this.mapPanel = mapPanel;
		this.pointPropertyControl = pointPropertyControl;
		this.customObjectPane = customObjectPane;
	}

	@Override
	public void actionPerformed(ActionEvent event) {

		if (!pointPropertyControl.isButtonActive()) {

			for (ObjectPropertyControl propertyControl : customObjectPane
					.getPropertyControlList()) {
				if (propertyControl instanceof PointPropertyControl) {
					PointPropertyControl pointPropertyControl = (PointPropertyControl) propertyControl;
					pointPropertyControl.deactivateButton();
				}

			}

			pointPropertyControl.activateButton();

			tools.setActiveTool(ToolsEnum.POINT_PROPERTY);
			mapPanel.getPanel().setCursor(
					cursorFactory.getCursor(ToolsEnum.POINT_PROPERTY));
		} else {
			pointPropertyControl.deactivateButton();

			tools.restorePreviousTool();
			mapPanel.getPanel().setCursor(
					cursorFactory.getCursor(tools.getActiveTool()));

		}

		mapPanel.refresh();

	}
}
