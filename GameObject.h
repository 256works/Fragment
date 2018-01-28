#pragma once

/*
GameObject�� ��ӹ޴� ��ü ����

stdafx.h�� include �� �� ��.
GameObject�� ��ӹ޾� �������մϴ�.
Draw, Update, Init, CollisionEvent�� virtual�� ��ӹ޾� �������մϴ�.
Draw�� ������ �� �� DrawSelf�� ���� ���־�� ��������Ʈ�� �׸��� �˴ϴ�.
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