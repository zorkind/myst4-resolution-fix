#include <dinput.h>

#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }

#define SAMPLE_BUFFER_SIZE 16

LPDIRECTINPUT8       g_pDI       = NULL;        
LPDIRECTINPUTDEVICE8 g_pKeyboard = NULL;
LPDIRECTINPUTDEVICE8 g_pMouse	 = NULL;  
LPDIRECTINPUTDEVICE8 g_pJoystick = NULL; 

    BYTE diks[256];		  // DirectInput keyboard state buffer 
	DIMOUSESTATE2 dims2;      // DirectInput mouse state structure
	DIJOYSTATE2 js;           // DInput joystick state 

void FreeDirectInput()
{
    // Unacquire the device one last time just in case 
    // the app tried to exit while the device is still acquired.
    if( g_pKeyboard ) 
        g_pKeyboard->Unacquire();
	if( g_pMouse ) 
        g_pMouse->Unacquire();
    if( g_pJoystick ) 
        g_pJoystick->Unacquire();

    // Release any DirectInput objects.
    SAFE_RELEASE( g_pKeyboard );
    SAFE_RELEASE( g_pMouse );
	SAFE_RELEASE( g_pJoystick );
    SAFE_RELEASE( g_pDI );
}
BOOL CALLBACK EnumJoysticksCallback( const DIDEVICEINSTANCE* pdidInstance,
                                     VOID* pContext )
{
    HRESULT hr;

    // Obtain an interface to the enumerated joystick.
    hr = g_pDI->CreateDevice( pdidInstance->guidInstance, &g_pJoystick, NULL );

    // If it failed, then we can't use this joystick. (Maybe the user unplugged
    // it while we were in the middle of enumerating it.)
    if( FAILED(hr) ) 
        return DIENUM_CONTINUE;

    // Stop enumeration. Note: we're just taking the first joystick we get. You
    // could store all the enumerated joysticks and let the user pick.
    return DIENUM_STOP;
}
BOOL CALLBACK EnumObjectsCallback( const DIDEVICEOBJECTINSTANCE* pdidoi,
                                   VOID* pContext )
{

    // For axes that are returned, set the DIPROP_RANGE property for the
    // enumerated axis in order to scale min/max values.
    if( pdidoi->dwType & DIDFT_AXIS )
    {
        DIPROPRANGE diprg; 
        diprg.diph.dwSize       = sizeof(DIPROPRANGE); 
        diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER); 
        diprg.diph.dwHow        = DIPH_BYID; 
        diprg.diph.dwObj        = pdidoi->dwType; // Specify the enumerated axis
        diprg.lMin              = -1000; 
        diprg.lMax              = +1000; 
    
        // Set the range for the axis
        if( FAILED( g_pJoystick->SetProperty( DIPROP_RANGE, &diprg.diph ) ) ) 
            return DIENUM_STOP;
         
    }

    return DIENUM_CONTINUE;
}

void PollDevices()
{
    HRESULT hr;   

	//KEYBOARD
    if( g_pKeyboard ) 
	{
		ZeroMemory( diks, sizeof(diks) );
		hr = g_pKeyboard->GetDeviceState( sizeof(diks), diks );
		if( FAILED(hr) ) 
		{
			g_pKeyboard->Acquire();
		}
	}

	//MOUSE
    if( g_pMouse ) 
	{
		ZeroMemory( &dims2, sizeof(dims2) );
		hr = g_pMouse->GetDeviceState( sizeof(DIMOUSESTATE2), &dims2 );

		if( FAILED(hr) ) 
			g_pMouse->Acquire();
	}

	//JOYSTICK
    if( g_pJoystick ) 
	{
		hr = g_pJoystick->Poll(); 
		if( FAILED(hr) )  
		{
			g_pJoystick->Acquire();

		}
		else
		{
			g_pJoystick->GetDeviceState( sizeof(DIJOYSTATE2), &js );
		}
	}
}
bool KeyDown(DWORD KeyID)
{
	//Check keyboard
	if (KeyID < 256)
	{
		if( g_pKeyboard ) 
			if ( diks[KeyID] & 0x80 )
				return true;
	}
	//Check mouse
	if (KeyID > 256 & KeyID < 265)
	{
		if( g_pMouse ) 
			if ( dims2.rgbButtons[KeyID - 256] & 0x80 )
				return true;
	}
	//Check joystick
	if (KeyID > 264)
	{
		if( g_pJoystick ) 
			if ( js.rgbButtons[KeyID - 264] & 0x80 )
				return true;
	}
	return false;
	//max 296
}

HRESULT InitDirectInput( HWND hDlg )
{
    HRESULT hr; 
  
    FreeDirectInput();


    // Create a DInput object
    if( FAILED( hr = DirectInput8Create( GetModuleHandle(NULL), DIRECTINPUT_VERSION, 
                                         IID_IDirectInput8, (VOID**)&g_pDI, NULL ) ) )
        return hr;

	//Create Keyboard
    g_pDI->CreateDevice( GUID_SysKeyboard, &g_pKeyboard, NULL );
	if( g_pKeyboard )
	{
		g_pKeyboard->SetDataFormat( &c_dfDIKeyboard );
		g_pKeyboard->SetCooperativeLevel( hDlg, DISCL_NONEXCLUSIVE|DISCL_BACKGROUND );
		g_pKeyboard->Acquire();
	}

	//Create Mouse
    g_pDI->CreateDevice( GUID_SysMouse, &g_pMouse, NULL );
	if( g_pMouse )
	{
		g_pMouse->SetDataFormat( &c_dfDIMouse2 );
		g_pMouse->SetCooperativeLevel( hDlg, DISCL_NONEXCLUSIVE|DISCL_BACKGROUND );
		g_pMouse->Acquire();
	}

	//Create Joystick
	g_pDI->EnumDevices( DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, NULL, DIEDFL_ATTACHEDONLY );
    if( g_pJoystick )
	{
		g_pJoystick->SetDataFormat( &c_dfDIJoystick2 );
		g_pJoystick->SetCooperativeLevel( hDlg, DISCL_NONEXCLUSIVE|DISCL_BACKGROUND );
		g_pJoystick->EnumObjects( EnumObjectsCallback, (VOID*)hDlg, DIDFT_ALL );
		g_pJoystick->Acquire();
	}

	return S_OK;

}
