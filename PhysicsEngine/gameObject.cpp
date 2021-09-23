#include "gameObject.h"
#include "baseGame.h"

void gameObject::destroy(gameObject* toDestroy) 
{
	for (int i = 0; i < baseGame::gameObjects.size(); i++) 
	{
		if (baseGame::gameObjects[i] == toDestroy) 
		{
			(*baseGame::gameObjects[i]).OnDestroy();
			baseGame::destroyedGameObjects.push_back(baseGame::gameObjects[i]);
			//delete[] baseGame::gameObjects[i];
			baseGame::gameObjects.erase(baseGame::gameObjects.begin() + i);
			break;
		}
	}
}