/*
 * IScreenElement.h
 *
 *  Created on: 20 sty 2020
 *      Author: Krzysztof
 */

#ifndef USERINTERFACE_ISCREENELEMENT_H_
#define USERINTERFACE_ISCREENELEMENT_H_

#include <memory> // shared_ptr
#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h> // GLFWwindow

namespace base_game {

class IScreenElement {
public:
	IScreenElement();
	virtual ~IScreenElement();

	virtual void vOnRestore() = 0;
	virtual void vOnRender(double fTime, float fElapsedTime) = 0;
	virtual void vOnUpdate(int deltaMilliseconds) = 0;

	virtual int vGetZOrder() const = 0;
	virtual void vSetZOrder(int const zOrder) const = 0;


	virtual bool vIsVisible() const = 0;
	virtual void vSetVisible(bool visible) = 0;
	virtual void vTerminate()=0;

	virtual bool vOnKeyCallback(GLFWwindow *window, int key, int scancode,
			int action, int mods) = 0;
	virtual bool vOnCharCallback(GLFWwindow *window,
			unsigned int codepoint) = 0;
	virtual bool vOnCharmodsCallback(GLFWwindow *window, unsigned int codepoint,
			int mods) = 0;
	//virtual LRESULT CALLBACK VOnMsgProc( AppMsg msg )=0;
	virtual bool vOnCursorPositionCallback(GLFWwindow *window, double xpos,
			double ypos) = 0;
	virtual bool vOnCursorEnterCallback(GLFWwindow *window, int entered) = 0;
	virtual bool vOnMouseButtonCallback(GLFWwindow *window, int button,
			int action, int mods) = 0;
	virtual bool vOnScrollCallback(GLFWwindow *window, double xoffset,
			double yoffset) = 0;

	virtual bool const operator <(IScreenElement const &other);

};

//namespace iscreen_element {
//bool compareByZOrder(const std::shared_ptr<IScreenElement> &first,
//		const std::shared_ptr<IScreenElement> &second);

//}

/*
 * class IScreenElement
 {
 public:
 virtual HRESULT VOnRestore() = 0;
 virtual HRESULT VOnLostDevice() = 0;
 virtual HRESULT VOnRender(double fTime, float fElapsedTime) = 0;
 virtual void VOnUpdate(int deltaMilliseconds) = 0;

 virtual int VGetZOrder() const = 0;
 virtual void VSetZOrder(int const zOrder) = 0;
 virtual bool VIsVisible() const = 0;
 virtual void VSetVisible(bool visible) = 0;

 virtual LRESULT CALLBACK VOnMsgProc( AppMsg msg )=0;

 virtual ~IScreenElement() { };
 virtual bool const operator <(IScreenElement const &other) { return VGetZOrder() < other.VGetZOrder(); }
 };
 */

} /* namespace base_game */

#endif /* USERINTERFACE_ISCREENELEMENT_H_ */
