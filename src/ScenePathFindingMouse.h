#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>
#include "Scene.h"
#include "Agent.h"
#include "Seek.h"
#include "PathFollowing.h"
#include "BFS.h"
#include "GBFS.h"
#include "Grid.h"
#include "Dijkstra.h"
#include "AStar.h"

class ScenePathFindingMouse :
	public Scene
{
public:
	ScenePathFindingMouse();
	~ScenePathFindingMouse();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
private:
	std::vector<Agent*> agents;
	Vector2D* coinPosition;
	const int numCoins = 1;
	int* idsAlreadyPicked;

	Grid *maze;
	bool draw_grid;
		
	void drawMaze();
	void drawCoin();
	SDL_Texture *background_texture;
	SDL_Texture *coin_texture;
	bool loadTextures(char* filename_bg, char* filename_coin); 
	bool AllAgentsOnTarget();
	void UpdateAllPaths();
	Agent* GenerateAgent(Agent::PathfindingAlgorithm* pathfindingAlgorithm, Grid* maze);
	void UpdatePathAlgorithm(int idAgent); 
	void GenerateCoinPositions();
	int GetNextTargetId(int actualID);
	bool IdIsAlreadyPicked(int idToCheck);
};
