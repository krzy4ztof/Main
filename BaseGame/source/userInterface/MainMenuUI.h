/*
 * MainMenuUI.h
 *
 *  Created on: 22 sty 2020
 *      Author: Krzysztof
 */

#ifndef USERINTERFACE_MAINMENUUI_H_
#define USERINTERFACE_MAINMENUUI_H_

#include "BaseUI.h"

namespace base_game {

class MainMenuUI: public BaseUI {
public:
	MainMenuUI();
	virtual ~MainMenuUI();

	virtual void vOnRestore();
	virtual void vOnRender(double fTime, float fElapsedTime);
	virtual int vGetZOrder() const;
	virtual void vSetZOrder(int const zOrder) const;
	virtual void vTerminate();

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

} /* namespace base_game */

#endif /* USERINTERFACE_MAINMENUUI_H_ */
