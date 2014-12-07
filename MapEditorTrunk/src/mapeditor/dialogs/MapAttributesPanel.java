package mapeditor.dialogs;

import java.awt.Container;
import java.awt.Dialog;
import java.awt.GridBagLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.ResourceBundle;

import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JTextField;
import javax.swing.ListSelectionModel;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

import mapeditor.config.Config;
import mapeditor.mapapi.MapApi;

public class MapAttributesPanel extends JDialog implements ActionListener, ListSelectionListener {

    private int initialRow;
    private int initialCol;
    private int selectedRow;
    private int selectedCol;
    private JTextField colItem = null;
    private JTextField rowItem = null;
    private ResourceBundle messages;
    private boolean canceled;
    private Config config;

    private final static String ACTION_DEFAULT_SIZE="ACTION_DEFAULT_SIZE";
    private final static String ACTION_PREVIOUS_SIZE="ACTION_PREVIOUS_SIZE";
    private final static String ACTION_OK="ACTION_OK";
    private final static String ACTION_CANCEL="ACTION_CANCEL";
   
    
    public MapAttributesPanel(Config configParam, ResourceBundle resourceBundle,
            JFrame jFrameParam){
        super(jFrameParam, Dialog.ModalityType.APPLICATION_MODAL);
        config = configParam;
        messages = resourceBundle;
        canceled = false;
        addWindowListener(new WindowAdapter() {

            @Override
            public void windowClosing(WindowEvent e) {
                canceled = true;
            }
        });
    }

    public int getSelectedCol() {
        return selectedCol;
    }

    public int getSelectedRow() {
        return selectedRow;
    }

    public boolean getCanceled() {
        return canceled;
    }

    public void activate(int no_rows, int no_cols) {
        /*parametry - MapApi*/
        this.initialRow = no_rows;
        this.initialCol = no_cols;
        colItem = new JTextField();
        rowItem = new JTextField();
        setTitle(messages.getString("MapAttributes"));
        JButton btn;
        Container p = this.getContentPane();
        p.setLayout(new GridLayout(5, 2));
        p.add(new JLabel(messages.getString("RowNumber")));
        p.add(rowItem);
        rowItem.setText(new Integer(no_rows).toString());
        p.add(new JLabel(messages.getString("ColNumber")));
        p.add(colItem);
        colItem.setText(new Integer(no_cols).toString());
        
        p.add(new JLabel(messages.getString("Layout")));
        
        
        p.add(activateListLayout());
        
        btn = new JButton(messages.getString("DefaultSize"));
        btn.addActionListener(this);
        btn.setActionCommand(MapAttributesPanel.ACTION_DEFAULT_SIZE);
        p.add(btn);
        btn = new JButton(messages.getString("PreviousSize"));
        btn.addActionListener(this);
        btn.setActionCommand(MapAttributesPanel.ACTION_PREVIOUS_SIZE);
        p.add(btn);
        btn = new JButton(messages.getString("OK"));
        btn.addActionListener(this);
        btn.setActionCommand(MapAttributesPanel.ACTION_OK);
        p.add(btn);
        btn = new JButton(messages.getString("Cancel"));
        btn.addActionListener(this);
        btn.setActionCommand(MapAttributesPanel.ACTION_CANCEL);
        p.add(btn);
        this.setDefaultCloseOperation(JFrame.HIDE_ON_CLOSE);
        //this.setSize(290, 130);
        this.setSize(290, 230);
        
        this.setResizable(true);
        this.show();
    }
    
    private JList<String> activateListLayout(){
    	String[] data = new String[]{"HEX","SQR"};
    	//DefaultListModel listModel = new DefaultListModel();
    	
    	JList<String> list = new JList<String>(data); //data has type Object[]
    	list.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
    	list.setLayoutOrientation(JList.VERTICAL);
    	list.setVisibleRowCount(-1);
    	list.addListSelectionListener(this);
    	return list;
    }

    public void actionPerformed(ActionEvent e) {
        String action = e.getActionCommand();
        if (action.equals(MapAttributesPanel.ACTION_OK)) {
            this.on_ok();
        } else if (action.equals(MapAttributesPanel.ACTION_DEFAULT_SIZE)) {
            selectedCol = config.getMapApiColumnsNumber();
            selectedRow = config.getMapApiRowsNumber();

            colItem.setText((new Integer(selectedCol)).toString());
            rowItem.setText(new Integer(selectedRow).toString());
        } else if (action.equals(MapAttributesPanel.ACTION_PREVIOUS_SIZE)) {
            selectedCol = initialCol;
            selectedRow = initialRow;
            colItem.setText(new Integer(selectedCol).toString());
            rowItem.setText(new Integer(selectedRow).toString());
        } else if (action.equals(MapAttributesPanel.ACTION_CANCEL)) {
            canceled = true;
            dispose();
        }

    }

    /**
     * Checks if given values for rows and columns are valid. If not fields they
     * are removed and the dialog window remains open.
     */
    private void on_ok() {

    	System.out.println("height");
    	System.out.println(this.size().getHeight());
    	System.out.println("width");
    	System.out.println(this.size().getWidth());
    	
        boolean ok = true;
        int value;
        try {
            value = Integer.valueOf(rowItem.getText()).intValue();

            if (value > 0) {
                selectedRow = value;
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
                selectedCol = value;
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

	@Override
	public void valueChanged(ListSelectionEvent e) {
		
		JList<String> list = (JList<String>) e.getSource();		
		System.out.println("VALUE: "+list.getSelectedValue());
		System.out.println("INDEX: "+list.getSelectedIndex());
		
		
		
		if (true){
			return;
		}
		ListSelectionModel lsm = (ListSelectionModel) e.getSource();
		int firstIndex = e.getFirstIndex();
		int lastIndex = e.getLastIndex();
		boolean isAdjusting = e.getValueIsAdjusting();
		System.out.println("Event for indexes " + firstIndex + " - "
				+ lastIndex + "; isAdjusting is " + isAdjusting
				+ "; selected indexes:");

		if (lsm.isSelectionEmpty()) {
			System.out.println(" <none>");
		} else {
			// Find out which indexes are selected.
			int minIndex = lsm.getMinSelectionIndex();
			int maxIndex = lsm.getMaxSelectionIndex();
			for (int i = minIndex; i <= maxIndex; i++) {
				if (lsm.isSelectedIndex(i)) {
					System.out.println(" " + i);
				}
			}
		}
	}
}


