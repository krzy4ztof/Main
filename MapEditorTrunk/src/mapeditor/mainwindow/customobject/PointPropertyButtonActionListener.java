package mapeditor.mainwindow.customobject;

import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Enumeration;

import javax.swing.AbstractButton;
import javax.swing.ButtonGroup;
import javax.swing.ButtonModel;
import javax.swing.DefaultButtonModel;
import javax.swing.JButton;

import mapeditor.mainwindow.CursorFactory;
import mapeditor.mainwindow.map.MapPane;
import mapeditor.mapapi.Tools;
import mapeditor.mapapi.Tools.ToolsEnum;

public class PointPropertyButtonActionListener implements ActionListener {

	private Tools tools;
	private MapPane mapPanel;
	private CursorFactory cursorFactory;
	private boolean active = false;
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
			mapPanel.getPanel().setCursor(cursorFactory
			// .getCursor(CursorFactory.CURSOR_POINT_PROPERTY));

					.getCursor(ToolsEnum.POINT_PROPERTY));
		} else {
			pointPropertyControl.deactivateButton();

			tools.restorePreviousTool();
			mapPanel.getPanel().setCursor(
					cursorFactory.getCursor(tools.getActiveTool()));

		}

		mapPanel.refresh();

	}

	public void actionPerformed_222(ActionEvent event) {
		String str = event.getActionCommand();
		Object sourceObject = event.getSource();

		if (sourceObject instanceof JButton) {
			JButton button = (JButton) sourceObject;

			ButtonModel buttonModel = button.getModel();
			if (buttonModel instanceof DefaultButtonModel) {
				ButtonGroup buttonGroup = ((DefaultButtonModel) buttonModel)
						.getGroup();
				buttonGroup.clearSelection();
				Enumeration<AbstractButton> enumButtons = buttonGroup
						.getElements();

				while (enumButtons.hasMoreElements()) {
					enumButtons.nextElement().setBackground(null);
				}

				// button.setBackground(new Color(255, 211, 136));
			}

			// button.setSelected(true);

			if (!active) {
				active = true;

				button.setBackground(new Color(255, 211, 136));
				button.setSelected(true);

				tools.setActiveTool(ToolsEnum.POINT_PROPERTY);
				mapPanel.getPanel().setCursor(cursorFactory
				// .getCursor(CursorFactory.CURSOR_POINT_PROPERTY));

						.getCursor(ToolsEnum.POINT_PROPERTY));
			} else {
				active = false;
				tools.restorePreviousTool();
				mapPanel.getPanel().setCursor(
						cursorFactory.getCursor(tools.getActiveTool()));

				button.setBackground(null);
			}

			// mapPanel.getPanel().setCursor(
			// Cursor.getPredefinedCursor(Cursor.CROSSHAIR_CURSOR));

			/*
			 * if (buttonModel instanceof DefaultButtonModel) { ButtonGroup
			 * buttonGroup = ((DefaultButtonModel) buttonModel) .getGroup();
			 * buttonGroup.clearSelection(); Enumeration<AbstractButton>
			 * enumButtons = buttonGroup .getElements();
			 * 
			 * while (enumButtons.hasMoreElements()) {
			 * enumButtons.nextElement().setBackground(null); }
			 * 
			 * button.setSelected(true); button.setBackground(new Color(255,
			 * 211, 136)); }
			 * 
			 * Container container = button.getTopLevelAncestor(); if (container
			 * != null) { container.requestFocus(); }
			 */
		}
	}
}
