#pragma once

class Scene
{
private:
	//char** mapData; // 2Â÷¿ø ¹è¿­ ¸Ê
	unsigned int mapWidth;
	unsigned int mapHeight;

	obj sceneControllGameObject;
public:
	//Scene(const char mapData[], int width, int height);
	Scene(int width, int height, obj sceneControllGameObject = obj::none);
	~Scene();
	//void SetMapData();
	int GetMapWidth();
	int GetMapHeight();
	void InitScene();
};