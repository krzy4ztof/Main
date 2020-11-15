/*
 * MainMenuUI.cpp
 *
 *  Created on: 22 sty 2020
 *      Author: Krzysztof
 */

#include "MainMenuUI.h"
#include "../../../BaseGame/source/debugging/Logger.h"
#include "../../../BaseGame/source/resourceCache/ResourceCache.h"
#include "../../../BaseGame/source/graphics3d/FiguresRenderer.h"
#include "../../../BaseGame/source/graphics3d/ShaderResourceLoader.h"
#include "../../../BaseGame/source/gameInitialization/VideoSystemGLFW.h"
#include "../../../BaseGame/source/graphics3d/FreeTypeResourceLoader.h"
#include "../../../BaseGame/source/graphics3d/FreeTypeCharacter.h"
#include "../../../BaseGame/source/graphics3d/FreeTypeRenderer.h"
#include "../../../BaseGame/source/graphics3d/TextureResourceLoader.h"
#include "../../../BaseGame/source/graphics3d/TextureRenderer.h"
#include "../../../BaseGame/source/graphics3d/OpenGLRenderer.h"
#include "../../../BaseGame/source/userInterface/GameUIPane.h"
#include "../../../BaseGame/source/userInterface/GameUILabel.h"
#include "../../../BaseGame/source/userInterface/GameUIButton.h"
#include "../../../BaseGame/source/userInterface/GameUIPngImage.h"
#include "../../../BaseGame/source/userInterface/QuitMessageBoxUI.h"
#include "../../../BaseGame/source/gameInitialization/GameMessages.h"

#include <glm/gtc/matrix_transform.hpp> // glm::ortho
#include <sstream>      // std::stringstream
#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h> // GLFWwindow
#include <string> // string


namespace logger = base_game::logger;

using base_game::FiguresRenderer;
using base_game::ShaderResourceLoader;
using base_game::VideoSystemGLFW;
using base_game::ResourceCache;
using base_game::ShaderCompiler;
using base_game::FreeTypeRenderer;
using base_game::FreeTypeLoader;
using base_game::FreeTypeCharacter;

using base_game::SpriteSheet;
using base_game::PngTextureLoader;
using base_game::PngRenderer;
using base_game::OpenGLRenderer;
using base_game::GameUIPane;
using base_game::GameUILabel;
using base_game::GameUIButton;
using base_game::GameUIPngImage;
using base_game::QuitMessageBoxUI;
using base_game::GameMessages;

using std::stringstream;
using std::shared_ptr;
using std::make_shared;
using std::string;

namespace watermill_base {

MainMenuUI::MainMenuUI(shared_ptr<OpenGLRenderer> openGLRenderer,
		shared_ptr<GameMessages> gameMessages) {
	logger::info("Create MainMenuUI");
	this->openGLRenderer = openGLRenderer;
	this->gameMessages = gameMessages;
//	spriteSheetLogo = make_shared<SpriteSheet>();
	gameUIPane = make_shared<GameUIPane>(openGLRenderer);
}

/*
MainMenuUI::MainMenuUI(shared_ptr<ResourceCache> resourceCache,
		std::shared_ptr<base_game::OpenGLRenderer> openGLRenderer) {
	logger::info("Create MainMenuUI");

	this->shrdPtrResourceCache = resourceCache;
	figuresRenderer = make_shared<FiguresRenderer>();
	freeTypeRenderer = make_shared<FreeTypeRenderer>();

	spriteSheetLogo = make_shared<SpriteSheet>();
	pngTextureLoader = make_shared<PngTextureLoader>(
			this->shrdPtrResourceCache);
	pngRenderer = make_shared<PngRenderer>();

	shaderCompiler = make_shared<ShaderCompiler>(this->shrdPtrResourceCache);
	// create window width=1024px (64rem), height=640px (40rem)

	// image 384px width (24rem), height 384px (24rem)
	// image left, right margin 302+16px (20rem), top 16+16px (2rem), bottom 226+16 (14rem)

	// title width 384px (24rem), height 48px (3rem)
	// image left, right 320px (20rem), bottom 128px (8rem), top [from image] 16+32px (3rem),
	// top [from border] 464px (2+24+3=29rem)

	// buttons width=192px (12rem), height=48px (3rem)
	// buttons left margin  96px, between 128px, right margin 96px, bottom 48px, top 302px

}
 */

MainMenuUI::~MainMenuUI() {
	logger::info("Destroy MainMenuUI");
//	vTerminate();
	gameUIPane.reset();
//	spriteSheetLogo.reset();
	gameMessages.reset();
	openGLRenderer.reset();

	tempQuitMessageBox.reset();
}

void MainMenuUI::init() {
	// Watermill Angular 96px =12x8 -> 2.0f
	// Instructions Angular 24px=3x8 -> 0.5f
	// Are you sure to quit? Angular 32px=4*8 -> 0.75f

	glm::mat4 projection = glm::ortho(0.0f,
			static_cast<GLfloat>(VideoSystemGLFW::WINDOW_WIDTH), 0.0f,
			static_cast<GLfloat>(VideoSystemGLFW::WINDOW_HEIGHT));
	gameUIPane->setProjection(projection);

	float rem = 16.0f;


	shared_ptr<GameUIPngImage> gameUIPngImage = make_shared<GameUIPngImage>(
			openGLRenderer, "intro_watermill.png");
	gameUIPngImage->setPosition(20 * rem, 14 * rem);
	gameUIPngImage->setSize(24 * rem, 24 * rem);

	gameUIPane->addPngImage(gameUIPngImage);


	string watermillText = gameMessages->getText("main_menu_watermill");
	//watermillText = "W";
	shared_ptr<GameUILabel> gameUILabel = make_shared<GameUILabel>(
			openGLRenderer, watermillText);
	//gameUILabel->setPosition(20 * rem, 8 * rem);

	//gameUILabel->setPosition(0, 8 * rem);
	gameUILabel->setPosition(0, 9 * rem);

	// gameUILabel->setSize(24 * rem, 3 * rem);

	gameUILabel->setSize(VideoSystemGLFW::WINDOW_WIDTH, 3 * rem);

	// gameUILabel->setScale(2.0f);
	gameUILabel->setScale(1.5f);

	gameUILabel->end();

	gameUIPane->addLabel(gameUILabel);

	glm::vec4 darkseagreen = glm::vec4(143.0f / 255.0f, 188.0f / 255.0f,
			143.0f / 255.0f, 1.0f);

	glm::vec4 cadetblue = glm::vec4(95.0f / 255.0f, 158.0f / 255.0f,
			160.0f / 255.0f, 1.0f);

	string startText = gameMessages->getText("main_menu_start");
	//startText = "sss";
	//startText = gameMessages->getText("pl_chars_pl");
	// startText = gameMessages->getText("pl_chars_a");

	shared_ptr<GameUIButton> gameUIButtonStart = make_shared<GameUIButton>(
			openGLRenderer, startText);
	gameUIButtonStart->setPosition(6 * rem, 3 * rem);
	gameUIButtonStart->setSize(12 * rem, 3 * rem);
	//gameUIButtonStart->setSize(12 * rem, 18);


	gameUIButtonStart->setColor(darkseagreen);
	gameUIButtonStart->setMouseOverColor(cadetblue);

	gameUIButtonStart->setLabelScale(0.5f);
	//gameUIButtonStart->initLabelOffset();
	gameUIButtonStart->setCursorCallback(MainMenuUI::cursorOverButton, this);

	gameUIButtonStart->end();
//	gameUIButtonStart->setLabelOffset(4 * rem, 1 * rem);
	gameUIPane->addButton(gameUIButtonStart);

	string quitText = gameMessages->getText("main_menu_quit");
	//quitText = "AAA";
	//quitText = " ";

	shared_ptr<GameUIButton> gameUIButtonQuit = make_shared<GameUIButton>(
			openGLRenderer, quitText);
	gameUIButtonQuit->setPosition((6 + 12 + 8) * rem, 3 * rem);
	gameUIButtonQuit->setSize(12 * rem, 3 * rem);
	//gameUIButtonQuit->setSize(12 * rem, 18);

	gameUIButtonQuit->setColor(darkseagreen);
	gameUIButtonQuit->setMouseOverColor(cadetblue);

	gameUIButtonQuit->setLabelScale(0.5f);
	//gameUIButtonQuit->initLabelOffset();
//	gameUIButtonQuit->setLabelOffset(4 * rem, 1 * rem);
	gameUIButtonQuit->setCallback(MainMenuUI::openQuitMessageBox, this);
	gameUIButtonQuit->setCursorCallback(MainMenuUI::cursorOverButton, this);
	gameUIButtonQuit->end();

	gameUIPane->addButton(gameUIButtonQuit);

	string instructionsText = gameMessages->getText("main_menu_instructions");
	//instructionsText = "yyy";

	shared_ptr<GameUIButton> gameUIButtonInstructions =
			make_shared<GameUIButton>(openGLRenderer, instructionsText);
	gameUIButtonInstructions->setPosition((6 + 12 + 8 + 12 + 8) * rem, 3 * rem);
	gameUIButtonInstructions->setSize(12 * rem, 3 * rem);
	//gameUIButtonInstructions->setSize(12 * rem, 18);

	gameUIButtonInstructions->setColor(darkseagreen);
	gameUIButtonInstructions->setMouseOverColor(cadetblue);

	gameUIButtonInstructions->setLabelScale(0.5f);
	//gameUIButtonInstructions->setLabelOffset(2 * rem, 1 * rem);
	//gameUIButtonInstructions->initLabelOffset();
	gameUIButtonInstructions->setCursorCallback(MainMenuUI::cursorOverButton,
			this);

	gameUIButtonInstructions->end();

	gameUIPane->addButton(gameUIButtonInstructions);
}

void MainMenuUI::vTerminate() {
}

int MainMenuUI::vGetZOrder() const {
	return 1;
}

void MainMenuUI::vSetZOrder(int const zOrder) const {
}

void MainMenuUI::vOnRestore() {
	// TODO: implement
	initRenderer();
//	activateRenderer();
}

void MainMenuUI::initRenderer() {
//	openGLRenderer->pngTextureLoader->init("intro_watermill.png",
//			spriteSheetLogo);

}

/*
void MainMenuUI::initRenderer() {
	stringstream ss;

	//ShaderCompiler shaderCompiler(this->shrdPtrResourceCache);
	GLuint programID = shaderCompiler->loadShaders("figures_renderer");
	figuresRenderer->init(programID);

	// vActivate();

	FreeTypeLoader freeTypeLoader(this->shrdPtrResourceCache);
	std::shared_ptr<std::map<GLushort, FreeTypeCharacter>> characters =
			freeTypeLoader.initFreetype();
	freeTypeLoader.debugCharacters();

	GLuint freeTypeProgramID = shaderCompiler->loadShaders(
			"fonts_renderer");

	freeTypeRenderer->init(freeTypeProgramID, characters);
	freeTypeRenderer->debugCharacters();

	// --------
	pngTextureLoader->init("intro_watermill.png",
			spriteSheetLogo);

	GLuint pngProgramID = shaderCompiler->loadShaders("texture_renderer");
	pngRenderer->init(pngProgramID);
}
 */

void MainMenuUI::activateRenderer() {
	//HumanView::vActivate();

	// Dark background
	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	// rgb(173, 216, 230)


	glClearColor(173.0f / 255.0f, 216.0f / 255.0f, 230.0f / 255.0f, 0.0f); // lightblue

	//const GLfloat color[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	const GLfloat color[] = { 173.0f / 255.0f, 216.0f / 255.0f, 230.0f / 255.0f,
			1.0f }; // lightblue
		
	glClearBufferfv(GL_COLOR, 0, color);



}

/*
void MainMenuUI::deactivateRenderer() {
	figuresRenderer->deactivate();
	freeTypeRenderer->deactivate();
}
 */

void MainMenuUI::preRender() {

	//rgb(173, 216, 230)
	const GLfloat lightblue[] = { 173.0f / 255.0f, 216.0f / 255.0f, 230.0f
			/ 255.0f, 1.0f };
	//glm::vec4 lightblue = glm::vec4(173.0f / 255.0f, 216.0f / 255.0f,
	//			230.0f / 255.0f, 1.0f);

	//glm::vec4 lightblue0 = glm::vec4(173.0f / 255.0f, 216.0f / 255.0f,
	//		230.0f / 255.0f, 0.0f);
//	const GLfloat lightblue0[] = { 173.0f / 255.0f, 216.0f / 255.0f, 230.0f
//			/ 255.0f, 0.0f };


	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // black

	//const GLfloat color[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//	const GLfloat color[] = { 173.0f / 255.0f, 216.0f / 255.0f, 230.0f / 255.0f,
//			1.0f }; // lightblue

	glClearBufferfv(GL_COLOR, 0, lightblue);

}

void MainMenuUI::vOnRender(double fTime, float fElapsedTime) {
	preRender();

	gameUIPane->onRender(fTime, fElapsedTime);
}

bool MainMenuUI::vOnKeyCallback(GLFWwindow *window, int key, int scancode,
		int action, int mods) {
	stringstream ss;
	ss << "MainMenuUI::vOnKeyCallback: key: " << key << "; scancode: "
			<< scancode << "; action:" << action << "; mods:" << mods;
	logger::info(ss);

//	if (base_game::g_pApp != nullptr) {
	if (action == GLFW_RELEASE && key == GLFW_KEY_Q) {
		tempOpenQuitMessageBox();
		return true;
	}
	/*
	 else if (key == GLFW_KEY_Y) {
			tempCloseQuitMessageBox();
			return true;
		} else if (key == GLFW_KEY_N) {
			tempCloseQuitMessageBox();
			return true;
		}
	 */
//	}

	return false;
}

void MainMenuUI::tempSetQuitMessageBox(
		shared_ptr<QuitMessageBoxUI> messageBoxUI) {
	this->tempQuitMessageBox = messageBoxUI;
}

void MainMenuUI::openQuitMessageBox(void *voidMainMenuUI) {
	MainMenuUI *mainMenuUI = (MainMenuUI*) voidMainMenuUI;
	mainMenuUI->tempOpenQuitMessageBox();
}

void MainMenuUI::cursorOverButton(void *voidMainMenuUI,
		boolean cursorOverButton) {

	MainMenuUI *mainMenuUI = (MainMenuUI*) voidMainMenuUI;
	mainMenuUI->tempCursorOverButton(cursorOverButton);
}

void MainMenuUI::tempOpenQuitMessageBox() {
	//vPushElement(m_MessageBox);
	//tempQuitMessageBox->vSetVisible(true);
	boolean result = tempQuitMessageBox->askIfShouldQuit();

	stringstream ss;
	ss << "AskIfShouldQuit: " << result;
	logger::info(ss);

	logger::info("");
}

void MainMenuUI::tempCursorOverButton(boolean cursorOverButton) {
	stringstream ss;
	ss << "MainMenuUI::tempCursorOverButton" << cursorOverButton;
	logger::info(ss);

	if (cursorOverButton) {
		this->openGLRenderer->cursorRenderer->activateHandCursor();
	} else {
		this->openGLRenderer->cursorRenderer->activateArrowCursor();
	}
	//openGLRenderer->videoSystemGLFW->
}


bool MainMenuUI::vOnCharCallback(GLFWwindow *window, unsigned int codepoint) {
	stringstream ss;
	ss << "MainMenuUI::vOnCharCallback: codepoint: " << codepoint;
	//logger::info(ss);
	return false;
}

bool MainMenuUI::vOnCharmodsCallback(GLFWwindow *window, unsigned int codepoint,
		int mods) {
	stringstream ss;
	ss << "MainMenuUI::vOnCharmodsCallback: codepoint: " << codepoint
			<< "; mods: " << mods;
	//logger::info(ss);
	return false;
}

bool MainMenuUI::vOnCursorPositionCallback(GLFWwindow *window, double xpos,
		double ypos) {
	stringstream ss;
	ss << "MainMenuUI::onCursorPositionCallback: xpos: " << xpos << "; ypos: "
			<< ypos;
	//logger::info(ss);

	if (gameUIPane->vOnCursorPositionCallback(window, xpos, ypos)) {
		return true;
	}

	return false;
}

bool MainMenuUI::vOnCursorEnterCallback(GLFWwindow *window, int entered) {
	stringstream ss;
	ss << "MainMenuUI::onCursorEnterCallback: entered: " << entered;
	return false;
}

bool MainMenuUI::vOnMouseButtonCallback(GLFWwindow *window, int button,
		int action, int mods) {
	stringstream ss;
	ss << "MainMenuUI::onMouseButtonCallback: button: " << button
			<< "; action: "
			<< action << "; mods: " << mods;
	logger::info(ss);
	if (gameUIPane->vOnMouseButtonCallback(window, button, action, mods)) {
		return true;
	}

	return false;
}

bool MainMenuUI::vOnScrollCallback(GLFWwindow *window, double xoffset,
		double yoffset) {
	stringstream ss;
	ss << "MainMenuUI::onScrollCallback: xoffset: " << xoffset << "; yoffset: "
			<< yoffset;
	return false;
}

} /* namespace watermill_base */
