package mapeditor.mainwindow.customobject;

import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;

import mapeditor.mapapi.Point3D;

public class PointPropertyChangeListener implements PropertyChangeListener {

	private CustomObjectPane customObjectPane;

	private PointPropertyControl pointPropertyControl;

	public PointPropertyChangeListener(CustomObjectPane customObjectPane,
			PointPropertyControl pointPropertyControl) {
		this.customObjectPane = customObjectPane;
		this.pointPropertyControl = pointPropertyControl;
	}

	@Override
	public void propertyChange(PropertyChangeEvent event) {
		Object valueObj = event.getNewValue();

		if (valueObj != null && valueObj instanceof Point3D) {
			pointPropertyControl.setNewValue((Point3D) valueObj);
			customObjectPane.enableButtons();
		}
	}
}
