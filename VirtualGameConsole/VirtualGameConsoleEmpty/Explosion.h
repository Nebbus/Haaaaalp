#ifndef INCLUDED_EXPLOSION
#define INCLUDED_EXPLOSION

#include <VGCVirtualGameConsole.h>
#include <vector>
#include "Object.h"

class Explosion : public Object {
public:
	Explosion(VGCVector pos, bool fren);
	~Explosion();
	void update();
	void render();
	void derender();


	int get_radius() const;
	int get_category() const { return 4; }
	bool is_fren() const { return  frend; }

private:
	VGCTimer stay_timer;
	VGCImage spr_boom;
	int boom_damage = 1;
	int obj_radius;
	int category;
	bool frend;

};

#endif