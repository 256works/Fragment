#pragma once

/*
GameObject를 상속받는 객체 설명

stdafx.h에 include 꼭 할 것.
GameObject를 상속받아 디자인합니다.
Draw, Update, Init, CollisionEvent를 virtual로 상속받아 재정의합니다.
Draw를 재정의 할 시 DrawSelf를 실행 해주어야 스프라이트를 그리게 됩니다.
*/

class GameObject
{
protected:
	obj objectIndex;
	spr spriteIndex;
	FPOINT pos;
	RECT bbox;
	bool destroyQue;
	float imageIndex;
	int depth;

	vector<GameObject*>::iterator it;

public:

	GameObject();
	~GameObject();

	void SetPos(POINT pos);
	void SetPos(FPOINT pos);
	obj GetObjType();
	GameObject* PlaceCollision(obj target, int x, int y);
	RECT GetBbox();
	FPOINT GetPos();
	bool IsDestroyQue();
	void InstanceDestroy();
	void DrawSelf();
	int GetDepth();

	virtual void Draw();
	virtual void Update();
	virtual void UserEvent(char number);
	virtual void Init();
	void UseCollision();
	void UseCollision(obj object, vector<GameObject*> list);
	void UseCollision(GameObject* instance);

	virtual void CollisionEvent(obj object, GameObject* inst);
};