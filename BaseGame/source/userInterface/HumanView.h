#ifndef HUMANVIEW_H
#define HUMANVIEW_H

#include "IGameView.h"
#include "../inputDevices/IPointerHandler.h"
#include "../inputDevices/IKeyboardHandler.h"

#include <memory> // shared_ptr, weak_ptr

namespace base_game {
	class HumanView : public IGameView {
		public:
			HumanView();
			virtual ~HumanView();

			virtual void vOnRestore();
			virtual void vOnRender(double fTime, float fElapsedTime);
			virtual void vOnAttach(unsigned int vid, unsigned int aid);
	virtual void describeYourself();
	virtual bool vOnKeyboardFunc(unsigned char key, int x, int y);
	virtual bool vOnKeyboardUpFunc(unsigned char key, int x, int y);
	virtual bool vOnSpecialFunc(int key, int x, int y);
	virtual bool vOnSpecialUpFunc(int key, int x, int y);
	virtual bool vOnMouseFunc(int button, int state, int x, int y);
	virtual bool vOnMotionFunc(int x, int y);
	virtual bool vOnPassiveMotionFunc(int x, int y);
	virtual bool vOnMouseWheelFunc(int wheel, int direction, int x, int y);


			void tempOnRender(double fTime, float fElapsedTime);
	virtual void tempVLoadGameDelegate();

protected:
	unsigned int m_ViewId;
	unsigned int m_ActorId;
	std::shared_ptr<IPointerHandler> m_PointerHandler;
	std::shared_ptr<IKeyboardHandler> m_KeyboardHandler;

		private:
			float tempAngle;
	};
}

#endif // HUMANVIEW_H
