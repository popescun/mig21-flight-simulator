#include "Matrix.h"

Matrix::Matrix()
{

}

void  Matrix::SetupWorldMatrix(LPDIRECT3DDEVICE8 g_pd3dDevice,D3DXMATRIX *matWorld)
{	        		
    g_pd3dDevice->SetTransform( D3DTS_WORLD, matWorld );        
}

D3DXMATRIX  Matrix::SetupViewMatrix(LPDIRECT3DDEVICE8 g_pd3dDevice,
									D3DXVECTOR3* PointView,
									D3DXVECTOR3* LookAt,
									D3DXVECTOR3* VecUp)
{	            
    D3DXMATRIX matView;	
    D3DXMatrixLookAtLH( &matView, PointView,LookAt,VecUp);	
    g_pd3dDevice->SetTransform( D3DTS_VIEW, &matView );	
	return matView;
}

D3DXMATRIX  Matrix::SetupProjectionMatrix(LPDIRECT3DDEVICE8 g_pd3dDevice,
										  float FOV,float ratio, float nearPlane,float farPlane)
{	            
    D3DXMATRIX matProj;
    D3DXMatrixPerspectiveFovLH( &matProj,FOV,ratio,nearPlane,farPlane);
	if(matProj._34!=1.0f)
	{
		matProj._11=matProj._11/matProj._34;
		matProj._12=matProj._12/matProj._34;
		matProj._13=matProj._13/matProj._34;
		matProj._14=matProj._14/matProj._34;
		matProj._21=matProj._21/matProj._34;
		matProj._22=matProj._22/matProj._34;
		matProj._23=matProj._23/matProj._34;
		matProj._24=matProj._24/matProj._34;
		matProj._31=matProj._31/matProj._34;
		matProj._32=matProj._32/matProj._34;
		matProj._33=matProj._33/matProj._34;
		matProj._34=matProj._34/matProj._34;
		matProj._41=matProj._41/matProj._34;
		matProj._42=matProj._42/matProj._34;
		matProj._43=matProj._43/matProj._34;
		matProj._44=matProj._44/matProj._34;
	}
    g_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );
	return matProj;
}

//matricile de vizualizare si perspectiva se pot combina intr-una 
//singura pentru a reduce costurile de calcul

/*D3DXMATRIX* D3DXMatrixScaling(
  D3DXMATRIX* pOut,
  FLOAT sx,
  FLOAT sy,
  FLOAT sz,
);*/ 
