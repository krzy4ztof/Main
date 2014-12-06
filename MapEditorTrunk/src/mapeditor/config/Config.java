package mapeditor.config;

import java.util.ResourceBundle;

public class Config {
	
	private final String mapapiDefaultColumnsNumber = "mapapi.default.columns.number";
	
	private final String mapapiDefaultRowsNumber = "mapapi.default.rows.number";
	
	private ResourceBundle resourceBundle;
	
	
	public Config(){
		resourceBundle = ResourceBundle.getBundle("mapeditor.config.config");
	}
	
	public Integer getMapApiDefaultColumnsNumber(){
		String string = resourceBundle.getString(mapapiDefaultColumnsNumber);
		Integer integer = new Integer(string);
		return integer;
	}
	
	public Integer getMapApiDefaultRowsNumber(){
		String string = resourceBundle.getString(mapapiDefaultRowsNumber);
		Integer integer = new Integer(string);
		return integer;
	}
}
