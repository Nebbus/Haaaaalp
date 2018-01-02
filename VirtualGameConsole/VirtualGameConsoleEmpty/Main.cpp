#include "VGCVirtualGameConsole.h"
#include "World.h"
#include <string>

using namespace std;

int VGCMain(const VGCStringVector &arguments) {
	World world;
	world.run();
	return 0;
}