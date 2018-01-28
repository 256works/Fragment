#include "stdafx.h"
#include "GameObject.h"

/*

GameObject ��� ���� �Լ�

--
�̺�Ʈ (���� �Լ� ���)

Init : �ʱ� �����ÿ� �۵��մϴ�.
Update : �ν��Ͻ��� ���� �� ������ �ݺ��մϴ�.
Draw : �� ������ ��ü�� �׸��ϴ�.
CollisionEvent : �ν��Ͻ� �浹 �̺�Ʈ�Դϴ�. object�� �浹�� obj ������ �ް� inst�� �浹�� �ν��Ͻ��� �ּҰ��� �޽��ϴ�.
UserEvent(number) : ����� �̺�Ʈ�� �����մϴ�.

--

InstanceDestroy() : �ν��Ͻ� ����. ���� �ٸ� ������� ������ ���� �� �Լ� �̿��� ��.
DrawSelf() : mySprite�� �� ��ġ�� �׸���. �ִϸ��̼��� �ڵ����� ���.

KEY->isKeyPressed(vk) : vkŰ�� ȣ�� ������ ���� �������� bool Ÿ������ ��ȯ�մϴ�.
KEY->isKeyDown(vk) : vkŰ�� ��� �������ִ��� bool Ÿ������ ��ȯ�մϴ�.
KEY->isKeyReleased(vk) : vkŰ�� �������� bool Ÿ������ ��ȯ�մϴ�.

UseCollision() : �浹�̺�Ʈ�� Ȱ��ȭ�մϴ�. ���귮�� �������Ƿ� ���� ���� ���� ������Ʈ���� Ȱ��ȭ���ּ���.
PlaceCollision(obj, x, y) : �浹�� üũ�Ͽ� �浹�� �ν��Ͻ��� �ּҸ� ��ȯ�մϴ�. �浹�����ʾ��� �� NULL�� ��ȯ�մϴ�. ���귮�� �����ϰ� �� �� �־� ����� ��õ�����ʽ��ϴ�.

GC->InstanceCreate(obj, x, y) : x, y��ġ�� obj�� �����մϴ�. ���� �� GameObject�����͸� ��ȯ�մϴ�. �� ���� �ʱ⿡ �ν��Ͻ� ������ �ʿ��� ��� �׹�° ���ڰ��� true�� �Է����ݴϴ�.
GC->SetViewPos(pos) : pos��ġ�� �並 �̵��մϴ�. ��� ���� ���� ������ ���̴� ȭ�鿡 ������ �ݴϴ�.
GC->GetViewPos() : �� ��ġ�� ��ȯ�մϴ�. FPOINT�����Դϴ�.
GC->GetMousePos() : ���콺 Ŀ�� ��ġ�� ��ȯ�մϴ�. FPOINT�����Դϴ�.

GC->ScreenShake(amount) : ȭ���� ���ϴ�.

GC->GotoScene(scene ��ȣ) : �ش� ������ �̵��մϴ�.
GC->RestartScene() : ���� ���� ������մϴ�.
GC->NextScene() : ���� ������ �̵��մϴ�.

Sprite::DrawSprite(sprite, frameindex, x, y) : Sprite�� �׸��ϴ�.
Sprite::DrawSpriteFix(sprite, frameindex, x, y) : ȭ�� ��鸲�� ������� ������ ��ġ�� ���� Sprite�� �׸��ϴ�.
Sprite::DrawSpritePart(sprite, frameindex, x, y, left, top, width, height) : Sprite�� ����� ���� �߶� �׸��ϴ�. �߽��� ������ ���� �ʽ��ϴ�.
Sprite::GetWidth(sprite) / ::GetHeight(sprite) : �ش� Sprite�� ũ�⸦ ��ȯ�մϴ�.
Sprite::GetRT() : ���� RenderTarget�� ��ȯ�մϴ�. (Direct2D)
Sprite::SetInterpolation(bool) : ��Ƽ���ϸ������ Ȱ��ȭ�մϴ�. �⺻���� ��Ȱ��ȭ�Դϴ�.
GC->DWriteText(text, pos) : �ش� ��ġ�� �ؽ�Ʈ�� �׸��ϴ�.

*/

GameObject::GameObject()
{
	/*
		��ü�� �⺻�Ӽ��� �ʱ�ȭ�մϴ�.
		��ǥ�� ������ �ִ� �ʱ⼳���� Init�̺�Ʈ���� ó���մϴ�.

		objectIndex �� ���� ������Ʈ�� ���а��Դϴ�. �̰��� �浹 �̺�Ʈ ó���� ���˴ϴ�.
		spriteIndex �� ���� ������Ʈ�� �⺻ ��������Ʈ�Դϴ�.
		bbox �� �浹�ڽ��� �ǹ��մϴ�. ����� 0�̸� �浹�� ��������ʽ��ϴ�.
		imageSpeed �� ������ �̹����� �����Ӵ� �ִϸ��̼� �ӵ��� �ǹ��մϴ�. 1�� ��� ���� �����ӿ� ���� �̹����� �Ѿ�Ե˴ϴ�.
		imageAlpha �� �̸� �Էµ� �̹����� ���İ��Դϴ�.
		depth �� ������Ʈ�� ����/���� �켱������ �ǹ��մϴ�. ���� �������� �ʰ� ó���˴ϴ�.
	*/
	objectIndex = obj::none;
	spriteIndex = spr::none;
	pos = {0, 0};
	bbox = {0, 0, 0, 0};
	destroyQue = false;
	imageIndex = 0;
	depth = 0;
	
}


GameObject::~GameObject()
{
	
}

void GameObject::SetPos(POINT pos)
{
	this->pos = FPOINT({(float)pos.x , (float)pos.y});
}

void GameObject::SetPos(FPOINT pos)
{
	this->pos = FPOINT({ pos.x , pos.y });
}

void GameObject::Draw()
{
	Sprite::DrawSprite(spriteIndex, (int)imageIndex, pos.x, pos.y);
}

void GameObject::Update()
{

}

void GameObject::UserEvent(char number)
{
}

void GameObject::Init()
{
}
void GameObject::UseCollision()
{
	RECT temp_bbox =
	{
		bbox.left + (long)(pos.x),
		bbox.top + (long)(pos.y),
		bbox.right + (long)(pos.x),
		bbox.bottom + (long)(pos.y)
	};

	vector<GameObject*> objectList = GC->GetObjectList();
	for (it = objectList.begin(); it != objectList.end(); ++it)
	{
		if ((*it) == this)
			continue;
		if ((*it)->bbox.top == 0 && (*it)->bbox.bottom == 0)
		{
			continue;
		}

		if (_IsCollision(temp_bbox, (*it)->GetBbox()))
		{
			CollisionEvent((*it)->GetObjType(), (*it));
		}
	}
}

void GameObject::UseCollision(obj object, vector<GameObject*> list)
{
	RECT temp_bbox =
	{
		bbox.left + (long)(pos.x),
		bbox.top + (long)(pos.y),
		bbox.right + (long)(pos.x),
		bbox.bottom + (long)(pos.y)
	};

	vector<GameObject*> objectList = list;
	for (it = objectList.begin(); it != objectList.end(); ++it)
	{
		if ((*it) == this)
			continue;
		if ((*it)->bbox.top == 0 && (*it)->bbox.bottom == 0)
		{
			continue;
		}

		if (_IsCollision(temp_bbox, (*it)->GetBbox()))
		{
			CollisionEvent(object, (*it));
		}
	}
}

void GameObject::UseCollision(GameObject * instance)
{
	RECT temp_bbox =
	{
		bbox.left + (long)(pos.x),
		bbox.top + (long)(pos.y),
		bbox.right + (long)(pos.x),
		bbox.bottom + (long)(pos.y)
	};

	if (_IsCollision(temp_bbox, instance->GetBbox()))
	{
		CollisionEvent(instance->GetObjType(), instance);
	}
}

void GameObject::CollisionEvent(obj object, GameObject * inst)
{

}

obj GameObject::GetObjType()
{
	return objectIndex;
}

GameObject * GameObject::PlaceCollision(obj target, int x, int y)
{
	RECT temp_bbox =
	{
		bbox.left + x,
		bbox.top + y,
		bbox.right + x,
		bbox.bottom + y
	};

	vector<GameObject*> objectList = GC->GetObjectList();
	for (it = objectList.begin(); it != objectList.end(); ++it)
	{
		if ((*it)->GetObjType() == target)
		{
			if (_IsCollision(temp_bbox, (*it)->GetBbox()))
			{
				return (*it);
			}
		}
	}
	return NULL;
}

RECT GameObject::GetBbox()
{
	return RECT({
		bbox.left + (int)pos.x,
		bbox.top + (int)pos.y,
		bbox.right + (int)pos.x,
		bbox.bottom + (int)pos.y,
	});
}

FPOINT GameObject::GetPos()
{
	return pos;
}

bool GameObject::IsDestroyQue()
{
	return destroyQue;
}

void GameObject::InstanceDestroy()
{
	destroyQue = true;
}

void GameObject::DrawSelf()
{
	Sprite::DrawSprite(spriteIndex, (int)imageIndex, pos.x, pos.y);
}

int GameObject::GetDepth()
{
	return depth;
}
