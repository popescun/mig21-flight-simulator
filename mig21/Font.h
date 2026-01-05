#include "d3d8.h"
#include "d3d8types.h"
#include "D3dx8math.h"
#include "D3dx8core.h"


class Font{
//functii publice
public:
		Font();
		LPD3DXFONT CreazaFontD3D(LPDIRECT3DDEVICE8 pDevice,HFONT hFont);
		//HRESULT  Init(LPDIRECT3DDEVICE8 pDevice);
		void WriteText(LPD3DXFONT pFont,LPCSTR pString,INT Count,LPRECT pRect,DWORD Format,D3DCOLOR Color);
		void AfiseazaText(LPDIRECT3DDEVICE8 pDevice,						
						LPD3DXFONT pFont,
						LPCSTR pString,
						D3DXCOLOR Color,
						long aliniereStanga,long aliniereSus,
						long latimeText,long inaltimeText);
		void AfiseazaTextSiFlotant(LPDIRECT3DDEVICE8 pDevice,								 
								 LPD3DXFONT pFont,
								 LPCSTR pString,float Numar,int nrDigiti,
								 D3DXCOLOR Color,
								 long aliniereStanga,long aliniereSus,
								 long latimeText,long inaltimeText,
								 long corectie);
		void AfiseazaTextSiParteaIntreagaDinFlotant(LPDIRECT3DDEVICE8 pDevice,								 
												  LPD3DXFONT pFont,
												  LPCSTR pString,float Numar,int nrDigiti,
												  D3DXCOLOR Color,
												  long aliniereStanga,long aliniereSus,
												  long latimeText,long inaltimeText,
												  long corectie);
		void AfiseazaTextSiIntreg(LPDIRECT3DDEVICE8 pDevice,								 
								LPD3DXFONT pFont,
								LPCSTR pString,float Numar,int nrDigiti,
								D3DXCOLOR Color,
								long aliniereStanga,long aliniereSus,
								long latimeText,long inaltimeText,
								long corectie);
		
		
		
		
private:
		
		
		
//date publice
public:
		typedef struct _Caracter{
			HFONT hFont;
			long latimeCaracter;
			long inaltimeCaracter;			
		}Caracter;
		Caracter hFonts[20];
		LPD3DXFONT pFonts[20];						
				
public:
		
								
};