package mapeditor.mapapi;

import java.awt.Graphics;
import java.awt.Point;

public class CopyPaste {
	enum State {
		NEW, FIRSTPOINT, SELECTING, LASTPOINT, DRAG
	}

	private State state;

	private MapApi mapApi;

	private Point firstPoint;

	private Point lastPoint;

	public CopyPaste(MapApi mapApi) {
		this.mapApi = mapApi;
		state = State.NEW;
	}

	public void onLeftButtonClick(Point point) {
		if (state == State.NEW) {
			firstPoint = point;
			System.out.println(point.x + " " + point.y);
			state = State.FIRSTPOINT;
		}
	}

	public void paint(Graphics graphics) {

		if (state == State.FIRSTPOINT) {
			graphics.drawLine(firstPoint.x, firstPoint.y, firstPoint.x + 10,
					firstPoint.y + 10);
		}
	}
}
