#ifndef INCLUDED_ENEMY
#define INCLUDED_ENEMY

#include "VGCVirtualGameConsole.h"
#include "Object.h"
#include "Bullet.h"

class Enemy : public Object{
public:
	Enemy(std::vector<Object*>* objects);
	~Enemy();
	void update();
	void render();
	void derender();

	void move();
	void fire();

	int get_radius() const;
	int get_category() const { return 2; }										//category: Enemy
	bool is_fren() const { return false; }

private:
	VGCImage spr_enemy;
	int enemy_health = 10;
	int enemy_damage = 1;
	int enemy_direction;

	
	void bullet_create();
};

#endif // !INCLUDED_ENEMY

