#include "d3d8.h"
#include "d3d8types.h"
#include "D3dx8math.h"

class SistemeParticule{
//functii publice
public:
		//jet
		SistemeParticule();
		~SistemeParticule();
		HRESULT CreateVertexBufferJet(LPDIRECT3DDEVICE8 g_pd3dDevice);
		HRESULT LockVertexBufferJet(D3DXVECTOR3 center);
		void SetVertexJet(LPDIRECT3DDEVICE8 g_pd3dDevice,D3DXVECTOR3 center);
		void DrawFlameFrontJet(LPDIRECT3DDEVICE8 g_pd3dDevice,int NrVertices);

		//clouds
		HRESULT CreateVertexBufferCloud(LPDIRECT3DDEVICE8 g_pd3dDevice);
		HRESULT LockVertexBufferCloud();
		void SetVertexCloud(LPDIRECT3DDEVICE8 g_pd3dDevice);
		void DrawCloud(LPDIRECT3DDEVICE8 g_pd3dDevice,int NrVertices);


		
		
		
private:
		//jet
		LPDIRECT3DVERTEXBUFFER8 pVBJet;
		struct Vertex
		{
			
			D3DXVECTOR3 position; 
			D3DXVECTOR3 normal;   
			float size;
			D3DXCOLOR color;
			FLOAT tu,tv;			
		};
		#define D3DFVF_Vertex (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_PSIZE|D3DFVF_DIFFUSE|D3DFVF_TEX1)	
		bool first;
		//clouds
		LPDIRECT3DVERTEXBUFFER8 pVBCloud;
		
				
//date publice
public:
		float PointSizeNormal;

		//jet
		int NrVerticesPerFrontFlameInitial,NrVerticesTotal,NrVerticesForRender,inel;
		int NrFlameFront;
		float radius;
		float PointSize,PointScaleA,PointScaleB,PointScaleC;

		//cloud
		int NrVerticesTotalCloud,NrVerticesForRenderCloud;				
		float PointSizeCloud,
			  PointScaleACloud,PointScaleBCloud,PointScaleCCloud;

		bool firstCloud;
		
private:
		
};
