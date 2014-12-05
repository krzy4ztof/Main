package mapEditor.dialogs;

import java.awt.Container;
import java.awt.Dialog;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.ResourceBundle;
import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JTextField;
import mapEditor.mapApi.MapApi;

public class MapResizePanel extends JDialog implements ActionListener {

    private int initialRow;
    private int initialCol;
    private int selectedRow;
    private int selectedCol;
    private JTextField colItem = null;
    private JTextField rowItem = null;
    private ResourceBundle messages;
    private boolean canceled;

    public MapResizePanel(ResourceBundle resourceBundle,
            JFrame jFrameParam) {
        super(jFrameParam, Dialog.ModalityType.APPLICATION_MODAL);
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
        setTitle(messages.getString("MapSize"));
        JButton btn;
        Container p = this.getContentPane();
        p.setLayout(new GridLayout(4, 2));
        p.add(new JLabel(messages.getString("RowNumber")));
        p.add(rowItem);
        rowItem.setText(new Integer(no_rows).toString());
        p.add(new JLabel(messages.getString("ColNumber")));
        p.add(colItem);
        colItem.setText(new Integer(no_cols).toString());
        btn = new JButton(messages.getString("DefaultSize"));
        btn.addActionListener(this);
        btn.setActionCommand("BTN_Default");
        p.add(btn);
        btn = new JButton(messages.getString("PreviousSize"));
        btn.addActionListener(this);
        btn.setActionCommand("BTN_Last");
        p.add(btn);
        btn = new JButton(messages.getString("OK"));
        btn.addActionListener(this);
        btn.setActionCommand("BTN_OK");
        p.add(btn);
        btn = new JButton(messages.getString("Cancel"));
        btn.addActionListener(this);
        btn.setActionCommand("BTN_Cancel");
        p.add(btn);
        this.setDefaultCloseOperation(JFrame.HIDE_ON_CLOSE);
        this.setSize(290, 130);
        this.setResizable(false);
        this.show();
    }

    public void actionPerformed(ActionEvent e) {
        String action = e.getActionCommand();
        if (action.equals("BTN_OK")) {
            this.on_ok();
        } else if (action.equals("BTN_Default")) {
            selectedCol = MapApi.DEFAULT_COLUMNS_NUMBER;
            selectedRow = MapApi.DEFAULT_ROWS_NUMBER;

            colItem.setText((new Integer(selectedCol)).toString());
            rowItem.setText(new Integer(selectedRow).toString());
        } else if (action.equals("BTN_Last")) {
            selectedCol = initialCol;
            selectedRow = initialRow;
            colItem.setText(new Integer(selectedCol).toString());
            rowItem.setText(new Integer(selectedRow).toString());
        } else if (action.equals("BTN_Cancel")) {
            canceled = true;
            dispose();
        }

    }

    /**
     * Checks if given values for rows and columns are valid. If not fields they
     * are removed and the dialog window remains open.
     */
    private void on_ok() {

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
}

