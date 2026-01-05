#include "Clouds.h"
#include <string>
#include <sstream>

Clouds::Clouds()
{			
	VertSlicesNr=8;
	OrizSlicesNr=8;						
	NrVerticesTotalCloud=VertSlicesNr*OrizSlicesNr*4;
	indexVertex=0;	

	D3DXCreateMatrixStack(0,&pStackImpostorMatrix);
}
//clouds
HRESULT Clouds::CreateVertexBufferCloud(LPDIRECT3DDEVICE8 g_pd3dDevice)
{	
	//NrVerticesTotalCloud=VertSlicesNr*OrizSlicesNr*4;
	NrVerticesTotalCloud=4;
	if(SUCCEEDED(g_pd3dDevice->CreateVertexBuffer(NrVerticesTotalCloud*sizeof(Vertex),0,
												  D3DFVF_VertexCloud,
												  D3DPOOL_DEFAULT,&pVBCloud)))
		return S_OK;
	else
		return E_FAIL;

				
}

HRESULT Clouds::LockVertexBufferCloud(D3DXVECTOR3 vImpostorCenter,
									  float ImpostorHeight,
									  float ImpostorWidth)
{
	Vertex *pVertices;
    if( FAILED(pVBCloud->Lock(0,0,(BYTE**)&pVertices,0)))
        return E_FAIL; 	
	else
	{									
		//compute impostors vertices				
		//top left
		pVertices[0].position=D3DXVECTOR3(vImpostorCenter.x-ImpostorWidth/2,
										  vImpostorCenter.y+ImpostorHeight/2,
										  vImpostorCenter.z);
		pVertices[0].normal=pVertices[0].position;
		pVertices[0].tu1=0.0f;
		pVertices[0].tv1=0.0f;
		//pVertices[indexVertex].tw1=0.0f;

		//bottom left
		pVertices[1].position=D3DXVECTOR3(vImpostorCenter.x-ImpostorWidth/2,
										  vImpostorCenter.y-ImpostorHeight/2,
										  vImpostorCenter.z);
		pVertices[1].normal=pVertices[1].position;
		pVertices[1].tu1=0.0f;
		pVertices[1].tv1=1.0f;
		//pVertices[indexVertex].tw1=0.0f;

		//top right
		pVertices[2].position=D3DXVECTOR3(vImpostorCenter.x+ImpostorWidth/2,
										  vImpostorCenter.y+ImpostorHeight/2,
										  vImpostorCenter.z);
		pVertices[2].normal=pVertices[2].position;
		pVertices[2].tu1=1.0f;
		pVertices[2].tv1=0.0f;
		//pVertices[indexVertex].tw1=0.0f;

		//top right
		pVertices[3].position=D3DXVECTOR3(vImpostorCenter.x+ImpostorWidth/2,
										  vImpostorCenter.y-ImpostorHeight/2,
										  vImpostorCenter.z);
		pVertices[3].normal=pVertices[3].position;
		pVertices[3].tu1=1.0f;
		pVertices[3].tv1=1.0f;
		//pVertices[indexVertex].tw1=0.0f;
					
		pVertices=NULL;
		pVBCloud->Unlock();    
		return S_OK;
	} 	
}
//------------------------------------------------------------------------------
HRESULT Clouds::GenerateDynamicImpostors(LPDIRECT3DDEVICE8 g_pd3dDevice,
										 D3DXVECTOR3 vCameraView,
										 D3DXVECTOR3 vTopLeftBack,
										 D3DXVECTOR3 vTopLeftFront,
										 D3DXVECTOR3 vTopRightBack,
										 D3DXVECTOR3 vTopRightFront,
										 D3DXVECTOR3 vBottomLeftBack,
										 D3DXVECTOR3 vBottomLeftFront,
										 D3DXVECTOR3 vBottomRightBack,
										 D3DXVECTOR3 vBottomRightFront,
										 D3DXMATRIX* pWorldMatrix)
{
	Vertex *pVertices;
    if( FAILED(pVBCloud->Lock(0,0,(BYTE**)&pVertices,0)))
        return E_FAIL; 	
	else
	{	
		D3DXVec3TransformCoord(&vCameraView, &vCameraView, pWorldMatrix);

		//compute gizmo box center for cloud
		D3DXVECTOR3 vTopFaceCenter=D3DXVECTOR3(0.0f,0.0f,0.0f);
		vTopFaceCenter.x=vTopLeftBack.x + (vTopRightBack.x-vTopLeftBack.x)/2;
		vTopFaceCenter.y=vTopLeftBack.y;
		vTopFaceCenter.z=vTopLeftFront.z + (vTopLeftBack.z-vTopLeftFront.z)/2;

		D3DXVECTOR3 vBottomFaceCenter=D3DXVECTOR3(0.0f,0.0f,0.0f);
		vBottomFaceCenter.x=vTopFaceCenter.x;
		vBottomFaceCenter.y=vBottomLeftBack.y;
		vBottomFaceCenter.z=vTopFaceCenter.z;

		vGizmoBoxCenter.x=vTopFaceCenter.x;
		vGizmoBoxCenter.y=vBottomFaceCenter.y+(vTopFaceCenter.y-vBottomFaceCenter.y)/2;
		vGizmoBoxCenter.z=vTopFaceCenter.z;

		//compute angles between view direction and gizmo box axes			
		D3DXVec3Subtract(&vCameraViewGizmoBoxCenter,&vGizmoBoxCenter,&vCameraView); 	
		float scaleTermen,distCameraViewGizmoBoxCenter;
		distCameraViewGizmoBoxCenter=D3DXVec3Length(&vCameraViewGizmoBoxCenter); 
		D3DXVec3Normalize(&vCameraViewGizmoBoxCenter,&vCameraViewGizmoBoxCenter); 

		D3DXVECTOR3 vBackFaceCenter=D3DXVECTOR3(0.0f,0.0f,0.0f);
		vBackFaceCenter.x=vGizmoBoxCenter.x;
		vBackFaceCenter.y=vGizmoBoxCenter.y;
		vBackFaceCenter.z=vTopLeftBack.z;
		D3DXVec3Subtract(&vAxaOz,&vBackFaceCenter,&vGizmoBoxCenter); 	
		D3DXVec3Normalize(&vAxaOz,&vAxaOz); 

		D3DXVec3Subtract(&vAxaOy,&vTopFaceCenter,&vGizmoBoxCenter); 	
		D3DXVec3Normalize(&vAxaOy,&vAxaOy); 

		D3DXVECTOR3 vProiectieCameraView,vProiectieGizmoBoxCenter,
					vProiectieCameraViewGizmoBoxCenter;
		vProiectieCameraView=D3DXVECTOR3(vCameraView.x,0.0f,vCameraView.z);
		vProiectieGizmoBoxCenter=D3DXVECTOR3(vGizmoBoxCenter.x,0.0f,vGizmoBoxCenter.z);
		D3DXVec3Subtract(&vProiectieCameraViewGizmoBoxCenter,
						 &vProiectieGizmoBoxCenter,
						 &vProiectieCameraView); 	
		D3DXVec3Normalize(&vProiectieCameraViewGizmoBoxCenter,&vProiectieCameraViewGizmoBoxCenter); 
				
		unghiProiectieCameraViewImpostorPositionAxaOz = (float)(acos(D3DXVec3Dot(&vProiectieCameraViewGizmoBoxCenter,&vAxaOz)));
		unghiViewAxaOy=(float)(acos(D3DXVec3Dot(&vCameraViewGizmoBoxCenter,&vAxaOy)));

		//compute impostors planes
		/*float GizmoBoxHeight;		
		D3DXVECTOR3 v1,v2,v3,
					v4,v5,v6,
					v7,v8,v9,
					v10,v11,v12,
					v13,v14,v15,
					v16,v17,v18,
					v19,v20,v21;

		GizmoBoxHeight=vTopLeftBack.z-vTopLeftFront.z;
		
		v1=vTopLeftBack;
		v2=vBackFaceCenter;
		v3=vBottomLeftBack;
		D3DXPlaneFromPoints(&planeImpostor1,&v1,&v2,&v3); 

		v4.x=vTopLeftBack.x;
		v4.y=vTopLeftBack.y;
		v4.z=vTopLeftBack.z-GizmoBoxHeight/6;
		v5.x=vBackFaceCenter.x;
		v5.y=vBackFaceCenter.y;
		v5.z=vBackFaceCenter.z-GizmoBoxHeight/6;
		v6.x=vBottomLeftBack.x;
		v6.y=vBottomLeftBack.y;
		v6.z=vBottomLeftBack.z-GizmoBoxHeight/6;
		D3DXPlaneFromPoints(&planeImpostor2,&v4,&v5,&v6); 

		v7.x=vTopLeftBack.x;
		v7.y=vTopLeftBack.y;
		v7.z=vTopLeftBack.z-2*GizmoBoxHeight/6;
		v8.x=vBackFaceCenter.x;
		v8.y=vBackFaceCenter.y;
		v8.z=vBackFaceCenter.z-2*GizmoBoxHeight/6;
		v9.x=vBottomLeftBack.x;
		v9.y=vBottomLeftBack.y;
		v9.z=vBottomLeftBack.z-2*GizmoBoxHeight/6;
		D3DXPlaneFromPoints(&planeImpostor3,&v7,&v8,&v9); 

		v10.x=vTopLeftBack.x;
		v10.y=vTopLeftBack.y;
		v10.z=vTopLeftBack.z-3*GizmoBoxHeight/6;
		v11.x=vBackFaceCenter.x;
		v11.y=vBackFaceCenter.y;
		v11.z=vBackFaceCenter.z-3*GizmoBoxHeight/6;
		v12.x=vBottomLeftBack.x;
		v12.y=vBottomLeftBack.y;
		v12.z=vBottomLeftBack.z-3*GizmoBoxHeight/6;
		D3DXPlaneFromPoints(&planeImpostor4,&v10,&v11,&v12); 

		v13.x=vTopLeftBack.x;
		v13.y=vTopLeftBack.y;
		v13.z=vTopLeftBack.z-4*GizmoBoxHeight/6;
		v14.x=vBackFaceCenter.x;
		v14.y=vBackFaceCenter.y;
		v14.z=vBackFaceCenter.z-4*GizmoBoxHeight/6;
		v15.x=vBottomLeftBack.x;
		v15.y=vBottomLeftBack.y;
		v15.z=vBottomLeftBack.z-4*GizmoBoxHeight/6;
		D3DXPlaneFromPoints(&planeImpostor5,&v13,&v14,&v15); 

		v16.x=vTopLeftBack.x;
		v16.y=vTopLeftBack.y;
		v16.z=vTopLeftBack.z-5*GizmoBoxHeight/6;
		v17.x=vBackFaceCenter.x;
		v17.y=vBackFaceCenter.y;
		v17.z=vBackFaceCenter.z-5*GizmoBoxHeight/6;
		v18.x=vBottomLeftBack.x;
		v18.y=vBottomLeftBack.y;
		v18.z=vBottomLeftBack.z-5*GizmoBoxHeight/6;
		D3DXPlaneFromPoints(&planeImpostor6,&v16,&v17,&v18); 

		v19.x=vTopLeftBack.x;
		v19.y=vTopLeftBack.y;
		v19.z=vTopLeftBack.z-6*GizmoBoxHeight/6;
		v20.x=vBackFaceCenter.x;
		v20.y=vBackFaceCenter.y;
		v20.z=vBackFaceCenter.z-6*GizmoBoxHeight/6;
		v21.x=vBottomLeftBack.x;
		v21.y=vBottomLeftBack.y;
		v21.z=vBottomLeftBack.z-6*GizmoBoxHeight/6;
		D3DXPlaneFromPoints(&planeImpostor7,&v19,&v20,&v21); 

		//transform impostors plane
		D3DXMATRIX planeMatrix;
		LPD3DXMATRIXSTACK pStackPlaneMatrix;		

		D3DXMatrixIdentity(&planeMatrix); 
		D3DXCreateMatrixStack(0,&pStackPlaneMatrix); 
		pStackPlaneMatrix->LoadIdentity();
		//unghiProiectieCameraViewAxaOz
		if(vCameraView.x>vGizmoBoxCenter.x && vCameraView.z<vGizmoBoxCenter.z)
			pStackPlaneMatrix->RotateAxisLocal(&D3DXVECTOR3(0.0f,1.0f,0.0f),-unghiProiectieCameraViewAxaOz); 
		else
			if(vCameraView.x<vGizmoBoxCenter.x && vCameraView.z<vGizmoBoxCenter.z)
				pStackPlaneMatrix->RotateAxisLocal(&D3DXVECTOR3(0.0f,1.0f,0.0f),unghiProiectieCameraViewAxaOz); 
			else
				if(vCameraView.x>vGizmoBoxCenter.x && vCameraView.z>vGizmoBoxCenter.z)
					pStackPlaneMatrix->RotateAxisLocal(&D3DXVECTOR3(0.0f,1.0f,0.0f),D3DX_PI-unghiProiectieCameraViewAxaOz); 
				else
					if(vCameraView.x<vGizmoBoxCenter.x && vCameraView.z>vGizmoBoxCenter.z)
						pStackPlaneMatrix->RotateAxisLocal(&D3DXVECTOR3(0.0f,1.0f,0.0f),-(D3DX_PI-unghiProiectieCameraViewAxaOz)); 

		if(vCameraView.y>vGizmoBoxCenter.y && vCameraView.z<vGizmoBoxCenter.z)
			pStackPlaneMatrix->RotateAxisLocal(&D3DXVECTOR3(1.0f,0.0f,0.0f),-(unghiViewAxaOy-D3DX_PI/2)); 
		else
			if(vCameraView.y<vGizmoBoxCenter.y && vCameraView.z<vGizmoBoxCenter.z)
				pStackPlaneMatrix->RotateAxisLocal(&D3DXVECTOR3(1.0f,0.0f,0.0f),(D3DX_PI/2-unghiViewAxaOy)); 
			else
				if(vCameraView.y>vGizmoBoxCenter.y && vCameraView.z>vGizmoBoxCenter.z)
					pStackPlaneMatrix->RotateAxisLocal(&D3DXVECTOR3(1.0f,0.0f,0.0f),unghiViewAxaOy-D3DX_PI/2); 
				else
					if(vCameraView.y<vGizmoBoxCenter.y && vCameraView.z>vGizmoBoxCenter.z)
						pStackPlaneMatrix->RotateAxisLocal(&D3DXVECTOR3(1.0f,0.0f,0.0f),-(D3DX_PI/2-unghiViewAxaOy)); 
		

		//pStackPlaneMatrix->RotateAxisLocal(&D3DXVECTOR3(0.0f,1.0f,0.0f),D3DX_PI/20.0f); 
		planeMatrix=*pStackPlaneMatrix->GetTop();		
		D3DXPlaneTransform(&planeImpostor1,&planeImpostor1,&planeMatrix); 
		D3DXPlaneTransform(&planeImpostor2,&planeImpostor2,&planeMatrix); 
		D3DXPlaneTransform(&planeImpostor3,&planeImpostor3,&planeMatrix); 
		D3DXPlaneTransform(&planeImpostor4,&planeImpostor4,&planeMatrix); 
		D3DXPlaneTransform(&planeImpostor5,&planeImpostor5,&planeMatrix); 
		D3DXPlaneTransform(&planeImpostor6,&planeImpostor6,&planeMatrix); 
		D3DXPlaneTransform(&planeImpostor7,&planeImpostor7,&planeMatrix); 
		pStackPlaneMatrix->Release();
		*/

		D3DXVECTOR3 vPoint=D3DXVECTOR3(0.0f,0.0f,0.0f);
		scaleTermen=distCameraViewGizmoBoxCenter;
		scaleTermen-=10.0f;
		//D3DXVec3Scale(&vPoint,&vCameraViewGizmoBoxCenter,scaleTermen); 				
		vPoint=D3DXVECTOR3(vGizmoBoxCenter.x,vGizmoBoxCenter.y,vGizmoBoxCenter.z);
		//D3DXPlaneFromPointNormal(&planeImpostor1,&vPoint,&vCameraViewGizmoBoxCenter); 
		D3DXPlaneFromPointNormal(&planeImpostor1,&vGizmoBoxCenter,&vCameraViewGizmoBoxCenter); 
		
		
		indexVertex=0;
		indexVertexFataSus=0;
		indexVertexFataJos=0;
		indexVertexFeteLaterale=0;
		//compute intersection between impostors and gizmo box										
		float BoxWidth,BoxHeight,BoxDepth;
		
		BoxWidth=vTopRightBack.x-vTopLeftBack.x;
		BoxHeight=vTopLeftBack.z-vTopLeftFront.z;
		BoxDepth=vTopLeftBack.y-vBottomLeftBack.y;

		//intersectia cu laturile fetei de sus
		//vIntersectie = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//vIntersectie=D3DXVECTOR3((float)(vTopLeftBack.x-100.0f),(float)(vTopLeftBack.y+100.0f),(float)(vTopLeftBack.z+100.0));
		auto* vIntersectie_ptr = D3DXPlaneIntersectLine(&vIntersectie,&planeImpostor1,&vTopLeftBack,&vTopLeftFront);
		if(!vIntersectie_ptr && vIntersectie_ptr->z<=vTopLeftBack.z && vIntersectie_ptr->z>=vTopLeftFront.z)
		{
			vecIntersectie[indexVertex]=vIntersectie;
			pVertices[indexVertex].position=vIntersectie;
			pVertices[indexVertex].normal=vIntersectie;
			pVertices[indexVertex].tu1=0.0f;
			pVertices[indexVertex].tv1=(vTopLeftBack.z-vIntersectie_ptr->z)/BoxHeight;
			pVertices[indexVertex].tw1=0.0f;
			indexVertex++;			
			indexVertexFataSus++;
		}
		
		//vIntersectie = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//vIntersectie=D3DXVECTOR3((float)(vTopLeftBack.x-100.0f),(float)(vTopLeftBack.y+100.0f),(float)(vTopLeftBack.z+100.0));
		vIntersectie_ptr = D3DXPlaneIntersectLine(&vIntersectie,&planeImpostor1,&vTopLeftBack,&vTopRightBack);
		if(vIntersectie_ptr && vIntersectie_ptr->x<=vTopRightBack.x && vIntersectie_ptr->x>=vTopLeftBack.x)
		{
			vecIntersectie[indexVertex]=vIntersectie;
			pVertices[indexVertex].position=vIntersectie;
			pVertices[indexVertex].normal=vIntersectie;
			pVertices[indexVertex].tu1=(vIntersectie_ptr->x-vTopLeftBack.x)/BoxWidth;
			pVertices[indexVertex].tv1=0.0f;
			pVertices[indexVertex].tw1=0.0f;
			indexVertex++;			
			indexVertexFataSus++;
		}		

		//vIntersectie = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//vIntersectie=D3DXVECTOR3((float)(vTopLeftBack.x-100.0f),(float)(vTopLeftBack.y+100.0f),(float)(vTopLeftBack.z+100.0));
		vIntersectie_ptr = D3DXPlaneIntersectLine(&vIntersectie,&planeImpostor1,&vTopRightBack,&vTopRightFront);
		if(vIntersectie_ptr && vIntersectie_ptr->z<=vTopRightBack.z && vIntersectie_ptr->z>=vTopRightFront.z)
		{
			vecIntersectie[indexVertex]=vIntersectie;
			pVertices[indexVertex].position=vIntersectie;
			pVertices[indexVertex].normal=vIntersectie;
			pVertices[indexVertex].tu1=1.0f;
			pVertices[indexVertex].tv1=(vTopRightBack.z-vIntersectie_ptr->z)/BoxHeight;
			pVertices[indexVertex].tw1=0.0f;
			indexVertex++;			
			indexVertexFataSus++;
		}

		//vIntersectie = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//vIntersectie=D3DXVECTOR3((float)(vTopLeftBack.x-100.0f),(float)(vTopLeftBack.y+100.0f),(float)(vTopLeftBack.z+100.0));
		vIntersectie_ptr = D3DXPlaneIntersectLine(&vIntersectie,&planeImpostor1,&vTopLeftFront,&vTopRightFront);
		if(vIntersectie_ptr && vIntersectie_ptr->x<=vTopRightFront.x && vIntersectie_ptr->x>=vTopLeftFront.x)
		{
			vecIntersectie[indexVertex]=vIntersectie;
			pVertices[indexVertex].position=vIntersectie;
			pVertices[indexVertex].normal=vIntersectie;
			pVertices[indexVertex].tu1=(vIntersectie_ptr->x-vTopLeftFront.x)/BoxWidth;
			pVertices[indexVertex].tv1=1.0f;
			pVertices[indexVertex].tw1=0.0f;
			indexVertex++;			
			indexVertexFataSus++;
		}

		//intersectia cu laturile fetelor laterale				
		//vIntersectie = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//vIntersectie=D3DXVECTOR3((float)(vTopLeftBack.x-100.0f),(float)(vTopLeftBack.y+100.0f),(float)(vTopLeftBack.z+100.0));
		vIntersectie_ptr = D3DXPlaneIntersectLine(&vIntersectie,&planeImpostor1,&vTopLeftBack,&vBottomLeftBack);
		if(vIntersectie_ptr && vIntersectie_ptr->y<=vTopLeftBack.y && vIntersectie_ptr->y>=vBottomLeftBack.y)
		{
			vecIntersectie[indexVertex]=vIntersectie;
			pVertices[indexVertex].position=vIntersectie;
			pVertices[indexVertex].normal=vIntersectie;
			pVertices[indexVertex].tu1=0.0f;
			pVertices[indexVertex].tv1=0.0f;
			pVertices[indexVertex].tw1=(vTopLeftBack.y-vIntersectie_ptr->y)/BoxDepth;
			indexVertex++;			
			indexVertexFeteLaterale++;

		}

		//vIntersectie = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//vIntersectie=D3DXVECTOR3((float)(vTopLeftBack.x-100.0f),(float)(vTopLeftBack.y+100.0f),(float)(vTopLeftBack.z+100.0));
		vIntersectie_ptr = D3DXPlaneIntersectLine(&vIntersectie,&planeImpostor1,&vTopLeftFront,&vBottomLeftFront);
		if(vIntersectie_ptr && vIntersectie_ptr->y<=vTopLeftFront.y && vIntersectie_ptr->y>=vBottomLeftFront.y)
		{
			vecIntersectie[indexVertex]=vIntersectie;
			pVertices[indexVertex].position=vIntersectie;
			pVertices[indexVertex].normal=vIntersectie;
			pVertices[indexVertex].tu1=0.0f;
			pVertices[indexVertex].tv1=1.0f;
			pVertices[indexVertex].tw1=(vTopLeftFront.y-vIntersectie_ptr->y)/BoxDepth;
			indexVertex++;
			indexVertexFeteLaterale++;
		}

		//vIntersectie = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//vIntersectie=D3DXVECTOR3((float)(vTopLeftBack.x-100.0f),(float)(vTopLeftBack.y+100.0f),(float)(vTopLeftBack.z+100.0));
		vIntersectie_ptr = D3DXPlaneIntersectLine(&vIntersectie,&planeImpostor1,&vTopRightBack,&vBottomRightBack);
		if(vIntersectie_ptr && vIntersectie_ptr->y<=vTopRightBack.y && vIntersectie_ptr->y>=vBottomRightBack.y)
		{
			vecIntersectie[indexVertex]=vIntersectie;
			pVertices[indexVertex].position=vIntersectie;
			pVertices[indexVertex].normal=vIntersectie;
			pVertices[indexVertex].tu1=1.0f;
			pVertices[indexVertex].tv1=0.0f;
			pVertices[indexVertex].tw1=(vTopLeftBack.y-vIntersectie_ptr->y)/BoxDepth;
			indexVertex++;
			indexVertexFeteLaterale++;
		}

		//vIntersectie = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//vIntersectie=D3DXVECTOR3((float)(vTopLeftBack.x-100.0f),(float)(vTopLeftBack.y+100.0f),(float)(vTopLeftBack.z+100.0));
		vIntersectie_ptr = D3DXPlaneIntersectLine(&vIntersectie,&planeImpostor1,&vTopRightFront,&vBottomRightFront);
		if(vIntersectie_ptr && vIntersectie_ptr->y<=vTopRightFront.y && vIntersectie_ptr->y>=vBottomRightFront.y)
		{
			vecIntersectie[indexVertex]=vIntersectie;
			pVertices[indexVertex].position=vIntersectie;
			pVertices[indexVertex].normal=vIntersectie;
			pVertices[indexVertex].tu1=1.0f;
			pVertices[indexVertex].tv1=1.0f;
			pVertices[indexVertex].tw1=(vTopRightFront.y-vIntersectie_ptr->y)/BoxDepth;
			indexVertex++;
			indexVertexFeteLaterale++;
		}		
		
		//vIntersectie = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//intersectia cu laturile fetei de jos
		//vIntersectie=D3DXVECTOR3((float)(vTopLeftBack.x-100.0f),(float)(vTopLeftBack.y+100.0f),(float)(vTopLeftBack.z+100.0));
		vIntersectie_ptr = D3DXPlaneIntersectLine(&vIntersectie,&planeImpostor1,&vBottomLeftBack,&vBottomLeftFront);
		if(vIntersectie_ptr && vIntersectie_ptr->z<=vBottomLeftBack.z && vIntersectie_ptr->z>=vBottomLeftFront.z)
		{
			vecIntersectie[indexVertex]=vIntersectie;
			pVertices[indexVertex].position=vIntersectie;
			pVertices[indexVertex].normal=vIntersectie;
			pVertices[indexVertex].tu1=0.0f;
			pVertices[indexVertex].tv1=(vBottomLeftBack.z-vIntersectie_ptr->z)/BoxHeight;
			pVertices[indexVertex].tw1=1.0f;
			indexVertex++;
			indexVertexFataJos++;
		}

		//vIntersectie = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//vIntersectie=D3DXVECTOR3((float)(vTopLeftBack.x-100.0f),(float)(vTopLeftBack.y+100.0f),(float)(vTopLeftBack.z+100.0));
		vIntersectie_ptr = D3DXPlaneIntersectLine(&vIntersectie,&planeImpostor1,&vBottomLeftBack,&vBottomRightBack);
		if(vIntersectie_ptr && vIntersectie_ptr->x<=vBottomRightBack.x && vIntersectie_ptr->x>=vBottomLeftBack.x)
		{
			vecIntersectie[indexVertex]=vIntersectie;
			pVertices[indexVertex].position=vIntersectie;
			pVertices[indexVertex].normal=vIntersectie;
			pVertices[indexVertex].tu1=(vIntersectie_ptr->x-vBottomLeftBack.x)/BoxWidth;
			pVertices[indexVertex].tv1=0.0f;
			pVertices[indexVertex].tw1=1.0f;
			indexVertex++;
			indexVertexFataJos++;
		}				

		//vIntersectie = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//vIntersectie=D3DXVECTOR3((float)(vTopLeftBack.x-100.0f),(float)(vTopLeftBack.y+100.0f),(float)(vTopLeftBack.z+100.0));
		vIntersectie_ptr = D3DXPlaneIntersectLine(&vIntersectie,&planeImpostor1,&vBottomRightBack,&vBottomRightFront);
		if(vIntersectie_ptr && vIntersectie_ptr->z<=vBottomRightBack.z && vIntersectie_ptr->z>=vBottomRightFront.z)
		{
			vecIntersectie[indexVertex]=vIntersectie;
			pVertices[indexVertex].position=vIntersectie;
			pVertices[indexVertex].normal=vIntersectie;
			pVertices[indexVertex].tu1=1.0f;
			pVertices[indexVertex].tv1=(vBottomRightBack.z-vIntersectie_ptr->z)/BoxHeight;
			pVertices[indexVertex].tw1=1.0f;
			indexVertex++;
			indexVertexFataJos++;
		}
		
		//vIntersectie = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//vIntersectie=D3DXVECTOR3((float)(vTopLeftBack.x-100.0f),(float)(vTopLeftBack.y+100.0f),(float)(vTopLeftBack.z+100.0));
		vIntersectie_ptr = D3DXPlaneIntersectLine(&vIntersectie,&planeImpostor1,&vBottomLeftFront,&vBottomRightFront);
		if(vIntersectie_ptr && vIntersectie_ptr->x<=vBottomRightFront.x && vIntersectie_ptr->x>=vBottomLeftFront.x)
		{
			vecIntersectie[indexVertex]=vIntersectie;
			pVertices[indexVertex].position=vIntersectie;
			pVertices[indexVertex].normal=vIntersectie;
			pVertices[indexVertex].tu1=(vIntersectie_ptr->x-vBottomLeftFront.x)/BoxWidth;
			pVertices[indexVertex].tv1=1.0f;
			pVertices[indexVertex].tw1=1.0f;
			indexVertex++;
			indexVertexFataJos++;
		}				
			
		/*D3DXPlaneIntersectLine(&pVertices[1].position,&planeImpostor1,&vTopRightBack,&vTopRightFront);
		D3DXPlaneIntersectLine(&pVertices[2].position,&planeImpostor1,&vBottomLeftBack,&vBottomLeftFront);
		D3DXPlaneIntersectLine(&pVertices[3].position,&planeImpostor1,&vBottomRightBack,&vBottomRightFront);

		//pVertices[0].normal=pVertices[0].position;
		pVertices[1].normal=pVertices[1].position;
		pVertices[2].normal=pVertices[2].position;
		pVertices[3].normal=pVertices[3].position;

		//pVertices[0].tu1=0.0f;
		//pVertices[0].tv1=0.5f;
		//pVertices[0].tw1=0.0f;

		pVertices[1].tu1=1.0f;
		pVertices[1].tv1=0.5f;
		pVertices[1].tw1=0.0f;

		pVertices[2].tu1=0.0f;
		pVertices[2].tv1=0.5f;
		pVertices[2].tw1=1.0f;

		pVertices[3].tu1=1.0f;
		pVertices[3].tv1=0.5f;
		pVertices[3].tw1=1.0f;
		*/

												
			/*pVertices[0].position=D3DXVECTOR3(-2000.0f,2000.0f,5000.0f); 
			pVertices[0].normal=D3DXVECTOR3(-2000.0f,2000.0f,5000.0f); 
			//pVertices[3].color=D3DXCOLOR(1.0f,1.0f,1.0f,1.0f); 
			pVertices[0].tu1=0.0f; 
			pVertices[0].tv1=0.0f; 
			pVertices[0].tw1=0.5f;

			pVertices[1].position=D3DXVECTOR3(-2000.0f,2000.0f,1000.0f); 
			pVertices[1].normal=D3DXVECTOR3(-2000.0f,2000.0f,1000.0f); 
			//pVertices[3].color=D3DXCOLOR(1.0f,1.0f,1.0f,1.0f); 
			pVertices[1].tu1=0.0f; 
			pVertices[1].tv1=1.0f; 
			pVertices[1].tw1=0.5f; 

			pVertices[2].position=D3DXVECTOR3(2000.0f,2000.0f,5000.0f); 
			pVertices[2].normal=D3DXVECTOR3(2000.0f,2000.0f,5000.0f); 
			//pVertices[3].color=D3DXCOLOR(1.0f,1.0f,1.0f,1.0f); 
			pVertices[2].tu1=1.0f; 
			pVertices[2].tv1=0.0f; 
			pVertices[2].tw1=0.5f; 

			pVertices[3].position=D3DXVECTOR3(2000.0f,2000.0f,1000.0f); 
			pVertices[3].normal=D3DXVECTOR3(2000.0f,2000.0f,1000.0f); 
			//pVertices[3].color=D3DXCOLOR(1.0f,1.0f,1.0f,1.0f); 
			pVertices[3].tu1=1.0f; 
			pVertices[3].tv1=1.0f; 
			pVertices[3].tw1=0.5f; 


			pVertices[4].position=D3DXVECTOR3(-2000.0f,4000.0f,3000.0f); 
			pVertices[4].normal=D3DXVECTOR3(-2000.0f,4000.0f,3000.0f); 
			//pVertices[3].color=D3DXCOLOR(1.0f,1.0f,1.0f,1.0f); 
			pVertices[4].tu1=0.0f; 
			pVertices[4].tv1=0.5f; 
			pVertices[4].tw1=0.0f;

			pVertices[5].position=D3DXVECTOR3(-2000.0f,0.0f,3000.0f); 
			pVertices[5].normal=D3DXVECTOR3(-2000.0f,0.0f,3000.0f); 
			//pVertices[3].color=D3DXCOLOR(1.0f,1.0f,1.0f,1.0f); 
			pVertices[5].tu1=0.0f; 
			pVertices[5].tv1=0.5f; 
			pVertices[5].tw1=1.0f; 

			pVertices[6].position=D3DXVECTOR3(2000.0f,4000.0f,3000.0f); 
			pVertices[6].normal=D3DXVECTOR3(2000.0f,4000.0f,3000.0f); 
			//pVertices[3].color=D3DXCOLOR(1.0f,1.0f,1.0f,1.0f); 
			pVertices[6].tu1=1.0f; 
			pVertices[6].tv1=0.5f; 
			pVertices[6].tw1=0.0f; 

			pVertices[7].position=D3DXVECTOR3(2000.0f,0.0f,3000.0f); 
			pVertices[7].normal=D3DXVECTOR3(2000.0f,0.0f,3000.0f); 
			//pVertices[3].color=D3DXCOLOR(1.0f,1.0f,1.0f,1.0f); 
			pVertices[7].tu1=1.0f; 
			pVertices[7].tv1=0.5f; 
			pVertices[7].tw1=1.0f; 
			*/

		pVertices=NULL;
		pVBCloud->Unlock();    
		return S_OK;
	}
 	
}
//--------------------------------------------------------------------------
HRESULT Clouds::GenerateDynamicImpostor(LPDIRECT3DDEVICE8 g_pd3dDevice,
										 D3DXVECTOR3 vCameraView,
										 D3DXVECTOR3 vImpostorCenter,//in origine
										 D3DXVECTOR3 vImpostorPosition,
										 float ImpostorHeight,
										 float ImpostorWidth,
										 D3DXMATRIX *pWorldMatrix)
{
	Vertex *pVertices;
    if( FAILED(pVBCloud->Lock(0,0,(BYTE**)&pVertices,0)))
        return E_FAIL; 	
	else
	{
		//compute impostors vertices				
		//top left
		pVertices[0].position=D3DXVECTOR3(vImpostorCenter.x-ImpostorWidth/2,
										  vImpostorCenter.y+ImpostorHeight/2,
										  vImpostorCenter.z);
		pVertices[0].normal=pVertices[0].position;
		pVertices[0].tu1=0.0f;
		pVertices[0].tv1=0.0f;
		//pVertices[indexVertex].tw1=0.0f;

		//bottom left
		pVertices[1].position=D3DXVECTOR3(vImpostorCenter.x-ImpostorWidth/2,
										  vImpostorCenter.y-ImpostorHeight/2,
										  vImpostorCenter.z);
		pVertices[1].normal=pVertices[1].position;
		pVertices[1].tu1=0.0f;
		pVertices[1].tv1=1.0f;
		//pVertices[indexVertex].tw1=0.0f;

		//top right
		pVertices[2].position=D3DXVECTOR3(vImpostorCenter.x+ImpostorWidth/2,
										  vImpostorCenter.y+ImpostorHeight/2,
										  vImpostorCenter.z);
		pVertices[2].normal=pVertices[2].position;
		pVertices[2].tu1=1.0f;
		pVertices[2].tv1=0.0f;
		//pVertices[indexVertex].tw1=0.0f;

		//bottom right
		pVertices[3].position=D3DXVECTOR3(vImpostorCenter.x+ImpostorWidth/2,
										  vImpostorCenter.y-ImpostorHeight/2,
										  vImpostorCenter.z);
		pVertices[3].normal=pVertices[3].position;
		pVertices[3].tu1=1.0f;
		pVertices[3].tv1=1.0f;
		//pVertices[indexVertex].tw1=0.0f;
					
		pVertices=NULL;
		pVBCloud->Unlock();    		
	}

	//D3DXVec3TransformCoord(&vImpostorCenter, &vImpostorCenter, pWorldMatrix);

	//vImpCenterPosition.x=vImpostorCenter.x;
	//vImpCenterPosition.y=vImpostorCenter.y;
	//vImpCenterPosition.z=vImpostorCenter.z;

	//compute matrix transformation of impostor position
	//transform impostors plane
			
	//pStackImpostorMatrix->LoadIdentity();
	//pStackImpostorMatrix->MultMatrixLocal(pWorldMatrix);
	pStackImpostorMatrix->LoadMatrix(pWorldMatrix);

	pStackImpostorMatrix->TranslateLocal(vImpostorPosition.x, vImpostorPosition.y, vImpostorPosition.z);
	//pStackImpostorMatrix->TranslateLocal(vImpostorCenter.x, vImpostorCenter.y, vImpostorCenter.z);

	D3DXVec3TransformCoord(&vImpostorPosition, &vImpostorPosition, pWorldMatrix);
	// note that impostor center is in the origin
	//D3DXVec3TransformCoord(&vImpostorCenter, &vImpostorCenter, pWorldMatrix);

	std::stringstream ss;
	ss << "vImpostorPosition.x:" << vImpostorPosition.x << ", vImpostorPosition.y:" << vImpostorPosition.y << ", vImpostorPosition.z:" << vImpostorPosition.z << std::endl;
	OutputDebugString(ss.str().c_str());
	ss.clear();
	ss << "vImpostorCenter.x:" << vImpostorCenter.x << ", vImpostorCenter.y:" << vImpostorCenter.y << ", vImpostorCenter.z:" << vImpostorCenter.z << std::endl;
	OutputDebugString(ss.str().c_str());

	D3DXVECTOR3 vOrigin{0.0f, 0.0f, 0.0f}, vImpostorCenterToImpostorPosition;
	D3DXVec3TransformCoord(&vOrigin, &vOrigin, pWorldMatrix);
	D3DXVec3Subtract(&vImpostorCenterToImpostorPosition, &vImpostorPosition, &vImpostorCenter);
	
	ss.clear();
	ss << "vImpostorCenterToImpostorPosition.x:" << vImpostorCenterToImpostorPosition.x 
		<< ", vImpostorCenterToImpostorPosition.y:" << vImpostorCenterToImpostorPosition.y 
		<< ", vImpostorCenterToImpostorPosition.z:" << vImpostorCenterToImpostorPosition.z << std::endl;
	OutputDebugString(ss.str().c_str());

	//compute angles between view direction and impostor axes			
	vAxaOx = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	vAxaOy = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vAxaOz = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	D3DXVec3TransformNormal(&vAxaOx, &vAxaOx, pWorldMatrix);
	D3DXVec3TransformNormal(&vAxaOy, &vAxaOy, pWorldMatrix);
	D3DXVec3TransformNormal(&vAxaOz, &vAxaOz, pWorldMatrix);

	D3DXVec3Normalize(&vAxaOx, &vAxaOx);
	D3DXVec3Normalize(&vAxaOy, &vAxaOy);
	D3DXVec3Normalize(&vAxaOz, &vAxaOz);

	ss.clear();
	ss << "vAxaOz.x:" << vAxaOz.x << ", vAxaOz.y:" << vAxaOz.y  << ", vAxaOz.z:" << vAxaOz.z << std::endl;
	OutputDebugString(ss.str().c_str());
	
	auto calculateUnghi = [this, &vCameraView, &vImpostorCenterToImpostorPosition, &vImpostorPosition, &ss]() {
		D3DXVECTOR3 vProiectieCameraViewXOZ, vProiectieImpostorPositionXOZ, vProiectieCameraViewImpostorPositionXOZ;

		vProiectieCameraViewXOZ = D3DXVECTOR3(vCameraView.x, 0.0f, vCameraView.z);
		//vProiectieImpostorPositionXOZ = D3DXVECTOR3(vImpostorCenterToImpostorPosition.x, 0.0f, vImpostorCenterToImpostorPosition.z);
		vProiectieImpostorPositionXOZ = D3DXVECTOR3(vImpostorPosition.x , 0.0f, vImpostorPosition.z);
		D3DXVec3Subtract(&vProiectieCameraViewImpostorPositionXOZ, &vProiectieImpostorPositionXOZ, &vProiectieCameraViewXOZ);
		D3DXVec3Normalize(&vProiectieCameraViewImpostorPositionXOZ, &vProiectieCameraViewImpostorPositionXOZ);
		unghiProiectieCameraViewImpostorPositionAxaOz = (float)(acos(D3DXVec3Dot(&vProiectieCameraViewImpostorPositionXOZ, &vAxaOz)));


		/*D3DXVec3Subtract(&vProiectieCameraViewImpostorPositionXOZ, &vProiectieCameraViewXOZ, &vProiectieImpostorPositionXOZ);
		D3DXVec3Normalize(&vProiectieCameraViewImpostorPositionXOZ, &vProiectieCameraViewImpostorPositionXOZ);
		auto temp = (float)(acos(D3DXVec3Dot(&vProiectieCameraViewImpostorPositionXOZ, &vAxaOz)));
		unghiProiectieCameraViewImpostorPositionAxaOz = temp < unghiProiectieCameraViewImpostorPositionAxaOz ? temp : unghiProiectieCameraViewImpostorPositionAxaOz;*/
			
		ss.clear();
		ss << "vProiectieCameraViewImpostorPositionXOZ.x:" << vProiectieCameraViewImpostorPositionXOZ.x
			<< ", vProiectieCameraViewImpostorPositionXOZ.y:" << vProiectieCameraViewImpostorPositionXOZ.y
			<< ", vProiectieCameraViewImpostorPositionXOZ.z:" << vProiectieCameraViewImpostorPositionXOZ.z << std::endl;
		OutputDebugString(ss.str().c_str());
	};

	calculateUnghi();

	ss.clear();
	auto unghiProiectieCameraViewAxaOzDegree = D3DXToDegree(unghiProiectieCameraViewImpostorPositionAxaOz);
	ss << "unghiProiectieCameraViewAxaOzDegree:" << unghiProiectieCameraViewAxaOzDegree << std::endl;
	OutputDebugString(ss.str().c_str());

	/*D3DXVECTOR3 vProiectieCameraViewXOY,
				vProiectieImpostorCenterXOY,
					vProiectieCameraViewImpostorCenterXOY;
		vProiectieCameraViewXOY=D3DXVECTOR3(vCameraView.x,vCameraView.y,0.0f);
		vProiectieImpostorCenterXOY=D3DXVECTOR3(vImpostorCenter.x,vImpostorCenter.y,0.0f);
		D3DXVec3Subtract(&vProiectieCameraViewImpostorCenterXOY,
						 &vProiectieImpostorCenterXOY,
						 &vProiectieCameraViewXOY);
		D3DXVec3Normalize(&vProiectieCameraViewImpostorCenterXOY,
						  &vProiectieCameraViewImpostorCenterXOY);

		unghiProiectieCameraViewAxaOx=(float)(acos(D3DXVec3Dot(&vProiectieCameraViewImpostorCenterXOY,&vAxaOx)));
		*/

	D3DXVec3Subtract(&vCameraViewImpostorPosition, &vCameraView, &vImpostorCenterToImpostorPosition);
	D3DXVec3Normalize(&vCameraViewImpostorPosition, &vCameraViewImpostorPosition);

	unghiViewAxaOy = (float)(acos(D3DXVec3Dot(&vCameraViewImpostorPosition, &vAxaOy)));

	ss.clear();
	auto unghiViewAxaOyDegree = D3DXToDegree(unghiViewAxaOy);
	ss << "unghiViewAxaOyDegree:" << unghiViewAxaOyDegree << std::endl;
	OutputDebugString(ss.str().c_str());

	ss.clear();
	float rotationAngleOz = 0.0f;
	/*if (vCameraView.z < vImpostorPosition.z) {
		if (vCameraView.x > vImpostorPosition.x) {*/
			rotationAngleOz = unghiProiectieCameraViewImpostorPositionAxaOz;
		/*	ss << "Front Case 1" << ", rotationAngleOz:" << D3DXToDegree(rotationAngleOz) << std::endl;
		}
		else
			if (vCameraView.x < vImpostorPosition.x) {
				rotationAngleOz = unghiProiectieCameraViewImpostorPositionAxaOz;
				ss << "Front Case 2" << ", rotationAngleOz:" << D3DXToDegree(rotationAngleOz) << std::endl;
			}
	}*/
	/*else {
		if (vCameraView.x > vImpostorPosition.x) {
			rotationAngleOz =unghiProiectieCameraViewImpostorPositionAxaOz;
			ss << "Case 3" << ", rotationAngleOz:" << D3DXToDegree(rotationAngleOz) << std::endl;
		}
		else
			if (vCameraView.x < vImpostorPosition.x) {
				rotationAngleOz = unghiProiectieCameraViewImpostorPositionAxaOz;
				ss << "Case 4" << ", rotationAngleOz:" << D3DXToDegree(rotationAngleOz) << std::endl;
			}
	}*/


	pStackImpostorMatrix->RotateAxisLocal(&D3DXVECTOR3(0.0f, 1.0f, 0.0f), rotationAngleOz);
	OutputDebugString(ss.str().c_str());

	/*if(vCameraView.y > vImpostorPosition.y && vCameraView.z < vImpostorPosition.z)
		pStackImpostorMatrix->RotateAxisLocal(&D3DXVECTOR3(1.0f,0.0f,0.0f),(unghiViewAxaOy-D3DX_PI/2)); 
	else
		if(vCameraView.y < vImpostorPosition.y && vCameraView.z < vImpostorPosition.z)
			pStackImpostorMatrix->RotateAxisLocal(&D3DXVECTOR3(1.0f,0.0f,0.0f),-(D3DX_PI/2-unghiViewAxaOy)); 
		else
			if(vCameraView.y > vImpostorPosition.y && vCameraView.z > vImpostorPosition.z)
				pStackImpostorMatrix->RotateAxisLocal(&D3DXVECTOR3(1.0f,0.0f,0.0f),(unghiViewAxaOy-D3DX_PI/2)); 
			else
				if(vCameraView.y < vImpostorPosition.y && vCameraView.z > vImpostorPosition.z)
					pStackImpostorMatrix->RotateAxisLocal(&D3DXVECTOR3(1.0f,0.0f,0.0f),-(D3DX_PI/2-unghiViewAxaOy)); */
		
						
	impostorMatrix=*pStackImpostorMatrix->GetTop();
	//pStackImpostorMatrix->Release();

	return S_OK;								
}

HRESULT Clouds::GenerateDynamicImpostorNew(LPDIRECT3DDEVICE8 g_pd3dDevice,
	D3DXVECTOR3 vCameraView,
	D3DXVECTOR3 vImpostorPosition,
	float ImpostorHeight,
	float ImpostorWidth,
	D3DXMATRIX* pWorldMatrix)
{
	D3DXVECTOR3 vOrigin{ 0.0f, 0.0f, 0.0f };
	Vertex* pVertices;
	if (FAILED(pVBCloud->Lock(0, 0, (BYTE**)&pVertices, 0)))
		return E_FAIL;
	else
	{
		//compute impostors vertices				
		//top left
		pVertices[0].position = D3DXVECTOR3(vOrigin.x - ImpostorWidth / 2,
			vOrigin.y + ImpostorHeight / 2,
			vOrigin.z);
		pVertices[0].normal = pVertices[0].position;
		pVertices[0].tu1 = 0.0f;
		pVertices[0].tv1 = 0.0f;

		//bottom left
		pVertices[1].position = D3DXVECTOR3(vOrigin.x - ImpostorWidth / 2,
			vOrigin.y - ImpostorHeight / 2,
			vOrigin.z);
		pVertices[1].normal = pVertices[1].position;
		pVertices[1].tu1 = 0.0f;
		pVertices[1].tv1 = 1.0f;

		//top right
		pVertices[2].position = D3DXVECTOR3(vOrigin.x + ImpostorWidth / 2,
			vOrigin.y + ImpostorHeight / 2,
			vOrigin.z);
		pVertices[2].normal = pVertices[2].position;
		pVertices[2].tu1 = 1.0f;
		pVertices[2].tv1 = 0.0f;

		//bottom right
		pVertices[3].position = D3DXVECTOR3(vOrigin.x + ImpostorWidth / 2,
			vOrigin.y - ImpostorHeight / 2,
			vOrigin.z);
		pVertices[3].normal = pVertices[3].position;
		pVertices[3].tu1 = 1.0f;
		pVertices[3].tv1 = 1.0f;

		pVertices = NULL;
		pVBCloud->Unlock();
	}

	// move the impostor to the position
	pStackImpostorMatrix->LoadMatrix(pWorldMatrix);
	pStackImpostorMatrix->TranslateLocal(vImpostorPosition.x, vImpostorPosition.y, vImpostorPosition.z);

	// calculate view direction

		// move impostor position into 3D space
	D3DXVec3TransformCoord(&vImpostorPosition, &vImpostorPosition, pWorldMatrix);

	std::stringstream ss;
	ss << "vImpostorPosition.x:" << vImpostorPosition.x << ", vImpostorPosition.y:" << vImpostorPosition.y << ", vImpostorPosition.z:" << vImpostorPosition.z << std::endl;
	OutputDebugString(ss.str().c_str());

	cameraDirection = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVec3Subtract(&cameraDirection, &vCameraView, &vImpostorPosition);
	ss.clear();
	ss << "cameraDirection.x:" << cameraDirection.x << ", viewDirection.y:" << cameraDirection.y << ", cameraDirection.z:" << cameraDirection.z << std::endl;
	OutputDebugString(ss.str().c_str());

	D3DXVec3Normalize(&cameraDirection, &cameraDirection);

	// construct rotation matrix
	D3DXMATRIX rotationMatrix;

	// method 1
	// use negative Y to rotate the impostor in oposite direction since we move the world instead of the airplane
	/*D3DXVECTOR3 lookUp{ 0.0f, -1.0, 0.0f };
	D3DXMatrixLookAtLH(&rotationMatrix, &vImpostorPosition, &(vImpostorPosition + cameraDirection), &lookUp);*/

	// method 2
	// 2.1 calculate rotation angles
	float azimuth = atan2f(cameraDirection.x, cameraDirection.z);
	float altitude = asinf(cameraDirection.y);
	//float altitude = atan2f(cameraDirection.y, sqrt(cameraDirection.x * cameraDirection.x + cameraDirection.z * cameraDirection.z));

	ss.clear();
	ss << "azimuth:" << D3DXToDegree(azimuth) << std::endl;
	OutputDebugString(ss.str().c_str());

	ss.clear();
	ss << "altitude:" << D3DXToDegree(altitude) << std::endl;
	OutputDebugString(ss.str().c_str());

	// 2.2 create rotation matrices
	D3DXMATRIX rotationX, rotationY;
	//altitude = 0.0f; // testing without  X axe rotation 
	D3DXMatrixRotationX(&rotationX, -altitude);
	D3DXMatrixRotationY(&rotationY, azimuth); 

	// 2.3 combine rotation matrices
	D3DXMatrixMultiply(&rotationMatrix, &rotationX, &rotationY);

	// apply the rotation matrix to the impostor world matrix
	pStackImpostorMatrix->MultMatrixLocal(&rotationMatrix);

	// update current impostor matrix
	impostorMatrix = *pStackImpostorMatrix->GetTop();

	return S_OK;
}

//------------------------------------------------------------------------------
void Clouds::SetVertexCloud(LPDIRECT3DDEVICE8 g_pd3dDevice,
							D3DXVECTOR3 vImpostorCenter,
							float ImpostorHeight,
							float ImpostorWidth)
{
	if(firstCloud)
	{
		CreateVertexBufferCloud(g_pd3dDevice);
		//LockVertexBufferCloud(vImpostorCenter,
		//					  ImpostorHeight,
		//					  ImpostorWidth);
		firstCloud=false;
	}
}

void Clouds::DrawCloud(LPDIRECT3DDEVICE8 g_pd3dDevice,
					   D3DPRIMITIVETYPE PrimitiveType,
					   UINT StartVertex,UINT PtimitiveCount)
{	
	g_pd3dDevice->SetStreamSource( 0,pVBCloud, sizeof(Vertex));	
	g_pd3dDevice->SetVertexShader( D3DFVF_VertexCloud);	
    g_pd3dDevice->DrawPrimitive(PrimitiveType ,StartVertex,PtimitiveCount);
}
//-----------------------------------------------------------------------------------
void Clouds::VolumeTexture(LPDIRECT3DDEVICE8 pd3dDevice)
{
	pd3dDevice->CreateVolumeTexture( 256, 256, 256 , 1, 0, D3DFMT_A8R8G8B8,
									D3DPOOL_MANAGED, &volTexture );
	
	D3DLOCKED_BOX LockedBox;
	volTexture->LockBox( 0, &LockedBox, 0, 0 );
        
	BYTE* pSliceStart = (BYTE*)LockedBox.pBits;

	int i=0;

	for( UINT w=0; w<256; w++ )
	{
		if(w<25)
			i=0;
		else
			if(w<50)
				i=1;
			else
				if(w<75)
					i=2;
				else
					if(w<125)
						i=3;
					else
						if(w<150)
							i=4;
						else
							if(w<175)
								i=6;
							else
								if(w<200)
									i=7;
								else
									if(w<225)
										i=8;
									else
										i=9;

		D3DLOCKED_RECT LockedRect;
		pTextureCloud[i]->LockRect(0,&LockedRect,0,0);
		memcpy(pSliceStart, LockedRect.pBits, 4*256*256);
		pTextureCloud[i]->UnlockRect(0);
		
		pSliceStart += LockedBox.SlicePitch;
    } 	
	volTexture->UnlockBox( 0 );
}
//-----------------------------------------------------------------------------
void Clouds::VolumeTextureFromProfiles(LPDIRECT3DDEVICE8 pd3dDevice)
{
	pd3dDevice->CreateVolumeTexture( 256, 256, 256 , 1, 0, D3DFMT_A8R8G8B8,
									D3DPOOL_MANAGED, &volTexture );
	
	D3DLOCKED_BOX LockedBox;
	volTexture->LockBox( 0, &LockedBox, 0, 0 );
	    
	BYTE* pSliceStart = (BYTE*)LockedBox.pBits;	
	D3DLOCKED_RECT LockedRectOrizProf,LockedRectVertProf;

	//incarcam profilul orizontal al norului
	/*pSliceStart = (BYTE*)LockedBox.pBits;
	pSliceStart += LockedBox.SlicePitch*128;
	pTextureProfilOrizontalNor->LockRect(0,&LockedRect,0,0);
	memcpy(pSliceStart, LockedRect.pBits, LockedBox.SlicePitch);
	pTextureProfilOrizontalNor->UnlockRect(0);
	*/
    

	//incarcam profilul vertical al norului
	/*pSliceStart = (BYTE*)LockedBox.pBits;
	BYTE* pByteVertical;
	pTextureProfilVerticalNor->LockRect(0,&LockedRect,0,0);
	BYTE* pCurentByte=(BYTE*)LockedRect.pBits;

	pByteVertical=pSliceStart+LockedBox.RowPitch/2;
	for(UINT w=0; w<256; w++ )
	{	
		if(w==127)	
		{
			w++;
			pByteVertical+=LockedBox.SlicePitch;
		}
		//float r=0.0f,g=0.0f,b=0.0f,a=0.0f;		
		
		for(UINT v=0;v<256;v++)
		{				
			*(DWORD*)pByteVertical=*(DWORD*)pCurentByte;
			pByteVertical+=LockedBox.RowPitch;//256*4;
			pCurentByte+=4;		
		}
		//pSliceStart+= LockedBox.SlicePitch; 
	}
	pTextureProfilVerticalNor->UnlockRect(0);
	*/
		

	//cream forma norului in  functie de profiluri		
	pTextureProfilOrizontalNor->LockRect(0,&LockedRectOrizProf,0,0);	
	pTextureProfilVerticalNor->LockRect(0,&LockedRectVertProf,0,0);	
	

	pSliceStart = (BYTE*)LockedBox.pBits;
	BYTE* pSliceCurent = (BYTE*)LockedBox.pBits;
	BYTE* pCurentByte = pSliceStart;

	
	BYTE* pCurentByteVertProfile=(BYTE*)LockedRectVertProf.pBits;

	for(UINT w=0; w<256; w++ )
	{
		//pCurentByte=pSliceCurent;				
		BYTE* pCurentByteOrizProfile=(BYTE*)LockedRectOrizProf.pBits;
		
		
		for(UINT v=0;v<256;v++)
		{			
			for(UINT u=0;u<256;u++)
			{
				if((*(DWORD*)pCurentByteOrizProfile)==0xff000000 ||
				   (*(DWORD*)pCurentByteVertProfile)==0xff000000)
				   *(DWORD*)pCurentByte=0xff000000;
				else
					if(*(DWORD*)pCurentByteOrizProfile<*(DWORD*)pCurentByteVertProfile)
						*(DWORD*)pCurentByte=*(DWORD*)pCurentByteOrizProfile;					
					else						
						*(DWORD*)pCurentByte=*(DWORD*)pCurentByteVertProfile;
					
						//*(DWORD*)pCurentByte=*(DWORD*)pCurentByteVertProfile;					
				//}
					//*(DWORD*)pCurentByte=*(DWORD*)pCurentByteVertProfile;					
					//*(DWORD*)pCurentByte=0xff111111;					
				pCurentByteOrizProfile+=4;				
				pCurentByteVertProfile+=4;
				pCurentByte+=4;				
			}
			pCurentByteVertProfile-=LockedRectVertProf.Pitch;
			
		}
		pCurentByteVertProfile+=LockedRectVertProf.Pitch;
		//pSliceCurent += LockedBox.SlicePitch;
	}

	pTextureProfilOrizontalNor->UnlockRect(0);
	pTextureProfilVerticalNor->UnlockRect(0);
	
	/*for( w=0; w<256; w++ )
	{
		pCurentByte=pSliceCurent;
		BYTE* pCurentByteVertProfile=(BYTE*)pSliceStart+LockedBox.RowPitch/2;
		BYTE* pCurentByteOrizProfile=(BYTE*)pSliceStart+LockedBox.SlicePitch*128;
		for(UINT v=0;v<256;v++)
		{
			for(UINT u=0;u<256;u++)
			{
				if((*(DWORD*)pCurentByteVertProfile)>0x00000000 |//>>24 if Byte=DWORD
				  (*(DWORD*)pCurentByteOrizProfile)>0x00000000)
					//*(DWORD*)pCurentByte=*(DWORD*)pCurentByteVertProfile;
					*(DWORD*)pCurentByte=*(DWORD*)pCurentByteVertProfile;
					//*(DWORD*)pCurentByte=0x11ffffff;
				pCurentByteOrizProfile+=4;
				pCurentByte+=4;				
			}
			//pCurentByte+=LockedBox.RowPitch;
			pCurentByteVertProfile+=LockedBox.RowPitch;
			//pCurentByteOrizProfile+=LockedBox.RowPitch;
		}
		pSliceCurent += LockedBox.SlicePitch;
	}*/
	volTexture->UnlockBox( 0 );
}
//-----------------------------------------------------------------------------
void Clouds::LoadTexturesFromFile(LPDIRECT3DDEVICE8 pd3dDevice)
{	
	/*string sourceFile;	
	sourceFile=pSrcFile;
	sourceFile+="Clouds1.jpg";
	pSrcFile=sourceFile;*/	

	for(int i=0;i<10;i++)
	D3DXCreateTextureFromFileEx( pd3dDevice, 
								pSrcFile[i], 
								D3DX_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, D3DFMT_A8R8G8B8, 
								D3DPOOL_MANAGED, D3DX_FILTER_TRIANGLE|D3DX_FILTER_MIRROR, 
								D3DX_FILTER_TRIANGLE|D3DX_FILTER_MIRROR, 0, NULL, NULL, &pTextureCloud[i]);

	//D3DXCreateTextureFromFile( pd3dDevice, pSrcFile[i],&pTextureCloud[i]);		
}

//-----------------------------------------------------------------------------
void Clouds::LoadProfilesTexturesFromFile(LPDIRECT3DDEVICE8 pd3dDevice)
{	
	/*string sourceFile;	
	sourceFile=pSrcFile;
	sourceFile+="Clouds1.jpg";
	pSrcFile=sourceFile;*/	
	
	D3DXCreateTextureFromFileEx( pd3dDevice, 
								pSrcFileProfilesTextures[0], 
								D3DX_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, D3DFMT_A8R8G8B8, 
								D3DPOOL_MANAGED, D3DX_FILTER_TRIANGLE|D3DX_FILTER_MIRROR, 
								D3DX_FILTER_TRIANGLE|D3DX_FILTER_MIRROR, 0, NULL, NULL, &pTextureProfilOrizontalNor);

	D3DXCreateTextureFromFileEx( pd3dDevice, 
								pSrcFileProfilesTextures[1], 
								D3DX_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, D3DFMT_A8R8G8B8, 
								D3DPOOL_MANAGED, D3DX_FILTER_TRIANGLE|D3DX_FILTER_MIRROR, 
								D3DX_FILTER_TRIANGLE|D3DX_FILTER_MIRROR, 0, NULL, NULL, &pTextureProfilVerticalNor);

	//D3DXCreateTextureFromFile( pd3dDevice, pSrcFile[i],&pTextureCloud[i]);		
}

// Function to generate a cloud-like texture considering camera direction
LPDIRECT3DTEXTURE8 Clouds::GenerateCloudTexture(LPDIRECT3DDEVICE8 pDevice, int width, int height) {
	BYTE* pCloudData = new BYTE[width * height * 4]; // 4 bytes for RGBA

	float scale = 0.05f; // Adjust this value to change cloud density based on camera direction

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			// Modify noise based on camera direction
			float noise = (sin(cameraDirection.x * scale * x) +
				cos(cameraDirection.y * scale * y) +
				sin(cameraDirection.z * scale * (x + y))) * 0.5f + 0.5f; // Normalize to [0, 1]

			// Set color based on noise
			BYTE color = (BYTE)(noise * 255); // Convert noise to grayscale
			pCloudData[(y * width + x) * 4 + 0] = color; // R
			pCloudData[(y * width + x) * 4 + 1] = color; // G
			pCloudData[(y * width + x) * 4 + 2] = color; // B
			pCloudData[(y * width + x) * 4 + 3] = 100;    // A
		}
	}

	LPDIRECT3DTEXTURE8 pTexture;
	D3DLOCKED_RECT lockedRect;
	if (SUCCEEDED(pDevice->CreateTexture(width, height, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &pTexture))) {
		pTexture->LockRect(0, &lockedRect, NULL, 0);
		memcpy(lockedRect.pBits, pCloudData, width * height * 4);
		pTexture->UnlockRect(0);
	}

	delete[] pCloudData;
	return pTexture;
}

