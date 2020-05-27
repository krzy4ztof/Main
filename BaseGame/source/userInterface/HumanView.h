#ifndef HUMANVIEW_H
#define HUMANVIEW_H

#include "IGameView.h"
#include "../inputDevices/IPointerHandler.h"
#include "../inputDevices/IKeyboardHandler.h"
#include "../graphics3d/FpsCounter.h"
#include "../graphics3d/OpenGLRenderer.h"
#include "IScreenElement.h"
#include "../mainLoop/ProcessManager.h"

#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h> // GLFWwindow
#include <memory> // shared_ptr, weak_ptr
#include <list> // list

namespace base_game {

typedef std::list<std::shared_ptr<IScreenElement> > ScreenElementList;

class HumanView: public IGameView {
	// See: page 272
public:
	HumanView(std::shared_ptr<OpenGLRenderer> openGLRenderer);
	virtual ~HumanView();

	virtual void vOnRestore();
	virtual void vOnRender(double fTime, float fElapsedTime);
	virtual void vOnAttach(unsigned int vid, unsigned int aid);
	virtual void vOnUpdate(unsigned long deltaMs);
	virtual void describeYourself();


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

	virtual void tempVLoadGameDelegate();
	virtual void tempVRender(double fTime, float fElapsedTime);

	// Virtual methods to control the layering of interface elements
	virtual void vPushElement(std::shared_ptr<IScreenElement> pElement);
	virtual void vRemoveElement(std::shared_ptr<IScreenElement> pElement);

protected:
	virtual void vRenderText();


	unsigned int m_ViewId;
	unsigned int m_ActorId;
	ProcessManager *pProcessManager;				// a game logic entity
	std::shared_ptr<IPointerHandler> m_PointerHandler;
	std::shared_ptr<IKeyboardHandler> m_KeyboardHandler;
	std::shared_ptr<OpenGLRenderer> openGLRenderer;

	float tempAngle;
	FpsCounter *fpsCounter;
	ScreenElementList m_ScreenElements;

	/*
protected:
	GameViewId m_ViewId;
	ActorId m_ActorId;
// this ProcessManager is for things like button animations, etc.
	ProcessManager *m_pProcessManager;
	DWORD m_currTick; // time right now
	DWORD m_lastDraw; // last time the game rendered
	bool m_runFullSpeed; // set to true if you want to run full speed
	virtual void VRenderText() {
	}
	;
public:
	bool LoadGame(TiXmlElement *pLevelData);
protected:
	virtual bool VLoadGameDelegate(TiXmlElement *pLevelData) {
		return true;
	}
	
public:
// Implement the IGameView interface
	virtual HRESULT VOnRestore();
	virtual void VOnRender(double fTime, float fElapsedTime);
	virtual void VOnLostDevice();
	virtual GameViewType VGetType() {
		return GameView_Human;
	}
	virtual GameViewId VGetId() const {
		return m_ViewId;
	}
	virtual void VOnAttach(GameViewId vid, optional<ActorId> aid) {
		m_ViewId = vid;
		m_ActorId = aid;
	}
	virtual LRESULT CALLBACK VOnMsgProc( AppMsg msg );
	virtual void VOnUpdate(int deltaMilliseconds);
// Virtual methods to control the layering of interface elements
	virtual void VPushElement(shared_ptr<IScreenElement> pElement);
	virtual void VRemoveElement(shared_ptr<IScreenElement> pElement);
	void TogglePause(bool active);
	˜ HumanView();
	HumanView(D3DCOLOR background);
	ScreenElementList m_ScreenElements;
	 // Interface sensitive objects
	 shared_ptr<IPointerHandler> m_PointerHandler;
	 int m_pointerRadius;
	 shared_ptr<IKeyboardHandler> m_KeyboardHandler;
	 // Audio
	 bool InitAudio();
	 //Camera adjustments.
	 virtual void VSetCameraOffset(const Vec4 & camOffset ) { }
	 protected:
	 virtual bool VLoadGameDelegate(TiXmlElement* pLevelData) { return true; }
	 };
	 */
};
}

#endif // HUMANVIEW_H
