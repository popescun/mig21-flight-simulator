#include "d3d8.h"
#include "d3d8types.h"

class CD3D{
//functii publice
public:
		CD3D();
		HRESULT InitializeazaD3D(UINT NrPlacaGrafica);
		/*void InitializeazaEchipament(D3DDEVTYPE TipEchipament,D3DFORMAT FormatModVideo,
							    D3DFORMAT BackBufferFormat);*/
		void InitializeazaEchipament(D3DDEVTYPE TipEchipament,D3DDISPLAYMODE ModVideo,//D3DFORMAT FormatModVideo,
							  D3DFORMAT BackBufferFormat);
		bool IdentificareaAdaptoruluiGrafic();
		HRESULT CreatEchipament(HWND hWnd,DWORD ModComportament);
		/*bool VerificaTipEchipamentGrafic(UINT NrPlacaGrafic,D3DDEVTYPE tip,
								  D3DFORMAT FormatModVideo,
								  D3DFORMAT BackBufferFormat);*/
		HRESULT VerificaTipEchipamentGrafic(UINT NrPlacaGrafica,D3DDEVTYPE tip,
									D3DDISPLAYMODE ModVideo);
		bool RetineCapacitatiEchipament();//D3DDEVTYPE TipEchipament);

//potected:
		UINT RetineNumarModuriVideo(UINT NrPlacaGrafica);
		void EnumeraModuriVideo(UINT NrPlacaGrafica);
		void ModVideoCurent(UINT NrPlacaGrafica);				
		bool VerificaFormatCompatibilCuEchipament(DWORD Usage,
												  D3DRESOURCETYPE TipResursa,
												  D3DFORMAT FormatVerificat);
		
		bool VerificaCompatibilDepthStencil(D3DRESOURCETYPE TipResursa,
										  D3DFORMAT DepthStencilFormat,										  
										  D3DFORMAT BackBufferFormat );
		



//date publice
public:
		
		struct IDirect3D8  *g_pD3D;
		struct IDirect3DDevice8 *g_pD3DDevice;
		//struct IDirect3DDevice8 *g_pD3DDevice1;
		
		
public:
		
		struct Device{
			UINT NrPlacaGrafica;//ptr. care se initializeaza DirectX			
			D3DDISPLAYMODE d3dAdapterDisplayMode;//al desktop-ului
			D3DDISPLAYMODE d3dModVideoCurent;//cu care se initializeaza DirectX
			UINT NumarModuriVideo;
			D3DDISPLAYMODE ModuriVideo[200];//se poate impleta o lista simplu inlantuita 
			D3DDEVTYPE TipEchipamentCurent;//cu care se initializeaza DirectX
			D3DFORMAT FormatModVideoCurent;//cu care se initializeaza DirectX			
			D3DPRESENT_PARAMETERS Parametri;//cu care se initializeaza DirectX			
			D3DCAPS8 pCapacitati;
			D3DADAPTER_IDENTIFIER8 pIdentificator;
		} Echipament;
						
};

