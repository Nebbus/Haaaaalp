#include "Enemy.h"
#include "VGCVirtualGameConsole.h"
#include "Object.h"
#include "Bullet.h"
#include "Explosion.h"
#include <ctime>

static const int WIDTH = 50;
static const int HEIGHT = 50;
static const int YSPEED = 1;
static const int XSPEED = 3;
static const int radius = 25;
static const bool fren = false;



//////////////////////////////////////////////////////////////////////////////////////////////
Enemy::Enemy(std::vector<Object*>* objects): spr_enemy(VGCDisplay::openImage("enemy.png", 1, 1))
{
	this->objects = objects;																	//indentify enemy
	enemy_direction = VGCRandomizer::getInt(0, 1);												//randomize start direction
	int STARTX = VGCRandomizer::getInt(0, 1080);												//randomize start position
	position = VGCVector(STARTX, 0);															//initialize position with above position
}
//////////////////////////////////////////////////////////////////////////////////////////////
Enemy::~Enemy(){
	VGCDisplay::closeImage(spr_enemy);
	
}
//////////////////////////////////////////////////////////////////////////////////////////////
void Enemy::update(){																			//when world calls for an update call all things that need constant checks

	move();
	fire();

}
//////////////////////////////////////////////////////////////////////////////////////////////
void Enemy::render(){																			
	VGCVector spr_index(0, 0);
	VGCAdjustment enemy_adjustment = VGCAdjustment(0.5, 0.5);

	VGCDisplay::renderImage(
		spr_enemy,
		spr_index,
		position,
		enemy_adjustment
	);
}
//////////////////////////////////////////////////////////////////////////////////////////////
void Enemy::derender()
{

	VGCDisplay::closeImage(spr_enemy);
}
//////////////////////////////////////////////////////////////////////////////////////////////
void Enemy::move()																				//set downward movement, check what direction to go and add horizontal movement accordingly
{
	const int xMin = WIDTH / 2;
	const int xMax = VGCDisplay::getWidth() - xMin;
	const int yMin = HEIGHT / 2;
	const int yMax = VGCDisplay::getHeight() - yMin;

	position.setY(position.getY() + YSPEED);
	
	if (position.getX() < 0) {																	//if enemy is about to go out of bounds sideways, change direction
		enemy_direction = 0;
	}
	if (position.getX() > 1080) {
		enemy_direction = 1;
	}
	if (enemy_direction == 0) {
		position.setX(position.getX() + XSPEED);
	}
	if(enemy_direction == 1) {
		position.setX(position.getX() - XSPEED);
	}
	if (position.getY() > 770) {																//kill enemy if they go below bounds
		
		VGCDisplay::closeImage(spr_enemy);
		Object::die();
	}

}
//////////////////////////////////////////////////////////////////////////////////////////////
void Enemy::fire()																				//fire a bullet at a randomized interval
{
	if (VGCRandomizer::getBool(0.015)) {
		bullet_create();
	}
		
		
}
//////////////////////////////////////////////////////////////////////////////////////////////
int Enemy::get_radius() const
{
	return radius;
}
//////////////////////////////////////////////////////////////////////////////////////////////

//PRIVATE

//////////////////////////////////////////////////////////////////////////////////////////////
void Enemy::bullet_create()																		//create a bullet going down, give it the current position, tell it if it's friendly and put it into the vector	
{
	Bullet* bullet = new Bullet(position, is_fren());
	objects->push_back(bullet);

}
//////////////////////////////////////////////////////////////////////////////////////////////
