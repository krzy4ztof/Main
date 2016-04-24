package mapeditor.themesapi;

import java.util.AbstractMap.SimpleEntry;
import java.util.HashMap;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Set;

public class EnumProperty extends MapObjectProperty {

	private Map<String, String> choices = null;
	private String key;

	public EnumProperty(String name, String key, String valueExternal) {
		super(name);
		choices = new HashMap<String, String>();
		this.key = key;
		choices.put(key, valueExternal);
	}

	public String getKey() {
		return key;
	}

	public void setKey(String key) {
		this.key = key;
	}

	public void addChoiceValue(String value, String valueExternal) {
		choices.put(value, valueExternal);
	}

	public Entry<String, String>[] getKeysEntrySet() {
		Set<Entry<String, String>> set = choices.entrySet();

		@SuppressWarnings("unchecked")
		Entry<String, String>[] array = set.toArray(new Entry[1]);

		return array;
	}

	public Entry<String, String> getEntry(String key) {
		return new SimpleEntry<String, String>(key, choices.get(key));

	}

	public Entry<String, String> getCurrentEntry() {
		return getEntry(key);

	}

	public String[] getKeys() {
		return choices.keySet().toArray(new String[1]);
	}

	@Override
	public Type getType() {
		return Type.Enum;
	}

	@Override
	public String getValueAsString() {
		return key;
	}

	@Override
	public void setValue(String value) {
		setKey(value);
	}

}
