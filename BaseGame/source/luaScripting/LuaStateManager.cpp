#include "LuaStateManager.h"

#include "../utilities/StringUtils.h"
#include "../debugging/Logger.h"
#include "../utilities/Templates.h"
#include "../resourceCache/ResourceCache.h"
#include "../resourceCache/ResourceHandle.h"
//#include "ScriptResourceExtraData.h"

#include <lua.hpp>
#include <iostream> // cout, endl
#include <string> // string
#include <cstring>// strcpy
#include <sstream>      // std::stringstream
#include <boost/filesystem.hpp> // boost::filesystem::path; boost::filesystem::recursive_directory_iterator;
//boost::filesystem::filesystem_error; boost::filesystem::directory_entry; boost::filesystem::exists;
//boost::filesystem::is_directory; boost::filesystem::is_regular_file; boost::filesystem::create_directory
//boost::filesystem::remove_all; boost::filesystem::copy_file; boost::filesystem::ofstream;
#include <boost/optional.hpp> // boost::optional

using std::string;
using std::cout;
using std::endl;
using std::strcpy;
using std::stringstream;
using std::shared_ptr;
using boost::filesystem::path;
using boost::optional;

namespace base_game {

// const string LuaStateManager::SCRIPTS_FOLDER = "scripts/";
const string LuaStateManager::SCRIPTS_FOLDER = "scripts";

LuaStateManager::LuaStateManager(shared_ptr<ResourceCache> resourceCache) {
	logger::trace("Create LuaStateManager");

	this->shrdPtrResourceCache = resourceCache;
}

/*
 LuaStateManager::LuaStateManager(string assetsFolder) {
 logger::trace("Create LuaStateManager");
 scriptsFolder = assetsFolder  + SCRIPTS_FOLDER;
 }
 */

LuaStateManager::~LuaStateManager() {
	logger::trace("Destroy LuaStateManager");
}

void LuaStateManager::print_error(lua_State* state) {
	// The error message is on top of the stack.
	// Fetch it, print it and then pop it off the stack.
	const char* message = lua_tostring(state, -1);
	puts(message);
	lua_pop(state, 1);
}

void LuaStateManager::execute(const char* filename) {
	lua_State *state = luaL_newstate();

	// Make standard libraries available in the Lua object
	luaL_openlibs(state);

	int result;

	lua_register(state, "howdy", lua_state_manager::howdy);

	// Load the program; this supports both source code and bytecode files.
	result = luaL_loadfile(state, filename);

	if (result != LUA_OK) {
		print_error(state);
		return;
	}

	// Finally, execute the program by calling into it.
	// Change the arguments if you're not running vanilla Lua code.

	result = lua_pcall(state, 0, LUA_MULTRET, 0);

	if (result != LUA_OK) {
		print_error(state);
		return;
	}
}

/*
 * int LuaState::DoString( const char *str, LuaObject& fenvObj )
 {
 lua_State* L = LuaState_to_lua_State(this);
 int status = luaL_loadbuffer(L, str, strlen(str), str);
 if (status != 0)
 return status;
 fenvObj.Push();
 SetFEnv(-2);
 return lua_pcall(L, 0, LUA_MULTRET, 0);
 }
 */

void LuaStateManager::temp_executeBuffer(const char* buffer) {
	lua_State *state = luaL_newstate();

	// Make standard libraries available in the Lua object
	luaL_openlibs(state);

	int result;

	stringstream ss;
	ss << "strlen -> " << strlen(buffer);
	logger::info(ss);

	logger::info("---START---");
	logger::info("");

	for (int i = 0; i < strlen(buffer); i++) {
		ss << *(buffer + i);
	}

	logger::info(ss);

	logger::info("---END---");

	lua_register(state, "howdy", lua_state_manager::howdy);

	// Load the program; this supports both source code and bytecode files.
	//result = luaL_loadfile(state, filename);

	result = luaL_loadbuffer(state, buffer, strlen(buffer),
			"gameScript") || lua_pcall(state, 0, 0, 0);

	// result = luaL_dostring(state, "print(\"Hello Lua String!!\")"); // attempt to call a nil value

	if (result != LUA_OK) {
		print_error(state);
		lua_pop(state, 1); /* pop error message from the stack */
	}

	lua_close(state);
}

void LuaStateManager::temp_executeBuffer_111(const char* buffer) {
	lua_State *state = luaL_newstate();

	// Make standard libraries available in the Lua object
	luaL_openlibs(state);

	int result;

	stringstream ss;
	ss << "strlen -> " << strlen(buffer);
	logger::info(ss);

	logger::info("---START---");
	logger::info("");

	for (int i = 0; i < strlen(buffer); i++) {
		ss << *(buffer + i);
	}

	logger::info(ss);

	logger::info("---END---");

	lua_register(state, "howdy", lua_state_manager::howdy);

	// Load the program; this supports both source code and bytecode files.
	//result = luaL_loadfile(state, filename);

	result = luaL_loadbuffer(state, buffer, strlen(buffer), buffer);

	// result = luaL_dostring(state, "print(\"Hello Lua String!!\")"); // attempt to call a nil value

	if (result != LUA_OK) {
		print_error(state);
		return;
	}

	// Finally, execute the program by calling into it.
	// Change the arguments if you're not running vanilla Lua code.

	result = lua_pcall(state, 0, LUA_MULTRET, 0);

	if (result != LUA_OK) {
		print_error(state);
		return;
	}

	lua_close(state);

}

void LuaStateManager::executeBuffer111(const char* buffer) {
	lua_State *state = luaL_newstate();

	// Make standard libraries available in the Lua object
	luaL_openlibs(state);

	int result;

	//lua_register(state, "howdy", lua_state_manager::howdy);

	// Load the program; this supports both source code and bytecode files.
	//result = luaL_loadfile(state, filename);

	result = luaL_dostring(state, buffer);

	if (result != LUA_OK) {
		print_error(state);
		return;
	}

	// Finally, execute the program by calling into it.
	// Change the arguments if you're not running vanilla Lua code.

	result = lua_pcall(state, 0, LUA_MULTRET, 0);

	if (result != LUA_OK) {
		print_error(state);
		return;
	}
}

char* LuaStateManager::loadScript(string scriptFileName) {
	stringstream ss;

	path resourcePath { LuaStateManager::SCRIPTS_FOLDER };
	resourcePath /= scriptFileName;
	resourcePath = resourcePath.make_preferred();

	ss << "resourcePath: " << resourcePath.string();
	logger::info(ss);

	string resourceName = resourcePath.string();

	Resource resource(resourceName);
	optional<shared_ptr<ResourceHandle>> pResourceHandle =
			shrdPtrResourceCache->getHandle(&resource);

	// stringstream ss;

	ss << "resourceNameXXX: " << pResourceHandle.get()->getName();
	logger::info(ss);

	ss << "resourceName: " << pResourceHandle.get()->getName();
	logger::info(ss);

	uintmax_t size = pResourceHandle.get()->getSize();
	char *resourceBuffer = pResourceHandle.get()->getBuffer();

	return resourceBuffer;
	/*
	 if (shared_ptr<ScriptResourceExtraData> scriptResourceExtraData =
	 dynamic_pointer_cast < ScriptResourceExtraData > (extraData)) {
	 result = scriptResourceExtraData->getData();
	 }
	 */
}

void LuaStateManager::temp_testLuaResourceCache(string scriptFileName) {
	char* scriptAsChar = loadScript(scriptFileName);
	temp_executeBuffer(scriptAsChar);

}

/*
 void LuaStateManager::testLua(string scriptFileName) {
 string scriptsFolder = "null";

 stringstream ss;
 ss << "lua script: " << scriptFileName;
 logger::trace(ss);

 string scriptFullFileName = scriptsFolder + scriptFileName;
 ss << "lua full script: " << scriptFullFileName;
 logger::trace(ss);


 char* scriptNameChar = string_utils::stringToChar(scriptFullFileName);

 execute(scriptNameChar);

 //lua_State *state = luaL_newstate();
 //lua_close(state);

 templates::safe_delete_array<char>(scriptNameChar);
 //	string_utils::safe_delete_char_array(scriptNameChar);
 }
 */

namespace lua_state_manager {

int howdy(lua_State* state) {
	// The number of function arguments will be on top of the stack.
	int args = lua_gettop(state);

	stringstream ss;
	ss << "howdy() was called with " << args << " arguments";
	logger::trace(ss);

	for (int n = 1; n <= args; ++n) {
		ss << "  argument " << n << ": " << lua_tostring(state, n);
		logger::trace(ss);
	}

	// Push the return value on top of the stack. NOTE: We haven't popped the
	// input arguments to our function. To be honest, I haven't checked if we
	// must, but at least in stack machines like the JVM, the stack will be
	// cleaned between each function call.

	lua_pushnumber(state, 123);

	// Let Lua know how many return values we've passed
	return 1;
}
}
}
