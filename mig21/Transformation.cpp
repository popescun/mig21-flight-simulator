#include "Transformation.h"

Transformation::Transformation()
{
	pStackMig=NULL;
	pStackTerrain=NULL;
	pStackCameraUp=NULL;
	pStackStabilizator=NULL;
	pStackEleron=NULL;

	D3DXCreateMatrixStack(0,&pStackMig); 
	pStackMig->LoadIdentity();

	D3DXCreateMatrixStack(0,&pStackTerrain); 
	pStackMig->LoadIdentity();

	D3DXCreateMatrixStack(0,&pStackStabilizator);			
	pStackStabilizator->LoadIdentity();

	D3DXCreateMatrixStack(0,&pStackEleron);			
	pStackEleron->LoadIdentity();

	D3DXCreateMatrixStack(0,&pStackRoti);			
	pStackRoti->LoadIdentity();	

	D3DXCreateMatrixStack(0,&pStackCameraUp); 
	pStackCameraUp->LoadIdentity();

	D3DXCreateMatrixStack(0,&pStackViewStatic);
	pStackViewStatic->LoadIdentity();

	D3DXCreateMatrixStack(0,&pStackEarth); 
	pStackEarth->LoadIdentity();

	D3DXCreateMatrixStack(0,&pStackSky); 
	pStackEarth->LoadIdentity();

	D3DXCreateMatrixStack(0,&pStackHUD); 
	pStackHUD->LoadIdentity();

	D3DXCreateMatrixStack(0,&pStackRotAxaAripa); 
	pStackRotAxaAripa->LoadIdentity();	

	D3DXMatrixIdentity(&MatMig); 

	D3DXMatrixIdentity(&MatMigInitial); 	
	MatMigInitial._41=0.0f;
	MatMigInitial._42=-145.83f;
	MatMigInitial._43=-23.22f;
	//pStackMig->LoadMatrix(&MatMigInitial);
	//pStackTerrain->LoadMatrix(&MatMigInitial);

	D3DXMatrixIdentity(&MatTerrain); 

	D3DXMatrixIdentity(&MatViewStatic); 

	D3DXMatrixIdentity(&MatIdentica); 

	MatTransformationCameraUp=MatIdentica;

	D3DXMatrixIdentity(&MatTranslatie); 			

	D3DXMatrixIdentity(&MatTextureTransformation); 	

	D3DXMatrixIdentity(&MatSkyTransformation); 			

	D3DXMatrixIdentity(&MatHUDTransformation); 	

	D3DXMatrixIdentity(&MatRotAxaAripaTransformation); 		
	
	flagInitialHUD=true;
}

void Transformation::Init()
{
	pStackMig=NULL;
	pStackTerrain=NULL;
	pStackCameraUp=NULL;
	pStackStabilizator=NULL;
	pStackEleron=NULL;

	D3DXCreateMatrixStack(0,&pStackMig); 
	pStackMig->LoadIdentity();

	D3DXCreateMatrixStack(0,&pStackTerrain); 
	pStackMig->LoadIdentity();

	D3DXCreateMatrixStack(0,&pStackStabilizator);			
	pStackStabilizator->LoadIdentity();

	D3DXCreateMatrixStack(0,&pStackEleron);			
	pStackEleron->LoadIdentity();

	D3DXCreateMatrixStack(0,&pStackRoti);			
	pStackRoti->LoadIdentity();	

	D3DXCreateMatrixStack(0,&pStackCameraUp); 
	pStackCameraUp->LoadIdentity();

	D3DXCreateMatrixStack(0,&pStackViewStatic);
	pStackViewStatic->LoadIdentity();

	D3DXCreateMatrixStack(0,&pStackEarth); 
	pStackEarth->LoadIdentity();

	D3DXCreateMatrixStack(0,&pStackSky); 
	pStackEarth->LoadIdentity();

	D3DXCreateMatrixStack(0,&pStackHUD); 
	pStackHUD->LoadIdentity();

	D3DXCreateMatrixStack(0,&pStackRotAxaAripa); 
	pStackRotAxaAripa->LoadIdentity();	

	D3DXMatrixIdentity(&MatMig); 

	D3DXMatrixIdentity(&MatMigInitial); 	
	MatMigInitial._41=0.0f;
	MatMigInitial._42=-145.83f;
	MatMigInitial._43=-23.22f;
	//pStackMig->LoadMatrix(&MatMigInitial);
	//pStackTerrain->LoadMatrix(&MatMigInitial);

	D3DXMatrixIdentity(&MatTerrain); 

	D3DXMatrixIdentity(&MatViewStatic); 

	D3DXMatrixIdentity(&MatIdentica); 

	MatTransformationCameraUp=MatIdentica;

	D3DXMatrixIdentity(&MatTranslatie); 			

	D3DXMatrixIdentity(&MatTextureTransformation); 	

	D3DXMatrixIdentity(&MatSkyTransformation); 			

	D3DXMatrixIdentity(&MatHUDTransformation); 	

	D3DXMatrixIdentity(&MatRotAxaAripaTransformation); 		
	
	flagInitialHUD=true;


}

D3DXMATRIX  Transformation::Translation(D3DXMATRIX* pInOut,//se apeleaza cu matricea identica
										 float tx,float ty,float tz)
{	   
	//translatii	
	auto result = *pInOut;
	D3DXMatrixTranslation(&result,tx,ty,tz); 		
	return result;
}

D3DXVECTOR3 Transformation::TransformationVector(D3DXMATRIX* matTransformation,
													  D3DXVECTOR3* pIntraIese)
{	 		
	D3DXVec3TransformCoord(pIntraIese,pIntraIese,matTransformation); 
	return *pIntraIese;	
}


D3DXMATRIX*  Transformation::MigTransformationStackMatrix(
											float *txx,float *tyy,float *tzz,											
											float *rtransversalx,float *rtransversaly,
											float *rtransversalz,float *unghitransversal,
											float *rlongitudinalx,float *rlongitudinaly,
											float *rlongitudinalz,float *unghilongitudinal,
											float *rverticalx,float *rverticaly,
											float *rverticalz,float *unghivertical,
											D3DXVECTOR3 *vectorAxaContact,float *unghicontact)
{			
	pStackMig->TranslateLocal(*txx,*tyy,*tzz);			
	pStackMig->RotateAxisLocal(&D3DXVECTOR3(*rtransversalx,*rtransversaly,*rtransversalz),*unghitransversal);
	pStackMig->RotateAxisLocal(&D3DXVECTOR3(*rlongitudinalx,*rlongitudinaly,*rlongitudinalz),*unghilongitudinal);	
	pStackMig->RotateAxisLocal(&D3DXVECTOR3(*rverticalx,*rverticaly,*rverticalz),*unghivertical);	
	pStackMig->RotateAxisLocal(vectorAxaContact,*unghicontact);	
  	//pStackMig->TranslateLocal(*txxT,*tyyT,*tzzT);			
	//pStackMig->TranslateLocal(-*txxG,-*tyyG,-*tzzG);				
	MatMig=*pStackMig->GetTop();		
	return pStackMig->GetTop();		
}

D3DXMATRIX*  Transformation::TerrainTransformationStackMatrix(
											float *txx,float *tyy,float *tzz,											
											float *rtransversalx,float *rtransversaly,
											float *rtransversalz,float *unghitransversal,
											float *rlongitudinalx,float *rlongitudinaly,
											float *rlongitudinalz,float *unghilongitudinal,
											float *rverticalx,float *rverticaly,
											float *rverticalz,float *unghivertical,
											D3DXVECTOR3 *vectorAxaContact,float *unghicontact)
{			
	pStackViewStatic->Translate(-*txx,-*tyy,-*tzz);		
	pStackViewStatic->RotateAxis(&D3DXVECTOR3(*rtransversalx,*rtransversaly,*rtransversalz),-*unghitransversal);
	pStackViewStatic->RotateAxis(&D3DXVECTOR3(*rlongitudinalx,*rlongitudinaly,*rlongitudinalz),-*unghilongitudinal);	
	pStackViewStatic->RotateAxis(&D3DXVECTOR3(*rverticalx,*rverticaly,*rverticalz),-*unghivertical);	
	pStackViewStatic->RotateAxis(vectorAxaContact,-*unghicontact);	
	//pStackViewStatic->Translate(*txxT,*tyyT,-*tzzT);		
	//pStackViewStatic->Translate(*txxG,*tyyG,*tzzG);			
	MatViewStatic=*pStackViewStatic->GetTop();
	
	//pStackCameraUp->Translate(-*txx,-*tyy,-*tzz);		
	pStackCameraUp->RotateAxis(&D3DXVECTOR3(*rtransversalx,*rtransversaly,*rtransversalz),-*unghitransversal);
	pStackCameraUp->RotateAxis(&D3DXVECTOR3(*rlongitudinalx,*rlongitudinaly,*rlongitudinalz),-*unghilongitudinal);
	pStackCameraUp->RotateAxis(&D3DXVECTOR3(*rverticalx,*rverticaly,*rverticalz),-*unghivertical);	
	pStackCameraUp->RotateAxis(vectorAxaContact,-*unghicontact);	
	MatTransformationCameraUp=*pStackCameraUp->GetTop();
			
	pStackTerrain->Translate(-*txx,-*tyy,-*tzz);		
	pStackTerrain->RotateAxis(&D3DXVECTOR3(*rtransversalx,*rtransversaly,*rtransversalz),-*unghitransversal);
	pStackTerrain->RotateAxis(&D3DXVECTOR3(*rlongitudinalx,*rlongitudinaly,*rlongitudinalz),-*unghilongitudinal);		
	pStackTerrain->RotateAxis(&D3DXVECTOR3(*rverticalx,*rverticaly,*rverticalz),-*unghivertical);	
	pStackTerrain->RotateAxis(vectorAxaContact,-*unghicontact);	
	//pStackTerrain->Translate(*txxT,*tyyT,-*tzzT);	
	//pStackTerrain->Translate(*txxG,*tyyG,*tzzG);			
	MatTerrain=*pStackTerrain->GetTop();					
	
	return pStackTerrain->GetTop();
}

D3DXMATRIX*  Transformation::HUDTransformationStackMatrix(float *txx,float *tyy,float *tzz,
														  float *tY,
														  float *unghiZ)
														  //float *unghitransversal,
														  //float *unghilongitudinal,
														  //float *unghivertical)
{
	pStackHUD->LoadIdentity();	
	pStackHUD->TranslateLocal(*txx,*tyy,*tzz);		
	//pStackHUD->TranslateLocal(0.0f,-*tY,0.0f);		
	pStackHUD->RotateAxisLocal(&D3DXVECTOR3(0.0f,0.0f,1.0f),*unghiZ);

	//*txx=0.0f;*tyy=0.0f;*tzz=0.0f;
		
	MatHUDTransformation=*pStackHUD->GetTop();
	
	return pStackHUD->GetTop();
}

void  Transformation::StabilizatorTransformationStackMatrix(LPDIRECT3DDEVICE8 g_pd3dDevice,
													  D3DXMATRIX* matMig,
													  float unghi,bool* uup, bool* ddown)
{	    	
	pStackStabilizator->LoadMatrix(matMig);		
	
	float CentruStabLaOrigine,hStabilizator;

	CentruStabLaOrigine=364.60f;	
	hStabilizator=145.8f;

	unghi=unghi*D3DX_PI/180.0f;
	
	//if(*ddown==true)
	//{	
		//pStackStabilizator->Translate(0.0f,-hStabilizator,0.0f);		
		pStackStabilizator->RotateAxisLocal(&D3DXVECTOR3(1.0f,0.0f,0.0f),unghi);		
		pStackStabilizator->TranslateLocal(0.0f,0.0f,CentruStabLaOrigine);		
		pStackStabilizator->TranslateLocal(0.0f,-(float)(sin(unghi)*CentruStabLaOrigine),-(float)(cos(unghi)*CentruStabLaOrigine));																
		//pStackStabilizator->TranslateLocal(0.0f,(float)(cos(unghi)*hStabilizator),-(float)(sin(unghi)*hStabilizator));														
		//pStackStabilizator->Translate(0.0f,hStabilizator,0.0f);		
	//}

	/*if(*ddown=false)			
	{	
		pStackStabilizator->RotateAxisLocal(&D3DXVECTOR3(1.0f,0.0f,0.0f),unghi);				
		pStackStabilizator->TranslateLocal(0.0f,0.0f,eleronZ);			
		pStackStabilizator->TranslateLocal(0.0f,-(float)sin(unghi)*eleronZ,(float)-cos(unghi)*eleronZ);																
	}
	
	if(*uup==true)
	{	
			pStackStabilizator->RotateAxisLocal(&D3DXVECTOR3(1.0f,0.0f,0.0f),unghi);				
			pStackStabilizator->TranslateLocal(0.0f,0.0f,eleronZ);			
			pStackStabilizator->TranslateLocal(0.0f,-(float)sin(unghi)*eleronZ,(float)-cos(unghi)*eleronZ);																
	}
	
	if(*uup==false)		
	{				
		pStackStabilizator->RotateAxisLocal(&D3DXVECTOR3(1.0f,0.0f,0.0f),unghi);		
		pStackStabilizator->TranslateLocal(0.0f,0.0f,eleronZ);		
		pStackStabilizator->TranslateLocal(0.0f,-(float)(sin(unghi)*eleronZ),-(float)(cos(unghi)*eleronZ));														
	}*/
				
	g_pd3dDevice->SetTransform( D3DTS_WORLD, pStackStabilizator->GetTop());   		    	
	//for(int i=0;i<3;i++)
	//	pStackStabilizator->Pop();	
}


void  Transformation::FlapsuriTransformationStackMatrix(LPDIRECT3DDEVICE8 g_pd3dDevice,
													  D3DXMATRIX* matMig,
													  float unghi)
{		
	pStackEleron->LoadMatrix(matMig);		

	float eleronZ,eleronY;

	eleronZ=61.3f;
	eleronY=61.3f;
	
	pStackEleron->RotateAxisLocal(&D3DXVECTOR3(1.0f,0.0f,0.0f),unghi);				
	pStackEleron->TranslateLocal(0.0f,0.0f,eleronZ-13.3f);			
	pStackEleron->TranslateLocal(0.0f,-(float)(sin(unghi)*eleronZ),-(float)(cos(unghi)*eleronZ));														
	//pppStack->TranslateLocal(0.0f,-eleronY,0.0f);																			
	
	g_pd3dDevice->SetTransform( D3DTS_WORLD, pStackEleron->GetTop());   		    	
	//for(int i=0;i<3;i++)
	//	pStackEleron->Release();
}


void  Transformation::RotiTransformationStackMatrix(LPDIRECT3DDEVICE8 g_pd3dDevice,
													D3DXMATRIX* matMig,
													D3DXVECTOR3 pozitie,
													float unghi)
{	
	//pStackRoti->LoadMatrix(matMig);				
	pStackRoti->LoadIdentity();				
	//pStackRoti->TranslateLocal(0.0f,115.84f,23.22f);				
	//pStackRoti->TranslateLocal(-126.75f,-115.84f,-23.22f);			
	pStackRoti->TranslateLocal(pozitie.x,pozitie.y,pozitie.z);			
	pStackRoti->RotateAxisLocal(&D3DXVECTOR3(1.0f,0.0f,0.0f),-unghi);				
			
	g_pd3dDevice->SetTransform( D3DTS_WORLDMATRIX(0), pStackRoti->GetTop());   		    		
}


D3DXVECTOR3* Transformation::CameraViewTransformation(D3DXMATRIX* matTransformation,
													  D3DXVECTOR3* pIntraIese)
{	 	
	D3DXVec3TransformCoord(pIntraIese,pIntraIese,matTransformation); 
	return pIntraIese;	
}

//ptr. meniul principal
D3DXMATRIX*  Transformation::EarthTransformationStackMatrix(float *tx,float *ty,float *tz,
															float *rOyx,float *rOyy,float *rOyz,
															float *unghiOy)
{	
	//pStackEarth->LoadIdentity();
	pStackEarth->TranslateLocal(*tx,*ty,*tz);			
	pStackEarth->RotateAxisLocal(&D3DXVECTOR3(*rOyx,*rOyy,*rOyz),*unghiOy);		
	
	*tx=0.0f;*ty=0.0f;*tz=0.0f;
	//*rOyx=0.0f;*rOyy=0.0f;*rOyz=0.0f;	
	//*unghiOy=0.0f;				
		
	return pStackEarth->GetTop();		
	//for(int i=0;i<2;i++)
	//	pStackEarth->Pop();	
}

//ptr. deplasarea cerului odata cu mig-ul
D3DXMATRIX*  Transformation::SkyTransformationStackMatrix(
												float *txx,float *tyy,float *tzz,//actiune tuturor fortelor
												//float *tzT,//actiune fortei de tractiune
												//float *txG,float *tyG,float *tzG,//actiune fortei de grutate
												float *rtransversalx,float *rtransversaly,
												float *rtransversalz,float *unghitransversal,
												float *rlongitudinalx,float *rlongitudinaly,
												float *rlongitudinalz,float *unghilongitudinal)
{	  					
	pStackSky->Translate(-*txx,-*tyy,-*tzz);				
	pStackSky->RotateAxis(&D3DXVECTOR3(*rtransversalx,*rtransversaly,*rtransversalz),-*unghitransversal);
	pStackSky->RotateAxis(&D3DXVECTOR3(*rlongitudinalx,*rlongitudinaly,*rlongitudinalz),-*unghilongitudinal);
	//pStackSky->Translate(0.0f,0.0f,-*tzT);			
	//pStackSky->Translate(*txG,*tyG,*tzG);				
			
	MatSkyTransformation=*pStackSky->GetTop();		

	*rtransversalx=0.0f;*rtransversaly=0.0f;*rtransversalz=0.0f;
	*rlongitudinalx=0.0f;*rlongitudinaly=0.0f;*rlongitudinalz=0.0f;	

	return pStackSky->GetTop();
	//for(int i=0;i<3;i++)
	//	pStackSky->Pop();	
}

void Transformation::PozitieNor(D3DXVECTOR3 pozitie)//se apeleaza inainte de SkyTransformationStackMatrix
{
	pStackSky->LoadIdentity();
	pStackSky->Translate(pozitie.x,pozitie.y,pozitie.z);
}