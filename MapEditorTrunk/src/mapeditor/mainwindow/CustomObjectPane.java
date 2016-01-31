package mapeditor.mainwindow;

import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;

import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JLayeredPane;
import javax.swing.JScrollPane;

import mapeditor.mapapi.MapApi;

public class CustomObjectPane {

	private JLayeredPane pane;

	private JScrollPane scrollPane;

	public CustomObjectPane(MapApi mapApi) {
		super();
		// createPanes(actionListener);

		pane = new JLayeredPane();
		pane.setLayout(new GridBagLayout());

		// /////////////////////////
		// activateLayers(mapApi);

		GridBagConstraints c = new GridBagConstraints();
		c.fill = GridBagConstraints.BOTH;
		c.weightx = 1.0;
		c.weighty = 0.0;
		c.gridx = 0;

		JLabel lastLabel = new JLabel("CUSTOM MAP OBJECT PANE");

		c.weighty = 1.0;
		c.gridx = 0;
		c.gridy = 0;
		pane.add(lastLabel, c);

		// /////////////////////
		scrollPane = new JScrollPane(pane);

	}

	public JComponent getPane() {
		return pane;
	}

	public JScrollPane getScrollPane() {
		return scrollPane;
	}
}
