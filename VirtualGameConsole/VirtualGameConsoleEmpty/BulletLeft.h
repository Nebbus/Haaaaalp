#ifndef INCLUDED_BULLETLEFT
#define INCLUDED_BULLETLEFT

#include <VGCVirtualGameConsole.h>
#include <vector>
#include "Object.h"

class BulletLeft : public Object {
public:
	BulletLeft(VGCVector pos, bool fren);
	~BulletLeft();
	void update();
	void render();
	void derender();

	void move();

	int get_radius() const;
	int get_category() const { return 0; }
	bool is_fren() const { return frend; }

private:
	VGCImage spr_bullet;
	int bullet_direction;
	int bullet_health = 10;
	int bullet_damage = 1;
	int SPEED;
	bool frend;
	int obj_radius;

};

#endif