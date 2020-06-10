/*
 * WatermillHumanView.h
 *
 *  Created on: 12 sty 2020
 *      Author: Krzysztof
 */

#ifndef SOURCE_USERINTERFACE_WATERMILLHUMANVIEW_H_
#define SOURCE_USERINTERFACE_WATERMILLHUMANVIEW_H_

#include "../../../BaseGame/source/resourceCache/ResourceCache.h"
#include "../../../BaseGame/source/userInterface/HumanView.h"
#include "../../../BaseGame/source/graphics3d/OpenGLRenderer.h"
#include "../../../BaseGame/source/userInterface/ScreenElementScene.h"
#include <memory> // shared_ptr, weak_ptr

namespace watermill_base {

class WatermillHumanView: public base_game::HumanView {
public:
	WatermillHumanView(std::shared_ptr<base_game::ResourceCache> resourceCache,
			std::shared_ptr<base_game::OpenGLRenderer> openGLRenderer);
	virtual ~WatermillHumanView();
	virtual void vTerminate();

	virtual void tempVLoadGameDelegate();
	virtual void vOnRender(double fTime, float fElapsedTime);
	virtual void tempVRender(double fTime, float fElapsedTime);

	void temp_InitScene();
protected:
	std::shared_ptr<base_game::ResourceCache> shrdPtrResourceCache;
	std::shared_ptr<base_game::ScreenElementScene> m_ScreenElementScene;
};

} /* namespace watermill */

#endif /* SOURCE_USERINTERFACE_WATERMILLHUMANVIEW_H_ */
