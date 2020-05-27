#include "HumanView.h"
#include "../debugging/Logger.h"
#include "../inputDevices/MovementController.h"
#include "../graphics3d/FpsCounter.h"
#include "../graphics3d/OpenGLRenderer.h"
#include "../utilities/Templates.h"
#include "../mainLoop/ProcessManager.h"

// #include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h> // GLFWwindow
#include <sstream>      // std::stringstream
#include <memory> // shared_ptr, weak_ptr, make_shared

using std::stringstream;
using std::make_shared;
using std::shared_ptr;

namespace base_game {
HumanView::HumanView(std::shared_ptr<OpenGLRenderer> openGLRenderer) {
	logger::info("Create HumanView");
	tempAngle = 0.0f;

	m_PointerHandler = nullptr;
	m_KeyboardHandler = nullptr;

	m_ViewId = 0;
	m_ActorId = 0;
	fpsCounter = new FpsCounter();
	this->openGLRenderer = openGLRenderer;
	pProcessManager = new ProcessManager();
}

HumanView::~HumanView() {
	templates::safe_delete<ProcessManager>(pProcessManager);
	templates::safe_delete < FpsCounter > (fpsCounter);
	logger::info("Destroy HumanView");
	m_KeyboardHandler.reset();
	m_PointerHandler.reset();

	while (!m_ScreenElements.empty()) {
		m_ScreenElements.pop_front();
	}
}

void HumanView::vOnAttach(unsigned int vid, unsigned int aid) {
	m_ViewId = vid;
	m_ActorId = aid;
}

void HumanView::vOnRestore() {
	logger::info("vOnRestore HumanView");

	for (ScreenElementList::iterator i = m_ScreenElements.begin();
			i != m_ScreenElements.end(); ++i) {
		(*i)->vOnRestore();
	}
}

void HumanView::tempVRender(double currentTime, float fElapsedTime) {

}

void HumanView::vOnRender(double fTime, float fElapsedTime) {
	//logger::info("HumanView::vOnRender");
	stringstream ss;

	// miliseconds
	double time = glfwGetTime();
	double elapsedTime = time - fpsCounter->getLastTime();
	float elapsedTimeFloat = static_cast<float>(elapsedTime);

	ss << "GLUT RENDER SCENE: time:" << time << "; elapsedTime " << elapsedTime;
//			<< "; angle: " << angle;
	//logger::info(ss);

	//if (base_game::g_pApp != nullptr) {
	//	g_pApp->onUpdateGame(time, elapsedTimeFloat);

		if (fpsCounter->renderNextFrame(time)) {



			/* Render here */
		//glClear(GL_COLOR_BUFFER_BIT);

			//g_pApp->onFrameRender(time, elapsedTimeFloat);

			/* Swap front and back buffers */
		//glfwSwapBuffers (window);

			/* Poll for and process events */
		//glfwPollEvents();

		// Render the scene
			if (openGLRenderer->vPreRender()) {
			this->vRenderText();

			//m_ScreenElements.sort(SortBy_SharedPtr_Content<IScreenElement>());
			for (ScreenElementList::iterator i = m_ScreenElements.begin();
					i != m_ScreenElements.end(); ++i) {
				if ((*i)->vIsVisible()) {
					(*i)->vOnRender(fTime, fElapsedTime);
				}
			}

			this->tempVRender(fTime, fElapsedTime);
			/*
			 * VRenderText();
			 m_ScreenElements.sort(
			 SortBy_SharedPtr_Content<IScreenElement>());
			 for(ScreenElementList::iterator i=m_ScreenElements.begin();
			 i!=m_ScreenElements.end(); ++i)
			 {
			 if ( (*i)->VIsVisible() )
			 {
			 (*i)->VOnRender(fTime, fElapsedTime);
			 }
			 }
			 // record the last successful paint
			 m_lastDraw = m_currTick;

			 *
			 */

		}

		openGLRenderer->vPostRender();

			/*
			 * // Render the scene
			 if(g_pApp->m_Renderer->VPreRender())
			 {
			 VRenderText();
			 m_ScreenElements.sort(
			 SortBy_SharedPtr_Content<IScreenElement>());
			 for(ScreenElementList::iterator i=m_ScreenElements.begin();
			 i!=m_ScreenElements.end(); ++i)
			 {
			 if ( (*i)->VIsVisible() )
			 {
			 (*i)->VOnRender(fTime, fElapsedTime);
			 }
			 }
			 // record the last successful paint
			 m_lastDraw = m_currTick;
			 }
			 g_pApp->m_Renderer->VPostRender();
			 * 
			 */
		}
//	} else {
//		ss << "g_pApp not initialized " << time << "; angle: " << angle;
//		logger::info(ss);
//	}


}

void HumanView::vOnUpdate(unsigned long deltaMilliseconds) {

	pProcessManager->updateProcesses(deltaMilliseconds);

	// m_Console.Update(deltaMilliseconds);

	for (ScreenElementList::iterator i = m_ScreenElements.begin();
			i != m_ScreenElements.end(); ++i) {
		(*i)->vOnUpdate(deltaMilliseconds);
	}
	/*
	m_pProcessManager->UpdateProcesses(deltaMilliseconds);

	m_Console.Update(deltaMilliseconds);

	// This section of code was added post-press. It runs through the screenlist
	// and calls VOnUpdate. Some screen elements need to update every frame, one
	// example of this is a 3D scene attached to the human view.
	//
	for (ScreenElementList::iterator i = m_ScreenElements.begin();
			i != m_ScreenElements.end(); ++i) {
		(*i)->VOnUpdate(deltaMilliseconds);
	}
	 */
}

void HumanView::describeYourself() {
	logger::info("HumanView describeYourself");
}

bool HumanView::vOnKeyCallback(GLFWwindow* window, int key, int scancode,
		int action, int mods) {
	stringstream ss;
	ss << "HumanView::onKeyCallback: key: " << key << "; scancode: " << scancode
			<< "; action: " << action << "; mods: " << mods;
	// logger::info(ss);

	if (m_KeyboardHandler) {
		m_KeyboardHandler->vOnKeyCallback(window, key, scancode, action, mods);
		return true;
	} else {
		return false;
	}
}

bool HumanView::vOnCharCallback(GLFWwindow* window, unsigned int codepoint) {
	stringstream ss;
	ss << "HumanView::onCharCallback: codepoint: " << codepoint;
	//logger::info(ss);

	if (m_KeyboardHandler) {
		m_KeyboardHandler->vOnCharCallback(window, codepoint);
		return true;
	} else {
		return false;
	}
}

bool HumanView::vOnCharmodsCallback(GLFWwindow* window, unsigned int codepoint,
		int mods) {
	stringstream ss;
	ss << "HumanView::onCharmodsCallback: codepoint: " << codepoint
			<< "; mods: " << mods;
	//logger::info(ss);

	if (m_KeyboardHandler) {
		m_KeyboardHandler->vOnCharmodsCallback(window, codepoint, mods);
		return true;
	} else {
		return false;
	}
}

bool HumanView::vOnCursorPositionCallback(GLFWwindow* window, double xpos,
		double ypos) {
	stringstream ss;
	ss << "HumanView::onCursorPositionCallback: xpos: " << xpos << "; ypos: "
			<< ypos;
	//logger::info(ss);

	if (m_PointerHandler) {
		m_PointerHandler->vOnCursorPositionCallback(window, xpos, ypos);
		return true;
	} else {
		return false;
	}
}

bool HumanView::vOnCursorEnterCallback(GLFWwindow* window, int entered) {
	stringstream ss;
	ss << "HumanView::onCursorEnterCallback: entered: " << entered;
	//logger::info(ss);

	if (m_PointerHandler) {
		m_PointerHandler->vOnCursorEnterCallback(window, entered);
		return true;
	} else {
		return false;
	}
}

bool HumanView::vOnMouseButtonCallback(GLFWwindow* window, int button,
		int action, int mods) {
	stringstream ss;
	ss << "HumanView::onMouseButtonCallback: button: " << button << "; action: "
			<< action << "; mods: " << mods;
	//logger::info(ss);

	if (m_PointerHandler) {
		m_PointerHandler->vOnMouseButtonCallback(window, button, action, mods);
		return true;
	} else {
		return false;
	}
}

bool HumanView::vOnScrollCallback(GLFWwindow* window, double xoffset,
		double yoffset) {
	stringstream ss;
	ss << "HumanView::onScrollCallback: xoffset: " << xoffset << "; yoffset: "
			<< yoffset;
	//logger::info(ss);

	if (m_PointerHandler) {
		m_PointerHandler->vOnScrollCallback(window, xoffset, yoffset);
		return true;
	} else {
		return false;
	}
}

void HumanView::tempVLoadGameDelegate() {
	shared_ptr<MovementController> movementController = make_shared<
			MovementController>();
	m_PointerHandler = movementController;
	m_KeyboardHandler = movementController;

}

/**
 * Renders text in the console
 */
void HumanView::vRenderText() {
}

void HumanView::vPushElement(shared_ptr<IScreenElement> pElement) {
	m_ScreenElements.push_front(pElement);
}

void HumanView::vRemoveElement(shared_ptr<IScreenElement> pElement) {
	m_ScreenElements.remove(pElement);
}


}
