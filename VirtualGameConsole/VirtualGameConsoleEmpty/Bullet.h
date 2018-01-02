#ifndef INCLUDED_BULLET
#define INCLUDED_BULLET

#include <VGCVirtualGameConsole.h>
#include <vector>
#include "Object.h"

class Bullet : public Object {
public:
	Bullet(VGCVector pos, bool fren);
	~Bullet();
	void update();
	void render();
	void derender();

	void move();

	int get_radius() const { return obj_radius; }
	int get_category() const { return 0; }
	bool is_fren() const { return frend; }

private:
	VGCImage spr_bullet;
	int bullet_direction;
	int bullet_health = 10;
	int bullet_damage = 1;
	int SPEED;
	int obj_radius = 13;
	bool frend;

};

#endif