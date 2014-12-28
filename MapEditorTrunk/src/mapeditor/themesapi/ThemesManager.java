/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package mapeditor.themesapi;

import java.util.Iterator;
import java.util.LinkedList;

/**
 *
 * @author krzysztof
 */
public class ThemesManager {

	private LinkedList<MapObjectsTheme> themesList = null;

	private LinkedList<ThemeApi> themeApiList = null;

	private MapObjectsTheme selectedTheme = null;

	private ThemeApi selectedThemeApi = null;

	private MapObject selectedMapObject;

	private MapObjectFactory mapObjectFactory;

	public ThemesManager(MapObjectFactory mapObjectFactory) {
		this.mapObjectFactory = mapObjectFactory;
		themesList = new LinkedList<MapObjectsTheme>();
		themeApiList = new LinkedList<ThemeApi>();
		selectedMapObject = mapObjectFactory.getBlankMapObject();
	}

	public Iterator<MapObjectsTheme> getThemesIterator() {
		Iterator<MapObjectsTheme> it = this.themesList.iterator();

		return it;
	}

	public LinkedList<ThemeApi> getThemesApis() {
		return themeApiList;
	}

	public MapObjectsTheme getFirstTheme() {

		return themesList.getFirst();
	}

	public boolean addTheme(MapObjectsTheme mapObjectsTheme) {
		return themesList.add(mapObjectsTheme);
	}

	public boolean addThemeApi(ThemeApi themeApi) {
		return themeApiList.add(themeApi);
	}

	public void describeYourself() {

		MapObjectsTheme curTheme = null;
		for (Iterator<MapObjectsTheme> it = this.getThemesIterator(); it
				.hasNext();) {
			curTheme = it.next();
			curTheme.describeYourself();
		}
	}

	public void describeYourselfThemeApi() {

		for (ThemeApi themeApi : themeApiList) {
			themeApi.describeYourself();
		}
	}

	public MapObjectsTheme getThemeByName(String themeName) {
		MapObjectsTheme mapObjectsTheme = null;

		for (Iterator<MapObjectsTheme> it = this.getThemesIterator(); it
				.hasNext();) {
			mapObjectsTheme = it.next();

			if (mapObjectsTheme.getName().contentEquals(themeName)) {
				return mapObjectsTheme;
			}
		}

		return null;
	}

	/**
	 * Searches within all MapObjectsThemes for MapObject with objectName equal
	 * to name parameter.
	 * 
	 * @param name
	 * @return
	 */
	public MapObject getMapObject(String name) {
		MapObjectsTheme curTheme = null;
		MapObject mapObject = null;
		for (Iterator<MapObjectsTheme> it = this.getThemesIterator(); it
				.hasNext();) {
			curTheme = it.next();
			mapObject = curTheme.getMapObject(name);

			if (mapObject != null) {
				return mapObject;
			}
		}

		if (mapObject == null) {
			mapObject = mapObjectFactory.getBlankMapObject();
		}
		return mapObject;
	}

	public MapObjectsTheme getSelectedTheme() {
		return selectedTheme;
	}

	public ThemeApi getSelectedThemeApi() {
		if (selectedThemeApi == null && !themeApiList.isEmpty()) {
			selectedThemeApi = themeApiList.getFirst();
		}

		return selectedThemeApi;
	}

	public void setSelectedTheme(MapObjectsTheme selectedTheme) {
		this.selectedTheme = selectedTheme;
	}

	public void setSelectedTheme(String name) {
		selectedTheme = getThemeByName(name);
	}

	public MapObject getSelectedMapObject() {
		return selectedMapObject;
	}

	public void setSelectedMapObject(MapObject selectedMapObject) {
		this.selectedMapObject = selectedMapObject;
	}
}
