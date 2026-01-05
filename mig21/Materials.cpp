#include "Materials.h"
#include "InitD3D.h"

Materials::Materials()
{	
    ZeroMemory( &mtrl, sizeof(D3DMATERIAL8) );
}

void Materials::AmbientDiffuseMetal(LPDIRECT3DDEVICE8 g_pd3dDevice,float r,float g, float b,float a)
{    
    mtrl.Diffuse.r = r;
	mtrl.Diffuse.g = g;
	mtrl.Diffuse.b = b;
	mtrl.Diffuse.a = a;

	mtrl.Ambient.r = r;
	mtrl.Ambient.g = g;
	mtrl.Ambient.b = b;
	mtrl.Ambient.a = a;
	
	mtrl.Emissive.r = 0.0f;
	mtrl.Emissive.g = 0.0f;
	mtrl.Emissive.b = 0.0f;
	mtrl.Emissive.a = a;



	mtrl.Specular.r = 0.5f;	
	mtrl.Specular.g = 0.5f;		
	mtrl.Specular.b = 0.5f;
	mtrl.Specular.a = a;
	
	mtrl.Power=10.0f;

    g_pd3dDevice->SetMaterial( &mtrl );
}

void Materials::Specular(LPDIRECT3DDEVICE8 g_pd3dDevice,float r,float g,float b,float alpha)
{        
    mtrl.Diffuse.r = r;
	mtrl.Diffuse.g = g;
	mtrl.Diffuse.b = b;
	mtrl.Diffuse.a = alpha;

	mtrl.Ambient.r = r;	
	mtrl.Ambient.g = g;
	mtrl.Ambient.b = b;
	mtrl.Ambient.a = alpha;
	
	mtrl.Emissive.r = 0.0f;
	mtrl.Emissive.g = 0.0f;
	mtrl.Emissive.b = 0.0f;
	mtrl.Emissive.a = alpha;



	mtrl.Specular.r = 1.0f;	
	mtrl.Specular.g = 1.0f;	
	mtrl.Specular.b = 1.0f;	
	mtrl.Specular.a = alpha;

	mtrl.Power=5.0f;

    g_pd3dDevice->SetMaterial( &mtrl );
}

void Materials::Emissive(LPDIRECT3DDEVICE8 g_pd3dDevice,float r,float g,float b,float alpha)
{        
    mtrl.Diffuse.r = 0.0f;
	mtrl.Diffuse.g = 0.0f;
	mtrl.Diffuse.b = 0.0f;
	mtrl.Diffuse.a = alpha;

	mtrl.Ambient.r = 0.0f;	
	mtrl.Ambient.g = 0.0f;
	mtrl.Ambient.b = 0.0f;
	mtrl.Ambient.a = alpha;
	
	mtrl.Emissive.r = r;
	mtrl.Emissive.g = g;
	mtrl.Emissive.b = b;
	mtrl.Emissive.a = alpha;



	mtrl.Specular.r = 0.0f;	
	mtrl.Specular.g = 0.0f;		
	mtrl.Specular.b = 0.0f;
	mtrl.Specular.a = alpha;

	mtrl.Power=5.0f;

    g_pd3dDevice->SetMaterial( &mtrl );
}

void Materials::Clouds(LPDIRECT3DDEVICE8 g_pd3dDevice,float r,float g, float b,float a)
{    
    mtrl.Diffuse.r = r;
	mtrl.Diffuse.g = g;
	mtrl.Diffuse.b = b;
	mtrl.Diffuse.a = a;

	mtrl.Ambient.r = r;
	mtrl.Ambient.g = g;
	mtrl.Ambient.b = b;
	mtrl.Ambient.a = a;
	
	mtrl.Emissive.r = 0.0f;
	mtrl.Emissive.g = 0.0f;
	mtrl.Emissive.b = 0.0f;
	mtrl.Emissive.a = a;



	mtrl.Specular.r = 0.0f;
	mtrl.Specular.g = 0.0f;
	mtrl.Specular.b = 0.0f;
	mtrl.Specular.a = a;
	
	mtrl.Power=10.0f;

    g_pd3dDevice->SetMaterial( &mtrl );
}