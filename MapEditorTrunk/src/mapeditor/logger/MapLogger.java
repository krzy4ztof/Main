package mapeditor.logger;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.logging.FileHandler;
import java.util.logging.Level;
import java.util.logging.LogManager;
import java.util.logging.Logger;
import java.util.logging.SimpleFormatter;

public class MapLogger {

	public static String APPLICATION_STARTUP = "info.applicationStartup";
	public static String FILE_VALID = "info.fileValid";
	public static String ACTION_COMMAND = "info.actionCommand";
	public static String MOUSE_CLICKED = "info.mouseClicked";

	public static String FILE_NOT_VALID = "error.fileNotValid";
	public static String REASON = "error.reason";
	public static String ERROR = "error.error";

	public static String DESCRIBE_MAP_OBJECT = "describe.mapObject";
	public static String DESCRIBE_MAP_OBJECT_PROPERTY = "describe.mapObjectProperty";
	public static String DESCRIBE_DEFAULT_MAP_OBJECT_PROPERTY = "describe.defaultMapObjectProperty";
	public static String DESCRIBE_THEME = "describe.theme";
	public static String DESCRIBE_THEME_ROW = "describe.themeRow";
	public static String DESCRIBE_CUSTOM_OBJECT_START = "describe.customObjectStart";
	public static String DESCRIBE_CUSTOM_OBJECT_END = "describe.customObjectEnd";
	public static String DESCRIBE_LAYER_ATTRIBUTES = "describe.layerAttributes";

	private Logger logger;

	private void activateLogManager(String loggerConfigFile)
			throws SecurityException, IOException {
		LogManager manager = LogManager.getLogManager();

		File file = new File(loggerConfigFile);
		InputStream ins = new FileInputStream(file);

		manager.readConfiguration(ins);

	}

	public MapLogger(String loggerConfigFile) throws SecurityException,
			IOException {

		activateLogManager(loggerConfigFile);
		logger = Logger.getLogger("mapeditor", "mapeditor.messages.Logger");

		FileHandler fileHandler = new FileHandler("log.txt");
		SimpleFormatter simpleFormatter = new SimpleFormatter();
		fileHandler.setFormatter(simpleFormatter);
		logger.addHandler(fileHandler);

		logger.setLevel(Level.FINE);
	}
}
