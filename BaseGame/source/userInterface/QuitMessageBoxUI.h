/*
 * MessageBox.h
 *
 *  Created on: 6 lip 2020
 *      Author: Krzysztof
 */

#ifndef USERINTERFACE_QUITMESSAGEBOXUI_H_
#define USERINTERFACE_QUITMESSAGEBOXUI_H_

#include "BaseUI.h"
#include "../resourceCache/ResourceCache.h"
#include "../graphics3d/FiguresRenderer.h"
#include "../graphics3d/ShaderResourceLoader.h"
#include "../graphics3d/FreeTypeRenderer.h"
#include "../graphics3d/OpenGLRenderer.h"
#include "GameUIDialog.h"
#include "../gameInitialization/GameMessages.h"

#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h> // GLFWwindow


namespace base_game {

class QuitMessageBoxUI: public BaseUI {
public:
	//MessageBoxUI(std::shared_ptr<base_game::ResourceCache> resourceCache,
	//		std::shared_ptr<base_game::OpenGLRenderer> openGLRenderer);
	QuitMessageBoxUI(std::shared_ptr<OpenGLRenderer> openGLRenderer,
			std::shared_ptr<GameMessages> gameMessages);
	virtual ~QuitMessageBoxUI();

	void init();
	virtual void vOnRestore();
	virtual void vOnRender(double fTime, float fElapsedTime);
	virtual void vOnRender_222(double fTime, float fElapsedTime);
	virtual int vGetZOrder() const;
	virtual void vSetZOrder(int const zOrder) const;
	virtual void vTerminate();

	/*
	void tempSetFiguresRenderer(
			std::shared_ptr<base_game::FiguresRenderer> figuresRenderer);
	void tempSetFreeTypeRenderer(
			std::shared_ptr<base_game::FreeTypeRenderer> freeTypeRenderer);
	 */

	virtual bool vOnKeyCallback(GLFWwindow *window, int key, int scancode,
			int action, int mods);
	virtual bool vOnCharCallback(GLFWwindow *window, unsigned int codepoint);
	virtual bool vOnCharmodsCallback(GLFWwindow *window, unsigned int codepoint,
			int mods);

	virtual bool vOnCursorPositionCallback(GLFWwindow *window, double xpos,
			double ypos);
	virtual bool vOnCursorEnterCallback(GLFWwindow *window, int entered);
	virtual bool vOnMouseButtonCallback(GLFWwindow *window, int button,
			int action, int mods);
	virtual bool vOnScrollCallback(GLFWwindow *window, double xoffset,
			double yoffset);
	

//	void tempOpenQuitMessageBox();
	void tempCloseQuitMessageBox();
	void tempCursorOverButton(boolean cursorOverButton);

	static void closeQuitMessageBoxYes(void *messageBoxUI);
	static void closeQuitMessageBoxNo(void *messageBoxUI);

	static void cursorOverButton(void *messageBoxUI, boolean cursorOverButton);


	void setModal(bool modal);
	bool isModal();

protected:
	//void initRenderer();
	void activateRenderer();
	std::shared_ptr<OpenGLRenderer> openGLRenderer;
	std::shared_ptr<GameMessages> gameMessages;
	std::shared_ptr<GameUIDialog> gameUIDialog;
	bool modal;

//	void deactivateRenderer();

	/*
	std::shared_ptr<base_game::ResourceCache> shrdPtrResourceCache;
	std::shared_ptr<base_game::FiguresRenderer> figuresRenderer;
	std::shared_ptr<base_game::FreeTypeRenderer> freeTypeRenderer;
	std::shared_ptr<base_game::ShaderCompiler> shaderCompiler;
	 */
	
};

} /* namespace base_game */

#endif /* USERINTERFACE_QUITMESSAGEBOXUI_H_ */
