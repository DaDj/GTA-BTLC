#pragma once
inline bool KeyPressed(unsigned int keyCode) {
	return (GetKeyState(keyCode) & 0x8000) != 0;
}