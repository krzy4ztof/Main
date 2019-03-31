#ifndef IGAMEVIEW_H
#define IGAMEVIEW_H

#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h> // GLFWwindow

namespace base_game {
	class IGameView {
		public:
			virtual ~IGameView();

	virtual void vOnRestore() = 0;
	virtual void vOnRender(double fTime, float fElapsedTime) = 0;
	virtual void vOnAttach(unsigned int vid, unsigned int aid) = 0;
	virtual void describeYourself() = 0;

	// Start Freeglut
	/*
	virtual bool vOnKeyboardFunc(unsigned char key, int x, int y);
	virtual bool vOnKeyboardUpFunc(unsigned char key, int x, int y);
	virtual bool vOnSpecialFunc(int key, int x, int y);
	virtual bool vOnSpecialUpFunc(int key, int x, int y);
	virtual bool vOnMouseFunc(int button, int state, int x, int y);
	virtual bool vOnMotionFunc(int x, int y);
	virtual bool vOnPassiveMotionFunc(int x, int y);
	virtual bool vOnMouseWheelFunc(int wheel, int direction, int x, int y);
	 */
	// End Freelglut

	virtual bool vOnKeyCallback(GLFWwindow* window, int key, int scancode,
			int action, int mods);
	virtual bool vOnCharCallback(GLFWwindow* window, unsigned int codepoint);
	virtual bool vOnCharmodsCallback(GLFWwindow* window, unsigned int codepoint,
			int mods);
	virtual bool vOnCursorPositionCallback(GLFWwindow* window, double xpos,
			double ypos);
	virtual bool vOnCursorEnterCallback(GLFWwindow* window, int entered);
	virtual bool vOnMouseButtonCallback(GLFWwindow* window, int button,
			int action, int mods);
	virtual bool vOnScrollCallback(GLFWwindow* window, double xoffset,
			double yoffset);

	
	virtual void tempVLoadGameDelegate() = 0;
	bool tempIsActive = false; // To remove -> zdublowane z active, ktore tez bedzie usuniete

	virtual void vActivate(); // To remove -> wyswietlanie bedzie zalezalo od tego czy elementy sa widoczne
	virtual void vDeactivate(); // To remove -> wyswietlanie bedzie zalezalo od tego czy elementy sa widoczne
	virtual bool isActive(); // To remove -> wyswietlanie bedzie zalezalo od tego czy elementy sa widoczne

		protected:
	bool active = false; // To remove -> wyswietlanie bedzie zalezalo od tego czy elementy sa widoczne

		private:
	};
}

#endif // IGAMEVIEW_H
