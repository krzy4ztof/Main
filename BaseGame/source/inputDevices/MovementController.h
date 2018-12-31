/*
 * MovementController.h
 *
 *  Created on: 30 gru 2018
 *      Author: Krzysztof
 */

#ifndef INPUTDEVICES_MOVEMENTCONTROLLER_H_
#define INPUTDEVICES_MOVEMENTCONTROLLER_H_

#include "IKeyboardHandler.h"
#include "IPointerHandler.h"

namespace base_game {

class MovementController: public IKeyboardHandler, public IPointerHandler {
public:
	MovementController();
	virtual ~MovementController();

	virtual bool vOnKeyboardFunc(unsigned char key, int x, int y);
	virtual bool vOnKeyboardUpFunc(unsigned char key, int x, int y);
	virtual bool vOnSpecialFunc(int key, int x, int y);
	virtual bool vOnSpecialUpFunc(int key, int x, int y);

	virtual bool vOnMouseFunc(int button, int state, int x, int y);
	virtual bool vOnMotionFunc(int x, int y);
	virtual bool vOnPassiveMotionFunc(int x, int y);
	virtual bool vOnMouseWheelFunc(int wheel, int direction, int x, int y);

protected:
	//m_keys[]
};

} /* namespace base_game */

#endif /* INPUTDEVICES_MOVEMENTCONTROLLER_H_ */
