#include "stdafx.h"
#include "Scene.h"

Scene::Scene(int width, int height, obj sceneControllGameObject)
{
	mapHeight = height;
	mapWidth = width;
	this->sceneControllGameObject = sceneControllGameObject;
}

Scene::~Scene()
{
}

int Scene::GetMapWidth()
{
	return mapWidth;
}

int Scene::GetMapHeight()
{
	return mapHeight;
}

void Scene::InitScene()
{
	GC->InstanceCreate(sceneControllGameObject, 0, 0, true);
}