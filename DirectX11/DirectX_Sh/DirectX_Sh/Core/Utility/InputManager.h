#pragma once

#define KEY_MAX 255

class InputManager
{
private:
	enum State
	{
		NONE,
		DOWN,
		UP,
		PRESS
	};
	
	InputManager();
	~InputManager();

public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new InputManager();
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static InputManager* Instance()
	{
		if (_instance != nullptr)
			return _instance;
	}

	void Update();

	bool Down(UINT key) { return _stateMap[key] == DOWN; }
	bool Up(UINT key) { return _stateMap[key] == UP; }
	bool Press(UINT key) { return _stateMap[key] == PRESS; }

	void SetMousePos(const Vector& pos) { mousePos = pos; }
	Vector GetMousePos() { return mousePos; }
	Vector GetScreenMousePos() { return mousePos - CENTRE; }

private:
	static InputManager* _instance;

	byte _curState[KEY_MAX];
	byte _oldState[KEY_MAX];
	byte _stateMap[KEY_MAX];

	Vector mousePos;
};