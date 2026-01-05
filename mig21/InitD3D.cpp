#include "InitD3D.h"

CD3D::CD3D()
{
	g_pD3D=NULL;
	g_pD3DDevice=NULL;
	ZeroMemory(&Echipament.Parametri,sizeof(Echipament.Parametri));		
	for(int i=0;i<=200;i++)
	{
		Echipament.ModuriVideo[i].Width=0;
		Echipament.ModuriVideo[i].Height=0;
		Echipament.ModuriVideo[i].RefreshRate=0;
		Echipament.ModuriVideo[i].Format=D3DFMT_UNKNOWN;
	}
	
}

HRESULT CD3D::InitializeazaD3D(UINT NrPlacaGrafica)
{	
	if(!FAILED(g_pD3D=Direct3DCreate8( D3D_SDK_VERSION )))
	{
		EnumeraModuriVideo(NrPlacaGrafica); 
		ModVideoCurent(NrPlacaGrafica);
		return S_OK;
	}
	else
		return E_FAIL;
}

void CD3D::InitializeazaEchipament(D3DDEVTYPE TipEchipament,D3DDISPLAYMODE ModVideo,//D3DFORMAT FormatModVideo,
							  D3DFORMAT BackBufferFormat)
{
	/*VerificaTipEchipamentGrafic(Echipament.NrPlacaGrafica,TipEchipament,
								FormatModVideo,
								BackBufferFormat);*/
	VerificaTipEchipamentGrafic(Echipament.NrPlacaGrafica,TipEchipament,
									ModVideo);
	RetineCapacitatiEchipament();//TipEchipament);

}

void CD3D::EnumeraModuriVideo(UINT NrPlacaGrafica)
{	
	//D3DDISPLAYMODE *pMod;
	Echipament.NrPlacaGrafica=NrPlacaGrafica;
	RetineNumarModuriVideo(Echipament.NrPlacaGrafica);

	for(UINT mod=0;mod<=Echipament.NumarModuriVideo;mod++)
	{		
		g_pD3D->EnumAdapterModes(NrPlacaGrafica,mod,&Echipament.ModuriVideo[mod]);
		//Echipament.ModuriVideo[mod]=pMod;		
	}

}

void CD3D::ModVideoCurent(UINT NrPlacaGrafica)
{	
	g_pD3D->GetAdapterDisplayMode(NrPlacaGrafica, &Echipament.d3dAdapterDisplayMode) ;    
}

UINT CD3D::RetineNumarModuriVideo(UINT NrPlacaGrafica)
{
	return(Echipament.NumarModuriVideo=g_pD3D->GetAdapterModeCount(NrPlacaGrafica)-1);
}


HRESULT CD3D::VerificaTipEchipamentGrafic(UINT NrPlacaGrafica,D3DDEVTYPE tip,
								  D3DDISPLAYMODE ModVideo
								  //D3DFORMAT FormatModVideo,
								  //D3DFORMAT BackBufferFormat
								  )
{
		
	switch(tip)
	{
		case D3DDEVTYPE_HAL:if(!FAILED(g_pD3D->CheckDeviceType(NrPlacaGrafica,tip,
						                           ModVideo.Format,ModVideo.Format,
												   //FormatModVideo,BackBufferFormat,
												   FALSE)))
						{
							Echipament.TipEchipamentCurent=tip; 
							Echipament.NrPlacaGrafica=NrPlacaGrafica;
							Echipament.FormatModVideoCurent=ModVideo.Format;
							Echipament.Parametri.BackBufferWidth=ModVideo.Width;
							Echipament.Parametri.BackBufferHeight=ModVideo.Height;
							Echipament.Parametri.BackBufferFormat=ModVideo.Format;							
							return S_OK;
							break;
						};
						
		case D3DDEVTYPE_REF :if(!FAILED(g_pD3D->CheckDeviceType(NrPlacaGrafica,tip,
						                           ModVideo.Format,ModVideo.Format,
												   //FormatModVideo,BackBufferFormat,
												   FALSE)))
						{
							Echipament.TipEchipamentCurent=tip; 
							Echipament.NrPlacaGrafica=NrPlacaGrafica;
							Echipament.FormatModVideoCurent=ModVideo.Format;
							Echipament.Parametri.BackBufferWidth=ModVideo.Width;
							Echipament.Parametri.BackBufferHeight=ModVideo.Height;
							Echipament.Parametri.BackBufferFormat=ModVideo.Format;
							return S_OK;
							break;
						};
						
		case D3DDEVTYPE_SW :if(!FAILED(g_pD3D->CheckDeviceType(NrPlacaGrafica,tip,
						                           ModVideo.Format,ModVideo.Format,
												   //FormatModVideo,BackBufferFormat,
												   FALSE)))
						{
							Echipament.TipEchipamentCurent=tip; 
							Echipament.NrPlacaGrafica=NrPlacaGrafica;
							Echipament.FormatModVideoCurent=ModVideo.Format;
							Echipament.Parametri.BackBufferWidth=ModVideo.Width;
							Echipament.Parametri.BackBufferHeight=ModVideo.Height;
							Echipament.Parametri.BackBufferFormat=ModVideo.Format;
							return S_OK;
							break;
						};
		case D3DDEVTYPE_FORCE_DWORD:if(!FAILED(g_pD3D->CheckDeviceType(NrPlacaGrafica,tip,
						                           ModVideo.Format,ModVideo.Format,
												   //FormatModVideo,BackBufferFormat,
												   FALSE)))
						{
							Echipament.TipEchipamentCurent=tip; 
							Echipament.NrPlacaGrafica=NrPlacaGrafica;
							Echipament.FormatModVideoCurent=ModVideo.Format;
							Echipament.Parametri.BackBufferWidth=ModVideo.Width;
							Echipament.Parametri.BackBufferHeight=ModVideo.Height;
							Echipament.Parametri.BackBufferFormat=ModVideo.Format;
							return S_OK;
							break;
						};
		default:return E_FAIL;
	}
}


bool CD3D::RetineCapacitatiEchipament()//D3DDEVTYPE TipEchipament)
{
	bool rezultat;
	rezultat=false;

	if(!FAILED(g_pD3D->GetDeviceCaps(Echipament.NrPlacaGrafica,Echipament.TipEchipamentCurent,
						  &Echipament.pCapacitati)))
	rezultat=true;
	return rezultat;
}


bool CD3D::VerificaFormatCompatibilCuEchipament(DWORD Usage,
							   D3DRESOURCETYPE TipResursa,D3DFORMAT FormatVerificat)
{
	bool rezultat;
	rezultat=false;

	if(!FAILED(g_pD3D->CheckDeviceFormat(Echipament.NrPlacaGrafica,Echipament.TipEchipamentCurent,
							  Echipament.FormatModVideoCurent,							
							  Usage,
							  TipResursa,
							  FormatVerificat)))

	rezultat=true;
	return rezultat;
}

HRESULT CD3D::CreatEchipament(HWND hWnd,DWORD ModComportament)
{	
	//bool rezultat;
	//rezultat=true;

	//ZeroMemory(&Echipament.Parametri,sizeof(Echipament.Parametri));
	if(!FAILED(g_pD3D->CreateDevice(Echipament.NrPlacaGrafica,
								   Echipament.TipEchipamentCurent,
								   hWnd,
								   ModComportament,
								   &Echipament.Parametri,
								   &g_pD3DDevice)))	

		return S_OK;
	else 		
		return E_FAIL;	
}

bool CD3D::VerificaCompatibilDepthStencil(D3DRESOURCETYPE TipResursa,
										  D3DFORMAT DepthStencilFormat,										  
										  D3DFORMAT BackBufferFormat)
{
	bool rezultat;
	rezultat=false;

	VerificaFormatCompatibilCuEchipament(D3DUSAGE_DEPTHSTENCIL,TipResursa,DepthStencilFormat);
	if (!FAILED(g_pD3D->CheckDepthStencilMatch(Echipament.NrPlacaGrafica,
								   Echipament.TipEchipamentCurent,	
								   Echipament.FormatModVideoCurent,
								   BackBufferFormat,
								   DepthStencilFormat
									)))
	rezultat = true;
	return rezultat;

}

bool CD3D::IdentificareaAdaptoruluiGrafic()
{
	bool rezultat;
	rezultat=false;	

	if(!FAILED(g_pD3D->GetAdapterIdentifier(Echipament.NrPlacaGrafica,
										   D3DENUM_NO_WHQL_LEVEL,
										   &Echipament.pIdentificator
										   )))

	rezultat=true;
	return rezultat;
	
}	

