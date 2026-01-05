#include "SistemParticule.h"


SistemeParticule::SistemeParticule()
{	

	PointSizeNormal=1.0f;

	//jet
	first=true;
	PointSize=7.0f;	
	PointScaleA=0.0f;
	PointScaleB=0.0f;
	PointScaleC=0.0f;
	NrVerticesTotal=0;
	NrVerticesPerFrontFlameInitial=0;
	NrVerticesForRender=0;
	inel=0;

	//cloud
	firstCloud=true;
	NrVerticesTotalCloud=0;
	NrVerticesForRenderCloud=0;				
	PointSizeCloud=500.0f;	
	PointScaleACloud=0.0f;
	PointScaleBCloud=0.0f;
	PointScaleCCloud=0.0f;

}

HRESULT SistemeParticule::CreateVertexBufferJet(LPDIRECT3DDEVICE8 g_pd3dDevice)
{	
	int NrVertPerFrontFlame;

	NrVertPerFrontFlame=NrVerticesPerFrontFlameInitial;

	while(NrVertPerFrontFlame>=1)
	{
		NrVerticesTotal+=NrVertPerFrontFlame;
		if(NrVertPerFrontFlame>NrVerticesPerFrontFlameInitial/2)			
			NrVertPerFrontFlame--;			
		else
			NrVertPerFrontFlame-=2;			
	}

	if(SUCCEEDED(g_pd3dDevice->CreateVertexBuffer(NrVerticesTotal*sizeof(Vertex),0,
												  D3DFVF_Vertex,
												  D3DPOOL_DEFAULT,&pVBJet)))
		return S_OK;
	else
		return E_FAIL;
}

HRESULT SistemeParticule::LockVertexBufferJet(D3DXVECTOR3 center)
{
	Vertex *pVertices;
	int i=0,j=1,k=0;
	int NrVerticesPerFrontFlame;
	float radiusInel,radiusInelFirst,pasInel,pasInelFirst;

	NrVerticesPerFrontFlame=NrVerticesPerFrontFlameInitial;
	radiusInelFirst=radius;
	radiusInel=radius;
	pasInelFirst=8.0f;
	pasInel=pasInelFirst;
	
	//ZeroMemory( &pVertices, sizeof(Vertex));
    if( FAILED(pVBJet->Lock( 0, 0, (BYTE**)&pVertices, 0 ) ) )
        return E_FAIL; 	
	else
	{
		//for(j;j<NrFlameFront;j++)
		while(NrVerticesPerFrontFlame>=1)
		{
			for(j;j<=NrVerticesPerFrontFlame;j++,i++)
			{
				pVertices[i].position = D3DXVECTOR3(center.x+(float)(radiusInel*cos(j*2*D3DX_PI/(NrVerticesPerFrontFlame))),
												center.y+(float)(radiusInel*sin(j*2*D3DX_PI/(NrVerticesPerFrontFlame))),
												center.z);
				pVertices[i].normal   = D3DXVECTOR3(center.x+(float)(radiusInel*cos(j*2*D3DX_PI/(NrVerticesPerFrontFlame))),
												center.y+(float)(radiusInel*sin(j*2*D3DX_PI/(NrVerticesPerFrontFlame))),
												center.z);	
				pVertices[i].color=D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
				pVertices[i].tu=0.5f;
				pVertices[i].tv=0.5f;								
			}				
			j=1;			
			radius-=0.5f;
			if(k<4)
			{				
				k++;
				radiusInel-=pasInel;
				pasInel-=0.6f;
			}
			else
			{		
				pasInelFirst-=0.6f;
				pasInel=pasInelFirst;
				center.z-=18.0f;			
				radiusInel=radius;
				if(radiusInel>radiusInelFirst/3.0f)
					k=2;
				else
					if(radiusInel>radiusInelFirst*2.0f/3.0f)
						k=3;
					else
						k=4;
			}
			if(NrVerticesPerFrontFlame>NrVerticesPerFrontFlameInitial/2)			
				NrVerticesPerFrontFlame--;			
			else
				NrVerticesPerFrontFlame-=2;			
		}
		pVertices=NULL;
		pVBJet->Unlock();    
		return S_OK;
	}
 	
}

void SistemeParticule::SetVertexJet(LPDIRECT3DDEVICE8 g_pd3dDevice,D3DXVECTOR3 center)
{
	if(first)
	{
		CreateVertexBufferJet(g_pd3dDevice);
		LockVertexBufferJet(center);
		first=false;
	}
}

void SistemeParticule::DrawFlameFrontJet(LPDIRECT3DDEVICE8 g_pd3dDevice,int NrVertices)
{	
	g_pd3dDevice->SetStreamSource( 0,pVBJet, sizeof(Vertex));	    
	g_pd3dDevice->SetVertexShader( D3DFVF_Vertex);	
    g_pd3dDevice->DrawPrimitive(D3DPT_POINTLIST ,0,NrVertices);
}

//clouds
HRESULT SistemeParticule::CreateVertexBufferCloud(LPDIRECT3DDEVICE8 g_pd3dDevice)
{	
	//int NrVertPerCloud;
		
	if(SUCCEEDED(g_pd3dDevice->CreateVertexBuffer(NrVerticesTotalCloud*sizeof(Vertex),0,
												  D3DFVF_Vertex,
												  D3DPOOL_DEFAULT,&pVBCloud)))
		return S_OK;
	else
		return E_FAIL;
}

HRESULT SistemeParticule::LockVertexBufferCloud()
{
	Vertex *pVertices;
	int i=0,j=1,k=0;		
	float newPosX,newPosY,newPosZ; 
	float distPuncte;

	newPosX=0.0f;
	newPosY=100.0f;
	newPosZ=4000.0f;
	distPuncte=30.0f;
	//ZeroMemory( &pVertices, sizeof(Vertex));
    if( FAILED(pVBCloud->Lock(0,0,(BYTE**)&pVertices,0)))
        return E_FAIL; 	
	else
	{		
		while(i<NrVerticesTotalCloud)
		{
			if(i<NrVerticesTotalCloud/4)
			{
				pVertices[i].size=400; 
				pVertices[i].position = D3DXVECTOR3(newPosX,newPosY,newPosZ+=distPuncte);
				pVertices[i].normal   = D3DXVECTOR3(newPosX,newPosY,newPosZ+=distPuncte);
				pVertices[i].color=D3DXCOLOR(1.0f,0.0f,0.0f,1.0f);
				pVertices[i].tu=0.5f;
				pVertices[i].tv=0.5f;											
				i++;
			}
			else
				if(i<NrVerticesTotalCloud*2/4)
				{					
					distPuncte=45.0f;
					newPosX=distPuncte;
					pVertices[i].size=400; 
					pVertices[i].position = D3DXVECTOR3(newPosX,newPosY,newPosZ-=distPuncte);
					pVertices[i].normal   = D3DXVECTOR3(newPosX,newPosY,newPosZ-=distPuncte);
					pVertices[i].color=D3DXCOLOR(1.0f,0.0f,0.0f,1.0f);
					pVertices[i].tu=0.5f;
					pVertices[i].tv=0.5f;											
					i++;
				}
				else
					if(i<NrVerticesTotalCloud*3/4)
					{				
						distPuncte=50.0f;
						newPosX=2*distPuncte;
						pVertices[i].size=400; 
						pVertices[i].position = D3DXVECTOR3(newPosX,newPosY,newPosZ+=distPuncte);
						pVertices[i].normal   = D3DXVECTOR3(newPosX,newPosY,newPosZ+=distPuncte);
						pVertices[i].color=D3DXCOLOR(1.0f,0.0f,0.0f,1.0f);
						pVertices[i].tu=0.5f;
						pVertices[i].tv=0.5f;											
						i++;
					}
					else
						if(i<NrVerticesTotalCloud)
						{			
							distPuncte=45.0f;
							newPosX=3*distPuncte;
							pVertices[i].size=400; 
							pVertices[i].position = D3DXVECTOR3(newPosX,newPosY,newPosZ-=distPuncte);
							pVertices[i].normal   = D3DXVECTOR3(newPosX,newPosY,newPosZ-=distPuncte);
							pVertices[i].color=D3DXCOLOR(1.0f,0.0f,0.0f,1.0f);
							pVertices[i].tu=0.5f;
							pVertices[i].tv=0.5f;											
							i++;
						}
		}
		
		pVertices=NULL;
		pVBCloud->Unlock();    
		return S_OK;
	}
 	
}

void SistemeParticule::SetVertexCloud(LPDIRECT3DDEVICE8 g_pd3dDevice)
{
	if(firstCloud)
	{
		CreateVertexBufferCloud(g_pd3dDevice);
		LockVertexBufferCloud();
		firstCloud=false;
	}
}

void SistemeParticule::DrawCloud(LPDIRECT3DDEVICE8 g_pd3dDevice,int NrVertices)
{	
	g_pd3dDevice->SetStreamSource( 0,pVBCloud, sizeof(Vertex));	
	g_pd3dDevice->SetVertexShader( D3DFVF_Vertex);	
    g_pd3dDevice->DrawPrimitive(D3DPT_POINTLIST ,0,NrVertices);
}




	






