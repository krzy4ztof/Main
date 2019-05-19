#ifndef DELAYPROCESS_H
#define DELAYPROCESS_H

#include "Process.h"

namespace base_game {
class DelayProcess: public Process {
public:
	explicit DelayProcess(unsigned long timeToDelay);
	virtual ~DelayProcess();

protected:
	virtual void vOnUpdate(unsigned long deltaMs);
private:
	unsigned long m_timeToDelay;
	unsigned long m_timeDelayedSoFar;

};
}

#endif // DELAYPROCESS_H
