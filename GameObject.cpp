#include "stdafx.h"
#include "GameObject.h"

/*

GameObject 사용 가능 함수

--
이벤트 (가상 함수 상속)

Init : 초기 생성시에 작동합니다.
Update : 인스턴스가 제거 될 때까지 반복합니다.
Draw : 이 곳에서 객체를 그립니다.
CollisionEvent : 인스턴스 충돌 이벤트입니다. object로 충돌한 obj 종류를 받고 inst로 충돌한 인스턴스의 주소값을 받습니다.
UserEvent(number) : 사용자 이벤트를 정의합니다.

--

InstanceDestroy() : 인스턴스 삭제. 절대 다른 방법으로 지우지 말고 이 함수 이용할 것.
DrawSelf() : mySprite를 내 위치에 그리기. 애니메이션은 자동으로 재생.

KEY->isKeyPressed(vk) : vk키가 호출 시점에 누른 상태인지 bool 타입으로 반환합니다.
KEY->isKeyDown(vk) : vk키가 계속 눌리고있는지 bool 타입으로 반환합니다.
KEY->isKeyReleased(vk) : vk키가 때졌는지 bool 타입으로 반환합니다.

UseCollision() : 충돌이벤트를 활성화합니다. 연산량이 많아지므로 비교적 수가 적은 오브젝트에서 활성화해주세요.
PlaceCollision(obj, x, y) : 충돌을 체크하여 충돌한 인스턴스의 주소를 반환합니다. 충돌하지않았을 시 NULL을 반환합니다. 연산량이 과다하게 늘 수 있어 사용을 추천하지않습니다.

GC->InstanceCreate(obj, x, y) : x, y위치에 obj를 생성합니다. 생성 된 GameObject포인터를 반환합니다. 씬 생성 초기에 인스턴스 생성이 필요한 경우 네번째 인자값을 true로 입력해줍니다.
GC->SetViewPos(pos) : pos위치로 뷰를 이동합니다. 뷰는 현재 게임 내에서 보이는 화면에 영향을 줍니다.
GC->GetViewPos() : 뷰 위치를 반환합니다. FPOINT단위입니다.
GC->GetMousePos() : 마우스 커서 위치를 반환합니다. FPOINT단위입니다.

GC->ScreenShake(amount) : 화면을 흔듭니다.

GC->GotoScene(scene 번호) : 해당 씬으로 이동합니다.
GC->RestartScene() : 현재 씬을 재시작합니다.
GC->NextScene() : 다음 씬으로 이동합니다.

Sprite::DrawSprite(sprite, frameindex, x, y) : Sprite를 그립니다.
Sprite::DrawSpriteFix(sprite, frameindex, x, y) : 화면 흔들림과 상관없이 고정된 위치를 가진 Sprite를 그립니다.
Sprite::DrawSpritePart(sprite, frameindex, x, y, left, top, width, height) : Sprite를 사이즈에 맞춰 잘라서 그립니다. 중심점 영향을 받지 않습니다.
Sprite::GetWidth(sprite) / ::GetHeight(sprite) : 해당 Sprite의 크기를 반환합니다.
Sprite::GetRT() : 현재 RenderTarget을 반환합니다. (Direct2D)
Sprite::SetInterpolation(bool) : 앤티에일리어싱을 활성화합니다. 기본값은 비활성화입니다.
GC->DWriteText(text, pos) : 해당 위치에 텍스트를 그립니다.

*/

GameObject::GameObject()
{
	/*
		객체의 기본속성을 초기화합니다.
		좌표에 영향이 있는 초기설정은 Init이벤트에서 처리합니다.

		objectIndex 는 현재 오브젝트의 구분값입니다. 이것은 충돌 이벤트 처리시 사용됩니다.
		spriteIndex 는 현재 오브젝트의 기본 스프라이트입니다.
		bbox 는 충돌박스를 의미합니다. 사이즈가 0이면 충돌에 영향받지않습니다.
		imageSpeed 는 설정된 이미지의 프레임당 애니메이션 속도를 의미합니다. 1일 경우 다음 프레임에 다음 이미지로 넘어가게됩니다.
		imageAlpha 는 미리 입력된 이미지의 알파값입니다.
		depth 는 오브젝트의 연산/렌더 우선순위를 의미합니다. 값이 낮을수록 늦게 처리됩니다.
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
