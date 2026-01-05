#include "EnvMap.h"

EnvMap::EnvMap()
{
	vView=D3DXVECTOR3(0.0f,0.0f,0.0f);
	
}

void EnvMap::Init(HWND hWnd,LPDIRECT3DDEVICE8 g_pd3dDevice)
{
	CreazaCubMap(hWnd,g_pd3dDevice);
	//RetineSetarileActuale(g_pd3dDevice);
}


HRESULT EnvMap::CreazaCubMap(HWND hWnd,LPDIRECT3DDEVICE8 g_pd3dDevice)
{
	//folosim un caz particular care se poate generaliza
	//D3DSURFACE_DESC *pDesc;
	//pBackBuffer->GetDesc(pDesc);
	//D3DUSAGE_RENDERTARGET
	if(FAILED(g_pd3dDevice->CreateCubeTexture( 16, 1, D3DUSAGE_RENDERTARGET,D3DFMT_X8R8G8B8,//pDesc->Format
                                D3DPOOL_DEFAULT, &pCubeMap )))
	{
		MessageBox(hWnd,"AiciNick F", NULL, MB_OK); 															
		return E_FAIL;
	}
	else
	{
		//MessageBox(hWnd,"AiciNick S", NULL, MB_OK); 															
		return S_OK;
	}	
}
//retine view matrix, projection matrix,BackBuffer,ZBuffer
void EnvMap::RetineSetarileActuale(LPDIRECT3DDEVICE8 g_pd3dDevice)
{
	//g_pd3dDevice->GetTransform(D3DTS_VIEW,&matViewSave);
	//g_pd3dDevice->GetTransform(D3DTS_PROJECTION,&matProjSave);
	g_pd3dDevice->GetRenderTarget(&pBackBuffer);
	g_pd3dDevice->GetDepthStencilSurface(&pZBuffer);
}


void EnvMap::CubMap(DWORD fata,LPDIRECT3DDEVICE8 g_pd3dDevice)
{		
	g_pd3dDevice->EndScene();
	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH(&matProj,D3DX_PI/3.5f,1.33f,60.0f,30000000.0f);
	g_pd3dDevice->SetTransform(D3DTS_PROJECTION,&matProj);			

		switch(fata)
		{
			case D3DCUBEMAP_FACE_POSITIVE_X:
				vLook=D3DXVECTOR3(1.0f,0.0f,0.0f);
				vUp=D3DXVECTOR3(0.0f,1.0f,0.0f);
				break;
			case D3DCUBEMAP_FACE_NEGATIVE_X:
				vLook=D3DXVECTOR3(-1.0f,0.0f,0.0f);
				vUp=D3DXVECTOR3(0.0f,1.0f,0.0f);
				break;
			case D3DCUBEMAP_FACE_POSITIVE_Y:
				vLook=D3DXVECTOR3(0.0f,1.0f,0.0f);
				vUp=D3DXVECTOR3(0.0f,0.0f,-1.0f);
				break;
			case D3DCUBEMAP_FACE_NEGATIVE_Y:
				vLook=D3DXVECTOR3(0.0f,-1.0f,0.0f);
				vUp=D3DXVECTOR3(0.0f,0.0f,1.0f);
				break;
			case D3DCUBEMAP_FACE_POSITIVE_Z:
				vLook=D3DXVECTOR3(0.0f,0.0f,1.0f);
				vUp=D3DXVECTOR3(0.0f,1.0f,0.0f);
				break;
			case D3DCUBEMAP_FACE_NEGATIVE_Z:
				vLook=D3DXVECTOR3(0.0f,0.0f,-1.0f);
				vUp=D3DXVECTOR3(0.0f,1.0f,0.0f);
				break;
		}

		D3DXMATRIX matView;
		D3DXMatrixLookAtLH(&matView,&vView,&vLook,&vUp);
		g_pd3dDevice->SetTransform(D3DTS_VIEW,&matView);

		LPDIRECT3DSURFACE8 pFace;
		//AICI ESTE BUBA!!!!!!!!!!!!!!!!!!!!!!!		
		pCubeMap->GetCubeMapSurface((D3DCUBEMAP_FACES)fata,0,&pFace);		
		g_pd3dDevice->SetRenderTarget(pFace,pZBuffer);
		pFace->Release();

		//g_pd3dDevice->BeginScene();		
		//Render() something					
}		//g_pd3dDevice->EndScene();

void EnvMap::RefacereSetari(LPDIRECT3DDEVICE8 g_pd3dDevice)
{		
	g_pd3dDevice->SetRenderTarget( pBackBuffer, pZBuffer );
    pBackBuffer->Release();
    pZBuffer->Release();
	//g_pd3dDevice->SetTransform( D3DTS_VIEW,&matViewSave );
    //g_pd3dDevice->SetTransform( D3DTS_PROJECTION,&matProjSave );

}

void EnvMap::SetareCoordonateTextura(LPDIRECT3DDEVICE8 g_pd3dDevice)
{
	g_pd3dDevice->SetTextureStageState( 0, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEREFLECTIONVECTOR );
    g_pd3dDevice->SetTextureStageState( 0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT3 );	    

}


void EnvMap::RefacereCoordonateTextura(LPDIRECT3DDEVICE8 g_pd3dDevice)
{
	g_pd3dDevice->SetTextureStageState( 0, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_PASSTHRU );
	g_pd3dDevice->SetTextureStageState( 0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE );	    
}

    
