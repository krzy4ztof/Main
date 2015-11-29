package mapeditor.mainwindow;

import java.awt.Graphics;
import java.awt.Image;
import java.awt.Paint;
import java.awt.Point;
import java.awt.Rectangle;
import java.awt.Stroke;
import java.util.Iterator;
import java.util.LinkedList;

import javax.swing.ImageIcon;

import mapeditor.dialogs.SegmentAttributesPanel;
import mapeditor.mapapi.CopyPaste;
import mapeditor.mapapi.CopyPasteSegment;
import mapeditor.mapapi.CopyPasteSegments;
import mapeditor.mapapi.DraggedSegments;
import mapeditor.mapapi.MapApi;
import mapeditor.mapapi.MapSegment;
import mapeditor.mapapi.SelectedSegments;
import mapeditor.themesapi.MapObject;
import otherprods.ExampleFileFilter;

public class MapPane extends GridPane {

	ExampleFileFilter fe;

	SegmentAttributesPanel r_SegmentAttributesPanel = new SegmentAttributesPanel();
	private MapApi mapApi;
	private CopyPaste copyPaste;

	// private JLayeredPane copyPastePane;

	public MapPane(MapApi mapApi, CopyPaste copyPaste) {
		super();
		this.mapApi = mapApi;
		this.copyPaste = copyPaste;

		/*
		 * copyPastePane = new JLayeredPane() {
		 * 
		 * private static final long serialVersionUID = 1L;
		 * 
		 * @Override public void paint(Graphics g) { super.paint(g);
		 * copyPastePane.paint(g); } }; scrollPane.add(copyPastePane, 2);
		 */
	}

	@Override
	protected boolean isLayoutHex() {
		return mapApi.isLayoutHex();
	}

	@Override
	protected int getGridApiColumnsSize() {
		return mapApi.getColumnsSize();
	};

	@Override
	protected int getGridApiRowsSize() {
		return mapApi.getRowsSize();
	};

	public void setMapApi(MapApi mapApi) {
		this.mapApi = mapApi;
	}

	public void centerMap() {
		Rectangle r = panel.getVisibleRect();

		int centerX = this.getGridWidth() / 2;
		int centerY = this.getGridHeight() / 2;

		int newX = centerX - r.width / 2;
		int newY = centerY - r.height / 2;

		Rectangle newRectangle = new Rectangle(newX, newY, r.width, r.height);

		panel.scrollRectToVisible(newRectangle);

		panel.repaint();
	}

	public void zoomMapIn() {
		Rectangle rectangle = panel.getVisibleRect();
		int oldMapWidth = getGridWidth();
		int oldMapHeight = getGridHeight();

		segmentHeight += 5;
		segmentWidth += 5;

		scrollMapToNewView(rectangle, oldMapWidth, oldMapHeight);
	}

	public void zoomMapOut() {
		Rectangle rectangle = panel.getVisibleRect();
		int oldMapWidth = getGridWidth();
		int oldMapHeight = getGridHeight();

		segmentHeight -= 5;
		segmentWidth -= 5;
		if (segmentHeight < 5) {
			segmentHeight = 5;
		}
		if (segmentWidth < 5) {
			segmentWidth = 5;
		}
		scrollMapToNewView(rectangle, oldMapWidth, oldMapHeight);
	}

	private void scrollMapToNewView(Rectangle oldRectangle, int oldMapWidth,
			int oldMapHeight) {
		double resizeX = (double) getGridWidth() / oldMapWidth;
		double resizeY = (double) getGridHeight() / oldMapHeight;

		int newX = 0;
		if (resizeX < 1) {
			newX = new Double(oldRectangle.x * resizeX
					- (oldRectangle.width - oldRectangle.width * resizeX) / 2)
					.intValue();
		} else {
			newX = new Double(oldRectangle.x * resizeX
					+ (oldRectangle.width * resizeX - oldRectangle.width) / 2)
					.intValue();
		}

		int newY = 0;
		if (resizeY < 1) {
			newY = new Double(oldRectangle.y * resizeY
					- (oldRectangle.height - oldRectangle.height * resizeY) / 2)
					.intValue();
		} else {
			newY = new Double(oldRectangle.y * resizeY
					+ (oldRectangle.height * resizeY - oldRectangle.height) / 2)
					.intValue();
		}

		Rectangle newRectangle = new Rectangle(newX, newY, oldRectangle.width,
				oldRectangle.height);
		panel.scrollRectToVisible(newRectangle);
		panel.repaint();
	}

	public void setDefaultMapZoom() {
		Rectangle rectangle = panel.getVisibleRect();
		int oldMapWidth = getGridWidth();
		int oldMapHeight = getGridHeight();

		segmentHeight = DEFAULT_SEGMENT_HEIGHT;
		segmentWidth = DEFAULT_SEGMENT_WIDTH;

		scrollMapToNewView(rectangle, oldMapWidth, oldMapHeight);
	}

	@Override
	protected MapObject getMapObject(int row, int col) {
		// System.out.println("row: " + row + "; col: " + col);
		MapObject mapObject = null;
		MapSegment mapSegment = mapApi.getSegment(row, col);
		if (mapSegment != null) {
			mapObject = mapApi.getSegment(row, col).getMapObject();
		}
		return mapObject;
	}

	@Override
	public void paint(Graphics graphics) {
		super.paint(graphics);

		int divider = 1;
		if (isLayoutHex()) {
			divider = 2;
		}
		/*
		 * Paint paint = Color.GREEN; // paint = new ColorUIResource(0, 128, 0);
		 * 
		 * paint = new ColorUIResource(0, 128, 32);
		 * 
		 * // Stroke stroke = new BasicStroke(4.0f); float dash[] = { 5.0f };//
		 * { 10.0f, 5.0f, 2.0f, 1.0f }; Stroke stroke = new BasicStroke(3.0f,
		 * BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND, 5.0f, dash, 0.0f);
		 */

		SelectedSegments selectedSegments = copyPaste.getSelectedSegments();
		if (selectedSegments != null) {
			Paint paint = selectedSegments.getPaint();
			Stroke stroke = selectedSegments.getStroke();

			Iterator<CopyPasteSegment> iterator = selectedSegments
					.iteratorForDrawing();

			while (iterator.hasNext()) {
				CopyPasteSegment segment = iterator.next();

				if (((segment.getPoint().x) % 2) == 0) {
					drawSegment(graphics, segment.getPoint().x,
							segment.getPoint().y, 1, segment.getImage(), paint,
							stroke);
				} else {
					drawSegment(graphics, segment.getPoint().x,
							segment.getPoint().y, divider, segment.getImage(),
							paint, stroke);
				}

			}
		}

		copyPaste.prePaint();

		// paint = Color.RED;
		/*
		 * paint = new ColorUIResource(136, 0, 21); paint = new
		 * ColorUIResource(206, 0, 31); paint = new ColorUIResource(224, 0, 32);
		 * 
		 * // stroke = new BasicStroke(5.0f); float dash2[] = { 5.0f }; stroke =
		 * new BasicStroke(2.0f, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND,
		 * 5.0f, dash2, 0.0f);
		 */
		DraggedSegments draggedSegments = copyPaste.getDraggedSegments();

		// if (draggedSegments != null && draggedSegments.isTheSame()) {
		if (draggedSegments != null) {
			Paint paint = draggedSegments.getPaint();
			Stroke stroke = draggedSegments.getStroke();

			Iterator<CopyPasteSegment> iterator = draggedSegments.iterator();

			while (iterator.hasNext()) {
				CopyPasteSegment segment = iterator.next();

				int firstColumn = getFirstVisibleColumnNumber();// + 1;
				int lastColumn = getLastVisibleColumnNumber();// - 1;
				int firstRow = getFirstVisibleRowNumber();// + 1;
				int lastRow = getLastVisibleRowNumber();// - 1;

				Point point = segment.getPoint();
				if (point.x >= firstColumn && point.x <= lastColumn
						&& point.y >= firstRow && point.y <= lastRow) {

					if (((segment.getPoint().x) % 2) == 0) {
						drawSegment(graphics, segment.getPoint().x,
								segment.getPoint().y, 1, segment.getImage(),
								paint, stroke);
					} else {
						drawSegment(graphics, segment.getPoint().x,
								segment.getPoint().y, divider,
								segment.getImage(), paint, stroke);
					}
				}
			}
		}

		copyPaste.paint(graphics);
	}

	public void paint_222(Graphics graphics) {
		// copyPaste.paint(graphics);
		super.paint(graphics);

		CopyPasteSegments cpsSelected = copyPaste.getSelectedSegments();

		if (cpsSelected != null) {
			LinkedList<LinkedList<CopyPasteSegment>> selectedSegments = cpsSelected
					.getSegments();

			if (selectedSegments != null) {

				int divider = 1;
				if (isLayoutHex()) {
					divider = 2;
				}

				ImageIcon imageFile = new ImageIcon("images/frontwheelar.png");
				Image image = imageFile.getImage();

				for (LinkedList<CopyPasteSegment> column : selectedSegments) {
					for (CopyPasteSegment segment : column) {

						// System.out.println(point.x + " <> " + point.y);

						if (((segment.getPoint().x) % 2) == 0) {
							drawSegment(graphics, segment.getPoint().x,
									segment.getPoint().y, 1, image);
						} else {
							drawSegment(graphics, segment.getPoint().x,
									segment.getPoint().y, divider, image);
						}

					}
				}

			}
		}

		copyPaste.prePaint();

		DraggedSegments cpsDragged = copyPaste.getDraggedSegments();

		if (cpsSelected != null && cpsDragged != null) {
			// boolean areTheSame = copyPaste.areSegmentsSame(selectedSegments,
			// draggedSegments);

			LinkedList<LinkedList<CopyPasteSegment>> draggedSegments = cpsDragged
					.getSegments();

			LinkedList<LinkedList<CopyPasteSegment>> selectedSegments = cpsSelected
					.getSegments();

			// boolean areTheSame = copyPaste.areSegmentsSame(selectedSegments,
			// draggedSegments);

			// if (areTheSame) {
			// if (draggedSegments != null) {
			if (draggedSegments != null) {
				// if (cpsDragged.isTheSame()) {
				if (true) {
					/*
					 * int divider = 1; if (isLayoutHex()) { divider = 2; }
					 * 
					 * ImageIcon imageFile = new ImageIcon(
					 * "images/rearwheelar.png"); Image image =
					 * imageFile.getImage();
					 * 
					 * for (LinkedList<Point> column : draggedSegments) { for
					 * (Point point : column) {
					 * 
					 * System.out.println(point.x + " {} " + point.y);
					 * 
					 * if (((point.x) % 2) == 0) { drawSegment(graphics,
					 * point.x, point.y, 1, image); } else {
					 * drawSegment(graphics, point.x, point.y, divider, image);
					 * }
					 * 
					 * } }
					 */

					if (draggedSegments != null) {

						int divider = 1;
						if (isLayoutHex()) {
							divider = 2;
						}

						int dragColNo = draggedSegments.size();

						for (int x = 0; x < dragColNo; x++) {

							LinkedList<CopyPasteSegment> dragRow = draggedSegments
									.get(x);
							LinkedList<CopyPasteSegment> selRow = selectedSegments
									.get(x);

							int rowNo = dragRow.size();

							for (int y = 0; y < rowNo; y++) {
								CopyPasteSegment dragSegment = dragRow.get(y);
								CopyPasteSegment selSegment = selRow.get(y);

								Image image = getImage(selSegment.getPoint().x,
										selSegment.getPoint().y);
								if (((dragSegment.getPoint().x) % 2) == 0) {
									drawSegment(graphics,
											dragSegment.getPoint().x,
											dragSegment.getPoint().y, 1, image);
								} else {
									drawSegment(graphics,
											dragSegment.getPoint().x,
											dragSegment.getPoint().y, divider,
											image);
								}
							}

						}

					}
				}
			}

		}

		copyPaste.paint(graphics);

	}

	void onCutEvent() {
		copyPaste.onCutEvent();
	}

	void onCopyEvent() {
		copyPaste.onCopyEvent();
	}

	void onPasteEvent() {
		copyPaste.onPasteEvent();
	}

}
