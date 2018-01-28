#pragma once
#include <bitset>

#define KEYMAX 256

class KeyController : public SingletonBase<KeyController>
{
private:
	bitset<KEYMAX> _keyUp;
	bitset<KEYMAX> _keyDown;

public:
	KeyController();
	~KeyController();

	void Init();
	bitset<KEYMAX> GetKeyUp();
	bitset<KEYMAX> GetKeyDown();
	void SetKeyUp(const unsigned char key, const bool state);
	void SetKeyDown(const unsigned char key, const bool state);

	bool isKeyPressed(const unsigned char key);
	bool isKeyDown(const unsigned char key);
	bool isKeyReleased(const unsigned char key);

};