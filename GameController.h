#pragma once
#define SHAKE_EASE 14.0f
#define HIGHPASS_AMOUNT 3000.0f
#define HIGHPASS_SPEED 32.0f
#define CURSOR_DISTANCE 5.0f
#define CURSOR_ALPHA_DEFAULT 0.5f
#define BGM_SLOW_TO_NORMAL_SPEED 38.0f

#define SAVE_DATA_FNAME L"score.dat"

#define PLAYER_ISDEAD ((obj_Player*)(GC->Player))->isDead

class GameController : public SingletonBase<GameController>
{
private:
	FPOINT view;
	vector<Scene*> sceneList;
	Scene* nowScene;
	unsigned int nowSceneIndex;
	vector<GameObject*> objectList;
	vector<GameObject*> objectListQue;

	unsigned int SceneChanger;
	POINT mousePos;
	HWND _hWnd;

	ID2D1Factory* pFactory;
	ID2D1HwndRenderTarget *pRenderTarget;

	IDWriteFactory *dwFactory;
	IDWriteTextFormat *dwTextFormat;
	ID2D1Bitmap *surface;

	FPOINT _d2dRate;
	FPOINT shakePos;
	float shakeAmount;
	float blurAlpha;

	float bgmHighpass;
	bool isHighpass;
	float cursor_angle;
	float cursor_dist;
	float cursor_alpha;

	float bgm_frequency;


public:
	unsigned long game_score, game_high_score;
	char life;
	// 게임 충돌 예외
	GameObject* Player, *GameManager;

	vector<GameObject*> vBullet;
	vector<GameObject*> vEnemy;

	//

	GameController();
	~GameController();
	void SetViewPos(POINT pos);
	FPOINT GetViewPos();
	FPOINT GetMousePos();
	GameObject* InstanceCreate(obj object, int x, int y, bool forceCreate = false);	// 게임 오브젝트 추가시

	int GetSceneWidth();
	int GetSceneHeight();
	void RestartScene();
	void NextScene();
	void GotoScene(unsigned int scene_index);

	LRESULT MainProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	vector<GameObject*>& GetObjectList();
	void DWriteText(TCHAR* text, FPOINT pos);
	FPOINT GetShakePos();
	void ScreenShake(int amount = 4);
	void UpdateMain();
	void SetBlurAlpha(float amount);
	void SetHighpass(bool highpass);
	void UserEvent(GameObject* inst, int eventNum);
	void SetBgmSlow();

	void LoadHighScore();
	void SaveHighScore();

private:
	void InitGame();
	void InitScene();	// 씬 추가
	void LoadSprite();	// 스프라이트 추가
	void LoadSound();	// 사운드 추가
	void SetShakePos();
	void UpdateMousePos();
	void AddQueInstance(GameObject* obj);
	void ReleaseGameInstanceAll();
	void SetFromQueInstance();
	void CheckDestroyInstance();
	void ChangeScene();
	void D2DDraw();
	void UpdateHighpass();
	void InitDWrite(TCHAR* font, float size, IDWriteFactory **factory, IDWriteTextFormat **format);

};