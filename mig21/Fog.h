#include "d3d8.h"
#include "d3d8types.h"
#include "D3dx8math.h"

class Fog{
//functii publice
public:
		Fog();
		void SetupVertexFog(LPDIRECT3DDEVICE8 g_pd3dDevice,float Start,float End,
							D3DXCOLOR Color,DWORD Mode,bool UseRange,float Density);
		void SetupPixelFog(LPDIRECT3DDEVICE8 g_pd3dDevice,float Start,float End,
						D3DXCOLOR Color,DWORD Mode,float Density);
		
		
		
private:
		
		
		
//date publice
public:
		
		
		
		
public:
		
		
						
};