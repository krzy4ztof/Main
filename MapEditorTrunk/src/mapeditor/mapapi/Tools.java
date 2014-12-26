package mapeditor.mapapi;

public class Tools {

	private ToolsEnum activeTool;

	public enum ToolsEnum {
		ERASER, BRUSH, BUCKET, PICKER, SELECTION
	}

	public void setActiveTool(ToolsEnum toolsEnum) {
		activeTool = toolsEnum;
	}

	public ToolsEnum getActiveTool() {
		return activeTool;
	}
}
