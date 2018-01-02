#ifndef INCLUDED_WORLD
#define INCLUDED_WORLD

#include "VGCVirtualGameConsole.h"
#include "Object.h"
#include "Ship2.h"
#include "Enemy.h"
#include "Bullet.h"
#include "BulletRight.h"
#include "BulletLeft.h"
#include "Explosion.h"
#include <string>

class World {
public:
	void run();
	typedef std::vector<Object*> ObjectVector;
	ObjectVector objects;
	Ship *ship;
	Enemy *enemy;
	Bullet *bullet;
	BulletRight *bullet_r;
	BulletLeft *bullet_l;
	Explosion *explosion;

private:
	void update();
	void render();
	void derender();

	void create();
	void enemy_create();
	VGCTimer boom_delay;

	void collision_detect();
	bool is_overlap(Object *obj_self, Object *obj_other);

	
};

#endif // !INCLUDED_WORLD;