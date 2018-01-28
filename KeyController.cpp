#include "stdafx.h"
#include "KeyController.h"


KeyController::KeyController()
{
}


KeyController::~KeyController()
{
}

void KeyController::Init()
{
	for (int i = 0; i < KEYMAX; i++)
	{
		GetKeyUp().set(i, false);
		GetKeyDown().set(i, false);
	}
}

bitset<KEYMAX> KeyController::GetKeyUp()
{
	return _keyUp;
}

bitset<KEYMAX> KeyController::GetKeyDown()
{
	return _keyDown;
}

void KeyController::SetKeyUp(const unsigned char key, const bool state)
{
	_keyUp.set(key, state);
}

void KeyController::SetKeyDown(const unsigned char key, const bool state)
{
	_keyDown.set(key, state);
}

bool KeyController::isKeyPressed(const unsigned char key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!GetKeyDown()[key])
		{
			SetKeyDown(key, true);
			return true;
		}
	}
	else
	{
		SetKeyDown(key, false);
	}
	return false;
}

bool KeyController::isKeyReleased(const unsigned char key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		SetKeyUp(key, true);
	}
	else
	{
		if (GetKeyUp()[key])
		{
			SetKeyUp(key, false);
			return true;
		}
	}

	return false;
}

bool KeyController::isKeyDown(const unsigned char key)
{
	if (GetAsyncKeyState(key) & 0x8000)
		return true;
	else
		return false;
}
