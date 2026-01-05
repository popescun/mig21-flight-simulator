#include "d3d8.h"
#include "d3d8types.h"
#include "D3dx8math.h"
#include "math.h"

class Terrain{
//functii publice
public:
		struct Point{
			int i;
			int j;
		};
		struct Nod{
			struct Nod* A;
			struct Nod* B;
			struct Nod* C;
			struct Nod* D;
			struct Nod* Parinte;
			bool flagA,flagB,flagC,flagD;
			//struct BinaryTriangleTree* tri;
			struct Point Point1;
			struct Point Point2;
			struct Point Point3;
			struct Point Point4;
		};
		Terrain();
		~Terrain();
		HRESULT CreateVertexBufferDinamic(LPDIRECT3DDEVICE8 g_pd3dDevice);
		void QuadTree(LPDIRECT3DDEVICE8 g_pd3dDevice,
					  D3DXVECTOR3 *pView,
					  D3DXVECTOR3 *pLeftViewingFrustum,
					  D3DXVECTOR3 *pRightViewingFrustum,
					  struct Nod* nod,int nivel);
		bool VerificaNod(D3DXVECTOR3 *pView,
							  D3DXVECTOR3 *pLeftViewingFrustum,
							  D3DXVECTOR3 *pRightViewingFrustum,
							  struct Nod* nod);
		HRESULT LockVertexBuffer(struct Nod* nod);
		void DrawTerrain(LPDIRECT3DDEVICE8 g_pd3dDevice,struct Nod* nod);
		void BuilMatrixOfVariance();
		
		
		
private:
		
		
		
//date publice
public:
		

		
		
						
private:		
		LPDIRECT3DVERTEXBUFFER8 pVB;
		struct Vertex
		{
			D3DXVECTOR3 position; 
			D3DXVECTOR3 normal;   			
			FLOAT tu,tv;
		};
		#define D3DFVF_Vertex (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)			
		D3DXVECTOR3 MatrixOfVariance[16][16];/*={
			{D3DXVECTOR3(-15000000,0,15000000),
			 D3DXVECTOR3(-15000000,0,15000000),},

		};*/
		
};