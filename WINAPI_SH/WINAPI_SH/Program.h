#pragma once
class Program
{
public:
	Program();
	~Program();

	void Update();
	void Render(HDC hdc);

	static HDC backBuffer;

private:
	string _curScene;
	unordered_map<string, shared_ptr<Scene>> _sceneTable;

	HBITMAP _hBitMap;
};

