#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

namespace base_game {
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
