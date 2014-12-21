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
public class MapThemesManager {

	private LinkedList<MapObjectsTheme> themesList = null;

	private LinkedList<ThemeApi> themeApiList = null;

	private MapObjectsTheme selectedTheme = null;

	public MapThemesManager() {
		themesList = new LinkedList<MapObjectsTheme>();
		themeApiList = new LinkedList<ThemeApi>();
	}

	public Iterator<MapObjectsTheme> getThemesIterator() {
		Iterator<MapObjectsTheme> it = this.themesList.iterator();

		return it;
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

		return mapObject;
	}

	public MapObjectsTheme getSelectedTheme() {
		return selectedTheme;
	}

	public void setSelectedTheme(MapObjectsTheme selectedTheme) {
		this.selectedTheme = selectedTheme;
	}

	public void setSelectedTheme(String name) {
		selectedTheme = getThemeByName(name);
	}
}
