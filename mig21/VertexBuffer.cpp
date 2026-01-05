#include "VertexBuffer.h"


VertexBuffer::VertexBuffer()
{
	first=true;
}

HRESULT VertexBuffer::CreateVertexBufferDinamic(LPDIRECT3DDEVICE8 g_pd3dDevice)
{
	if(SUCCEEDED(g_pd3dDevice->CreateVertexBuffer(NrFlameFront*NrVertices*sizeof(Vertex),0,
												  D3DFVF_Vertex,
												  D3DPOOL_DEFAULT,&pVB)))
		return S_OK;
	else
		return E_FAIL;
}

HRESULT VertexBuffer::LockVertexBuffer(D3DXVECTOR3 center)
{
	int i=0,j=1;
	Vertex *pVertices;
	//ZeroMemory( &pVertices, sizeof(Vertex));
    if( FAILED(  pVB->Lock( 0, 0, (BYTE**)&pVertices, 0 ) ) )
        return E_FAIL; 
	
	else
	{
		for(j;j<=NrFlameFront;j++)
		{
			for(i;i<=j*NrVertices-1;i++)
			{
				pVertices[i].position = D3DXVECTOR3(center.x+(float)(radius*cos(i*2*D3DX_PI/(NrVertices-1))),
												center.y+(float)(radius*sin(i*2*D3DX_PI/(NrVertices-1))),
												center.z);
				pVertices[i].normal   = D3DXVECTOR3(center.x+(float)(radius*cos(i*2*D3DX_PI/(NrVertices-1))),
												center.y+(float)(radius*sin(i*2*D3DX_PI/(NrVertices-1))),
												center.z);			
				pVertices[i].tu=0.5f;
				pVertices[i].tv=0.5f;

			}
			radius-=0.6f;
			center.z-=4;
		}
		pVertices=NULL;
		pVB->Unlock();    
		return S_OK;
	}
 	
}

void VertexBuffer::DrawFlameFront(LPDIRECT3DDEVICE8 g_pd3dDevice,D3DXVECTOR3 center)
{
	if(first)
	{
		CreateVertexBufferDinamic(g_pd3dDevice);
		LockVertexBuffer(center);
		first=false;
	}
	g_pd3dDevice->SetStreamSource( 0,pVB, sizeof(Vertex));	    
    g_pd3dDevice->DrawPrimitive(D3DPT_POINTLIST ,0,NrFlameFront*NrVertices);
}




	






