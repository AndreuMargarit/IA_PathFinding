#include "ScenePathFindingMouse.h"

using namespace std;

ScenePathFindingMouse::ScenePathFindingMouse()
{
	draw_grid = false;
	maze = new Grid("../res/maze.csv");

	loadTextures("../res/maze.png", "../res/coin.png");

	srand((unsigned int)time(NULL));
	
	//agents.push_back(GenerateAgent(new GBFS, maze));
	//agents.push_back(GenerateAgent(new BFS, maze));
	agents.push_back(GenerateAgent(new Dijkstra, maze));

	// set agent position coords to the center of a random cell
	Vector2D rand_cell(-1,-1);
	while (!maze->isValidCell(rand_cell))
		rand_cell = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));

	for (int i = 0; i < agents.size(); i++)
		agents[i]->setPosition(maze->cell2pix(rand_cell));

	// set the coin in a random cell (but at least 3 cells far from the agent)
	coinPosition = Vector2D(-1,-1);
	while ((!maze->isValidCell(coinPosition)) || (Vector2D::Distance(coinPosition, rand_cell)<3))
		coinPosition = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));

	UpdateAllPaths();
}

ScenePathFindingMouse::~ScenePathFindingMouse()
{
	if (background_texture)
		SDL_DestroyTexture(background_texture);
	if (coin_texture)
		SDL_DestroyTexture(coin_texture);

	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void ScenePathFindingMouse::update(float dtime, SDL_Event *event)
{
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_SPACE)
			draw_grid = !draw_grid;
		break;
	/*case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			Vector2D cell = maze->pix2cell(Vector2D((float)(event->button.x), (float)(event->button.y)));
			if (maze->isValidCell(cell)) {
				agents[0]->addPathPoint(maze->cell2pix(cell));
			}
		}
		break;*/
	default:
		break;
	}
	
	for (int i = 0; i < agents.size(); i++) {
		agents[i]->update(dtime, event);
		// if we have arrived to the coin, replace it in a random cell!
		if ((agents[i]->getCurrentTargetIndex() == -1) && (maze->pix2cell(agents[i]->getPosition()) == coinPosition))
		{
			agents[i]->SetHasArrivedToTarget(true);
		}
	}

	UpdateAllPaths();
}

void ScenePathFindingMouse::draw()
{
	drawMaze();
	drawCoin();

	if (draw_grid)
	{
		SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 255, 255, 255, 127);
		for (int i = 0; i < SRC_WIDTH; i+=CELL_SIZE)
		{
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), i, 0, i, SRC_HEIGHT);

		}
		for (int j = 0; j < SRC_HEIGHT; j = j += CELL_SIZE)
		{
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), 0, j, SRC_WIDTH, j);
		}
	}

	//Draw all nodes of the gridd
	/*
	Graf graph = agents[0]->GetGraph();
	Node* node;
	for (int i = 0; i < SRC_WIDTH / CELL_SIZE; i++)
	{
		for (int j = 0; j < SRC_HEIGHT / CELL_SIZE; j++)
			if (graph.CheckNode(Vector2D(i, j)))
			{
				node = graph.GetNode(Vector2D(i, j));
				Vector2D aux = maze->cell2pix(node->GetPosition());
				draw_circle(TheApp::Instance()->getRenderer(),aux.x , aux.y, 15, 255, 0, 0, 255);
			}
	}*/

	agents[0]->draw();
}

const char* ScenePathFindingMouse::getTitle()
{
	return "SDL Path Finding :: PathFinding Mouse Demo";
}

void ScenePathFindingMouse::drawMaze()
{
	SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 0, 255, 255);
	SDL_Rect rect;
	Vector2D coords;
	for (int j = 0; j < maze->getNumCellY(); j++)
	{
		for (int i = 0; i < maze->getNumCellX(); i++)
		{		
			if (!maze->isValidCell(Vector2D((float)i, (float)j)))
			{
				SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 0, 255, 255);
				coords = maze->cell2pix(Vector2D((float)i, (float)j)) - Vector2D((float)CELL_SIZE / 2, (float)CELL_SIZE / 2);
				rect = { (int)coords.x, (int)coords.y, CELL_SIZE, CELL_SIZE };
				SDL_RenderFillRect(TheApp::Instance()->getRenderer(), &rect);
			} else {
				// Do not draw if it is not necessary (bg is already black)
			}
		}
	}
	//Alternative: render a backgroud texture:
	//SDL_RenderCopy(TheApp::Instance()->getRenderer(), background_texture, NULL, NULL );
}

void ScenePathFindingMouse::drawCoin()
{
	Vector2D coin_coords = maze->cell2pix(coinPosition);
	int offset = CELL_SIZE / 2;
	SDL_Rect dstrect = {(int)coin_coords.x-offset, (int)coin_coords.y - offset, CELL_SIZE, CELL_SIZE};
	SDL_RenderCopy(TheApp::Instance()->getRenderer(), coin_texture, NULL, &dstrect);
}

bool ScenePathFindingMouse::loadTextures(char* filename_bg, char* filename_coin)
{
	SDL_Surface *image = IMG_Load(filename_bg);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	background_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	if (image)
		SDL_FreeSurface(image);

	image = IMG_Load(filename_coin);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	coin_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	if (image)
		SDL_FreeSurface(image);

	return true;
}

Agent* ScenePathFindingMouse::GenerateAgent(Agent::PathfindingAlgorithm* pathfindingAlgorithm, Grid* maze) {

	Agent* agent = new Agent;
	agent->InitializeGraph(maze);
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agent->setBehavior(new PathFollowing);
	agent->setAlgorithm(pathfindingAlgorithm);
	agent->setTarget(Vector2D(-20, -20));
	return agent;

}

bool ScenePathFindingMouse::AllAgentsOnTarget() {

	for (int i = 0; i < agents.size(); i++) {
		if (!agents[i]->GetHasArrivedToTarget()) {
			return false;
		}
	}
	return true;

}

void ScenePathFindingMouse::UpdateAllPaths() {

	if (AllAgentsOnTarget()) {
		coinPosition = Vector2D(-1, -1);
		while ((!maze->isValidCell(coinPosition)) || (Vector2D::Distance(coinPosition, maze->pix2cell(agents[0]->getPosition())) < 3))
			coinPosition = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));

		for (int i = 0; i < agents.size(); i++) {
			UpdatePathAlgorithm(i);
			agents[i]->SetHasArrivedToTarget(false);
		}
	}
}

void ScenePathFindingMouse::UpdatePathAlgorithm(int idAgent) {

	agents[idAgent]->getAlgorithm()->GeneratePath(agents[idAgent]->GetGraph(), maze->pix2cell(agents[idAgent]->getPosition()), coinPosition);

	for (int i = 0; i < agents[idAgent]->getAlgorithm()->GetGeneratedPath().size(); i++) {
		agents[idAgent]->addPathPoint(maze->cell2pix(agents[idAgent]->getAlgorithm()->GetGeneratedPath()[i].GetPosition()));
	}

}
