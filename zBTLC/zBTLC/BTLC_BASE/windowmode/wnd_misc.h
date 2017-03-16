#pragma once
#include <stdint.h>
//#include "d3d8/d3d8.h"
#include "d3d8/dinput.h"
#include "../../game_sa/RenderWare.h"
class Interval
{
private:
	unsigned int initial_;

public:
	inline Interval() : initial_(GetTickCount()) { }

	virtual ~Interval() { }

	inline unsigned int value() const
	{
		return GetTickCount() - initial_;
	}
};

class Fps
{
protected:
	unsigned int m_fps;
	unsigned int m_fpscount;
	Interval m_fpsinterval;

public:
	Fps() : m_fps(0), m_fpscount(0) { }

	void update()
	{
		m_fpscount++;

		if (m_fpsinterval.value() > 1000)
		{
			m_fps = m_fpscount;
			m_fpscount = 0;
			m_fpsinterval = Interval();
		}
	}

	unsigned int get() const
	{
		return m_fps;
	}
};

typedef struct _D3DPRESENT_PARAMETERS_D3D9_
{
	UINT                BackBufferWidth;
	UINT                BackBufferHeight;
	D3DFORMAT           BackBufferFormat;
	UINT                BackBufferCount;
	D3DMULTISAMPLE_TYPE MultiSampleType;
	DWORD               MultiSampleQuality;
	D3DSWAPEFFECT       SwapEffect;
	HWND                hDeviceWindow;
	BOOL                Windowed;
	BOOL                EnableAutoDepthStencil;
	D3DFORMAT           AutoDepthStencilFormat;
	DWORD               Flags;
	UINT                FullScreen_RefreshRateInHz;
	UINT                FullScreen_PresentationInterval;
} D3DPRESENT_PARAMETERS_D3D9;

struct IDirectInputDeviceA;
struct IDirectInputA;
struct IDirect3DSwapChain8;

struct GameDxInput
{
	unsigned char __pad00[24];
	IDirectInputA* pInput;
	IDirectInputDeviceA* pInputDevice;
	unsigned char __pad04[8];
};

typedef float RwReal;

struct DisplayMode
{
	int nWidth;
	int nHeight;
	unsigned char __pad00[12];
};