#include "Fog.h"

Fog::Fog()
{

}

void Fog::SetupVertexFog(LPDIRECT3DDEVICE8 g_pd3dDevice,float Start,float End,
							D3DXCOLOR Color,DWORD Mode,bool UseRange,float Density)
{	

	g_pd3dDevice->SetRenderState(D3DRS_FOGENABLE,true);
	g_pd3dDevice->SetRenderState(D3DRS_FOGCOLOR,Color);

	if(D3DFOG_LINEAR==Mode)
	{
		g_pd3dDevice->SetRenderState(D3DRS_FOGVERTEXMODE,Mode);
		g_pd3dDevice->SetRenderState(D3DRS_FOGSTART,*(DWORD*)(&Start));
		g_pd3dDevice->SetRenderState(D3DRS_FOGEND,*(DWORD*)(&End));
	}
	else
	{
		g_pd3dDevice->SetRenderState(D3DRS_FOGVERTEXMODE,Mode);
		g_pd3dDevice->SetRenderState(D3DRS_FOGDENSITY,*(DWORD*)(&Density));
	}

	if(UseRange) g_pd3dDevice->SetRenderState(D3DRS_RANGEFOGENABLE,true);	
}

void Fog::SetupPixelFog(LPDIRECT3DDEVICE8 g_pd3dDevice,float Start,float End,
						D3DXCOLOR Color,DWORD Mode,float Density)
{	

	g_pd3dDevice->SetRenderState(D3DRS_FOGENABLE,true);
	g_pd3dDevice->SetRenderState(D3DRS_FOGCOLOR,Color);

	if(D3DFOG_LINEAR==Mode)
	{
		g_pd3dDevice->SetRenderState(D3DRS_FOGTABLEMODE,Mode);
		g_pd3dDevice->SetRenderState(D3DRS_FOGSTART,*(DWORD*)(&Start));
		g_pd3dDevice->SetRenderState(D3DRS_FOGEND,*(DWORD*)(&End));
	}
	else
	{
		g_pd3dDevice->SetRenderState(D3DRS_FOGTABLEMODE,Mode);
		g_pd3dDevice->SetRenderState(D3DRS_FOGDENSITY,*(DWORD*)(&Density));
	}
		
}