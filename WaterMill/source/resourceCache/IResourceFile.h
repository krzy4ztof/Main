#ifndef IRESOURCEFILE_H
#define IRESOURCEFILE_H

namespace base_game {
	class IResourceFile {
		public:
			virtual ~IResourceFile();
			virtual bool vOpen()=0;

		protected:

		private:
	};
}
#endif // IRESOURCEFILE_H
