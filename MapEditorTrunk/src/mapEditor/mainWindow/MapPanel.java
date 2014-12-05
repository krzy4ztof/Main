package mapEditor.mainWindow;

import mapEditor.mapApi.MapObject;
import mapEditor.mapApi.MapApi;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.Point;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import javax.swing.ImageIcon;
import javax.swing.JPanel;
import mapEditor.dialogs.SegmentAttributesPanel;

import otherProds.ExampleFileFilter;

public class MapPanel extends JPanel implements MouseListener,
        MouseMotionListener {

    ExampleFileFilter fe;
    private Point LUcornerMap = new Point(0, 0);
    /*Wsp�rz�dne punktu (segmentu) na mapie znajduj�cego si�
    w lewym g�rnym punkcie (segmencie) MapPanelu */
    final int defaultSegmentWidth = 40;
    /*sta�a - domy�lna szeroko�� segmentu*/
    private int SegmentWidth = defaultSegmentWidth;
    /*szerokosc segmentu mapy*/
    final int defaultSegmentHeight = 40;
    /*sta�a - domy�lna wysoko�� segmentu*/
    private int SegmentHeight = defaultSegmentHeight;
    /*wysoko�� segmentu mapy*/
    private ImageIcon blank = new ImageIcon("");
    /*pusta ikona - dla niewype�nionych segment�w mapy*/
    private SegmentAttributesPanel r_SegmentAttributesPanel = new SegmentAttributesPanel();
    private GraphicsSystem graphicsSystem;
    private MapApi mapApi;

    public MapPanel(GraphicsSystem graphicsSystemParam, MapApi mapApiParam) {
        super();
        graphicsSystem = graphicsSystemParam;
        mapApi = mapApiParam;

        addMouseListener(this);
        addMouseMotionListener(this);
    }

    public void setMapApi(MapApi mapApi) {
        this.mapApi = mapApi;
    }


    public void MoveMap(int x, int y) {
        LUcornerMap.x += 2 * x;
        LUcornerMap.y += y;
        this.repaint();
    }

    public void ZoomMapIn() {
        SegmentHeight += 5;
        SegmentWidth += 5;
        this.repaint();
    }

    public void ZoomMapOut() {
        SegmentHeight -= 5;
        SegmentWidth -= 5;
        if (SegmentHeight < 5) {
            SegmentHeight = 5;
        }
        if (SegmentWidth < 5) {
            SegmentWidth = 5;
        }
        this.repaint();
    }

    public void SetDefaultMapZoom() {
        SegmentHeight = defaultSegmentHeight;
        SegmentWidth = defaultSegmentWidth;
        this.repaint();
    }



    @Override
    public void paint(Graphics g) {
        /*
        Przechwytuje komunikat o zmianie wielko�ci okna
         */
        super.paint(g);
        DrawMap(g);
    }

    private Image getImage(int row, int col) {
        /*zwraca ImageIcon danego
        segmentu mapy. Parametry: col - kolumna,
        row - rz�d*/

        MapObject mapObject = null;

        mapObject = mapApi.getSegment(row, col).getMapObject();
        if (mapObject != null) {
            return mapObject.getImageIcon().getImage();
        } else {
            return this.blank.getImage();
        }
    }

    private void DrawMap(Graphics g) {
        /* rysuje map�*/
        int ImMap;
        CorrectMap();// to musi by� wywo�ane na pocz�tku

        g.setColor(Color.RED);

        for (int x = 0; x < HowManyColumns(); x++) {
            for (int y = 0; y < HowManyRows(); y++) {
                if (((LUcornerMap.x + x) % 2) == 0) {
                    g.drawRect(x * SegmentWidth, y * SegmentHeight,
                            SegmentWidth, SegmentHeight);
                    g.drawImage(this.getImage(y + LUcornerMap.y,
                            x + LUcornerMap.x),
                            x * SegmentWidth, y * SegmentHeight,
                            SegmentWidth, SegmentHeight,
                            getBackground(), this);
                } else {
                    g.drawRect(x * SegmentWidth, (int) ((y + 0.5) * SegmentHeight),
                            SegmentWidth, SegmentHeight);
                    g.drawImage(this.getImage(y + LUcornerMap.y,
                            x + LUcornerMap.x),
                            x * SegmentWidth, (int) ((y + 0.5) * SegmentHeight),
                            SegmentWidth, SegmentHeight,
                            getBackground(), this);
                }
            }
        }
    }

    private void CorrectMap() {
        /* koryguje warto�� zmiennej LUcornerMap;
        wa�ne podczas zmiany rozmiaru ekranu, te�
        przy wczytaniu nowej mapy z menu*/
        int hmc = HowManyColumns();
        int hmr = HowManyRows();
        int mxc = mapApi.getColumnsSize();
        int mxr = mapApi.getRowsSize();


        if (LUcornerMap.x > mxc - hmc) {
            LUcornerMap.x = mxc - hmc;
        }
        if (LUcornerMap.x < 0) {
            LUcornerMap.x = 0;
        }
        if (LUcornerMap.y > mxr - hmr) {
            LUcornerMap.y = mxr - hmr;
        }
        if (LUcornerMap.y < 0) {
            LUcornerMap.y = 0;
        }

    }

    private int HowManyColumns() {
        /*zwraca liczb� kolumn mapy jaka ma byc wyswietlona;
        zale�y od SegmentWidth i od wielkosci mapy*/
        int avCol = getWidth() / SegmentWidth;
        int maxCol = mapApi.getColumnsSize();

        if (avCol <= maxCol) {
            return avCol;
        } else {
            return maxCol;
        }
    }

    private int HowManyRows() {
        /*zwraca liczb� rz�d�w mapy jaka ma byc wyswietlona;
        zale�y od SegmentHeight i od wielkosci mapy*/
        int avRow = getHeight() / SegmentHeight;
        int maxRow = mapApi.getRowsSize();
//		System.out.println("avR= "+avRow+" maxR= "+maxRow);
        if (avRow <= maxRow) {
            return avRow;
        } else {
            return maxRow;
        }
    }

    public void mouseEntered(MouseEvent e) {
    }

    public void mouseExited(MouseEvent e) {
    }

    public void mouseReleased(MouseEvent e) {
    }

    public void mouseClicked(MouseEvent e) {
        /* pojedyncze klikniecie. e.getButton(): 1 - dla
        lewego (rysuje ikon�), 3 - dla prawego przycisku
        (menu atrybut�w)*/
        Point seg = this.CursorAtSegment(e.getPoint());

        if (seg.x != -1) {
            if (e.getButton() == 1) {
                MapObject mapObject = graphicsSystem.getSelectedMapObject();
                mapApi.getSegment(seg.y, seg.x).setMapObject(mapObject);

                this.repaint();
            } else {

                r_SegmentAttributesPanel.setVisible(true);
                System.out.println("menu atrybut�w");
            }
        }
    }

    public void mousePressed(MouseEvent e) {
    }

    public void mouseDragged(MouseEvent e) {
        /* przesuwanie myszy ze wcisni�tym przyciskiem
        e.getButton() - zawsze daje 0*/
        Point seg = this.CursorAtSegment(e.getPoint());
        if (seg.x != -1) {
            BmpPanel p_BmpPanel = graphicsSystem.bmpPanel;
            MapObject mapObject = p_BmpPanel.getSelectedMapObject();
            mapApi.getSegment(seg.y, seg.x).setMapObject(mapObject);

            this.repaint();
        }
    }

    public void mouseMoved(MouseEvent e) {
    }

    private Point CursorAtSegment(Point cur) {
        /* parametr cur - wsp�rz�dne kursora myszy na MapPanelu;
        zwraca kolumn� i wiersz segmentu kt�ry wskazywany jest
        przez kursor. Zwraca Point(-1,-1) je�eli kursor wyjdzie
        poza map�*/
        int C = cur.x / SegmentWidth;
        int R = cur.y / SegmentHeight;
        int maxCol = mapApi.getColumnsSize();
        int maxRow = mapApi.getRowsSize();

        C += LUcornerMap.x;
        if (C % 2 == 1) {
            R = (int) ((cur.y - 0.5 * SegmentHeight) / SegmentHeight);
        }
        R += LUcornerMap.y;

        if ((C % 2 == 1) && (cur.y < SegmentHeight) && (LUcornerMap.y == 0)) {
            return new Point(-1, -1);//nieparzysty rz�d, g�rny margines
        }
        if ((C >= maxCol) || (R >= maxRow)) {
            return new Point(-1, -1);
        }
        if ((C < 0) || (R < 0)) {
            return new Point(-1, -1);
        }
        return new Point(C, R);

    }
}

