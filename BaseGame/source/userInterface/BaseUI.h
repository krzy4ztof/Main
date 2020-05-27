/*
 * BaseUI.h
 *
 *  Created on: 22 sty 2020
 *      Author: Krzysztof
 */

#ifndef USERINTERFACE_BASEUI_H_
#define USERINTERFACE_BASEUI_H_

#include "IScreenElement.h"

namespace base_game {

class BaseUI: public IScreenElement {
public:
	BaseUI();
	virtual ~BaseUI();

	virtual void vOnUpdate(int);
	virtual bool vIsVisible() const;
	virtual void vSetVisible(bool visible);
protected:
	bool m_bIsVisible;
};

/*
 * class BaseUI : public IScreenElement
 {
 protected:
 int					m_PosX, m_PosY;
 int					m_Width, m_Height;
 optional<int>		m_Result;
 bool				m_bIsVisible;
 public:
 BaseUI() { m_bIsVisible = true; m_PosX = m_PosY = 0; m_Width = 100; m_Height = 100; }
 virtual void VOnUpdate(int) { };
 virtual HRESULT VOnLostDevice() { return S_OK; }
 virtual bool VIsVisible() const { return m_bIsVisible; }
 virtual void VSetVisible(bool visible) { m_bIsVisible = visible; }
 };
 *
 */

} /* namespace base_game */

#endif /* USERINTERFACE_BASEUI_H_ */
