/*
 * MainMenuUI.h
 *
 *  Created on: 22 sty 2020
 *      Author: Krzysztof
 */

#ifndef USERINTERFACE_MAINMENUUI_H_
#define USERINTERFACE_MAINMENUUI_H_

#include "../../../BaseGame/source/userInterface/BaseUI.h"
#include "../../../BaseGame/source/resourceCache/ResourceCache.h"
#include "../../../BaseGame/source/graphics3d/FiguresRenderer.h"
#include "../../../BaseGame/source/graphics3d/ShaderResourceLoader.h"
#include "../../../BaseGame/source/graphics3d/FreeTypeRenderer.h"
#include "../../../BaseGame/source/graphics3d/TextureResourceLoader.h"
#include "../../../BaseGame/source/graphics3d/TextureRenderer.h"
#include "../../../BaseGame/source/graphics3d/OpenGLRenderer.h"
#include "../../../BaseGame/source/userInterface/GameUIPane.h"
#include "../../../BaseGame/source/userInterface/QuitMessageBoxUI.h"
#include "../../../BaseGame/source/gameInitialization/GameMessages.h"

#include <memory> // shared_ptr
#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h> // GLFWwindow

namespace watermill_base {

// TeapotWarsView.cpp -> MainMenuUI
class MainMenuUI: public base_game::BaseUI {
public:
//	MainMenuUI(std::shared_ptr<base_game::ResourceCache> resourceCache,
//			std::shared_ptr<base_game::OpenGLRenderer> openGLRenderer);
	MainMenuUI(std::shared_ptr<base_game::OpenGLRenderer> openGLRenderer,
			std::shared_ptr<base_game::GameMessages> gameMessages);
	virtual ~MainMenuUI();

	void init();
	virtual void vOnRestore();
	virtual void vOnRender(double fTime, float fElapsedTime);
	//virtual void vOnRender_222(double fTime, float fElapsedTime);
	virtual int vGetZOrder() const;
	virtual void vSetZOrder(int const zOrder) const;
	virtual void vTerminate();
	void preRender();

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

	void tempOpenQuitMessageBox();
//	void tempCloseQuitMessageBox();
	void tempCursorOverButton(boolean cursorOverButton);


	void tempSetQuitMessageBox(
			std::shared_ptr<base_game::QuitMessageBoxUI> messageBoxUI);

	static void openQuitMessageBox(void *mainMenuUI);

	static void cursorOverButton(void *mainMenuUI, boolean cursorOverButton);


protected:
	void initRenderer();
	void activateRenderer();
//	std::shared_ptr<base_game::SpriteSheet> spriteSheetLogo;
	std::shared_ptr<base_game::OpenGLRenderer> openGLRenderer;
	std::shared_ptr<base_game::GameUIPane> gameUIPane;
	std::shared_ptr<base_game::GameMessages> gameMessages;
		

	std::shared_ptr<base_game::QuitMessageBoxUI> tempQuitMessageBox;

	/*
	std::shared_ptr<base_game::ResourceCache> shrdPtrResourceCache;
	std::shared_ptr<base_game::FiguresRenderer> figuresRenderer;
	std::shared_ptr<base_game::FreeTypeRenderer> freeTypeRenderer;

	std::shared_ptr<base_game::PngTextureLoader> pngTextureLoader;
	std::shared_ptr<base_game::PngRenderer> pngRenderer;

	std::shared_ptr<base_game::ShaderCompiler> shaderCompiler;
	 */
};

/*
 * class MainMenuUI : public BaseUI
 {
 protected:
 CDXUTDialog m_SampleUI;					// dialog for sample specific controls
 void Set();
 bool m_bCreatingGame;
 int m_NumAIs;
 int m_NumPlayers;
 std::vector<std::wstring> m_Levels;
 int m_LevelIndex;
 std::string m_HostName;
 std::string m_HostListenPort;
 std::string m_ClientAttachPort;

 public:
 MainMenuUI();
 virtual ~MainMenuUI();

 // IScreenElement Implementation
 virtual HRESULT VOnRestore();
 virtual HRESULT VOnRender(double fTime, float fElapsedTime);
 virtual int VGetZOrder() const { return 1; }
 virtual void VSetZOrder(int const zOrder) { }

 virtual LRESULT CALLBACK VOnMsgProc( AppMsg msg );
 static void CALLBACK OnGUIEvent( UINT nEvent, int nControlID, CDXUTControl* pControl, void *pUserContext );
 void CALLBACK _OnGUIEvent( UINT nEvent, int nControlID, CDXUTControl* pControl, void *pUserContext );
 };
 */

} /* namespace watermill_base */

#endif /* USERINTERFACE_MAINMENUUI_H_ */
