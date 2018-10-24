#pragma once
#include <dinput.h>
#include "Global.h"

class KeyBoard
{
private:
	BYTE					key_states[256];
	DIDEVICEOBJECTDATA		key_events[1024];
	LPDIRECTINPUT8			direct_input;
	LPDIRECTINPUTDEVICE8	keyboard;
	static KeyBoard*		key_board;

public:
	KeyBoard();

	static KeyBoard* GetKeyBoard();
	void InitKeyboard(HWND h_wnd);
	void ProcessKeyBoard();
	virtual void OnKeyUp(int KeyCode);
	virtual void OnKeyDown(int KeyCode);
	int IsKeyDown(int KeyCode);

	~KeyBoard();
};
