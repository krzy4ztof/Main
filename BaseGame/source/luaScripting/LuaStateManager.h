#ifndef LUASTATEMANAGER_H
#define LUASTATEMANAGER_H

#include "../resourceCache/ResourceCache.h"

#include <lua.hpp> // lua_State
#include <string> // string
#include <memory> // shared_ptr

namespace base_game {
	class LuaStateManager {
		public:
			const static std::string SCRIPTS_FOLDER;

	LuaStateManager(std::shared_ptr<ResourceCache> resourceCache);

	// LuaStateManager(std::string assetsFolder);
			virtual ~LuaStateManager();

	char* loadScript(std::string scriptFileName);

	void testLua(std::string scriptFileName); // TO REMOVE
	void temp_testLuaResourceCache(std::string scriptFileName);

		protected:

		private:
	std::shared_ptr<ResourceCache> shrdPtrResourceCache;
	// std::string scriptsFolder;


			void print_error(lua_State* state);
			void execute(const char* filename);
	void executeBuffer111(const char* buffer);
	void temp_executeBuffer_111(const char* buffer);
	void temp_executeBuffer(const char* buffer);
	};

	namespace lua_state_manager {
		int howdy(lua_State* state);
	}
}
#endif // LUASTATEMANAGER_H
