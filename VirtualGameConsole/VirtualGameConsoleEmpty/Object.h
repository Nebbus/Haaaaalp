#ifndef INCLUDED_OBJECT
#define INCLUDED_OBJECT

#include "VGCVirtualGameConsole.h"
#include <cstdlib>

class Object {
public:
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void derender() = 0;
	
	std::vector<Object*>* objects;
	VGCVector position;
	virtual bool is_alive();
	virtual void die();
	
	VGCVector get_position();														
	virtual int get_radius() const = 0;
	virtual int get_category() const = 0;											// 0 = Bullet, 1 = Ship, 2 = Enemy
	virtual bool is_fren() const = 0;

private:
	bool alive = true;
	//int obj_radius;
	
};
#endif
