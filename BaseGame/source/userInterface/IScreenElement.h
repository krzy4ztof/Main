/*
 * IScreenElement.h
 *
 *  Created on: 20 sty 2020
 *      Author: Krzysztof
 */

#ifndef USERINTERFACE_ISCREENELEMENT_H_
#define USERINTERFACE_ISCREENELEMENT_H_

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

};

namespace iscreen_element {
bool compareByZOrder(const IScreenElement &first, const IScreenElement &second);
}

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
