package mapeditor.dialogs;

import mapeditor.mapapi.MapLayout;
import mapeditor.messages.MapMessages;

public class MapLayoutWrapper {

	String name;

	MapLayoutWrapper(MapLayout mapLayout, MapMessages messages) {
		switch (mapLayout) {
		case HEX:
			name = messages.getString(MapMessages.LAY_HEX);

			break;
		case SQR:
			name = messages.getString(MapMessages.LAY_SQR);

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
