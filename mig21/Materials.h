#include "d3d8.h"
#include "d3d8types.h"

class Materials{
//functii publice
public:
		Materials();
		void AmbientDiffuseMetal(LPDIRECT3DDEVICE8 g_pd3dDevice,float r,float g, float b,float a);
		void Specular(LPDIRECT3DDEVICE8 g_pd3dDevice,float r,float g,float b,float alpha);
		void Emissive(LPDIRECT3DDEVICE8 g_pd3dDevice,float r,float g,float b,float alpha);
		void Clouds(LPDIRECT3DDEVICE8 g_pd3dDevice,float r,float g, float b,float a);
		
private:
		D3DMATERIAL8 mtrl;
		
		
//date publice
public:
		
		
		
		
public:
		
		
						
};
