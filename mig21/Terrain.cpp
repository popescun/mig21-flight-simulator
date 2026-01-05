#include "Terrain.h"

Terrain::Terrain()
{
	BuilMatrixOfVariance();
}


void Terrain::QuadTree(LPDIRECT3DDEVICE8 g_pd3dDevice,
					   D3DXVECTOR3 *pView,
					   D3DXVECTOR3 *pLeftViewingFrustum,
					   D3DXVECTOR3 *pRightViewingFrustum,
					   struct Nod* nod,int nivel)
{
	
	nod=new(Nod);	
	nod->A=NULL;
	nod->B=NULL;
	nod->C=NULL;
	nod->D=NULL;	
	if(nivel==0)
	{
		nod->Parinte=NULL;
		nod->flagA=false;
		nod->flagB=false;
		nod->flagC=false;
		nod->flagD=false;
	}

	if(nod->Parinte==NULL)
	{
		nod->Point1.i=16;
		nod->Point1.j=0;
		nod->Point2.i=0;
		nod->Point2.j=0;
		nod->Point3.i=0;
		nod->Point3.j=16;
		nod->Point4.i=16;
		nod->Point4.j=16;
	}
	else
		if((nod->Parinte->flagA==true)&&(nod->Parinte->flagB==false)
		  &&(nod->Parinte->flagC==false)&&(nod->Parinte->flagD==false))
		{
			nod->Point1=nod->Parinte->Point1;
			nod->Point2.i=(nod->Parinte->Point1.i+nod->Parinte->Point2.i+1)/2;
			nod->Point2.j=nod->Parinte->Point1.j;
			nod->Point3.i=(nod->Parinte->Point1.i+nod->Parinte->Point2.i+1)/2;
			nod->Point3.j=(nod->Parinte->Point2.j+nod->Parinte->Point3.j+1)/2;
			nod->Point4.i=nod->Parinte->Point4.i;
			nod->Point4.j=(nod->Parinte->Point3.j+nod->Parinte->Point4.j+1)/2;
		}
		else
			if((nod->Parinte->flagA==false)&&(nod->Parinte->flagB==true)
		      &&(nod->Parinte->flagC==false)&&(nod->Parinte->flagD==false))
			{
				nod->Point1.i=(nod->Parinte->Point1.i+nod->Parinte->Point2.i+1)/2;
				nod->Point1.j=nod->Parinte->Point1.j;
				nod->Point2=nod->Parinte->Point2;				
				nod->Point3.i=nod->Parinte->Point3.i;				
				nod->Point3.j=(nod->Parinte->Point2.j+nod->Parinte->Point3.j+1)/2;
				nod->Point4.i=(nod->Parinte->Point2.i+nod->Parinte->Point3.i+1)/2;
				nod->Point4.j=(nod->Parinte->Point3.j+nod->Parinte->Point4.j+1)/2;
			}
			else
				if((nod->Parinte->flagA==false)&&(nod->Parinte->flagB==false)
		          &&(nod->Parinte->flagC==true)&&(nod->Parinte->flagD==false))
				{
					nod->Point1.i=(nod->Parinte->Point1.i+nod->Parinte->Point2.i+1)/2;
					nod->Point1.j=(nod->Parinte->Point2.j+nod->Parinte->Point3.j+1)/2;
					nod->Point2.i=nod->Parinte->Point2.i;
					nod->Point2.j=(nod->Parinte->Point2.j+nod->Parinte->Point3.j+1)/2;
					nod->Point3=nod->Parinte->Point3;
					nod->Point4.i=(nod->Parinte->Point3.i+nod->Parinte->Point4.i+1)/2;
					nod->Point4.j=nod->Parinte->Point4.j;					
				}
				else
					if((nod->Parinte->flagA==false)&&(nod->Parinte->flagB==false)
					  &&(nod->Parinte->flagC==false)&&(nod->Parinte->flagD==true))
					{
						nod->Point1.i=nod->Parinte->Point1.i;
						nod->Point1.j=(nod->Parinte->Point2.j+nod->Parinte->Point3.j+1)/2;
						nod->Point2.i=(nod->Parinte->Point1.i+nod->Parinte->Point2.i+1)/2;
						nod->Point2.j=(nod->Parinte->Point2.j+nod->Parinte->Point3.j+1)/2;
						nod->Point3.i=(nod->Parinte->Point2.i+nod->Parinte->Point3.i+1)/2;
						nod->Point3.j=nod->Parinte->Point3.j;
						nod->Point4=nod->Parinte->Point4;					
					}

	if(VerificaNod(pView,pLeftViewingFrustum,pRightViewingFrustum,nod)&&(nivel<(log(16)/log(2))))
	{
		nod->A->Parinte=nod;
		QuadTree(g_pd3dDevice,pView,pLeftViewingFrustum,pRightViewingFrustum,nod->A,++nivel);
		nivel--;
		nod->Parinte->flagA=false;
		nod->B->Parinte=nod;
		QuadTree(g_pd3dDevice,pView,pLeftViewingFrustum,pRightViewingFrustum,nod->B,++nivel);
		nivel--;
		nod->Parinte->flagB=false;
		nod->C->Parinte=nod;
		QuadTree(g_pd3dDevice,pView,pLeftViewingFrustum,pRightViewingFrustum,nod->C,++nivel);
		nivel--;
		nod->Parinte->flagC=false;
		nod->D->Parinte=nod;
		QuadTree(g_pd3dDevice,pView,pLeftViewingFrustum,pRightViewingFrustum,nod->D,++nivel);
		nivel--;
		nod->Parinte->flagD=false;
	}
	else
		if(VerificaNod(pView,pLeftViewingFrustum,pRightViewingFrustum,nod)&&(nivel==(log(16)/log(2))))
				DrawTerrain(g_pd3dDevice,nod);
		else			
			nod=NULL;					
}

bool Terrain::VerificaNod(D3DXVECTOR3 *pView,
							   D3DXVECTOR3 *pLeftViewingFrustum,
							   D3DXVECTOR3 *pRightViewingFrustum,
							   struct Nod* nod)
{		
	//leftPointFOV=(float)(view.x-farPlane*tan(FOV/2));
	//rightPointFOV=(float)(view.x+farPlane*tan(FOV/2));

	if(((MatrixOfVariance[nod->Point1.i][nod->Point1.j].x>pLeftViewingFrustum->x)&&
		(MatrixOfVariance[nod->Point1.i][nod->Point1.j].x<pRightViewingFrustum->x)&&
		(MatrixOfVariance[nod->Point1.i][nod->Point1.j].z>pView->z))
		|((MatrixOfVariance[nod->Point2.i][nod->Point2.j].x>pLeftViewingFrustum->x)&&
		(MatrixOfVariance[nod->Point2.i][nod->Point2.j].x<pRightViewingFrustum->x)&&
		(MatrixOfVariance[nod->Point2.i][nod->Point2.j].z>pView->z))
		|((MatrixOfVariance[nod->Point3.i][nod->Point3.j].x>pLeftViewingFrustum->x)&&
		(MatrixOfVariance[nod->Point3.i][nod->Point3.j].x<pRightViewingFrustum->x)&&
		(MatrixOfVariance[nod->Point3.i][nod->Point3.j].z>pView->z))
		|((MatrixOfVariance[nod->Point4.i][nod->Point4.j].x>pLeftViewingFrustum->x)&&
		(MatrixOfVariance[nod->Point4.i][nod->Point4.j].x<pRightViewingFrustum->x)&&
		(MatrixOfVariance[nod->Point4.i][nod->Point4.j].z>pView->z))) 
		return true;
	else
		return false;
}

HRESULT Terrain::CreateVertexBufferDinamic(LPDIRECT3DDEVICE8 g_pd3dDevice)
{
	if(SUCCEEDED(g_pd3dDevice->CreateVertexBuffer(4*sizeof(Vertex),0,
												  D3DFVF_Vertex,
												  D3DPOOL_DEFAULT,&pVB)))
		return S_OK;
	else
		return E_FAIL;
}

HRESULT Terrain::LockVertexBuffer(struct Nod* nod)
{
	int i=0,j=1;
	Vertex *pVertices;
	//ZeroMemory( &pVertices, sizeof(Vertex));
    if( FAILED(  pVB->Lock( 0, 0, (BYTE**)&pVertices, 0 ) ) )
        return E_FAIL; 
	
	else
	{		
		pVertices[0].position = MatrixOfVariance[nod->Point4.i][nod->Point4.j];
		pVertices[0].normal   = MatrixOfVariance[nod->Point4.i][nod->Point4.j];
		pVertices[0].tu=0.5f;
		pVertices[0].tv=0.5f;

		pVertices[1].position = MatrixOfVariance[nod->Point3.i][nod->Point3.j];
		pVertices[1].normal   = MatrixOfVariance[nod->Point3.i][nod->Point3.j];
		pVertices[1].tu=0.5f;
		pVertices[1].tv=0.5f;

		pVertices[2].position = MatrixOfVariance[nod->Point4.i][nod->Point4.j];
		pVertices[2].normal   = MatrixOfVariance[nod->Point4.i][nod->Point4.j];
		pVertices[2].tu=0.5f;
		pVertices[2].tv=0.5f;

		pVertices[3].position = MatrixOfVariance[nod->Point2.i][nod->Point2.j];
		pVertices[3].normal   = MatrixOfVariance[nod->Point2.i][nod->Point2.j];
		pVertices[3].tu=0.5f;
		pVertices[3].tv=0.5f;
	
		pVertices=NULL;
		pVB->Unlock();    
		return S_OK;
	}
 	
}

void Terrain::DrawTerrain(LPDIRECT3DDEVICE8 g_pd3dDevice,struct Nod* nod)//o singura celula
{	
	CreateVertexBufferDinamic(g_pd3dDevice);
	LockVertexBuffer(nod);	
	g_pd3dDevice->SetStreamSource( 0,pVB, sizeof(Vertex));	    
    g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP ,0,3);
}

void Terrain::BuilMatrixOfVariance()
{	
	float latura=30000000;

	for(int i=0;i<16;i++)
		for(int j=0;j<16;j++)		
			MatrixOfVariance[i][j]=D3DXVECTOR3(-latura/2+j*latura/16,0,latura/2-i*latura/16);		

}