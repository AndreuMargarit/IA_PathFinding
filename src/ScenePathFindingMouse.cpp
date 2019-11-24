#include "ScenePathFindingMouse.h"

using namespace std;

ScenePathFindingMouse::ScenePathFindingMouse()
{
	draw_grid = false;
	maze = new Grid("../res/maze.csv");

	loadTextures("../res/maze.png", "../res/coin.png");

	srand((unsigned int)time(NULL));

	agents.push_back(GenerateAgent(new GBFS, maze));
	agents.push_back(GenerateAgent(new BFS, maze));
	agents.push_back(GenerateAgent(new Dijkstra, maze));
	agents.push_back(GenerateAgent(new AStar, maze));

	// set agent position coords to the center of a random cell
	Vector2D rand_cell(-1,-1);
	while (!maze->isValidCell(rand_cell))
		rand_cell = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));

	for (int i = 0; i < agents.size(); i++)
		agents[i]->setPosition(maze->cell2pix(rand_cell));

	idsAlreadyPicked = new int[numCoins];
	coinPosition = new Vector2D[numCoins];

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
	default:
		break;
	}

	for (int i = 0; i < agents.size(); i++) {
		agents[i]->update(dtime, event);
		// if we have arrived to the coin, replace it in a random cell!
		if ((agents[i]->getCurrentTargetIndex() == -1) && (maze->pix2cell(agents[i]->getPosition()) == coinPosition[numCoins - 1]))
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

	for (int i = 0; i < agents.size(); i++) {
		agents[i]->draw();
	}
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
	for (int i = 0; i < coinPosition->Length(); i++) {
		Vector2D coin_coords = maze->cell2pix(coinPosition[i]);
		int offset = CELL_SIZE / 2;
		SDL_Rect dstrect = { (int)coin_coords.x - offset, (int)coin_coords.y - offset, CELL_SIZE, CELL_SIZE };
		SDL_RenderCopy(TheApp::Instance()->getRenderer(), coin_texture, NULL, &dstrect);
	}
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
		GenerateCoinPositions();

		for (int i = 0; i < agents.size(); i++) {
			idsAlreadyPicked = new int[numCoins];
			UpdatePathAlgorithm(i);
			agents[i]->SetHasArrivedToTarget(false);
		}
	}
}

void ScenePathFindingMouse::UpdatePathAlgorithm(int idAgent) {

	for (int i = 0; i < numCoins; i++) {
		if (i == 0)
			agents[idAgent]->getAlgorithm()->GeneratePath(agents[idAgent]->GetGraph(), maze->pix2cell(agents[idAgent]->getPosition()), coinPosition[GetNextTargetId(i)]);
		else
			agents[idAgent]->getAlgorithm()->GeneratePath(agents[idAgent]->GetGraph(), maze->pix2cell(agents[idAgent]->getPathPoint(agents[idAgent]->getPathSize() - 1)), coinPosition[GetNextTargetId(i)]);

		for (int i = 0; i < agents[idAgent]->getAlgorithm()->GetGeneratedPath().size(); i++) {
			agents[idAgent]->addPathPoint(maze->cell2pix(agents[idAgent]->getAlgorithm()->GetGeneratedPath()[i].GetPosition()));
		}
	}
}

void ScenePathFindingMouse::GenerateCoinPositions() {
	// set the coin in a random cell (but at least 3 cells far from the agent)
	for (int i = 0; i < numCoins; i++) {

		while ((!maze->isValidCell(coinPosition[i])) || (Vector2D::Distance(coinPosition[i], maze->pix2cell(agents[0]->getPosition())) < 3))
			coinPosition[i] = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
	}
}

int ScenePathFindingMouse::GetNextTargetId(int actualID) {

	float calculatedDistance;
	float closestCoin; 
	float idClosestCoin = 0;

	if (actualID == 0) {

		closestCoin = Vector2D::Distance(maze->pix2cell(agents[0]->getPosition()), coinPosition[0]);

		for (int i = 1; i < numCoins; i++) {
			calculatedDistance = Vector2D::Distance(maze->pix2cell(agents[0]->getPosition()), coinPosition[i]);
			if (calculatedDistance < closestCoin) {
				closestCoin = calculatedDistance;
				idClosestCoin = i;
			}
		}
	}
	else {

		closestCoin = 1000;

		for (int i = 0; i < numCoins; i++) {
			if (i != idsAlreadyPicked[actualID - 1] && !IdIsAlreadyPicked(i)) {
				calculatedDistance = Vector2D::Distance(coinPosition[idsAlreadyPicked[actualID - 1]], coinPosition[i]);
				if (calculatedDistance < closestCoin) {
					closestCoin = calculatedDistance;
					idClosestCoin = i;
				}
			}
		}
	}

	idsAlreadyPicked[actualID] = idClosestCoin;
	return idClosestCoin;
}

bool ScenePathFindingMouse::IdIsAlreadyPicked(int idToCheck) {
	for (int i = 0; i < numCoins; i++) {
		if (idsAlreadyPicked[i] == idToCheck)
			return true;
	}
	return false;
}

