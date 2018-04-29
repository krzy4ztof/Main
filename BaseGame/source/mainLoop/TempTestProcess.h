#ifndef TEMPTESTPROCESS_H
#define TEMPTESTPROCESS_H

#include "Process.h"

#include <string> // string

namespace base_game {
	class TempTestProcess : public Process {
		public:
			TempTestProcess(std::string action);
			virtual ~TempTestProcess();

		protected:
			virtual void vOnUpdate(unsigned long deltaMs);

		private:
			std::string action;
	};
}

#endif // TEMPTESTPROCESS_H
