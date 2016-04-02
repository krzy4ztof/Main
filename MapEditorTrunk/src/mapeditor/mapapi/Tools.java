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

		System.out.println("1. AC " + activeTool + " PRE " + previousTool);

		if (toolsEnum != activeTool) {
			previousTool = activeTool;
		}

		/*
		 * if (activeTool != null && activeTool != previousTool) { previousTool
		 * = activeTool; }
		 */

		activeTool = toolsEnum;
		System.out.println("2. AC " + activeTool + " PRE " + previousTool);

	}

	public ToolsEnum getActiveTool() {
		return activeTool;
	}

	public void restorePreviousTool() {

		System.out.println("RESTORE AC " + activeTool + " PRE " + previousTool);
		if (previousTool != null) {
			activeTool = previousTool;
		}

		previousTool = null;
	}
}
