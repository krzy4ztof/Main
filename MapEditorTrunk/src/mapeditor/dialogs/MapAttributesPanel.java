package mapeditor.dialogs;

import java.awt.Container;
import java.awt.Dialog;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Window;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JTextField;
import javax.swing.ListSelectionModel;

import mapeditor.config.Config;
import mapeditor.mapapi.MapAttributes;
import mapeditor.mapapi.MapLayout;
import mapeditor.messages.MapMessages;

public class MapAttributesPanel extends JDialog {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	MapAttributes initialMapAttributes;
	MapAttributes selectedMapAttributes;

	// private int initialRow;
	// private int initialCol;
	// private int selectedRow;
	// private int selectedCol;
	JTextField colItem = null;
	JTextField rowItem = null;
	private MapMessages messages;
	boolean canceled;
	private Config config;

	final static String ACTION_DEFAULT_SIZE = "ACTION_DEFAULT_SIZE";
	final static String ACTION_PREVIOUS_SIZE = "ACTION_PREVIOUS_SIZE";
	final static String ACTION_OK = "ACTION_OK";
	final static String ACTION_CANCEL = "ACTION_CANCEL";

	private MapAttributesPanelActionListener mapActionListener;
	private MapAttributesPanelListSelectionListener mapListSelectionListener;

	public MapAttributesPanel(Config configParam, MapMessages messages,
			Container container) {
		super((Window) container, Dialog.ModalityType.APPLICATION_MODAL);
		config = configParam;
		this.messages = messages;
		canceled = false;
		mapActionListener = new MapAttributesPanelActionListener(this);
		mapListSelectionListener = new MapAttributesPanelListSelectionListener();
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
		/* parametry - MapApi */
		this.initialMapAttributes = mapAttributes;
		try {
			this.selectedMapAttributes = mapAttributes.clone();
		} catch (CloneNotSupportedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		// this.initialRow = no_rows;
		// this.initialCol = no_cols;
		colItem = new JTextField();
		rowItem = new JTextField();
		setTitle(messages.getString(MapMessages.ATTR_TITLE));
		JButton btn;

		Container pane = this.getContentPane();

		JButton button;
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
		pane.add(new JLabel(messages.getString(MapMessages.ATTR_LAYOUT)), c);

		c.gridx = 0;
		c.gridy = 3;
		pane.add(new JLabel(), c);

		c.gridx = 1;
		c.gridy = 2;
		c.gridheight = 2;
		pane.add(activateListLayout(), c);

		c.gridx = 0;
		c.gridy = 4;
		c.gridheight = 1;
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

		// ////

		c.gridx = 0;
		c.gridy = 6;
		pane.add(new JLabel(messages.getString(MapMessages.ATTR_LAYOUT)), c);

		c.gridx = 1;
		c.gridy = 6;
		c.gridheight = 2;
		pane.add(activateComboBox(), c);

		setDefaultCloseOperation(JFrame.HIDE_ON_CLOSE);
		// setSize(290, 165);
		setSize(290, 265);

		// this.setResizable(true);

		setLocationRelativeTo(getParent());
		setVisible(true);
	}

	private JList<MapLayoutWrapper> activateListLayout() {

		MapLayoutWrapper mlwHex = new MapLayoutWrapper(MapLayout.HEX, messages);
		MapLayoutWrapper mlwSqr = new MapLayoutWrapper(MapLayout.SQR, messages);

		MapLayoutWrapper[] data = new MapLayoutWrapper[] { mlwHex, mlwSqr };
		// DefaultListModel listModel = new DefaultListModel();

		JList<MapLayoutWrapper> list = new JList<MapLayoutWrapper>(data); // data
																			// has
																			// type
																			// Object[]
		list.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		list.setLayoutOrientation(JList.VERTICAL);
		list.setVisibleRowCount(-1);
		list.addListSelectionListener(mapListSelectionListener);
		list.setSelectedValue(mlwSqr, true);
		return list;
	}

	private JComboBox<MapLayoutWrapper> activateComboBox() {
		MapLayoutWrapper mlwHex = new MapLayoutWrapper(MapLayout.HEX, messages);
		MapLayoutWrapper mlwSqr = new MapLayoutWrapper(MapLayout.SQR, messages);

		MapLayoutWrapper[] data = new MapLayoutWrapper[] { mlwHex, mlwSqr };
		JComboBox<MapLayoutWrapper> comboBox = new JComboBox<MapLayoutWrapper>(
				data);
		comboBox.addActionListener(new LayoutActionListener(
				this.selectedMapAttributes));

		return comboBox;
	}

	/**
	 * Checks if given values for rows and columns are valid. If not fields they
	 * are removed and the dialog window remains open.
	 */
	void onOkAction() {

		System.out.println("height");
		System.out.println(this.size().getHeight());
		System.out.println("width");
		System.out.println(this.size().getWidth());

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

		if (ok) {
			dispose();
		}
	}

	public void setDefaultSize() {
		selectedMapAttributes.setColumns(config.getMapApiColumnsNumber());
		selectedMapAttributes.setRows(config.getMapApiRowsNumber());

		colItem.setText((new Integer(selectedMapAttributes.getColumns()))
				.toString());
		rowItem.setText(new Integer(selectedMapAttributes.getRows()).toString());
	}

	public void setPreviousSize() {
		selectedMapAttributes.setColumns(initialMapAttributes.getColumns());
		selectedMapAttributes.setRows(initialMapAttributes.getRows());
		colItem.setText(new Integer(selectedMapAttributes.getColumns())
				.toString());
		rowItem.setText(new Integer(selectedMapAttributes.getRows()).toString());
	}

	public void onCancelAction() {
		canceled = true;
		dispose();
	}

}
