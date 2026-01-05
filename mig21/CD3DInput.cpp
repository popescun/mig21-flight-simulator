#include "CD3DInput.h"
#include "Fizica.h"

extern Fizica* pFizica;
LPDIRECTINPUT8  pD3DInputJoystick; 
LPDIRECTINPUTDEVICE8 pJoystick;
const DIDEVICEINSTANCE* pDIDInstance;
BOOL CALLBACK    EnumJoysticksCallback( const DIDEVICEINSTANCE* pdidInstance, VOID* pContext );
BOOL CALLBACK EnumAxesCallback( const DIDEVICEOBJECTINSTANCE* pdidoi,VOID* pContext );

CD3DInput::CD3DInput()
{
	pD3DInput=NULL;
	pSysKeyboardDevice=NULL;	
	lXVechi=0;
	lYVechi=0;	
	medieDataEleroane=0.0f;
	medieDataStabilizator=0.0f;
	contorDataStabilizator=0;
	contorDataEleroane=0;
}
//------------------------------------------------------------------------
HRESULT CD3DInput::CreateD3DInputObject(HINSTANCE  hInstance,HWND hWnd)         
{
	// HINSTANCE  g_hinst; // initialized earlier

	HRESULT hr; 	
	hr = DirectInput8Create(hInstance, 
							DIRECTINPUT_VERSION, 
							IID_IDirectInput8, 
							(void**)&pD3DInputJoystick, NULL); 	

	pD3DInput = pD3DInputJoystick; //todo(Nicu): fix it
	
	if FAILED(hr) 
	{ 
		// DirectInput not available; take appropriate action 
		MessageBox(hWnd,"DirectInputObject failed", NULL, MB_OK); 
		return E_FAIL;

	}
	else
	{
		//MessageBox(hWnd,"DirectInputObject successed", NULL, MB_OK); 
		return S_OK;
	}
} 

//KEYBOARD
//------------------------------------------------------------------------
HRESULT CD3DInput::CreateSysKeyboardDevice(HWND hWnd)         
{
	HRESULT hr; 	
	hr = pD3DInput->CreateDevice(GUID_SysKeyboard, &pSysKeyboardDevice, NULL); 
	if FAILED(hr) 
	{ 		
		MessageBox(hWnd,"SysKeyboardDevice failed", NULL, MB_OK); 
		return E_FAIL; 
	} 
	else
	{
		//MessageBox(hWnd,"SysKeyboardDevice successed", NULL, MB_OK); 
		hr = pSysKeyboardDevice->SetDataFormat(&c_dfDIKeyboard); 
		if FAILED(hr) 
		{ 		
			MessageBox(hWnd,"Set data format failed", NULL, MB_OK); 
			DI_Term();
			return E_FAIL; 
		} 
		else
		{
			//MessageBox(hWnd,"Set data format successed", NULL, MB_OK); 
			return S_OK;
		}

		return S_OK;
	}
}
//------------------------------------------------------------------------
HRESULT CD3DInput::SetSysKeyboardBehavior(HWND hWnd)         
{
	// Set the cooperative level 
	HRESULT hr; 	
	hr = pSysKeyboardDevice->SetCooperativeLevel(hWnd, 
							DISCL_FOREGROUND | DISCL_NONEXCLUSIVE); 
 
	if FAILED(hr) 
	{ 
		MessageBox(hWnd,"Set keyboard behavior failed", NULL, MB_OK); 
		DI_Term(); 
		return E_FAIL; 
	} 
	else
	{
		//MessageBox(hWnd,"Set keyboard behavior successed", NULL, MB_OK); 
		return S_OK; 
	}	
}
//------------------------------------------------------------------------
void CD3DInput::ProcessSysKeyboardInput(HWND hWnd) 
{ 
	if (pSysKeyboardDevice) pSysKeyboardDevice->Acquire(); 

    #define KEYDOWN(name,key) (name[key] & 0x80) 
	//#define KEYUP(name,key) ((name[key] & 0x80) 
 
    char     buffer[256]; 
    HRESULT  hr; 
 
    hr = pSysKeyboardDevice->GetDeviceState(sizeof(buffer),(LPVOID)&buffer); 
    if FAILED(hr) 
    { 
         // If it failed, the device has probably been lost. 
         // Check for (hr == DIERR_INPUTLOST) 
         // and attempt to reacquire it here. 
         return; 
    } 

	
		
	if (KEYDOWN(buffer,DIK_LEFT))
	{
		//button pressed. 
		//MessageBox(hWnd,"Butonul minus a fost apasat", NULL, MB_OK); 				        					
		pFizica->flagBracareEleroaneStangaPress=true;
		pFizica->flagBracareEleroaneStangaRelease=false;
		pFizica->flagBracareEleroaneDreaptaPress=false;
		pFizica->flagBracareEleroaneDreaptaRelease=false;		
	}
	
	if (!KEYDOWN(buffer,DIK_LEFT) && pFizica->flagBracareEleroaneStangaPress==true)	
	{
		//button released. 
		//MessageBox(hWnd,"Butonul minus a fost eliberat", NULL, MB_OK); 				        
		pFizica->flagBracareEleroaneStangaPress=false;
		pFizica->flagBracareEleroaneStangaRelease=true;
		pFizica->flagBracareEleroaneDreaptaPress=false;
		pFizica->flagBracareEleroaneDreaptaRelease=false;		
	}

	
	if (KEYDOWN(buffer,DIK_RIGHT))
	{
		//button pressed. 
		//MessageBox(hWnd,"Butonul minus a fost apasat", NULL, MB_OK); 				        					
		pFizica->flagBracareEleroaneDreaptaPress=true;
		pFizica->flagBracareEleroaneDreaptaRelease=false;
		pFizica->flagBracareEleroaneStangaPress=false;
		pFizica->flagBracareEleroaneStangaRelease=false;																
	}
	
	if (!KEYDOWN(buffer,DIK_RIGHT) && pFizica->flagBracareEleroaneDreaptaPress==true)
	{
		//button pressed. 
		//MessageBox(hWnd,"Butonul minus a fost apasat", NULL, MB_OK); 				        					
		pFizica->flagBracareEleroaneDreaptaPress=false;
		pFizica->flagBracareEleroaneDreaptaRelease=true;
		pFizica->flagBracareEleroaneStangaPress=false;
		pFizica->flagBracareEleroaneStangaRelease=false;																
	}
		    	     
} 
//------------------------------------------------------------------------
void CD3DInput::DI_Term() 
{ 
    if (pD3DInput) 
    { 
        if (pSysKeyboardDevice) 
        { 
        // Always unacquire device before calling Release(). 
            pSysKeyboardDevice->Unacquire(); 
            pSysKeyboardDevice->Release();
            pSysKeyboardDevice= NULL; 
        } 
        pD3DInput->Release();
        pD3DInput = NULL; 
    } 
} 

//JOYSTICK
//------------------------------------------------------------------------
HRESULT CD3DInput::EnumDevices(HWND hWnd) 
{
	//g_pDI is an initialized pointer to IDirectInput8	
	HRESULT hr;

	//pD3DInputJoystick=pD3DInput;
	if(FAILED(pD3DInputJoystick->EnumDevices(DI8DEVCLASS_GAMECTRL,EnumJoysticksCallback,
						   (VOID*)hWnd, DIEDFL_ATTACHEDONLY)))
	return hr;	
		
	if (FAILED(hr = pJoystick->SetDataFormat(&c_dfDIJoystick)))
		return hr;

	
	if (FAILED(hr = pJoystick->SetCooperativeLevel(hWnd, 
                    DISCL_EXCLUSIVE | DISCL_FOREGROUND)))
		return hr;		

	DIDEVCAPS diDevCaps;
	diDevCaps.dwSize = sizeof(DIDEVCAPS);
	if (FAILED(hr = pJoystick->GetCapabilities(&diDevCaps)))		
		return hr;	

	if ( FAILED( hr = pJoystick->EnumObjects( EnumAxesCallback, 
                                              (VOID*)hWnd, DIDFT_AXIS ) ) )	
        return hr;
	    

    return S_OK;
}
//-----------------------------------------------------------------------------
HRESULT CD3DInput::UpdateInputState(HWND hWnd)
{	
    HRESULT     hr;
    //CHAR        strText[128]; // Device state text
    DIJOYSTATE js;           // Direct Input joystick state 
    //CHAR*       str;

    if (NULL == pJoystick) 
        return S_OK;

    // Poll the device to read the current state
    hr = pJoystick->Poll(); 
    if (FAILED(hr)) 
	{
		hr = pJoystick->Acquire();
		while(hr == DIERR_INPUTLOST) 
			hr = pJoystick->Acquire();
		return S_OK; 
	}
	

	pFizica->flagJoystick=true;			
    hr = pJoystick->GetDeviceState(sizeof(DIJOYSTATE), &js);
	
    if (FAILED(hr))
        return hr; 
	else
	{		
		
		/*if(contorDataEleroane<4)
		{
			medieDataEleroane+=js.lX;
			contorDataEleroane++;
		}
		else
		{
			medieDataEleroane=medieDataEleroane/4.0f;
			contorDataEleroane=0;*/
			//pFizica->unghiBracareEleroane=(float)(-medieDataEleroane*20.0f/2000000000);
			
			
			if(js.lX>-2000000000/2 && js.lX<2000000000/2)
			{

				pFizica->pasEleroaneDecrease=1.0f;
				if(js.lX>0)
					pFizica->pasEleroaneIncrease=(float)(js.lX*8.5f/2000000000);//temp
				else
					pFizica->pasEleroaneIncrease=-(float)(js.lX*1.5f/2000000000);

				/*if(pFizica->flagFlapsLanding)
				{
					pFizica->pasEleroaneDecrease=1.0f;
					pFizica->pasEleroaneIncrease=(float)(js.lX*0.1f/2000000000);
				}*/
			}
			else
			{
				pFizica->pasEleroaneDecrease=1.0f;
				if(js.lX>0)
					pFizica->pasEleroaneIncrease=(float)(js.lX*8.5f/2000000000);
				else
					pFizica->pasEleroaneIncrease=-(float)(js.lX*3.0f/2000000000);

				/*if(pFizica->flagFlapsLanding)
				{
					pFizica->pasEleroaneDecrease=1.0f;
					pFizica->pasEleroaneIncrease=-(float)(js.lX*0.1f/2000000000);
				}*/
			}
						

			if(js.lX>=0 && js.lX>-pFizica->unghiBracareEleroane)//lXVechi)// && pFizica->tzMig!=0.0f)
			{								
				pFizica->rlx=0.0f;
				pFizica->rly=0.0f;
				pFizica->rlz=1.0f;																								
			
				if(pFizica->unghiBracareEleroane>(float)(-js.lX*20.0f/2000000000))//-20.0f)			
				{
					if(pFizica->unghiBracareEleroane>0.0f)			
						pFizica->unghiBracareEleroane-=pFizica->pasEleroaneDecrease;
					else
						pFizica->unghiBracareEleroane-=pFizica->pasEleroaneIncrease;		
				}
				else
					pFizica->unghiBracareEleroane=(float)(-js.lX*20.0f/2000000000);//-20.0f;

			}		

			if(js.lX>=0 && js.lX<-pFizica->unghiBracareEleroane)//lXVechi)
			{
				pFizica->rlx=0.0f;
				pFizica->rly=0.0f;
				pFizica->rlz=1.0f;			
				
				if(pFizica->unghiBracareEleroane>-1.0f && pFizica->unghiBracareEleroane<1.0f)
					pFizica->unghiBracareEleroane=0.0f;
				else
					if(pFizica->unghiBracareEleroane<0.0f)
						pFizica->unghiBracareEleroane+=pFizica->pasEleroaneDecrease;
					else
						if(pFizica->unghiBracareEleroane>0.0f)
							pFizica->unghiBracareEleroane-=pFizica->pasEleroaneDecrease;
			}

			if(js.lX<=0 && js.lX<-pFizica->unghiBracareEleroane)//<lXVechi)
			{								
				pFizica->rlx=0.0f;
				pFizica->rly=0.0f;
				pFizica->rlz=1.0f;										
				
				if(pFizica->unghiBracareEleroane<(float)(-js.lX*20.0f/2000000000))//20.0f)
				{
					if(pFizica->unghiBracareEleroane<0.0f)
						pFizica->unghiBracareEleroane+=pFizica->pasEleroaneDecrease;
					else
						pFizica->unghiBracareEleroane+=pFizica->pasEleroaneIncrease;				
				}
				else
					pFizica->unghiBracareEleroane=(float)(-js.lX*20.0f/2000000000);//20.0f;
			}

			if(js.lX<=0 && js.lX>-pFizica->unghiBracareEleroane)//lXVechi)
			{
				pFizica->rlx=0.0f;
				pFizica->rly=0.0f;
				pFizica->rlz=1.0f;				
				
				if(pFizica->unghiBracareEleroane>-1.0f && pFizica->unghiBracareEleroane<1.0f)
					pFizica->unghiBracareEleroane=0.0f;
				else
					if(pFizica->unghiBracareEleroane>0.0f)
						pFizica->unghiBracareEleroane-=pFizica->pasEleroaneDecrease;			
					else
						if(pFizica->unghiBracareEleroane<0.0f)
							pFizica->unghiBracareEleroane+=pFizica->pasEleroaneDecrease;
			}
		
		//	medieDataEleroane=0.0f;
		//}
		
		//stabilzator	
		/*if(contorDataStabilizator<=0)
		{
			medieDataStabilizator+=js.lY;
			contorDataStabilizator++;
		}
		else
		{
			medieDataStabilizator=medieDataStabilizator/1.0f;
			contorDataStabilizator=0;*/
			
			if(pFizica->vMig<=455.0f || (pFizica->vMig>455.0f && pFizica->altM>=10000.0f))
			{
				pFizica->unghiBracareMinim=14.0f;
				pFizica->unghiBracareMaxim=28.0f;
				pFizica->rataEfortBracare=0.6f;//0.375f;
				//efort la mansa mic=>rata mare de modificare
			}
			
			if((pFizica->vMig>455.0f && pFizica->vMig<=992.0f) && pFizica->altM<4500.0f)
			{
				pFizica->unghiBracareMinim=(float)(14.0f*455.0f/pFizica->vMig);
				pFizica->unghiBracareMaxim=(float)(28.0f*455.0f/pFizica->vMig);
				pFizica->rataEfortBracare=(float)(0.375f*455.0f/pFizica->vMig);
				//efort la mansa creste=>rata variata(descrescatoare) de modificare
			}

			if(pFizica->vMig>992.0f) 
			{
				pFizica->unghiBracareMinim=4.0f;
				pFizica->unghiBracareMaxim=15.0f;
				pFizica->rataEfortBracare=0.2f;
				//efort la mansa maxim=>rata minima de modificare
			}
																									
			
			if(js.lY>=0 && js.lY>pFizica->unghiBracareStabilizator)
			{
				pFizica->rtx=1.0f;
				pFizica->rty=0.0f;
				pFizica->rtz=0.0f;	
				
				if(pFizica->unghiBracareStabilizator<(float)(js.lY*pFizica->unghiBracareMaxim/2000000000))
					pFizica->unghiBracareStabilizator+=pFizica->rataEfortBracare;
				//else
				//	pFizica->unghiBracareStabilizator=(float)(js.lY*pFizica->unghiBracareMaxim/2000000000);

			}

			if(js.lY>=0 && js.lY<pFizica->unghiBracareStabilizator)
			{
				pFizica->rtx=1.0f;
				pFizica->rty=0.0f;
				pFizica->rtz=0.0f;

				if(pFizica->unghiBracareStabilizator>-1.0f && pFizica->unghiBracareStabilizator<1.0f)
					pFizica->unghiBracareStabilizator=0.0f;
				else
					if(pFizica->unghiBracareStabilizator<0.0f)
						pFizica->unghiBracareStabilizator-=-pFizica->rataEfortBracare;
					else
						if(pFizica->unghiBracareStabilizator>0.0f)
							pFizica->unghiBracareStabilizator-=pFizica->rataEfortBracare;
			}

				
			if(js.lY<=0 && js.lY<pFizica->unghiBracareStabilizator)
			{
				pFizica->rtx=1.0f;
				pFizica->rty=0.0f;
				pFizica->rtz=0.0f;	
				
				if(pFizica->unghiBracareStabilizator>(float)(js.lY*pFizica->unghiBracareMinim/2000000000))
					pFizica->unghiBracareStabilizator+=-pFizica->rataEfortBracare;
				//else
				//	pFizica->unghiBracareStabilizator=(float)(js.lY*pFizica->unghiBracareMinim/2000000000);
			}	
				

			if(js.lY<=0 && js.lY>pFizica->unghiBracareStabilizator)
			{
				pFizica->rtx=1.0f;
				pFizica->rty=0.0f;
				pFizica->rtz=0.0f;

				if(pFizica->unghiBracareStabilizator>-1.0f && pFizica->unghiBracareStabilizator<1.0f)
					pFizica->unghiBracareStabilizator=0.0f;
				else
					if(pFizica->unghiBracareStabilizator>0.0f)
						pFizica->unghiBracareStabilizator-=pFizica->rataEfortBracare;
					else
						if(pFizica->unghiBracareStabilizator<0.0f)
							pFizica->unghiBracareStabilizator-=-pFizica->rataEfortBracare;
			}

			/*if(js.lY!=0)
				lYVechi=js.lY;
			else
				lYVechi=-lYVechi;*/

			//medieDataStabilizator=0.0f;
		//}


		/*pFizica->rlx=0.0f;
		pFizica->rly=0.0f;
		pFizica->rlz=1.0f;	

		if(contorDataEleroane<5)
		{
			medieDataEleroane+=js.lX;
			contorDataEleroane++;
		}
		else
		{
			medieDataEleroane=medieDataEleroane/5.0f;
			contorDataEleroane=0;
			pFizica->unghiBracareEleroane=(float)(-medieDataEleroane*20.0f/2000000000);
			medieDataEleroane=0.0f;
		}

		*/

		/*
		if(pFizica->vMig<=455.0f || (pFizica->vMig>455.0f && pFizica->altM>=10000.0f))
		{
			pFizica->unghiBracareMinim=14.0f;
			pFizica->unghiBracareMaxim=28.0f;
			//pFizica->rataEfortBracare=0.6f;//0.375f;
			//efort la mansa mic=>rata mare de modificare
		}
		
		if((pFizica->vMig>455.0f && pFizica->vMig<=992.0f) && pFizica->altM<4500.0f)
		{
			pFizica->unghiBracareMinim=(float)(14.0f*455.0f/pFizica->vMig);
			pFizica->unghiBracareMaxim=(float)(28.0f*455.0f/pFizica->vMig);
			//pFizica->rataEfortBracare=(float)(0.375f*455.0f/pFizica->vMig);
			//efort la mansa creste=>rata variata(descrescatoare) de modificare
		}

		if(pFizica->vMig>992.0f) 
		{
			pFizica->unghiBracareMinim=4.0f;
			pFizica->unghiBracareMaxim=15.0f;
			//pFizica->rataEfortBracare=0.2f;
			//efort la mansa maxim=>rata minima de modificare
		}

		pFizica->rtx=1.0f;
		pFizica->rty=0.0f;
		pFizica->rtz=0.0f;
		
		if(contorDataStabilizator<3)
		{
			medieDataStabilizator+=js.lY;
			contorDataStabilizator++;
		}
		else
		{
			medieDataStabilizator=medieDataStabilizator/3.0f;
			contorDataStabilizator=0;
		if(js.lY>0)
			pFizica->unghiBracareStabilizator=(float)(medieDataStabilizator*pFizica->unghiBracareMaxim/2000000000);
		else
			pFizica->unghiBracareStabilizator=(float)(medieDataStabilizator*pFizica->unghiBracareMinim/2000000000);		
			medieDataStabilizator=0.0f;
		}
		*/

		/*if(js.lY>0)
			pFizica->unghiBracareStabilizator=(float)(js.lY*pFizica->unghiBracareMaxim/2000000000);
		else
			pFizica->unghiBracareStabilizator=(float)(js.lY*pFizica->unghiBracareMinim/2000000000);		
		*/
					
		
		return S_OK;
	}	
}
//------------------------------------------------------------------------
BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, 
											  VOID* hWnd)
{
	//pDIDInstance=pdidInstance;
	HRESULT hr;

    // Obtain an interface to the enumerated joystick.
    hr = pD3DInputJoystick->CreateDevice(pdidInstance->guidInstance,  
										 &pJoystick, NULL);		
    if(FAILED(hr)) 				
        return DIENUM_CONTINUE;	
	else
	
		return DIENUM_STOP;
	//return S_OK;
}
//-----------------------------------------------------------------------------
BOOL CALLBACK EnumAxesCallback( const DIDEVICEOBJECTINSTANCE* pdidoi,
                                VOID* pContext )
{    
	//HWND hDlg = (HWND)pContext;
	/*DIPROPDWORD didz; 
	didz.diph.dwSize       = sizeof(DIPROPDWORD); 
	didz.diph.dwHeaderSize = sizeof(DIPROPHEADER); 
	didz.diph.dwHow        = DIPH_DEVICE; 
	didz.diph.dwObj        = 0; // Specify the enumerated axis    
	didz.dwData            = DIPROPAUTOCENTER_OFF;
    
	// Set the dead zone for the axis
	if( FAILED( pJoystick->SetProperty( DIPROP_AUTOCENTER, &didz.diph ) ) )
		return DIENUM_STOP;
	*/

	if(pdidoi->guidType==GUID_XAxis) 
	{
		DIPROPRANGE diprg; 
		diprg.diph.dwSize       = sizeof(DIPROPRANGE); 
		diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER); 
		diprg.diph.dwHow        = DIPH_BYID; 
		diprg.diph.dwObj        = pdidoi->dwType; // Specify the enumerated axis
		diprg.lMin              = -2000000000;
		diprg.lMax              = 2000000000; 
		
    
		// Set the range for the axis
		if( FAILED( pJoystick->SetProperty( DIPROP_RANGE, &diprg.diph ) ) )
			return DIENUM_STOP;
	}

	if(pdidoi->guidType==GUID_YAxis) 
	{
		DIPROPRANGE diprg; 
		diprg.diph.dwSize       = sizeof(DIPROPRANGE); 
		diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER); 
		diprg.diph.dwHow        = DIPH_BYID; 
		diprg.diph.dwObj        = pdidoi->dwType; // Specify the enumerated axis
		diprg.lMin              = -2000000000; 
		diprg.lMax              = 2000000000; 
    
		// Set the range for the axis
		if( FAILED( pJoystick->SetProperty( DIPROP_RANGE, &diprg.diph ) ) )
			return DIENUM_STOP;
	}


	if(pdidoi->guidType==GUID_YAxis) 
	{
		DIPROPDWORD didz; 
		didz.diph.dwSize       = sizeof(DIPROPDWORD); 
		didz.diph.dwHeaderSize = sizeof(DIPROPHEADER); 
		didz.diph.dwHow        = DIPH_BYID; 
		didz.diph.dwObj        = pdidoi->dwType; // Specify the enumerated axis    
		didz.dwData            = 2000; 
    
		// Set the dead zone for the axis
		if( FAILED( pJoystick->SetProperty( DIPROP_DEADZONE, &didz.diph ) ) )
			return DIENUM_STOP;
	}

	if(pdidoi->guidType==GUID_XAxis) 
	{
		DIPROPDWORD didz; 
		didz.diph.dwSize       = sizeof(DIPROPDWORD); 
		didz.diph.dwHeaderSize = sizeof(DIPROPHEADER); 
		didz.diph.dwHow        = DIPH_BYID; 
		didz.diph.dwObj        = pdidoi->dwType; // Specify the enumerated axis    
		didz.dwData            = 2000;
    
		// Set the dead zone for the axis
		if( FAILED( pJoystick->SetProperty( DIPROP_DEADZONE, &didz.diph ) ) )
			return DIENUM_STOP;
	}

	

    // Set the UI to reflect what axes the joystick supports
	/*if (pdidoi->guidType == GUID_XAxis)
	{
        EnableWindow( GetDlgItem( hDlg, IDC_X_AXIS ), TRUE );
        EnableWindow( GetDlgItem( hDlg, IDC_X_AXIS_TEXT ), TRUE );
	}
	if (pdidoi->guidType == GUID_YAxis)
	{
        EnableWindow( GetDlgItem( hDlg, IDC_Y_AXIS ), TRUE );
        EnableWindow( GetDlgItem( hDlg, IDC_Y_AXIS_TEXT ), TRUE );
	}
	if (pdidoi->guidType == GUID_ZAxis)
	{
        EnableWindow( GetDlgItem( hDlg, IDC_Z_AXIS ), TRUE );
        EnableWindow( GetDlgItem( hDlg, IDC_Z_AXIS_TEXT ), TRUE );
	}
	if (pdidoi->guidType == GUID_RxAxis)
	{
        EnableWindow( GetDlgItem( hDlg, IDC_X_ROT ), TRUE );
        EnableWindow( GetDlgItem( hDlg, IDC_X_ROT_TEXT ), TRUE );
	}
	if (pdidoi->guidType == GUID_RyAxis)
	{
        EnableWindow( GetDlgItem( hDlg, IDC_Y_ROT ), TRUE );
        EnableWindow( GetDlgItem( hDlg, IDC_Y_ROT_TEXT ), TRUE );
	}
	if (pdidoi->guidType == GUID_RzAxis)
	{
        EnableWindow( GetDlgItem( hDlg, IDC_Z_ROT ), TRUE );
        EnableWindow( GetDlgItem( hDlg, IDC_Z_ROT_TEXT ), TRUE );
	}
	if (pdidoi->guidType == GUID_Slider)
	{
        EnableWindow( GetDlgItem( hDlg, IDC_SLIDER0 ), TRUE );
        EnableWindow( GetDlgItem( hDlg, IDC_SLIDER0_TEXT ), TRUE );
        EnableWindow( GetDlgItem( hDlg, IDC_SLIDER1 ), TRUE );
        EnableWindow( GetDlgItem( hDlg, IDC_SLIDER1_TEXT ), TRUE );
    }*/

    return DIENUM_CONTINUE;
}


