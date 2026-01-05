#include "d3d8.h"
#include "d3d8types.h"
#include "D3dx8math.h"

class EnvMap{
//functii publice
public:
		EnvMap();
		~EnvMap();
		void Init(HWND hWnd,LPDIRECT3DDEVICE8 g_pd3dDevice);
		HRESULT CreazaCubMap(HWND hWnd,LPDIRECT3DDEVICE8 g_pd3dDevice);
		void RetineSetarileActuale(LPDIRECT3DDEVICE8 g_pd3dDevice);
		void CubMap(DWORD fata,LPDIRECT3DDEVICE8 g_pd3dDevice);
		void SetareCoordonateTextura(LPDIRECT3DDEVICE8 g_pd3dDevice);
		void RefacereCoordonateTextura(LPDIRECT3DDEVICE8 g_pd3dDevice);
		void RefacereSetari(LPDIRECT3DDEVICE8 g_pd3dDevice);
		
private:
		
		
		
//date publice
public:		
		LPDIRECT3DCUBETEXTURE8 pCubeMap;
		D3DXMATRIX matProjSave,matViewSave;
		LPDIRECT3DSURFACE8 pBackBuffer,pZBuffer;
		D3DXVECTOR3 vView;
		D3DXVECTOR3 vLook,vUp;
		
public:
		
								
};




