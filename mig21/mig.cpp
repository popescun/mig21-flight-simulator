//-----------------------------------------------------------------------------
// File: CameraView.cpp
// Copyright (c) 2002 Nick Popescu. All rights reserved.
//-----------------------------------------------------------------------------
#include "d3dx8.h"
#include "D3dx8mesh.h"
#include "D3dx8math.h"
#include "D3dx8tex.h"
#include "D3dx8core.h."
#include "D3d8types.h"

#include <mmsystem.h>
#include <stdlib.h>
#include <tchar.h>

#include "CD3DInput.h"
#include "InitD3D.h"
#include "Materials.h"
#include "Lights.h"
#include "Matrix.h"
#include "Transformation.h"
#include "Mesh.h"
#include "Fog.h"
#include "EnvMap.h"
#include "Font.h"
#include "Fizica.h"
#include "SistemParticule.h"
#include "Clouds.h"

#include "resource.h"

#include <sstream>

#include <windowsx.h>
//#define _UNICODE

//Prototipuri de functii
BOOL CALLBACK DlgFizica( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );
//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
HINSTANCE hInstantaAplicatiei;

LPDIRECT3DTEXTURE8		pTextureMozaic			= NULL; // Pointer to texture resource
LPDIRECT3DTEXTURE8		pTextureStema			= NULL; // Pointer to texture resource
LPDIRECT3DTEXTURE8		pTextureTeren			= NULL; // Pointer to texture resource
LPDIRECT3DTEXTURE8		pTextureZonaMuntoasa	= NULL; // Pointer to texture resource
LPDIRECT3DTEXTURE8		pTexturePista			= NULL; // Pointer to texture resource
LPDIRECT3DTEXTURE8		pTextureBaza			= NULL; // Pointer to texture resource
LPDIRECT3DTEXTURE8		pTextureHangar			= NULL; // Pointer to texture resource
LPDIRECT3DTEXTURE8		pTextureSprite			= NULL; // Pointer to texture resource
LPDIRECT3DTEXTURE8		pTextureEarth			= NULL; // Pointer to texture resource
LPDIRECT3DTEXTURE8		pTextureText			= NULL; // Pointer to texture resource
LPDIRECT3DTEXTURE8		pTextureBackGround		= NULL; // Pointer to texture resource
LPDIRECT3DTEXTURE8		pTextureCer				= NULL; // Pointer to texture resource
LPDIRECT3DTEXTURE8		pTextureCloud			= NULL; // Pointer to texture resource


LPD3DXMESH				pMeshMig				=NULL;  //Pointer to mesh object
LPD3DXMESH				pMeshMigCgOrigine		=NULL;  //Pointer to mesh object
LPD3DXMESH				pMeshMigNew  = NULL;  //Pointer to mesh object
LPD3DXMESH				pMeshRoataStanga		=NULL;  //Pointer to mesh object
LPD3DXMESH				pMeshTerrain			=NULL;  //Pointer to mesh object
LPD3DXMESH				pMeshTerrainCgOrigine	=NULL;  //Pointer to mesh object
LPD3DXMESH				pMeshBaza				=NULL;  //Pointer to mesh object
LPD3DXMESH				texCerMesh				=NULL;  //Pointer to mesh object
LPD3DXMESH				DisplayMesh				=NULL;  //Pointer to mesh object
LPD3DXMESH				pHUDMesh				=NULL;  //Pointer to mesh object
LPD3DXMESH				EarthMesh				=NULL;
LPD3DXSPRITE			pSprite					=NULL;



//HWND hWnd;

CD3DInput *pD3DInput=new CD3DInput;
CD3D *gD3D=new CD3D;
Materials *pMaterials=new Materials;
Lights *pLights=new Lights;
Matrix *pMatrix=new Matrix;
Transformation *pTransformation=new Transformation;
Mesh *pMesh=new Mesh;
Mesh *pMeshMeniuPrincipal=new Mesh;
Fog *pFog=new Fog;
EnvMap *pEnvMap=new EnvMap;
Font *pFont=new Font;
Fizica *pFizica=new Fizica;
SistemeParticule *pSistParticule=new SistemeParticule;
SistemeParticule *pCloud=new SistemeParticule;
Clouds *pClouds=new Clouds;


//float tx=0.0f,ty=0.0f,tz=0.0f,tzCameraUp=0.0f;
float rtx=1.0f,rty=0.0f,rtz=0.0f;	
float rlx=0.0f,rly=0.0f,rlz=1.0f;	
//float rotTranMig=D3DX_PI/450.0f;
float unghiBracareEleroane=0.0f;
float rotLongMig=0.0f,rotFlaps=0.0f,rotStabilizator=0.0f;
float viewXInitial=0.0f,viewYInitial=0.0f,viewZInitial=0.0f;	
float viewXDinamic=0.0f,viewYDinamic=0.0f,viewZDinamic=0.0f;	
float viewXStatic=0.0f,viewYStatic=0.0f,viewZStatic=0.0f;	
float viewXCurent=0.0f,viewYCurent=0.0f,viewZCurent=0.0f;	
float lookX=0.0f,lookY=0.0f,lookZ=0.0f;
D3DXVECTOR3* pViewDinamic=NULL;
D3DXVECTOR3* pViewStatic=NULL;	
D3DXVECTOR3* pLook=NULL;
D3DXVECTOR3* pUp=NULL;
//D3DXVECTOR3* pCentruGreutateMig=NULL;		
D3DXVECTOR3  VectorFataMig=D3DXVECTOR3(0.0f,0.0f,0.0f);		
D3DXVECTOR3  VectorFataMigOld=D3DXVECTOR3(0.0f,0.0f,0.0f);	
D3DXVECTOR3  ProiectieVectorFataMig=D3DXVECTOR3(0.0f,0.0f,0.0f);		
D3DXVECTOR3  VectorSpateMig=D3DXVECTOR3(0.0f,0.0f,0.0f);		
D3DXVECTOR3  ProiectieVectorSpateMig=D3DXVECTOR3(0.0f,0.0f,0.0f);		

D3DXVECTOR3  VectorStangaMig=D3DXVECTOR3(0.0f,0.0f,0.0f);		
D3DXVECTOR3  ProiectieVectorStangaMig=D3DXVECTOR3(0.0f,0.0f,0.0f);		
D3DXVECTOR3  VectorDreaptaMig=D3DXVECTOR3(0.0f,0.0f,0.0f);		
D3DXVECTOR3  ProiectieVectorDreaptaMig=D3DXVECTOR3(0.0f,0.0f,0.0f);		

D3DXVECTOR3  VectorSusMig=D3DXVECTOR3(0.0f,0.0f,0.0f);		
D3DXVECTOR3  ProiectieVectorSusMig=D3DXVECTOR3(0.0f,0.0f,0.0f);		
D3DXVECTOR3  VectorJosMig=D3DXVECTOR3(0.0f,0.0f,0.0f);		
D3DXVECTOR3  ProiectieVectorJosMig=D3DXVECTOR3(0.0f,0.0f,0.0f);			

D3DXVECTOR3  VectorAxaLongitudinalaMig=D3DXVECTOR3(0.0f,0.0f,0.0f);		
D3DXVECTOR3	 VectorAxaTransversalaOrizontalaMig=D3DXVECTOR3(0.0f,0.0f,0.0f);		 
D3DXVECTOR3	 VectorAxaTransversalaVerticalaMig=D3DXVECTOR3(0.0f,0.0f,0.0f);		 
D3DXVECTOR3  ProiectieVectorAxaLongitudinalaMig=D3DXVECTOR3(0.0f,0.0f,0.0f);		
D3DXVECTOR3	 ProiectieVectorAxaTransversalaOrizontalaMig=D3DXVECTOR3(0.0f,0.0f,0.0f);		 
D3DXVECTOR3	 ProiectieVectorAxaTransversalaVerticalaMig=D3DXVECTOR3(0.0f,0.0f,0.0f);		 

	
	
D3DXPLANE	planOrizontal;	
D3DXVECTOR3  VectorPerpendicularDreapta=D3DXVECTOR3(0.0f,0.0f,0.0f);
D3DXVECTOR3  VectorOrizontalDreapta=D3DXVECTOR3(0.0f,0.0f,0.0f);
D3DXVECTOR3  VectorOrizontArtificial=D3DXVECTOR3(0.0f,0.0f,0.0f);
D3DXVECTOR3  VectorNormala=D3DXVECTOR3(0.0f,0.0f,0.0f);
float unghiInclinareAnterior=0.0f,unghiNormalaOrizontArtificial=0.0f;
float unghiInclinareVertical=0.0f,unghiInclinareOrizontal=0.0f;	
//D3DXVECTOR3  VectorPerpendicularStanga=D3DXVECTOR3(0.0f,0.0f,0.0f);	
		
//bool up=false,down=false;
float left=false,right=false,palonierstg=false,palonierdr=false,flaps=false;
bool flag_camerastatica=false;
bool flag_cameradinamica1=true;
bool flag_cameradinamica2=false;
int contor=101;	
bool flagScene=true,Migload=true;
	
//pentru cresterea progr. a puterii motorului
bool powerUp=false;
bool powerDown=false;	
	

//Earth
float rx=0.0f,ry=1.0f,rz=0.0f,unghiOy=D3DX_PI/200;
float earthtx=60.0f,earthty=55.0f,earthtz=0.0f;
bool MeniuPrincipalLoad=true;

//fog
float StartFog=5500000.0f;
float EndFog=7000000.0f;
float FogDensity=0.005f;

//Matrix
//D3DXMATRIX ViewMatrix;
//bool MatrixSettingFlag=true;

//font
LPCSTR pString;
INT Count;
RECT Rect;
DWORD Format;
D3DXCOLOR Color;	

//sky
bool flagOverSky=false;

//stencil buffer
unsigned long mask=0X00000000;

//fill mode (wire or not)	
bool flagWire=true;

//terrain
float FOV;
float farPlane;
D3DXVECTOR3* pLeftViewingFrustum=NULL;
D3DXVECTOR3* pRightViewingFrustum=NULL;

//FPS+time
float FrameRate=0.0f,FrameCount=0.0f;						
float TimeMissionSeconds;
float TimeMissionFrame=1.0f;
float TimeCount=0.0f;
LONGLONG lpFrequency; //address of current frequency 
LONGLONG pPerformanceCountBeginFrame;// address of current counter value 						
LONGLONG pPerformanceCountEndFrame;// address of current counter value 
//fps control
LONGLONG curentTime;
LONGLONG timeCount=40;
//LONGLONG performanceCounter;
bool performanceFlag=false;
LONGLONG nextTime=0;
bool moveFlag=true;

//Game states
bool flagPaused=false;

//Afisaje
bool flagAfisaje=false;

//comenzi
//bool flagAfisajComenzi=false;
int contorAfisajComenziFlapsuri=400;
int contorAfisajComenziMotor=400;

//scalare
D3DXMATRIX* pMatScalare=NULL;

//temp
int indexVertex=0;	

//HUD
//float unghiOriz=0.0f;
float txHUDFix=0.0f,tyHUDFix=70.0f,tzHUDFix=440.0f;
float tYHUD=0.0f,rotZHUD=0.0f;

// mouse move
int prev_xPos = 0, prev_yPos = 0;

//-----------------------------------------------------------------------------
// Name: LoadMesh()
// Desc: Creates the scene geometry
//-----------------------------------------------------------------------------
	HRESULT LoadMeshes(HWND hWnd)
{						 
	pMesh->pFileNames[0]="models/mig21.x";
	//pMesh->pFileNames[1]="models/mig21Cg=Origine.x";	
	pMesh->pFileNames[1] = "models/new_mig21.x";
	pMesh->pFileNames[2]="models/roatastanga.x";	
	pMesh->pFileNames[3]="models/terrain.x";		
	//pMesh->pFileNames[4]="models/terrainCg=Origine.x";		
	pMesh->pFileNames[4]="models/baza.x";		
	pMesh->pFileNames[5]="models/HUD.x";		
	pMesh->pFileNames[6] = "models/mig21Cg=Origine.x";
	//pMesh->pFileNames[2]="cloud.x";	
	//pMesh->pFileNames[3]="display.x";	
		
	pMesh->Load(hWnd,gD3D->g_pD3DDevice,7);

	pMeshMig=pMesh->pMeshes[0];	
	pMeshMigCgOrigine=pMesh->pMeshes[6];	
	pMeshMigNew = pMesh->pMeshes[1];
	pMeshRoataStanga=pMesh->pMeshes[2];	
	pMeshTerrain=pMesh->pMeshes[3];	
	//pMeshTerrainCgOrigine=pMesh->pMeshes[4];	
	pMeshBaza=pMesh->pMeshes[4];	
	//texCerMesh=pMesh->pMeshes[2];
	//DisplayMesh=pMesh->pMeshes[3];
	pHUDMesh=pMesh->pMeshes[5];	
	
	

	D3DXCreateTextureFromFile( gD3D->g_pD3DDevice , "texturi/Mozaic-aluminiu.dds",&pTextureMozaic);		
	D3DXCreateTextureFromFile( gD3D->g_pD3DDevice , "texturi/Stema.jpg",&pTextureStema) ;
	//D3DXCreateTextureFromFile( gD3D->g_pD3DDevice , "Asphalt3.jpg",&pTexturePista) ;	
	D3DXCreateTextureFromFile( gD3D->g_pD3DDevice , "texturi/taxyway-light.dds",&pTexturePista) ;	
	D3DXCreateTextureFromFile( gD3D->g_pD3DDevice , "texturi/Grass256.dds",&pTextureBaza) ;		
	//D3DXCreateTextureFromFile( gD3D->g_pD3DDevice , "Grass256.jpg",&pTextureTeren) ;
	//D3DXCreateTextureFromFile( gD3D->g_pD3DDevice , "texturi/Land0.dds",&pTextureTeren) ;
	D3DXCreateTextureFromFile( gD3D->g_pD3DDevice , "texturi/4_7_10.bmp",&pTextureTeren) ;
	//D3DXCreateTextureFromFile( gD3D->g_pD3DDevice , "texturi/teren.dds",&pTextureTeren) ;
	D3DXCreateTextureFromFile( gD3D->g_pD3DDevice , "texturi/TexturaBaza.dds",&pTextureZonaMuntoasa) ;	
	//D3DXCreateTextureFromFile( gD3D->g_pD3DDevice , "Land1.jpg",&pTextureTeren) ;	
	//D3DXCreateTextureFromFile( gD3D->g_pD3DDevice , "texBaza.jpg",&pTextureTeren) ;	
	D3DXCreateTextureFromFile( gD3D->g_pD3DDevice , "texturi/Stucco11.jpg",&pTextureHangar) ;	
	D3DXCreateTextureFromFile( gD3D->g_pD3DDevice , "texturi/particle.dds",&pTextureSprite);		
	D3DXCreateTextureFromFile( gD3D->g_pD3DDevice , "texturi/sky-senin.jpg",&pTextureCer) ;	
	D3DXCreateTextureFromFile( gD3D->g_pD3DDevice , "texturi/nor.bmp",&pTextureCloud) ;	

	//D3DXCreateSprite(gD3D->g_pD3DDevice ,&pSprite);


		
	return S_OK;	
}
//-----------------------------------------------------------------------------
// Name: LoadMesh()
// Desc: Creates the scene geometry
//-----------------------------------------------------------------------------
HRESULT LoadMeshMeniuPrincipal(HWND hWnd)
{						 
	pMeshMeniuPrincipal->pFileNames[0]="models/prezentare.x";		
	pMeshMeniuPrincipal->Load(hWnd,gD3D->g_pD3DDevice,1);
	
	EarthMesh=pMeshMeniuPrincipal->pMeshes[0];
		
	D3DXCreateTextureFromFile( gD3D->g_pD3DDevice , "texturi/Earthmap.tga",&pTextureEarth) ;	
	D3DXCreateTextureFromFile( gD3D->g_pD3DDevice , "texturi/Mozaic.jpg",&pTextureText);	
	D3DXCreateTextureFromFile( gD3D->g_pD3DDevice , "texturi/Prezentare.jpg",&pTextureBackGround);	
	
	return S_OK;	
}

//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
VOID Cleanup()
{
    if( pTextureMozaic!= NULL )
        pTextureMozaic->Release();

	if( pTextureStema!= NULL )
        pTextureStema->Release();

	if( pTexturePista!= NULL )
        pTexturePista->Release();

	if( pTextureTeren!= NULL )
        pTextureTeren->Release();	

	if( pMeshMig!= NULL )
        pMeshMig->Release();

	if( pMeshTerrain!= NULL )
        pMeshTerrain->Release();

	if( pMeshBaza!= NULL )
        pMeshBaza->Release();

	if(pTransformation->pStackMig!=NULL)
		pTransformation->pStackMig->Release();

	if(pTransformation->pStackTerrain!=NULL)
		pTransformation->pStackTerrain->Release();

	if(pTransformation->pStackStabilizator!=NULL)
		pTransformation->pStackStabilizator->Release();

	if(pTransformation->pStackEleron!=NULL)
		pTransformation->pStackEleron->Release();

    if( gD3D->g_pD3DDevice != NULL )
        gD3D->g_pD3DDevice->Release();


    if( gD3D->g_pD3D != NULL )
        gD3D->g_pD3D->Release();
}
//-----------------------------------------------------------------------------
void BeginScene(HWND hWnd,D3DXMATRIX *MigMatWorld)
{
	float factorIntuneric;	
	//factorIntuneric=1.35f;
	factorIntuneric=1.11f;
	 gD3D->g_pD3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,
                         D3DXCOLOR(0.67f*factorIntuneric,0.82f*factorIntuneric,0.91f*factorIntuneric,1.0f), 1.0f,0);
	//D3DXCOLOR(0.67f,0.82f,0.91f,1.0f)-constituie si culoarea atmosferei
	 //-------------- RENDER STATES	

    // Begin the scene
    gD3D->g_pD3DDevice->BeginScene();

	//Rotunjire (antialising) muchiilor 
	gD3D->g_pD3DDevice->SetRenderState( D3DRS_EDGEANTIALIAS, TRUE );
	gD3D->g_pD3DDevice->SetRenderState( D3DRS_DITHERENABLE , TRUE ); 
	//gD3D->g_pD3DDevice->SetRenderState( D3DRS_FILLMODE , D3DFILL_POINT); 	
    gD3D->g_pD3DDevice->SetRenderState( D3DRS_ZENABLE,D3DZB_TRUE);
	gD3D->g_pD3DDevice->SetRenderState( D3DRS_STENCILENABLE,true);
	gD3D->g_pD3DDevice->SetRenderState( D3DRS_CULLMODE , D3DCULL_NONE);
	gD3D->g_pD3DDevice->SetRenderState( D3DRS_LASTPIXEL , false);	
	//gD3D->g_pD3DDevice->SetRenderState( D3DRS_LOCALVIEWER , false);
	//gD3D->g_pD3DDevice->SetRenderState( D3DRS_CLIPPING , true);
	gD3D->g_pD3DDevice->SetRenderState( D3DRS_SHADEMODE, D3DSHADE_PHONG);	
	//gD3D->g_pD3DDevice->SetRenderState( D3DRS_NORMALIZENORMALS , true);
	gD3D->g_pD3DDevice->SetRenderState( D3DRS_SPECULARENABLE , false);
	//----------------------------------------------------------------			

	//cursorul
	BOOL bShow;
	bShow=FALSE;
	gD3D->g_pD3DDevice->ShowCursor(bShow);
	
	pLights->Directional(gD3D->g_pD3DDevice,0,
						 *pTransformation->CameraViewTransformation(&pTransformation->MatTransformationCameraUp,&D3DXVECTOR3(0.0f,-1.0f,-2.0f)),
						 //D3DXVECTOR3(0.0f,-1.0f,-1.0f),
						 0.7f*factorIntuneric,0.7f*factorIntuneric,0.7f*factorIntuneric);// sistemul de lumini se misca odata cu pamantul si cerul relativ la mig
	//pLights->Directional(gD3D->g_pD3DDevice,pLights->light1,D3DXVECTOR3(0.0f,-1.0f,1.0f),0.7f,0.7f,0.7f);
	//pLights->Directional(gD3D->g_pD3DDevice,pLights->light2,D3DXVECTOR3(0.0f,0.0f,1.0f),0.7f,0.7f,0.7f);
	//pLights->Directional(gD3D->g_pD3DDevice,pLights->light3,D3DXVECTOR3(-1.0f,-1.0f,0.0f),0.7f,0.7f,0.7f);

	//pLights->Directional(gD3D->g_pD3DDevice,D3DXVECTOR3(0.0f,-1.0f,0.0f));	
	//pLights->Point(gD3D->g_pD3DDevice,1,
	//	   0.0f,900.0f,0.0f,
	//	   1.0f,1.0f,1.0f,
	//	   2000.0f);
	//SetupPointLights(0.0f,-800.0f,0.0f);
	//SetupSpotlLights(0.0f,800.0f, 1000.0f,D3DXVECTOR3(0.0f,800.0f,-1000.0f));
	/*pLights->Spot(gD3D->g_pD3DDevice,
				  0,//index
		          0.0f,5000000.0f,0.0f,//position
				  D3DXVECTOR3(0.0f,-1.0f,0.0f),//direction
				  30000000.0f//range
				  );*/
	
	
    //SetupMatrices();	
	FOV=(float)(D3DX_PI/6.5f);
	farPlane=30000000.0f;
	pMatrix->SetupProjectionMatrix(gD3D->g_pD3DDevice,FOV,
			(float)gD3D->Echipament.d3dModVideoCurent.Width/
			gD3D->Echipament.d3dModVideoCurent.Height,
			35.0f,farPlane);
		
	//ptr clear day se va folosi FogDensity=0.0f;		
	if(VectorFataMig.y<3000000.0f || VectorFataMig.y>3500000.0f)
	{
		pFog->SetupVertexFog(gD3D->g_pD3DDevice,5500000.0f,6500000.0f,//StartFog,EndFog,
						 D3DXCOLOR(0.67f*factorIntuneric,0.82f*factorIntuneric,0.91f*factorIntuneric,1.0f),
						 D3DFOG_LINEAR,true,0.01f);
		//pFog->SetupPixelFog(gD3D->g_pD3DDevice,5500000.0f,6500000.0f,
		//				D3DXCOLOR(0.67f,0.82f,0.91f,1.0f),D3DFOG_LINEAR,0.00001f);	
		//pFog->SetupVertexFog(gD3D->g_pD3DDevice,100000,6000000,
		//					 D3DXCOLOR(0.67f,0.82f,0.91f,1.0f),D73DFOG_EXP,true,0.0000001f);		
	}
	//D3DXCOLOR(0.25f,0.81f,0.99f,0.0f)
	//D3DXCOLOR(0.67f,0.82f,0.91f,1.0f)
	//  else
	//se va folosi pentru intrarea in nori
	//float FogDensity=0.0000001f; va creste de la o valoare mica pana deasupra norilor
	//{				
		//StartFog=50000.0f;
		//EndFog=70000.0f;		

		//pFog->SetupVertexFog(gD3D->g_pD3DDevice,StartFog,EndFog,
		//					 D3DXCOLOR(0.67f*factorIntuneric,0.82f*factorIntuneric,0.91f*factorIntuneric,1.0f),
		//					 D3DFOG_LINEAR,false,FogDensity);

		//pFog->SetupPixelFog(gD3D->g_pD3DDevice,StartFog,EndFog,
		//				D3DXCOLOR(0.67f,0.82f,0.91f,1.0f),D3DFOG_LINEAR,FogDensity);
		//if(VectorFataMig.y>VectorFataMigOld.y)		
		//if(FogDensity<1.0f)		
		//	FogDensity+=0.001f;					
		//else		
		//	FogDensity=0.001f;							
	//}

	VectorFataMigOld=VectorFataMig;
	
	//pLeftViewingFrustum=&D3DXVECTOR3((float)(-farPlane*tan(FOV/2)),0,farPlane);  //ptr. calsa terrain, QuadTree
	//pLeftViewingFrustum=&D3DXVECTOR3((float)(farPlane*tan(FOV/2)),0,farPlane);

	pLook = &D3DXVECTOR3(lookX, lookY, lookZ);
	pUp = &D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	if(flag_camerastatica)
	{	
		if (contor<150.0f)	
		{
			//pTransformation->MatViewStatic=*pTransformation->pStackViewStatic->GetTop();
			contor++;		
		}
		else
		{									
			pTransformation->pStackViewStatic->LoadIdentity();						
			contor=0;
		}

		pViewStatic=&D3DXVECTOR3(viewXStatic,viewYStatic,viewZStatic);			
		pViewStatic->x-= 6000.0f;
		pViewStatic->y+= 200.0f;
		//pViewStatic->y += 4000.0f;
		pViewStatic->z+= 4000.0;				

		pLook = &D3DXVECTOR3(lookX, lookY, lookZ);

		pMatrix->SetupViewMatrix(gD3D->g_pD3DDevice,
							 //pTransformation->CameraViewTransformation(&pTransformation->MatViewStatic,&D3DXVECTOR3(pViewStatic->x-3000,pViewStatic->y-500+3000,pViewStatic->z+40000)),
							 pTransformation->CameraViewTransformation(&pTransformation->MatViewStatic,pViewStatic),
							 pLook,
							 pTransformation->CameraViewTransformation(&pTransformation->MatTransformationCameraUp,pUp)
							);	

		viewXCurent=pViewStatic->x;
		viewYCurent=pViewStatic->y;
		viewZCurent=pViewStatic->z;		
	}
			
	
	if(flag_cameradinamica1)
	{
		pViewDinamic=&D3DXVECTOR3(viewXDinamic,viewYDinamic,viewZDinamic);					
		pMatrix->SetupViewMatrix(gD3D->g_pD3DDevice,
								 pViewDinamic,
								 pLook,
								 pUp);

		viewXCurent=pViewDinamic->x;
		viewYCurent=pViewDinamic->y;
		viewZCurent=pViewDinamic->z;
	}

	if(flag_cameradinamica2)
	{		
		pViewDinamic=&D3DXVECTOR3(viewXDinamic,viewYDinamic,viewZDinamic);					
		pMatrix->SetupViewMatrix(gD3D->g_pD3DDevice,
								 pTransformation->CameraViewTransformation(&pTransformation->MatTransformationCameraUp,pViewDinamic),//pViewDinamic,
								 pLook,
								 pTransformation->CameraViewTransformation(&pTransformation->MatTransformationCameraUp,pUp));//pUp);//										

		viewXCurent=pViewDinamic->x;
		viewYCurent=pViewDinamic->y;
		viewZCurent=pViewDinamic->z;				
	}

	//pTransformation->CameraViewTransformation(MigMatWorld,pLeftViewingFrustum);
	//pTransformation->CameraViewTransformation(MigMatWorld,pRightViewingFrustum);
	
	//pTransformation->TransformationVector(&pTransformation->MatMig,pLeftViewingFrustum);		
		
	//enviroment mapping
	pEnvMap->vView=D3DXVECTOR3(0.0f,0.0f,0.0f);										
	pTransformation->TransformationVector(&pTransformation->MatMig,&pEnvMap->vView);
	
	//fog
	//StartFog=StartFog+VectorFataMig.z-VectorFataMigOld.z;
	//EndFog=EndFog+VectorFataMig.z-VectorFataMigOld.z;

	//sky
	if(VectorFataMig.y>1050000.0f)
		flagOverSky=true;
	else
		flagOverSky=true;

	/*if(ok)
	{
	TCHAR buffer1[10];
	TCHAR buffer2[10];

	_itoa(VectorFataMig.z,buffer1,10);
	_itoa(VectorFataMigOld.z,buffer2,10);
	MessageBox(hWnd,buffer1, "New", MB_OK);
	MessageBox(hWnd,buffer2, "Old", MB_OK);
	ok=false;
	}*/	
}
//-----------------------------------------------------------------------------
void CalculeazaParametri(D3DXMATRIX *pMatMig)
{
	VectorFataMig=D3DXVECTOR3(0.0f,0.0f,780.0f);
	pTransformation->TransformationVector(&pTransformation->MatMig,&VectorFataMig);		
	VectorSpateMig=D3DXVECTOR3(0.0f,0.0f,-780.0f);
	pTransformation->TransformationVector(&pTransformation->MatMig,&VectorSpateMig);	
	VectorStangaMig=D3DXVECTOR3(-380.0f,0.0f,0.0f);
	pTransformation->TransformationVector(&pTransformation->MatMig,&VectorStangaMig);
	VectorDreaptaMig=D3DXVECTOR3(380.0f,0.0f,0.0f);
	pTransformation->TransformationVector(&pTransformation->MatMig,&VectorDreaptaMig);		
	VectorSusMig=D3DXVECTOR3(0.0f,300.0f,0.0f);
	pTransformation->TransformationVector(&pTransformation->MatMig,&VectorSusMig);	
	VectorJosMig=D3DXVECTOR3(0.0f,-300.0f,0.0f);
	pTransformation->TransformationVector(&pTransformation->MatMig,&VectorJosMig);
	//din clasa Fizica recalc. in TestColiziuneNew
	//pFizica->VectorCentruRotiVechi=pFizica->VectorCentruRoti;
	//pFizica->VectorCentruRoti=D3DXVECTOR3(0.0f,-146.44f,-23.21f);	
	//pTransformation->TransformationVector(pMatMig,&pFizica->VectorCentruRoti);
	//pFizica->VectorRoataFata=D3DXVECTOR3(0.0f,-146.44f,453.32f);	
	//pTransformation->TransformationVector(pMatMig,&pFizica->VectorRoataFata);
	//pFizica->VectorCentruDeGreutate=D3DXVECTOR3(-0.3f,0.0f,0.0f);
	//pTransformation->TransformationVector(&pTransformation->MatMig,&pFizica->VectorCentruDeGreutate);

	//calculul unghiului de inclinare a axei long. fata de orizontala (tetaz)
	ProiectieVectorFataMig=D3DXVECTOR3(VectorFataMig.x,0.0f,VectorFataMig.z);										
	ProiectieVectorSpateMig=D3DXVECTOR3(VectorSpateMig.x,0.0f,VectorSpateMig.z);
	D3DXVec3Subtract(&VectorAxaLongitudinalaMig,&VectorFataMig,&VectorSpateMig); 
	D3DXVec3Subtract(&ProiectieVectorAxaLongitudinalaMig,&ProiectieVectorFataMig,&ProiectieVectorSpateMig); 
	
	

	if(VectorFataMig.y>=VectorSpateMig.y)			
	{
		pFizica->tetazRadiani=(float)acos(D3DXVec3Length(&ProiectieVectorAxaLongitudinalaMig)
							             /D3DXVec3Length(&VectorAxaLongitudinalaMig));				
		pFizica->tetazGrade=D3DXToDegree(pFizica->tetazRadiani);
	}
			
	else
		if(VectorFataMig.y<VectorSpateMig.y)								
		{
			pFizica->tetazRadiani=-(float)acos(
							  D3DXVec3Length(&ProiectieVectorAxaLongitudinalaMig)
							  /D3DXVec3Length(&VectorAxaLongitudinalaMig));							
			pFizica->tetazGrade=D3DXToDegree(pFizica->tetazRadiani);
		}	
			
	//unghiul de inclinare al axei transversale orizontale a mig-ului fata de planul orizontal (tetax)
	ProiectieVectorStangaMig=D3DXVECTOR3(VectorStangaMig.x,0.0f,VectorStangaMig.z);										
	ProiectieVectorDreaptaMig=D3DXVECTOR3(VectorDreaptaMig.x,0.0f,VectorDreaptaMig.z);
	D3DXVec3Subtract(&VectorAxaTransversalaOrizontalaMig,&VectorStangaMig,&VectorDreaptaMig); 	
	D3DXVec3Subtract(&ProiectieVectorAxaTransversalaOrizontalaMig,&ProiectieVectorStangaMig,&ProiectieVectorDreaptaMig); 	
		

	if(VectorDreaptaMig.y>=VectorStangaMig.y)
	{
		pFizica->tetaxRadiani=-(float)acos(D3DXVec3Length(&ProiectieVectorAxaTransversalaOrizontalaMig)
							             /D3DXVec3Length(&VectorAxaTransversalaOrizontalaMig));				
		pFizica->tetaxGrade=D3DXToDegree(pFizica->tetaxRadiani);
	}
	else
		if(VectorDreaptaMig.y<VectorStangaMig.y)
		{
			pFizica->tetaxRadiani=(float)acos(D3DXVec3Length(&ProiectieVectorAxaTransversalaOrizontalaMig)
							             /D3DXVec3Length(&VectorAxaTransversalaOrizontalaMig));				
			pFizica->tetaxGrade=D3DXToDegree(pFizica->tetaxRadiani);
		}
	
	//unghiul de inclinare al axei transversale verticale a mig-ului fata de planul orizontal (tetay)
	ProiectieVectorSusMig=D3DXVECTOR3(VectorSusMig.x,0.0f,VectorSusMig.z);										
	ProiectieVectorJosMig=D3DXVECTOR3(VectorJosMig.x,0.0f,VectorJosMig.z);										
	D3DXVec3Subtract(&VectorAxaTransversalaVerticalaMig,&VectorSusMig,&VectorJosMig); 	
	D3DXVec3Subtract(&ProiectieVectorAxaTransversalaVerticalaMig,&ProiectieVectorSusMig,&ProiectieVectorJosMig); 	
		
	if(VectorSusMig.y>VectorJosMig.y)
	{
		pFizica->tetayRadiani=(float)acos(D3DXVec3Length(&ProiectieVectorAxaTransversalaVerticalaMig)
							             /D3DXVec3Length(&VectorAxaTransversalaVerticalaMig));				
		pFizica->tetayGrade=D3DXToDegree(pFizica->tetayRadiani);
	}
	else
		if(VectorSusMig.y<VectorJosMig.y)
		{
			pFizica->tetayRadiani=-(float)acos(D3DXVec3Length(&ProiectieVectorAxaTransversalaVerticalaMig)
							             /D3DXVec3Length(&VectorAxaTransversalaVerticalaMig));				
			pFizica->tetayGrade=D3DXToDegree(pFizica->tetayRadiani);
		}
			
	//calcul unghi inclinare mig	
	VectorOrizontArtificial=D3DXVECTOR3(1.0f,0.0f,0.0f);
	//VectorNormala=D3DXVECTOR3(0.0f,1.0f,0.0f);
	VectorPerpendicularDreapta=D3DXVECTOR3(380.0f,100000.0f,0.0f);
	pTransformation->TransformationVector(&pTransformation->MatMig,&VectorPerpendicularDreapta);		
	VectorOrizontalDreapta=D3DXVECTOR3(380.0f,0.0f,100000.0f);
	pTransformation->TransformationVector(&pTransformation->MatMig,&VectorOrizontalDreapta);		
	
	D3DXVECTOR3 vOrigLoc=D3DXVECTOR3(0.0f,0.0f,0.0f);
	D3DXVECTOR3 vec2=D3DXVECTOR3(0.0f,0.0f,0.0f);
	D3DXVECTOR3 vec3=D3DXVECTOR3(0.0f,0.0f,0.0f);

	pFizica->VectorCentruDeGreutate=D3DXVECTOR3(-0.3f,0.0f,0.0f);
	pTransformation->TransformationVector(&pTransformation->MatMig,&pFizica->VectorCentruDeGreutate);
	vOrigLoc=pFizica->VectorCentruDeGreutate;
	vec2=D3DXVECTOR3(vOrigLoc.x+1.0f,vOrigLoc.y,vOrigLoc.z);
	vec3=D3DXVECTOR3(vOrigLoc.x,vOrigLoc.y,vOrigLoc.z+1.0f);

	D3DXPlaneFromPoints(&planOrizontal,
						&vOrigLoc,
						&vec2,
						&vec3); 

	
	D3DXVECTOR3 VarfVectorInclinareAripaVertical=D3DXVECTOR3(0.0f,0.0f,0.0f);
	D3DXVECTOR3 VectorInclinareAripaVertical=D3DXVECTOR3(0.0f,0.0f,0.0f);

	D3DXVECTOR3 VarfVectorInclinareAripaOrizontal=D3DXVECTOR3(0.0f,0.0f,0.0f);
	D3DXVECTOR3 VectorInclinareAripaOrizontal=D3DXVECTOR3(0.0f,0.0f,0.0f);

	float unghiAtitudLong;
	if(pFizica->tetazGrade>=0.0f)
		if(pFizica->tetayGrade>=0.0f)
			unghiAtitudLong=pFizica->tetazGrade;
		else
			unghiAtitudLong=180.0f-pFizica->tetazGrade;
	else
		if(pFizica->tetayGrade>=0.0f)
			unghiAtitudLong=pFizica->tetazGrade;
		else
			unghiAtitudLong=-180.0f-pFizica->tetazGrade;

	//if((unghiAtitudLong>=80.0f && unghiAtitudLong<=100.0f)
	//	|| (unghiAtitudLong<=-80.0f && unghiAtitudLong>=-100.0f))
		D3DXPlaneIntersectLine(&VarfVectorInclinareAripaOrizontal,
						   &planOrizontal,
						   &VectorDreaptaMig,
						   &VectorOrizontalDreapta);	
	//else
		D3DXPlaneIntersectLine(&VarfVectorInclinareAripaVertical,
						   &planOrizontal,
						   &VectorDreaptaMig,
						   &VectorPerpendicularDreapta);
		

	D3DXVec3Subtract(&VectorInclinareAripaVertical,&VarfVectorInclinareAripaVertical,&vOrigLoc); 	
	D3DXVec3Subtract(&VectorInclinareAripaOrizontal,&VarfVectorInclinareAripaOrizontal,&vOrigLoc); 		
	//este invers mai sus
	D3DXVec3Subtract(&VectorAxaTransversalaOrizontalaMig,&VectorDreaptaMig,&VectorStangaMig); 	
	D3DXVec3Normalize(&VectorInclinareAripaVertical,&VectorInclinareAripaVertical); 
	D3DXVec3Normalize(&VectorInclinareAripaOrizontal,&VectorInclinareAripaOrizontal); 
	D3DXVec3Normalize(&VectorAxaTransversalaOrizontalaMig,&VectorAxaTransversalaOrizontalaMig); 
		
	//if(unghiAtitudLong<=80.0f || unghiAtitudLong>=100.0f)
	//if((unghiAtitudLong>=80.0f && unghiAtitudLong<=100.0f)
	//	|| (unghiAtitudLong<=-80.0f && unghiAtitudLong>=-100.0f))
	/*if(pFizica->tetaxGrade>-20.0f && pFizica->tetaxGrade<20.0f 
		&& pFizica->unghiRotatieLongitudinalaMig==0.0f)
	//{		
	if(pFizica->tetayGrade>=0.0f)	
		if(VectorDreaptaMig.y<=VectorStangaMig.y)		
		{
			unghiInclinareVertical=(float)(acos(D3DXVec3Dot(&VectorInclinareAripaVertical,
											&VectorAxaTransversalaOrizontalaMig)));		
			unghiInclinareOrizontal=(float)(acos(D3DXVec3Dot(&VectorInclinareAripaOrizontal,
											&VectorAxaTransversalaOrizontalaMig)));		

			if(unghiInclinareVertical<unghiInclinareOrizontal)
				pFizica->unghiInclinare=unghiInclinareVertical;
			else
				pFizica->unghiInclinare=unghiInclinareOrizontal;
			unghiInclinareAnterior=pFizica->unghiInclinare;
		}			
		else		
		{
			unghiInclinareVertical=-(float)(acos(D3DXVec3Dot(&VectorInclinareAripaVertical,
											&VectorAxaTransversalaOrizontalaMig)));		
			unghiInclinareOrizontal=-(float)(acos(D3DXVec3Dot(&VectorInclinareAripaOrizontal,
											&VectorAxaTransversalaOrizontalaMig)));		
			if(unghiInclinareVertical>unghiInclinareOrizontal)
				pFizica->unghiInclinare=unghiInclinareVertical;
			else
				pFizica->unghiInclinare=unghiInclinareOrizontal;
			unghiInclinareAnterior=pFizica->unghiInclinare;
		}
	else

		if(VectorDreaptaMig.y<=VectorStangaMig.y)
		{
			unghiInclinareVertical=(float)(D3DX_PI
											+(acos(D3DXVec3Dot(&VectorInclinareAripaVertical,
											&VectorAxaTransversalaOrizontalaMig))));
			unghiInclinareOrizontal=(float)(D3DX_PI
											+(acos(D3DXVec3Dot(&VectorInclinareAripaOrizontal,
											&VectorAxaTransversalaOrizontalaMig))));
			if(unghiInclinareVertical<unghiInclinareOrizontal)
				pFizica->unghiInclinare=unghiInclinareVertical;
			else
				pFizica->unghiInclinare=unghiInclinareOrizontal;
			unghiInclinareAnterior=pFizica->unghiInclinare;
		}
		else
		{
			unghiInclinareVertical=-(float)(D3DX_PI
											+(acos(D3DXVec3Dot(&VectorInclinareAripaVertical,
											&VectorAxaTransversalaOrizontalaMig))));
			unghiInclinareOrizontal=-(float)(D3DX_PI
											+(acos(D3DXVec3Dot(&VectorInclinareAripaOrizontal,
											&VectorAxaTransversalaOrizontalaMig))));
			if(unghiInclinareVertical>unghiInclinareOrizontal)
				pFizica->unghiInclinare=unghiInclinareVertical;
			else
				pFizica->unghiInclinare=unghiInclinareOrizontal;
			unghiInclinareAnterior=pFizica->unghiInclinare;
		}
	else*/
		//if(pFizica->unghiRotatieTransversalaMig==0.0f)
		if(pFizica->tetayGrade>=0.0f)	
			if(VectorDreaptaMig.y<=VectorStangaMig.y)		
			{
				unghiInclinareVertical=(float)(acos(D3DXVec3Dot(&VectorInclinareAripaVertical,
												&VectorAxaTransversalaOrizontalaMig)));		
				//unghiInclinareOrizontal=(float)(acos(D3DXVec3Dot(&VectorInclinareAripaOrizontal,
				//								&VectorAxaTransversalaOrizontalaMig)));		

				//if(unghiInclinareVertical<unghiInclinareOrizontal)
					pFizica->unghiInclinare=unghiInclinareVertical;					
				//else
				//	pFizica->unghiInclinare=unghiInclinareOrizontal;
			}			
			else		
			{
				unghiInclinareVertical=-(float)(acos(D3DXVec3Dot(&VectorInclinareAripaVertical,
												&VectorAxaTransversalaOrizontalaMig)));		
				//unghiInclinareOrizontal=-(float)(acos(D3DXVec3Dot(&VectorInclinareAripaOrizontal,
				//								&VectorAxaTransversalaOrizontalaMig)));		
				//if(unghiInclinareVertical>unghiInclinareOrizontal)
					pFizica->unghiInclinare=unghiInclinareVertical;
				//else
				//	pFizica->unghiInclinare=unghiInclinareOrizontal;
			}
		else

			if(VectorDreaptaMig.y<=VectorStangaMig.y)
			{
				unghiInclinareVertical=(float)(D3DX_PI
												-(acos(D3DXVec3Dot(&VectorInclinareAripaVertical,
												&VectorAxaTransversalaOrizontalaMig))));
				//unghiInclinareOrizontal=(float)(D3DX_PI
				//								-(acos(D3DXVec3Dot(&VectorInclinareAripaOrizontal,
				//								&VectorAxaTransversalaOrizontalaMig))));
				//if(unghiInclinareVertical>unghiInclinareOrizontal)
					pFizica->unghiInclinare=unghiInclinareVertical;
				//else
				//	pFizica->unghiInclinare=unghiInclinareOrizontal;
			}
			else
			{
				unghiInclinareVertical=-(float)(D3DX_PI
												-(acos(D3DXVec3Dot(&VectorInclinareAripaVertical,
												&VectorAxaTransversalaOrizontalaMig))));
				//unghiInclinareOrizontal=-(float)(D3DX_PI
				//								-(acos(D3DXVec3Dot(&VectorInclinareAripaOrizontal,
				//								&VectorAxaTransversalaOrizontalaMig))));
				//if(unghiInclinareVertical>unghiInclinareOrizontal)
					pFizica->unghiInclinare=unghiInclinareVertical;
				//else
				//	pFizica->unghiInclinare=unghiInclinareOrizontal;
			}

		/*if(pFizica->tetayGrade>=0.0f)	
			if(VectorDreaptaMig.y<=VectorStangaMig.y)					
				pFizica->unghiInclinare=-pFizica->unghiRotatieLongitudinalaMig;														
			else					
				pFizica->unghiInclinare=-pFizica->unghiRotatieLongitudinalaMig;																							
		else
			if(VectorDreaptaMig.y<=VectorStangaMig.y)			
				pFizica->unghiInclinare=-pFizica->unghiRotatieLongitudinalaMig;																							
			else			
				pFizica->unghiInclinare=-pFizica->unghiRotatieLongitudinalaMig;*/
}	
//-----------------------------------------------------------------------------
// Name: EndScene()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
void EndSceneAndPresent(HWND hWndMig)
{
	// End the scene
    gD3D->g_pD3DDevice->EndScene();

	// Present the backbuffer contents to the display
    gD3D->g_pD3DDevice->Present( NULL, NULL, hWndMig, NULL );
	
}
//-----------------------------------------------------------------------------
// Name: AfisajMig()
// Desc: Display avionics
//-----------------------------------------------------------------------------
/*void AfisajMig()
{
	int i,nrDigiti;
	char buffer[8],*buffer1;
	int  decimal, sign;
	long aliniereStanga,aliniereSusColoanaText,latimeText,inaltimeText,CountLowText;


	latimeText=10;
	inaltimeText=20;
	aliniereStanga=0;
	aliniereSusColoanaText=0;
	CountLowText=0;//init

	pFont->hFont=CreateFont(0,0,0,0,FW_MEDIUM,0,0,0,0,0,0,0,0,"Arial");	
	pFont->Init(gD3D->g_pD3DDevice);	
						
	//dezactivam ceata pentru a nu afecta textul
	gD3D->g_pD3DDevice->SetRenderState(D3DRS_FOGENABLE,false);
	
	//---------------------------------------------------
	//text
	pString="FPS[frames/s]:";
	Count=strlen("FPS[frames/s]:");		
	CountLowText=0;
	for(i=0;i<=Count;i++)
		if(islower(pString[i]))
			CountLowText+=(long)2.5;
	Rect.left=aliniereStanga;
	Rect.top=aliniereSusColoanaText;
	Rect.right=Rect.left+Count*latimeText-CountLowText;
	Rect.bottom=Rect.top+inaltimeText;
	Format=DT_LEFT;
	Color=D3DXCOLOR (1.0f,0.0f,0.0f,1.0f);
	pFont->WriteText(pString,Count,&Rect,Format,Color);
	
	/*char buffer[4];						
	_itoa((int)FrameRate,buffer,10);	

	for(i=0;i<8;i++)
		if(buffer[i]>='0') break;*/
	
	/*nrDigiti=5;	
	buffer1= _fcvt((float)FrameRate, nrDigiti, &decimal, &sign );
	//_itoa((int)(pFizica->roAer),buffer5,10);
	
	if(decimal>0)
	{
		for(int i=0;i<decimal;i++)
			buffer[i]=buffer1[i];
		buffer[decimal]='.';
		for(i=decimal+1;i<=10;i++)
			buffer[i]=buffer1[i-1];
	}
	else
	{
		buffer[0]='0';		
		buffer[1]='.';
		for(i=2;i<2+(-decimal);i++)
			buffer[i]='0';
		int k=i+10;
		int j=0;
		for(i;i<=k;i++)
		buffer[i]=buffer1[j++];
	}		


	//valoare							
	if(sign!=0)
	{
		Rect.left=Rect.right;	
		Rect.top=aliniereSusColoanaText;
		Rect.right=Rect.left+10;
		Rect.bottom=Rect.top+inaltimeText;
		Format=DT_LEFT;
		Color=D3DXCOLOR (1.0f,0.0f,0.0f,1.0f);		
		pFont->WriteText("-",1,&Rect,Format,Color);			
		
		Rect.left=Rect.right;//Count*latimeText-CountLowText;
		Count=nrDigiti;
		Rect.top=aliniereSusColoanaText;
		Rect.right=Rect.left+Count*latimeText;
		Rect.bottom=Rect.top+inaltimeText;
		pFont->WriteText(buffer,Count,&Rect,Format,Color);	
	}
	else
	{
		Rect.left=Rect.right;//Count*latimeText-CountLowText;
		Count=nrDigiti;
		Rect.top=aliniereSusColoanaText;
		Rect.right=Rect.left+Count*latimeText;
		Rect.bottom=Rect.top+inaltimeText;
		Format=DT_LEFT;
		Color=D3DXCOLOR (1.0f,0.0f,0.0f,1.0f);		
		pFont->WriteText(buffer,Count,&Rect,Format,Color);	
	}
	//------------------------------------------------------
	latimeText=10;
	inaltimeText=20;
	aliniereStanga=800;
	aliniereSusColoanaText=320;

	//text
	pString="ALT:";
	Count=strlen("ALT:");	
	CountLowText=0;
	for(i=0;i<=Count;i++)
		if(islower(pString[i]))
			CountLowText+=(long)2.5;
	Rect.left=aliniereStanga;
	Rect.top=aliniereSusColoanaText;//Rect.bottom anterior
	Rect.right=Rect.left+Count*latimeText-CountLowText;
	Rect.bottom=Rect.top+inaltimeText;
	Format=DT_LEFT;
	Color=D3DXCOLOR (1.0f,0.0f,0.0f,1.0f);
	pFont->WriteText(pString,Count,&Rect,Format,Color);
	
	/*char buffer[4];						
	_itoa((int)FrameRate,buffer,10);	

	for(i=0;i<8;i++)
		if(buffer[i]>='0') break;*/
	

	/*nrDigiti=8;	
	buffer1= _fcvt(pFizica->altM, nrDigiti, &decimal, &sign );	
	
	bool esteIntreg=false;
	esteIntreg=true;	

	if(decimal>0)
	{
		for(int i=0;i<decimal;i++)
			buffer[i]=buffer1[i];
		if(!esteIntreg) 
		{
			buffer[decimal]='.';
			for(i=decimal+1;i<=10;i++)
				buffer[i]=buffer1[i-1];
		}
	}
	else
	{
		buffer[0]='0';		
		buffer[1]='.';
		for(i=2;i<2+(-decimal);i++)
			buffer[i]='0';
		int k=i+10;
		int j=0;
		for(i;i<=k;i++)
		buffer[i]=buffer1[j++];
	}		


	//valoare							
	if(sign!=0)
	{
		Rect.left=Rect.right;			
		Rect.right=Rect.left+10;		
		Format=DT_LEFT;
		Color=D3DXCOLOR (1.0f,0.0f,0.0f,1.0f);		
		pFont->WriteText("-",1,&Rect,Format,Color);			
		
		Rect.left=Rect.right;//Count*latimeText-CountLowText;
		Count=nrDigiti;
		Rect.right=Rect.left+Count*latimeText;		
		pFont->WriteText(buffer,Count,&Rect,Format,Color);	
	}
	else
	{
		Rect.left=Rect.right;//Count*latimeText-CountLowText;
		Count=nrDigiti;		
		Rect.right=Rect.left+Count*latimeText;		
		Format=DT_LEFT;
		Color=D3DXCOLOR (1.0f,0.0f,0.0f,1.0f);		
		pFont->WriteText(buffer,Count,&Rect,Format,Color);	
	}

	/*pString="ALT[m]:";
	Count=7;
	Rect.left=800;
	Rect.top=320;
	Rect.right=860;
	Rect.bottom=340;
	Format=DT_LEFT;
	Color=D3DXCOLOR (1.0f,0.0f,0.0f,1.0f);
	pFont->WriteText(pString,Count,&Rect,Format,Color);					
	
	//buffer[0]=NULL;
	//buffer[1]=NULL;
	char buffer1[8];						
	//for(int i=0;i<8;i++)
	//	buffer[i]='x';
	long int alt;
	alt=(int)(pFizica->altM);
	_itoa(alt,buffer1,10);
	
	for(i=0;i<8;i++)
		if(buffer1[i]>='0') break;
	//i-=2;
	//k=k;
	Count=i-1;
	Rect.left=860;
	Rect.top=320;
	Rect.right=940;
	Rect.bottom=340;
	Format=DT_LEFT;
	Color=D3DXCOLOR (1.0f,0.0f,0.0f,1.0f);
	pFont->WriteText(buffer1,Count,&Rect,Format,Color);*/

	//------------------------------------------------------
	//text
	/*pString="TIME[s]:";
	Count=strlen("TIME[s]:");	
	CountLowText=0;
	for(i=0;i<=Count;i++)
		if(islower(pString[i]))
			CountLowText+=(long)2.5;
	Rect.left=aliniereStanga;
	Rect.top=Rect.bottom;//anterior
	Rect.right=Rect.left+Count*latimeText-CountLowText;
	Rect.bottom=Rect.top+inaltimeText;
	Format=DT_LEFT;
	Color=D3DXCOLOR (1.0f,0.0f,0.0f,1.0f);
	pFont->WriteText(pString,Count,&Rect,Format,Color);
	
	/*char buffer[4];						
	_itoa((int)FrameRate,buffer,10);	

	for(i=0;i<8;i++)
		if(buffer[i]>='0') break;*/
	
	/*nrDigiti=3;	
	buffer1= _fcvt(TimeMissionSecunde, nrDigiti, &decimal, &sign );	
	
	if(decimal>0)
	{
		for(int i=0;i<decimal;i++)
			buffer[i]=buffer1[i];
		buffer[decimal]='.';
		for(i=decimal+1;i<=10;i++)
			buffer[i]=buffer1[i-1];
	}
	else
	{
		buffer[0]='0';		
		buffer[1]='.';
		for(i=2;i<2+(-decimal);i++)
			buffer[i]='0';
		int k=i+10;
		int j=0;
		for(i;i<=k;i++)
		buffer[i]=buffer1[j++];
	}		


	//valoare							
	if(sign!=0)
	{
		Rect.left=Rect.right;			
		Rect.right=Rect.left+10;		
		Format=DT_LEFT;
		Color=D3DXCOLOR (1.0f,0.0f,0.0f,1.0f);		
		pFont->WriteText("-",1,&Rect,Format,Color);			
		
		Rect.left=Rect.right;//Count*latimeText-CountLowText;
		Count=nrDigiti;
		Rect.right=Rect.left+Count*latimeText;		
		pFont->WriteText(buffer,Count,&Rect,Format,Color);	
	}
	else
	{
		Rect.left=Rect.right;//Count*latimeText-CountLowText;
		Count=nrDigiti;		
		Rect.right=Rect.left+Count*latimeText;		
		Format=DT_LEFT;
		Color=D3DXCOLOR (1.0f,0.0f,0.0f,1.0f);		
		pFont->WriteText(buffer,Count,&Rect,Format,Color);	
	}

	/*pString="TIME[s]:";
	Count=8;
	Rect.left=800;
	Rect.top=340;
	Rect.right=860;
	Rect.bottom=360;
	Format=DT_LEFT;
	Color=D3DXCOLOR (0.0f,0.0f,0.0f,1.0f);
	pFont->WriteText(pString,Count,&Rect,Format,Color);					
			
	//int  decimal, sign;	
	char buffer2[6];	
	//char buffer22[6];

	//buffer2= _fcvt(TimeMissionFrame, 10, &decimal, &sign );
	_itoa((int)TimeMissionSecunde,buffer2,10);

	/*for(i=0;i<5;i++)
	{
		buffer22[i]=*buffer2;	
		buffer2++;
	}*/


	
	/*for(i=0;i<5;i++)
		if(buffer2[i]>='0') break;	
	//k=k;
	Count=i-1;	
	Rect.left=860;
	Rect.top=340;
	Rect.right=910;
	Rect.bottom=360;
	Format=DT_LEFT;
	Color=D3DXCOLOR (0.0f,0.0f,0.0f,1.0f);
	pFont->WriteText(buffer2,Count,&Rect,Format,Color);	*/
	//-----------------------------------------------------
	/*pString="vzfMig[km/h]:";
	Count=13;
	Rect.left=800;
	Rect.top=360;
	Rect.right=900;
	Rect.bottom=380;
	Format=DT_LEFT;
	Color=D3DXCOLOR (0.0f,0.0f,0.0f,1.0f);
	pFont->WriteText(pString,Count,&Rect,Format,Color);					
				
	char buffer3[6];	

	//buffer5= _fcvt( pFizica->vTf, 0, &decimal, &sign );
	float viteza;
	viteza=pFizica->vzfMig*3600/1000;
	_itoa((int)viteza,buffer3,10);

		
	for(i=0;i<5;i++)
		if(buffer3[i]>='0') break;	
	//k=k;
	Count=i-1;
	
	Rect.left=900;
	Rect.top=360;
	Rect.right=970;
	Rect.bottom=380;
	Format=DT_LEFT;
	Color=D3DXCOLOR (0.0f,0.0f,0.0f,1.0f);
	pFont->WriteText(buffer3,Count,&Rect,Format,Color);
	//-----------------------------------------------------	
	pString="ACCELERATIA[m/s2]:";
	if(pFizica->powerUp)
		pString="ACCELERATIA[m/s2]:";
	else
		if(pFizica->powerDown)
			pString="DECELERATIA[m/s2]:";
	Count=18;
	Rect.left=800;
	Rect.top=380;
	Rect.right=960;
	Rect.bottom=400;
	Format=DT_LEFT;
	Color=D3DXCOLOR (0.0f,0.0f,0.0f,1.0f);
	pFont->WriteText(pString,Count,&Rect,Format,Color);					
				
	char buffer4[6];	

	_itoa((int)pFizica->azMig,buffer4,10);
	if(pFizica->powerUp)
		_itoa((int)pFizica->azMig,buffer4,10);
	else
		if(pFizica->powerDown)
			_itoa((int)pFizica->azMig,buffer4,10);
	
	


	for(i=0;i<5;i++)
		if(buffer4[i]>='0') break;	
	//k=k;
	Count=i-1;
	Rect.left=960;
	Rect.top=380;
	Rect.right=1080;
	Rect.bottom=400;
	Format=DT_LEFT;
	Color=D3DXCOLOR (0.0f,0.0f,0.0f,1.0f);
	pFont->WriteText(buffer4,Count,&Rect,Format,Color);
	//-----------------------------------------------------	
	pString="DEPLASAREA:";
	Count=11;
	Rect.left=800;
	Rect.top=400;
	Rect.right=920;
	Rect.bottom=420;
	Format=DT_LEFT;
	Color=D3DXCOLOR (0.0f,0.0f,0.0f,1.0f);
	pFont->WriteText(pString,Count,&Rect,Format,Color);					
				
	char buffer6[6];	

	//buffer5= _fcvt( pFizica->vTf, 0, &decimal, &sign );
	_itoa((int)pFizica->tzMig,buffer6,10);

		
	for(i=0;i<5;i++)
		if(buffer6[i]>='0') break;	
	//k=k;
	Count=i-1;
	
	Rect.left=920;
	Rect.top=400;
	Rect.right=1010;
	Rect.bottom=420;
	Format=DT_LEFT;
	Color=D3DXCOLOR (0.0f,0.0f,0.0f,1.0f);
	pFont->WriteText(buffer6,Count,&Rect,Format,Color);
	//-----------------------------------------------------
	pString="tetaZ:";
	Count=6;
	Rect.left=800;
	Rect.top=420;
	Rect.right=860;
	Rect.bottom=440;
	Format=DT_LEFT;
	Color=D3DXCOLOR (0.0f,0.0f,0.0f,1.0f);
	pFont->WriteText(pString,Count,&Rect,Format,Color);					
				
	char buffer7[6];	

	//buffer5= _fcvt( pFizica->vTf, 0, &decimal, &sign );
	_itoa((int)pFizica->tetazGrade,buffer7,10);

		
	for(i=0;i<5;i++)
		if(buffer7[i]>='0') break;	
	//k=k;
	Count=i-1;
	
	Rect.left=860;
	Rect.top=420;
	Rect.right=910;
	Rect.bottom=440;
	Format=DT_LEFT;
	Color=D3DXCOLOR (0.0f,0.0f,0.0f,1.0f);
	pFont->WriteText(buffer7,Count,&Rect,Format,Color);
	//-----------------------------------------------------
	pString="tetaY:";
	Count=6;
	Rect.left=800;
	Rect.top=440;
	Rect.right=860;
	Rect.bottom=460;
	Format=DT_LEFT;
	Color=D3DXCOLOR (0.0f,0.0f,0.0f,1.0f);
	pFont->WriteText(pString,Count,&Rect,Format,Color);					
				
	char buffer8[6];	

	//buffer5= _fcvt( pFizica->vTf, 0, &decimal, &sign );
	_itoa((int)pFizica->tetayGrade,buffer8,10);

		
	for(i=0;i<5;i++)
		if(buffer8[i]>='0') break;	
	//k=k;
	Count=i-1;
	
	Rect.left=860;
	Rect.top=440;
	Rect.right=910;
	Rect.bottom=460;
	Format=DT_LEFT;
	Color=D3DXCOLOR (0.0f,0.0f,0.0f,1.0f);
	pFont->WriteText(buffer8,Count,&Rect,Format,Color);
	//-----------------------------------------------------
	pString="tetaX:";
	Count=6;
	Rect.left=800;
	Rect.top=460;
	Rect.right=860;
	Rect.bottom=480;
	Format=DT_LEFT;
	Color=D3DXCOLOR (0.0f,0.0f,0.0f,1.0f);
	pFont->WriteText(pString,Count,&Rect,Format,Color);					
				
	char buffer9[6];	

	//buffer5= _fcvt( pFizica->vTf, 0, &decimal, &sign );
	_itoa((int)pFizica->tetaxGrade,buffer9,10);

		
	for(i=0;i<5;i++)
		if(buffer8[i]>='0') break;	
	//k=k;
	Count=i-1;
	
	Rect.left=860;
	Rect.top=460;
	Rect.right=910;
	Rect.bottom=480;
	Format=DT_LEFT;
	Color=D3DXCOLOR (0.0f,0.0f,0.0f,1.0f);
	pFont->WriteText(buffer9,Count,&Rect,Format,Color);
	//-----------------------------------------------------
	pString="TRACTIUNE:";
	Count=10;
	Rect.left=800;
	Rect.top=748;
	Rect.right=900;
	Rect.bottom=768;
	Format=DT_LEFT;
	Color=D3DXCOLOR (0.0f,0.0f,0.0f,1.0f);
	pFont->WriteText(pString,Count,&Rect,Format,Color);					
	
	
	char buffer5[8];							
	_itoa((int)pFizica->Tf,buffer5,10);
	
	for(i=0;i<4;i++)
		if(buffer5[i]>='0') break;
	//i-=2;
	//k=k;
	Count=i-1;
	Rect.left=900;
	Rect.top=748;
	Rect.right=980;
	Rect.bottom=768;
	Format=DT_LEFT;
	Color=D3DXCOLOR (0.0f,0.0f,0.0f,1.0f);
	pFont->WriteText(buffer5,Count,&Rect,Format,Color);
}*/
//-----------------------------------------------------------------------------
void AfisajSistem()
{	
	//pFont->hFont=CreateFont(0,0,0,0,FW_BOLD,0,true,0,0,0,0,0,0,"Arial");	
	//pFont->Init(gD3D->g_pD3DDevice);

	long aliniereStanga;
	long aliniereSus;

	aliniereStanga=0;//1024-26*(pFont->hFonts[2].latimeCaracter+2); 
	aliniereSus=0;//768-pFont->hFonts[2].inaltimeCaracter; 

	pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[2],
						"Sistem",
						D3DXCOLOR (0.0f,0.0f,1.0f,0.5f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[2].latimeCaracter,pFont->hFonts[2].inaltimeCaracter);

	//pFont->pFont->Release();

	//pFont->hFont=CreateFont(0,0,0,0,FW_MEDIUM,0,0,0,0,0,0,0,0,"Arial");	
	//pFont->Init(gD3D->g_pD3DDevice);	
	
	aliniereSus+=pFont->hFonts[2].inaltimeCaracter;
	pFont->AfiseazaTextSiIntreg(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"FPSstabilit[frames/second]:",
								pFizica->fps,5,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus,
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-115);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiIntreg(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"fpsMediu[frames/second]:",
								pFizica->fpsMediu,5,//todo(Nicu): re-enable
								//pFizica->fps,5,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus,
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-95);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiIntreg(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"FPScalculat[frames/second]:",
								(float)FrameRate,5,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus,
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-115);

	

	/*aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"tpf[s]:",
								(float)pFizica->tpf,8,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus,
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-33);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiIntreg(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"lpFrequency[ms]:",
								(float)lpFrequency,8,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus,
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-60);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiIntreg(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"timeCount[ms]:",
								(float)timeCount,8,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus,
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-30);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiIntreg(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"nextTime[ms]:",
								(float)nextTime,8,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus,
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-30);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiIntreg(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"curentTime[ms]:",
								(float)curentTime,8,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus,
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-30);
	*/				
}
//-----------------------------------------------------------------------------

void AfisajOrientareSpatiala()
{

	//pFont->hFont=CreateFont(0,0,0,0,FW_BOLD,0,true,0,0,0,0,0,0,"Arial");	
	//pFont->Init(gD3D->g_pD3DDevice);
	
	long aliniereStanga; 
	long aliniereSus; 	
	
	aliniereStanga=10; 
	aliniereSus=60; 

	pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[2],
						"Orientare spatiala",
						D3DXCOLOR (0.0f,0.0f,1.0f,0.5f),
						aliniereStanga,aliniereSus, 
						pFont->hFonts[2].latimeCaracter,pFont->hFonts[2].inaltimeCaracter);

	//pFont->pFont->Release();

	//pFont->hFont=CreateFont(0,0,0,0,FW_MEDIUM,0,0,0,0,0,0,0,0,"Arial");	
	//pFont->Init(gD3D->g_pD3DDevice);	
	
	aliniereSus+=pFont->hFonts[2].inaltimeCaracter;	
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "ALT[m]:",
												  (float)pFizica->altM,7,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus, 
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -15);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;	
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "VectorCentruRoti(altUnitWorld)[unitWorld]:",
												  (float)pFizica->VectorCentruRoti.y,7,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus, 
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -175);

	/*aliniereSus+=pFont->hFonts[1].inaltimeCaracter;	
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "VectorCentruRotiTest.y[unitWorld]:",
												  (float)pFizica->VectorCentruRotiTest.y,7,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus, 
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -120);*/
	
	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"tetaX[grade]:",
								(float)pFizica->tetaxGrade,4,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus, 
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-50);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"tetaY[grade]:",
								(float)pFizica->tetayGrade,4,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus, 
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-50);
	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"tetaZ[grade]:",
								(float)pFizica->tetazGrade,4,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus, 
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-50);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"tetaX[radiani]:",
								(float)pFizica->tetaxRadiani,6,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus, 
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-60);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"tetaY[radiani]:",
								(float)pFizica->tetayRadiani,6,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus, 
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-60);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"tetaZ[radiani]:",
								(float)pFizica->tetazRadiani,6,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus, 
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-60);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"unghiRotTranMig[radiani]:",
								(float)pFizica->unghiRotatieTransversalaMig,6,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus, 
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-85);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"unghiRotTranMig[grade]:",
								(float)D3DXToDegree(pFizica->unghiRotatieTransversalaMig),6,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus, 
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-70);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"unghiDiferenta[grade]:",
								(float)D3DXToDegree(pFizica->unghiRotatieTransversalaMigAnterior-pFizica->unghiRotatieTransversalaMig),6,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus, 
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-70);
	
	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"unghiStabilizator[grade]:",
								(float)pFizica->unghiBracareStabilizator,6,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus, 
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-100);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"unghiBracareMinim[grade]:",
								(float)pFizica->unghiBracareMinim,6,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus, 
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-90);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"unghiBracareMaxim[grade]:",
								(float)pFizica->unghiBracareMaxim,6,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus, 
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-90);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"rataEfortBracare[grade]:",
								(float)pFizica->rataEfortBracare,6,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus, 
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-100);			

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"unghiRotLongMig[radiani]:",
								(float)pFizica->unghiRotatieLongitudinalaMig,6,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus, 
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-80);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"unghiRotLongMig[grade]:",
								(float)D3DXToDegree(pFizica->unghiRotatieLongitudinalaMig),6,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus, 
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-80);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"unghiEleroane[grade]:",
								(float)pFizica->unghiBracareEleroane,6,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus, 
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-75);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"unghiRotVertMig[radiani]:",
								(float)pFizica->unghiRotatieVerticalaMig,6,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus, 
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-80);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"unghiRotVertMig[grade]:",
								(float)D3DXToDegree(pFizica->unghiRotatieVerticalaMig),6,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus, 
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-80);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"unghiAmpenaj[grade]:",
								(float)pFizica->unghiBracareAmpenaj,6,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus, 
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-75);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"alpha[grade]:",
								(float)pFizica->alphaAtacGrade,8,
								D3DXCOLOR (1.0f,0.5f,0.0f,1.0f),
								aliniereStanga,aliniereSus, 
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-50);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"alpha[radiani]:",
								(float)pFizica->alphaAtacRadiani,8,
								D3DXCOLOR (1.0f,0.5f,0.0f,1.0f),
								aliniereStanga,aliniereSus, 
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-50);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"unghiVitezeLocale[grade]:",
								(float)(D3DXToDegree(pFizica->unghiVitezeLocale)),8,
								D3DXCOLOR (1.0f,0.5f,0.0f,1.0f),
								aliniereStanga,aliniereSus, 
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-100);	


	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"unghiNormalaOrizontArtificial[grade]:",
								(float)(D3DXToDegree(unghiNormalaOrizontArtificial)),8,
								D3DXCOLOR (1.0f,0.5f,0.0f,1.0f),
								aliniereStanga,aliniereSus, 
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-160);		

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"unghiInclinareAnterior[grade]:",
								(float)(D3DXToDegree(unghiInclinareAnterior)),8,
								D3DXCOLOR (1.0f,0.5f,0.0f,1.0f),
								aliniereStanga,aliniereSus, 
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-130);	


	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"unghiInclinareVertical[grade]:",
								(float)(D3DXToDegree(unghiInclinareVertical)),8,
								D3DXCOLOR (1.0f,0.5f,0.0f,1.0f),
								aliniereStanga,aliniereSus, 
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-130);	

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"unghiInclinareOrizontal[grade]:",
								(float)(D3DXToDegree(unghiInclinareOrizontal)),8,
								D3DXCOLOR (1.0f,0.5f,0.0f,1.0f),
								aliniereStanga,aliniereSus, 
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-130);	
	
	
	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"unghiInclinare[grade]:",
								(float)(D3DXToDegree(pFizica->unghiInclinare)),6,
								D3DXCOLOR (1.0f,0.5f,0.0f,1.0f),
								aliniereStanga,aliniereSus, 
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-100);	
		
	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	if(pFizica->kLong==true)
		pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[1],
						"kLong:true",
						D3DXCOLOR (0.0f,0.0f,0.0f,0.5f),
						aliniereStanga,aliniereSus, 
						pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter);
	else
		pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[1],
						"kLong:false",
						D3DXCOLOR (0.0f,0.0f,0.0f,0.5f),
						aliniereStanga,aliniereSus, 
						pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"unghiRotatieLongitudinalaMigPerturbatii:",
								(float)(pFizica->unghiRotatieLongitudinalaMigPerturbatii),6,
								D3DXCOLOR (1.0f,0.5f,0.0f,1.0f),
								aliniereStanga,aliniereSus, 
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-170);		
	

	//pFont->pFont->Release();	
}
//-----------------------------------------------------------------------------
void AfisajParametriAerodinamici()
{
	long aliniereStanga; 
	long aliniereSus; 	
	
	aliniereStanga=420; 
	aliniereSus=0; 

	//pFont->hFont=CreateFont(0,0,0,0,FW_BOLD,0,true,0,0,0,0,0,0,"Arial");	
	//pFont->Init(gD3D->g_pD3DDevice);	

	pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[2],
						"Parametri aerodinamici",
						D3DXCOLOR (0.0f,0.0f,1.0f,0.5f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[2].latimeCaracter,pFont->hFonts[2].inaltimeCaracter);

	//pFont->pFont->Release();

	//pFont->hFont=CreateFont(0,0,0,0,FW_MEDIUM,0,0,0,0,0,0,0,0,"Arial");	
	//pFont->Init(gD3D->g_pD3DDevice);	
	
	aliniereSus+=pFont->hFonts[2].inaltimeCaracter;
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"Taer[gradeCelsius]:",
								(float)pFizica->T,4,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus,
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-70);
	
	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"patm[KPa]:",
								(float)pFizica->patm,6,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus,
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-30);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"roAer[Kgf*s2/m4]:",
								(float)pFizica->roAer,4,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus,
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-55);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"Crz:",
								(float)pFizica->Crz,8,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus,
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-12);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"Cry:",
								(float)pFizica->Cry,8,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus,
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-12);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"Crx:",
								(float)pFizica->Crx,8,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus,
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-12);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"Cz:",
								(float)pFizica->Cz,8,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus,
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-8);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"Czstabilizator:",
								(float)pFizica->Czstabilizator,8,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus,
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-63);		

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"Czeleroane:",
								(float)pFizica->Czeleroane,8,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus,
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-35);		
	//pFont->pFont->Release();
}
//-----------------------------------------------------------------------------
void AfisajComenziTest()
{
	long aliniereStanga; 
	long aliniereSus; 	
	
	aliniereStanga=420; 
	aliniereSus=200; 

	pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[2],
						"Comenzi",
						D3DXCOLOR (0.0f,0.0f,1.0f,0.5f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[2].latimeCaracter,pFont->hFonts[2].inaltimeCaracter);		

	aliniereSus+=pFont->hFonts[2].inaltimeCaracter; 	
	if(pFizica->flagFlapsBagat==TRUE)			
		pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[1],
						"flagFlapsBagat:TRUE",
						D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter);
	else
		pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[1],
						"flagFlapsBagat:FALSE",
						D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 	
	if(pFizica->flagFlapsTakeOff==TRUE)			
		pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[1],
						"flagFlapsTakeOff:TRUE",
						D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter);
	else
		pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[1],
						"flagFlapsTakeOff:FALSE",
						D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 	
	if(pFizica->flagFlapsLanding==TRUE)			
		pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[1],
						"flagFlapsLanding:TRUE",
						D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter);
	else
		pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[1],
						"flagFlapsLanding:FALSE",
						D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 	
	if(pFizica->flagDecolare==TRUE)			
		pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[1],
						"flagDecolare:TRUE",
						D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter);
	else
		pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[1],
						"flagDecolare:FALSE",
						D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 	
	if(pFizica->takeOff==TRUE)			
		pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[1],
						"takeOff:TRUE",
						D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter);
	else
		pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[1],
						"takeOff:FALSE",
						D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter);


	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 	
	if(pFizica->flagAterizare==TRUE)			
		pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[1],
						"flagAterizare:TRUE",
						D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter);
	else
		pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[1],
						"flagAterizare:FALSE",
						D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter);	

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"VectorRoataFata.y:",
								(float)pFizica->VectorRoataFata.y,8,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus,
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-75);			
	
	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"VectorCentruRoti.y:",
								(float)pFizica->VectorCentruRoti.y,8,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus,
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-75);			
}
//-----------------------------------------------------------------------------
void AfisajComenziFlapsuri()
{
	long aliniereStanga; 
	long aliniereSus; 	

	contorAfisajComenziFlapsuri++;
	
	aliniereStanga=750; 
	aliniereSus=120; 
		
	if(pFizica->flagFlapsBagat==TRUE)			
		pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[1],
						"Flaps:Bagat...",
						D3DXCOLOR (0.0f,0.0f,0.0f,0.7f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter);
	/*else
		pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[1],
						"flagFlapsBagat:FALSE",
						D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter);*/

	//aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 	
	if(pFizica->flagFlapsTakeOff==TRUE)			
		pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[1],
						"Flaps:TakeOff...",
						D3DXCOLOR (0.0f,0.0f,0.0f,0.7f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter);
	/*else
		pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[1],
						"flagFlapsTakeOff:FALSE",
						D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter);*/

	//aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 	
	if(pFizica->flagFlapsLanding==TRUE)			
		pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[1],
						"Flaps:Landing...",
						D3DXCOLOR (0.0f,0.0f,0.0f,0.7f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter);
	
	/*else
		pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[1],
						"flagFlapsLanding:FALSE",
						D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter);	*/
}
//-----------------------------------------------------------------------------
void AfisajComenziMotor()
{
	long aliniereStanga; 
	long aliniereSus; 	

	contorAfisajComenziMotor++;
	
	aliniereStanga=750; 
	aliniereSus=100; 
		
	if(pFizica->flagStartEngine==TRUE)			
		pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[1],
						"Start engine...",
						D3DXCOLOR (0.0f,0.0f,0.0f,0.7f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter);

	if(pFizica->flagStopEngine==TRUE)			
		pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[1],
						"Stop engine...",
						D3DXCOLOR (0.0f,0.0f,0.0f,0.7f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter);	
	/*else
		pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[1],
						"flagFlapsLanding:FALSE",
						D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter);	*/
}

//-----------------------------------------------------------------------------
void AfisajForte()
{
	long aliniereStanga; 
	long aliniereSus; 	
	
	aliniereStanga=640; 
	aliniereSus=0; 	

	pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[2],
						"Forte",
						D3DXCOLOR (0.0f,0.0f,1.0f,0.5f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[2].latimeCaracter,pFont->hFonts[2].inaltimeCaracter);
		
	aliniereSus+=pFont->hFonts[2].inaltimeCaracter; 	
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"G[Kgf]:",
								(float)pFizica->G,7,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus,
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-20);

	/*aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 	
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"Ti[Kgf]:",
								(float)pFizica->Tinstant,7,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus,
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-28);
	*/

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 	
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"Tf[Kgf]:",
								(float)pFizica->Tf,7,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus,
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-28);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 	
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"Ffrecare[Kgf]:",
								(float)pFizica->Ffrecare,7,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus,
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-50);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 	
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"Ffranare[Kgf]:",
								(float)pFizica->Ffranare,7,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus,
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-50);

	/*aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 	
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"N[Kgf]:",
								(float)pFizica->N,7,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus,
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-20);
	*/

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 	
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"Rxf[Kgf]:",
								(float)pFizica->Rxf,7,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus,
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-30);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 	
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"Ryf[Kgf]:",
								(float)pFizica->Ryf,7,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus,
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-30);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 	
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"Rzf[Kgf]:",
								(float)pFizica->Rzf,7,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus,
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-30);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 	
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"Pf[Kgf]:",
								(float)pFizica->Pf,7,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus,
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-30);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 	
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"Pfaripa[Kgf]:",
								(float)pFizica->Pfaripa,7,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus,
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-30);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 	
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"Pfstabilizator[Kgf]:",
								(float)pFizica->Pfstabilizator,7,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus,
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-82);

	/*aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 	
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"Fcfx[Kgf]:",
								(float)pFizica->Fcfx,7,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus,
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-35);
	*/
	
	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 	
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"Fcfy[Kgf]:",
								(float)pFizica->Fcfy,7,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus,
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-35);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 	
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"FreactiuneSol[Kgf]:",
								(float)pFizica->FreactiuneSol,7,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus,
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-70);

	/*aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 	
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"Freactiune.x[Kgf]:",
								(float)pFizica->Freactiune.compX,7,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus,
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-70);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 	
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"Freactiune.y[Kgf]:",
								(float)pFizica->Freactiune.compY,7,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus,
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-70);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 	
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"Freactiune.z[Kgf]:",
								(float)pFizica->Freactiune.compZ,7,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus,
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-70);	
	*/

	//impulsuri
	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 	
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"impulsMig[Kg*m/s]:",
								(float)pFizica->impulsMig,7,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus,
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-50);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 	
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"impulsMigX[Kg*m/s]:",
								(float)pFizica->impulsMigX,7,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus,
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-50);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 	
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"impulsMigY[Kg*m/s]:",
								(float)pFizica->impulsMigY,7,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus,
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-50);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 	
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"impulsMigZ[Kg*m/s]:",
								(float)pFizica->impulsMigZ,7,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus,
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-50);
	
	/*aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 	
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"RezultantaForte[Kgf]:",
								(float)pFizica->RezultantaForte,7,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus,
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-80);
	*/

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 	
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"RezultantaX:",
								(float)pFizica->RezultantaX,7,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus,
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-40);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 	
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"RezultantaY:",
								(float)pFizica->RezultantaY,7,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus,
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-40);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 	
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"RezultantaZ:",
								(float)pFizica->RezultantaZ,7,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus,
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-40);

	/*aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 									
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "vecRezultantaForte.x:",
								 (float)(pFizica->vecRezultantaForte.x),7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus,
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -80);	
	
	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 									
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "vecRezultantaForte.y:",
								 (float)(pFizica->vecRezultantaForte.y),7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus,
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -80);	

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 									
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "vecRezultantaForte.z:",
								 (float)(pFizica->vecRezultantaForte.z),7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus,
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -80);*/

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 									
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "temp1:",
								 (float)(pFizica->temp1),7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus,
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -20);
	
	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 									
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "temp2:",
								 (float)(pFizica->temp2),7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus,
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -20);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 									
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "ForteCg:",
								 (float)(pFizica->ForteCg),7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus,
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -25);
	
	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 									
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "ForteCp:",
								 (float)(pFizica->ForteCp),7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus,
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -25);	

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 									
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "FortaContact:",
								 (float)(pFizica->FortaContact),7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus,
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -25);	

}
//-----------------------------------------------------------------------------
void AfisajAcceleratii()
{
	long aliniereStanga; 
	long aliniereSus; 	
	
	aliniereStanga=860; 
	aliniereSus=0; 		

	pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[2],
						"Acceleratii",
						D3DXCOLOR (0.0f,0.0f,1.0f,0.5f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[2].latimeCaracter,pFont->hFonts[2].inaltimeCaracter);
		
	aliniereSus+=pFont->hFonts[2].inaltimeCaracter; 			
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"g[m/s2]:",
								(float)pFizica->g,5,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus,
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-28);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 			
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "axMig[m/s2]:",
												  (float)pFizica->axMig,6,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus,
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -38);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 			
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "ayMig[m/s2]:",
												  (float)pFizica->ayMig,4,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus,
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -38);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 			
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "azMig[m/s2]:",
												  (float)pFizica->azMig,4,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus,
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -38);
	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 			
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "aMig[m/s2]:",
												  (float)pFizica->aMig,4,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus,
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -38);
}	
//-----------------------------------------------------------------------------
void AfisajViteze()
{
	long aliniereStanga; 
	long aliniereSus; 	
	
	aliniereStanga=860; 
	aliniereSus=100; 		

	pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[2],
						"Viteze",
						D3DXCOLOR (0.0f,0.0f,1.0f,0.5f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[2].latimeCaracter,pFont->hFonts[2].inaltimeCaracter);
		
	aliniereSus+=pFont->hFonts[2].inaltimeCaracter; 						
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "M:",
												  (float)((pFizica->vMig*1000.0f/3600.0f)/pFizica->vs),4,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus,
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  0);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 						
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "vMig[km/h]:",
												  (float)(pFizica->vMig),4,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus,
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -30);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 						
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "vxfMig[Km/h]:",
												  (float)(pFizica->vxfMig*3600/1000),4,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus,
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -35);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 						
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "vxiMig[Km/h]:",
												  (float)(pFizica->vxiMig*3600/1000),4,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus,
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -35);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 						
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "vyfMig[Km/h]:",
												  (float)(pFizica->vyfMig*3600/1000),4,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus,
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -35);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 						
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "vyiMig[Km/h]:",
												  (float)(pFizica->vyiMig*3600/1000),4,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus,
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -35);
	
	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 						
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "vzfMig[Km/h]:",
												  (float)(pFizica->vzfMig*3600/1000),4,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus,
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -35);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 						
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "vziMig[Km/h]:",
												  (float)(pFizica->vziMig*3600/1000),4,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus,
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -35);	
}	
//-----------------------------------------------------------------------------
void AfisajDeplasari()
{
	long aliniereStanga; 
	long aliniereSus; 	
	
	aliniereStanga=860; 
	aliniereSus=280; 		

	pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[2],
						"Deplasari",
						D3DXCOLOR (0.0f,0.0f,1.0f,0.5f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[2].latimeCaracter,pFont->hFonts[2].inaltimeCaracter);
		
	aliniereSus+=pFont->hFonts[2].inaltimeCaracter; 									
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "txMig[m]:",
								 (float)(pFizica->txMig),7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus,
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -27);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 									
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "tyMig[m]:",
								 (float)(pFizica->tyMig),7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus,
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -27);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 									
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "tzMig[m]:",
								 (float)(pFizica->tzMig),7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus,
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -27);	

	aliniereStanga=820; 
	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 									
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "tan(tetaz)*tzMig[m]:",
								 (float)(-(float)(tan(pFizica->tetazRadiani)*fabs(pFizica->tzMig))),7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus,
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -85);		
}	
//-----------------------------------------------------------------------------
void AfisajColiziuni()
{
	long aliniereStanga; 
	long aliniereSus; 	
	
	aliniereStanga=230; 
	aliniereSus=240; 		

	pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[2],
						"Coliziuni",
						D3DXCOLOR (0.0f,0.0f,1.0f,0.5f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[2].latimeCaracter,pFont->hFonts[2].inaltimeCaracter);

	aliniereSus+=pFont->hFonts[2].inaltimeCaracter; 									
	if(pFizica->dupaContact==TRUE)
		pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[1],
						"dupaContact:TRUE",
						D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter);
	else
		pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[1],
						"dupaContact:FALSE",
						D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter);

		
	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 									
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "distPanaLaContact[m]:",
								 (float)(pFizica->distPanaLaContact),12,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus,
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -70);	

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 									
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "dist*cos(unghiVOx):",
								 (float)(fabs(pFizica->distPanaLaContact*cos(pFizica->unghiVecVitMigOxLocal))),12,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus,
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -70);	

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 									
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "dist*cos(unghiVOy):",
								 (float)(fabs(pFizica->distPanaLaContact*cos(pFizica->unghiVecVitMigOyLocal))),12,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus,
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -70);	

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 									
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "dist*cos(unghiVOz):",
								 (float)(fabs(pFizica->distPanaLaContact*cos(pFizica->unghiVecVitMigOzLocal))),12,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus,
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -70);	

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;	
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "index:",
												  (float)pFizica->index,7,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus, 
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -20);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;	
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "indexVecDistMin:",
												  (float)pFizica->indexVecDistMin,7,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus, 
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -20);
	
	//dir vMig
	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;	
	if(pFizica->tablouVectoriTestati[pFizica->index].hit==TRUE)
		pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[1],
						"hit:TRUE",
						D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter);
	else
		pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[1],
						"hit:FALSE",
						D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;	
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "faceIndex:",
												  (float)pFizica->tablouVectoriTestati[pFizica->index].faceIndex,7,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus, 
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -35);			

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;	
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "distanta:",
												  (float)pFizica->tablouVectoriTestati[pFizica->index].distanta,7,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus, 
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -40);
	
	//1
	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;	
	if(pFizica->tablouVectoriTestati[pFizica->index].hit1==TRUE)
		pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[1],
						"hit1:TRUE",
						D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter);
	else
		pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[1],
						"hit1:FALSE",
						D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;	
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "faceIndex1:",
												  (float)pFizica->tablouVectoriTestati[pFizica->index].faceIndex1,7,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus, 
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -35);			

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;	
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "distanta1:",
												  (float)pFizica->tablouVectoriTestati[pFizica->index].distanta1,7,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus, 
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -40);
	//2	
	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;	
	if(pFizica->tablouVectoriTestati[pFizica->index].hit2==TRUE)
		pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[1],
						"hit2:TRUE",
						D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter);
	else
		pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[1],
						"hit2:FALSE",
						D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;	
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "faceIndex2:",
												  (float)pFizica->tablouVectoriTestati[pFizica->index].faceIndex2,7,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus, 
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -35);			

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;	
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "distanta2:",
												  (float)pFizica->tablouVectoriTestati[pFizica->index].distanta2,7,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus, 
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -40);
	

	//3	
	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;	
	if(pFizica->tablouVectoriTestati[pFizica->index].hit3==TRUE)
		pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[1],
						"hit3:TRUE",
						D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter);
	else
		pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[1],
						"hit3:FALSE",
						D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;	
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "faceIndex3:",
												  (float)pFizica->tablouVectoriTestati[pFizica->index].faceIndex3,7,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus, 
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -35);			

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;	
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "distanta3:",
												  (float)pFizica->tablouVectoriTestati[pFizica->index].distanta3,7,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus, 
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -40);

	//origine axe loclale
	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;	
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "origineAxeLocale.x:",
												  (float)pFizica->origineAxeLocale.x,7,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus, 
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -80);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;	
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "origineAxeLocale.y:",
												  (float)pFizica->origineAxeLocale.y,7,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus, 
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -80);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;	
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "origineAxeLocale.z:",
												  (float)pFizica->origineAxeLocale.z,7,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus, 
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -80);

	
	//normalaFata
	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;	
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "normalaFata.x:",
												  (float)pFizica->tablouVectoriTestati[pFizica->index].normala.x,7,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus, 
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -45);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;	
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "normalaFata.y:",
												  (float)pFizica->tablouVectoriTestati[pFizica->index].normala.y,7,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus, 
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -45);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;	
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "normalaFata.z:",
												  (float)pFizica->tablouVectoriTestati[pFizica->index].normala.z,7,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus, 
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												 -45);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;	
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "unghiNormalaAxaOx:",
												  (float)D3DXToDegree(pFizica->unghiNormalaAxaOx),7,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus, 
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												 -35);	

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;	
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "unghiNormalaAxaOy:",
												  (float)D3DXToDegree(pFizica->unghiNormalaAxaOy),7,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus, 
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												 -35);	

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;	
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "unghiNormalaAxaOz:",
												  (float)D3DXToDegree(pFizica->unghiNormalaAxaOz),7,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus, 
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												 -35);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;	
	if(pFizica->hitInainte==TRUE)
		pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[1],
						"hitInainte:TRUE",
						D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter);
	else
		pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[1],
						"hitInainte:FALSE",
						D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter);


	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;	
	if(pFizica->hitInapoi==TRUE)
		pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[1],
						"hitInapoi:TRUE",
						D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter);
	else
		pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[1],
						"hitInapoi:FALSE",
						D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter);


	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;	
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "Freactiune:",
												  (float)pFizica->tablouVectoriTestati[pFizica->index].Freactiune,7,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus, 
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -45);

	//vector actual
	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;	
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "vectorActual.x:",
												  (float)pFizica->tablouVectoriTestati[pFizica->index].vectorActual.x,7,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus, 
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -45);
	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;	
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "vectorActual.y:",
												  (float)pFizica->tablouVectoriTestati[pFizica->index].vectorActual.y,7,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus, 
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -45);
	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;	
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "vectorActual.z:",
												  (float)pFizica->tablouVectoriTestati[pFizica->index].vectorActual.z,7,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus, 
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -45);

	//vector anticipat	
	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;	
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "vectorAnticipat.x:",
												  (float)pFizica->tablouVectoriTestati[pFizica->index].vectorAnticipat.x,7,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus, 
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -65);
	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;	
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "vectorAnticipat.y:",
												  (float)pFizica->tablouVectoriTestati[pFizica->index].vectorAnticipat.y,7,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus, 
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -65);
	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;	
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "vectorAnticipat.z:",
												  (float)pFizica->tablouVectoriTestati[pFizica->index].vectorAnticipat.z,7,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus, 
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -65);

	aliniereStanga=360; 
	aliniereSus=480; 		
	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;	
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "vecVxyzfMigLocalContact.x:",
												  (float)pFizica->vecVxyzfMigLocalContact.x,7,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus, 
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -85);
	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;	
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "vecVxyzfMigLocalContact.y:",
												  (float)pFizica->vecVxyzfMigLocalContact.y,7,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus, 
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -85);
	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;	
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "vecVxyzfMigLocalContact.z:",
												  (float)pFizica->vecVxyzfMigLocalContact.z,7,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus, 
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -85);

	aliniereStanga=440;
	//
	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;	
	if(pFizica->hitVecVxfMigLocal==TRUE)
		pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[1],
						"hitVecVxfMigLocal:TRUE",
						D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter);
	else
		pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[1],
						"hitVecVxfMigLocal:FALSE",
						D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;	
	if(pFizica->hitVecVyfMigLocal==TRUE)
		pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[1],
						"hitVecVyfMigLocal:TRUE",
						D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter);
	else
		pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[1],
						"hitVecVyfMigLocal:FALSE",
						D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;	
	if(pFizica->hitVecVzfMigLocal==TRUE)
		pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[1],
						"hitVecVzfMigLocal:TRUE",
						D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter);
	else
		pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[1],
						"hitVecVzfMigLocal:FALSE",
						D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;	
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "distantaVxLocal:",
												  (float)D3DXToDegree(pFizica->distantaVxLocal),7,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus, 
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -65);
	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;	
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "distantaVyLocal:",
												  (float)D3DXToDegree(pFizica->distantaVyLocal),7,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus, 
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -65);
	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;	
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "distantaVzLocal:",
												  (float)D3DXToDegree(pFizica->distantaVzLocal),7,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus, 
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,						
												  -65);

	 
	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;	
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "txMigContact:",
												  (float)pFizica->txMigContact,7,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus, 
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -40);
	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;	
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "tyMigContact:",
												  (float)pFizica->tyMigContact,7,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus, 
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -40);
	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;	
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "tzMigContact:",
												  (float)pFizica->tzMigContact,7,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus, 
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -40);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;	
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "tyMigSalvat:",
												  (float)pFizica->tyMigSalvat,7,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus, 
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -40);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;	
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "RadiusBoundSphere:",
												  (float)pFizica->RadiusBoundSphere,7,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga-20,aliniereSus, 
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -80);	

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;	
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "distContactVectorCentruRoti:",
												  (float)pFizica->distContactVectorCentruRoti,7,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga-20,aliniereSus, 
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -120);		
}	
//-----------------------------------------------------------------------------
void AfisajVectori()
{
	long aliniereStanga; 
	long aliniereSus; 	
	
	aliniereStanga=680; 
	aliniereSus=380; 		

	pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[2],
						"Vectori",
						D3DXCOLOR (0.0f,0.0f,1.0f,0.5f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[2].latimeCaracter,pFont->hFonts[2].inaltimeCaracter);
			

	aliniereSus+=pFont->hFonts[2].inaltimeCaracter; 									
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "vecOrigine.x:",
								 (float)(pFizica->vecOrigine.x),7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus,
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -40);	

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 									
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "vecOrigine.y:",
								 (float)(pFizica->vecOrigine.y),7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus,
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -80);	

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 									
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "vecOrigine.z:",
								 (float)(pFizica->vecOrigine.z),7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus,
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -80);	

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 									
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "vecVxyzfMigLocalContact.x:",
								 (float)(pFizica->vecVxyzfMigLocalContact.x),7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus,
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -90);	

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 									
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "vecVxyzfMigLocalContact.y:",
								 (float)(pFizica->vecVxyzfMigLocalContact.y),7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus,
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -90);	

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 									
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "vecVxyzfMigLocalContact.z:",
								 (float)(pFizica->vecVxyzfMigLocalContact.z),7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus,
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -90);	


	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 									
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "vectorBratFortaContact.x:",
								 (float)(pFizica->vectorBratFortaContact.x),7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus,
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -100);	
	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 									
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "vectorBratFortaContact.y:",
								 (float)(pFizica->vectorBratFortaContact.y),7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus,
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -100);	
	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 									
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "vectorBratFortaContact.z:",
								 (float)(pFizica->vectorBratFortaContact.z),7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus,
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -100);	

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 									
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "vectorAxaRotatieContact.x:",
								 (float)(pFizica->vectorAxaRotatieContact.x),7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus,
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -110);	



	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 									
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "vectorAxaRotatieContact.y:",
								 (float)(pFizica->vectorAxaRotatieContact.y),7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus,
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -110);	

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 									
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "vectorAxaRotatieContact.z:",
								 (float)(pFizica->vectorAxaRotatieContact.z),7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus,
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -110);	


	/*aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 									
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "vecVzfMig.y:",
								 (float)(pFizica->vecVzfMig.y),7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus,
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -30);	

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 									
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "vecVxfMigLocal:",
								 (float)(pFizica->vecVxfMigLocal.x),7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus,
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -40);	
	
	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 									
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "vecVyfMigLocal:",
								 (float)(pFizica->vecVyfMigLocal.y),7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus,
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -40);		

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 									
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "vecVzfMigLocal:",
								 (float)(pFizica->vecVzfMigLocal.z),7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus,
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -40);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 									
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "vecVxyzfMigLocal.x:",
								 (float)(pFizica->vecVxyzfMigLocal.x),7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus,
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -50);	
	
	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 									
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "vecVxyzfMigLocal.y:",
								 (float)(pFizica->vecVxyzfMigLocal.y),7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus,
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -50);	

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 									
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "vecVxyzfMigLocal.z:",
								 (float)(pFizica->vecVxyzfMigLocal.z),7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus,
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -50);	

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 									
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "vecVxyzfMigLocalNormalizat.x:",
								 (float)(pFizica->vecVxyzfMigLocalNormalizat.x),7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus,
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -80);	
	
	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 									
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "vecVxyzfMigLocalNormalizat.y:",
								 (float)(pFizica->vecVxyzfMigLocalNormalizat.y),7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus,
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -80);	

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 									
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "vecVxyzfMigLocalNormalizat.z:",
								 (float)(pFizica->vecVxyzfMigLocalNormalizat.z),7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus,
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -80);		

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 									
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "unghiVecVitMigOxLocal:",
								 (float)(D3DXToDegree(pFizica->unghiVecVitMigOxLocal)),7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus,
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -70);		

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 									
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "unghiVecVitMigOyLocal:",
								 (float)(D3DXToDegree(pFizica->unghiVecVitMigOyLocal)),7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus,
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -70);		
	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 									
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "unghiVecVitMigOzLocal:",
								 (float)(D3DXToDegree(pFizica->unghiVecVitMigOzLocal)),7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus,
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -70);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 									
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "unghiVecVitMigContactOx:",
								 (float)(D3DXToDegree(pFizica->unghiVecVitMigContactOx)),7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus,
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -80);	

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 									
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "unghiVecVitMigContactOy:",
								 (float)(D3DXToDegree(pFizica->unghiVecVitMigContactOy)),7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus,
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -80);	

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 									
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "unghiVecVitMigContactOz:",
								 (float)(D3DXToDegree(pFizica->unghiVecVitMigContactOz)),7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus,
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -80);	

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 									
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "unghiVecVitMigNormala:",
								 (float)(D3DXToDegree(pFizica->unghiVecVitMigNormala)),7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus,
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -70);
	

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 									
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "unghiVecVitMigContactNormala:",
								 (float)(D3DXToDegree(pFizica->unghiVecVitMigContactNormala)),7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus,
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -90);
	*/

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 									
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "unghiRotatieDupaContact:",
								 (float)(D3DXToDegree(pFizica->unghiRotatieDupaContact)),7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus,
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -90);
		

	/*aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 									
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "VectCrossProduct.x:",
								 (float)(D3DXToDegree(pFizica->VectCrossProduct.x)),7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus,
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -70);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 									
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "VectCrossProduct.y:",
								 (float)(D3DXToDegree(pFizica->VectCrossProduct.y)),7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus,
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -70);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 									
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "VectCrossProduct.z:",
								 (float)(D3DXToDegree(pFizica->VectCrossProduct.z)),7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus,
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -70);*/
		
}	
//-----------------------------------------------------------------------------
void AfisajMisiune()
{
	long aliniereStanga,aliniereSus; 

	//aliniereStanga=0;
	//aliniereSus=768-pFont->hFonts[1].inaltimeCaracter*4;
	aliniereStanga=700;
	aliniereSus=0;

	/*pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[2],
						"Deplasari",
						D3DXCOLOR (0.0f,0.0f,1.0f,0.5f),
						aliniereStanga,240,
						20,20);*/
			
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"Tf[Kgf]:",
								(float)pFizica->Tf,7,
								D3DXCOLOR (1.0f,0.0f,0.0f,0.5f),
								aliniereStanga,aliniereSus,
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-28);
	aliniereStanga=700+120;
	if(pFizica->Tf==0.0f)
		pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[1],
						"STOP",
						D3DXCOLOR (0.0f,0.0f,0.0f,0.5f),
						aliniereStanga,aliniereSus, 
						pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter);

	if(pFizica->Tf==170.0f)
		pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[1],
						"RALANTI",
						D3DXCOLOR (0.0f,0.0f,0.0f,0.5f),
						aliniereStanga,aliniereSus, 
						pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter);

	if(pFizica->Tf==3400.0f)
		pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[1],
						"MAXIM CU A.S.L.",
						D3DXCOLOR (0.0f,0.0f,0.0f,0.5f),
						aliniereStanga,aliniereSus, 
						pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter);

	if(pFizica->Tf==4100.0f)
		pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[1],
						"MAXIM",
						D3DXCOLOR (0.0f,0.0f,0.0f,0.5f),
						aliniereStanga,aliniereSus, 
						pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter);

	if(pFizica->Tf==5300.0f)
		pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[1],
						"FORTAJ MINIM",
						D3DXCOLOR (0.0f,0.0f,0.0f,0.5f),
						aliniereStanga,aliniereSus, 
						pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter);

	if(pFizica->Tf==6600.0f)
		pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[1],
						"FORTAJ MAXIM",
						D3DXCOLOR (0.0f,0.0f,0.0f,0.5f),
						aliniereStanga,aliniereSus, 
						pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter);

	aliniereStanga=700;
	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 						
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "vMig[km/h]:",
												  (float)(pFizica->vMig),4,
												  D3DXCOLOR (1.0f,0.0f,0.0f,0.5f),
												  aliniereStanga,aliniereSus,
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -40);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 						
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "vVertMig[m/s]:",
												  (float)(pFizica->vVertMig),4,
												  D3DXCOLOR (1.0f,0.0f,0.0f,0.5f),
												  aliniereStanga,aliniereSus,
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -55);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter; 						
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  "Time[s]:",
												  (float)(TimeMissionSeconds),4,
												  D3DXCOLOR (1.0f,0.0f,0.0f,0.5f),
												  aliniereStanga,aliniereSus,
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -30);		

	aliniereStanga=300;
	aliniereSus=320;	
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
												  pFont->pFonts[1],
												  " alt:",
												  (float)pFizica->altM,7,
												  D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
												  aliniereStanga,aliniereSus, 
												  pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												  -30);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiParteaIntreagaDinFlotant(gD3D->g_pD3DDevice,
												pFont->pFonts[1],
												" alpha:",
												(float)pFizica->alphaAtacGrade,2,
												D3DXCOLOR (1.0f,0.0f,0.0f,1.0f),
												aliniereStanga,aliniereSus, 
												pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												-35);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
												pFont->pFonts[1],
												" alphafileu:",
												(float)D3DXToDegree(pFizica->alphaAtacRotatieInFileuRadiani),4,
												D3DXCOLOR (1.0f,0.0f,0.0f,1.0f),
												aliniereStanga,aliniereSus, 
												pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												-60);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
												pFont->pFonts[1],
												" tetaZ:",
												(float)pFizica->tetazGrade,4,
												D3DXCOLOR (1.0f,0.0f,0.0f,1.0f),
												aliniereStanga,aliniereSus, 
												pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												-35);
	
	
	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
												pFont->pFonts[1],
												" ny:",
												//(float)(pFizica->Pfaripa/pFizica->G),4,
												pFizica->ny,4,
												D3DXCOLOR (1.0f,0.0f,0.0f,1.0f),
												aliniereStanga,aliniereSus, 
												pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
												-20);	
}
//-----------------------------------------------------------------------------
void AfisajCloud()
{
	long aliniereStanga,aliniereSus; 

	aliniereStanga=200;
	aliniereSus=0;

	/*pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[2],
						"Deplasari",
						D3DXCOLOR (0.0f,0.0f,1.0f,0.5f),
						aliniereStanga,240,
						20,20);*/
			
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								pFont->pFonts[1],
								"unghiProiectieCameraViewImpostorPositionAxaOz:",
								(float)D3DXToDegree(pClouds->unghiProiectieCameraViewImpostorPositionAxaOz),7,
								D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								aliniereStanga,aliniereSus,
								pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								-100);	
		
	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "unghiViewAxaOy:",
								 (float)D3DXToDegree(pClouds->unghiViewAxaOy),7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus, 
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -40);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "vImpostorCenter.x:",
								 (float)pClouds->vImpostorCenterPosition.x,7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus, 
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -40);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "vImpostorCenter.y:",
								 (float)pClouds->vImpostorCenterPosition.y,7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus, 
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -40);

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "vImpostorCenter.z:",
								 (float)pClouds->vImpostorCenterPosition.z,7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus, 
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -40);
	
	/*aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiIntreg(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "indexVertex:",
								 (float)indexVertex,7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus, 
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -40);	

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "vIntersectie.x:",
								 (float)pClouds->vecIntersectie[indexVertex].x,7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus, 
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -40);	

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "vIntersectie.y:",
								 (float)pClouds->vecIntersectie[indexVertex].y,7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus, 
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -40);	

	aliniereSus+=pFont->hFonts[1].inaltimeCaracter;
	pFont->AfiseazaTextSiFlotant(gD3D->g_pD3DDevice,
								 pFont->pFonts[1],
								 "vIntersectie.z:",
								 (float)pClouds->vecIntersectie[indexVertex].z,7,
								 D3DXCOLOR (0.0f,0.0f,0.0f,1.0f),
								 aliniereStanga,aliniereSus, 
								 pFont->hFonts[1].latimeCaracter,pFont->hFonts[1].inaltimeCaracter,
								 -40);
	*/
	
}
//-----------------------------------------------------------------------------
// Name: AfisajForte()
// Desc: Display avionics
//-----------------------------------------------------------------------------
/*void AfisajForte()
{
	int i;
	char buffer[8],*buffer1;//[8];							
	int  decimal, sign;      	
	int top=300;

	pFont->hFont=CreateFont(0,0,0,0,FW_MEDIUM,0,0,0,0,0,0,0,0,"Arial");	
	pFont->Init(gD3D->g_pD3DDevice);
									
	//dezactivam ceata pentru a nu afecta textul
	gD3D->g_pD3DDevice->SetRenderState(D3DRS_FOGENABLE,false);
	//------------------------------------------------------
	pString="M:";
	Count=2;
	Rect.left=10;
	Rect.top=300;
	Rect.right=30;
	Rect.bottom=320;
	Format=DT_LEFT;
	Color=D3DXCOLOR (1.0f,0.0f,0.0f,1.0f);
	pFont->WriteText(pString,Count,&Rect,Format,Color);					
				
	buffer1= _fcvt(pFizica->M, 10, &decimal, &sign );
	//_itoa((int)(pFizica->roAer),buffer5,10);
	
	if(decimal>0)
	{
		for(int i=0;i<decimal;i++)
			buffer[i]=buffer1[i];
		buffer[decimal]='.';
		for(i=decimal+1;i<=10;i++)
			buffer[i]=buffer1[i-1];
	}
	else
	{
		buffer[0]='0';		
		buffer[1]='.';
		for(i=2;i<2+(-decimal);i++)
			buffer[i]='0';
		int k=i+10;
		int j=0;
		for(i;i<=k;i++)
		buffer[i]=buffer1[j++];
	}		
			
	Rect.left=30;
	Rect.top=300;
	Rect.right=40;
	Rect.bottom=320;
	Format=DT_LEFT;
	Color=D3DXCOLOR (1.0f,0.0f,0.0f,1.0f);
	if(sign!=0)
		pFont->WriteText("-",1,&Rect,Format,Color);		
	Count=i-1;
	Rect.left=40;
	Rect.top=300;
	Rect.right=140;
	Rect.bottom=320;
	Format=DT_LEFT;
	Color=D3DXCOLOR (1.0f,0.0f,0.0f,1.0f);	
	pFont->WriteText(buffer,5,&Rect,Format,Color);			
	//------------------------------------------------------
	pString="Tf[kgf]:";
	Count=8;
	Rect.left=10;
	Rect.top=320;
	Rect.right=60;
	Rect.bottom=340;
	Format=DT_LEFT;
	Color=D3DXCOLOR (1.0f,0.0f,0.0f,1.0f);
	pFont->WriteText(pString,Count,&Rect,Format,Color);					
			
	_itoa((int)(pFizica->Tf),buffer,10);
	
	for(i=0;i<8;i++)
		if(buffer[i]>='0') break;
	//i-=2;
	//k=k;
	Count=i-1;
	Rect.left=60;
	Rect.top=320;
	Rect.right=140;
	Rect.bottom=340;
	Format=DT_LEFT;
	Color=D3DXCOLOR (1.0f,0.0f,0.0f,1.0f);
	pFont->WriteText(buffer,Count,&Rect,Format,Color);
	//------------------------------------------------------
	pString="Ti[kgf]:";
	Count=8;
	Rect.left=10;
	Rect.top=340;
	Rect.right=60;
	Rect.bottom=360;
	Format=DT_LEFT;
	Color=D3DXCOLOR (1.0f,0.0f,0.0f,1.0f);
	pFont->WriteText(pString,Count,&Rect,Format,Color);					
			
	_itoa((int)(pFizica->Tinstant),buffer,10);
	
	for(i=0;i<8;i++)
		if(buffer[i]>='0') break;
	//i-=2;
	//k=k;
	Count=i-1;
	Rect.left=60;
	Rect.top=340;
	Rect.right=140;
	Rect.bottom=360;
	Format=DT_LEFT;
	Color=D3DXCOLOR (1.0f,0.0f,0.0f,1.0f);
	pFont->WriteText(buffer,Count,&Rect,Format,Color);
	//------------------------------------------------------
	pString="Crz:";
	Count=4;
	Rect.left=10;
	Rect.top=360;
	Rect.right=40;
	Rect.bottom=380;
	Format=DT_LEFT;
	Color=D3DXCOLOR (1.0f,0.0f,0.0f,1.0f);
	pFont->WriteText(pString,Count,&Rect,Format,Color);					
			
	buffer1= _fcvt(pFizica->Crz, 10, &decimal, &sign );
	//_itoa((int)(pFizica->roAer),buffer5,10);
	
	if(decimal>0)
	{
		for(int i=0;i<decimal;i++)
			buffer[i]=buffer1[i];
		buffer[decimal]='.';
		for(i=decimal+1;i<=10;i++)
			buffer[i]=buffer1[i-1];
	}
	else
	{
		buffer[0]='0';		
		buffer[1]='.';
		for(i=2;i<2+(-decimal);i++)
			buffer[i]='0';
		int k=i+10;
		int j=0;
		for(i;i<=k;i++)
		buffer[i]=buffer1[j++];
	}		
			
	Rect.left=40;
	Rect.top=360;
	Rect.right=50;
	Rect.bottom=380;
	Format=DT_LEFT;
	Color=D3DXCOLOR (1.0f,0.0f,0.0f,1.0f);
	if(sign!=0)
		pFont->WriteText("-",1,&Rect,Format,Color);		
	Count=i-1;
	Rect.left=50;
	Rect.top=360;
	Rect.right=150;
	Rect.bottom=380;
	Format=DT_LEFT;
	Color=D3DXCOLOR (1.0f,0.0f,0.0f,1.0f);	
	pFont->WriteText(buffer,8,&Rect,Format,Color);	
	//------------------------------------------------------
	pString="Rzf[kgf]:";
	Count=9;
	Rect.left=10;
	Rect.top=380;
	Rect.right=70;
	Rect.bottom=400;
	Format=DT_LEFT;
	Color=D3DXCOLOR (1.0f,0.0f,0.0f,1.0f);
	pFont->WriteText(pString,Count,&Rect,Format,Color);					
			
	_itoa((int)(pFizica->Rzf),buffer,10);
	
	for(i=0;i<8;i++)
		if(buffer[i]>='0') break;
	//i-=2;
	//k=k;
	Count=i-1;
	Rect.left=70;
	Rect.top=380;
	Rect.right=150;
	Rect.bottom=400;
	Format=DT_LEFT;
	Color=D3DXCOLOR (1.0f,0.0f,0.0f,1.0f);
	pFont->WriteText(buffer,Count,&Rect,Format,Color);		
	//------------------------------------------------------
	pString="roAer[kg/m3]:";
	Count=13;
	Rect.left=10;
	Rect.top=400;
	Rect.right=110;
	Rect.bottom=420;
	Format=DT_LEFT;
	Color=D3DXCOLOR (1.0f,0.0f,0.0f,1.0f);
	pFont->WriteText(pString,Count,&Rect,Format,Color);					
		
	buffer1= _fcvt(pFizica->roAer, 10, &decimal, &sign );
	//_itoa((int)(pFizica->roAer),buffer5,10);
	
	if(decimal>0)
	{
		for(i=0;i<decimal;i++)
			buffer[i]=buffer1[i];
		buffer[decimal]='.';
		for(i=decimal+1;i<=10;i++)
			buffer[i]=buffer1[i-1];
	}
	else
	{
		buffer[0]='0';		
		buffer[1]='.';
		for(i=2;i<2+(-decimal);i++)
			buffer[i]='0';
		int k=i+10;
		int j=0;
		for(i;i<=k;i++)
		buffer[i]=buffer1[j++];
	}
		
			
	Rect.left=110;
	Rect.top=400;
	Rect.right=120;
	Rect.bottom=420;
	Format=DT_LEFT;
	Color=D3DXCOLOR (1.0f,0.0f,0.0f,1.0f);
	if(sign!=0)
		pFont->WriteText("-",1,&Rect,Format,Color);		
	Count=i-1;
	Rect.left=120;
	Rect.top=400;
	Rect.right=220;
	Rect.bottom=420;
	Format=DT_LEFT;
	Color=D3DXCOLOR (1.0f,0.0f,0.0f,1.0f);	
	pFont->WriteText(buffer,5,&Rect,Format,Color);		
	//------------------------------------------------------
	pString="Pf[kgf]:";
	Count=8;
	Rect.left=10;
	Rect.top=420;
	Rect.right=60;
	Rect.bottom=440;
	Format=DT_LEFT;
	Color=D3DXCOLOR (1.0f,0.0f,0.0f,1.0f);
	pFont->WriteText(pString,Count,&Rect,Format,Color);					
		
	_itoa((int)(pFizica->Ffr+pFizica->Ffranare),buffer,10);
	//_itoa((int)(pFizica->Pf),buffer,10);
	
	for(i=0;i<8;i++)
		if(buffer[i]>='0') break;
	//i-=2;
	//k=k;
	Count=i-1;
	Rect.left=70;
	Rect.top=420;
	Rect.right=150;
	Rect.bottom=440;
	Format=DT_LEFT;
	Color=D3DXCOLOR (1.0f,0.0f,0.0f,1.0f);
	pFont->WriteText(buffer,Count,&Rect,Format,Color);		
	//------------------------------------------------------
	pString="Cz:";
	Count=3;
	Rect.left=10;
	Rect.top=440;
	Rect.right=40;
	Rect.bottom=460;
	Format=DT_LEFT;
	Color=D3DXCOLOR (1.0f,0.0f,0.0f,1.0f);
	pFont->WriteText(pString,Count,&Rect,Format,Color);					
			
	buffer1= _fcvt(pFizica->Cz, 10, &decimal, &sign );
	//_itoa((int)(pFizica->roAer),buffer5,10);
	
	if(decimal>0)
	{
		for(int i=0;i<decimal;i++)
			buffer[i]=buffer1[i];
		buffer[decimal]='.';
		for(i=decimal+1;i<=10;i++)
			buffer[i]=buffer1[i-1];
	}
	else
	{
		buffer[0]='0';		
		buffer[1]='.';
		for(i=2;i<2+(-decimal);i++)
			buffer[i]='0';
		int k=i+10;
		int j=0;
		for(i;i<=k;i++)
		buffer[i]=buffer1[j++];
	}		
			
	Rect.left=40;
	Rect.top=440;
	Rect.right=50;
	Rect.bottom=460;
	Format=DT_LEFT;
	Color=D3DXCOLOR (1.0f,0.0f,0.0f,1.0f);
	if(sign!=0)
		pFont->WriteText("-",1,&Rect,Format,Color);		
	Count=i-1;
	Rect.left=50;
	Rect.top=440;
	Rect.right=150;
	Rect.bottom=460;
	Format=DT_LEFT;
	Color=D3DXCOLOR (1.0f,0.0f,0.0f,1.0f);	
	pFont->WriteText(buffer,5,&Rect,Format,Color);	
}*/
//-----------------------------------------------------------------------------
// Name: RenderMig()
//-----------------------------------------------------------------------------
//VOID RenderMig(float tz,float rz,float unghi)
VOID RenderMig(HWND hWnd,D3DXMATRIX *pMigMatWorld,LPD3DXMESH pMesh)
{
		StartFog=10000.0f;
		EndFog=11000.0f;		
		FogDensity=0.001f;
		//pFog->SetupVertexFog(gD3D->g_pD3DDevice,
		//					StartFog,EndFog,
		//					D3DXCOLOR(0.67f*factorIntuneric,0.82f*factorIntuneric,0.91f*factorIntuneric,1.0f),
		//					D3DFOG_EXP,false,FogDensity);

		//pFog->SetupVertexFog(gD3D->g_pD3DDevice,
		//					StartFog,EndFog,
		//					D3DXCOLOR(0.9f,0.3f,0.0f,0.03f),
		//					D3DFOG_LINEAR,true,FogDensity);
						
		//mig 21 lancer		
		//D3DXMATRIX ViewWorldMatrix;
		//D3DXMatrixMultiply(&ViewWorldMatrix,&ViewMatrix,pMigMatWorld); 
				
		

		gD3D->g_pD3DDevice->SetRenderState( D3DRS_CULLMODE , D3DCULL_NONE);
		gD3D->g_pD3DDevice->SetRenderState( D3DRS_ZBIAS ,0);
		gD3D->g_pD3DDevice->SetRenderState( D3DRS_SPECULARENABLE , true);

		//D3DXMatrixScaling(pMatScalare,0.0f,0.0f,0.0f); 
		
		//D3DXMatrixTranslation(pMigMatWorld, -500.0f, 0.0f, 0.0f);
		pMatrix->SetupWorldMatrix(gD3D->g_pD3DDevice,pMigMatWorld);						
				
		//conul de transformare		
		gD3D->g_pD3DDevice->SetRenderState( D3DRS_COLORVERTEX,false);//nu folosim cul vertex-ilor, o luam de la material    				
		//gD3D->g_pD3DDevice->SetRenderState( D3DRS_DIFFUSEMATERIALSOURCE,D3DMCS_MATERIAL);
		pMaterials->AmbientDiffuseMetal(gD3D->g_pD3DDevice,0.9f,0.2f,0.04f,1.0f);
		gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG1);    				
		gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_CURRENT);//la primul stage current=diffuse    		
		pMesh->DrawSubset(0);			
		
		//roti
		pMaterials->AmbientDiffuseMetal(gD3D->g_pD3DDevice,0.1f,0.1f,0.1f,1.0f);
		pTransformation->RotiTransformationStackMatrix(gD3D->g_pD3DDevice,
													   pMigMatWorld,
													   D3DXVECTOR3(-126.75f,-115.84f,-23.22f),
													   pFizica->unghiRotatieRoti);			
				
		pMesh->DrawSubset(28);	
		//pMeshRoataStanga->DrawSubset(0);				
		pTransformation->RotiTransformationStackMatrix(gD3D->g_pD3DDevice,
													   pMigMatWorld,
													   D3DXVECTOR3(129.38f,-115.84f,-23.22f),
													   pFizica->unghiRotatieRoti);			
		pMesh->DrawSubset(29);			

		pTransformation->RotiTransformationStackMatrix(gD3D->g_pD3DDevice,
													   pMigMatWorld,
													   D3DXVECTOR3(0.01f,-123.77f,453.276f),
													   pFizica->unghiRotatieRoti);			
		pMesh->DrawSubset(30);			
	
		pMatrix->SetupWorldMatrix(gD3D->g_pD3DDevice,pMigMatWorld);
		//fuzelaj		
		pMaterials->AmbientDiffuseMetal(gD3D->g_pD3DDevice,0.4f,0.4f,0.4f,1.0f);						
		//pMaterials->AmbientDiffuseMetal(gD3D->g_pD3DDevice,1.0f,0.2f,0.2f,1.0f);						
		/*gD3D->g_pD3DDevice->SetTexture(0,g_pTextureMozaic);		
		gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE2X);    
		gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);*/
		
		//cub texture
		//gD3D->g_pD3DDevice->SetTexture(0,pEnvMap->pCubeMap);
		//pEnvMap->SetareCoordonateTextura(gD3D->g_pD3DDevice);
					
		//gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE);    		
		//gD3D->g_pD3DDevice->SetRenderState(D3DRS_TEXTUREFACTOR 	,0X25666666);
		//gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP,D3DTOP_BLENDFACTORALPHA);    		
		//gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		//gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);    

		gD3D->g_pD3DDevice->SetTexture(0,pTextureMozaic);		
		//gD3D->g_pD3DDevice->SetRenderState(D3DRS_TEXTUREFACTOR 	,0X25666666);
		//gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP,D3DTOP_BLENDFACTORALPHA);    		
		gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE2X);    		
		gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);    
				

		pMesh->DrawSubset(1);
		pMesh->DrawSubset(2);		
		pMesh->DrawSubset(3);
		pMesh->DrawSubset(4);	
		
		pMatrix->SetupWorldMatrix(gD3D->g_pD3DDevice,pMigMatWorld);			

		//escamotaje
		pMesh->DrawSubset(24);		
		pMesh->DrawSubset(25);		
		pMesh->DrawSubset(26);		
		pMesh->DrawSubset(27);	
		
		pMatrix->SetupWorldMatrix(gD3D->g_pD3DDevice,pMigMatWorld);			
		
		//aripi
		pMesh->DrawSubset(9);
		pMesh->DrawSubset(10);	

		pMatrix->SetupWorldMatrix(gD3D->g_pD3DDevice,pMigMatWorld);			

		//ampenaj vertical
		pMesh->DrawSubset(5);

					

		//stabilizatoare spate		
		//if(pFizica->flagBracareStabilizatorUpPress==true | pFizica->flagBracareStabilizatorDownPress==true)
		//{
			pTransformation->StabilizatorTransformationStackMatrix(gD3D->g_pD3DDevice,
				            pMigMatWorld,pFizica->unghiBracareStabilizator,false,false);			

			pMesh->DrawSubset(15);		
			pMesh->DrawSubset(16);			
		//}
		/*else
			{
				//pTransformation->StabilizatorTransformationStackMatrix(gD3D->g_pD3DDevice,
				//          pMigMatWorld,pFizica->unghiBracareStabilizator,&up,&down);			
				pMesh->DrawSubset(15);		
				pMesh->DrawSubset(16);
			}*/		
		
					

		//refacer render state dupa cub texture
		//pEnvMap->RefacereCoordonateTextura(gD3D->g_pD3DDevice);
		//gD3D->g_pD3DDevice->SetTextureStageState( 1, D3DTSS_COLOROP,D3DTOP_DISABLE);    

		pMatrix->SetupWorldMatrix(gD3D->g_pD3DDevice,pMigMatWorld);			
				

		//eleroane aripi				
		pMaterials->AmbientDiffuseMetal(gD3D->g_pD3DDevice,0.24f,0.36f,0.23f,1.0f);		
		gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG1);    		
		gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);    
		//gD3D->g_pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE,D3DMCS_MATERIAL);		
		if(left )
		{
			pMesh->DrawSubset(11);
			pMesh->DrawSubset(13);
			
		}
		else
			if(right)
			{
				pMesh->DrawSubset(11);
				pMesh->DrawSubset(13);			
			
			}
			else

			{				
				pMesh->DrawSubset(11);		
				pMesh->DrawSubset(13);
			}
								
		if(flaps)
		{
			rotFlaps=(float)D3DX_PI/4.0f;
			pTransformation->FlapsuriTransformationStackMatrix(gD3D->g_pD3DDevice,pMigMatWorld,
															rotFlaps);
			pMesh->DrawSubset(12);						
			pMesh->DrawSubset(14);		
		}
		else
		{
			rotFlaps=(float)D3DX_PI/4.0f;
			pMesh->DrawSubset(12);						
			pMesh->DrawSubset(14);		
		}
																
		//pMatrix->SetupWorldMatrix(gD3D->g_pD3DDevice,pMigMatWorld);		
		//stema ampenaj
		pMaterials->AmbientDiffuseMetal(gD3D->g_pD3DDevice,0.4f,0.4f,0.4f,1.0f);				
		gD3D->g_pD3DDevice->SetTexture(0,pTextureStema);		
		gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE2X);    
		gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);    		
		pMesh->DrawSubset(20);
		pMesh->DrawSubset(21);



		//ejector motor
		pMaterials->Specular(gD3D->g_pD3DDevice,0.5f,0.5f,0.5f,1.0f);
		//cub texture
		//gD3D->g_pD3DDevice->SetTexture(0,pEnvMap->pCubeMap);
		//pEnvMap->SetareCoordonateTextura(gD3D->g_pD3DDevice);

		//gD3D->g_pD3DDevice->SetRenderState(D3DRS_TEXTUREFACTOR 	,0X25FFFFFF);
		//gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP,D3DTOP_BLENDFACTORALPHA);    		
		gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG1);    					
		//gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE);    
		//gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);    
		gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_CURRENT);    
		
		pMesh->DrawSubset(19);

		pMaterials->Specular(gD3D->g_pD3DDevice,0.5f,0.5f,0.5f,1.0f);
		//cub texture
		//gD3D->g_pD3DDevice->SetTexture(0,pEnvMap->pCubeMap);
		//pEnvMap->SetareCoordonateTextura(gD3D->g_pD3DDevice);

		//gD3D->g_pD3DDevice->SetRenderState(D3DRS_TEXTUREFACTOR 	,0X25FFFFFF);
		//gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP,D3DTOP_BLENDFACTORALPHA);    		
		gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG1);    					
		//gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE);    
		//gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);    
		gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_CURRENT);    
		
		
		//Ghidaje ampenaj				
		pMesh->DrawSubset(6);
		pMesh->DrawSubset(7);	

		//refacer render state dupa cub texture
		//pEnvMap->RefacereCoordonateTextura(gD3D->g_pD3DDevice);
								
		//carlinga
		
		pMaterials->Specular(gD3D->g_pD3DDevice,1.0f,1.0f,1.0f,0.1f);
		//0.2f,0.73f,0.68f,0.38f);
		gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG1);    		
		gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
				
		//gD3D->g_pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE,D3DMCS_MATERIAL);
		//g_pd3dDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,D3DMCS_MATERIAL);
		//g_pd3dDevice->SetRenderState(D3DRS_SPECULARMATERIALSOURCE,D3DMCS_MATERIAL);

		//gD3D->g_pD3DDevice->SetRenderState(D3DRS_TEXTUREFACTOR 	,0X25FFFFFF);
		//gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,D3DTOP_BLENDFACTORALPHA);    		
		gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,D3DTOP_SELECTARG1);    		
		//gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);    
		//gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE); 
		gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_CURRENT);    

		/*gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG1);		
		gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_CURRENT);*/
		gD3D->g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
		gD3D->g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);		
		gD3D->g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE ,true);
		//pMesh->DrawSubset(17);
		pMesh->DrawSubset(18);									
		gD3D->g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE ,false);

		pEnvMap->RefacereCoordonateTextura(gD3D->g_pD3DDevice);
		

		//stabilizator ampenaj
		pMaterials->AmbientDiffuseMetal(gD3D->g_pD3DDevice,0.24f,0.36f,0.23f,1.0f);		
		gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG1);    		
		gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);  				
		if(palonierstg)		
			pMesh->DrawSubset(8);								
		else
			if(palonierdr)			
				pMesh->DrawSubset(8);							
			else			
				pMesh->DrawSubset(8);									
					

		//sistem de particule 2D
		/*pSprite->Begin();		
			pSprite->Draw(g_pTextureSprite,NULL,NULL,NULL,0.2f,NULL,
						  0x80ffffff);
		pSprite->End();*/

		//interior motor
		gD3D->g_pD3DDevice->SetTexture(0,pTextureSprite);	
		pMaterials->AmbientDiffuseMetal(gD3D->g_pD3DDevice,0.17f,0.17f,0.17f,1.0f);
		gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP,D3DTOP_SELECTARG1);    
		gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
		gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_TEXTURE);

		

		if(pFizica->Tf>=pFizica->MAXIM)
		{
			pMaterials->Emissive(gD3D->g_pD3DDevice,1.0f,1.0f,0.9f,1.0f);		
			gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP,D3DTOP_MODULATE2X);    
						
		}
		if(pFizica->Tf>=pFizica->FORTAJ_MINIM)
		{
			pMaterials->Emissive(gD3D->g_pD3DDevice,1.0f,1.0f,0.9f,1.0f);		
			gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP,D3DTOP_MODULATE4X);    		
			
		}						
		pMesh->DrawSubset(22);		
		
		//jet
		if(pFizica->Tf>=pFizica->FORTAJ_MAXIM)
		{			
			pMaterials->Emissive(gD3D->g_pD3DDevice,0.67f,0.23f,0.0f,0.015f);
			
			//gD3D->g_pD3DDevice->SetRenderState(D3DRS_EMISSIVEMATERIALSOURCE,D3DMCS_MATERIAL);			
			//gD3D->g_pD3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,D3DMCS_MATERIAL);						
			gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP,D3DTOP_SELECTARG1); 
			gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_CURRENT);
			//gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_TEXTURE);						
			gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG1);		
			gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_CURRENT);
			gD3D->g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
			gD3D->g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);		
			gD3D->g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE ,true);
			gD3D->g_pD3DDevice->SetRenderState( D3DRS_ZWRITEENABLE, FALSE );
			if(pSistParticule->PointSize<18.7f)
				pSistParticule->PointSize+=1.7f;			
			else
				pSistParticule->PointSize-=1.7f;
			gD3D->g_pD3DDevice->SetRenderState(D3DRS_POINTSCALEENABLE ,true);
			pSistParticule->PointScaleA=0.0f;
			pSistParticule->PointScaleB=0.0f;
			pSistParticule->PointScaleC=1.0f;
			float MinSize;
			MinSize=0.0f;
			gD3D->g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE, *((DWORD*)&pSistParticule->PointSize));
			gD3D->g_pD3DDevice->SetRenderState( D3DRS_POINTSIZE_MIN, *((DWORD*)&MinSize));
			gD3D->g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_A, *((DWORD*)&pSistParticule->PointScaleA));
			gD3D->g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_B, *((DWORD*)&pSistParticule->PointScaleB));
			gD3D->g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_C, *((DWORD*)&pSistParticule->PointScaleC));
			//pJet->NrFlameFront=75;//nr. fronturi de flacara
			pSistParticule->NrVerticesPerFrontFlameInitial=53;//nr. vertex-uri pentru fiecare front de flacara
			pSistParticule->radius=25;
			pSistParticule->SetVertexJet(gD3D->g_pD3DDevice,D3DXVECTOR3(0.0f,145.0f-145.83f,-530.0f-23.22f));			
			
			if(pSistParticule->inel<=0)
				pSistParticule->inel=400;
			else
				pSistParticule->inel-=100;

			if(pSistParticule->NrVerticesForRender<pSistParticule->NrVerticesTotal)
			{
				pSistParticule->NrVerticesForRender+=400;				
				if(pSistParticule->NrVerticesForRender>pSistParticule->NrVerticesTotal)
					pSistParticule->NrVerticesForRender=pSistParticule->NrVerticesTotal;
			}
			else
				pSistParticule->NrVerticesForRender=pSistParticule->NrVerticesTotal-pSistParticule->inel;
				
			pSistParticule->DrawFlameFrontJet(gD3D->g_pD3DDevice,pSistParticule->NrVerticesForRender);
			gD3D->g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE ,false);
			gD3D->g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE, *((DWORD*)&pSistParticule->PointSizeNormal));
			gD3D->g_pD3DDevice->SetRenderState(D3DRS_POINTSCALEENABLE ,false);					    
			gD3D->g_pD3DDevice->SetRenderState( D3DRS_COLORVERTEX,false);//nu folosim cul vertex-ilor, o luam de la material    							
			gD3D->g_pD3DDevice->SetRenderState( D3DRS_ZWRITEENABLE, TRUE);

			/*pMaterials->Specular(gD3D->g_pD3DDevice,0.3f,0.67f,0.3f,0.19f);//alb trebuie combinat cu tex
			gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG1);		
			gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
			gD3D->g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
			gD3D->g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);		
			gD3D->g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE ,true);
			pMesh->DrawSubset(23);			
			gD3D->g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE ,false);*/
		}

		

		gD3D->g_pD3DDevice->SetRenderState( D3DRS_SPECULARENABLE , false);

		gD3D->g_pD3DDevice->SetRenderState(D3DRS_FOGENABLE,false);
}

VOID RenderMigNew(HWND hWnd, D3DXMATRIX* mig_world_matrix, LPD3DXMESH mesh) {
	gD3D->g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	gD3D->g_pD3DDevice->SetRenderState(D3DRS_ZBIAS, 0);
	gD3D->g_pD3DDevice->SetRenderState(D3DRS_SPECULARENABLE, true);

	LPD3DXMATRIXSTACK stack_mig;
	D3DXCreateMatrixStack(0, &stack_mig);
	stack_mig->LoadMatrix(mig_world_matrix);
	stack_mig->RotateAxisLocal(&D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DX_PI);
	//stack_mig->TranslateLocal(0.0f, 50.0f, 394.0f); // for 50 scaling
	stack_mig->TranslateLocal(0.0f, 20.0f, -30.0f);
	stack_mig->ScaleLocal(42.0f, 42.0f, 42.0f);
	pMatrix->SetupWorldMatrix(gD3D->g_pD3DDevice, stack_mig->GetTop());

	//Rotunjire (antialising) muchiilor 
	gD3D->g_pD3DDevice->SetRenderState(D3DRS_EDGEANTIALIAS, TRUE);
	gD3D->g_pD3DDevice->SetRenderState(D3DRS_DITHERENABLE, TRUE);
	gD3D->g_pD3DDevice->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
	//g_pd3dDevice->SetRenderState( D3DRS_LOCALVIEWER , TRUE ); 
	//g_pd3dDevice->SetRenderState( D3DRS_FILLMODE , D3DFILL_WIREFRAME ); 	
	gD3D->g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	gD3D->g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	for (int i = 0; i < pMesh->mesh_material_number_[1]; ++i) {
		gD3D->g_pD3DDevice->SetMaterial(&pMesh->mesh_materials_[1][i].MatD3D);

		if (i == 0) {
			gD3D->g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
			gD3D->g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
			gD3D->g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
			gD3D->g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
			gD3D->g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
			gD3D->g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			gD3D->g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		}
		else {
			gD3D->g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
			gD3D->g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
			gD3D->g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		}

		if (pMesh->mesh_textures_[1][i]) {
			gD3D->g_pD3DDevice->SetTexture(0, pMesh->mesh_textures_[1][i]);
		}

		mesh->DrawSubset(i);
	}
}

//-----------------------------------------------------------------------------
// Name: RenderTeren()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
VOID RenderTeren(HWND hWnd,D3DXMATRIX *pTerenWorld,LPD3DXMESH pMesh)
{				
		gD3D->g_pD3DDevice->SetRenderState( D3DRS_CULLMODE , D3DCULL_NONE);			
		//D3DXMATRIX* pOut;
		//D3DXMatrixMultiply(pOut,pMatScalare,pTerenWorld); 
		pMatrix->SetupWorldMatrix(gD3D->g_pD3DDevice,pTerenWorld);

		//pamant
		pMaterials->AmbientDiffuseMetal(gD3D->g_pD3DDevice,0.7f,0.7f,0.7f,1.0f);    		
		//gD3D->g_pD3DDevice->SetTexture(0,pTextureMozaic);		
		gD3D->g_pD3DDevice->SetTexture(0,pTextureTeren);		

		gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE);    
		gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);    		
		pMesh->DrawSubset(0);//campie					
		
		gD3D->g_pD3DDevice->SetTexture(0,pTextureZonaMuntoasa);				
		pMeshTerrain->DrawSubset(1);//zona muntoasa				

		//gD3D->g_pD3DDevice->SetRenderState( D3DRS_ZBIAS ,0);
		gD3D->g_pD3DDevice->SetTexture(0,pTextureBaza);				
		//pMesh->DrawSubset(2);//teren baza

		//if(pFizica->altM>1.0f)
		//	gD3D->g_pD3DDevice->SetRenderState( D3DRS_ZBIAS ,50);
		//else
			gD3D->g_pD3DDevice->SetRenderState( D3DRS_ZBIAS ,5);

		gD3D->g_pD3DDevice->SetTexture(0,pTexturePista);				
		pMeshBaza->DrawSubset(0);//baza

		gD3D->g_pD3DDevice->SetRenderState( D3DRS_ZBIAS ,0);			
}
//-----------------------------------------------------------------------------
VOID RenderHUD(HWND hWnd,D3DXMATRIX *pHUDWorld,LPD3DXMESH pMesh)
{
	gD3D->g_pD3DDevice->SetRenderState( D3DRS_CULLMODE , D3DCULL_NONE);			
	pMatrix->SetupWorldMatrix(gD3D->g_pD3DDevice,pHUDWorld);		

	float factorIntuneric;	
	factorIntuneric=5.0f;
	pMaterials->Emissive(gD3D->g_pD3DDevice,0.047f*factorIntuneric,
									0.988f*factorIntuneric,
									0.0f*factorIntuneric,1.0f);
	gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG1);    				
	gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_CURRENT);//la primul stage current=diffuse    		
	

	pMesh->DrawSubset(0);
	pMesh->DrawSubset(1);
	pMesh->DrawSubset(2);
	pMesh->DrawSubset(3);
	pMesh->DrawSubset(4);
	pMesh->DrawSubset(5);
	pMesh->DrawSubset(6);
}
//-----------------------------------------------------------------------------
// Name: RenderCer()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
VOID RenderCer(HWND hWnd,D3DXMATRIX *pSkyMatWorld)
{			
		//cer
		float factorIntuneric;	
		factorIntuneric=1.0f;
		gD3D->g_pD3DDevice->SetRenderState( D3DRS_CULLMODE , D3DCULL_NONE);
		//pMatrix->SetupWorldMatrix(gD3D->g_pD3DDevice,pMigMatWorld);
		//pMatrix->SetupWorldMatrix(gD3D->g_pD3DDevice,pTransformation->SkyTransformationStackMatrix(0.0f,0.0f,&tz));
		pMatrix->SetupWorldMatrix(gD3D->g_pD3DDevice,pSkyMatWorld);		

		pMaterials->AmbientDiffuseMetal(gD3D->g_pD3DDevice,0.67f*factorIntuneric,
											   0.82f*factorIntuneric,
											   0.98f*factorIntuneric,0.9f);//culoarea atmosferei (ex. albastra in timpul zilei), 
																   		   //identica,cu Clear(...) colour      								
		gD3D->g_pD3DDevice->SetTexture(0,pTextureCer);									
		gD3D->g_pD3DDevice->SetRenderState(D3DRS_TEXTUREFACTOR 	,0X7243525B);
		//0X70333333);
		//0X7243525B);
		
		//texture transformation ptr. miscarea norilor
		gD3D->g_pD3DDevice->SetTextureStageState(0,D3DTSS_TEXTURETRANSFORMFLAGS ,D3DTTFF_COUNT2);		
		if (pTransformation->MatTextureTransformation._32<1.0f)
			pTransformation->MatTextureTransformation._32+=0.00005f;//0.0002f;
		else
			pTransformation->MatTextureTransformation._32=0.0f;
		gD3D->g_pD3DDevice->SetTransform(D3DTS_TEXTURE0,&pTransformation->MatTextureTransformation);


		gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP,D3DTOP_BLENDFACTORALPHA);
		gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE); 
		gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG1);		
		gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
		gD3D->g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_SRCALPHA);
		gD3D->g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
		gD3D->g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE ,true);
		//texTerenMesh->DrawSubset(4);		
		gD3D->g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE ,false);						
		gD3D->g_pD3DDevice->SetTextureStageState(0,D3DTSS_TEXTURETRANSFORMFLAGS ,D3DTTFF_DISABLE);
										
		/*if(gD3D->VerificaFormatCompatibilCuEchipament(D3DUSAGE_RENDERTARGET,
							   D3DRTYPE_CUBETEXTURE ,D3DFMT_X8R8G8B8))
			MessageBox(hWnd,"AiciNick S", NULL, MB_OK); 															
		else
			MessageBox(hWnd,"AiciNick F", NULL, MB_OK);*/
}
//-----------------------------------------------------------------------------
// Name: RenderCloud()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
VOID RenderCloud(HWND hWnd,D3DXMATRIX *pCloudMatWorld)
{					
		float factorIntuneric;	
		factorIntuneric=1.0f;
		gD3D->g_pD3DDevice->SetRenderState( D3DRS_CULLMODE , D3DCULL_NONE);
		//pMatrix->SetupWorldMatrix(gD3D->g_pD3DDevice,pMigMatWorld);
		//pMatrix->SetupWorldMatrix(gD3D->g_pD3DDevice,pTransformation->SkyTransformationStackMatrix(0.0f,0.0f,&tz));
		

		//pMatrix->SetupWorldMatrix(gD3D->g_pD3DDevice,pCloudMatWorld);		

		//pMaterials->AmbientDiffuseMetal(gD3D->g_pD3DDevice,0.67f*factorIntuneric,
		//									   0.82f*factorIntuneric,
		//									   0.98f*factorIntuneric,0.9f);//culoarea atmosferei (ex. albastra in timpul zilei), 

		
		//gD3D->g_pD3DDevice->SetTexture(0,pTextureCloud);
		//gD3D->g_pD3DDevice->SetTexture(0,pTextureSprite);
		

		//gD3D->g_pD3DDevice->SetTexture(0,pClouds->volTexture);
		//gD3D->g_pD3DDevice->SetTexture(0,pClouds->pTextureCloud[0]);
		//gD3D->g_pD3DDevice->SetTexture(0,pClouds->pTextureProfilOrizontalNor);
		
		pMaterials->Clouds(gD3D->g_pD3DDevice, 1.0f, 1.0f, 1.0f, 0.5f);		
		gD3D->g_pD3DDevice->SetRenderState( D3DRS_COLORVERTEX,false);//nu folosim cul vertex-ilor, o luam de la material    				
				
		gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP,D3DTOP_SELECTARG1); 
		//gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
		gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE);			
		gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG1);		
		gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
		//gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		gD3D->g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
		gD3D->g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);		
		gD3D->g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE ,true);
		gD3D->g_pD3DDevice->SetRenderState( D3DRS_ZWRITEENABLE, FALSE );


		/*StartFog=4000.0f;
		EndFog=7000.0f;		
		FogDensity=1.0f;
		pFog->SetupVertexFog(gD3D->g_pD3DDevice,
							StartFog,EndFog,
							D3DXCOLOR(0.67f*factorIntuneric,0.82f*factorIntuneric,0.91f*factorIntuneric,1.0f),
							D3DFOG_EXP,true,FogDensity);

		pFog->SetupPixelFog(gD3D->g_pD3DDevice,
							StartFog,EndFog,
							D3DXCOLOR(0.67f*factorIntuneric,0.82f*factorIntuneric,0.91f*factorIntuneric,1.0f),
							D3DFOG_LINEAR,FogDensity);		
		*/
		

		// drawing a cloud with sprites
		/*gD3D->g_pD3DDevice->SetRenderState(D3DRS_POINTSPRITEENABLE ,true);
		
		//D3DVIEWPORT8 *pViewport; 
		//gD3D->g_pD3DDevice->GetViewport(pViewport);
		//pCloud->PointSizeCloud=400.0f/pViewport->Height;

		//pCloud->PointSizeCloud=800.0f;
		gD3D->g_pD3DDevice->SetRenderState(D3DRS_POINTSCALEENABLE ,true);
		pCloud->PointScaleACloud=0.0f;
		pCloud->PointScaleBCloud=0.0f;
		pCloud->PointScaleCCloud=0.0f;		
		float MinSize,MaxSize;
		MinSize=400.0f;
		//MaxSize=400.0f;
		//gD3D->g_pD3DDevice->SetRenderState( D3DRS_POINTSIZE_MIN, *((DWORD*)&MinSize));
		//gD3D->g_pD3DDevice->SetRenderState( D3DRS_POINTSIZE_MAX, *((DWORD*)&MaxSize));
		//gD3D->g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE, *((DWORD*)&pCloud->PointSizeCloud));
		gD3D->g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_A, *((DWORD*)&pCloud->PointScaleACloud));
		gD3D->g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_B, *((DWORD*)&pCloud->PointScaleBCloud));
		gD3D->g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_C, *((DWORD*)&pCloud->PointScaleCCloud));

		pCloud->NrVerticesTotalCloud=200;
		pCloud->SetVertexCloud(gD3D->g_pD3DDevice);			
		pCloud->DrawCloud(gD3D->g_pD3DDevice,pCloud->NrVerticesTotalCloud);		

		gD3D->g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE, *((DWORD*)&pCloud->PointSizeNormal));
		gD3D->g_pD3DDevice->SetRenderState(D3DRS_POINTSCALEENABLE ,false);

		gD3D->g_pD3DDevice->SetRenderState(D3DRS_FOGENABLE,false);
		*/

		/*pClouds->pVBCloud->Lock(0,0,(BYTE**)&pClouds->pVertices,0);			
		

		//pClouds->pVertices[4].tu1=0.0f; 
		//pClouds->pVertices[4].tv1=1.0f; 
		//if(pClouds->pVertices[4].tv1<1.0f)
		//	pClouds->pVertices[4].tv1+=0.1f; 		
		//else
			pClouds->pVertices[4].tv1=0.4f; 		
			
		//pClouds->pVertices[5].tu1=0.0f; 
		//pClouds->pVertices[5].tv1=0.0f; 
		//if(pClouds->pVertices[5].tv1<1.0f)
		//	pClouds->pVertices[5].tv1+=0.1f; 		
		//else
			pClouds->pVertices[5].tv1=0.4f; 		
			
		//pClouds->pVertices[6].tu1=1.0f; 
		//pClouds->pVertices[6].tv1=1.0f; 
		//if(pClouds->pVertices[6].tv1<1.0f)
		//	pClouds->pVertices[6].tv1+=0.1f; 		
		//else
			pClouds->pVertices[6].tv1=0.4f; 		
			
		//pClouds->pVertices[7].tu1=1.0f; 
		//pClouds->pVertices[7].tv1=0.0f; 
		//if(pClouds->pVertices[7].tv1<1.0f)
		//	pClouds->pVertices[7].tv1+=0.1f; 		
		//else
			pClouds->pVertices[7].tv1=0.4f; 		

		pClouds->pVertices=NULL;
		pClouds->pVBCloud->Unlock();*/


		// when should it be enabled?
		//viewYCurent=12000.0f;

		std::stringstream ss;
		ss << "viewXCurent:" << viewXCurent << ", viewYCurent:" << viewYCurent <<  ", viewZCurent:" << viewZCurent << std::endl;
		OutputDebugString(ss.str().c_str());
		
		/*pClouds->GenerateDynamicImpostors(gD3D->g_pD3DDevice,
										 D3DXVECTOR3(viewXCurent,viewYCurent,viewZCurent),
										 D3DXVECTOR3(-5000.0f,14000.0f,11000.0f),
										 D3DXVECTOR3(-5000.0f,14000.0f,1000.0f),
										 D3DXVECTOR3(5000.0f,14000.0f,11000.0f),
										 D3DXVECTOR3(5000.0f,14000.0f,1000.0f),
										 D3DXVECTOR3(-5000.0f,4000.0f,11000.0f),
										 D3DXVECTOR3(-5000.0f,4000.0f,1000.0f),
										 D3DXVECTOR3(5000.0f,4000.0f,11000.0f),
										 D3DXVECTOR3(5000.0f,4000.0f,1000.0f),
										 &pTransformation->MatMig);*/
		
		// pClouds->vImpCenterPosition works only with GenerateDynamicImpostor
		// enable for GenerateDynamicImpostor
		pClouds->vImpostorCenterPosition =D3DXVECTOR3(4000.0f, 30000.0f, 100000.0f);
		/*pClouds->GenerateDynamicImpostor(gD3D->g_pD3DDevice,
										 D3DXVECTOR3(viewXCurent,viewYCurent,viewZCurent),
										 D3DXVECTOR3(0.0f,0.0f,0.0f),
										 pClouds->vImpostorCenterPosition,
										 80000.0f,
										 160000.0f,
										 &pTransformation->MatTerrain);*/

		pClouds->GenerateDynamicImpostorNew(gD3D->g_pD3DDevice, 
			{viewXCurent, viewYCurent, viewZCurent}, 
			pClouds->vImpostorCenterPosition, 
			30000.0f, 
			60000.0f, 
			&pTransformation->MatTerrain); 

		gD3D->g_pD3DDevice->SetTexture(0, pClouds->GenerateCloudTexture(gD3D->g_pD3DDevice, 3000, 600));

		// enable for GenerateDynamicImpostor
		pMatrix->SetupWorldMatrix(gD3D->g_pD3DDevice,&pClouds->impostorMatrix);		

		// draw simple 2D cloud
		// works with GenerateDynamicImpostor
		pClouds->DrawCloud(gD3D->g_pD3DDevice,
							D3DPT_TRIANGLESTRIP,
							0,2);	
		
		/*div_t div_result;
		//div_result=div(pClouds->indexVertex,2);
		//if(div_result.rem==0 | pClouds->indexVertex==3)
		pClouds->DrawCloud(gD3D->g_pD3DDevice,
						   D3DPT_TRIANGLESTRIP, 
						   0,pClouds->indexVertex-2);						

		pClouds->DrawCloud(gD3D->g_pD3DDevice,
						   D3DPT_TRIANGLEFAN, 
						   0,pClouds->indexVertex-2);						
		
		//pClouds->DrawCloud(gD3D->g_pD3DDevice,4,2);	
		*/

		//for(int i=0;i<pClouds->VertSlicesNr*pClouds->OrizSlicesNr;i++)		
		//	pClouds->DrawCloud(gD3D->g_pD3DDevice,i*4,2);		

		//StartFog=40.0f;
		//EndFog=60.0f;		
		//FogDensity=1.0f;
		//pFog->SetupVertexFog(gD3D->g_pD3DDevice,
		//					StartFog,EndFog,
		//					D3DXCOLOR(0.67f*factorIntuneric,0.82f*factorIntuneric,0.91f*factorIntuneric,1.0f),
		//					D3DFOG_EXP,false,FogDensity);

		//pFog->SetupPixelFog(gD3D->g_pD3DDevice,
		//					StartFog,EndFog,
		//					D3DXCOLOR(0.67f*factorIntuneric,0.82f*factorIntuneric,0.91f*factorIntuneric,1.0f),
		//					D3DFOG_LINEAR,FogDensity);
		
		//pClouds->DrawCloud(gD3D->g_pD3DDevice,0,12);							
		
		/*ss.clear();
		ss << "indexVertex:" << pClouds->indexVertex << ", indexVertexFataSus:"  << pClouds->indexVertexFataSus 
			 << ", indexVertexFataJos:" << pClouds->indexVertexFataJos  
			 << ", indexVertexFeteLaterale:" << pClouds->indexVertexFeteLaterale << std::endl;
		OutputDebugString(ss.str().c_str());*/

		//if(pClouds->indexVertexFataSus==2 && pClouds->indexVertexFataJos==2)	
		if (pClouds->indexVertex == 4) {
			pClouds->DrawCloud(gD3D->g_pD3DDevice, D3DPT_TRIANGLESTRIP, 0, 2);
		}

		if (pClouds->indexVertex == 3) {
			pClouds->DrawCloud(gD3D->g_pD3DDevice, D3DPT_TRIANGLESTRIP, 0, 1);
		}

		if (pClouds->indexVertex == 5) {
			pClouds->DrawCloud(gD3D->g_pD3DDevice, D3DPT_TRIANGLESTRIP, 0, 3);
		}

		if (pClouds->indexVertex == 6) {
			pClouds->DrawCloud(gD3D->g_pD3DDevice, D3DPT_TRIANGLESTRIP, 0, 4);
		}

		/*if (pClouds->indexVertexFeteLaterale != 0 && pClouds->indexVertexFataSus == 2)
			pClouds->DrawCloud(gD3D->g_pD3DDevice,
							   D3DPT_TRIANGLESTRIP,
							   pClouds->indexVertexFataSus+
							   pClouds->indexVertexFataJos,1);	*/		

		//gD3D->g_pD3DDevice->SetRenderState(D3DRS_FOGENABLE,false);
		
		gD3D->g_pD3DDevice->SetRenderState( D3DRS_COLORVERTEX,false);//nu folosim cul vertex-ilor, o luam de la material    				
		gD3D->g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE ,false);
		gD3D->g_pD3DDevice->SetRenderState( D3DRS_ZWRITEENABLE,TRUE);
										
		/*if(gD3D->VerificaFormatCompatibilCuEchipament(D3DUSAGE_RENDERTARGET,
							   D3DRTYPE_CUBETEXTURE ,D3DFMT_X8R8G8B8))
			MessageBox(hWnd,"AiciNick S", NULL, MB_OK); 															
		else
			MessageBox(hWnd,"AiciNick F", NULL, MB_OK);*/
}
//-----------------------------------------------------------------------------
// Name: AfisajMeniuPrincipal()
// Desc: Display meniu
//-----------------------------------------------------------------------------
void RenderFrame(HWND hWnd)
{
	/*D3DVIEWPORT8 viewData = { 0,
							  0,
							  gD3D->Echipament.d3dModVideoCurent.Width,
							  gD3D->Echipament.d3dModVideoCurent.Height,
							  0.0f,
							  1.0f};

	HRESULT hr;
	hr = gD3D->g_pD3DDevice->SetViewport(&viewData);*/

	BeginScene(hWnd, &pTransformation->MatMig);
	//if(flagOverSky)
	//{							
	
	RenderTeren(hWnd, &pTransformation->MatTerrain, pMeshTerrain);
	
	/*RenderCer(hWnd, pTransformation->SkyTransformationStackMatrix(
		&pFizica->txMig, &pFizica->tyMig, &pFizica->tzMig,
		//&pFizica->tzT,
		//&pFizica->txG,&pFizica->tyG,&pFizica->tzG,
		&rtx, &rty, &rtz, &pFizica->unghiRotatieTransversalaMig,
		&rlx, &rly, &rlz, &pFizica->unghiRotatieLongitudinalaMig));//se implementeaza doar rotirea si deplasarea pe verticala
	*/
	//} else {
		//RenderCer(hWnd,&pTransformation->MatTerrain);
   //}

	//if(pFizica->altM<1.0f)
		//RenderMig(hWndMig,&pTransformation->MatIdentica,pMeshMig);														
	//else	
	/*viewData.X=100;
    viewData.Y=100;
    viewData.Width=600;
    viewData.Height=600;
    viewData.MinZ=0.0f;
    viewData.MaxZ=1.0f;
	
	hr = gD3D->g_pD3DDevice->SetViewport(&viewData);*/	
	txHUDFix=0.0f,tyHUDFix=122.0f,tzHUDFix=550.0f;

	//stack_mig->TranslateLocal(0.0f, 50.0f, 394.0f);

	rotZHUD=pFizica->unghiInclinare;
	pTransformation->HUDTransformationStackMatrix(&txHUDFix, &tyHUDFix, &tzHUDFix, &tYHUD, &rotZHUD);				
	RenderHUD(hWnd,&pTransformation->MatHUDTransformation,pHUDMesh);
		
	/*RenderMig*/(hWnd,&pTransformation->MatIdentica,pMeshMigCgOrigine);
	RenderMigNew(hWnd, &pTransformation->MatIdentica, pMeshMigNew);
								
	//pTransformation->PozitieNor(D3DXVECTOR3(0.0f,2000.0f,3000.0f));
	//pTransformation->SkyTransformationStackMatrix(&pFizica->txMig,&pFizica->tyMig,&pFizica->tzMig,																	
													//&rtx,&rty,&rtz,&pFizica->unghiRotatieTransversalaMig,
													//&rlx,&rly,&rlz,&pFizica->unghiRotatieLongitudinalaMig);

	//RenderCloud(hWnd,&pTransformation->MatSkyTransformation);
	//RenderCloud(hWnd,&pTransformation->MatTerrain); //bun


	//afisaje
	if(pFizica->takeOff==true)// && pFizica->flagFlapsLanding==true)
	{								
		//flagPaused=true;//temp								
		//flagAfisaje=true;//temp
	}	
	
	if(pFizica->dupaContact==true)// && pFizica->hitVecVzfMigLocal==TRUE)//temp
	{
		//flagPaused=true;//temp								
		//flagAfisaje=true;//temp
	}	

	if(pFizica->unghiRotatieDupaContact!=0.0f)// && pFizica->flagDecolare==true)//temp
	{
		//flagPaused=true;//temp								
		//flagAfisaje=true;//temp
	}		

	if(pFizica->flagAterizare==true)
	{
		//flagPaused=true;//temp								
		//flagAfisaje=true;//temp
	}	

	if(pFizica->temp1<=pFizica->temp2)//temp
	{
		//flagPaused=true;//temp							
		//flagAfisaje=true;//temp
	}
							
	if(pFizica->distPanaLaContact>0.0f && pFizica->distPanaLaContact<100.0f 
		&& pFizica->flagFlapsTakeOff==false)
	{
		//flagPaused=true;//temp								
		//flagAfisaje=true;//temp
	}

	/*if(pFizica->VectorCentruRoti.y<=-146.44f && pFizica->flagDecolare==true)//temp
	{
		flagPaused=true;//temp								
		flagAfisaje=true;//temp
	}*/

	if((pFizica->index==1 || pFizica->index==3) && pFizica->dupaContact==true)
	{
		//flagPaused=true;//temp								
		//flagAfisaje=true;//temp
	}

	if(pFizica->tablouVectoriTestati[pFizica->index].hit==false && pFizica->flagFlapsLanding==true)
	{
		//flagPaused=true;//temp								
		//flagAfisaje=true;//temp
	}

	if(pFizica->tetaxGrade!=0.0f && pFizica->dupaContact==false)
	{
		//flagPaused=true;//temp								
		//flagAfisaje=true;//temp
	}
														

	//Afisaje														
	AfisajSistem();
	//AfisajOrientareSpatiala();
	//AfisajMisiune(); //todo(Nicu): re-enable
	//AfisajForte();						
	//AfisajVectori();								
	//flagPaused=true;//temp								
	//flagAfisaje=true;//temp
	if(flagAfisaje==true)
	{							
		AfisajOrientareSpatiala();
		AfisajParametriAerodinamici();										
		AfisajForte();						
		AfisajAcceleratii();						
		AfisajViteze();
		AfisajDeplasari();	
		//AfisajColiziuni();
		AfisajVectori();								
		AfisajComenziTest();
	}	
	//AfisajCloud();
							
	if(contorAfisajComenziFlapsuri<30)
		AfisajComenziFlapsuri();

	if(contorAfisajComenziMotor<30)
		AfisajComenziMotor();

	EndSceneAndPresent(hWnd);																																											
}
//-----------------------------------------------------------------------------
void AfisajMeniuPrincipal()
{								
	/*pString="Locotenent Nicolae POPESCU";
	Count=26;
	Rect.left=1024-26*20;
	Rect.top=728;
	Rect.right=1024;
	Rect.bottom=768;
	Format=DT_LEFT;
	Color=D3DXCOLOR (0.0f,0.0f,1.0f,1.0f);
	pFont->WriteText(pFont->pFonts[0],pString,Count,&Rect,Format,Color);*/
	long aliniereStanga; 
	long aliniereSus; 
	
	//int nrPixeliOx;
	//HDC hDC;
	//nrPixeliOx=GetDeviceCaps(hDC,LOGPIXELSX);

	aliniereStanga=0; 
	aliniereSus=768-pFont->hFonts[1].inaltimeCaracter; 


	pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[1],
						"www.ADElineImage.com",
						D3DXCOLOR (1.0f,1.0f,0.0f,1.0f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[1].latimeCaracter+2,pFont->hFonts[1].inaltimeCaracter);				
		
	aliniereStanga=1024-26*(pFont->hFonts[0].latimeCaracter+2); 
	aliniereSus=768-pFont->hFonts[0].inaltimeCaracter; 
	

	pFont->AfiseazaText(gD3D->g_pD3DDevice,
						pFont->pFonts[0],
						"Locotenent Nick POPESCU",
						D3DXCOLOR (0.0f,0.0f,1.0f,1.0f),
						aliniereStanga,aliniereSus,
						pFont->hFonts[0].latimeCaracter+5,pFont->hFonts[0].inaltimeCaracter);				
	//LOGFONT
}
//-----------------------------------------------------------------------------
// Name: RenderEarth()
// Desc: Draws the presentation scene
//-----------------------------------------------------------------------------
VOID RenderMeniuPrincipal(D3DXMATRIX *pEarthMatWorld,HWND hWndMeniuPrincipal)
{

	//D3DXMATRIX ViewMatrix;
	//D3DXMATRIX ViewWorldMatrix;
	//D3DXMatrixIdentity(&ViewMatrix); 	
	//D3DXMatrixIdentity(&ViewWorldMatrix); 	

	
    // Clear the backbuffer and the zbuffer
    gD3D->g_pD3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,
                         D3DXCOLOR(0.0f,0.0f,0.0f,1.0f), 1.0f, 0 );
    // Begin the scene
    gD3D->g_pD3DDevice->BeginScene();

    

	//SetupDirectionalLights(D3DXVECTOR3(-1.0f,0.0f,0.0f));
	pLights->Directional(gD3D->g_pD3DDevice,0,
						 D3DXVECTOR3(-1.0f,-1.5f,-1.0f),1.0f,1.0f,1.0f);
	//pLights->Directional(gD3D->g_pD3DDevice,D3DXVECTOR3(0.0f,-1.0f,0.0f));	
	//SetupPointLights(0.0f,400.0f,800.0f);
	//SetupPointLights(0.0f,-800.0f,0.0f);
	//SetupSpotlLights(0.0f,800.0f, 1000.0f,D3DXVECTOR3(0.0f,800.0f,-1000.0f));
	//SetupSpotlLights(0.0f,800.0f, -1000.0f,D3DXVECTOR3(0.0f,-800.0f,1000.0f));
	
	
    //SetupMatrices();	
	pMatrix->SetupProjectionMatrix(gD3D->g_pD3DDevice,D3DX_PI/4,
			(float)gD3D->Echipament.d3dModVideoCurent.Width/
			gD3D->Echipament.d3dModVideoCurent.Height,
			1.0f,10000.0f);	
				
	pMatrix->SetupViewMatrix(gD3D->g_pD3DDevice,
							 &D3DXVECTOR3(0.0f,0.0f,-200.0f),
							 &D3DXVECTOR3(0.0f,0.0f,0.0f),
							 &D3DXVECTOR3(0.0f,1.0f,0.0f)
							);

	//-------------- RENDER STATES
	//Rotunjire (antialising) muchiilor 
	gD3D->g_pD3DDevice->SetRenderState( D3DRS_EDGEANTIALIAS, TRUE );
	gD3D->g_pD3DDevice->SetRenderState( D3DRS_DITHERENABLE , TRUE ); 
	//g_pd3dDevice->SetRenderState( D3DRS_FILLMODE , D3DFILL_WIREFRAME ); 	
    //gD3D->g_pD3DDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
	gD3D->g_pD3DDevice->SetRenderState( D3DRS_CULLMODE , D3DCULL_NONE);
	gD3D->g_pD3DDevice->SetRenderState( D3DRS_CLIPPING , TRUE);
	gD3D->g_pD3DDevice->SetRenderState( D3DRS_SPECULARENABLE , true);
	//----------------------------------------------------------------
		
				
	pMaterials->AmbientDiffuseMetal(gD3D->g_pD3DDevice,0.7f,0.7f,0.7f,1.0f);    		
	gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE);    
	gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);    	
	
	//D3DXMatrixMultiply(&ViewWorldMatrix,&ViewMatrix,pEarthMatWorld); 
		
	pMatrix->SetupWorldMatrix(gD3D->g_pD3DDevice,pEarthMatWorld);		
	gD3D->g_pD3DDevice->SetTexture(0,pTextureEarth);
	EarthMesh->DrawSubset(0);
	pMatrix->SetupWorldMatrix(gD3D->g_pD3DDevice, &pTransformation->Translation(&pTransformation->MatTranslatie,60.0f,55.0f,0.0f));	
	gD3D->g_pD3DDevice->SetTexture(0,pTextureText);
	EarthMesh->DrawSubset(1);
	//D3DXMatrixMultiply(&ViewWorldMatrix,&ViewMatrix,&pTransformation->MatIdentica); 
	pMatrix->SetupWorldMatrix(gD3D->g_pD3DDevice,&pTransformation->MatIdentica);		
	gD3D->g_pD3DDevice->SetTexture(0,pTextureBackGround);		
	EarthMesh->DrawSubset(2);
	
	AfisajMeniuPrincipal();
    // End the scene
    gD3D->g_pD3DDevice->EndScene();

    // Present the backbuffer contents to the display	
    gD3D->g_pD3DDevice->Present( NULL, NULL, hWndMeniuPrincipal, NULL );
		
		
	
	//D3DXMatrixIdentity(&ViewMatrix); 	
	//D3DXMatrixIdentity(&ViewWorldMatrix);
	
}		
//-----------------------------------------------------------------------------
// Name: MigMsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT WINAPI MigMsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	int virt_key=(int) wParam;
	int lKeyData=(int) lParam;	
	int i=0;		
	float r=1600.0f;			
	short status;

    switch( msg )
    {						
		
		case WM_SETCURSOR:
			// Turn off window cursor 
			SetCursor( NULL );
			gD3D->g_pD3DDevice->ShowCursor(FALSE);
			return TRUE; // prevent Windows from setting cursor to window class cursor
			break;

		case WM_MOUSEMOVE: {
			switch (virt_key) {
			case MK_LBUTTON: {
				auto xPos = GET_X_LPARAM(lParam);
				auto yPos = GET_Y_LPARAM(lParam);
				auto deltaX = xPos - prev_xPos;
				auto deltaY = yPos - prev_yPos;

				std::stringstream ss;
				ss << "mouse x:" << xPos << ", y:" << yPos << std::endl;
				OutputDebugString(ss.str().c_str());

				ss.clear();
				ss << "mouse deltaX:" << deltaX << ", deltaY:" << deltaY << std::endl;
				OutputDebugString(ss.str().c_str());

				float angleX = 0.0f; float angleY = 0.0f;

				if (deltaX < 0) {
					angleY = -0.4f;
				}
				else {
					angleY = 0.4f;
				}
				if (deltaY < 0) {
					angleX = -0.4f;
				}
				else {
					angleX = 0.4f;
				}

				ss.clear();
				ss << "mouse angleX:" << angleX << ", angleY:" << angleY << std::endl;
				OutputDebugString(ss.str().c_str());

				auto angleXRadian = D3DXToRadian(angleX);
				auto angleYRadian = D3DXToRadian(angleY);

				pFizica->unghiRotatieVerticalaMig = 0.0f;
				pFizica->rvy = 0.0f;
				pFizica->unghiRotatieTransversalaMig = 0.0f;
				pFizica->rtx = 0.0f;

				if(abs(deltaX) > abs(deltaY)) {
					pFizica->unghiRotatieVerticalaMig = angleYRadian;
					pFizica->rvy = 1.0f;
					prev_xPos = xPos;
				}
				else {
					pFizica->unghiRotatieTransversalaMig = angleXRadian;
					pFizica->rtx = 1.0f;
					prev_yPos = yPos;
				}
				break;
			}
			default: break;
			}
			break;
		}
		case WM_LBUTTONUP: {
			pFizica->unghiRotatieVerticalaMig = 0.0;
			pFizica->rvy = 0.0f;
			pFizica->unghiRotatieTransversalaMig = 0.0f;
			pFizica->rtx = 0.0f;
			break;
		}
		case WM_KEYDOWN:										
			/*case WM_CHAR:
			switch(wParam)
				{
				case 43:
					pFizica->powerUp=true;
					break;				
				}
			return 0;*/
			switch(virt_key){
				case VK_NUMPAD5:	
					{						
						lookX=0.0f;lookY=70.0f;lookZ=700.0f;

						viewXDinamic=0.0f;
						viewYDinamic=25.0f;//f18 viewY=15.0f;
						viewZDinamic=-2000.0f;//viewZ=-65.0f;
						
						/*viewY=170.0f;					
						viewZ=-850.0f;
						viewX=-300.0f;*///din lateral											
						flag_camerastatica=false;
						flag_cameradinamica1=true;
						flag_cameradinamica2=false;
						//ok=true;//pentru verificarea parametrilor
					}
					break;
				case VK_F1:	
					{
						/*viewXDinamic=0.0f;
						viewYDinamic=70.0f;
						viewZDinamic=400.0f;*/
						//lookY=70.0f;
						flag_camerastatica=false;
						flag_cameradinamica1=true;
						flag_cameradinamica2=false;						
					}
					break;
				case VK_F2:	
					{						
						/*viewXDinamic=0.0f;
						viewYDinamic=25.0f;
						viewZDinamic=-1550.0f;*/
						//lookY=70.0f;

						flag_camerastatica=false;
						flag_cameradinamica1=false;
						flag_cameradinamica2=true;						
					}
					break;
				case VK_F3:	
					{
						flag_camerastatica=true;
						flag_cameradinamica1=false;
						flag_cameradinamica2=false;											  
					}
					break;						
				case VK_F7:	
					//DialogBox(hInstantaAplicatiei,MAKEINTRESOURCE(IDD_DIALOG_FIZICA),hWnd,(DLGPROC)DlgFizica);											
					if(flagAfisaje==false)													
						flagAfisaje=true;												
					else
						flagAfisaje=false;
					
					break;				
				case VK_F12:					
					if(flagPaused==false)									
					{
						flagPaused=true;			

						gD3D->g_pD3DDevice->BeginScene();					
						pFont->AfiseazaText(gD3D->g_pD3DDevice,
											pFont->pFonts[0],
											"PAUSE",
											 D3DXCOLOR (0.0f,0.0f,1.0f,0.5f),
											 450,300,
											 40,60);
						gD3D->g_pD3DDevice->EndScene();
						gD3D->g_pD3DDevice->Present( NULL, NULL, NULL, NULL );
					}
					else
						flagPaused=false;
					break;	
				case VK_NUMPAD4:
					//status=GetKeyState(VK_LCONTROL);
					//status=status>>15;
					//if(status) 
					viewXDinamic-=200;					
					break;
				case VK_NUMPAD6:
					//status=GetKeyState(VK_NUMPAD4);
					//status=status>>15;
					//if(status) 				
					//{
						if((viewXDinamic>=0)&&(viewXDinamic<r)&&(viewZDinamic>=-r)&&(viewZDinamic<0))			
						{
							viewXDinamic+=40;
							viewZDinamic=(float)(-sqrt(r*r-viewXDinamic*viewXDinamic));
						}
						else
							if((viewXDinamic>0)&&(viewXDinamic<=r)&&(viewZDinamic>=0)&&(viewZDinamic<r))			
							{
								viewXDinamic-=40;
								viewZDinamic=(float)sqrt(r*r-viewXDinamic*viewXDinamic);
							}				
							else
								if((viewXDinamic<=0)&&(viewXDinamic>-r)&&(viewZDinamic>0)&&(viewZDinamic<=r))			
								{
									viewXDinamic-=40;
									viewZDinamic=(float)sqrt(r*r-viewXDinamic*viewXDinamic);
								}
								else
								if((viewXDinamic<0)&&(viewXDinamic>=-r)&&(viewZDinamic<=0)&&(viewZDinamic>-r))			
								{
									viewXDinamic+=40;
									viewZDinamic=(float)(-sqrt(r*r-viewXDinamic*viewXDinamic));
								}
					//}					
					break;
				case VK_NUMPAD2:
					//status=GetKeyState(VK_LCONTROL);
					//status=status>>15;
					//if(status) 
					viewYDinamic-=200;					
					break;
				case VK_NUMPAD8:
					//status=GetKeyState(VK_LCONTROL);
					//status=status>>15;
					//if(status) 
					viewYDinamic+=200;					
					break;
				case VK_LEFT:
					if (!pFizica->flagStartEngine) {
						pFizica->txMig -= 3.0f;
						break;
					}
					if(pFizica->tzMig!=0.0f)
					{
						rlx=0.0f;
						rly=0.0f;
						rlz=1.0f;				
						//rotLongMig=(float)D3DX_PI/14;					
					}								
					//right=false;
					//left=true;				
					//pTransformation->MatTransformationCameraUp;
					pFizica->flagBracareEleroaneStangaPress=true;
					pFizica->flagBracareEleroaneStangaRelease=false;
					pFizica->flagBracareEleroaneDreaptaPress=false;
					pFizica->flagBracareEleroaneDreaptaRelease=false;				
					break;				
				case VK_RIGHT:
					if (!pFizica->flagStartEngine) {
						pFizica->txMig += 3.0f;
						break;
					}
					if(pFizica->tzMig!=0.0f)
					{
						rlx=0.0f;
						rly=0.0f;
						rlz=1.0f;
						//rotLongMig=(float)-D3DX_PI/14;					
					}							
					//left=false;
					//right=true;				
					//pTransformation->MatTransformationCameraUp;
					pFizica->flagBracareEleroaneDreaptaPress=true;
					pFizica->flagBracareEleroaneDreaptaRelease=false;
					pFizica->flagBracareEleroaneStangaPress=false;
					pFizica->flagBracareEleroaneStangaRelease=false;														
					break;				
				case VK_DOWN:
					if (!pFizica->flagStartEngine) {
						pFizica->tyMig -= 3.0f;
						break;
					}
					//for(i=0;i<=2200000;i++);										
					if(pFizica->tzMig!=0.0f)
					{
						rtx=1.0f;
						rty=0.0f;
						rtz=0.0f;
						//rotTranMig=(float)-D3DX_PI/150;											
					}
					//rotStabilizator=(float)D3DX_PI/10.9f;				
					rotLongMig=0.0f;					
					//up=false;
					//down=true;		
					//pTransformation->MatTransformationCameraUp;
					pFizica->flagBracareStabilizatorDownPress=true;				
					pFizica->flagBracareStabilizatorDownRelease=false;				
					pFizica->flagBracareStabilizatorUpPress=false;									
					pFizica->flagBracareStabilizatorUpRelease=false;														
					break;					
				case VK_UP:
				{
					if (!pFizica->flagStartEngine) {
						pFizica->tyMig += 3.0f;
						break;
					}

					if (pFizica->tzMig != 0.0f)
					{
						rtx = 1.0f;
						rty = 0.0f;
						rtz = 0.0f;
						//rotTranMig=(float)D3DX_PI/250;						
					}
					//rotStabilizator=(float)-D3DX_PI/24;				
					rotLongMig = 0.0f;
					//up=true;
					//down=false;				
					//pTransformation->MatTransformationCameraUp;
					pFizica->flagBracareStabilizatorUpPress = true;
					pFizica->flagBracareStabilizatorUpRelease = false;
					pFizica->flagBracareStabilizatorDownPress = false;
					pFizica->flagBracareStabilizatorDownRelease = false;
					break;
				}
				case 'N'://palonier stanga				
					if(pFizica->tzMig!=0.0f)
					{
						rtx=0.0f;//ar trebui modificata functia MigTSM ptr a 
								 //contine si rotatia in jurul axei Oz
						rty=1.0f;
						rtz=0.0f;				
						//rotTranMig=-D3DX_PI/16;					
					}				
					palonierstg=true;
					palonierdr=false;
					//pTransformation->MatTransformationCameraUp;//=*pTransformation->pStackCameraUp->GetTop();		
					break;
				case 'M'://palonier dreapta
					if(pFizica->tzMig!=0.0f)
					{
						rtx=0.0f;
						rty=1.0f;
						rtz=0.0f;				
						//rotTranMig=D3DX_PI/16;					
					}				
					palonierdr=true;
					palonierstg=false;				
					//pTransformation->MatTransformationCameraUp;//=*pTransformation->pStackCameraUp->GetTop();		
					break;
				case 'F'://flapsuri		
					
					//flagAfisajComenzi=true;
					contorAfisajComenziFlapsuri=0;

					if(pFizica->flagFlapsBagat==true)
					{
						pFizica->sensFlapsDown=true;
						pFizica->flagFlapsBagat=false;
						pFizica->flagFlapsTakeOff=true;										
						pFizica->flagFlapsLanding=false;				
					}
					else
						if(pFizica->flagFlapsTakeOff==true)
						{
							if(pFizica->sensFlapsDown==true)
							{
								pFizica->flagFlapsBagat=false;
								pFizica->flagFlapsTakeOff=false;										
								pFizica->flagFlapsLanding=true;				
							}
							else
							{
								pFizica->flagFlapsBagat=true;
								pFizica->flagFlapsTakeOff=false;										
								pFizica->flagFlapsLanding=false;				
							}
						}
						else
							if(pFizica->flagFlapsLanding==true)
							{
								pFizica->sensFlapsDown=false;
								pFizica->flagFlapsBagat=false;
								pFizica->flagFlapsTakeOff=true;										
								pFizica->flagFlapsLanding=false;				
							}					
					break;			
				case '1':
					if(indexVertex<pClouds->indexVertex-1)
						indexVertex++;									
					else
						indexVertex=0;
					break;			
				case '6':												
									
					break;			
				case '7':								
					
					break;			
				case '8':								
					
					break;						
				case '9':											
					
					break;
				case '0':								
					
					break;
				case VK_BACK:													
					break;	
				case VK_CONTROL:
					status=GetKeyState(VK_LCONTROL);
					status=status>>15;
					if(status)
						pFizica->powerDown=true;															
					break;	
				case VK_SHIFT:					
					status=GetKeyState(VK_LSHIFT);
					status=status>>15;
					if(status)
						pFizica->powerUp=true;					
					break;							
				//camera controls
				case 'W':
					if (!pFizica->flagStartEngine) {
						pFizica->tzMig += 3.0f;
						break;
					}
					/*if(flagWire)
					{
						gD3D->g_pD3DDevice->SetRenderState( D3DRS_FILLMODE , D3DFILL_WIREFRAME );
						flagWire=false;
					}
					else
					{
						gD3D->g_pD3DDevice->SetRenderState( D3DRS_FILLMODE , D3DFILL_SOLID);
						flagWire=true;
					}*/
					pFizica->powerUp=true;
					break;
				case 'S':
					if (!pFizica->flagStartEngine) {
						pFizica->tzMig -= 3.0f;
						break;
					}
					pFizica->powerDown=true;
					break;
				case 'A':				
					pFizica->flagBracareAmpenajStangaPress=true;
					pFizica->flagBracareAmpenajDreaptaPress=false;
					pFizica->flagBracareAmpenajStangaRelease=false;
					pFizica->flagBracareAmpenajDreaptaRelease=false;
					break;
				case 'D':				
					pFizica->flagBracareAmpenajStangaPress=false;
					pFizica->flagBracareAmpenajDreaptaPress=true;
					pFizica->flagBracareAmpenajStangaRelease=false;
					pFizica->flagBracareAmpenajDreaptaRelease=false;
					break;
				case 'B'://break				
					if(pFizica->Ffranare>0.0f)
						pFizica->Ffranare=0.0f;				
					else
						pFizica->Ffranare=pFizica->Tmax-pFizica->Ffrecare;
					break;
				case 'X':				
					//moveLookY=5.0f;
					break;
				case 'Z':				
					flagScene=true;
					//moveLookY=-5.0f;				
					break;
				/*case 'G':	
					{
						pFizica->dupaContact=false;
						pFizica->vyfMig=0.0f;
						pFizica->vyiMig=0.0f;
						pFizica->tyMig=100.0f;					
					}
					break;
				*/
				case 'H':					
					pFizica->dupaContact=true;				
					break;

				case 'I':
					//flagAfisajComenzi=true;					
					contorAfisajComenziMotor=0;
					if(pFizica->flagStopEngine==true)
					{
						pFizica->flagStartEngine=true;
						pFizica->flagStopEngine=false;
					}
					else
						if(pFizica->flagStartEngine==true)
						{
							pFizica->flagStartEngine=false;
							pFizica->flagStopEngine=true;
						}
					break;					
				break;			
			}			
			return 0;			
		case WM_KEYUP:			
			/*case WM_DEADCHAR:
			switch(wParam)
				{
				case 43:
					pFizica->powerUp=false;
					break;				
				}
			return 0;*/			
			switch(virt_key){
				case VK_LEFT:
					if (!pFizica->flagStartEngine) {
						pFizica->txMig = 0.0f;
						break;
					}
					//left=false;
					pFizica->flagBracareEleroaneDreaptaPress=false;
					pFizica->flagBracareEleroaneDreaptaRelease=false;
					pFizica->flagBracareEleroaneStangaPress=false;
					pFizica->flagBracareEleroaneStangaRelease=true;				
					break;				
				case VK_RIGHT:
					if (!pFizica->flagStartEngine) {
						pFizica->txMig = 0.0f;
						break;
					}
					pFizica->flagBracareEleroaneDreaptaPress=false;
					pFizica->flagBracareEleroaneDreaptaRelease=true;
					pFizica->flagBracareEleroaneStangaPress=false;
					pFizica->flagBracareEleroaneStangaRelease=false;				
					//right=false;					
					break;
				case VK_UP:
					if (!pFizica->flagStartEngine) {
						pFizica->tyMig = 0.0f;
						break;
					}
					//up=false;					
					pFizica->flagBracareStabilizatorUpRelease=true;					
					pFizica->flagBracareStabilizatorUpPress=false;					
					pFizica->flagBracareStabilizatorDownPress=false;					
					pFizica->flagBracareStabilizatorDownRelease=false;					
					break;
				case VK_DOWN:
					if (!pFizica->flagStartEngine) {
						pFizica->tyMig = 0.0f;
						break;
					}
					//down=false;										
					pFizica->flagBracareStabilizatorDownRelease=true;					
					pFizica->flagBracareStabilizatorDownPress=false;					
					pFizica->flagBracareStabilizatorUpPress=false;					
					pFizica->flagBracareStabilizatorUpRelease=false;					
					break;	
				case 'N':
					palonierstg=false;
					break;
				case 'M':
					palonierdr=false;
					break;
				case 'B'://flapsuri					
					flaps=false;													
					break;
				case VK_CONTROL:
					status=GetKeyState(VK_LCONTROL);
					status=status>>15;
					if(!status)
						pFizica->powerDown=false;										 													
					break;
				case VK_SHIFT:
					status=GetKeyState(VK_LSHIFT);
					status=status>>15;
					if(!status)
						pFizica->powerUp=false;					
					break;
				case 'W':
					if (!pFizica->flagStartEngine) {
						pFizica->tzMig = 0.0f;
						break;
					}
					pFizica->powerUp=false;					
					break;
				case 'S':
					if (!pFizica->flagStartEngine) {
						pFizica->tzMig = 0.0f;
						break;
					}
					pFizica->powerDown=false;
					break;
				case 'A':
					pFizica->flagBracareAmpenajStangaPress=false;
					pFizica->flagBracareAmpenajDreaptaPress=false;
					pFizica->flagBracareAmpenajStangaRelease=true;
					pFizica->flagBracareAmpenajDreaptaRelease=false;
					break;
				case 'D':
					pFizica->flagBracareAmpenajStangaPress=false;
					pFizica->flagBracareAmpenajDreaptaPress=false;
					pFizica->flagBracareAmpenajStangaRelease=false;
					pFizica->flagBracareAmpenajDreaptaRelease=true;
					break;
				case 'F':					
					//flagAfisajComenzi=false;
					break;					
				case 'X':					
					//moveLookY=0.0f;
				break;
				case 'Z':
					//moveLookY=0.0f;				
				break;	
				case 'G':
					pFizica->dupaContact=true;
					pFizica->vyfMig=0.0f;
					pFizica->vyiMig=0.0f;
					pFizica->tyMig=0.0f;					
				break;					
			}					
			break;

			return 0;	
        case WM_DESTROY:
            PostQuitMessage( 0 );
            return 0;
    }				
    return DefWindowProc( hWnd, msg, wParam, lParam );
}
//-----------------------------------------------------------------------------
// Name: MeniuPrincipalMsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT WINAPI MeniuPrincipalMsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	int virt_key=(int) wParam;
	int lKeyData=(int) lParam;	
	int i=0;		
    switch( msg )
    {						
		
		case WM_KEYDOWN:					
			switch(virt_key){																			
			case VK_DOWN:					
				break;					
			case VK_UP:									
				break;									
			case 'A':
				flagScene=false;				
				break;	
			case 'X':
				DestroyWindow(hWnd);
				break;
			}			
			break;			
			return 0;			
		case WM_KEYUP:
			switch(virt_key){				
				case 'X':					
				break;
				case 'Z':					
				break;				
			}					
			break;
			return 0;	
        case WM_DESTROY:
            PostQuitMessage( 0 );
            return 0;
    }				
    return DefWindowProc( hWnd, msg, wParam, lParam );
}
//--------------------------------------------------------------------------------
BOOL CALLBACK DlgFizica( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
{
	//int virt_key=(int) wParam;
	//int lKeyData=(int) lParam;			

    switch( msg )
    {
		case WM_INITDIALOG:	
			//ShowWindow(hDlg,SW_SHOW);
			//UpdateWindow(hDlg);
			break;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{				
				case IDOK:					
					EndDialog(hDlg,wParam);					
					break;
				case IDCANCEL:
					EndDialog(hDlg,wParam);					
					break;				
				default:
					return true;
			}
				
    }	
	return true;    
}

//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: Initializes Direct3D
//-----------------------------------------------------------------------------
HRESULT InitD3D(HWND hWnd)
{
	// Create the D3D object.
	if (NULL == (gD3D->g_pD3D = Direct3DCreate8(D3D_SDK_VERSION)))
		return E_FAIL;

	// Get the current desktop display mode, so we can set up a back
	// buffer of the same format
	D3DDISPLAYMODE d3ddm;
	if (FAILED(gD3D->g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
		return E_FAIL;

	//d3ddm.Width=1024;
	//d3ddm.Height=768;
	//d3ddm.Format=D3DFMT_X1R5G5B5;
	//d3ddm.Format=D3DFMT_X8R8G8B8; // pe compu lu ra
	//d3ddm.RefreshRate=60;

	// Set up the structure used to create the D3DDevice. Since we are now
	// using more complex geometry, we will create a device with a zbuffer.
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = true;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = d3ddm.Width;
	d3dpp.BackBufferHeight = d3ddm.Height;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24X8;

	// Create the D3DDevice
	if (FAILED(gD3D->g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &gD3D->g_pD3DDevice)))
	{
		return E_FAIL;
	}
	return S_OK;
}


//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT )
{
    // Register the MIG window class
	hInstantaAplicatiei=hInst;

	HICON hIcon=LoadIcon(NULL,"mig.jpg");
	//WNDCLASSEX wcMeniuPrincipal = { sizeof(WNDCLASSEX), NULL, MeniuPrincipalMsgProc, 0L, 0L, 
      //                GetModuleHandle(NULL), 
		//			  hIcon,
			//		  NULL, NULL, NULL,
              //        "Meniu Principal", NULL };    

    WNDCLASSEX wcMig = { sizeof(WNDCLASSEX), NULL, MigMsgProc, 0L, 0L, 
                      GetModuleHandle(NULL), 
					  hIcon,
					  //LoadImage( hInst,"mig1.ico",IMAGE_BITMAP,SM_CXICON,SM_CYICON,  
					  //			 LR_LOADFROMFILE ), 
					  NULL, NULL, NULL,
                      "MIG 21 LANCER", NULL };
	
	//RegisterClassEx( &wcMeniuPrincipal);
	RegisterClassEx( &wcMig);
    
	RECT rcClient;
	GetClientRect( GetDesktopWindow(), &rcClient); 
	
	//WS_BORDER
	//HWND hWndMeniuPrincipal = CreateWindow( "Meniu Principal", "MIG 21 LANCER", 
      //                        WS_OVERLAPPEDWINDOW, rcClient.left, rcClient.top, 
		//					  rcClient.right, rcClient.bottom,
          //                    GetDesktopWindow(), NULL, wcMeniuPrincipal.hInstance, NULL );

    HWND hWndMig = CreateWindow( "MIG 21 LANCER", "MIG 21 LANCER", 
                              WS_OVERLAPPEDWINDOW, 100, 100, 2800, 1800,
							  //WS_OVERLAPPEDWINDOW, rcClient.left, rcClient.top, rcClient.right, rcClient.bottom,
                              GetDesktopWindow(), NULL, wcMig.hInstance, NULL );	
					

	ShowWindow(hWndMig, SW_SHOW);
	UpdateWindow(hWndMig);

	//D3DInput 
	//pD3DInput->CreateD3DInputObject(hInstantaAplicatiei,hWndMeniuPrincipal);
	//pD3DInput->EnumDevices(hWndMeniuPrincipal); 
	//pD3DInput->CreateSysKeyboardDevice(hWndMeniuPrincipal);
	pD3DInput->CreateD3DInputObject(hInstantaAplicatiei, hWndMig);

    // Initialize Direct3D	
    if( SUCCEEDED(gD3D->InitializeazaD3D(0))) //InitD3D( hWnd ) ) )
	//if(SUCCEEDED(InitD3D(hWndMig)))
    {			
		gD3D->Echipament.d3dModVideoCurent.Width = gD3D->Echipament.d3dAdapterDisplayMode.Width;
		gD3D->Echipament.d3dModVideoCurent.Height=gD3D->Echipament.d3dAdapterDisplayMode.Height;
		gD3D->Echipament.d3dModVideoCurent.RefreshRate=gD3D->Echipament.d3dAdapterDisplayMode.RefreshRate;
		gD3D->Echipament.d3dModVideoCurent.Format=gD3D->Echipament.d3dAdapterDisplayMode.Format;
		gD3D->Echipament.Parametri.Windowed = true;
		gD3D->Echipament.Parametri.hDeviceWindow = hWndMig;
		gD3D->Echipament.Parametri.BackBufferWidth = gD3D->Echipament.d3dModVideoCurent.Width;
		gD3D->Echipament.Parametri.BackBufferHeight = gD3D->Echipament.d3dModVideoCurent.Height;
		gD3D->Echipament.Parametri.BackBufferFormat = gD3D->Echipament.d3dModVideoCurent.Format;
		gD3D->Echipament.Parametri.BackBufferCount=1;
		gD3D->Echipament.Parametri.SwapEffect= D3DSWAPEFFECT_DISCARD;
		gD3D->Echipament.Parametri.EnableAutoDepthStencil = TRUE;
		gD3D->Echipament.Parametri.AutoDepthStencilFormat = D3DFMT_D24X8;//D3DFMT_D16-la placile mai vechi;		
		//gD3D->Echipament.Parametri.FullScreen_RefreshRateInHz =D3DPRESENT_RATE_DEFAULT ;
		//gD3D->Echipament.Parametri.FullScreen_PresentationInterval =D3DPRESENT_INTERVAL_DEFAULT;		
		
		if(SUCCEEDED(gD3D->VerificaTipEchipamentGrafic(gD3D->Echipament.NrPlacaGrafica,
													   D3DDEVTYPE_HAL,
													   gD3D->Echipament.d3dModVideoCurent)))
				//if(gD3D->CreatEchipament(hWndMeniuPrincipal,D3DCREATE_HARDWARE_VERTEXPROCESSING )==S_OK)
				if (gD3D->CreatEchipament(hWndMig, D3DCREATE_HARDWARE_VERTEXPROCESSING) == S_OK)
		
		//MessageBox(hWnd,"AiciNick", NULL, MB_OK); 								
        //Load the geometry
        //if( SUCCEEDED( LoadMeshFromAFile() ) )
		{            
			//MessageBox(hWndMeniuPrincipal,"OK", NULL, MB_OK); 								
            
			//enviroment mapping initialization			
			//pEnvMap->Init(hWndMeniuPrincipal ,gD3D->g_pD3DDevice);	
			
			//volume texture
			/*pClouds->pSrcFile[0] = "texturi/Clouds/Cloud1.jpg";
			pClouds->pSrcFile[1]="texturi/Clouds/Cloud2.jpg";
			pClouds->pSrcFile[2]="texturi/Clouds/Cloud3.jpg";
			pClouds->pSrcFile[3]="texturi/Clouds/Cloud4.jpg";
			pClouds->pSrcFile[4]="texturi/Clouds/Cloud5.jpg";
			pClouds->pSrcFile[5]="texturi/Clouds/Cloud6.jpg";
			pClouds->pSrcFile[6]="texturi/Clouds/Cloud7.jpg";
			pClouds->pSrcFile[7]="texturi/Clouds/Cloud8.jpg";
			pClouds->pSrcFile[8]="texturi/Clouds/Cloud9.jpg";
			pClouds->pSrcFile[9]="texturi/Clouds/Cloud10.jpg";
			pClouds->LoadTexturesFromFile(gD3D->g_pD3DDevice);
			pClouds->VolumeTexture(gD3D->g_pD3DDevice);*/

			pClouds->pSrcFileProfilesTextures[0] = "texturi/Clouds/ProfilVertical.jpg";
			//pClouds->pSrcFileProfilesTextures[0] = "texturi/Clouds/Cloud1.jpg";
			pClouds->pSrcFileProfilesTextures[1]="texturi/Clouds/ProfilOrizontal.jpg";
			pClouds->LoadProfilesTexturesFromFile(gD3D->g_pD3DDevice);
			//pClouds->VolumeTextureFromProfiles(gD3D->g_pD3DDevice);
			// set simple rectangle for 2D cloud
			pClouds->SetVertexCloud(gD3D->g_pD3DDevice,
									D3DXVECTOR3(0.0f,0.0f,0.0f),
									4000.0f,
									4000.0f);
			
				
			
			//Font initialization
			/*LOGFONT *pLogFont;
			
			pLogFont->lfHeight=40; 
			pLogFont->lfWidth=20; 
			pLogFont->lfEscapement=0; 
			pLogFont->lfOrientation=0; 
			pLogFont->lfWeight=FW_MEDIUM; 
			pLogFont->lfItalic=0; 
			pLogFont->lfUnderline=0; 
			pLogFont->lfStrikeOut=0; 
			pLogFont->lfCharSet=0;//ANSI 
			pLogFont->lfOutPrecision=OUT_TT_PRECIS; 
			pLogFont->lfClipPrecision=CLIP_CHARACTER_PRECIS|CLIP_LH_ANGLES; 
			pLogFont->lfQuality=PROOF_QUALITY; 
			pLogFont->lfPitchAndFamily=DEFAULT_PITCH|FF_DONTCARE; 
			lstrcpy(pLogFont->lfFaceName,"Monotype Corsiva");*/
			//pLogFont->lfFaceName[LF_FACESIZE]; 

			pFont->hFonts[0].hFont=CreateFont(50,15,0,0,FW_MEDIUM,0,0,
									   0,0,0,0,0,0,"Monotype Corsiva");
			pFont->hFonts[0].inaltimeCaracter=50;	
			pFont->hFonts[0].latimeCaracter=15;						
			//pFont->hFonts[0]=CreateFontIndirect(pLogFont);

			pFont->hFonts[1].hFont=CreateFont(15,8,0,0,FW_MEDIUM,0,0,
									   0,0,0,0,0,0,"Times New Roman");
			pFont->hFonts[1].inaltimeCaracter=15;	
			pFont->hFonts[1].latimeCaracter=12;	
			//pLogFont->lfHeight=0; 
			//pLogFont->lfWidth=0; 
			//lstrcpy(pLogFont->lfFaceName,"Times New Roman");
			//pFont->hFonts[1]=CreateFontIndirect(pLogFont);

			pFont->hFonts[2].hFont=CreateFont(20,8,0,0,FW_BOLD,true,true,
									   0,0,0,0,0,0,"Times New Roman");
			pFont->hFonts[2].inaltimeCaracter=20;	
			pFont->hFonts[2].latimeCaracter=10;	
			//pLogFont->lfWeight=FW_BOLD; 
			//pLogFont->lfItalic=true; 
			//pLogFont->lfUnderline=true; 
			//pFont->hFonts[2]=CreateFontIndirect(pLogFont);

			pFont->pFonts[0]=pFont->CreazaFontD3D(gD3D->g_pD3DDevice,pFont->hFonts[0].hFont);			
			pFont->pFonts[1]=pFont->CreazaFontD3D(gD3D->g_pD3DDevice,pFont->hFonts[1].hFont);
			pFont->pFonts[2]=pFont->CreazaFontD3D(gD3D->g_pD3DDevice,pFont->hFonts[2].hFont);
			
			//GetDeviceCaps			
			//HDC hDC;			
			//TEXTMETRIC tm;
			//SelectObject(hDC,pFont->hFonts[1]);
			//GetTextMetrics(hDC,&tm);
			/*char buffer[20];			
			if(pFont->pFonts[0]->GetLogFont(pLogFont)==D3D_OK)
			//if(pFont->pFonts[1]->GetDevice(&gD3D->g_pD3DDevice)==D3D_OK)
				MessageBox(hWndMeniuPrincipal,"Bun!!!", "Nick", MB_OK);
			else
				MessageBox(hWndMeniuPrincipal,"Caca!!!", "Nick", MB_OK);*/
			///long nr;
			//nr=-1234L;
			//_itoa(pLogFont->lfWeight, buffer, 10);
			//MessageBox(hWndMeniuPrincipal,buffer, "Test", MB_OK);
			//pLogFont->lfFaceName
			
			//Initialization Fizica
			//pFizica->Init();

			QueryPerformanceCounter((LARGE_INTEGER*) &nextTime);

			if(lpFrequency!=0)
			{
				//QueryPerformanceFrequency((LARGE_INTEGER*) &lpFrequency);
				performanceFlag=true;
				timeCount=lpFrequency/25;
				QueryPerformanceCounter((LARGE_INTEGER*) &nextTime);				
			}
			else
				nextTime=timeGetTime();			
			
            MSG msg;
            ZeroMemory( &msg, sizeof(msg) );
			// Enter the message loop
			
			PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE );			

            while( msg.message!=WM_QUIT )
            {								
                if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
                {
                    TranslateMessage( &msg );
                    DispatchMessage( &msg );
                }
                else				
				{
					flagScene = false; // todo(Nicu): remove it
					if(flagScene)
					{							
						//ShowWindow( hWndMeniuPrincipal,SW_SHOW );			
						//UpdateWindow( hWndMeniuPrincipal);												
						//ShowWindow( hWndMig,SW_SHOW);			
						//UpdateWindow( hWndMig);							
												
						if(MeniuPrincipalLoad) 
						{	
							//pD3DInput->SetSysKeyboardBehavior(hWndMeniuPrincipal);						
							//LoadMeshMeniuPrincipal(hWndMeniuPrincipal);
							MeniuPrincipalLoad=false;
							Migload=true;

							//tx=0.0f;ty=0.0f;tz=0.0f;						
							rtx=1.0f;rty=0.0f;rtz=0.0f;	
							rlx=0.0f,rly=0.0f,rlz=1.0f;	
							//rotTranMig=0.0f;
							rotLongMig=0.0f;						
							viewXInitial=0.0f;viewYInitial=375.0f;viewZInitial=-1550.0f;	
							//viewXDinamic=0.0f;viewYDinamic=75.0f;viewZDinamic=400.0f;
							viewXDinamic = 0.0f; viewYDinamic = 60.0f; viewZDinamic = -1550.0f;
							viewXStatic=0.0f;viewYStatic=375.0f;viewZStatic=-1550.0f;	
							lookX=0.0f;lookY=70.0f;lookZ=700.0f;
							TimeMissionSeconds=0;
							pTransformation->Init();
							pFizica->Init();
							pFizica->InitForte();
							pFizica->InitComenzi();							

							earthtx=60.0f,earthty=55.0f,earthtz=0.0f;
						}
												
						//pTransformation->MatMig=pTransformation->MatIdentica;
						/*pTransformation->pStackMig->LoadIdentity();
						pTransformation->pStackTerrain->LoadIdentity();
						pTransformation->pStackSky->LoadIdentity();
						pTransformation->pStackCameraUp->LoadIdentity();
						*/
						
						if(gD3D->g_pD3DDevice->TestCooperativeLevel()==D3DERR_DEVICELOST)							
						{
							//MessageBox(hWndMeniuPrincipal,"device lost", "Nick", MB_OK);													
							//gD3D->g_pD3DDevice->Reset(&gD3D->Echipament.Parametri);
						}
						else
						if(gD3D->g_pD3DDevice->TestCooperativeLevel()==D3DERR_DEVICENOTRESET)
							{
								//MessageBox(hWndMeniuPrincipal,"device not reset", "Nick", MB_OK);
								//if(gD3D->g_pD3DDevice->Reset(&gD3D->Echipament.Parametri)==D3D_OK)
									//MessageBox(hWndMeniuPrincipal,"reset ok", "Nick", MB_OK);
								//else
									//MessageBox(hWndMeniuPrincipal,"reset not ok", "Nick", MB_OK);
							}
						
						//if(gD3D->g_pD3DDevice->TestCooperativeLevel()==D3D_OK)
							//RenderMeniuPrincipal(pTransformation->EarthTransformationStackMatrix(&earthtx,&earthty,&earthtz,&rx,&ry,&rz,&unghiOy),hWndMeniuPrincipal);																		
						
					}
	 				else
					{
						//ShowWindow( hWndMig,SW_SHOW );			
						//UpdateWindow( hWndMig);												
						//ShowWindow( hWndMeniuPrincipal,SW_HIDE);									
						//UpdateWindow( hWndMeniuPrincipal);		
												
						if(Migload)
						{
							pD3DInput->CreateSysKeyboardDevice(hWndMig);
							pD3DInput->SetSysKeyboardBehavior(hWndMig);	
							//pD3DInput->CreateD3DInputObject(hInstantaAplicatiei,hWndMig);
							//pD3DInput->EnumDevices(hWndMig); 
							LoadMeshes(hWndMig);
							Migload=false;
							MeniuPrincipalLoad=true;

							// todo(Nicu): this block was added for init w/o main menu
							//tx=0.0f;ty=0.0f;tz=0.0f;						
							rtx = 1.0f; rty = 0.0f; rtz = 0.0f;
							rlx = 0.0f, rly = 0.0f, rlz = 1.0f;
							//rotTranMig=0.0f;
							rotLongMig = 0.0f;
							viewXInitial = 0.0f; viewYInitial = 375.0f; viewZInitial = -1550.0f;
							//viewXDinamic = 0.0f; viewYDinamic = 75.0f; viewZDinamic = 400.0f;
							viewXDinamic = 0.0f; viewYDinamic = 114.0f; viewZDinamic = 291.0f;
							//viewXStatic = 0.0f; viewYStatic = 375.0f; viewZStatic = -1550.0f;
							//lookX = 0.0f; lookY = 70.0f; lookZ = 700.0f;
							lookX = 0.0f; lookY = 98.0f; lookZ = 600.0f;
							TimeMissionSeconds = 0;
							pTransformation->Init();
							pFizica->Init();
							pFizica->InitForte();
							pFizica->InitComenzi();

							earthtx = 60.0f, earthty = 55.0f, earthtz = 0.0f;
						}
						if(flagPaused==false)							
						{	
							pD3DInput->ProcessSysKeyboardInput(hWndMig);													

							//masuram timpul la inceputul randarii frame-ului
							//LONGLONG pPerformanceCountBeginFrame;// address of current counter value 						
							//QueryPerformanceCounter((LARGE_INTEGER*) &pPerformanceCountBeginFrame); 
							
							//BeginScene(hWndMig,&pTransformation->MatMig);																																							     
							gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_MINFILTER, D3DTEXF_LINEAR); 							
							gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_MAGFILTER, D3DTEXF_ANISOTROPIC); 
							gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_MIPFILTER, D3DTEXF_LINEAR); 
							gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_ADDRESSU,  D3DTADDRESS_MIRROR);
							gD3D->g_pD3DDevice->SetTextureStageState( 0, D3DTSS_ADDRESSV,  D3DTADDRESS_MIRROR);

							//cub mapping	
							/*pEnvMap->RetineSetarileActuale(gD3D->g_pD3DDevice);
							for(DWORD fata=0;fata<5;fata++)
							{														
								pEnvMap->CubMap(fata,gD3D->g_pD3DDevice);
								gD3D->g_pD3DDevice->BeginScene();
								gD3D->g_pD3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,
												D3DXCOLOR(0.67f,0.82f,0.91f,1.0f), 1.0f, 0 );														
								RenderTeren(hWndMig,&pTransformation->MatTerrain);														
								RenderCer(hWndMig,&pTransformation->MatSkyTransformation);
								gD3D->g_pD3DDevice->EndScene();

							}
							pEnvMap->RefacereSetari(gD3D->g_pD3DDevice);*/

							if(moveFlag)
							{						
								//pD3DInput->UpdateInputState(hWndMig);
								CalculeazaParametri(&pTransformation->MatMig);

								//Fizica mig	
								pFizica->fps=25.0f;//(float)(lpFrequency/(curentTime-nextTime));
								pFizica->tpf=0.04f;//(float)((curentTime-nextTime)/lpFrequency);
								if(pFizica->vzfMig>0.0f)
									TimeMissionSeconds+=pFizica->tpf;
								else
									TimeMissionSeconds=0.0f;
								pFizica->altUnitWorld=pFizica->VectorCentruRoti.y + 146.44f;							
								//pFizica->altUnitWorld=pFizica->tablouVectoriTestati[pFizica->index].vectorActual.y;
								pFizica->altM=pFizica->altUnitWorld / 100.0f;							
								//pFizica->SalvezaMarimiInainteDeTestColiziuni();//temp
								// disable for moving camera by keyboard
								pFizica->CalculeazaParametriAerodinamici(&pTransformation->MatMig, pMeshTerrain);
						
								/*if(pFizica->TestColiziuni(texTerenMesh,&pTransformation->MatMig)==true)
								{
									//MessageBox(hWndMig,"Bun!!!", "Nick", MB_OK);								
									pFizica->CalculeazaMarimiPanaLaColiziuni();								
									//if(pFizica->VectorCentruRoti.y==0.0f)
									//	flagPaused=true;								
								}*/

								//pFizica->SalvezaMarimiInainteDeTestColiziuni();
								/*if(pFizica->TestColiziuniNew(&pTransformation->MatMig,
														   pMeshMig,pMeshTerrain,
												 pFizica->tablouVectoriTestati)==TRUE)*/
								pFizica->TestColiziuniNew(&pTransformation->MatMig, pMeshMig, pMeshTerrain, pFizica->tablouVectoriTestati);
								//end fizica
																
								pTransformation->MigTransformationStackMatrix(&pFizica->txMig,&pFizica->tyMig,&pFizica->tzMig,																		
																		&pFizica->rtx,&pFizica->rty,&pFizica->rtz,&pFizica->unghiRotatieTransversalaMig,
																		&pFizica->rlx,&pFizica->rly,&pFizica->rlz,&pFizica->unghiRotatieLongitudinalaMig,
																		&pFizica->rvx,&pFizica->rvy,&pFizica->rvz,&pFizica->unghiRotatieVerticalaMig,
																		&pFizica->vectorAxaRotatieContact,&pFizica->unghiRotatieDupaContact);
									//este necesara stiva de matrici a mig-ului
									//pentru deplasarea relativa fata de pamant
									//pentru parametrii de zbor						

								pTransformation->TerrainTransformationStackMatrix(
																		&pFizica->txMig,&pFizica->tyMig,&pFizica->tzMig,																		
																		&pFizica->rtx,&pFizica->rty,&pFizica->rtz,&pFizica->unghiRotatieTransversalaMig,
																		&pFizica->rlx,&pFizica->rly,&pFizica->rlz,&pFizica->unghiRotatieLongitudinalaMig,
																		&pFizica->rvx,&pFizica->rvy,&pFizica->rvz,&pFizica->unghiRotatieVerticalaMig,
																		&pFizica->vectorAxaRotatieContact,&pFizica->unghiRotatieDupaContact);
									//pamantul se misca relativ fata de mig																	
									//a fost necesar datorita randarii tremurate 
									//a mig-ului odata cu crestere foarte mare a 
									//valorilor coordonatelor vertex-ilor																		
								moveFlag=false;																

							}
							
							//QueryPerformanceCounter((LARGE_INTEGER*) &curentTime);
							//flagPaused=true;
							//RenderFrame(hWndMig);
							if(performanceFlag)
								QueryPerformanceCounter((LARGE_INTEGER*) &curentTime);
							else
								curentTime=timeGetTime();
							

							if(curentTime>=nextTime)
							{															
								RenderFrame(hWndMig);
								//Frame rate							 														
								pPerformanceCountBeginFrame=pPerformanceCountEndFrame;
								QueryPerformanceCounter((LARGE_INTEGER*) &pPerformanceCountEndFrame); 
							
								//QueryPerformanceCounter((LARGE_INTEGER*) &pPerformanceCountBeginFrame); 							
								QueryPerformanceFrequency((LARGE_INTEGER*) &lpFrequency); 
							
								//FrameRate+=1.0f;//(float)(lpFrequency/(pPerformanceCountEndFrame - pPerformanceCountBeginFrame));											
							
						
								TimeMissionFrame=(float)(pPerformanceCountEndFrame - pPerformanceCountBeginFrame);
								//nu mai asa da calculul
								TimeMissionFrame=TimeMissionFrame/lpFrequency;						
								//if(pFizica->vzfMig>0.0f)
								//	TimeMissionSeconds+=TimeMissionFrame;

								if(TimeCount<=1.0f)
								{
									TimeCount+=TimeMissionFrame;
									FrameCount+=1;								
								}
								else		
								{
									FrameRate=FrameCount;						
									TimeCount=0.0f;
									FrameCount=0;
								}

								//FrameRate=(float)(lpFrequency/(pPerformanceCountEndFrame - pPerformanceCountBeginFrame));											
								nextTime+=timeCount;

								if(nextTime<curentTime)
									nextTime=curentTime+timeCount;

								moveFlag=true;
							}
																							
							//TimeMissionFrame=(float)(pPerformanceCountEndFrame - pPerformanceCountBeginFrame);						
							//nu mai asa da calculul
							//TimeMissionFrame=TimeMissionFrame/lpFrequency;						
							//if(pFizica->vzfMig>0.0f)
								//TimeMissionSeconds=TimeMissionSeconds+TimeMissionFrame;						
							
							/*if(TimeCount<=1.0f)
							{
								TimeCount+=TimeMissionFrame;
								FrameCount+=1;								
							}
							else		
							{
								FrameRate=FrameCount;						
								TimeCount=0.0f;
								FrameCount=0;
							}*/
							
							//TimeMissionSecunde=TimeMissionFrame;																			
													
						}
													
					}
				}
									
            }
        }
    }

    // Clean up everything and exit the app
    Cleanup();
    //UnregisterClass( "Meniu Principal", wcMeniuPrincipal.hInstance );
	UnregisterClass( "MIG 21 LANCER", wcMig.hInstance );
    return 0;
}



