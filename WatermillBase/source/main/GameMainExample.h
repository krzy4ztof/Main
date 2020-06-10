#ifndef GAMEMAINEXAMPLE_H
#define GAMEMAINEXAMPLE_H

//#include "../gameInitialization/InitOptions.h"
//#include "../gameInitialization/DebuggingOptions.h"
//#include "../gameInitialization/PlayerOptions.h"

namespace watermill_base {
class GameMainExample {
public:
	GameMainExample();
	virtual ~GameMainExample();
	int init();
protected:

private:
	//			InitOptions *initOptions;
	//			PlayerOptions *playerOptions;
	//			DebuggingOptions *debuggingOptions;
};
}
#endif // GAMEMAINEXAMPLE_H
