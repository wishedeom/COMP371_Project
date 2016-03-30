#pragma once
#include "../VS2013/Block.h"
//#include "Sun.h"
#include <vector>
#include "../VS2013/Building.h"
//#include "Skybox.h"
#include "../VS2013/Tree.h"
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
	vector<Tree*> trees;
//	Skybox* skyptr;
	Tree* treeptr;
};