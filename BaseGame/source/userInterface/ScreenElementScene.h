/*
 * ScreenElementScene.h
 *
 *  Created on: 22 sty 2020
 *      Author: Krzysztof
 */

#ifndef USERINTERFACE_SCREENELEMENTSCENE_H_
#define USERINTERFACE_SCREENELEMENTSCENE_H_

#include "IScreenElement.h"

namespace base_game {

class ScreenElementScene: public IScreenElement {
public:
	ScreenElementScene();
	virtual ~ScreenElementScene();

	virtual void vOnRestore();
	virtual void vOnRender(double fTime, float fElapsedTime);
	virtual void vOnUpdate(int deltaMS);

	virtual int vGetZOrder() const;
	virtual void vSetZOrder(int const zOrder) const;

	virtual bool vIsVisible() const;
	virtual void vSetVisible(bool visible);
	virtual void vTerminate();

};

/*
 * class ScreenElementScene : public IScreenElement, public Scene
 {
 public:
 ScreenElementScene(shared_ptr<IRenderer> renderer) : Scene(renderer) { }
 virtual ~ScreenElementScene(void)
 {
 GCC_WARNING("~ScreenElementScene()");
 }

 // IScreenElement Implementation
 virtual void VOnUpdate(int deltaMS) { OnUpdate(deltaMS); };
 virtual HRESULT VOnRestore()
 { OnRestore(); return S_OK; }
 virtual HRESULT VOnRender(double fTime, float fElapsedTime)
 { OnRender(); return S_OK; }
 virtual HRESULT VOnLostDevice()
 { OnLostDevice(); return S_OK; }
 virtual int VGetZOrder() const { return 0; }
 virtual void VSetZOrder(int const zOrder) { }

 // Don't handle any messages
 virtual LRESULT CALLBACK VOnMsgProc( AppMsg msg ) { return 0; }

 virtual bool VIsVisible() const { return true; }
 virtual void VSetVisible(bool visible) { }
 virtual bool VAddChild(ActorId id, shared_ptr<ISceneNode> kid) { return Scene::AddChild(id, kid); }
 };
 *
 */

} /* namespace base_game */

#endif /* USERINTERFACE_SCREENELEMENTSCENE_H_ */
