#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H

#include "ActorComponent.h"
#include <string> // string
#include <boost/property_tree/ptree.hpp>// ptree

namespace base_game {
class RenderComponent: public ActorComponent {
public:
	const static std::string COMPONENT_NAME;
	const static std::string COLOR_NODE_NAME;
	const static std::string ATTR_R;
	const static std::string ATTR_G;
	const static std::string ATTR_B;

	const static std::string ATTR_A;

	RenderComponent();
	virtual ~RenderComponent();
	virtual bool vInit(const boost::property_tree::ptree componentNode);
	virtual size_t vGetId();
	virtual void vPostInit();

	virtual void describeYourself();

	void tempRenderComponentFunction();

protected:
	bool readColorNode(const boost::property_tree::ptree& positionNode);
	float r, g, b, a;

private:
};

namespace render_component {
ActorComponent* componentFactory();
}
}
#endif // RENDERCOMPONENT_H
