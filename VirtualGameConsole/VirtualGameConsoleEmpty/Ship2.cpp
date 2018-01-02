#include "Ship2.h"
#include "VGCVirtualGameConsole.h"
#include "Object.h"
#include "Bullet.h"
#include "BulletRight.h"
#include "BulletLeft.h"
#include "Explosion.h"

static const VGCVector POSITION = VGCVector(540, 600);
static const int WIDTH = 50;																	//sprite width
static const int HEIGHT = 50;																	//sprite height
static const int SPEED = 5;
static const double TIMER = 0.5;																//Interval between shots
static const int radius = 25;
static const bool fren = true;

//////////////////////////////////////////////////////////////////////////////////////////////
Ship::Ship(std::vector<Object*>* objects):spr_ship(VGCDisplay::openImage("ship.png", 1, 1))	
{
	shoot_timer = VGCClock::openTimer(TIMER);													//start a timer
	this->objects = objects;																	//identify ship
	position = POSITION;	
	category = 1;
}
//////////////////////////////////////////////////////////////////////////////////////////////
Ship::~Ship()
{

	VGCDisplay::closeImage(spr_ship);
	VGCClock::closeTimer(shoot_timer);

}
//////////////////////////////////////////////////////////////////////////////////////////////
void Ship::update() {																			//when world calls for an update call all things that need constant checks
	move();
	fire();
	if (ship_health <= 0)
	{
		die();	
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////
void Ship::render()																				
{	
	VGCVector spr_index(0, 0);
	VGCAdjustment ship_adjustment = VGCAdjustment(0.5, 0.5);
	
	VGCDisplay::renderImage(
		spr_ship,
		spr_index,
		position,
		ship_adjustment
	);

}
//////////////////////////////////////////////////////////////////////////////////////////////
void Ship::derender(){
}
//////////////////////////////////////////////////////////////////////////////////////////////
void Ship::move()																				//check if of of the keys are pressed, if the ship is in bounds let it move
{
	const int xMin = WIDTH / 2;
	const int yMin = HEIGHT / 2;
	const int xMax = VGCDisplay::getWidth() - xMin;
	const int yMax = VGCDisplay::getHeight() - yMin;

	if (VGCKeyboard::isPressed(VGCKey::W_KEY) && position.getY() >= yMin) {
		position.setY(position.getY() - SPEED);
	}
	if (VGCKeyboard::isPressed(VGCKey::A_KEY) && position.getX() >= xMin)
	{
		position.setX(position.getX() - SPEED);
	}
	if (VGCKeyboard::isPressed(VGCKey::S_KEY) && position.getY() <= yMax)
	{
		position.setY(position.getY() + SPEED);
	}
	if (VGCKeyboard::isPressed(VGCKey::D_KEY) && position.getX() <= xMax)
	{
		position.setX(position.getX() + SPEED);
	}
	
}
//////////////////////////////////////////////////////////////////////////////////////////////
void Ship::fire()																				//check if the key is pressed and if above timer is done, if so call bullet_create() and reset the timer
{
	if (VGCKeyboard::isPressed(VGCKey::SPACE_KEY) && VGCClock::isExpired(shoot_timer)) {
		VGCClock::reset(shoot_timer);
		bullet_create_front();
		bullet_create_right();
		bullet_create_left();
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////
int Ship::get_radius() const																	
{
	return radius;
}
//////////////////////////////////////////////////////////////////////////////////////////////

//PRIVATE

//////////////////////////////////////////////////////////////////////////////////////////////
void Ship::bullet_create_front()																//create a bullet going forward, give it the current position, tell it if it's friendly and put it into the vector
{
	Bullet* bullet = new Bullet(position, is_fren());
	objects->push_back(bullet);


}
//////////////////////////////////////////////////////////////////////////////////////////////

void Ship::bullet_create_right()																//create a bullet going to the right, give it the current position, tell it if it's friendly and put it into the vector
{
	BulletRight* bullet_r = new BulletRight(position, is_fren());
	objects->push_back(bullet_r);

}
//////////////////////////////////////////////////////////////////////////////////////////////

void Ship::bullet_create_left()																	//create a bullet going to the left, give it the current position, tell it if it's friendly and put it into the vector
{
	BulletLeft* bullet_l = new BulletLeft(position, is_fren());
	objects->push_back(bullet_l);

}
//////////////////////////////////////////////////////////////////////////////////////////////
