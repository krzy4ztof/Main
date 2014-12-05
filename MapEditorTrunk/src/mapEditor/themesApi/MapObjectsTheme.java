/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package mapEditor.themesApi;

import java.util.Iterator;
import java.util.LinkedList;
import mapEditor.mapApi.MapObject;

/**
 *
 * @author krzysztof
 */
public class MapObjectsTheme{

    private String name;
    private LinkedList<MapObject> objectsList = null;

    public MapObjectsTheme(String name) {
        this.name = name;
        objectsList = new LinkedList<MapObject>();
    }

    public String getName() {
        return name;
    }

    public LinkedList<MapObject> getObjectsList() {
        return objectsList;
    }

    public Iterator<MapObject> getObjectsIterator(){
        Iterator<MapObject> it = this.objectsList.iterator();

        return it;
    }

    public boolean addMapObject(MapObject mapObject){

        return objectsList.add(mapObject);
    }

    public MapObject getMapObject(int index){
        
        if (objectsList.size() < index){
            return null;
        }
 
        return objectsList.get(index);
    }

    /**
     * Searches for MapObject which objectName equals name
     * @param name
     * @return
     */
    public MapObject getMapObject(String name){
        
        for (MapObject mapObject: objectsList){
            if (mapObject.getObjectName().equals(name)){
                return mapObject;
            }

        }
        return null;
    }


    public int getThemeSize(){

        return objectsList.size();
    }

    public void describeYourself() {

        System.out.println("Theme name: " + name);
        MapObject curObject = null;
        for (Iterator<MapObject> it = this.getObjectsIterator(); it.hasNext();) {
            curObject = it.next();
            curObject.describeYourself();
        }
    }
}
