#include "d3d8.h"
#include "d3d8types.h"
#include "D3dx8math.h"

class Matrix{
//functii publice
public:
		Matrix();
		void SetupWorldMatrix(LPDIRECT3DDEVICE8 g_pd3dDevice,D3DXMATRIX *matWorld);
		D3DXMATRIX SetupViewMatrix(LPDIRECT3DDEVICE8 g_pd3dDevice,
									D3DXVECTOR3* PointView,
									D3DXVECTOR3* LookAt,
									D3DXVECTOR3* VecUp);
		D3DXMATRIX SetupProjectionMatrix(LPDIRECT3DDEVICE8 g_pd3dDevice,
										 float FOV,float ratio, 
										 float nearPlane,float farPlane);
		
private:
		
		
		
//date publice
public:				
		
		
		
public:
		
		
						
};