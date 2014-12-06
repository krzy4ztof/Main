package mapeditor.mainwindow;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Image;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Hashtable;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JPanel;
import mapeditor.themesapi.MapObjectsTheme;
import mapeditor.themesapi.MapThemesList;
import mapeditor.mapapi.MapObject;

public class BmpPanel extends JPanel implements ActionListener {

    private Hashtable<String, JButton> Items = new Hashtable<String, JButton>();
    /** Items - wska�niki do przycisk�w z ikonami
    Symbole haszuj�ce: "BMP_"+numer (1-8)*/
    private MapObjectsTheme curMapObjectsTheme = null;
    /** Numer Tematu, kt�rego ikony s� aktualnie
    wy�wietlane */
    private int ImageNumber = 0; // Do skasowania
    /** Numer Ikony znajduj�cej si� na przycisku
    Items.get("BMP_1")*/
    private int SelectedImage = 0; // Do skasowania
    private MapObject curMapObject = null; // W zamian za ImageNumber i SelectedImage

    private GraphicsSystem graphicsSystem = null;
    private MapThemesList mapThemesList = null;
    /** Numer w Ikony kt�r� aktualnie wybrano przyciskiem
    Items.get("BMP_x"). UWAGA!! Jest to numer Ikony
    a nie numer przycisku!!!*/
    public BmpPanel(MapThemesList mapThemesListParam, GraphicsSystem graphicsSystemParam) {
        super();
        mapThemesList = mapThemesListParam;
        graphicsSystem = graphicsSystemParam;

    }

    public void activate() {
        /**
         */
        JButton Btn;
        GridBagLayout gridbag = new GridBagLayout();
        GridBagConstraints c = new GridBagConstraints();
        this.setLayout(gridbag);
        curMapObjectsTheme = mapThemesList.getFirstTheme();

        c.fill = GridBagConstraints.BOTH;
        c.weightx = 2.0;//proporcje powi�kszania si�
        c.weighty = 2.0;

        int k = 0, i = 0;
        for (i = 0; i < 4; i++) {
            for (int j = 0; j < 2; j++) {
                Btn = new JButton();
                Btn.addActionListener(this);// zmieni si� na mapk�
                Btn.setActionCommand("BMP_" + Integer.toString(k));
                c.gridy = i;
                c.gridx = j;
                gridbag.setConstraints(Btn, c);
                Items.put("BMP_" + Integer.toString(k), Btn);
                this.add(Btn);
                k++;
            }
        }

        Items.get("BMP_0").setBackground(Color.RED);
        Btn = new JButton("^");
        Btn.addActionListener(this);// zmieni si� na mapk�
        Btn.setActionCommand("SCR_up");
        c.weightx = 1.0;//proporcje powi�kszania si�
        c.weighty = 1.0;//proporcje powi�kszania si�
        c.gridx = 0;
        c.gridy = i;
        gridbag.setConstraints(Btn, c);
        this.add(Btn);

        Btn = new JButton("V");
        Btn.addActionListener(this);// zmieni si� na mapk�
        Btn.setActionCommand("SCR_down");
        c.gridx = 1;
        c.gridy = i;
        gridbag.setConstraints(Btn, c);
        this.add(Btn);

        this.SetAvailableIcons();
    }

    public void actionPerformed(ActionEvent e) {
        /** prowadzi nas�uch menu s�u��cego do
        wyboru grupy tematycznej. Powoduje wy�wietlenie
        ikon nale��cych do wybranego Tematu.
        Prowadzi te� nas�uch dw�ch przycisk�w przesuwaj�cych
        list� dost�pnych ikon. */

        String Command = e.getActionCommand();
        if (Command.startsWith("MNU_")) {

            this.curMapObjectsTheme = mapThemesList.getThemeByName(Command.substring(4));
            this.curMapObjectsTheme.describeYourself();

            this.SetAvailableIcons();
        } else if (Command.startsWith("SCR_")) {
            //nas�uch przycisk�w przesuwaj�cych list� ikon
            if (Command.substring(4).equals("up")) {
                this.ChangeActualButton(Color.LIGHT_GRAY);
                this.ImageNumber--;
                if (this.ImageNumber < 0) {
                    this.ImageNumber = 0;
                }
                this.ChangeActualButton(Color.RED);
            } else if (Command.substring(4).equals("down")) {
                this.ChangeActualButton(Color.LIGHT_GRAY);
                this.ImageNumber++;
                int maxNumber = this.curMapObjectsTheme.getThemeSize();

                if (this.ImageNumber > maxNumber - 1) {
                    this.ImageNumber = maxNumber - 1;
                }
                if (this.ImageNumber < 0) {
                    this.ImageNumber = 0;
                }
                this.ChangeActualButton(Color.RED);
            }
            this.SetAvailableIcons();

        } else if (Command.startsWith("BMP_")) {
            //nas�uch przycisk�w ustawiaj�cych ikon� jako "p�dzel"
            int btn_number = Integer.parseInt(Command.substring(4));
            int maxNumber = this.curMapObjectsTheme.getThemeSize();

            int sel = btn_number + this.ImageNumber;
            if (sel < maxNumber) {
                for (int i = 0; i < 8; i++) {
                    Items.get("BMP_" + Integer.toString(i)).setBackground(Color.LIGHT_GRAY);
                }
                Items.get(Command).setBackground(Color.RED);
                this.SelectedImage = sel;
            }
        }
        graphicsSystem.getJFrame().requestFocus();
    }

    private void ChangeActualButton(Color def_color) {
        int nr_int = this.getActualButtonNumber();
        if ((nr_int >= 0) && (nr_int < 8)) {
            Integer nr = new Integer(nr_int);
            String Command = "BMP_" + nr.toString();
            Items.get(Command).setBackground(def_color);
        }
    }

    private int getActualButtonNumber() {
        /* zwraca numer pod�wietlonego na czerwono przycisku */
        return (this.SelectedImage - this.ImageNumber);
    }

    @Override
    public void paint(Graphics g) {
        /*Przechwytuje komunikat o zmianie wielko�ci okna*/
        super.paint(g);
    }

    private void SetAvailableIcons() {
        /**Aktualizuje zbi�r dost�pnych Ikon na przyciskach
        Items*/
        int ThSize = this.curMapObjectsTheme.getThemeSize();

        int i = 0, j = 0, k = 0;
        ImageIcon img, img_sc;
        JButton btn;
        for (i = this.ImageNumber; i < ThSize && k < 8; i++) {
            img = curMapObjectsTheme.getMapObject(i).getImageIcon();

            img_sc = new ImageIcon(
                    img.getImage().getScaledInstance(
                    40, 40, Image.SCALE_DEFAULT));

            btn = Items.get("BMP_" + Integer.toString(k));
            btn.setIcon(img_sc);
            k++;
        }

        for (i = k; i < 8; i++) {
            img = new ImageIcon("../Images/" + "NULL.jpg");
            img_sc = new ImageIcon(
                    img.getImage().getScaledInstance(
                    40, 40, Image.SCALE_DEFAULT));

            btn = Items.get("BMP_" + Integer.toString(i));
            btn.setIcon(img_sc);
        }
    }

    public String getActualIconFilename() {
        String result = null;
        result = this.getSelectedMapObject().getImageName();
        return result;
    }

    public MapObject getSelectedMapObject() {
        MapObject mapObject = null;
        mapObject = curMapObjectsTheme.getMapObject(this.SelectedImage);
        return mapObject;
    }
}
