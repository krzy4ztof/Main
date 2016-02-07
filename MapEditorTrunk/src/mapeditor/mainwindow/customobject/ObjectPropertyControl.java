package mapeditor.mainwindow.customobject;

import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;

import javax.swing.JLabel;
import javax.swing.JLayeredPane;

public class ObjectPropertyControl {

	private JLabel label;

	private JLayeredPane pane;

	public ObjectPropertyControl(String objectName) {

		pane = new JLayeredPane();
		pane.setLayout(new GridBagLayout());

		GridBagConstraints c = new GridBagConstraints();
		c.fill = GridBagConstraints.BOTH;
		c.weightx = 0.0;
		c.weighty = 0.0;
		c.gridx = 0;
		c.gridy = 0;

		label = new JLabel(objectName);

		pane.add(label, c);
	}

	public JLabel getLabel() {
		return label;
	}

	public JLayeredPane getPane() {
		return pane;
	}

}
