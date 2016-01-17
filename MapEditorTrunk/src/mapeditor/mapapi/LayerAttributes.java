package mapeditor.mapapi;

public class LayerAttributes {

	public final static int NO_ACTIVE_LAYER = -1;

	private boolean active = false;
	private boolean objectsVisible = true;
	private boolean backgroundVisible = true;
	private int index;

	public LayerAttributes(int index) {
		this.setIndex(index);
	}

	public boolean isActive() {
		return active;
	}

	public void setActive(boolean active) {
		this.active = active;
	}

	public boolean isObjectsVisible() {
		return objectsVisible;
	}

	public void setObjectsVisible(boolean objectsVisible) {
		this.objectsVisible = objectsVisible;
	}

	public boolean isBackgroundVisible() {
		return backgroundVisible;
	}

	public void setBackgroundVisible(boolean backgroundVisible) {
		this.backgroundVisible = backgroundVisible;
	}

	public Integer getIndex() {
		return index;
	}

	public void setIndex(int index) {
		this.index = index;
	}

	public void describeYourself() {
		System.out.println("    Layer index: " + index + "; active: " + active
				+ "; objectsVisible: " + objectsVisible + "; backgroundVisible"
				+ backgroundVisible);
	}

}
