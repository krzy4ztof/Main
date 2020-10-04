/*
 * MessageBox.cpp
 *
 *  Created on: 6 lip 2020
 *      Author: Krzysztof
 */

#include "QuitMessageBoxUI.h"
#include "../debugging/Logger.h"
#include "../resourceCache/ResourceCache.h"
#include "../graphics3d/FiguresRenderer.h"
#include "../graphics3d/ShaderResourceLoader.h"
#include "../gameInitialization/VideoSystemGLFW.h"
#include "../graphics3d/FreeTypeResourceLoader.h"
#include "../graphics3d/FreeTypeCharacter.h"
#include "../graphics3d/FreeTypeRenderer.h"
#include "../graphics3d/OpenGLRenderer.h"
#include "GameUIPane.h"
#include "../gameInitialization/GameMessages.h"

#include <glm/gtc/matrix_transform.hpp> // glm::ortho
#include <sstream>      // std::stringstream
#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h> // GLFWwindow
#include <string> // string

using std::stringstream;
using std::shared_ptr;
using std::make_shared;
using std::string;

namespace base_game {

QuitMessageBoxUI::QuitMessageBoxUI(shared_ptr<OpenGLRenderer> openGLRenderer,
		shared_ptr<GameMessages> gameMessages) :
		modal(true) {
	logger::info("Create QuitMessageBoxUI");
	this->openGLRenderer = openGLRenderer;
	this->gameMessages = gameMessages;
	gameUIDialog = make_shared<GameUIDialog>(openGLRenderer);
}

QuitMessageBoxUI::~QuitMessageBoxUI() {
	logger::info("Destroy QuitMessageBoxUI");
	gameUIDialog.reset();
	gameMessages.reset();
	openGLRenderer.reset();

	//vTerminate();
}

void QuitMessageBoxUI::setModal(bool modal) {
	this->modal = modal;
}

bool QuitMessageBoxUI::isModal() {
	return modal;
}

void QuitMessageBoxUI::init() {

	// offsetX = 11 + 0.5
	// offsetY = 16 + 0.5

	glm::mat4 projection = glm::ortho(0.0f,
			static_cast<GLfloat>(VideoSystemGLFW::WINDOW_WIDTH), 0.0f,
			static_cast<GLfloat>(VideoSystemGLFW::WINDOW_HEIGHT));

	float rem = 16.0f;

	shared_ptr<GameUIPane> gameUIPane = make_shared<GameUIPane>(openGLRenderer);
	gameUIPane->setProjection(projection);

	gameUIDialog->setProjection(projection);

	//float screenWidth = VideoSystemGLFW::WINDOW_WIDTH / rem;

	float dialogWidth = 42 * rem;
	float dialogHeight = 16 * rem;
	gameUIDialog->setSize(dialogWidth, dialogHeight);
	gameUIDialog->setPosition((11 + 0.5) * rem, (16 + 0.5) * rem); //setPosition(184, 264)

	float xPos = (VideoSystemGLFW::WINDOW_WIDTH - dialogWidth) / 2; // 176
	// float yPos = (VideoSystemGLFW::WINDOW_HEIGHT - dialogHeight) / 2; //192
	float yPos = (VideoSystemGLFW::WINDOW_HEIGHT - dialogHeight) / 3 * 2; //256


	gameUIDialog->setPosition(xPos, yPos);

	//openGLRenderer->freeTypeRenderer->activate(projection);

	//openGLRenderer->freeTypeRenderer->startRender();

	//glm::vec3 black = glm::vec3(0.0, 0.0f, 0.0f);
	glm::vec4 darkseagreen = glm::vec4(143.0f / 255.0f, 188.0f / 255.0f,
			143.0f / 255.0f, 1.0f);

	// #5f9ea0
	glm::vec4 cadetblue = glm::vec4(95.0f / 255.0f, 158.0f / 255.0f,
			160.0f / 255.0f, 1.0f);

	glm::vec4 lightblue = glm::vec4(173.0f / 255.0f, 216.0f / 255.0f,
			230.0f / 255.0f, 1.0f);

	gameUIDialog->setBackgroundColor(lightblue);
	gameUIDialog->setBorderWidth(0.5 * rem);
	gameUIDialog->setBorderColor(darkseagreen);

	string quitQuestionText = gameMessages->getText(
			"quit_msgbox_are_you_sure_to_quit");
	 shared_ptr<GameUILabel> gameUILabel = make_shared<GameUILabel>(
			openGLRenderer, quitQuestionText);
	// gameUILabel->setPosition(11 * rem, 10 * rem);
	// gameUILabel->setPosition(0, 10 * rem);
	gameUILabel->setPosition(0, 12 * rem);


	gameUILabel->setSize(dialogWidth, 0);
	gameUILabel->setScale(0.75f);
	gameUILabel->end();

	gameUIPane->addLabel(gameUILabel);
	gameUIDialog->addPane(gameUIPane);

	// button yes
	//openGLRenderer->freeTypeRenderer->renderText("Are you sure to quit?",
	//		(11 + 0.5 + 11) * rem, (16 + 0.5 + 10) * rem, 0.75f, black);

	string yesText = gameMessages->getText("quit_msgbox_yes");
	shared_ptr<GameUIButton> gameUIButtonYes = make_shared<GameUIButton>(
			openGLRenderer, yesText);
	gameUIButtonYes->setPosition(6 * rem, 3 * rem);
	gameUIButtonYes->setSize(12 * rem, 3 * rem);
	gameUIButtonYes->setColor(darkseagreen);
	gameUIButtonYes->setMouseOverColor(cadetblue);

	gameUIButtonYes->setLabelScale(0.5f);
	//gameUIButtonYes->initLabelOffset();
	//gameUIButtonYes->setLabelOffset(5 * rem, 1 * rem);

	gameUIButtonYes->setCallback(QuitMessageBoxUI::closeQuitMessageBoxYes, this);
	gameUIButtonYes->setCursorCallback(QuitMessageBoxUI::cursorOverButton,
			this);
	gameUIButtonYes->end();

	gameUIPane->addButton(gameUIButtonYes);

	string noText = gameMessages->getText("quit_msgbox_no");
	shared_ptr<GameUIButton> gameUIButtonNo = make_shared<GameUIButton>(
			openGLRenderer, noText);
	gameUIButtonNo->setPosition((6 + 12 + 6) * rem, 3 * rem);
	gameUIButtonNo->setSize(12 * rem, 3 * rem);
	gameUIButtonNo->setColor(darkseagreen);
	gameUIButtonNo->setMouseOverColor(cadetblue);
	gameUIButtonNo->setLabelScale(0.5f);

	gameUIButtonNo->setCursorCallback(QuitMessageBoxUI::cursorOverButton, this);
	gameUIButtonNo->setCallback(QuitMessageBoxUI::closeQuitMessageBoxNo, this);

	//gameUIButtonNo->initLabelOffset();
	//gameUIButtonNo->setLabelOffset(5 * rem, 1 * rem);
	gameUIButtonNo->end();

	gameUIPane->addButton(gameUIButtonNo);

	closeQuitMessageBoxNo(this);
}

void QuitMessageBoxUI::vTerminate() {

}

int QuitMessageBoxUI::vGetZOrder() const {
	return 99;
}

void QuitMessageBoxUI::vSetZOrder(int const zOrder) const {
}

void QuitMessageBoxUI::vOnRestore() {
	// TODO: implement
	stringstream ss;
	ss << "on Restore msgui";
	logger::info(ss);

	//initRenderer();
	//openGLRenderer->initRenderers();
//	activateRenderer();
}

void QuitMessageBoxUI::activateRenderer() {
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

void QuitMessageBoxUI::vOnRender(double fTime, float fElapsedTime) {
	gameUIDialog->onRender(fTime, fElapsedTime);
}

void QuitMessageBoxUI::vOnRender_222(double fTime, float fElapsedTime) {
// TODO: implement

	glm::mat4 projection = glm::ortho(0.0f,
			static_cast<GLfloat>(VideoSystemGLFW::WINDOW_WIDTH), 0.0f,
			static_cast<GLfloat>(VideoSystemGLFW::WINDOW_HEIGHT));

	float rem = 16.0f;
	// 3 rem = 3 * 0.5 font height
	// 1 rem = 0.5 font height

	// Message Box
	// width 42, height 14
	//rgb(143, 188, 143)
	glm::vec4 darkseagreen = glm::vec4(143.0f / 255.0f, 188.0f / 255.0f,
			143.0f / 255.0f, 1.0f);

	openGLRenderer->figuresRenderer->activate(projection);
//	figuresRenderer->renderRectangle(glm::vec2(11 * rem, 16 * rem),
//			glm::vec2((11 + 42) * rem, (16 + 16) * rem), darkseagreen);

	// top
	openGLRenderer->figuresRenderer->renderRectangle(
			glm::vec2(11 * rem, (16 + 16 - 0.5) * rem),
			glm::vec2((11 + 42) * rem, (16 + 16) * rem), darkseagreen);

	// bottom
	openGLRenderer->figuresRenderer->renderRectangle(
			glm::vec2(11 * rem, 16 * rem),
			glm::vec2((11 + 42) * rem, (16 + 0.5) * rem), darkseagreen);

	// left
	openGLRenderer->figuresRenderer->renderRectangle(
			glm::vec2(11 * rem, (16 + 0.5) * rem),
			glm::vec2((11 + 0.5) * rem, (16 + 16 - 0.5) * rem), darkseagreen);

	// right
	openGLRenderer->figuresRenderer->renderRectangle(
			glm::vec2((11 + 42) * rem, (16 + 0.5) * rem),
			glm::vec2((11 + 42 - 0.5) * rem, (16 + 16 - 0.5) * rem),
			darkseagreen);

	glm::vec4 lightblue = glm::vec4(173.0f / 255.0f, 216.0f / 255.0f,
			230.0f / 255.0f, 1.0f);

	// body
	openGLRenderer->figuresRenderer->renderRectangle(
			glm::vec2((11 + 0.5) * rem, (16 + 0.5) * rem),
			glm::vec2((11 + 42 - 0.5) * rem, (16 + 16 - 0.5) * rem), lightblue);

	// button yes
	openGLRenderer->figuresRenderer->renderRectangle(
			glm::vec2((11 + 0.5 + 6) * rem, (16 + 0.5 + 3) * rem),
			glm::vec2((11 + 0.5 + 6 + 12) * rem, (16 + 0.5 + 3 + 3) * rem),
			darkseagreen);

	// button no
	openGLRenderer->figuresRenderer->renderRectangle(
			glm::vec2((11 + 0.5 + 6 + 12 + 6) * rem, (16 + 0.5 + 3) * rem),
			glm::vec2((11 + 0.5 + 6 + 12 + 6 + 12) * rem,
					(16 + 0.5 + 3 + 3) * rem), darkseagreen);

	openGLRenderer->figuresRenderer->deactivate();

	//gameUIPane->renderLabels(fTime, fElapsedTime);

	openGLRenderer->freeTypeRenderer->activate(projection);

	openGLRenderer->freeTypeRenderer->startRender();

	glm::vec3 black = glm::vec3(0.0, 0.0f, 0.0f);

	// button yes
	openGLRenderer->freeTypeRenderer->renderText("Are you sure to quit?",
			(11 + 0.5 + 11) * rem, (16 + 0.5 + 10) * rem, 0.75f, black);

	// button yes
	openGLRenderer->freeTypeRenderer->renderText("Yes",
			(11 + 0.5 + 6 + 5) * rem, (16 + 0.5 + 3 + 1) * rem, 0.5f, black);

	// button no
	openGLRenderer->freeTypeRenderer->renderText("No",
			(11 + 0.5 + 6 + 12 + 6 + 5) * rem, (16 + 0.5 + 3 + 1) * rem, 0.5f,
			black);

	openGLRenderer->freeTypeRenderer->deactivate();

}

bool QuitMessageBoxUI::vOnKeyCallback(GLFWwindow *window, int key, int scancode,
		int action, int mods) {
	stringstream ss;
	ss << "QuitMessageBoxUI::vOnKeyCallback: key: " << key << "; scancode: "
			<< scancode << "; action:" << action << "; mods:" << mods;
	logger::info(ss);

//	if (base_game::g_pApp != nullptr) {

	if (action == GLFW_RELEASE) {
		if (key == GLFW_KEY_Y) {
			tempCloseQuitMessageBox();
			return true;
		} else if (key == GLFW_KEY_N) {
			tempCloseQuitMessageBox();
			return true;
		}
	}
	//}

	return false;
}

void QuitMessageBoxUI::closeQuitMessageBoxYes(void *voidMessageBoxUI) {
	QuitMessageBoxUI *messageBoxUI = (QuitMessageBoxUI*) voidMessageBoxUI;
	messageBoxUI->tempCloseQuitMessageBox();
}

void QuitMessageBoxUI::closeQuitMessageBoxNo(void *voidMessageBoxUI) {
	QuitMessageBoxUI *messageBoxUI = (QuitMessageBoxUI*) voidMessageBoxUI;
	messageBoxUI->tempCloseQuitMessageBox();
}

void QuitMessageBoxUI::tempCloseQuitMessageBox() {
	//vRemoveElement(m_MessageBox);
	this->vSetVisible(false);
	stringstream ss;
	ss << "QuitMessageBoxUI::tempCloseQuitMessageBox";
	logger::info(ss);
	//m_MessageBox.reset();
}

void QuitMessageBoxUI::cursorOverButton(void *voidMessageBoxUI,
		boolean cursorOverButton) {

	QuitMessageBoxUI *messageBoxUI = (QuitMessageBoxUI*) voidMessageBoxUI;
	messageBoxUI->tempCursorOverButton(cursorOverButton);
}

void QuitMessageBoxUI::tempCursorOverButton(boolean cursorOverButton) {
	stringstream ss;
	ss << "QuitMessageBoxUI::tempCursorOverButton" << cursorOverButton;
	logger::info(ss);
	if (cursorOverButton) {
		this->openGLRenderer->cursorRenderer->activateHandCursor();
	} else {
		this->openGLRenderer->cursorRenderer->activateArrowCursor();
	}
}

bool QuitMessageBoxUI::vOnCharCallback(GLFWwindow *window, unsigned int codepoint) {
	stringstream ss;
	ss << "QuitMessageBoxUI::vOnCharCallback: codepoint: " << codepoint;
	//logger::info(ss);
	return modal;
}

bool QuitMessageBoxUI::vOnCharmodsCallback(GLFWwindow *window,
		unsigned int codepoint, int mods) {
	stringstream ss;
	ss << "MessageBoxUI::vOnCharmodsCallback: codepoint: " << codepoint
			<< "; mods: " << mods;
	//logger::info(ss);
	return modal;
}

bool QuitMessageBoxUI::vOnCursorPositionCallback(GLFWwindow *window, double xpos,
		double ypos) {
	stringstream ss;
	ss << "QuitMessageBoxUI::onCursorPositionCallback: xpos: " << xpos
			<< "; ypos: "
			<< ypos;
	//logger::info(ss);

	if (gameUIDialog->vOnCursorPositionCallback(window, xpos, ypos)) {
		return true;
	}

	return modal;
}

bool QuitMessageBoxUI::vOnCursorEnterCallback(GLFWwindow *window, int entered) {
	stringstream ss;
	ss << "QuitMessageBoxUI::onCursorEnterCallback: entered: " << entered;
	return modal;
}

bool QuitMessageBoxUI::vOnMouseButtonCallback(GLFWwindow *window, int button,
		int action, int mods) {
	stringstream ss;
	ss << "QuitMessageBoxUI::onMouseButtonCallback: button: " << button
			<< "; action: "
			<< action << "; mods: " << mods;
	logger::info(ss);

	if (gameUIDialog->vOnMouseButtonCallback(window, button, action, mods)) {
		return true;
	}

	return modal;
}

bool QuitMessageBoxUI::vOnScrollCallback(GLFWwindow *window, double xoffset,
		double yoffset) {
	stringstream ss;
	ss << "QuitMessageBoxUI::onScrollCallback: xoffset: " << xoffset
			<< "; yoffset: "
			<< yoffset;
	return modal;
}




} /* namespace base_game */
