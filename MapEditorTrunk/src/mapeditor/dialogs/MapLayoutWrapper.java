package mapeditor.dialogs;

import mapeditor.mapapi.MapLayout;
import mapeditor.messages.MapMessages;

public class MapLayoutWrapper {

	private String name;
	private MapLayout mapLayout;

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

		this.mapLayout = mapLayout;

	}

	@Override
	public String toString() {
		return name;
	}

	public MapLayout getMapLayout() {
		return mapLayout;
	}
}
