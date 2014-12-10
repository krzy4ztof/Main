package mapeditor.dialogs;

import mapeditor.mapapi.MapLayout;
import mapeditor.messages.MapMessages;

public class MapLayoutWrapper {

	String name;

	MapLayoutWrapper(MapLayout mapLayout, MapMessages messages) {
		switch (mapLayout) {
		case HEX:
			name = messages.getLayoutHex();

			break;
		case SQR:
			name = messages.getLayoutSqr();

			break;
		default:
			name = "";
		}

	}

	@Override
	public String toString() {
		return name;
	}
}
