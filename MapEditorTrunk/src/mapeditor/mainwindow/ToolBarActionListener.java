package mapeditor.mainwindow;

import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Enumeration;

import javax.swing.AbstractButton;
import javax.swing.ButtonGroup;
import javax.swing.ButtonModel;
import javax.swing.DefaultButtonModel;
import javax.swing.JButton;

import mapeditor.mapapi.Tools;
import mapeditor.mapapi.Tools.ToolsEnum;

public class ToolBarActionListener implements ActionListener {

	private Tools tools;

	public ToolBarActionListener(Tools tools) {
		this.tools = tools;
	}

	@Override
	public void actionPerformed(ActionEvent event) {
		String str = event.getActionCommand();
		Object sourceObject = event.getSource();

		if (sourceObject instanceof JButton) {
			JButton button = (JButton) sourceObject;

			ButtonModel buttonModel = button.getModel();
			System.out.println("Button Model:" + buttonModel);
			if (buttonModel instanceof DefaultButtonModel) {
				ButtonGroup buttonGroup = ((DefaultButtonModel) buttonModel)
						.getGroup();
				buttonGroup.clearSelection();
				Enumeration<AbstractButton> enumButtons = buttonGroup
						.getElements();

				while (enumButtons.hasMoreElements()) {
					enumButtons.nextElement().setBackground(null);
				}

				button.setSelected(true);
				button.setBackground(new Color(255, 211, 136));
			}
		}

		System.out.println("Toolbar: " + event.getActionCommand());
		System.out.println("Source: " + event.getSource());

		if (str.equals(MainWindow.ACTION_TOOLBAR_ERASER)) {
			tools.setActiveTool(ToolsEnum.ERASER);
		} else if (str.equals(MainWindow.ACTION_TOOLBAR_BRUSH)) {
			tools.setActiveTool(ToolsEnum.BRUSH);
		} else if (str.equals(MainWindow.ACTION_TOOLBAR_BUCKET)) {
			tools.setActiveTool(ToolsEnum.BUCKET);
		} else if (str.equals(MainWindow.ACTION_TOOLBAR_PICKER)) {
			tools.setActiveTool(ToolsEnum.PICKER);
		} else if (str.equals(MainWindow.ACTION_TOOLBAR_SELECTION)) {
			tools.setActiveTool(ToolsEnum.SELECTION);
		}

		System.out.println("Co wybrano: " + tools.getActiveTool());
	}
}
