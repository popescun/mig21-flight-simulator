#include "d3d8.h"
#include "d3d8types.h"
#include "D3dx8math.h"

class Transformation{
//functii publice
public:
		Transformation();
		void Init();
		D3DXMATRIX  Translation(D3DXMATRIX* pInOut,
			                     float tx,float ty,float tz);
		D3DXMATRIX*  MigTransformationStackMatrix(
											float *txx,float *tyy,float *tzz,											
											float *rtransversalx,float *rtransversaly,
											float *rtransversalz,float *unghitransversal,
											float *rlongitudinalx,float *rlongitudinaly,
											float *rlongitudinalz,float *unghilongitudinal,
											float *rverticalx,float *rverticaly,
											float *rverticalz,float *unghivertical,
											D3DXVECTOR3 *vectorAxaContact,float *unghicontact);
		D3DXMATRIX*  TerrainTransformationStackMatrix(
											float *txx,float *tyy,float *tzz,											
											float *rtransversalx,float *rtransversaly,
											float *rtransversalz,float *unghitransversal,
											float *rlongitudinalx,float *rlongitudinaly,
											float *rlongitudinalz,float *unghilongitudinal,
											float *rverticalx,float *rverticaly,
											float *rverticalz,float *unghivertical,
											D3DXVECTOR3 *vectorAxaContact,float *unghicontact);
		D3DXMATRIX*  HUDTransformationStackMatrix(float *txx,float *tyy,float *tzz,
														  float *tY,
														  float *unghiZ);
		void  StabilizatorTransformationStackMatrix(LPDIRECT3DDEVICE8 g_pd3dDevice,
													D3DXMATRIX* matMig,
													float unghi,bool* uup, bool* doown);
		void  FlapsuriTransformationStackMatrix(LPDIRECT3DDEVICE8 g_pd3dDevice,
													  D3DXMATRIX* matMig,
													  float unghi);
		void  RotiTransformationStackMatrix(LPDIRECT3DDEVICE8 g_pd3dDevice,
													D3DXMATRIX* matMig,
													D3DXVECTOR3 pozitie,
													float unghi);
		D3DXVECTOR3* CameraViewTransformation(D3DXMATRIX* matTransformation,
											  D3DXVECTOR3* pInOut);
		D3DXVECTOR3 TransformationVector(D3DXMATRIX* matTransformation,
													  D3DXVECTOR3* pIntraIese);
		D3DXMATRIX*  EarthTransformationStackMatrix(float *tx,float *ty,float *tz,
													float *rOyx,float *rOyy,float *rOyz,
													float *unghiOy);
		D3DXMATRIX*  SkyTransformationStackMatrix(
												float *txx,float *tyy,float *tzz,//actiune tuturor fortelor
												//float *tzT,//actiune fortei de tractiune
												//float *txG,float *tyG,float *tzG,//actiune fortei de grutate
												float *rtransversalx,float *rtransversaly,
												float *rtransversalz,float *unghitransversal,
												float *rlongitudinalx,float *rlongitudinaly,
												float *rlongitudinalz,float *unghilongitudinal);
		void PozitieNor(D3DXVECTOR3 pozitie);
		
		
private:
		
		
		
//date publice
public:
		LPD3DXMATRIXSTACK pStackMig;  //Stiva de matrici pentru mig
		LPD3DXMATRIXSTACK pStackTerrain;  //Stiva de matrici pentru mig
		LPD3DXMATRIXSTACK pStackCameraUp;//Stiva de matrici pentru vectorul pUP
		LPD3DXMATRIXSTACK pStackViewStatic;//Stiva de matrici pentru vectorul pUP
		LPD3DXMATRIXSTACK pStackStabilizator;//Stiva de matrici pentru stabilizator
		LPD3DXMATRIXSTACK pStackEleron;//Stiva de matrici pentru eleron
		LPD3DXMATRIXSTACK pStackRoti;//Stiva de matrici pentru eleron
		LPD3DXMATRIXSTACK pStackEarth;//Stiva de matrici pentru eleron
		LPD3DXMATRIXSTACK pStackSky;//Stiva de matrici pentru sky
		LPD3DXMATRIXSTACK pStackHUD;//Stiva de matrici pentru sky
		LPD3DXMATRIXSTACK pStackRotAxaAripa;//Stiva de matrici pentru sky
		D3DXMATRIX MatMig; 
		D3DXMATRIX MatMigInitial; 
		D3DXMATRIX MatTerrain; 
		D3DXMATRIX MatViewStatic; 
		D3DXMATRIX MatTransformationCameraUp; 
		D3DXMATRIX MatIdentica;
		D3DXMATRIX MatTranslatie;		
		D3DXMATRIX MatTextureTransformation;
		D3DXMATRIX MatSkyTransformation;
		
		D3DXMATRIX MatRotAxaAripaTransformation;
		D3DXMATRIX MatHUDTransformation;

		bool flagInitialHUD;
		
						
private:
		
};