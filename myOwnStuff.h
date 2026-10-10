#pragma once
#include <d3dx9core.h>

class CmyOwnStuff
{
public:
	CmyOwnStuff(IDirect3DDevice9 *pD3DDevice);
	~CmyOwnStuff(void);
	void Render(void);
	void OnLostDevice(void);
	void OnResetDevice(void);

	IDirect3DDevice9*  m_pD3DDevice;
	ID3DXSprite*	   m_pBackgroundSprite;
	IDirect3DTexture9* m_pBackgroundTexture; 


};
