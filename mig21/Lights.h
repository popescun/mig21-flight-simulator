#include "d3d8.h"
#include "d3d8types.h"
#include "D3dx8math.h"

class Lights{
//functii publice
public:
		Lights();
		void Directional(LPDIRECT3DDEVICE8 g_pd3dDevice,DWORD index,D3DXVECTOR3 vecDir,float r,float g,float b);
		void Point(LPDIRECT3DDEVICE8 g_pd3dDevice,DWORD index,
				   float x,float y, float z,
				   float r,float g,float b,
				   float range);
		void Spot(LPDIRECT3DDEVICE8 g_pd3dDevice,DWORD index,
				  float x,float y, float z,
				  D3DXVECTOR3 vecDir,
				  float range);
		
		
public:
		D3DLIGHT8 light;
		//D3DLIGHT8 light2;
		//D3DLIGHT8 light3;
		//D3DLIGHT8 light4;
		//D3DLIGHT8 light5;
		
		
//date publice
public:
		
		
		
		
public:
		
		
						
};