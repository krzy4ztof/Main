#ifndef IGAMEVIEW_H
#define IGAMEVIEW_H

namespace base_game {
	class IGameView {
		public:
			virtual ~IGameView();

	virtual void vOnRestore() = 0;
	virtual void vOnRender(double fTime, float fElapsedTime) = 0;
	virtual void vOnAttach(unsigned int vid, unsigned int aid) = 0;
	virtual void describeYourself() = 0;

	virtual bool vOnKeyboardFunc(unsigned char key, int x, int y);
	virtual bool vOnKeyboardUpFunc(unsigned char key, int x, int y);
	virtual bool vOnSpecialFunc(int key, int x, int y);
	virtual bool vOnSpecialUpFunc(int key, int x, int y);
	virtual bool vOnMouseFunc(int button, int state, int x, int y);
	virtual bool vOnMotionFunc(int x, int y);
	virtual bool vOnPassiveMotionFunc(int x, int y);
	virtual bool vOnMouseWheelFunc(int wheel, int direction, int x, int y);

	virtual void tempVLoadGameDelegate() = 0;


		protected:

		private:
	};
}

#endif // IGAMEVIEW_H
