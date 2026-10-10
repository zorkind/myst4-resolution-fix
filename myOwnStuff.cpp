#include "StdAfx.h"
#include ".\myownstuff.h"
//#include "memory.h"
//#include "image.h"
//#include "di.h"
//#include "mesh.h"
//#include "ini.h"
#include <stdio.h>


CmyOwnStuff::CmyOwnStuff(IDirect3DDevice9 *pD3DDevice)
{
   extern HINSTANCE gl_hThisInstance;
	
   m_pD3DDevice = pD3DDevice;

   m_pBackgroundSprite  = NULL;
   m_pBackgroundTexture = NULL;



}

CmyOwnStuff::~CmyOwnStuff(void)
{
	if (m_pBackgroundSprite) m_pBackgroundSprite->Release();
	if (m_pBackgroundTexture) m_pBackgroundTexture->Release();

}

void CmyOwnStuff::Render(void)
{


}

void CmyOwnStuff::OnLostDevice(void)
{
	m_pBackgroundSprite->OnLostDevice();

}

void CmyOwnStuff::OnResetDevice(void)
{
	m_pBackgroundSprite->OnResetDevice();

}


