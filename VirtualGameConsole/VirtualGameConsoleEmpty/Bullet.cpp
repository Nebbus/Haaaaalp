#include <VGCVirtualGameConsole.h>
#include "Bullet.h"
#include "Ship2.h"
#include <cstdlib>
#include <vector>

using namespace std;
//////////////////////////////////////////////////////////////////////////////////////////////
Bullet::Bullet(VGCVector pos, bool fren): spr_bullet(VGCDisplay::openImage("bullet.png", 1, 1))
{
	position = pos;																				//set position to the same as the object that created the bullet
	frend = fren;																				//set whether or not the bullet is hostile
	SPEED = 3;
}
//////////////////////////////////////////////////////////////////////////////////////////////
Bullet::~Bullet()
{
	VGCDisplay::closeImage(spr_bullet);
}
//////////////////////////////////////////////////////////////////////////////////////////////
void Bullet::update()																			//when world calls for an update call all things that need constant checks
{
	move();
	
}
//////////////////////////////////////////////////////////////////////////////////////////////
void Bullet::render()
{
	VGCVector spr_index(0, 0);
	VGCAdjustment bullet_adjustment = VGCAdjustment(0.5, 0.5);

	VGCDisplay::renderImage(
		spr_bullet,
		spr_index,
		position,
		bullet_adjustment
	);
}
//////////////////////////////////////////////////////////////////////////////////////////////
void Bullet::derender()
{
	VGCDisplay::closeImage(spr_bullet);
}

//////////////////////////////////////////////////////////////////////////////////////////////
void Bullet::move()																				//set movement according to what object created the bullet
{
	if (!frend) {
		position.setY(position.getY() + SPEED);
	}
	else {
		position.setY(position.getY() - SPEED);
	}  
	if (position.getY() < -50 || position.getY() > 770 || position.getX() < -50 || position.getX() > 1130) {	//if out of bounds, kill the bullet
		// Object::die();
		Object::die();
		VGCDisplay::closeImage(spr_bullet);
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////
