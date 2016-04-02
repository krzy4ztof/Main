package mapeditor.mainwindow;

import java.awt.Color;
import java.awt.Container;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Enumeration;

import javax.swing.AbstractButton;
import javax.swing.ButtonGroup;
import javax.swing.ButtonModel;
import javax.swing.DefaultButtonModel;
import javax.swing.JButton;

import mapeditor.mainwindow.map.MapPane;
import mapeditor.mapapi.CopyPaste;
import mapeditor.mapapi.Tools;
import mapeditor.mapapi.Tools.ToolsEnum;

public class ToolBarActionListener implements ActionListener {

	private Tools tools;
	private MapPane mapPanel;
	private CursorFactory cursorFactory;
	private CopyPaste copyPaste;

	public ToolBarActionListener(Tools tools, CursorFactory cursorFactory,
			MapPane mapPanel, CopyPaste copyPaste) {
		this.tools = tools;
		this.cursorFactory = cursorFactory;
		this.mapPanel = mapPanel;
		this.copyPaste = copyPaste;
	}

	@Override
	public void actionPerformed(ActionEvent event) {

		if (tools.getActiveTool() == ToolsEnum.POINT_PROPERTY) {
			// locked
			return;
		}

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

				button.setSelected(true);
				button.setBackground(new Color(255, 211, 136));
			}

			Container container = button.getTopLevelAncestor();
			if (container != null) {
				container.requestFocus();
			}
		}

		if (str.equals(MainWindow.ACTION_TOOLBAR_ERASER)) {
			tools.setActiveTool(ToolsEnum.ERASER);
			mapPanel.getPanel().setCursor(
			// cursorFactory.getCursor(CursorFactory.CURSOR_ERASER));
					cursorFactory.getCursor(ToolsEnum.ERASER));
			copyPaste.onActionPerformed();
		} else if (str.equals(MainWindow.ACTION_TOOLBAR_BRUSH)) {
			tools.setActiveTool(ToolsEnum.BRUSH);
			mapPanel.getPanel().setCursor(
			// cursorFactory.getCursor(CursorFactory.CURSOR_BRUSH));
					cursorFactory.getCursor(ToolsEnum.BRUSH));

			copyPaste.onActionPerformed();
		} else if (str.equals(MainWindow.ACTION_TOOLBAR_BUCKET)) {
			tools.setActiveTool(ToolsEnum.BUCKET);
			mapPanel.getPanel().setCursor(
			// cursorFactory.getCursor(CursorFactory.CURSOR_BUCKET));
					cursorFactory.getCursor(ToolsEnum.BUCKET));
			copyPaste.onActionPerformed();

		} else if (str.equals(MainWindow.ACTION_TOOLBAR_PICKER)) {
			tools.setActiveTool(ToolsEnum.PICKER);
			mapPanel.getPanel().setCursor(
			// cursorFactory.getCursor(CursorFactory.CURSOR_PICKER));
					cursorFactory.getCursor(ToolsEnum.PICKER));

			copyPaste.onActionPerformed();
		} else if (str.equals(MainWindow.ACTION_TOOLBAR_SELECTION)) {
			tools.setActiveTool(ToolsEnum.SELECTION);
			mapPanel.getPanel().setCursor(
			// Cursor.getPredefinedCursor(Cursor.CROSSHAIR_CURSOR));
					cursorFactory.getCursor(ToolsEnum.SELECTION));

			copyPaste.onActionPerformed();
		} else if (str.equals(MainWindow.ACTION_TOOLBAR_HAMMER)) {
			tools.setActiveTool(ToolsEnum.HAMMER);
			mapPanel.getPanel().setCursor(
			// cursorFactory.getCursor(CursorFactory.CURSOR_HAMMER));
					cursorFactory.getCursor(ToolsEnum.HAMMER));
			copyPaste.onActionPerformed();
		}
	}
}
