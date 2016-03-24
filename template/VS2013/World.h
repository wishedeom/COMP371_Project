#pragma once
#include "Block.h"
//#include "Sun.h"
#include <vector>
#include "Building.h"
#include "Skybox.h"
#include "Tree.h"
//size of the world in blocks, the world is currently a 2x2 world (4 blocks)
#define WORLD_HEIGHT 4
#define WORLD_LENGTH 4

class World
{
public:
	World();
	~World();
	void Draw();
	static building* buildingsptr;
private:
	//hold the blocks to be drawn;
	//static Sun* sunptr;
	//static Block* blockptr;
	static vector<Block*> blocks;
	Skybox* skyptr;
	static Tree* treeptr;
};