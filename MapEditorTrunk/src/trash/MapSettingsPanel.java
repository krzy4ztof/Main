package trash;

import mapeditor.mainwindow.GraphicsSystem;
import java.awt.Container;
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
import mapeditor.mapapi.MapApi;

public class MapSettingsPanel extends JDialog implements ActionListener {
    /* Okno wywo�ywane po wybraniu pozycji z Plik->Nowy...
    Ustala wymiary nowej mapy*/

    private int default_row;
    private int default_col;
    private int last_row;
    private int last_col;
    private JTextField col_item = new JTextField();
    private JTextField row_item = new JTextField();
    private ResourceBundle messages = null;
    private MapApi mapApi = null;
    private GraphicsSystem graphicsSystem = null;

    public MapSettingsPanel(ResourceBundle resourceBundle, 
            GraphicsSystem graphicsSystemParam, MapApi mapApiParam) {
        super(graphicsSystemParam.getJFrame());
        messages = resourceBundle;
        mapApi = mapApiParam;
        graphicsSystem = graphicsSystemParam;
        addWindowListener(new WindowAdapter() {

            @Override
            public void windowClosing(WindowEvent e) {
                dispose();
            }
        });
    }

    public MapSettingsPanel() {
        super();
        addWindowListener(new WindowAdapter() {

            @Override
            public void windowClosing(WindowEvent e) {
                dispose();
                System.exit(0);
            }
        });
    }

    public void activate(int no_rows, int no_cols) {
        /*parametry - MapApi*/
        this.default_row = MapApi.DEFAULT_ROWS_NUMBER;
        this.default_col = MapApi.DEFAULT_COLUMNS_NUMBER;
        this.last_row = mapApi.getRowsSize();
        this.last_col = mapApi.getColumnsSize();
        setTitle(messages.getString("MapSize"));
        JButton btn;
        Container p = this.getContentPane();
        p.setLayout(new GridLayout(4, 2));
        p.add(new JLabel(messages.getString("RowNumber")));
        p.add(row_item);
        row_item.setText(new Integer(no_rows).toString());
        p.add(new JLabel(messages.getString("ColNumber")));
        p.add(col_item);
        col_item.setText(new Integer(no_cols).toString());
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
        p.add(new JLabel(""));

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
            col_item.setText((new Integer(this.default_col)).toString());
            row_item.setText(new Integer(this.default_row).toString());
        } else if (action.equals("BTN_Last")) {
            col_item.setText(new Integer(this.last_col).toString());
            row_item.setText(new Integer(this.last_row).toString());
        }

    }

    private void on_ok() {
        /* sprawdza czy podane ilo�ci kolumn i wierszy s�
        prawid�owe i ewentualnie tworzy nowy MapApi*/

        int r = 0, c = 0;
        boolean ok = true;
        try {
            r = Integer.valueOf(row_item.getText()).intValue();
        } catch (java.lang.NumberFormatException e) {
            row_item.setText("");
            ok = false;
        }

        try {
            c = Integer.valueOf(col_item.getText()).intValue();
        } catch (java.lang.NumberFormatException e) {
            col_item.setText("");
            ok = false;
        }
        if (ok) {
            mapApi.resetMap(c, r);
            graphicsSystem.getJFrame().repaint();
            dispose();
        }
    }
}

