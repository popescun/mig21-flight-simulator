#include "Font.h"


Font::Font()
{
	for(int i=0;i<20;i++)
	{
		//hFonts[i]=NULL;
		pFonts[i]=NULL;
	}
}

LPD3DXFONT Font::CreazaFontD3D(LPDIRECT3DDEVICE8 pDevice,HFONT hFont)
{
	LPD3DXFONT pFont;

	int i;
	i=0;

	//while(hFonts[i]!=NULL && i<20)
	//{
		if(SUCCEEDED(D3DXCreateFont(pDevice,hFont,&pFont)))
			return pFont;
		else
			return NULL;
		//i++;
	//}
	//return S_OK;	
}


void Font::WriteText(LPD3DXFONT pFont,LPCSTR pString,INT Count,LPRECT pRect,DWORD Format,D3DCOLOR Color)
{
	//pFont->Begin();
	pFont->DrawTextA(pString,Count,pRect,Format,Color); 
	//pFont->End();	
}

void Font::AfiseazaText(LPDIRECT3DDEVICE8 pDevice,						
						LPD3DXFONT pFont,
						LPCSTR pString,
						D3DXCOLOR Color,
						long aliniereStanga,long aliniereSus,
						long latimeText,long inaltimeText)
{	
	INT Count;
	RECT Rect;
	DWORD Format;	
	
	int i;	
	long CountLowText;	
	
	//LOGFONT *pLogFont;
	//pFont->GetLogFont(pLogFont); 


	//dezactivam ceata pentru a nu afecta textul
	pDevice->SetRenderState(D3DRS_FOGENABLE,false);
								
	CountLowText=0;//init

	//---------------------------------------------------
	//text	
	Count=strlen(pString);		
	CountLowText=0;
	for(i=0;i<=Count;i++)
		if(islower(pString[i]))
			CountLowText+=(long)latimeText/2;	
	Rect.left=aliniereStanga;
	Rect.top=aliniereSus;
	Rect.right=Rect.left+Count*latimeText;//-CountLowText;
	Rect.bottom=Rect.top+inaltimeText;
	Format=DT_LEFT;
	//Color=D3DXCOLOR (1.0f,0.0f,0.0f,1.0f);
	WriteText(pFont,pString,Count,&Rect,Format,Color);
		
}

void Font::AfiseazaTextSiFlotant(LPDIRECT3DDEVICE8 pDevice,								 
								 LPD3DXFONT pFont,
								 LPCSTR pString,float Numar,int nrDigiti,
								 D3DXCOLOR Color,
								 long aliniereStanga,long aliniereSus,
								 long latimeText,long inaltimeText,
								 long corectie)
{	
	INT Count;
	RECT Rect;
	DWORD Format;
	
	//int i;
	char buffer[20],*buffer1;
	int  decimal, sign;	
	//long CountLowText;	
	
	for(int i=0;i<nrDigiti;i++)
		buffer[i]='0';
	//dezactivam ceata pentru a nu afecta textul
	pDevice->SetRenderState(D3DRS_FOGENABLE,false);
	
	//latimeText=10;
	//inaltimeText=20;
	//aliniereStanga=0;
	//aliniereSusColoanaText=0;
	//CountLowText=0;//init

	//---------------------------------------------------
	//text
	//pString="FPS[frames/s]:";
	Count=strlen(pString);		
	/*CountLowText=0;
	for(i=0;i<=Count;i++)
		if(islower(pString[i]))
			CountLowText+=(long)latimeText/2;*/
	Rect.left=aliniereStanga;
	Rect.top=aliniereSus;
	Rect.right=Rect.left+Count*latimeText+corectie;//-CountLowText;
	Rect.bottom=Rect.top+inaltimeText;
	Format=DT_LEFT;
	//Color=D3DXCOLOR (1.0f,0.0f,0.0f,1.0f);
	WriteText(pFont,pString,Count,&Rect,Format,Color);
	
	/*char buffer[4];						
	_itoa((int)FrameRate,buffer,10);	

	for(i=0;i<8;i++)
		if(buffer[i]>='0') break;*/
	
	//nrDigiti=5;	
	buffer1= _fcvt((float)Numar, nrDigiti, &decimal, &sign );	
		

	if(decimal>0)
	{
		for(int i=0;i<decimal;i++)
			buffer[i]=buffer1[i];
		buffer[decimal]='.';
		for(int i=decimal+1;i<=10;i++)
			buffer[i]=buffer1[i-1];
	}
	else
	{
		buffer[0]='0';		
		buffer[1]='.';
		int i = 2;
		for(;i<2+(-decimal);i++)
			buffer[i]='0';
		int k=i+10;
		int j=0;
		for(i;i<=k;i++)
		buffer[i]=buffer1[j++];
	}
		


	//valoare							
	if(sign!=0)
	{
		Rect.left=Rect.right;	
		//Rect.top=aliniereSus;
		Rect.right=Rect.left+latimeText;
		//Rect.bottom=Rect.top+inaltimeText;
		Format=DT_LEFT;
		//Color=D3DXCOLOR (1.0f,0.0f,0.0f,1.0f);		
		WriteText(pFont,"-",1,&Rect,Format,Color);			
		
		Rect.left=Rect.right;//Count*latimeText-CountLowText;
		if (Numar==0.0f) 
			Count=1;
		else
			Count=nrDigiti;
		//Rect.top=aliniereSusColoanaText;
		Rect.right=Rect.left+Count*latimeText;
		//Rect.bottom=Rect.top+inaltimeText;
		WriteText(pFont,buffer,Count,&Rect,Format,Color);	
	}
	else
	{
		Rect.left=Rect.right;//Count*latimeText-CountLowText;
		if (Numar==0.0f) 
			Count=1;
		else	
			Count=nrDigiti;
		//Rect.top=aliniereSus;
		Rect.right=Rect.left+Count*latimeText;
		//Rect.bottom=Rect.top+inaltimeText;
		Format=DT_LEFT;
		//Color=D3DXCOLOR (1.0f,0.0f,0.0f,1.0f);		
		WriteText(pFont,buffer,Count,&Rect,Format,Color);	
	}	
}

void Font::AfiseazaTextSiParteaIntreagaDinFlotant(LPDIRECT3DDEVICE8 pDevice,								 
												  LPD3DXFONT pFont,
												  LPCSTR pString,float Numar,int nrDigiti,
												  D3DXCOLOR Color,
												  long aliniereStanga,long aliniereSus,
												  long latimeText,long inaltimeText,
												  long corectie)
{	
	INT Count;
	RECT Rect;
	DWORD Format;
	
	//int i;
	char buffer[8],*buffer1;
	int  decimal, sign;	
	//long CountLowText;	
	
	for(int i=0;i<8;i++)
		buffer[i]='0';
	//dezactivam ceata pentru a nu afecta textul
	pDevice->SetRenderState(D3DRS_FOGENABLE,false);
	
	//latimeText=10;
	//inaltimeText=20;
	//aliniereStanga=0;
	//aliniereSusColoanaText=0;
	//CountLowText=0;//init

	//---------------------------------------------------
	//text
	//pString="FPS[frames/s]:";
	Count=strlen(pString);		
	/*CountLowText=0;
	for(i=0;i<=Count;i++)
		if(islower(pString[i]))
			CountLowText+=(long)latimeText/2;*/
	Rect.left=aliniereStanga;
	Rect.top=aliniereSus;
	Rect.right=Rect.left+Count*latimeText+corectie;//-CountLowText;
	Rect.bottom=Rect.top+inaltimeText;
	Format=DT_LEFT;
	//Color=D3DXCOLOR (1.0f,0.0f,0.0f,1.0f);
	WriteText(pFont,pString,Count,&Rect,Format,Color);
	
	/*char buffer[4];						
	_itoa((int)FrameRate,buffer,10);	

	for(i=0;i<8;i++)
		if(buffer[i]>='0') break;*/
	
	//nrDigiti=5;	
	buffer1= _fcvt((float)Numar, nrDigiti, &decimal, &sign );	
	
	if(decimal>0)
	{
		for(int i=0;i<decimal;i++)
			buffer[i]=buffer1[i];
		buffer[decimal]='.';
		for(int i=decimal+1;i<=10;i++)
			buffer[i]=buffer1[i-1];
	}
	else
	{
		buffer[0]='0';		
		buffer[1]='.';
		int i = 2;
		for(;i<2+(-decimal);i++)
			buffer[i]='0';
		int k=i+10;
		int j=0;
		for(i;i<=k;i++)
		buffer[i]=buffer1[j++];
	}		


	//valoare							
	if(sign!=0)
	{
		Rect.left=Rect.right;	
		//Rect.top=aliniereSus;
		Rect.right=Rect.left+latimeText;
		//Rect.bottom=Rect.top+inaltimeText;
		Format=DT_LEFT;
		//Color=D3DXCOLOR (1.0f,0.0f,0.0f,1.0f);		
		WriteText(pFont,"-",1,&Rect,Format,Color);			
		
		Rect.left=Rect.right;//Count*latimeText-CountLowText;
		if(decimal>0)
			Count=decimal;
		else
			Count=1;
		//Rect.top=aliniereSusColoanaText;
		Rect.right=Rect.left+Count*latimeText;
		//Rect.bottom=Rect.top+inaltimeText;
		WriteText(pFont,buffer,Count,&Rect,Format,Color);	
	}
	else
	{
		Rect.left=Rect.right;//Count*latimeText-CountLowText;		
		if(decimal>0)
			Count=decimal;
		else
			Count=1;
		//Rect.top=aliniereSus;
		Rect.right=Rect.left+Count*latimeText;
		//Rect.bottom=Rect.top+inaltimeText;
		Format=DT_LEFT;
		//Color=D3DXCOLOR (1.0f,0.0f,0.0f,1.0f);		
		WriteText(pFont,buffer,Count,&Rect,Format,Color);	
	}	

}

void Font::AfiseazaTextSiIntreg(LPDIRECT3DDEVICE8 pDevice,								 
								LPD3DXFONT pFont,
								LPCSTR pString,float Numar,int nrDigiti,
								D3DXCOLOR Color,
								long aliniereStanga,long aliniereSus,
								long latimeText,long inaltimeText,
								long corectie)
{	
	int Count;
	RECT Rect;
	DWORD Format;
	
	//int i;
	char buffer[8];	
	//long CountLowText;	
	
	for(int i=0;i<8;i++)
		buffer[i]='0';

	//dezactivam ceata pentru a nu afecta textul
	pDevice->SetRenderState(D3DRS_FOGENABLE,false);
		
	//CountLowText=0;//init

	Count=strlen(pString);		
	/*CountLowText=0;
	for(i=0;i<=Count;i++)
		if(islower(pString[i]))
			CountLowText+=(long)latimeText/2;*/
	Rect.left=aliniereStanga;
	Rect.top=aliniereSus;
	Rect.right=Rect.left+Count*latimeText+corectie;//-CountLowText;
	Rect.bottom=Rect.top+inaltimeText;
	Format=DT_LEFT;	
	WriteText(pFont,pString,Count,&Rect,Format,Color);
		
	_itoa((int)Numar,buffer,10);
	
	int i = 0;
	for(;i<4;i++)
		if(buffer[i]>='0') break;
	//i-=2;
	//k=k;
	Count=i-1;
	Rect.left=Rect.right;	
	Rect.right=Rect.right+Count*latimeText;	
	WriteText(pFont,buffer,Count,&Rect,Format,Color);
}
