#include <VGCVirtualGameConsole.h>
#include "BulletRight.h"
#include "Ship2.h"
#include <cstdlib>
#include <vector>

using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////
BulletRight::BulletRight(VGCVector pos, bool fren) : spr_bullet(VGCDisplay::openImage("bullet.png", 1, 1))
{
	position = pos;																				//set position to the same as the object that created the bullet
	frend = fren;																				//set whether or not the bullet is hostile
	SPEED = 3;
	obj_radius = 13;
}
//////////////////////////////////////////////////////////////////////////////////////////////
BulletRight::~BulletRight()
{
	VGCDisplay::closeImage(spr_bullet);
}
//////////////////////////////////////////////////////////////////////////////////////////////
void BulletRight::update()																		//when world calls for an update call all things that need constant checks
{
	move();

}
//////////////////////////////////////////////////////////////////////////////////////////////
void BulletRight::render()
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
void BulletRight::derender()
{
	VGCDisplay::closeImage(spr_bullet);
}
//////////////////////////////////////////////////////////////////////////////////////////////
void BulletRight::move()																		//set movement according to what object created the bullet
{
	if (frend) {
		position.setY(position.getY() - SPEED);
		position.setX(position.getX() + SPEED);
	}
	if (position.getY() < -50 || position.getY() > 770 || position.getX() < -50 || position.getX() > 1130) {	//if out of bounds, kill the bullet
		//Object::die();
		this->die();
		VGCDisplay::closeImage(spr_bullet);
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////
int BulletRight::get_radius() const
{
	return obj_radius;
}
//////////////////////////////////////////////////////////////////////////////////////////////
