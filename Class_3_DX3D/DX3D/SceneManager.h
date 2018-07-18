#pragma once

#define g_pSceneManager SceneManager::GetInstance()

class IScene;

class SceneManager
{
private:
	SceneManager();
	~SceneManager();

public:
	static SceneManager* GetInstance()
	{
		static SceneManager instance;
		return &instance;
	}

	vector<IScene*> m_vecScene;

	IScene* m_pCurrScene;
	//IScene* m_pLoadingScene;

	void Init();
	void Destroy();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void SetCurrentScene(size_t index);

	void calcLoadingPercentage(int currentLoading, int maxLoading);

	string m_pCurrSceneString;
	float m_pLoadingPercentage;
	string m_pLoadingString;

};

