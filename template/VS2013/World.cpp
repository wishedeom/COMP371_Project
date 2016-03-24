#pragma once
#include "World.h"

vector<Block*> World::blocks;
building* World::buildingsptr = NULL;
Tree* World::treeptr;
//Sun* World::sunptr;

World::World(){
	//set the camera here
	//set sun here: note current sun.cpp doesnt work
//	sunptr = new Sun();
	skyptr = new Skybox(1);
	treeptr = new Tree(0.5f, 0.75f, "C:/Users/mimi/Desktop/template/MegaOne/Images/birch_tree_small.png");
	blocks;
	building buildings;
	buildingsptr = new building();
	buildingsptr->BuildCity();

	//populates the world with a # of blocks
	//can be changed to have a random number of blocks, or take input 

	for (GLuint i = 0; i < WORLD_HEIGHT; i++){
		for (int j = 0; j < WORLD_LENGTH; j++){
			Block* b = (new Block(i,j));
			blocks.push_back(b);
		}
	}
}

World::~World(){
	for (GLuint i = 0; i < blocks.size(); i++){
		delete blocks.at(i);
		blocks.at(i) = nullptr;
	}
	blocks.clear();
	delete buildingsptr;
	buildingsptr = nullptr;
	delete treeptr;
	treeptr = nullptr;
/*	delete sunptr;
	sunptr = nullptr;*/
}


void World::Draw(){
	//gotta find a more efficient way to draw the blocks
	//sunptr->Draw();
	treeptr->draw();

/*	buildingsptr->Draw();
*/
	for (int i = 0; i < blocks.size(); i++){
		blocks.at(i)->draw();
	}

	//skyptr->draw(); // is drawn only there is another object...????
	
}