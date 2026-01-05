#include "Lights.h"

Lights::Lights()
{
	ZeroMemory( &light, sizeof(D3DLIGHT8) );
	//ZeroMemory( &light2, sizeof(D3DLIGHT8) );
	//ZeroMemory( &light3, sizeof(D3DLIGHT8) );
	//ZeroMemory( &light4, sizeof(D3DLIGHT8) );
	//ZeroMemory( &light5, sizeof(D3DLIGHT8) );
}

void Lights::Directional(LPDIRECT3DDEVICE8 g_pd3dDevice,DWORD index,
						 D3DXVECTOR3 vecDir,float r,float g,float b)
{            
    light.Type       = D3DLIGHT_DIRECTIONAL;

    light.Diffuse.r  = 0.5f;
    light.Diffuse.g  = 0.5f;
    light.Diffuse.b  = 0.5f;

	light.Ambient.r  = r;
    light.Ambient.g  = g;
    light.Ambient.b  = b;

	light.Specular.r  = 1.0f;
    light.Specular.g  = 1.0f;
    light.Specular.b  = 1.0f;
	    	
    D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction, &vecDir );
    
    g_pd3dDevice->SetLight( index, &light );
    g_pd3dDevice->LightEnable( index, TRUE );
    g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
}



void Lights::Point(LPDIRECT3DDEVICE8 g_pd3dDevice,DWORD index,
				   float x,float y, float z,
				   float r,float g,float b,
				   float range)
{    

    light.Type       = D3DLIGHT_POINT;

    light.Diffuse.r  = 0.5f;
    light.Diffuse.g  = 0.5f;
    light.Diffuse.b  = 0.5f;

	light.Ambient.r  = r;
    light.Ambient.g  = g;
    light.Ambient.b  = b;

	light.Specular.r  = 1.0f;
    light.Specular.g  = 1.0f;
    light.Specular.b  = 1.0f;

	light.Position.x=x;
	light.Position.y=y;
	light.Position.z=z;

	light.Attenuation0=0.0f;
	light.Attenuation1=1.0f;
	light.Attenuation2=1.0f;
	light.Range=range;

	g_pd3dDevice->SetLight( index, &light );
    g_pd3dDevice->LightEnable( index, TRUE );
    g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
	
}



void Lights::Spot(LPDIRECT3DDEVICE8 g_pd3dDevice,DWORD index,
				  float x,float y, float z,
				  D3DXVECTOR3 vecDir,
				  float range)
{        
    
    light.Type       = D3DLIGHT_SPOT;

    light.Diffuse.r  = 1.0f;
    light.Diffuse.g  = 1.0f;
    light.Diffuse.b  = 1.0f;

	light.Ambient.r  = 1.0f;
    light.Ambient.g  = 1.0f;
    light.Ambient.b  = 1.0f;

	light.Specular.r  = 1.0f;
    light.Specular.g  = 1.0f;
    light.Specular.b  = 1.0f;

	light.Attenuation0=1.0f;
	light.Attenuation1=0.0f;
	light.Attenuation2=0.0f;

	light.Range=range;
    
	light.Position.x=x;
	light.Position.y=y;
	light.Position.z=z;
	
    D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction, &vecDir );

	light.Theta=D3DX_PI/2.2f;
	light.Phi=D3DX_PI/2;
	

    g_pd3dDevice->SetLight( index, &light );
    g_pd3dDevice->LightEnable( index, TRUE );
    g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, TRUE );	
}

