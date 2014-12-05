package mapEditor.mapApi;

import java.io.File;
import java.util.LinkedList;

public class MapApi {

    //private int Columns,Rows;
	/* ilosc kolumn i wierszy mapy*/
//	private int Image_theme[10][10];//do zmiany na dynamiczne
	/*numer tematu do kt�rego
    nale�y obrazek na segmencie [x][y]*/
//	private int Image_no[10][10]//do zmiany na dynamiczne
	/*numer obrazeku na	segmencie [x][y]*/
//	private ImagesList p_ImagesList;// tego tu nnie b�dzie
    public static int DEFAULT_COLUMNS_NUMBER = 20;
    /* domy�lna liczba kolumn (u�ywana je�eli liczba
    kolumn w kostruktorze MapApi <= 0*/
    public static int DEFAULT_ROWS_NUMBER = 20;
    /* domy�lna liczba kwierszy (u�ywana je�eli liczba
    kolumn w kostruktorze MapApi <= 0*/
    private LinkedList<LinkedList<MapSegment>> segments;

    /**
     * Stores reference to file from which map was loaded or to which it was
     * saved
     */
    private File file = null;
    /**
     * Constructor. No number of rows nor columns is given. The next method to
     * invoke should be setSize(col, row) method.
     *
     */
    public MapApi() {
    }

    /**
     * Constructor
     * @param col Number of columns. When col <= 0 then default number of
     * columns is set.
     * @param row Number of rows. When row <= then default number of rows
     * is set.
     */
    public MapApi(int col, int row) {
        this.resetMap(col, row);
    }

    /**
     * Set size of MapApi. THe method should be invoked after MapApi()
     * constructor
     * @param col Number of columns. When col <= 0 then default number of
     * columns is set.
     * @param row Number of rows. When row <= then default number of rows
     * is set.
     */
    public void resetMap(int cols, int rows) {
        if (cols <= 0) {
            cols = DEFAULT_COLUMNS_NUMBER;
        }
        if (rows <= 0) {
            rows = DEFAULT_ROWS_NUMBER;
        }

        segments = new LinkedList<LinkedList<MapSegment>>();
        LinkedList<MapSegment> newRow;
        MapSegment se;
        for (int i = 0; i < rows; i++) {
            newRow = new LinkedList<MapSegment>();
            segments.add(newRow);

            for (int j = 0; j < cols; j++) {
                se = new MapSegment();
                newRow.add(se);
            }
        }
        file = null;
    }

    /**
     * Increases or decreases map size without deleting already existing
     * MapSegments
     * @param rows
     * @param cols
     */
    public void changeSize(int rows, int cols) {
        if (rows > 0) {
            changeRowsSize(rows);
        }

        if (cols > 0) {
            changeColumnsSize(cols);
        }

    }

    /**
     * Increases or decreases map rows size without deleting already existing
     * MapSegments
     * @param rows
     */
    private void changeRowsSize(int rows) {
        int rowsSize = getRowsSize();
        int colsSize = getColumnsSize();
        LinkedList<MapSegment> newRow = null;
        MapSegment segment = null;

        if (rows > rowsSize) {
            for (int i = rowsSize; i < rows; i++) {
                newRow = new LinkedList<MapSegment>();
                segments.add(newRow);
                for (int j = 0; j < colsSize; j++) {
                    segment = new MapSegment();
                    newRow.add(segment);
                }
            }
        } else if (rows < rowsSize) {
            for (int i = rows; i < rowsSize; i++) {
                segments.removeLast();
            }
        }
    }

    /**
     * Increases or decreases map rows size without deleting already existing
     * MapSegments
     * @param cols
     */
    private void changeColumnsSize(int cols) {
        int colsSize = getColumnsSize();
        LinkedList<MapSegment> newRow = null;
        MapSegment segment = null;

        if (cols > 0) {
            if (cols > colsSize) {
                for (LinkedList<MapSegment> row : segments) {
                    for (int i = colsSize; i < cols; i++) {
                        segment = new MapSegment();
                        row.add(segment);
                    }
                }
            } else if (cols < colsSize) {
                for (LinkedList<MapSegment> row : segments) {
                    for (int i = cols; i < colsSize; i++) {
                        row.removeLast();
                    }
                }
            }
        }
    }

    public MapSegment getSegment(int row, int col) {
        return segments.get(row).get(col);
    }

    /**
     *
     * @return Number of map columns
     */
    public int getColumnsSize() {
        return segments.get(0).size();
    }

    /**
     *
     * @return number of map rows
     */
    public int getRowsSize() {
        return segments.size();
    }

    /**
     *
     * @return File from which map was loaded or to which it was
     * saved
     */
    public File getFile() {
        return file;
    }

    /**
     *
     * @param file File from which map was loaded or to which it was
     * saved
     */
    public void setFile(File file) {
        this.file = file;
    }
}
