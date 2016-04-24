package mapeditor.mapapi;

public class Tools {

	private ToolsEnum activeTool;

	private ToolsEnum previousTool;

	public enum ToolsEnum {
		ERASER, BRUSH, BUCKET, PICKER, SELECTION, HAMMER, POINT_PROPERTY
	}

	public Tools() {
	}

	public void setActiveTool(ToolsEnum toolsEnum) {
		if (toolsEnum != activeTool) {
			previousTool = activeTool;
		}

		activeTool = toolsEnum;
	}

	public ToolsEnum getActiveTool() {
		return activeTool;
	}

	public void restorePreviousTool() {
		if (previousTool != null) {
			activeTool = previousTool;
		}

		previousTool = null;
	}
}
