#include "ActorFactory.h"
#include "Actor.h"
#include "ComponentFactory.h"
#include "RenderComponent.h"
#include "ScriptComponent.h"
#include "TransformComponent.h"
#include "../utilities/Templates.h"
#include "../resourceCache/ResourceHandle.h"
#include "../resourceCache/IResourceExtraData.h"
#include "../resourceCache/XmlResourceExtraData.h"

#include <memory> // shared_ptr, dynamic_pointer_cast
#include <string> // string
#include <boost/property_tree/ptree.hpp> // ptree
#include "../utilities/PropertyTreeUtils.h"
#include "../debugging/Logger.h"
#include <sstream>      // std::stringstream
#include <boost/property_tree/xml_parser.hpp> // read_xml
#include <boost/optional.hpp> // boost::optional

using std::shared_ptr;
using std::dynamic_pointer_cast;
using std::string;
using boost::property_tree::ptree;
using value_type = boost::property_tree::ptree::value_type;
// typedef std::pair<const Key, self_type>      value_type; See \boost_1_60_0\boost\property_tree\ptree.hpp
using std::stringstream;
using boost::optional;
using boost::property_tree::read_xml;

namespace base_game {

const string ActorFactory::ACTOR_NODE_NAME = "actor";

ActorFactory::ActorFactory(shared_ptr<ResourceCache> resourceCache) {
	logger::trace("Create ActorFactory");
	componentFactory = new ComponentFactory;
	componentFactory->registerComponent(RenderComponent::COMPONENT_NAME,
			&render_component::componentFactory);
	componentFactory->registerComponent(ScriptComponent::COMPONENT_NAME,
			&script_component::componentFactory);
	componentFactory->registerComponent(TransformComponent::COMPONENT_NAME,
			&transform_component::componentFactory);

	this->shrdPtrResourceCache = resourceCache;
}

ActorFactory::~ActorFactory() {
	logger::trace("Destroy ActorFactory");
	templates::safe_delete<ComponentFactory>(componentFactory);

	shrdPtrResourceCache.reset();
}

unsigned int ActorFactory::getNextActorId() {
	nextActorId++;
	return nextActorId;
}
;
ptree* ActorFactory::loadAndReturnRootXmlElement(const string& resourceName) {
	// See TiXmlElement* XmlResourceLoader::LoadAndReturnRootXmlElement(const char* resourceString)

	stringstream ss;

	/*
	 ss << "ActorFactory::loadAndReturnRootXmlElement: "
	 << shrdPtrResourceCache->tempGetAssetsFolder() << " + "
	 << resourceName;
	 logger::info(ss);
	 */

	Resource resource(resourceName);
	optional<shared_ptr<ResourceHandle>> pResourceHandle =
			shrdPtrResourceCache->getHandle(&resource);

	//     shared_ptr<XmlResourceExtraData> pExtraData = static_pointer_cast<XmlResourceExtraData>(pResourceHandle->GetExtra());
	// return pExtraData->GetRoot();

	// TODO zamiast
	// read_xml(filename, *pPtree);
	// użyc:
	// void read_xml(std::basic_istream<typename Ptree::key_type::value_type> &stream,Ptree &pt,

	shared_ptr<IResourceExtraData> extraData =
			pResourceHandle.get()->getExtraData();

	ss << pResourceHandle.get()->getResource().getName();
	logger::info(ss);

	ss << extraData->vToString();
	logger::info(ss);

	ptree* pPtree = nullptr;

	if (shared_ptr<XmlResourceExtraData> xmlExtraData = dynamic_pointer_cast<
			XmlResourceExtraData>(extraData)) {
		pPtree = xmlExtraData->getRoot();
	}

	/*
	 else {

	 pPtree = new ptree();
	 // ptree* pPtree = new ptree();
	 string filename = shrdPtrResourceCache->tempGetAssetsFolder()
	 + resourceName;
	 read_xml(filename, *pPtree);
	 }
	 */

	return pPtree;
}

/*
 ptree* ActorFactory::loadAndReturnRootXmlElement_222(
 const string& resourceName) {
 // See TiXmlElement* XmlResourceLoader::LoadAndReturnRootXmlElement(const char* resourceString)



 stringstream ss;
 ss << "ActorFactory::loadAndReturnRootXmlElement: "
 << shrdPtrResourceCache->tempGetAssetsFolder()
 << " + "
 << resourceName;
 logger::trace(ss);

 ptree* pPtree = new ptree();

 string filename = shrdPtrResourceCache->tempGetAssetsFolder()
 + resourceName;

 read_xml(filename, *pPtree);

 return pPtree;
 }
 */

shared_ptr<Actor> ActorFactory::createActor(const string& resourceName) {

//shared_ptr<Actor> ActorFactory::createActor(const string& resourceName,
	//	ptree& actorTree) {

	//	shared_ptr<Actor> ActorFactory::createActor(ptree& actorTree) {

	//void ResourceCache::tempLoadAndReturnRootXmlElement(const string& resourceName, ptree& tree) {
	//shrdPtrResourceCache->tempLoadAndReturnRootXmlElement(
	//	"actors/player_character.xml", actorTree);

	//ptree* actorTree = shrdPtrResourceCache->loadAndReturnRootXmlElement(resourceName);
	ptree* actorTree = loadAndReturnRootXmlElement(resourceName);

	property_tree_utils::print_tree(*actorTree, 0);
	optional<ptree&> actorNode = getActorNode(*actorTree);
	if (!actorNode.is_initialized()) {
		stringstream ss;
		ss << "Failed to create actor from resource! ";
		logger::error(ss);
		return shared_ptr<Actor>();
	}

	unsigned int actorId = nextActorId;
	if (actorId == INVALID_ACTOR_ID) {
		actorId = getNextActorId();
	}

	shared_ptr<Actor> actor(new Actor(actorId));
	if (!actor->init(actorNode.get())) {
		stringstream ss;
		ss << "Failed to initialize actor! ";
		logger::error(ss);
		return shared_ptr<Actor>();
	}

	for (const value_type& actorChild : actorNode.get()) {

		string name = actorChild.first;
		int compRes = name.compare("<xmlattr>");
		if (compRes == 0) {
			logger::trace("To jest <xmlattr>");
		} else {
			shared_ptr<ActorComponent> actorComponent =
					componentFactory->create(actorChild);

			if (actorComponent) {
				logger::trace("Stworzono actorComponent");
				actor->addComponent(actorComponent);
				actorComponent->setOwner(actor);

				stringstream ss;
				ss << "Post add actorComponent actor use_count: "
						<< actor.use_count();
				logger::trace(ss);
			} else {
				logger::error("Nie stworzono actorComponent");
				return shared_ptr<Actor>();
			}
		}
	}

	actor->postInit();
	// see StrongActorPtr ActorFactory::CreateActor(const char* actorResource, TiXmlElement *overrides, const Mat4x4 *pInitialTransform, const ActorId serversActorId)
	//XmlResourceLoader->loadResource();
	return actor;
}

optional<ptree&> ActorFactory::getActorNode(ptree& actorTree) {

	optional<ptree&> element = actorTree.get_child_optional(ACTOR_NODE_NAME);
	return element;
}

/*
 namespace actor_factory {
 void safe_delete(ActorFactory* p) {
 if (p) {
 delete (p);
 (p)=nullptr;
 }
 }
 }*/
}
