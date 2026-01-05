#include "d3d8.h"
#include "d3d8types.h"
#include "D3dx8math.h"

class Clouds{
//functii publice
public:		
		Clouds();
		~Clouds();				
		HRESULT CreateVertexBufferCloud(LPDIRECT3DDEVICE8 g_pd3dDevice);
		HRESULT LockVertexBufferCloud(D3DXVECTOR3 vImpostorCenter,
									  float ImpostorHeight,
									  float ImpostorWidth);
		void SetVertexCloud(LPDIRECT3DDEVICE8 g_pd3dDevice,
							D3DXVECTOR3 vImpostorCenter,
							float ImpostorHeight,
							float ImpostorWidth);
		void DrawCloud(LPDIRECT3DDEVICE8 g_pd3dDevice,
					   D3DPRIMITIVETYPE PrimitiveType,
					   UINT StartVertex,UINT PtimitiveCount);
		void VolumeTexture(LPDIRECT3DDEVICE8 pd3dDevice);
		void VolumeTextureFromProfiles(LPDIRECT3DDEVICE8 pd3dDevice);
		void LoadTexturesFromFile(LPDIRECT3DDEVICE8 pd3dDevice);
		void LoadProfilesTexturesFromFile(LPDIRECT3DDEVICE8 pd3dDevice);

		HRESULT GenerateDynamicImpostors(LPDIRECT3DDEVICE8 g_pd3dDevice,
										 D3DXVECTOR3 vCameraView,
										 D3DXVECTOR3 vTopLeftBack,
										 D3DXVECTOR3 vTopLeftFront,
										 D3DXVECTOR3 vTopRightBack,
										 D3DXVECTOR3 vTopRightFront,
										 D3DXVECTOR3 vBottomLeftBack,
										 D3DXVECTOR3 vBottomLeftFront,
										 D3DXVECTOR3 vBottomRightBack,
										 D3DXVECTOR3 vBottomRightFront,
			                             D3DXMATRIX* pWorldMatrix);
		HRESULT GenerateDynamicImpostor(LPDIRECT3DDEVICE8 g_pd3dDevice,
										 D3DXVECTOR3 vCameraView,
										 D3DXVECTOR3 vImpostorCenter,//in origine
										 D3DXVECTOR3 vPozitie,
										 float ImpostorHeight,
										 float ImpostorWidth,
										 D3DXMATRIX *pWorldMatrix);
		HRESULT GenerateDynamicImpostorNew(LPDIRECT3DDEVICE8 g_pd3dDevice,
										D3DXVECTOR3 vCameraView,
										D3DXVECTOR3 vImpostorPosition,
										float ImpostorHeight,
										float ImpostorWidth,
										D3DXMATRIX* pWorldMatrix);
		LPDIRECT3DTEXTURE8 GenerateCloudTexture(LPDIRECT3DDEVICE8 pDevice, int width, int height);
						
private:			
						
				
//date publice
public:	
		struct Vertex
		{
			D3DXVECTOR3 position; 
			D3DXVECTOR3 normal;   			
			//D3DXCOLOR color;
			FLOAT tu1,tv1,tw1;			
			//FLOAT tu2,tv2,tw2;			
			//FLOAT tu3,tv3,tw3;			
		};
		#define D3DFVF_VertexCloud (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1|D3DFVF_TEXCOORDSIZE3(0))					

		Vertex *pVertices;
		LPDIRECT3DVERTEXBUFFER8 pVBCloud;			
		LPDIRECT3DTEXTURE8 pTextureCloud[10];
		LPDIRECT3DTEXTURE8 pTextureProfilOrizontalNor,
						   pTextureProfilVerticalNor;
		LPDIRECT3DVOLUMETEXTURE8 volTexture;
		int NrVerticesTotalCloud,VertSlicesNr,OrizSlicesNr;						
		bool firstCloud;
		LPCSTR pSrcFile[10];
		LPCSTR pSrcFileProfilesTextures[2];

		//dynamic impostors
		D3DXVECTOR3 vCameraViewGizmoBoxCenter;
		D3DXVECTOR3 vGizmoBoxCenter,
			        //vTopLeftBack,vTopLeftFront,vTopRightBack,vTopRightFront,
					//vBottomLeftBack,vBottomLeftFront,vBottomRightBack,vBottomRightFront,
					vAxaOx,vAxaOy,vAxaOz;

		D3DXPLANE planeImpostor1,planeImpostor2,planeImpostor3,
			      planeImpostor4,planeImpostor5,planeImpostor6,
				  planeImpostor7;

		float unghiViewAxaOx,unghiViewAxaOy,unghiViewAxaOz,
			  unghiProiectieCameraViewAxaOx, unghiProiectieCameraViewImpostorPositionAxaOz;

		D3DXVECTOR3 vIntersectie,vecIntersectie[8];
		int indexVertex,indexVertexFataSus,indexVertexFataJos,indexVertexFeteLaterale;

		D3DXVECTOR3 cameraDirection;
		D3DXVECTOR3 vCameraViewImpostorPosition;
		D3DXVECTOR3 vImpostorCenterPosition;
		D3DXMATRIX impostorMatrix;
		LPD3DXMATRIXSTACK pStackImpostorMatrix;		
};
