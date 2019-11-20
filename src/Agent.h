#pragma once
#include <iostream>
#include <minmax.h>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "SDL_SimpleApp.h"
#include "Path.h"
#include "Vector2D.h"
#include "utils.h"
#include "Graf.h"
#include "Grid.h"
#include "Node.h"

class Grid;

class Agent
{
public:
	class SteeringBehavior
	{
	public:
		SteeringBehavior() {};
		virtual ~SteeringBehavior() {};
		virtual void applySteeringForce(Agent *agent, float dtime) {};
	};

	class PathfindingAlgorithm 
	{
	public:
		std::vector<Node> generatedPath;
		PathfindingAlgorithm() {};
		virtual ~PathfindingAlgorithm() {};
	};

private:
	SteeringBehavior *steering_behaviour;
	PathfindingAlgorithm* pathfinding_algorithm;
	Vector2D position;
	Vector2D velocity;
	Vector2D target;

	// Pathfinding
	Path path;
	int currentTargetIndex;

	float mass;
	float orientation;
	float max_force;
	float max_velocity;

	SDL_Texture *sprite_texture;
	bool draw_sprite;
	int sprite_num_frames;
	int sprite_w;
	int sprite_h;

	Graf graph;

public:
	Agent();
	~Agent();
	Vector2D getPosition();
	Vector2D getTarget();
	Vector2D getVelocity();
	float getMaxVelocity();
	float getMaxForce();
	float getMass();
	Agent::PathfindingAlgorithm* getAlgorithm();
	void setBehavior(SteeringBehavior *behavior);
	void setAlgorithm(PathfindingAlgorithm *algorithm);
	void setPosition(Vector2D position);
	void setTarget(Vector2D target);
	void setVelocity(Vector2D velocity);
	void addPathPoint(Vector2D point);
	void setCurrentTargetIndex(int idx);
	int getCurrentTargetIndex();
	int getPathSize();
	Vector2D getPathPoint(int idx);
	void clearPath();
	void update(float dtime, SDL_Event *event);
	void draw();
	bool Agent::loadSpriteTexture(char* filename, int num_frames=1);
	void InitializeGraph(Grid* grid);
	Graf GetGraph();


};
