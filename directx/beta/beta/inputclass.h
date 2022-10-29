#ifndef _INPUTCLASS_H_
#define _INPUTCLASS_H_
#define DIRECTINPUT_VERSION 0x0800

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include <dinput.h>

class InputManager
{
public:
	InputManager();
	InputManager(const InputManager&);
	~InputManager();

	bool Initialize(HINSTANCE, HWND, int, int);
	void Shutdown();
	bool Frame();

	bool IsEscapePressed();
	static bool IsKeyPressed(int);
	static bool IsMouseAxisPressed();

public:
	static float mouseIX;
	static float mouseIY;
	static DIMOUSESTATE m_currMouseState;
	static DIMOUSESTATE m_oldMouseState;

private:
	bool ReadKeyboard();
	bool ReadMouse();
	void ProcessInput();

private:
	IDirectInput8* m_directInput;
	IDirectInputDevice8* m_keyboard;
	IDirectInputDevice8* m_mouse;

	static int m_mouseX;
	static int m_mouseY;
	static unsigned char m_keyboardState[256];

	int m_screenWidth, m_screenHeight;
};

#endif