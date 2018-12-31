/*
 * IPointerHandler.h
 *
 *  Created on: 28 gru 2018
 *      Author: Krzysztof
 */

#ifndef INPUTDEVICES_IPOINTERHANDLER_H_
#define INPUTDEVICES_IPOINTERHANDLER_H_

namespace base_game {

class IPointerHandler {
public:
	IPointerHandler();
	virtual ~IPointerHandler();

	//virtual bool VOnPointerMove(const Point &pos, const int radius) = 0;
	//virtual bool VOnPointerButtonDown(const Point &pos, const int radius, const std::string &buttonName) = 0;
	//virtual bool VOnPointerButtonUp(const Point &pos, const int radius, const std::string &buttonName) = 0;

	virtual bool vOnMouseFunc(int button, int state, int x, int y) = 0;
	virtual bool vOnMotionFunc(int x, int y) = 0;
	virtual bool vOnPassiveMotionFunc(int x, int y) = 0;
	virtual bool vOnMouseWheelFunc(int wheel, int direction, int x, int y) = 0;

};

namespace pointer_handler {
void onMouseFunc(int button, int state, int x, int y);
void onMotionFunc(int x, int y);
void onPassiveMotionFunc(int x, int y);
void onMouseWheelFunc(int wheel, int direction, int x, int y);
}

} /* namespace base_game */

#endif /* INPUTDEVICES_IPOINTERHANDLER_H_ */
