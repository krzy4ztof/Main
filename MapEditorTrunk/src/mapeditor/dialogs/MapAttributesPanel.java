package mapeditor.dialogs;

import java.awt.Container;
import java.awt.Dialog;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Window;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.logging.Level;
import java.util.logging.Logger;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JTextField;

import mapeditor.config.Config;
import mapeditor.logger.MapLogger;
import mapeditor.mapapi.MapAttributes;
import mapeditor.mapapi.MapLayout;
import mapeditor.messages.MapMessages;

public class MapAttributesPanel extends JDialog {

	private static final Logger logger = Logger
			.getLogger(MapAttributesPanel.class.getName());

	private static final long serialVersionUID = 1L;

	MapAttributes initialMapAttributes;
	MapAttributes selectedMapAttributes;

	JTextField colItem = null;
	JTextField rowItem = null;
	JTextField layerItem = null;

	private MapMessages messages;
	boolean canceled;
	private Config config;

	final static String ACTION_DEFAULT_SIZE = "ACTION_DEFAULT_SIZE";
	final static String ACTION_PREVIOUS_SIZE = "ACTION_PREVIOUS_SIZE";
	final static String ACTION_OK = "ACTION_OK";
	final static String ACTION_CANCEL = "ACTION_CANCEL";

	private MapAttributesPanelActionListener mapActionListener;

	public MapAttributesPanel(Config configParam, MapMessages messages,
			Container container) {
		super((Window) container, Dialog.ModalityType.APPLICATION_MODAL);
		config = configParam;
		this.messages = messages;
		canceled = false;
		mapActionListener = new MapAttributesPanelActionListener(this);
		addWindowListener(new WindowAdapter() {

			@Override
			public void windowClosing(WindowEvent e) {
				canceled = true;
			}
		});
	}

	public boolean isCanceled() {
		return canceled;
	}

	public MapAttributes getSelectedMapAttributes() {
		return selectedMapAttributes;
	}

	public void activate(MapAttributes mapAttributes) {
		this.initialMapAttributes = mapAttributes;
		try {
			this.selectedMapAttributes = mapAttributes.clone();
		} catch (CloneNotSupportedException e) {
			logger.log(Level.SEVERE, MapLogger.ERROR, e);
		}

		colItem = new JTextField();
		rowItem = new JTextField();
		layerItem = new JTextField();
		setTitle(messages.getString(MapMessages.ATTR_TITLE));
		JButton btn;

		Container pane = this.getContentPane();

		pane.setLayout(new GridBagLayout());
		GridBagConstraints c = new GridBagConstraints();

		c.fill = GridBagConstraints.BOTH;
		c.weightx = 1;
		c.weighty = 1;

		c.gridx = 0;
		c.gridy = 0;
		pane.add(new JLabel(messages.getString(MapMessages.ATTR_ROW_NUMBER)), c);

		c.gridx = 1;
		c.gridy = 0;
		pane.add(rowItem, c);
		rowItem.setText(new Integer(initialMapAttributes.getRows()).toString());

		c.gridx = 0;
		c.gridy = 1;
		pane.add(new JLabel(messages.getString(MapMessages.ATTR_COL_NUMBER)), c);

		c.gridx = 1;
		c.gridy = 1;
		pane.add(colItem, c);
		colItem.setText(new Integer(initialMapAttributes.getColumns())
				.toString());

		c.gridx = 0;
		c.gridy = 2;
		pane.add(
				new JLabel(messages.getString(MapMessages.ATTR_LAYERS_NUMBER)),
				c);

		c.gridx = 1;
		c.gridy = 2;
		pane.add(layerItem, c);
		layerItem.setText(new Integer(initialMapAttributes.getLayers())
				.toString());

		c.gridx = 0;
		c.gridy = 3;
		pane.add(new JLabel(messages.getString(MapMessages.ATTR_LAYOUT)), c);

		c.gridx = 1;
		c.gridy = 3;
		pane.add(activateComboBox(), c);

		c.gridx = 0;
		c.gridy = 4;
		btn = new JButton(messages.getString(MapMessages.ATTR_DEFAULT_SIZE));
		btn.addActionListener(mapActionListener);
		btn.setActionCommand(MapAttributesPanel.ACTION_DEFAULT_SIZE);
		pane.add(btn, c);

		c.gridx = 1;
		c.gridy = 4;
		btn = new JButton(messages.getString(MapMessages.ATTR_PREVIOUS_SIZE));
		btn.addActionListener(mapActionListener);
		btn.setActionCommand(MapAttributesPanel.ACTION_PREVIOUS_SIZE);
		pane.add(btn, c);

		c.gridx = 0;
		c.gridy = 5;
		btn = new JButton(messages.getString(MapMessages.ATTR_OK));
		btn.addActionListener(mapActionListener);
		btn.setActionCommand(MapAttributesPanel.ACTION_OK);
		pane.add(btn, c);

		c.gridx = 1;
		c.gridy = 5;
		btn = new JButton(messages.getString(MapMessages.ATTR_CANCEL));
		btn.addActionListener(mapActionListener);
		btn.setActionCommand(MapAttributesPanel.ACTION_CANCEL);
		pane.add(btn, c);

		setDefaultCloseOperation(JFrame.HIDE_ON_CLOSE);
		setSize(290, 165);

		setLocationRelativeTo(getParent());
		setVisible(true);
	}

	private JComboBox<MapLayoutWrapper> activateComboBox() {
		MapLayoutWrapper mlwHex = new MapLayoutWrapper(MapLayout.HEX, messages);
		MapLayoutWrapper mlwSqr = new MapLayoutWrapper(MapLayout.SQR, messages);

		MapLayoutWrapper[] data = new MapLayoutWrapper[] { mlwHex, mlwSqr };
		JComboBox<MapLayoutWrapper> comboBox = new JComboBox<MapLayoutWrapper>(
				data);

		MapLayout mapLayout = selectedMapAttributes.getMapLayout();
		if (mapLayout.equals(MapLayout.HEX)) {
			comboBox.setSelectedItem(mlwHex);
		} else {
			comboBox.setSelectedItem(mlwSqr);
		}

		comboBox.addActionListener(new LayoutActionListener(
				selectedMapAttributes));

		return comboBox;
	}

	/**
	 * Checks if given values for rows and columns are valid. If not fields they
	 * are removed and the dialog window remains open.
	 */
	void onOkAction() {

		boolean ok = true;
		int value;
		try {
			value = Integer.valueOf(rowItem.getText()).intValue();

			if (value > 0) {
				selectedMapAttributes.setRows(value);
			} else {
				rowItem.setText("");
				ok = false;
			}
		} catch (java.lang.NumberFormatException e) {
			rowItem.setText("");
			ok = false;
		}

		try {
			value = Integer.valueOf(colItem.getText()).intValue();

			if (value > 0) {
				selectedMapAttributes.setColumns(value);
			} else {
				rowItem.setText("");
				ok = false;
			}

		} catch (java.lang.NumberFormatException e) {
			colItem.setText("");
			ok = false;
		}

		try {
			value = Integer.valueOf(layerItem.getText()).intValue();

			if (value > 0 && value <= MapAttributes.MAX_LAYERS_NUMBER) {
				selectedMapAttributes.setLayers(value);
			} else {
				layerItem.setText("");
				ok = false;
			}

		} catch (java.lang.NumberFormatException e) {
			layerItem.setText("");
			ok = false;
		}

		if (ok) {
			dispose();
		}
	}

	public void setDefaultSize() {
		selectedMapAttributes.setColumns(config.getMapApiColumnsNumber());
		selectedMapAttributes.setRows(config.getMapApiRowsNumber());
		selectedMapAttributes.setLayers(config.getMapApiLayersNumber());

		colItem.setText((new Integer(selectedMapAttributes.getColumns()))
				.toString());
		rowItem.setText(new Integer(selectedMapAttributes.getRows()).toString());
		layerItem.setText(new Integer(selectedMapAttributes.getLayers())
				.toString());

	}

	public void setPreviousSize() {
		selectedMapAttributes.setColumns(initialMapAttributes.getColumns());
		selectedMapAttributes.setRows(initialMapAttributes.getRows());
		selectedMapAttributes.setLayers(initialMapAttributes.getLayers());

		colItem.setText(new Integer(selectedMapAttributes.getColumns())
				.toString());
		rowItem.setText(new Integer(selectedMapAttributes.getRows()).toString());
		layerItem.setText(new Integer(selectedMapAttributes.getLayers())
				.toString());
	}

	public void onCancelAction() {
		canceled = true;
		dispose();
	}

}
