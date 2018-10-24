#include "KeyBoard.h"

KeyBoard* KeyBoard::key_board = NULL;

KeyBoard::KeyBoard()
{

}

KeyBoard * KeyBoard::GetKeyBoard()
{
	if (key_board == 0)
		key_board = new KeyBoard();
	return key_board;
}

void KeyBoard::InitKeyboard(HWND h_wnd)
{
	HRESULT
		hr = DirectInput8Create
		(
			GetModuleHandle(NULL),
			DIRECTINPUT_VERSION,
			IID_IDirectInput8, (VOID**)&direct_input, NULL
		);

	// TO-DO: put in exception handling
	if (FAILED(hr) == true)
		return;

	hr = direct_input->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);

	// TO-DO: put in exception handling
	if (FAILED(hr) == true)
		return;

	hr = keyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr) == true)
		return;

	hr = keyboard->SetCooperativeLevel(h_wnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(hr) == true)
		return;

	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = 1024;

	hr = keyboard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	if (FAILED(hr) == true)
		return;

	hr = keyboard->Acquire();
	if (FAILED(hr) == true)
		return;
}

void KeyBoard::ProcessKeyBoard()
{
	HRESULT hr = keyboard->GetDeviceState(sizeof(key_states), (LPVOID)&key_states);
	if (hr != S_OK)
	{
		hr = keyboard->Acquire();
		keyboard->GetDeviceState(sizeof(key_states), (LPVOID)&key_states);
	}
	// Collect all key states first
	keyboard->GetDeviceState(sizeof(key_states), key_states);

	// Collect all buffered events
	DWORD dwElements = 1024;
	hr = keyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), key_events, &dwElements, 0);

	// Scan through all data, check if the key is pressed or released
	for (DWORD i = 0; i < dwElements; i++)
	{
		int KeyCode = key_events[i].dwOfs;
		int KeyState = key_events[i].dwData;
		if ((KeyState & 0x80) > 0)
			OnKeyDown(KeyCode);
		else
			OnKeyUp(KeyCode);
	}
}

void KeyBoard::OnKeyUp(int KeyCode)
{

}

void KeyBoard::OnKeyDown(int KeyCode)
{

}


int KeyBoard::IsKeyDown(int KeyCode)
{
	return (key_states[KeyCode] & 0x80) > 0;
}



KeyBoard::~KeyBoard()
{
}
