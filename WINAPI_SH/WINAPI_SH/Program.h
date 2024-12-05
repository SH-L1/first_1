#pragma once
class Program
{
public:
	Program();
	~Program();

	void Update();
	void Render(HDC hdc);

private:
	string _curScene;
	unordered_map<string, shared_ptr<Scene>> _sceneTable;
};

