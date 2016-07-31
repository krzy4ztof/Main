#ifndef LUASTATEMANAGER_H
#define LUASTATEMANAGER_H

#include <lua.hpp> // lua_State
#include <string> // string

namespace watermill {
	class LuaStateManager {
		public:
			const static std::string SCRIPTS_FOLDER;

			LuaStateManager(std::string assetsFolder);
			virtual ~LuaStateManager();
			void testLua(std::string scriptFileName);

		protected:

		private:
			std::string scriptsFolder;

			void print_error(lua_State* state);
			void execute(const char* filename);
	};

	namespace lua_state_manager {
		void safe_delete(LuaStateManager* p);
		int howdy(lua_State* state);
	}
}
#endif // LUASTATEMANAGER_H
