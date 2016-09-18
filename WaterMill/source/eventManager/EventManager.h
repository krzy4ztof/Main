#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

namespace watermill {
	class EventManager {
		public:
			EventManager();
			virtual ~EventManager();

		protected:

		private:
	};

	namespace event_manager {
		void safe_delete(EventManager* p);
	}
}
#endif // EVENTMANAGER_H
