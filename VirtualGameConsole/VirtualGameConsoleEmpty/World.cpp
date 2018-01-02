
#include "World.h"
#include "Ship2.h"
#include "Enemy.h"
#include "Bullet.h"
#include "BulletRight.h"
#include "BulletLeft.h"
#include "Explosion.h"

using namespace std;
//////////////////////////////////////////////////////////////////////////////////////////////
void World::run(){
	const string application_name = "Spaaace";													//set app name
	const int DISPLAY_WIDTH = 1080;																//set display size
	const int DISPLAY_HEIGHT = 720;
	const double SPAWN_TIME = 2;																//set spawntime for enemies
	const double BOOM_DELAY = 0.5;																//Interval between shots


	VGCVirtualGameConsole::initialize(application_name, DISPLAY_WIDTH, DISPLAY_HEIGHT);			//initialize window
	VGCTimer spawn_timer = VGCClock::openTimer(SPAWN_TIME);
	//boom_delay = VGCClock::openTimer(BOOM_DELAY);
	


	create();																					//create player avatar and put it in the vector
		
	while (VGCVirtualGameConsole::beginLoop()) {

		while (VGCClock::isExpired(spawn_timer)) {												//create enemies and put it in the vector	
			VGCClock::reset(spawn_timer);
			enemy_create();
		}

		update();																				//update all objects every frame

		if (VGCDisplay::beginFrame()) {

			VGCColor backgroundColor = VGCColor(255, 0, 0, 0);									//draw window background
			VGCDisplay::clear(backgroundColor);


			render();																			//render all objects

			VGCDisplay::endFrame();
		}
		VGCVirtualGameConsole::endLoop();
	}

//destroy all objects			
	derender();
	delete ship;
	objects.erase(objects.begin(), objects.end());
	
	
	//VGCClock::closeTimer(boom_delay);
	VGCClock::closeTimer(spawn_timer);		
	VGCVirtualGameConsole::finalize();
}
//////////////////////////////////////////////////////////////////////////////////////////////
void World::update() {	
	auto copy = objects;																		//take a snapshot of the objects in the vector						
	for (auto &object : copy) {																	//go through all objects in vector and run their update()
		object->update();
	}
	vector<Object*> boom = {};
	auto it = objects.begin();																	//go to start of vector
	while (it != objects.end()) {																//go through all objects in vector and check if they're alive, if not delete them
		Object* obj = *it;
		if (!obj->is_alive()) {
			
			VGCVector obj_position = obj->get_position();
			bool obj_fren = obj->is_fren();
			int obj_cat = obj->get_category();

			if (obj_cat == 0) {
				int test = 0;
			}

     		delete *it;
			it = objects.erase(it);

			if ((obj_cat != 4 || obj_cat != 0) && !obj_fren) {

			Explosion *explosion = new Explosion(obj_position, obj_fren);
			boom.push_back(explosion);
			}
			

			
		}
		else {
				++it;
		}
	}

	for (auto explosion : boom) {
		objects.push_back(explosion);
	}
	boom.erase(boom.begin(), boom.end());
	collision_detect();
}
//////////////////////////////////////////////////////////////////////////////////////////////
void World::render() {
	for (ObjectVector::size_type i = 0; i < objects.size(); i++) {								//go through all objects in vector and call their render()
		objects[i]->render();
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////
void World::derender(){
	for (auto &object : objects) {																//go through all objects in vector and call their derender()
		object->derender();
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////
void World::create() {
	ship = new Ship(&objects);																	//create new ship
	objects.push_back(ship);																	//put that ship into the vector
}
//////////////////////////////////////////////////////////////////////////////////////////////
void World::enemy_create() {										
	enemy = new Enemy(&objects);																//create new enemy
	objects.push_back(enemy);																	//put that enemy into the vector
}
//////////////////////////////////////////////////////////////////////////////////////////////
void World::collision_detect() {
																								//go through all objects in vector and check if they collide
	ObjectVector objects(objects);		
	//static const double BOOM_DELAY;
	for (size_t i = 0; i < objects.size(); i++) {												//go through all objects in vector
		Object *obj_self = objects[i];

		for (size_t j = 0; j < objects.size(); j++) {											//on all objects, go through all other objects
			Object *obj_other = objects[j];

			if (obj_self->get_category() != obj_other->get_category()) {						//check if the first object is of the same type as the second object or not

				if (obj_self->is_fren() != obj_other->is_fren() && is_overlap(obj_self, obj_other)) {	//if they are different objects, check if they are unfriendly towards each other and check if they overlap
					//Score += entity0->collide(entity1, mEntities);
					if(obj_other->get_category() == 2 && obj_self->get_category() == 0){
 						int test = 0;
					}
        			obj_other->die();
				}

			}
		}
	}
	
}
//////////////////////////////////////////////////////////////////////////////////////////////
bool World::is_overlap(Object *obj_self, Object *obj_other) {			
																								//check if 2 objects overlap
	VGCVector position_self = obj_self->get_position();											//store the position of both objects in 2 vectors
	VGCVector position_other = obj_other->get_position();
	
	int self_x = position_self.getX();															//split up the vector in x and y values and get the radius of the object
	int self_y = position_self.getY();
	int self_radius = obj_self->get_radius();
	
	int other_x = position_other.getX();
	int other_y = position_other.getY();
	int other_radius = obj_other->get_radius();
	
	int diameter_x = self_x - other_x;															//get the distance between the 2 objects for x and y values
	int diameter_y = self_y - other_y;

	return (diameter_x * diameter_x) + (diameter_y * diameter_y) < ((self_radius + other_radius) * (self_radius + other_radius));	//use Pythagorean theorem to calculate direct distance between the 2 objects, if the distance is shorter than the distance between the 2 objects' radii then return true
}
//////////////////////////////////////////////////////////////////////////////////////////////