/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package mapeditor.themesapi;

import java.util.Iterator;
import java.util.LinkedList;

import mapeditor.mapapi.MapObject;

/**
 *
 * @author krzysztof
 */
public class MapThemesList {

	private LinkedList<MapObjectsTheme> themesList = null;

	private MapObjectsTheme currentTheme = null;

	public MapThemesList() {
		themesList = new LinkedList<MapObjectsTheme>();
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

	public MapObjectsTheme getCurrentTheme() {
		return currentTheme;
	}

	public void setCurrentTheme(MapObjectsTheme currentTheme) {
		this.currentTheme = currentTheme;
	}

	public void setCurrentTheme(String name) {
		currentTheme = getThemeByName(name);
	}
}
