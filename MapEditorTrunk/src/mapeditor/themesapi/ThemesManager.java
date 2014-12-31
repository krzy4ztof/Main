package mapeditor.themesapi;

import java.util.LinkedList;

/**
 *
 * @author krzysztof
 */
public class ThemesManager {

	private LinkedList<ThemeApi> themeApiList = null;

	private ThemeApi selectedThemeApi = null;

	private MapObject selectedMapObject;

	private MapObjectFactory mapObjectFactory;

	public ThemesManager(MapObjectFactory mapObjectFactory) {
		this.mapObjectFactory = mapObjectFactory;
		themeApiList = new LinkedList<ThemeApi>();
		selectedMapObject = mapObjectFactory.getBlankMapObject();
	}

	public LinkedList<ThemeApi> getThemesApis() {
		return themeApiList;
	}

	public boolean addThemeApi(ThemeApi themeApi) {
		return themeApiList.add(themeApi);
	}

	public void describeYourselfThemeApi() {

		for (ThemeApi themeApi : themeApiList) {
			themeApi.describeYourself();
		}
	}

	public MapObject getMapObjectApi(String name) {
		MapObject mapObject = null;
		for (ThemeApi themeApi : themeApiList) {
			mapObject = themeApi.getMapObject(name);
			if (mapObject != null) {
				return mapObject;
			}
		}

		if (mapObject == null) {
			mapObject = mapObjectFactory.getBlankMapObject();
		}
		return mapObject;
	}

	public ThemeApi getSelectedThemeApi() {
		if (selectedThemeApi == null && !themeApiList.isEmpty()) {
			selectedThemeApi = themeApiList.getFirst();
		}

		return selectedThemeApi;
	}

	public MapObject getSelectedMapObject() {
		return selectedMapObject;
	}

	public void setSelectedMapObject(MapObject selectedMapObject) {
		this.selectedMapObject = selectedMapObject;
	}
}
