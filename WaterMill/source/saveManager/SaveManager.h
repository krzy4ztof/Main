#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#include <string> // string
#include <boost/filesystem.hpp>// path

namespace base_game {
	class SaveManager {
		public:
			SaveManager();
			virtual ~SaveManager();
			void init(std::string userProfile, std::string gameAppDir);


		protected:

		private:
			boost::filesystem::path* savePath;
	};

	namespace save_manager {
		void safe_delete(SaveManager* p);
	}
}
#endif // SAVEMANAGER_H
