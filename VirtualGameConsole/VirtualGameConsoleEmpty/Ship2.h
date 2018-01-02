#ifndef INCLUDED_SHIP
#define INCLUDED_SHIP

#include "VGCVirtualGameConsole.h"
#include "Object.h"

class Ship : public Object{
public:
	Ship(std::vector<Object*>* objects);
	~Ship();
	void update();
	void render();	
	void derender();
	
	void move();
	void fire();
	
	int get_radius() const;
	int get_category()const { return 1; }									//category: Ship
	bool is_fren() const { return true; }
	

private:
	VGCImage spr_ship;
	VGCTimer shoot_timer;
	int ship_health = 10;
	int ship_damage = 10;
	bool frend = true;
	int category;
	
	void bullet_create_front();
	void bullet_create_right();
	void bullet_create_left();

};

#endif
