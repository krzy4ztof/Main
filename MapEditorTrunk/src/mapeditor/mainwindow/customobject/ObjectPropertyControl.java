package mapeditor.mainwindow.customobject;

import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JLayeredPane;
import javax.swing.JSeparator;

import mapeditor.themesapi.EnumProperty;
import mapeditor.themesapi.LongProperty;
import mapeditor.themesapi.MapObjectProperty;
import mapeditor.themesapi.PointProperty;
import mapeditor.themesapi.StringProperty;
import mapeditor.themesapi.TextProperty;

public abstract class ObjectPropertyControl {

	protected JLabel label;

	protected JLayeredPane pane;

	protected JSeparator separator;

	public static ObjectPropertyControl getControlInstance(
			MapObjectProperty property, CustomObjectPane customObjectPane) {

		if (property instanceof EnumProperty) {
			return new EnumPropertyControl((EnumProperty) property,
					customObjectPane);
		} else if (property instanceof LongProperty) {
			return new LongPropertyControl((LongProperty) property,
					customObjectPane);

		} else if (property instanceof PointProperty) {

		} else if (property instanceof StringProperty) {
			return new StringPropertyControl((StringProperty) property,
					customObjectPane);
		} else if (property instanceof TextProperty) {
			return new TextPropertyControl((TextProperty) property,
					customObjectPane);
		} else {
		}

		return null;

	}

	public JLabel getLabel() {
		return label;
	}

	public JLayeredPane getPane() {
		return pane;
	}

	public JSeparator getSeparator() {
		return separator;
	}

	public abstract void onOkAction();

	public abstract void onCancelAction();

	public abstract JComponent getComponent();

}
