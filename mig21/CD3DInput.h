#include <tchar.h>
#include <windows.h>
#include <basetsd.h>
#include <dinput.h>

class CD3DInput{
//functii publice
public:
		CD3DInput();
		//~CD3DInput();
		HRESULT CreateD3DInputObject(HINSTANCE  hInstance,HWND hWnd);         
		HRESULT CreateSysKeyboardDevice(HWND hWnd);   
		HRESULT SetSysKeyboardBehavior(HWND hWnd);  
		void ProcessSysKeyboardInput(HWND hWnd); 
		void DI_Term();

		//JOYSTICK
		HRESULT EnumDevices(HWND hWnd); 
		HRESULT UpdateInputState(HWND hWnd);
		

//potected:
		
		
//date publice
public:
		LPDIRECTINPUT8  pD3DInput; 
		LPDIRECTINPUTDEVICE8  pSysKeyboardDevice;

		LONG lXVechi,lYVechi;
		float medieDataEleroane,medieDataStabilizator;
		int contorDataEleroane,contorDataStabilizator;

		//JOYSTICK																				
};
