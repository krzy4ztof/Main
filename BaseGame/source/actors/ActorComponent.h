#ifndef ACTORCOMPONENT_H
#define ACTORCOMPONENT_H

#include <boost/property_tree/ptree.hpp>// ptree
#include <memory> // shared_ptr, weak_ptr
#include <string> // string

namespace base_game {
class Actor;

class ActorComponent {
public:
	ActorComponent();
	virtual ~ActorComponent();
	virtual bool vInit(const boost::property_tree::ptree componentNode) = 0;
	void setOwner(std::shared_ptr<Actor>);

	// size_t (8 bytes) - stores object of maxiumum size
	//
	// The same as:
	// unsigned long long (8 bytes)
	// unsigned long long int (8 bytes)
	//
	// Shorter values are:
	// unsigned int (4 bytes)
	// unsigned long int (4 bytes)
	virtual size_t vGetId() = 0;

	virtual void describeYourself() = 0;
	virtual void vPostInit() = 0;
	virtual void vUpdate(int deltaMs);

	static size_t getIdFromName(std::string name);
protected:
	std::shared_ptr<Actor> pOwner;

private:

};
}
#endif // ACTORCOMPONENT_H
