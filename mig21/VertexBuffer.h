#include "d3d8.h"
#include "d3d8types.h"
#include "D3dx8math.h"

class VertexBuffer{
//functii publice
public:
		VertexBuffer();
		~VertexBuffer();
		HRESULT CreateVertexBufferDinamic(LPDIRECT3DDEVICE8 g_pd3dDevice);
		HRESULT LockVertexBuffer(D3DXVECTOR3 center);
		void DrawFlameFront(LPDIRECT3DDEVICE8 g_pd3dDevice,D3DXVECTOR3 center);

		
		
		
private:
		LPDIRECT3DVERTEXBUFFER8 pVB;
		struct Vertex
		{
			D3DXVECTOR3 position; 
			D3DXVECTOR3 normal;   			
			FLOAT tu,tv;
		};
		#define D3DFVF_Vertex (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)	
		bool first;
		
				
//date publice
public:
		int NrVertices;
		int NrFlameFront;
		float radius;
		
private:
		
};
