#ifndef GAMEMAIN_H
#define GAMEMAIN_H

//#include "../gameInitialization/InitOptions.h"
//#include "../gameInitialization/DebuggingOptions.h"
//#include "../gameInitialization/PlayerOptions.h"

namespace watermill_base {
class GameMain {
public:
	GameMain();
	virtual ~GameMain();
	int init(int argc, char** argv);
protected:

private:
	//			InitOptions *initOptions;
	//			PlayerOptions *playerOptions;
	//			DebuggingOptions *debuggingOptions;
};
}
#endif // GAMEMAIN_H
