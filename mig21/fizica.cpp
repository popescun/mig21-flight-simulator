#include "Fizica.h"
#include <stdlib.h>

Fizica::Fizica()
{
	D3DXCreateMatrixStack(0,&pStackOrientareAxe); 
	pStackOrientareAxe->LoadIdentity();	

	D3DXCreateMatrixStack(0,&pStackColiziuni); 
	pStackColiziuni->LoadIdentity();	

	D3DXMatrixIdentity(&MatOrientareAxe); 		
	D3DXMatrixIdentity(&MatColiziuni); 		
}

void Fizica::Init()
{	
	//NumVerticesMeshDeTestat=0;
	//FVFMeshDeTestat=0;
	//CenterBoundSphere=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//RadiusBoundSphere=0.0f;		

	for(int i=0;i<10;i++)
	{
		//tablouVectoriTestati[i].valid=false;
		tablouVectoriTestati[i].hit=false;
		tablouVectoriTestati[i].distanta=0.0f;
	}
	index=0;
	indexVecDistMin=0;
	NrDeVectori=0;

	//Freactiune.compX=0.0f;
	//Freactiune.compY=0.0f;
	//Freactiune.compZ=0.0f;
	//Freactiune2=NULL;
	//Freactiune3=NULL;

	distPanaLaContact=0.0f;
	temp1=0.0f;
	temp2=0.0f;

	FortaContact=0.0f;
	bratFortaContact=0.0f;
	unghiRotatieContact=0.0f;
	unghiRotatieDupaContact=0.0f;
	
	vectorBratFortaContact=D3DXVECTOR3(0.0f,0.0f,0.0f);
	vectorAxaRotatieContact=D3DXVECTOR3(0.0f,0.0f,0.0f);

	unghiNormalaAxaOx=0.0f;
	unghiNormalaAxaOy=0.0f;
	unghiNormalaAxaOz=0.0f;
	unghiVecVitMigNormala=0.0f;
	//
	unghiVecVitMigContactNormala=0.0f;
	unghiVecVitMigContactOx=0.0f;
	unghiVecVitMigContactOy=0.0f;
	unghiVecVitMigContactOz=0.0f;
	vecVxyzfMigLocalContact=D3DXVECTOR3(0.0f,0.0f,0.0f);	
	OpusvecVxyzfMigLocalNormalizat=D3DXVECTOR3(0.0f,0.0f,0.0f);
	VectCrossProduct=D3DXVECTOR3(0.0f,0.0f,0.0f);						
	D3DXMatrixIdentity(&MatContact); 	
	pQuatRotVitContact=NULL;
	vxfMigContact=0.0f; 
	vxiMigContact=0.0f; 
	vyfMigContact=0.0f;
	vyiMigContact=0.0f; 
	vzfMigContact=0.0f; 
	vziMigContact=0.0f; 
	vVertMigContact=0.0f;
	txMigContact=0.0f;
	tyMigContact=0.0f;
	tzMigContact=0.0f;
	unghiRotLongContact=0.0f;
	unghiRotTranContact=0.0f;
	unghiRotVertContact=0.0f;
	dupaContact=false;
	primulContact=false;
	takeOff=false;
	landing=true;
	flagRicoseuMod=false;
	//orientarea initiala a sisitemului de axe	
	origineAxeLocale=D3DXVECTOR3(0.0f,0.0f,0.0f);
	vectorVarfOxLocal=D3DXVECTOR3(1.0f,0.0f,0.0f);
	vectorVarfOyLocal=D3DXVECTOR3(0.0f,1.0f,0.0f);
	vectorVarfOzLocal=D3DXVECTOR3(0.0f,0.0f,1.0f);
	vectorOpusVarfOxLocal=D3DXVECTOR3(-1.0f,0.0f,0.0f);
	vectorOpusVarfOyLocal=D3DXVECTOR3(0.0f,-1.0f,0.0f);
	vectorOpusVarfOzLocal=D3DXVECTOR3(0.0f,0.0f,-1.0f);
	vectorOrigineVarfOxLocal=D3DXVECTOR3(0.0f,0.0f,0.0f);
	vectorOrigineVarfOyLocal=D3DXVECTOR3(0.0f,0.0f,0.0f);
	vectorOrigineVarfOzLocal=D3DXVECTOR3(0.0f,0.0f,0.0f);
	vectorOrigineOpusVarfOxLocal=D3DXVECTOR3(0.0f,0.0f,0.0f);
	vectorOrigineOpusVarfOyLocal=D3DXVECTOR3(0.0f,0.0f,0.0f);
	vectorOrigineOpusVarfOzLocal=D3DXVECTOR3(0.0f,0.0f,0.0f);
	pStackOrientareAxe->LoadIdentity();	
	D3DXMatrixIdentity(&MatOrientareAxe); 		
	hitVecVxfMigLocal=false;
	hitVecVyfMigLocal=false;
	hitVecVzfMigLocal=false;			
	distantaVxLocal=0.0f;
	distantaVyLocal=0.0f;
	distantaVzLocal=0.0f;
		

	hitInainte=false;						
	hitInapoi=false;							
	
	pStackColiziuni->LoadIdentity();
	D3DXMatrixIdentity(&MatColiziuni); 		
		
	VectorCentruRotiTest=D3DXVECTOR3(0.0f,0.71f-145.83f,0.0f-23.22f);
	VectorCentruRoti=D3DXVECTOR3(0.0f,0.71f-145.83f,0.0f-23.22f);
	VectorCentruRotiVechi=D3DXVECTOR3(0.0f,0.71f-145.83f,0.0f-23.22f);		
	VectorRoataFata=D3DXVECTOR3(0.0f,0.71f-145.83f,475.0f-23.22f);
	//VectorCentruDeGreutate=D3DXVECTOR3(-0.3f,145.6f-145.83f,0.0f-23.22f);
	VectorCentruDeGreutate=D3DXVECTOR3(0.0f,0.0f,0.0f);
	VectorCentruDeGreutateVechi=D3DXVECTOR3(0.0f,0.0f,0.0f);
	
	distContactVectorCentruRoti=0.0f;

	txMigSalvat=0.0f;	 	
	tyMigSalvat=0.0f;	
	tzMigSalvat=0.0f;
	vxfMigSalvat=0.0f;	
	vxiMigSalvat=0.0f;
	vyfMigSalvat=0.0f;
	vyiMigSalvat=0.0f;
	vzfMigSalvat=0.0f;
	vziMigSalvat=0.0f;
		
	 				 

	tpf=0.0f;// [s/frame]
	fps=0.0f;// [frames/s]
	fpsMediu=0.0f;
	fpsMediuVechi=0.0f;

	g=9.8f;// [m/s*s]	
	//G=7870.0f;//[kgf]
	m=0.0f;

	//FreactiuneSol=7870.0f;
	flagDecolare=false;
	rataDecolare=0.0f;
	flagAterizare=false;
	rataAterizare=0.0f;

	//forta de tractiune	
	powerUp=false;
	powerDown=false;
	
	TimpPartialAcceleratie=0.0f;
	TimpTotalAcceleratie=0.0f;	
	
	STOP=0.0f;
	RALANTI=170.0F;	
	MAXIM_ASL=3400.0F;
	MAXIM=4100.0F;
	FORTAJ_MINIM=5300.0F;
	FORTAJ_MAXIM=6600.0F;			
	
	//forta de greutate
	G=7740.0f;// [kgf]
	vfG=0.0f;// [m/s] 
	viG=0.0f;// [m/s] 
				
	N=0.0f;
	vfN=0.0f;// [m/s] 
	viN=0.0f;// [m/s] 
	aN=0.0f;//[m/s*s]

	//dxG=0.0f;
	//dyG=0.0f;
	//dzG=0.0f;
	alphaAtacGrade=0.0f;//[grade] 
	alphaAtacRadiani=0.0f;//[radiani] 
	alphaAtacRotatieInFileuGrade=0.0f;//[grade] 
	alphaAtacRotatieInFileuRadiani=0.0f;//[radiani] 
	timpVirareInFileuri=0.0f;
	unghiRotireInFileu=0.0f;


	tetaxRadiani=0.0f;
	tetaxGrade=0.0f;
	tetayRadiani=0.0f;
	tetayGrade=0.0f;
	tetazRadiani=0.0f;
	tetazGrade=0.0f;
	gamaRadiani=0.0f;
	gamaGrade=0.0f;	

	unghiInclinare=0.0f;
	
				
	unghiRotatieTransversalaMig=0.0f;//unghiul de bracare al mig-ului
	unghiRotatieTransversalaMigAnterior=0.0f;
	//unghiRotatieTransversalaMigMaxim=0.0f;	
	unghiRotatieLongitudinalaMig=0.0f;
	//unghiBracareStabilizatorMaxim=0.0f;//unghiul de bracare al stabilizatorului comandat maxim	
	unghiRotatieVerticalaMig=0.0f;//unghiul de  rotatie long. al mig-ului
		
	rtx=0.0f;
	rty=0.0f;
	rtz=0.0f;
	rlx=0.0f;
	rly=0.0f;
	rlz=0.0f;
	rvx=0.0f;
	rvy=0.0f;
	rvz=0.0f;

	bratCg=0.0f;
	bratCp=0.0f;
	unghiBalansForteCg=0.0f;
	unghiBalansForteCp=0.0f;
	ForteCg=0.0f;
	ForteCp=0.0f;

	unghiRotatieRoti=0.0f;
	vUnghiularaRoti=0.0f;

	kLong=true;
	unghiRotatieLongitudinalaMigPerturbatii=0.0f;
	kTran=true;
	flagStartPeturbatii = false;
		
	//vxGf=0.0f;// [m/s]
	//vxGi=0.0f;// [m/s]
	//vyGf=0.0f;// [m/s]
	//vyGi=0.0f;// [m/s]
	//vzGf=0.0f;// [m/s]
	//vzGi=0.0f;// [m/s]	
	//txG=0.0f;// [units/frame]		
	//tyG=0.0f;// [units/frame]		
	//tzG=0.0f;// [units/frame]	
	//TDeccG=0.0;
	
	//forta portanta
	Pf=0.0f;// [kgf] FortaPortantaFinala
	Pfaripa=0.0f;
	ny=0.0f;//suprasarcina
	//Pi=0.0f;// [kgf] FortaPortantaInitiala
	vfPf=0.0f;//[m/s]
	viPf=0.0f;//[m/s]
	aPf=0.0f;//[m/s*s]
	

	//S=23;//[m*m] suprafata portanta a aripii
	Saripa=23.0f;//[m*m] suprafata portanta a aripii
	Sstabilizator=3.94f;//[m*m] suprafata portanta a stabilizatorului
	Seleroane=1.18f;//[m*m] 2*0.59f
	Sampenaj=5.335f;//[m*m] suprafata portanta a stabilizatorului
	SxMig=20.083f;//[m*m] suprafata in sectiune longitudinala pe Ox = 1.2f*12.29f+5.335f
	SyMig=44.438f;//[m*m] suprafata in sectiune longitudinala pe Oy = Saripa temporar
	vs=330.0f;//[m/s]
	Cz=0.0f;	

	Pfstabilizator=0.0f;// [kgf] 	
	Czstabilizator=0.0f;//coeficientul de portanta stabilizator

	Pfeleroane=0.0f;// [kgf] 	
	Czeleroane=0.0f;

	Pfampenaj=0.0f;// [kgf] 	
	Czampenaj=0.0f;//coeficientul de portanta stabilizator

	//forte de rezistenta
	Rxf=0.0f;// [kgf] FortaDeRezistentaFinalaX
	Rxi=0.0f;// [kgf] FortaDeRezistentaInitialaX
	vfRxf=0.0f;//[m/s]
	viRxf=0.0f;//[m/s]
	aRxf=0.0f;//[m/s*s]
	Crx=0.0f;
	
	Ryf=0.0f;// [kgf] FortaDeRezistentaFinalaY
	Ryi=0.0f;// [kgf] FortaDeRezistentaInitialaY
	vfRyf=0.0f;//[m/s]
	viRyf=0.0f;//[m/s]
	aRyf=0.0f;//[m/s*s]
	Cry=0.0f;
	
	Rzf=0.0f;// [kgf] FortaDeRezistentaFinalaZ
	Rzi=0.0f;// [kgf] FortaDeRezistentaInitialaZ
	vfRzf=0.0f;//[m/s]
	viRzf=0.0f;//[m/s]
	aRzf=0.0f;//[m/s*s]
	Crz=0.0f;//se va calcula

	//Ffrecare=0.0f;//[kgf] forta de frecre cu PDA
	vfFfrecare=0.0f;//[m/s]
	viFfrecare=0.0f;//[m/s]
	aFfrecare=0.0f;//[m/s*s]
	//Cfrrepaus=0.6f;//coeficientul de frecare
	//Cfr=0.4f;

	//Ffranare=0.0f;
	vfFfranare=0.0f;//[m/s]
	viFfranare=0.0f;//[m/s]
	aFfranare=0.0f;//[m/s*s]

	Fcfx=0.0f;//[kgf]
	Fcfy=0.0f;//[kgf]
	Fcfz=0.0f;//[kgf]
	razaFcf=1000.0f;

	RezultantaX=0.0f;
	RezultantaY=0.0f;
	RezultantaZ=0.0f;
	RezultantaForte=0.0f;
	impulsMig=0.0f;
	impulsMigX=0.0f;
	impulsMigY=0.0f;
	impulsMigZ=0.0f;
	vecRezultantaForte=D3DXVECTOR3(0.0f,0.0f,0.0f);

	axMig=0.0f; //[m/s*s]acceleratia pe axa Ox a Mig-ului
	ayMig=0.0f; //[m/s*s]acceleratia pe axa Oy a Mig-ului
	azMig=0.0f; //[m/s*s]acceleratia de traiectorie, pe axa Oz a Mig-ului
	aVertMig=0.0f;//[m/s*s] AcceleratiaVerticalaMig
	aMig=0.0f;
	
	vxfMig=0.0f; //[m/s]viteza finala pe axa Ox a Mig-ului
	vxiMig=0.0f; //[m/s]viteza initiala pe axa Ox a Mig-ului
	vyfMig=0.0f; //[m/s]viteza finala pe axa Oy a Mig-ului
	vyiMig=0.0f; //[m/s]viteza initiala pe axa Oy a Mig-ului
	vzfMig=0.0f; //[m/s]viteza de traiectorie finala, pe axa Oz a Mig-ului
	vziMig=0.0f; //[m/s]viteza de traiectorie initiala, pe axa Oz a Mig-ului
	
	vecOrigine=D3DXVECTOR3(0.0f,0.0f,0.0f);
	vecVxfMig=D3DXVECTOR3(0.0f,0.0f,0.0f);
	vecVyfMig=D3DXVECTOR3(0.0f,0.0f,0.0f);
	vecVzfMig=D3DXVECTOR3(0.0f,0.0f,0.0f);

	vecVxfMigLocal=D3DXVECTOR3(0.0f,0.0f,0.0f);
	vecVyfMigLocal=D3DXVECTOR3(0.0f,0.0f,0.0f);
	vecVzfMigLocal=D3DXVECTOR3(0.0f,0.0f,0.0f);

	vecVxyfMigLocal=D3DXVECTOR3(0.0f,0.0f,0.0f);
	vecVxyzfMigLocal=D3DXVECTOR3(0.0f,0.0f,0.0f);
	vecVxyzfMigLocalVechi=D3DXVECTOR3(0.0f,0.0f,0.0f);
	vecVxyzfMigLocalNormalizat=D3DXVECTOR3(0.0f,0.0f,0.0f);
	unghiVitezeLocale=0.0f;

	unghiVecVitMigOxLocal=0.0f;
	unghiVecVitMigOyLocal=0.0f;
	unghiVecVitMigOzLocal=0.0f;

	viMig=0.0f;
	vMig=0.0f;	
	vVertMig=0.0f;//[m/s] VitezaVerticalaMig

	M=0.0f;
	altM=0.0f;//[m] altitudinea in metri
	altUnitWorld=0.0f;		
	T=0.0f;//[F]
	patm=0.0f;//[pound/feet*feet] presiunea atmosferica
	roAer=0.0f;//[Kg/m*m*m] densitatea aerului
	
	txMig=0.0f; //[m]deplasare pe axa Ox a Mig-ului
	tyMig=0.0f; //[m]deplasare pe axa Oy a Mig-ului
	tzMig=0.0f; //[m]deplasare longitudinala Mig (pe axa Oz)

	VectoriTestatiPentruColiziune();
}

void Fizica::InitForte()
{
	Tmax=6600.0f;
	Tinstant=0.0f;
	if(flagStopEngine==true)
		Tf=0.0f;// [kgf]
	G=7750.0f;// [kgf]
	FreactiuneSol=7870.0f;		
	//Ffrecare=(float)(Cfr*FreactiuneSol);	
	Ffranare=0.0f;
}

void Fizica::InitComenzi()
{
	flagJoystick=false;

	flagStartEngine=false;
	flagStopEngine=true;

	flagBracareStabilizatorUpPress=false;
	flagBracareStabilizatorDownPress=false;
	flagBracareStabilizatorUpRelease=false;
	flagBracareStabilizatorDownRelease=false;

	flagBracareEleroaneStangaPress=false;
	flagBracareEleroaneDreaptaPress=false;
	flagBracareEleroaneStangaRelease=false;
	flagBracareEleroaneDreaptaRelease=false;

	flagBracareAmpenajStangaPress=false;
	flagBracareAmpenajDreaptaPress=false;
	flagBracareAmpenajStangaRelease=false;
	flagBracareAmpenajDreaptaRelease=false;

	flagFlapsBagat=true;
	flagFlapsTakeOff=false;			
	flagFlapsLanding=false;	
	sensFlapsDown=true;

	unghiBracareStabilizator=0.0f;//unghiul de bracare al stabilizatorului comandat
	unghiBracareMinim=0.0f;
	unghiBracareMaxim=0.0f;

	rataEfortBracare=0.0f;
	unghiBracareEleroane=0.0f;
	pasEleroaneDecrease=0.0f;
	pasEleroaneIncrease=0.0f;
	timpRotatieLongitudinala=0.0f;
	unghiBracareAmpenaj=0.0f;//unghiul de bracare al stabilizatorului comandat			
}

/*void Fizica::CalculeazaDinamicaForteiDeTractiune()//F=m*a
{			
	TimpPartialAcceleratie=0.055f;	
	TimpTotalAcceleratie=1.0f;
	TimpPartialAcceleratie=TimpTotalAcceleratie/60;
	
	if(powerUp && Tinstant<Tmax)//**
	{
		if(dzT==0)//*
		{
			TDecc=0.0f;				
			contorDecczTf=0;
			contordzT=0;		
			Tinstant+=(Tmax*TimpPartialAcceleratie)/TimpTotalAcceleratie;		
			if(Tinstant>Tmax) Tinstant=Tmax;			
			vectorTf[contorAcczTf][0]=Tinstant;
			vectorTf[contorAcczTf][1]=tpf;
			contorAcczTf++;
			//if(TAcc>0.2f) // s-a renuntat la inertia maselor de rotatie
			//{	
				//aici se va calcula forta de rezistenta la inaintare
				Ti=Tf;				
				Tf=vectorTf[contorazT][0];
				//azT=vectorTf[contorazT][0]*g/m;			
				//vzTf=vzTi+azT*vectorTf[contorazT][1];
				//tzT=(float)(vzTi*vectorTf[contorazT][1]+
				//	azT*vectorTf[contorazT][1]*vectorTf[contorazT][1]*0.5)*100;
				contorazT++;
				TAcc=0;
			//}
			//else
			//	TAcc++;			
		}
		else//*
		{
			Tinstant+=(Tmax*TimpPartialAcceleratie)/TimpTotalAcceleratie;		
			contorDecczTf--;
			if(contordzT<contorDecczTf)
				//if(TDecc>0.2f)
				{				
					Ti=Tf;				
					Tf=vectorTf[contordzT][0];					
					//dzT=vectorTf[contordzT][0]*g/m;			
					//vzTf=vzTi-dzT*tpf;
					//tzT=(float)(vzTi*tpf+dzT*tpf*tpf*0.5)*100;
					contordzT++;
					TDecc=0;
				}
				//else
				//	TDecc++;											
			else
				dzT=0.0f;
		}		
	}
	else//**
		if(powerDown && Tinstant>=0.0f)//**
		{
			if(azT==0.0f)//*
			{
				TAcc=0.0f;
				contorAcczTf=0;
				contorazT=0;						
				Tinstant-=(Tmax*TimpPartialAcceleratie)/TimpTotalAcceleratie;		
				if(Tinstant<0.0f) Tinstant=0.0f;				
				vectorTf[contorDecczTf][0]=Tinstant;
				vectorTf[contorDecczTf][1]=tpf;
				contorDecczTf++;
				//if(TDecc>0.2f)
				//{				
					Ti=Tf;				
					Tf=vectorTf[contordzT][0];
					//dzT=vectorTf[contordzT][0]*g/m;			
					//vzTf=vzTi-dzT*tpf;
					//tzT=(float)(vzTi*tpf+dzT*tpf*tpf*0.5)*100;
					contordzT++;
					TDecc=0;
				//}
				//else
				//	TDecc++;				
			}
			else//*
			{
				Tinstant-=(Tmax*TimpPartialAcceleratie)/TimpTotalAcceleratie;		
				contorAcczTf--;
				if(contorazT<contorAcczTf)
					//if(TAcc>0.2f)
					{		
						Ti=Tf;				
						Tf=vectorTf[contorazT][0];
						//azT=vectorTf[contorazT][0]*g/m;			
						//vzTf=vzTi+azT*tpf;
						//tzT=(float)(vzTi*tpf+azT*tpf*tpf*0.5)*100;
						contorazT++;
						TAcc=0;
					}
					//else
					//	TAcc++;											
				else
					azT=0.0f;
			}			
		}
		else//**
		{				
			if(dzT==0)//*
				if(contorazT<contorAcczTf)
					//if(TAcc>0.2f)
					{						
						Ti=Tf;				
						Tf=vectorTf[contorazT][0];
						//azT=vectorTf[contorazT][0]*g/m;			
						//vzTf=vzTi+azT*tpf;
						//tzT=(float)(vzTi*tpf+azT*tpf*tpf*0.5)*100;
						contorazT++;
						TAcc=0;
					}
					//else
					//	TAcc++;											
			else//*
				azT=0.0f;

			if(azT==0)//*
				if(contordzT<contorDecczTf)
					//if(TDecc>0.5f)
					{					
						Ti=Tf;				
						Tf=vectorTf[contordzT][0];
						//dzT=vectorTf[contordzT][0]*g/m;			
						//vzTf=vzTi-dzT*tpf;
						//tzT=(float)(vzTi*tpf+dzT*tpf*tpf*0.5)*100;
						contordzT++;
						TDecc=0;
					}
					//else
					//	TDecc++;											
			else//*
				dzT=0.0f;
		}			
	
	//if(Tf<0.0f) Tf=0.0f;				
	//if(vzTf<0.0f) vzTf=0.0f;	
	//if(vectorTf[contordzT][0]==0.0f) vzTf=0.0f;
	//vzTi=vzTf;
}*/
//----------------------------------------------------------------------------
void Fizica::CalculeazaDinamicaForteiDeTractiune()//F=m*a
{			
	TimpPartialAcceleratie=0.055f;	
	TimpTotalAcceleratie=1.0f;
	TimpPartialAcceleratie=TimpTotalAcceleratie/30.0f;		

	float pas;
	
	STOP=0.0f;
	RALANTI=170.0F;	
	MAXIM_ASL=3400.0F;
	MAXIM=4100.0F;
	FORTAJ_MINIM=5300.0F;
	FORTAJ_MAXIM=6600.0F;

	//if(engineStart)
		//index_regim_motor++;			
	

	
		
	if(flagStartEngine==true)
	{
		pas=85.0f;
		if(powerUp)
		{
			if(Tf>0.0f && Tf<RALANTI)
				pas=85.0f;

			if(Tf>=170.0f && Tf<MAXIM_ASL)
				pas=85.0f;

			if(Tf>=3400.0f && Tf<=MAXIM)
				pas=100.0f;

			if(Tf>=4100.0f && Tf<=FORTAJ_MINIM)
				pas=100.0f;

			if(Tf>=5300.0f && Tf<=FORTAJ_MAXIM)
				pas=100.0f;
		}

		if(powerUp && Tf<FORTAJ_MAXIM)//**		
			Tf+=pas;

		

		if(powerDown)
		{
			if(Tf>0.0f && Tf<=RALANTI+85.0f)
				pas=85.0f;

			if(Tf>170.0f && Tf<=MAXIM_ASL)
				pas=85.0f;

			if(Tf>3400.0f && Tf<=MAXIM)
				pas=100.0f;

			if(Tf>4100.0f && Tf<=FORTAJ_MINIM)
				pas=100.0f;

			if(Tf>5300.0f && Tf<=FORTAJ_MAXIM)
				pas=100.0f;
		}
		
		if(powerDown && Tf>RALANTI)	
			Tf-=pas;					
	}
	
	if(flagStopEngine==true)
	{
		pas=0.0f;
		if(Tf>0.0f && Tf<=RALANTI+85.0f)
			pas=85.0f;

		if(Tf>170.0f && Tf<=MAXIM_ASL)
			pas=85.0f;

		if(Tf>3400.0f && Tf<=MAXIM)
			pas=100.0f;

		if(Tf>4100.0f && Tf<=FORTAJ_MINIM)
			pas=100.0f;

		if(Tf>5300.0f && Tf<=FORTAJ_MAXIM)
			pas=100.0f;
	
	
	//if(powerDown && Tf>170.0f)	
		Tf-=pas;			
	}
}
//----------------------------------------------------------------------------
void Fizica::CalculeazaDinamicaForteiDeFrecare()
{	
	Cfrrepaus=0.6f;//coeficientul de frecare
	Cfr=0.15f;	
	if(vMig>0.0f)
		Ffrecare=(float)(Cfr*FreactiuneSol);		
	else
		Ffrecare=(float)(Cfrrepaus*FreactiuneSol);			
}
//----------------------------------------------------------------------------
void Fizica::CalculeazaDinamicaForteiDeReactiuneTeren()
{				  						  
	temp1=(float)(G+Rzf*sin(tetazRadiani)+Ryf*sin(tetayRadiani));				  
	temp2=(float)(Pf+Tf*sin(tetazRadiani));
				 
	/*temp1=(float)(G*sin(tetayRadiani)+Ryf+Fcfy);
	temp2=(float)(Pf*cos(alphaAtacRadiani)
				  //+FreactiuneSol*sin(tetayRadiani)
				  +Ffrecare*cos(tetayRadiani)
				  +Ffranare*cos(tetayRadiani));
	*/
				 
				  	
	//FreactiuneSol=0.0f;			

	if(altM<0.2f)//distContactVectorCentruRoti<1.0f)
	{
		if(temp2<=temp1)// && FreactiuneSol>0.0f)				
			//FreactiuneSol=(float)((temp1-temp2));
			FreactiuneSol=(float)((G*sin(tetayRadiani)+Ryf+Fcfy
							      -Pf*cos(alphaAtacRadiani)
								  -Ffrecare*cos(tetayRadiani)
								  -Ffranare*cos(tetayRadiani))/sin(tetayRadiani));	
	}
	else
		//if(altM>0.1f)
			FreactiuneSol=0.0f;			
	
}
//----------------------------------------------------------------------------
void Fizica::CalculeazaDinamicaForteiDeGreutate()//F=m*a
{
	//double n;	
	G=7750.0f+120.0f;
	m=(float)(G/g);	
	G=(float)(m*g);


	/*modf(tetazGrade,&n);//partea intreaga a lui tetaGrade	
	if(n==0)
	{
		vzGf=0.0f;
		vzGi=0.0f;			
	}

	modf(tetayGrade,&n);//partea intreaga a lui tetaGrade	
	if(n==0)
	{
		vyGf=0.0f;
		vyGi=0.0f;			
	}

	modf(tetaxGrade,&n);//partea intreaga a lui tetaGrade	
	if(n==0)
	{
		vxGf=0.0f;
		vxGi=0.0f;			
	}*/
		

	/*if(TDeccG>2.0f)
	{	
		

		vGf=vGi+g*tpf;//cazul caderii libere		
		vVertMig=(float)(vGf-vzfMig*sin(tetazRadiani));
		txG=(float)(vVertMig*sin(tetaxRadiani)*tpf+g*sin(tetaxRadiani)*tpf*tpf*0.5)*100;
		tyG=(float)(vVertMig*sin(tetayRadiani)*tpf+g*sin(tetayRadiani)*tpf*tpf*0.5)*100;
		tzG=(float)(vVertMig*sin(tetazRadiani)*tpf+g*sin(tetazRadiani)*tpf*tpf*0.5)*100;
		//vxGi=vxGf;
		//vyGi=vyGf;						
		//vzGi=vzGf;						
		vGi=vGf;
		TDeccG=0;
	}
	else
		TDeccG++;*/
	
}
//----------------------------------------------------------------------------
void Fizica::CalculeazaAlpha()
{	
	alphaAtacRadiani=0.0f;
	//alphaAtacRotatieInFileuRadiani=0.0f;
	float unghiDiferenta;
	unghiDiferenta=unghiRotatieTransversalaMigAnterior-unghiRotatieTransversalaMig;
	if(flagJoystick==false)
	{
		//rataCrestereAOA si rataDescrestereAOA sunt param. specifici fiecarui avion
		if(flagBracareStabilizatorDownPress==true)
			if(alphaAtacRotatieInFileuRadiani<D3DXToRadian(1.1f*unghiBracareStabilizator))
				alphaAtacRotatieInFileuRadiani+=-unghiRotatieTransversalaMig;//D3DXToRadian(1.1f*unghiBracareStabilizator);	

		if(flagBracareStabilizatorUpPress==true)
			if(alphaAtacRotatieInFileuRadiani>D3DXToRadian(1.1f*unghiBracareStabilizator))
				alphaAtacRotatieInFileuRadiani-=unghiRotatieTransversalaMig;//D3DXToRadian(1.1f*unghiBracareStabilizator);	

		if(flagBracareStabilizatorDownRelease==true || flagBracareStabilizatorUpRelease==true)
		{
			if(alphaAtacRotatieInFileuRadiani>-0.008 && alphaAtacRotatieInFileuRadiani<0.008)
				alphaAtacRotatieInFileuRadiani=0.0f;

			if(alphaAtacRotatieInFileuRadiani>0.008f)
				alphaAtacRotatieInFileuRadiani-=0.008f;
			
			if(alphaAtacRotatieInFileuRadiani<-0.006f)
				alphaAtacRotatieInFileuRadiani+=0.008f;
			
		}
	}
	else
	{
		if(unghiBracareStabilizator>=0.0f)
		{
			if(alphaAtacRotatieInFileuRadiani<D3DXToRadian(1.1f*unghiBracareStabilizator))
				alphaAtacRotatieInFileuRadiani+=-unghiRotatieTransversalaMig;
		
			else
			{
				if(alphaAtacRotatieInFileuRadiani>0.008f)
						alphaAtacRotatieInFileuRadiani-=0.008f;
				else
					alphaAtacRotatieInFileuRadiani=0.0f;
			}
		}



		if(unghiBracareStabilizator<=0.0f)
		{
			if(alphaAtacRotatieInFileuRadiani>D3DXToRadian(1.1f*unghiBracareStabilizator))
				alphaAtacRotatieInFileuRadiani-=unghiRotatieTransversalaMig;//D3DXToRadian(1.1f*unghiBracareStabilizator);	
			else
			{
				if(alphaAtacRotatieInFileuRadiani<-0.006f)
					alphaAtacRotatieInFileuRadiani+=0.008f;
				else
					alphaAtacRotatieInFileuRadiani=0.0f;
			}
		}		
	}


	if(altM>1.1f)//distContactVectorCentruRoti>1.0f)
	{
		alphaAtacRadiani=alphaAtacRotatieInFileuRadiani;
		alphaAtacRadiani=(float)(alphaAtacRadiani+(float)(atan2(-vyfMig,vzfMig)));//+alphaAtacRotatieInFileuRadiani);						
		
		alphaAtacGrade=D3DXToDegree(alphaAtacRadiani);	
				
		/*if(D3DXToDegree(alphaAtacRadiani)>32.0f | D3DXToDegree(alphaAtacRadiani)<-32.0f)
		{
			alphaAtacGrade=32.0f;
			alphaAtacRadiani=D3DXToRadian(alphaAtacGrade);			

			txMig=50.0f;
			tyMig=50.0f;
			tzMig-=50.0f;
			unghiRotatieTransversalaMig=0.001f;
			unghiRotatieLongitudinalaMig=0.002f;
			/*if(Fcfy>0.0f)
				Fcfy-=32000.0f;		
			if(Fcfy<0.0f)*/
			//	Fcfy=0.0f;
		//}
	}
	else
	{		
		alphaAtacRadiani=tetazRadiani;
		alphaAtacGrade=tetazGrade;

	}

	//if(vMig<1.0f)
	//{		
	//	alphaAtacGrade=-7.0f;	
	//	alphaAtacRadiani=D3DXToRadian(alphaAtacGrade);				
	//}

			
	/*}
	else
	{
		alphaAtacRadiani=tetazRadiani;
		alphaAtacGrade=tetazGrade;//D3DXToDegree(alphaAtacRadiani);
		//alphaAtacRadiani=D3DXToRadian(alphaAtacGrade);
	}*/
	
}
//----------------------------------------------------------------------------
void Fizica::CalculeazaCzInfunctieDeMSiAlpha()
{	
	float ratie1,ratie2;	
	//ratie1=(float)(0.047f-0.04)/9.0f;	
	//ratie2=0.004f;
	
	/*if(M>=0.0f && vzfMig<=200.0f)	
		Cz=(float)(0.00022f*vzfMig*alphaAtacGrade);		
		//Cz=0.035
	else
		if(M<=0.7f)	
			Cz=(float)(0.040f*alphaAtacGrade);		
		else
			if(M>=0.0f && M<=1.0f)	
				Cz=(float)(0.043f*alphaAtacGrade);		
			else
				if(M<=1.1f)	
					Cz=(float)(0.045f*alphaAtacGrade);*/

	ratie1=(float)(0.087f-0.065f)/9.0f;	
	ratie2=((0.087f-0.065f)-0.035f)/5.0f;
	float rataCzTakeOff;

	if(M<0.3f)// && altM<1.0f)//takeOff==false)
	{
		rataCzTakeOff=vMig*0.05f/3000.0f;
		Cz=(float)(rataCzTakeOff)*alphaAtacGrade;
	}
	else	
	if(M<=1.0f)	
		Cz=(float)(0.03f-ratie1)*alphaAtacGrade;
	else
		if(M<=1.1f)				
			Cz=(float)(0.03f-ratie1*2.0f)*alphaAtacGrade;				
		else
			if(M<=1.2f)					
				Cz=(float)(0.03f-ratie1*3.0f)*alphaAtacGrade;				
			else
				if(M<=1.3f)						
					Cz=(float)(0.03f-ratie1*4.0f)*alphaAtacGrade;				
				else
					if(M<=1.4f)	
						Cz=(float)(0.087-ratie1*5.0f)*alphaAtacGrade;				
					else
						if(M<=1.5f)	
							Cz=(float)(0.087-ratie1*6.0f)*alphaAtacGrade;				
						else
							if(M<=1.6f)									
								Cz=(float)(0.087-ratie1*7.0f)*alphaAtacGrade;				
							else
								if(M<=1.7f)	
									Cz=(float)(0.087-ratie1*8.0f)*alphaAtacGrade;				
								else
									if(M<=1.8f)											
										Cz=(float)(0.087-ratie1*9.0f)*alphaAtacGrade;				
									//
									else
										if(M<=1.9f)		
											Cz=(float)(0.087-ratie1*9.0f-ratie2)*alphaAtacGrade;														
										else
											if(M<=2.0f)												
												Cz=(float)(0.087-ratie1*9.0f-ratie2*2.0f)*alphaAtacGrade;														
											else
												if(M<=2.1f)																								
													Cz=(float)(0.087-ratie1*9.0f-ratie2*3.0f)*alphaAtacGrade;														
												else
													if(M<=2.2f)																								
														Cz=(float)(0.087-ratie1*9.0f-ratie2*4.0f)*alphaAtacGrade;														
													else
														if(M<=2.3f)																								
															Cz=(float)(0.087-ratie1*9.0f-ratie2*5.0f)*alphaAtacGrade;																												
}
//---------------------------------------------------------------------------
void Fizica::CalculeazaM()
{
	//if(vzfMig>=1.0f)
		M=(float)(vzfMig/vs);
	//else
	//	M=0.0f;
}
//----------------------------------------------------------------------------
void Fizica::CalculeazaSuprasarcina()
{		
	ny=(float)(Pfaripa/G);
}
//----------------------------------------------------------------------------
void Fizica::CalculeazaDinamicaForteiDeRezistentaRx()
{		
	//altM acest parametru se initializeaza cu vectorFataMigY		
	//altF=altM*100.0f/30.5f;
	//CalculeazaM();
	T=(float)(15.04f-0.00649f*altM);
	patm=(float)(101.29f*exp(5.256f*log((T+273.1f)/288.08f)));
	roAer=(float)(patm/(0.2869f*(T+273.1f)));		
	Crx=10.0f;	
	if(vxfMig>0.0f)
		Rxf=(float)(roAer/2*vxfMig*vxfMig*SxMig*Crx);
	else
		Rxf=-(float)(roAer/2*vxfMig*vxfMig*SxMig*Crx);
		
}
//----------------------------------------------------------------------------
void Fizica::CalculeazaDinamicaForteiDeRezistentaRy()
{		
	//altM acest parametru se initializeaza cu vectorFataMigY		
	//altF=altM*100.0f/30.5f;
	//CalculeazaM();
	T=(float)(15.04f-0.00649f*altM);
	patm=(float)(101.29f*exp(5.256f*log((T+273.1f)/288.08f)));
	roAer=(float)(patm/(0.2869f*(T+273.1f)));		
	Cry=1.2f;			

	if(FreactiuneSol>0.0f)//temp
		Ryf=0.0f;//temp					
	else
	if(vyfMig>0.0f)
		Ryf=(float)(roAer/2*vyfMig*vyfMig*(Saripa+14.74f+Sstabilizator)*Cry);
	else
		Ryf=-(float)(roAer/2*vyfMig*vyfMig*(Saripa+14.74f+Sstabilizator)*Cry);
		
}
//----------------------------------------------------------------------------
void Fizica::CalculeazaDinamicaForteiDeRezistentaRz()//
{		
	//altM acest parametru se initializeaza cu vectorFataMigY		
	//altF=altM*100.0f/30.5f;
	//CalculeazaM();
	T=(float)(15.04f-0.00649f*altM);
	patm=(float)(101.29f*exp(5.256f*log((T+273.1f)/288.08f)));
	roAer=(float)(patm/(0.2869f*(T+273.1f)));
	//Cz se citeste dintr-o baza de date	
	//CalculeazaCz();		
	/*if(M>1)
		Crz=(float)(Cz*Cz*K)/(D3DX_PI*2.22f);//lambda=2.22f
	else*/
	float ratie=0.0f;	
	if(M<=0.3f)
	{
		//ratie=0.0001f;
		Crz=0.0066f+ratie;
	}
	else
		if(M<=0.5f)
		{
			//ratie=0.0001f;
			Crz=0.0066f+ratie;
		}
		else
			if(M<=0.8f)
			{
				//ratie=0.0001f;
				Crz=0.0066f+ratie;
			}
			else
				if(M<=1.0f)
				{
					//ratie=(0.038f-0.006f)/1.4f;
					Crz=0.012f+ratie;
				}
				else
					if(M<=1.2f)
					{
						//ratie=(0.038f-0.006f)/1.4f;
						Crz=0.02f+ratie;
					}
					else
						if(M<=1.4f)
						{
							//ratie=(0.038f-0.006f)/1.4f;					
							Crz=0.038f+ratie;
						}
			
		if(flagFlapsTakeOff )
			Crz=Crz+0.05f*Crz;

		if(flagFlapsLanding)
			Crz=Crz+0.1f*Crz;

		if(Tf>=0.0f)
			Rzf=(float)(roAer/2*vzfMig*vzfMig*(Saripa+14.74f+Sstabilizator)*Crz);
		else
			Rzf=0.0f;		
}
//----------------------------------------------------------------------------
void Fizica::CalculeazaDinamicaForteiPortante()
{	
	//M=(float)(vzfMig/vs);
	//CalculeazaM();
	//altM acest parametru se initializeaza cu vectorFataMigY			
	T=15.04f-0.00649f*altM;
	patm=(float)(101.29f*exp(5.256f*log((T+273.1f)/288.08f)));
	roAer=(float)(patm/(0.2869f*(T+273.1f)));	
	CalculeazaCzInfunctieDeMSiAlpha();
	//Cz=0.075f;

	if(flagFlapsTakeOff)
		Cz=(float)(Cz+Cz*0.16f);
	
	if(flagFlapsLanding)
		Cz=(float)(Cz+Cz*0.08f);
	
	Pf=(float)(roAer/2*vzfMig*vzfMig*(Saripa+14.74f+Sstabilizator)*Cz);//-20000.0f;				
	Pfaripa=(float)(roAer/2*vzfMig*vzfMig*(Saripa/2.0f)*Cz/2.0f);//-20000.0f;				
}
//----------------------------------------------------------------------------
void Fizica::CalculeazaDinamicaForteiCentrifuge()	
{		
	Fcfy=0.0f;
	//razaFcf=16.5f*45.0f/unghiBracareStabilizator;		
	//razaFcf=(float)(5.5f*tan(D3DXToRadian(90.0f-unghiBracareStabilizator)));						
	if(altM<0.1f)
	{
	if(flagBracareStabilizatorDownPress==true || unghiBracareStabilizator>0.0f)					
		Fcfy=RezultantaY;
	if(flagBracareStabilizatorUpPress==true || unghiBracareStabilizator<0.0f)
		Fcfy=RezultantaY;//+200.0f;			
	}
	else
	{
		if(flagBracareStabilizatorDownPress==true || unghiBracareStabilizator>0.0f)					
			Fcfy=RezultantaY+500.0f*unghiBracareStabilizator/unghiBracareMaxim;
		if(flagBracareStabilizatorUpPress==true || unghiBracareStabilizator<0.0f)
			Fcfy=RezultantaY;//+200.0f;			

	}
}
//----------------------------------------------------------------------------
void Fizica::CalculeazaVectorVitezaMig(D3DXMATRIX *pMatMig)
{	
	vecOrigine=D3DXVECTOR3(0.0f,0.0f,0.0f);
	vecVxfMig=D3DXVECTOR3(vxfMig,0.0f,0.0f);
	vecVyfMig=D3DXVECTOR3(0.0f,vyfMig,0.0f);
	vecVzfMig=D3DXVECTOR3(0.0f,0.0f,vzfMig);				
			
	//D3DXVec3TransformCoord(&vecVxyzfMigLocal,&vecVxyzfMigLocal,matColiziuni);	

	D3DXVec3TransformCoord(&vecOrigine,&vecOrigine,pMatMig);	
	D3DXVec3TransformCoord(&vecVxfMig,&vecVxfMig,pMatMig);	
	D3DXVec3TransformCoord(&vecVyfMig,&vecVyfMig,pMatMig);	
	D3DXVec3TransformCoord(&vecVzfMig,&vecVzfMig,pMatMig);		
	
	D3DXVec3Subtract(&vecVxfMigLocal,&vecVxfMig,&vecOrigine); 	
	D3DXVec3Subtract(&vecVyfMigLocal,&vecVyfMig,&vecOrigine); 
	D3DXVec3Subtract(&vecVzfMigLocal,&vecVzfMig,&vecOrigine);
	
	vecVxyzfMigLocalVechi=vecVxyzfMigLocalNormalizat;
	//D3DXVec3Normalize(&vecVxyzfMigLocalVechi,&vecVxyzfMigLocalVechi);

	D3DXVec3Add(&vecVxyfMigLocal,&vecVxfMigLocal,&vecVyfMigLocal); 		
	D3DXVec3Add(&vecVxyzfMigLocal,&vecVxyfMigLocal,&vecVzfMigLocal); 						

	if(vxfMig<=0.0f)
		impulsMigX=-(float)(D3DXVec3Length(&vecVxfMigLocal)*m);//se va calcula separat
	else
		impulsMigX=(float)(D3DXVec3Length(&vecVxfMigLocal)*m);//se va calcula separat

	if(vyfMig<=0.0f)
		impulsMigY=-(float)(D3DXVec3Length(&vecVyfMigLocal)*m);//se va calcula separat
	else
		impulsMigY=(float)(D3DXVec3Length(&vecVyfMigLocal)*m);//se va calcula separat

	if(vzfMig<=0.0f)
		impulsMigZ=-(float)(D3DXVec3Length(&vecVzfMigLocal)*m);//se va calcula separat
	else
		impulsMigZ=(float)(D3DXVec3Length(&vecVzfMigLocal)*m);//se va calcula separat	

	D3DXVec3Normalize(&vecVxfMigLocal,&vecVxfMigLocal); 
	D3DXVec3Normalize(&vecVyfMigLocal,&vecVyfMigLocal); 
	D3DXVec3Normalize(&vecVzfMigLocal,&vecVzfMigLocal); 
	D3DXVec3Normalize(&vecVxyzfMigLocalNormalizat,&vecVxyzfMigLocal);
	
	//unghiVecVitMigOxLocal=(float)(acos(D3DXVec3Dot(&vecVxyzfMigLocalNormalizat,&vecVxfMigLocal))); 
	//unghiVecVitMigOyLocal=(float)(acos(D3DXVec3Dot(&vecVxyzfMigLocalNormalizat,&vecVyfMigLocal))); 
	//unghiVecVitMigOzLocal=(float)(acos(D3DXVec3Dot(&vecVxyzfMigLocalNormalizat,&vecVzfMigLocal))); 
				
	//D3DXVec3Normalize(&vecVxyzfMigLocalNormalizat,&vecVxyzfMigLocal); 

	impulsMig=(float)(D3DXVec3Length(&vecVxyzfMigLocal)*m);//se va calcula separat
	//impulsMig=(float)(vzfMig*m);//se va calcula separat
	viMig=vMig;
	//if(vzfMig!=0.0f)
		vMig=(float)(D3DXVec3Length(&vecVxyzfMigLocal)*3600.0f/1000.0f);
	//else
	//	vMig=0.0f;
	//impulsMig=(float)(vMig*1000.0f/3600.0f*m);//se va calcula separat
	//aMig=(float)(vMig-viMig/tpf);
	aMig=(float)(sqrt(axMig*axMig+ayMig*ayMig+azMig*azMig));

	//viteza verticala
	D3DXVec3TransformCoord(&vecVxyzfMigLocal,&vecVxyzfMigLocal,pMatMig);	
	//vVertMig=vecVxyzfMigLocal.y-vecOrigine.y;	
	//vVertMig=0.0f;
	/*if((VectorCentruRoti.y-VectorCentruRotiVechi.y)<-0.1f || (VectorCentruRoti.y-VectorCentruRotiVechi.y)>0.1f)
		vVertMig=(float)((VectorCentruRoti.y-VectorCentruRotiVechi.y)/(100.0f*tpf));	
	else
		vVertMig=0.0f;*/

	if((VectorCentruDeGreutate.y-VectorCentruDeGreutateVechi.y)<-0.1f || (VectorCentruDeGreutate.y-VectorCentruDeGreutateVechi.y)>0.1f)
		vVertMig=(float)((VectorCentruDeGreutate.y-VectorCentruDeGreutateVechi.y)/(100.0f*tpf));	
	else
		vVertMig=0.0f;

}
//----------------------------------------------------------------------------
void Fizica::SalvezaMarimiInainteDeTestColiziuni()
{	
	 txMigSalvat=txMig;
	 tyMigSalvat=tyMig;
	 tzMigSalvat=tzMig;

	 vxfMigSalvat=vxfMig;
	 vxiMigSalvat=vxiMig;
	 vyfMigSalvat=vyfMig;
	 vyiMigSalvat=vyiMig;
	 vzfMigSalvat=vzfMig;
	 vziMigSalvat=vziMig;

}
//----------------------------------------------------------------------------
void Fizica::VectoriTestatiPentruColiziune()
{
	int index;
	index=0;
	/*tablouVectoriTestati[index].valid=true;
	tablouVectoriTestati[index].vectorInitial=D3DXVECTOR3(0.0f,0.71f,0.0f);
	tablouVectoriTestati[index].vectorActual=D3DXVECTOR3(0.0f,0.71f,0.0f);
	tablouVectoriTestati[index].vectorAnticipat=D3DXVECTOR3(0.0f,0.71f,0.0f);*/

	//Varf	0
	//tablouVectoriTestati[index].valid=true;
	tablouVectoriTestati[index].vectorInitial=D3DXVECTOR3(-0.35f,-0.2f,785.05f);
	tablouVectoriTestati[index].vectorActual=D3DXVECTOR3(-0.35f,-0.2f,785.05f);
	tablouVectoriTestati[index].vectorAnticipat=D3DXVECTOR3(-0.35f,-0.2f,785.05f);
	tablouVectoriTestati[index].distanta=(float)fabs(tablouVectoriTestati[index].vectorInitial.y);

	//roata fata 1
	index++;	
	//tablouVectoriTestati[index].valid=true;
	tablouVectoriTestati[index].vectorInitial=D3DXVECTOR3(0.0f,-136.44f,453.32f);
	tablouVectoriTestati[index].vectorActual=D3DXVECTOR3(0.0f,-136.44f,453.32f);
	tablouVectoriTestati[index].vectorAnticipat=D3DXVECTOR3(0.0f,-136.44f,453.32f);
	tablouVectoriTestati[index].distanta=(float)fabs(tablouVectoriTestati[index].vectorInitial.y);

	//roata stanga 2		
	index++;	
	//tablouVectoriTestati[index].valid=true;
	tablouVectoriTestati[index].vectorInitial=D3DXVECTOR3(-126.75f,-136.44f,-23.21f);
	tablouVectoriTestati[index].vectorActual=D3DXVECTOR3(-126.75f,-136.44f,-23.21f);
	tablouVectoriTestati[index].vectorAnticipat=D3DXVECTOR3(-126.75f,-136.44f,-23.21f);
	tablouVectoriTestati[index].distanta=(float)fabs(tablouVectoriTestati[index].vectorInitial.y);
	

	//roata dreapta 3
	index++;	
	//tablouVectoriTestati[index].valid=true;
	tablouVectoriTestati[index].vectorInitial=D3DXVECTOR3(126.69f,-136.44f,-23.21f);
	tablouVectoriTestati[index].vectorActual=D3DXVECTOR3(126.69f,-136.44f,-23.22f);
	tablouVectoriTestati[index].vectorAnticipat=D3DXVECTOR3(126.69f,-136.44f,-23.21f);
	tablouVectoriTestati[index].distanta=(float)fabs(tablouVectoriTestati[index].vectorInitial.y);
			
	//AripaStanga 4
	index++;	
	//tablouVectoriTestati[index].valid=true;
	tablouVectoriTestati[index].vectorInitial=D3DXVECTOR3(-377.7f,-17.0f,-225.0f);
	tablouVectoriTestati[index].vectorActual=D3DXVECTOR3(-377.7f,-17.0f,-225.0f);
	tablouVectoriTestati[index].vectorAnticipat=D3DXVECTOR3(-377.7f,-17.0f,-225.0f);
	tablouVectoriTestati[index].distanta=(float)fabs(tablouVectoriTestati[index].vectorInitial.y);

	//AripaDreapta 5
	index++;	
	//tablouVectoriTestati[index].valid=true;
	tablouVectoriTestati[index].vectorInitial=D3DXVECTOR3(378.7f,-17.0f,-225.0f);
	tablouVectoriTestati[index].vectorActual=D3DXVECTOR3(378.7f,-17.0f,-225.0f);
	tablouVectoriTestati[index].vectorAnticipat=D3DXVECTOR3(378.7f,-17.0f,-225.0f);
	tablouVectoriTestati[index].distanta=(float)fabs(tablouVectoriTestati[index].vectorInitial.y);

	//AmpenajSus 6
	index++;	
	//tablouVectoriTestati[index].valid=true;
	tablouVectoriTestati[index].vectorInitial=D3DXVECTOR3(0.1f,301.97f,-722.78f);
	tablouVectoriTestati[index].vectorActual=D3DXVECTOR3(0.1f,301.97f,-722.78f);
	tablouVectoriTestati[index].vectorAnticipat=D3DXVECTOR3(0.1f,301.97f,-722.78f);
	tablouVectoriTestati[index].distanta=(float)fabs(tablouVectoriTestati[index].vectorInitial.y);
			

	//Spate 7
	index++;	
	//tablouVectoriTestati[index].valid=true;
	tablouVectoriTestati[index].vectorInitial=D3DXVECTOR3(0.0f,-42.0f,-561.62f);
	tablouVectoriTestati[index].vectorActual=D3DXVECTOR3(0.0f,-42.0f,-561.62f);
	tablouVectoriTestati[index].vectorAnticipat=D3DXVECTOR3(0.0f,-42.0f,-561.62f);
	tablouVectoriTestati[index].distanta=(float)fabs(tablouVectoriTestati[index].vectorInitial.y);

	//StabilizatorStanga 8
	index++;	
	//tablouVectoriTestati[index].valid=true;
	tablouVectoriTestati[index].vectorInitial=D3DXVECTOR3(-170.2f,145.7f,-582.7f);
	tablouVectoriTestati[index].vectorActual=D3DXVECTOR3(-170.2f,145.7f,-582.7f);
	tablouVectoriTestati[index].vectorAnticipat=D3DXVECTOR3(-170.2f,145.7f,-582.7f);
	tablouVectoriTestati[index].distanta=(float)fabs(tablouVectoriTestati[index].vectorInitial.y);

	//StabilizatorDreapta 9
	index++;	
	//tablouVectoriTestati[index].valid=true;
	tablouVectoriTestati[index].vectorInitial=D3DXVECTOR3(170.2f,145.7f,-582.7f);
	tablouVectoriTestati[index].vectorActual=D3DXVECTOR3(170.2f,145.7f,-582.7f);
	tablouVectoriTestati[index].vectorAnticipat=D3DXVECTOR3(170.2f,145.7f,-582.7f);
	tablouVectoriTestati[index].distanta=(float)fabs(tablouVectoriTestati[index].vectorInitial.y);
	//index++;

	NrDeVectori=index+1;
	
}
//----------------------------------------------------------------------------
void Fizica::VectoriRotiPentruColiziune()
{
	int index;
	index=1;
	
	if(takeOff==false)
	{
		//roata fata 1		
		//tablouVectoriTestati[index].valid=true;
		tablouVectoriTestati[index].vectorInitial=D3DXVECTOR3(0.0f,-136.44f,453.32f);
		//tablouVectoriTestati[index].vectorActual=D3DXVECTOR3(0.0f,-147.44f,453.32f);
		//tablouVectoriTestati[index].vectorAnticipat=D3DXVECTOR3(0.0f,-147.44f,453.32f);
		//tablouVectoriTestati[index].distanta=(float)fabs(tablouVectoriTestati[index].vectorInitial.y);

		//roata stanga 2		
		index++;	
		//tablouVectoriTestati[index].valid=true;
		tablouVectoriTestati[index].vectorInitial=D3DXVECTOR3(-126.75f,-136.44f,-23.21f);
		//tablouVectoriTestati[index].vectorActual=D3DXVECTOR3(-126.75f,-136.44f,-23.21f);
		//tablouVectoriTestati[index].vectorAnticipat=D3DXVECTOR3(-126.75f,-136.44f,-23.21f);
		//tablouVectoriTestati[index].distanta=(float)fabs(tablouVectoriTestati[index].vectorInitial.y);
		

		//roata dreapta 3
		index++;	
		//tablouVectoriTestati[index].valid=true;
		tablouVectoriTestati[index].vectorInitial=D3DXVECTOR3(126.69f,-136.44f,-23.21f);
		//tablouVectoriTestati[index].vectorActual=D3DXVECTOR3(126.69f,-136.44f,-23.22f);
		//tablouVectoriTestati[index].vectorAnticipat=D3DXVECTOR3(126.69f,-136.44f,-23.21f);
		//tablouVectoriTestati[index].distanta=(float)fabs(tablouVectoriTestati[index].vectorInitial.y);						
	}
	else
	{
		//roata fata 1		
		//tablouVectoriTestati[index].valid=true;
		tablouVectoriTestati[index].vectorInitial=D3DXVECTOR3(0.0f,-156.44f,453.32f);
		//tablouVectoriTestati[index].vectorActual=D3DXVECTOR3(0.0f,-147.44f,453.32f);
		//tablouVectoriTestati[index].vectorAnticipat=D3DXVECTOR3(0.0f,-148.44f,453.32f);
		//tablouVectoriTestati[index].distanta=(float)fabs(tablouVectoriTestati[index].vectorInitial.y);

		//roata stanga 2		
		index++;	
		//tablouVectoriTestati[index].valid=true;
		tablouVectoriTestati[index].vectorInitial=D3DXVECTOR3(-126.75f,-156.44f,-23.21f);
		//tablouVectoriTestati[index].vectorActual=D3DXVECTOR3(-126.75f,-147.44f,-23.21f);
		//tablouVectoriTestati[index].vectorAnticipat=D3DXVECTOR3(-126.75f,-147.44f,-23.21f);
		//tablouVectoriTestati[index].distanta=(float)fabs(tablouVectoriTestati[index].vectorInitial.y);
		

		//roata dreapta 3
		index++;	
		//tablouVectoriTestati[index].valid=true;
		tablouVectoriTestati[index].vectorInitial=D3DXVECTOR3(126.69f,-156.44f,-23.21f);
		//tablouVectoriTestati[index].vectorActual=D3DXVECTOR3(126.69f,-147.44f,-23.22f);
		//tablouVectoriTestati[index].vectorAnticipat=D3DXVECTOR3(126.69f,-147.44f,-23.21f);
		//tablouVectoriTestati[index].distanta=(float)fabs(tablouVectoriTestati[index].vectorInitial.y);						
	}	
}
//----------------------------------------------------------------------------
/*bool Fizica::TestColiziuni(LPD3DXBASEMESH pMesh,D3DXMATRIX *matMig)
{		
	
	//pStackColiziuni->LoadMatrix(matMig);					
	pStackColiziuni->TranslateLocal(-txMig,tyMig,tzMig);			  		
	pStackColiziuni->RotateAxisLocal(&D3DXVECTOR3(1.0f,0.0f,0.0f),unghiRotatieTransversalaMig);
	pStackColiziuni->RotateAxisLocal(&D3DXVECTOR3(0.0f,0.0f,1.0f),unghiRotatieLongitudinalaMig);	
	MatColiziuni=*pStackColiziuni->GetTop();		
	
	VectorCentruRotiTest=D3DXVECTOR3(0.0f,0.0f,0.0f);		
	D3DXVec3TransformCoord(&VectorCentruRotiTest,&VectorCentruRotiTest,&MatColiziuni);		

	/*D3DXVECTOR3 vec;
	if(VectorCentruRotiTest.y<=0.009f)
		vec=D3DXVECTOR3(0.0f,-1.0f,0.0f);			
	else
		vec=vecVxyzfMigLocalNormalizat;*/
	
	/*D3DXVECTOR3 vector=D3DXVECTOR3(0.0f,-1.0f,0.0f);
	D3DXVECTOR3 vector1=D3DXVECTOR3(-0.005f,-1.0f,0.0f);
	D3DXVECTOR3 vector2=D3DXVECTOR3(0.0f,-1.0f,0.005f);

	//vector1=D3DXVECTOR3(vecVxyzfMigLocalNormalizat.x-0.5f,vecVxyzfMigLocalNormalizat.y,vecVxyzfMigLocalNormalizat.z);
	//vector2=D3DXVECTOR3(vecVxyzfMigLocalNormalizat.x,vecVxyzfMigLocalNormalizat.y,vecVxyzfMigLocalNormalizat.z+0.5f);
	//vector3=D3DXVECTOR3(0.0f,0.0f,vecVxyzfMigLocalNormalizat.z);

	D3DXVec3Normalize(&vector,&vector); 
	D3DXVec3Normalize(&vector1,&vector1); 
	D3DXVec3Normalize(&vector2,&vector2); 

	D3DXIntersect(pMesh,
				  &VectorCentruRotiTest,
				  &vector,
				  &pHit,
				  &pFaceIndex,
				  &pU,
				  &pV,
				  &pDist
				  );

	D3DXIntersect(pMesh,
				  &VectorCentruRotiTest,
				  &vector1,//vector1,//directia este dir Rezultantei fortelor
				  &pHit1,
				  &pFaceIndex1,
				  &pU1,
				  &pV1,
				  &pDist1
				  );

	D3DXIntersect(pMesh,
				  &VectorCentruRotiTest,
				  &vector2,//vector2,//directia este dir Rezultantei fortelor
				  &pHit2,
				  &pFaceIndex2,
				  &pU2,
				  &pV2,
				  &pDist2
				  );
	
	D3DXVec3Scale(&vector,&vector,pDist); 
	D3DXVec3Scale(&vector1,&vector1,pDist1); 
	D3DXVec3Scale(&vector2,&vector2,pDist2); 
	//D3DXVec3Scale(&vector3,&vecVxyzfMigLocalNormalizat,pDist); 
	

	pU1=D3DXVec3Length(&vector1); 
	pU2=D3DXVec3Length(&vector2); 

	D3DXVECTOR3 vectorFata1=D3DXVECTOR3(0.0f,0.0f,0.0f);
	D3DXVECTOR3 vectorFata2=D3DXVECTOR3(0.0f,0.0f,0.0f);

	D3DXVec3Subtract(&vectorFata1,&vector1,&vector); 	
	D3DXVec3Subtract(&vectorFata2,&vector2,&vector); 
	//D3DXVec3Normalize(&vectorFata1,&vectorFata1); 
	//D3DXVec3Normalize(&vectorFata2,&vectorFata2); 
	
	//D3DXVECTOR3 normala=D3DXVECTOR3(0.0f,0.0f,0.0f);
	D3DXVec3Cross(&normalaFata,&vectorFata1,&vectorFata2); 	
	D3DXVec3Normalize(&normalaFata,&normalaFata); 

	/*D3DXPLANE pFataColiziune;
	D3DXPlaneFromPoints(&pFataColiziune,&vector1,&vector2,&vector3); 
	D3DXPLANE* D3DXPlaneNormalize(D3DXPLANE* pOut,CONST D3DXPLANE* pP);*/
	
	//altUnitWorld=VectorCentruRotiTest.y;							
	//altM=VectorCentruRotiTest.y/100.0f;

	/*float valoareCritica,bounceVal;	
	valoareCritica=10.0f;
	
	if(pHit==false && (vMig*3600.0f/1000.0f)<310.0f)
		bounceVal=-(float)(RezultantaZ*sin(tetazRadiani)
				  +RezultantaX*sin(tetaxRadiani)
				  +RezultantaY*sin(tetayRadiani));
		//bounceVal=impulsMig;//temp
	else
		if(pHit==false)
			bounceVal=impulsMig;
					   

	//coliziune cu terenul
	//VectorCentruRotiTest.y
	if(pHit==false)			
		//if((vyfMig*3600.0f/1000.0f)<=-valoareCritica)		
	{
		//N=G;		
		//if(vzfMig<=0.0f)
			FreactiuneSol=bounceVal;//=f(vyfMig)				
		//else
		//	FreactiuneSol=80000.0f;

		Ryf=0.0f;
		vyfMig=0.0f;
		//tyMig=0.0f;
		ayMig=0.0f;
		vyiMig=0.0f;		
		return true;
	}	
	else
	{
		N=0.0f;		
		FreactiuneSol=0.0f;	
		//Ryf=0.0f;
		return false;
	}			
}*/
//----------------------------------------------------------------------------
bool Fizica::TestColiziuni(D3DXMATRIX *pMatMig,
							  LPD3DXMESH pMeshDeTestat,LPD3DXMESH pMesh,
							  StructVectorTestat  TablouVectoriTestati[10])
{	

	bool rezultat=false;			
	//int indexVecDistMin=0;
	//DWORD faceIndexInainte;
	DWORD faceIndexInapoi;			
	float distantaInainteInapoi;
	D3DXVECTOR3 vectorInainteInapoi;
	//float distantaInainte;
	float distantaInapoi;			
	D3DXVECTOR3 vectorInainteDeTest;

	//int i=0;	
	//StructVectorTestat *pStructVectorTestat;
	//pStructVectorTestat=pInceputTablouVectoriTestati[0];	
	/*LPD3DXMESH pMeshTest;
	LPDIRECT3DVERTEXBUFFER8* ppVBMeshDeTestat;
	pMeshTest=pMeshDeTestat;	
	pMeshDeTestat->GetVertexBuffer(ppVBMeshDeTestat);	
	NumVerticesMeshDeTestat=pMeshDeTestat->GetNumVertices();	
	FVFMeshDeTestat=pMeshDeTestat->GetFVF();	

	D3DXComputeBoundingSphere(ppVBMeshDeTestat,
							  NumVerticesMeshDeTestat,
							  FVFMeshDeTestat,
							  &CenterBoundSphere,
							  &RadiusBoundSphere);*/

	index=0;
	//D3DXVECTOR3 vectorInitial=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//D3DXVECTOR3 vectorActual=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//D3DXVECTOR3 vectorAnticipat=D3DXVECTOR3(0.0f,0.0f,0.0f);
	D3DXVECTOR3 distantaDir=D3DXVECTOR3(0.0f,0.0f,0.0f);
	D3DXVECTOR3 distantaDir1=D3DXVECTOR3(0.0f,0.0f,0.0f);
	D3DXVECTOR3 distantaDir2=D3DXVECTOR3(0.0f,0.0f,0.0f);					
	D3DXVECTOR3 distantaDir3=D3DXVECTOR3(0.0f,0.0f,0.0f);					
	//dir=TablouVectoriTestati[i].dir;
	//dir1=TablouVectoriTestati[i].dir1;
	//dir2=TablouVectoriTestati[i].dir2;

	//pStackColiziuni->LoadMatrix(matMig);						
	for(index=0;index<7;index++)
	//{
		D3DXVec3TransformCoord(&TablouVectoriTestati[index].vectorActual,&TablouVectoriTestati[index].vectorInitial,pMatMig);									
	//	if(TablouVectoriTestati[index].distanta<TablouVectoriTestati[index+1].distanta)

	//}

	//calculam distanta pana la contact dintre VectorCentruRoti si mesha
	D3DXVECTOR3 dirContactVectorCentruRoti=D3DXVECTOR3(0.0f,-1.0f,0.0f);
	BOOL hit;
	DWORD faceIndex;
	float coordU;					
	float coordV;	
	
	D3DXIntersect(pMesh,
				  &VectorCentruRoti,
				  &dirContactVectorCentruRoti,
				  &hit,
				  &faceIndex,
				  &coordU,
				  &coordV,
				  &distContactVectorCentruRoti, nullptr, nullptr);	

	//Taking off
	temp1=(float)(G+Rzf*sin(tetazRadiani));//*sin(tetayRadiani));
								  //+Ryf);
								  //+Rzf*sin(tetazRadiani));
	
	temp2=(float)(Pf+Tf*sin(tetazRadiani));
	              /*Pf*cos(alphaAtacRadiani)
				  //+FreactiuneSol*sin(tetayRadiani)
				  +Ffrecare*cos(tetayRadiani)
				  +Ffranare*cos(tetayRadiani)
				   )/sin(tetayRadiani));*/
	
	if(vVertMig>=0.0f && distContactVectorCentruRoti<0.0005f)					
		if(temp1>=temp2)										
			tyMig=-(float)(tan(tetazRadiani)*fabs(tzMig));
		else
			if(tyMig<-(float)(tan(tetazRadiani)*fabs(tzMig)))
				tyMig=-(float)(tan(tetazRadiani)*fabs(tzMig));
			
	if(vVertMig<=0.0f && distContactVectorCentruRoti<1.0)
		if(temp1>=temp2)										
			tyMig=-(float)(tan(tetazRadiani)*fabs(tzMig));		

	//reorientarea sistemului de axe
	pStackOrientareAxe->RotateAxisLocal(&D3DXVECTOR3(1.0f,0.0f,0.0f),unghiRotatieTransversalaMig);
	pStackOrientareAxe->RotateAxisLocal(&D3DXVECTOR3(0.0f,0.0f,1.0f),unghiRotatieLongitudinalaMig);	
	MatOrientareAxe=*pStackOrientareAxe->GetTop();
	
	origineAxeLocale=D3DXVECTOR3(0.0f,0.0f,0.0f);
	vectorVarfOxLocal=D3DXVECTOR3(1.0f,0.0f,0.0f);
	vectorVarfOyLocal=D3DXVECTOR3(0.0f,1.0f,0.0f);
	vectorVarfOzLocal=D3DXVECTOR3(0.0f,0.0f,1.0f);
	vectorOpusVarfOxLocal=D3DXVECTOR3(-1.0f,0.0f,0.0f);
	vectorOpusVarfOyLocal=D3DXVECTOR3(0.0f,-1.0f,0.0f);	
	vectorOpusVarfOzLocal=D3DXVECTOR3(0.0f,0.0f,-1.0f);
			
	D3DXVec3TransformCoord(&origineAxeLocale,&origineAxeLocale,pMatMig);		
	D3DXVec3TransformCoord(&vectorVarfOxLocal,&vectorVarfOxLocal,pMatMig);		
	D3DXVec3TransformCoord(&vectorVarfOyLocal,&vectorVarfOyLocal,pMatMig);		
	D3DXVec3TransformCoord(&vectorVarfOzLocal,&vectorVarfOzLocal,pMatMig);
	D3DXVec3TransformCoord(&vectorOpusVarfOxLocal,&vectorOpusVarfOxLocal,pMatMig);
	D3DXVec3TransformCoord(&vectorOpusVarfOyLocal,&vectorOpusVarfOyLocal,pMatMig);
	D3DXVec3TransformCoord(&vectorOpusVarfOzLocal,&vectorOpusVarfOzLocal,pMatMig);				
	
	D3DXVec3Subtract(&vectorOrigineVarfOxLocal,&vectorVarfOxLocal,&origineAxeLocale);
	D3DXVec3Subtract(&vectorOrigineVarfOyLocal,&vectorVarfOyLocal,&origineAxeLocale);
	D3DXVec3Subtract(&vectorOrigineVarfOzLocal,&vectorVarfOzLocal,&origineAxeLocale);
	D3DXVec3Subtract(&vectorOrigineOpusVarfOxLocal,&vectorOpusVarfOxLocal,&origineAxeLocale);
	D3DXVec3Subtract(&vectorOrigineOpusVarfOyLocal,&vectorOpusVarfOyLocal,&origineAxeLocale);
	D3DXVec3Subtract(&vectorOrigineOpusVarfOzLocal,&vectorOpusVarfOzLocal,&origineAxeLocale);
	
	D3DXVec3Normalize(&vectorOrigineVarfOxLocal,&vectorOrigineVarfOxLocal); 
	D3DXVec3Normalize(&vectorOrigineVarfOyLocal,&vectorOrigineVarfOyLocal); 
	D3DXVec3Normalize(&vectorOrigineVarfOzLocal,&vectorOrigineVarfOzLocal); 
	D3DXVec3Normalize(&vectorOrigineOpusVarfOxLocal,&vectorOrigineOpusVarfOxLocal); 
	D3DXVec3Normalize(&vectorOrigineOpusVarfOyLocal,&vectorOrigineOpusVarfOyLocal); 
	D3DXVec3Normalize(&vectorOrigineOpusVarfOzLocal,&vectorOrigineOpusVarfOzLocal); 
	
	//D3DXVec3Normalize(&vectorVarfOxLocal,&vectorVarfOxLocal); 
	//D3DXVec3Normalize(&vectorVarfOyLocal,&vectorVarfOyLocal); 
	//D3DXVec3Normalize(&vectorVarfOzLocal,&vectorVarfOzLocal); 			

	//test intersectie pe directiile vitezelor locale				
	//VectorCentruDeGreutate
	D3DXIntersect(pMesh,
				  &VectorCentruDeGreutate,
				  &vecVxfMigLocal,//este normalizat
				  &hitVecVxfMigLocal,
				  &faceIndex,
				  &coordU,
				  &coordV,
				  &distantaVxLocal, nullptr, nullptr);//neutilizat
	
	D3DXIntersect(pMesh,
				  &VectorCentruDeGreutate,
				  &vecVyfMigLocal,//este normalizat
				  &hitVecVyfMigLocal,
				  &faceIndex,
				  &coordU,
				  &coordV,
				  &distantaVyLocal, nullptr, nullptr);//neutilizat
	
	D3DXIntersect(pMesh,
				  &VectorCentruDeGreutate,
				  &vecVzfMigLocal,//este normalizat
				  &hitVecVzfMigLocal,
				  &faceIndex,
				  &coordU,
				  &coordV,
				  &distantaVzLocal, nullptr, nullptr);//neutilizat

	//matricea de transformare anticipata a vectorului testat 																																			
	pStackColiziuni->LoadMatrix(pMatMig);			
	pStackColiziuni->TranslateLocal(txMig,tyMig,tzMig);			  								
	pStackColiziuni->RotateAxisLocal(&D3DXVECTOR3(1.0f,0.0f,0.0f),unghiRotatieTransversalaMig);
	pStackColiziuni->RotateAxisLocal(&D3DXVECTOR3(0.0f,0.0f,1.0f),unghiRotatieLongitudinalaMig);
	MatColiziuni=*pStackColiziuni->GetTop();

	
	if(distContactVectorCentruRoti<900.0f)
		if(dupaContact==false)
		{					
			index=0;



			while(TablouVectoriTestati[index].valid==true)// && TablouVectoriTestati[i].hit==false)
			{					
				
				//vectorInitial=TablouVectoriTestati[index].vectorInitial;						
				//vectorActual=TablouVectoriTestati[index].vectorActual;				
				//vectorAnticipat=TablouVectoriTestati[index].vectorAnticipat;				
				
				//determinam directiile pentru testul de intersectie de la vectori spre mesha
				if(distContactVectorCentruRoti<=1.0f && (tetayGrade<-80.0f || tetayGrade>80.0f))// takeOff==false)
				{
					takeOff=false;
					landing=true;
					TablouVectoriTestati[index].dir2=D3DXVECTOR3(-0.005f,-1.0f,0.0f);			
					TablouVectoriTestati[index].dir=D3DXVECTOR3(0.0f,-1.0f,0.0f);			
					TablouVectoriTestati[index].dir1=D3DXVECTOR3(0.0f,-1.0f,0.0f);			
					TablouVectoriTestati[index].dir3=D3DXVECTOR3(0.0f,-1.0f,0.005f);				

					D3DXVec3Normalize(&TablouVectoriTestati[index].dir2,&TablouVectoriTestati[index].dir2); 
					D3DXVec3Normalize(&TablouVectoriTestati[index].dir,&TablouVectoriTestati[index].dir); 
					D3DXVec3Normalize(&TablouVectoriTestati[index].dir1,&TablouVectoriTestati[index].dir1); 
					D3DXVec3Normalize(&TablouVectoriTestati[index].dir3,&TablouVectoriTestati[index].dir3); 
					
					distantaDir2=D3DXVECTOR3(-0.005f,-1.0f,0.0f);			
					distantaDir=D3DXVECTOR3(0.0f,-1.0f,0.0f);			
					distantaDir1=D3DXVECTOR3(0.0f,-1.0f,0.0f);			
					distantaDir3=D3DXVECTOR3(0.0f,-1.0f,0.005f);

					D3DXVec3Normalize(&distantaDir1,&distantaDir1); 
					D3DXVec3Normalize(&distantaDir,&distantaDir); 
					D3DXVec3Normalize(&distantaDir2,&distantaDir2); 
					D3DXVec3Normalize(&distantaDir3,&distantaDir3);
				}
				else
				{
					takeOff=true;
					landing=false;
					TablouVectoriTestati[index].dir2=D3DXVECTOR3(vecVxyzfMigLocalNormalizat.x-0.05f,vecVxyzfMigLocalNormalizat.y,vecVxyzfMigLocalNormalizat.z);						
					TablouVectoriTestati[index].dir=D3DXVECTOR3(vecVxyzfMigLocalNormalizat.x,vecVxyzfMigLocalNormalizat.y,vecVxyzfMigLocalNormalizat.z);															
					TablouVectoriTestati[index].dir1=D3DXVECTOR3(vecVxyzfMigLocalNormalizat.x,vecVxyzfMigLocalNormalizat.y,vecVxyzfMigLocalNormalizat.z);											
					TablouVectoriTestati[index].dir3=D3DXVECTOR3(vecVxyzfMigLocalNormalizat.x,vecVxyzfMigLocalNormalizat.y,vecVxyzfMigLocalNormalizat.z+0.05f);							

					D3DXVec3Normalize(&TablouVectoriTestati[index].dir2,&TablouVectoriTestati[index].dir2); 
					D3DXVec3Normalize(&TablouVectoriTestati[index].dir,&TablouVectoriTestati[index].dir); 
					D3DXVec3Normalize(&TablouVectoriTestati[index].dir1,&TablouVectoriTestati[index].dir1); 
					D3DXVec3Normalize(&TablouVectoriTestati[index].dir3,&TablouVectoriTestati[index].dir3); 

					distantaDir2=D3DXVECTOR3(vecVxyzfMigLocalNormalizat.x-0.05f,vecVxyzfMigLocalNormalizat.y,vecVxyzfMigLocalNormalizat.z);						
					distantaDir=D3DXVECTOR3(vecVxyzfMigLocalNormalizat.x,vecVxyzfMigLocalNormalizat.y,vecVxyzfMigLocalNormalizat.z);			
					distantaDir1=D3DXVECTOR3(vecVxyzfMigLocalNormalizat.x,vecVxyzfMigLocalNormalizat.y,vecVxyzfMigLocalNormalizat.z);					
					distantaDir3=D3DXVECTOR3(vecVxyzfMigLocalNormalizat.x,vecVxyzfMigLocalNormalizat.y,vecVxyzfMigLocalNormalizat.z+0.05f);			
					
					D3DXVec3Normalize(&distantaDir1,&distantaDir1); 
					D3DXVec3Normalize(&distantaDir,&distantaDir); 
					D3DXVec3Normalize(&distantaDir2,&distantaDir2); 
					D3DXVec3Normalize(&distantaDir3,&distantaDir3);				
				}				 				
				
				//test intersectie vector actual cu pMesh
				D3DXIntersect(pMesh,
							  &TablouVectoriTestati[index].vectorActual,
							  &TablouVectoriTestati[index].dir,
							  &TablouVectoriTestati[index].hit,
							  &TablouVectoriTestati[index].faceIndex,
							  &TablouVectoriTestati[index].coordU,
							  &TablouVectoriTestati[index].coordV,
							  &TablouVectoriTestati[index].distanta, nullptr, nullptr);				
				

				//determinarea normalei suprafetei de contact											
				D3DXVECTOR3 vector;
				if(distContactVectorCentruRoti<=1.0f && (tetayGrade<-80.0f || tetayGrade>80.0f))// takeOff==false)
					vector=VectorCentruDeGreutate;
				else
					vector=TablouVectoriTestati[index].vectorActual;

				D3DXIntersect(pMesh,
							  &vector,
							  &TablouVectoriTestati[index].dir1,
							  &TablouVectoriTestati[index].hit1,
							  &TablouVectoriTestati[index].faceIndex1,
							  &TablouVectoriTestati[index].coordU1,
							  &TablouVectoriTestati[index].coordV1,
							  &TablouVectoriTestati[index].distanta1, nullptr, nullptr);

				D3DXIntersect(pMesh,
							  &vector,
							  &TablouVectoriTestati[index].dir2,
							  &TablouVectoriTestati[index].hit2,
							  &TablouVectoriTestati[index].faceIndex2,
							  &TablouVectoriTestati[index].coordU2,
							  &TablouVectoriTestati[index].coordV2,
							  &TablouVectoriTestati[index].distanta2, nullptr, nullptr);

				D3DXIntersect(pMesh,
							  &vector,
							  &TablouVectoriTestati[index].dir3,
							  &TablouVectoriTestati[index].hit3,
							  &TablouVectoriTestati[index].faceIndex3,
							  &TablouVectoriTestati[index].coordU3,
							  &TablouVectoriTestati[index].coordV3,
							  &TablouVectoriTestati[index].distanta3, nullptr, nullptr);		

				D3DXVec3Scale(&distantaDir,&distantaDir,TablouVectoriTestati[index].distanta); 
				D3DXVec3Scale(&distantaDir1,&distantaDir1,TablouVectoriTestati[index].distanta1); 
				D3DXVec3Scale(&distantaDir2,&distantaDir2,TablouVectoriTestati[index].distanta2); 
				D3DXVec3Scale(&distantaDir3,&distantaDir3,TablouVectoriTestati[index].distanta3); 

				D3DXVECTOR3 vectorFata1=D3DXVECTOR3(0.0f,0.0f,0.0f);
				D3DXVECTOR3 vectorFata2=D3DXVECTOR3(0.0f,0.0f,0.0f);

				D3DXVec3Subtract(&vectorFata1,&distantaDir2,&distantaDir1); 	
				D3DXVec3Subtract(&vectorFata2,&distantaDir3,&distantaDir1); 		
				
				D3DXVec3Cross(&TablouVectoriTestati[index].normala,&vectorFata1,&vectorFata2); 	
				D3DXVec3Normalize(&TablouVectoriTestati[index].normala,&TablouVectoriTestati[index].normala); 						
				

				//determinarea unghiului dintre normala supraf. de cont. si axele locale
				unghiNormalaAxaOx=0.0f;//D3DXToRadian(90.0f);
				unghiNormalaAxaOy=0.0f;//D3DXToRadian(0.0f);
				unghiNormalaAxaOz=0.0f;//D3DXToRadian(90.0f);		
						
				unghiNormalaAxaOx=(float)(acos(D3DXVec3Dot(&TablouVectoriTestati[index].normala,&vectorOrigineVarfOxLocal))); 
				unghiNormalaAxaOy=(float)(acos(D3DXVec3Dot(&TablouVectoriTestati[index].normala,&vectorOrigineVarfOyLocal))); 
				unghiNormalaAxaOz=(float)(acos(D3DXVec3Dot(&TablouVectoriTestati[index].normala,&vectorOrigineVarfOzLocal))); 		
				
				//transformarea anticipata a vectorului testat 																																			
				vectorInainteDeTest=TablouVectoriTestati[index].vectorActual;				
				//TablouVectoriTestati[index].vectorAnticipat=TablouVectoriTestati[index].vectorActual;
				D3DXVec3TransformCoord(&TablouVectoriTestati[index].vectorAnticipat,&TablouVectoriTestati[index].vectorInitial,&MatColiziuni);									

				//pStackColiziuni->LoadIdentity();			
				D3DXVec3Subtract(&vectorInainteInapoi,&vectorInainteDeTest,&TablouVectoriTestati[index].vectorAnticipat); 	
				distantaInainteInapoi=D3DXVec3Length(&vectorInainteInapoi);
				
				//test pentru determinarea coliziunii
				 //1.test in directia lui vecVxyzfMigLocalNormalizat		

					//vectorAnticipat=vectorActual;
				/*D3DXIntersect(pMesh,
							 &TablouVectoriTestati[index].vectorAnticipat,
							 &TablouVectoriTestati[index].dir,
							 &hitInainte,
							 &faceIndexInainte,
							 &coordU,
							 &coordV,
							 &distantaInainte);*/
				
				//2.test in directia lui -vecVxyzfMigLocalNormalizat			
				D3DXVECTOR3 MinusvecVxyzfMigLocalNormalizat;
				MinusvecVxyzfMigLocalNormalizat=-TablouVectoriTestati[index].dir;
				//dir=-dir;
				D3DXIntersect(pMesh,
							  &TablouVectoriTestati[index].vectorAnticipat,
							  &MinusvecVxyzfMigLocalNormalizat,
							  &hitInapoi,
							  &faceIndexInapoi,
							  &coordU,
							  &coordV,
							  &distantaInapoi, nullptr, nullptr);

				//obs. pista se va incarca separat ca mesa
				if(TablouVectoriTestati[index].hit==TRUE && hitInapoi==TRUE
					&& TablouVectoriTestati[index].faceIndex==faceIndexInapoi)				
				{											
					distPanaLaContact=TablouVectoriTestati[index].distanta;							

					if(txMig<0.0f)				
							txMig=-(float)(distPanaLaContact*cos(unghiVecVitMigOxLocal));				
					else
						if(txMig>0.0f)
							txMig=(float)(distPanaLaContact*cos(unghiVecVitMigOxLocal));
						else
							if(txMig==0.0f)
								txMig=0.0f;				

					if(tyMig<0.0f)		
						//if((distPanaLaContact*cos(unghiVecVitMigOy))>0.71f)
							tyMig=-(float)(distPanaLaContact*cos(unghiVecVitMigOyLocal));//+0.071f-tan(tetazRadiani)*fabs(tzMig));							
							//tyMig=-(float)(tan(tetazRadiani)*fabs(tzMig));				
						//else
						//	tyMig=0.0f;
					else
						if(tyMig>0.0f)
							//if((distPanaLaContact*cos(unghiVecVitMigOy))>0.71f)
								tyMig=(float)(distPanaLaContact*cos(unghiVecVitMigOyLocal));//-0.071f;				
								//tyMig=(float)(tan(tetazRadiani)*fabs(tzMig));														
							//else
							//	tyMig=0.0f;
						else
							if(tyMig==0.0f)
								tyMig=0.0f;									
							
					if(tzMig<0.0f)				
							tzMig=-(float)(distPanaLaContact*cos(unghiVecVitMigOzLocal));				
					else
						if(tzMig>0.0f)
							tzMig=(float)(distPanaLaContact*cos(unghiVecVitMigOzLocal));
						else
							if(tzMig==0.0f)
							tzMig=0.0f;

					//calculam deplasarile dupa contact pe baza teoriei conservarii impulsului
					dupaContact=true;
					//1.calculam unghiul dintre vectroul viteza Mig si normala la supraf. de contact															
					OpusvecVxyzfMigLocalNormalizat=-vecVxyzfMigLocalNormalizat;
					D3DXVec3Normalize(&OpusvecVxyzfMigLocalNormalizat,&OpusvecVxyzfMigLocalNormalizat); 
					unghiVecVitMigNormala=(float)(acos(D3DXVec3Dot(&TablouVectoriTestati[index].normala,
																   &OpusvecVxyzfMigLocalNormalizat))); 
					//2.calculam vectorul vecVxyzfMigLocalContact (de reflexie|recul) normalizat				
					//ESTE GRESIT!!!												
					D3DXVec3Cross(&VectCrossProduct,			
								  &OpusvecVxyzfMigLocalNormalizat,
								  &TablouVectoriTestati[index].normala); 
					D3DXVec3Normalize(&VectCrossProduct,&VectCrossProduct); 
					
					D3DXMatrixIdentity(&MatContact); 	
					D3DXMatrixRotationAxis(&MatContact,
										   &VectCrossProduct,
										   2*unghiVecVitMigNormala); 
					D3DXVec3Normalize(&VectCrossProduct,&VectCrossProduct); 
					D3DXVec3TransformCoord(&vecVxyzfMigLocalContact,&OpusvecVxyzfMigLocalNormalizat,&MatContact);
					
					/*pQuatRotVitContact->x=OpusvecVxyzfMigLocalNormalizat.x;
					pQuatRotVitContact->y=OpusvecVxyzfMigLocalNormalizat.y;
					pQuatRotVitContact->z=OpusvecVxyzfMigLocalNormalizat.z;
					if(D3DXVec3Length(&vecVxyzfMigLocalNormalizat)>0.0f)
						D3DXQuaternionRotationAxis(pQuatRotVitContact,
											       &pVectCrossProduct,
												   -2*unghiVecVitMigNormala); 
					vecVxyzfMigLocalContact.x=pQuatRotVitContact->x;
					vecVxyzfMigLocalContact.y=pQuatRotVitContact->y;
					vecVxyzfMigLocalContact.z=pQuatRotVitContact->z;*/


					/*if(D3DXVec3Length(&vecVxyzfMigLocalNormalizat)>0.0f)
						D3DXVec3Subtract(&vecVxyzfMigLocalContact,
										 &TablouVectoriTestati[index].normala,
										 &vecVxyzfMigLocalNormalizat);*/
					D3DXVec3Normalize(&vecVxyzfMigLocalContact,&vecVxyzfMigLocalContact); 
					unghiVecVitMigContactNormala=(float)(acos(D3DXVec3Dot(&TablouVectoriTestati[index].normala,
																   &vecVxyzfMigLocalContact)));
					
					//3.calculam unghiurile dintre vecVxyzfMigLocalContact si axele locale
					D3DXVECTOR3 vitMigVarfAxa,vitMigOpusVarfAxa;
					vitMigVarfAxa=D3DXVECTOR3(0.0f,0.0f,0.0f);
					vitMigOpusVarfAxa=D3DXVECTOR3(0.0f,0.0f,0.0f);

					D3DXVec3Subtract(&vitMigVarfAxa,
									 &vecVxyzfMigLocalContact,&vectorOrigineVarfOxLocal); 	
					D3DXVec3Subtract(&vitMigOpusVarfAxa,
									 &vecVxyzfMigLocalContact,&vectorOrigineOpusVarfOxLocal); 					

					
					if(D3DXVec3Length(&vitMigVarfAxa)<D3DXVec3Length(&vitMigOpusVarfAxa))
						unghiVecVitMigContactOx=(float)(acos(D3DXVec3Dot(&vecVxyzfMigLocalContact,&vectorOrigineVarfOxLocal))); 
					else
						unghiVecVitMigContactOx=(float)(acos(D3DXVec3Dot(&vecVxyzfMigLocalContact,&vectorOrigineOpusVarfOxLocal))); 

					D3DXVec3Subtract(&vitMigVarfAxa,
									 &vecVxyzfMigLocalContact,&vectorOrigineVarfOyLocal); 	
					D3DXVec3Subtract(&vitMigOpusVarfAxa,
									 &vecVxyzfMigLocalContact,&vectorOrigineOpusVarfOyLocal); 					

					if(D3DXVec3Length(&vitMigVarfAxa)<D3DXVec3Length(&vitMigOpusVarfAxa))
						unghiVecVitMigContactOy=(float)(acos(D3DXVec3Dot(&vecVxyzfMigLocalContact,&vectorOrigineVarfOyLocal))); 
					else
						unghiVecVitMigContactOy=(float)(acos(D3DXVec3Dot(&vecVxyzfMigLocalContact,&vectorOrigineOpusVarfOyLocal))); 

					D3DXVec3Subtract(&vitMigVarfAxa,
									 &vecVxyzfMigLocalContact,&vectorOrigineVarfOzLocal); 	
					D3DXVec3Subtract(&vitMigOpusVarfAxa,
									 &vecVxyzfMigLocalContact,&vectorOrigineOpusVarfOzLocal); 					
					
					if(D3DXVec3Length(&vitMigVarfAxa)<D3DXVec3Length(&vitMigOpusVarfAxa))
						unghiVecVitMigContactOz=(float)(acos(D3DXVec3Dot(&vecVxyzfMigLocalContact,&vectorOrigineVarfOzLocal))); 					
					else
						unghiVecVitMigContactOz=(float)(acos(D3DXVec3Dot(&vecVxyzfMigLocalContact,&vectorOrigineOpusVarfOzLocal))); 					
					//4.determ. sensul vitezelor locale dupa contact										
					//Ox								
					if(hitVecVxfMigLocal==TRUE)
					{
						if(vxfMig<0.0f)
							vxiMigContact=(float)((fabs(impulsMig)/m)*cos(unghiVecVitMigContactOx)); 
						else
							if(vxfMig>0.0f)
								vxiMigContact=-(float)((fabs(impulsMig)/m)*cos(unghiVecVitMigContactOx)); 
							else
								if(vxfMig==0.0f)
									vxiMigContact=0.0f;

						//vxfMig=0.0f;
						//vxiMig=0.0f;
						//txMig=0.0f;
						txMigContact=(float)(vxiMigContact*tpf)*100;//+axMig*tpf*tpf*0.5)*100;					
					}
					else
						//vxiMigContact=0.0f;
						txMigContact=0.0f;//tyMig;					

						//vxfMig=vxiMig+axMig*tpf;
					//if(TablouVectoriTestati[index].vectorActual.y>0.1f)
						//txMigContact=(float)(vxiMigContact*tpf)*100;//+axMig*tpf*tpf*0.5)*100;					
					//else
					//	txMigContact=0.0f;

						//vxiMig=vxfMig;
					
					//Oy									
					if(hitVecVyfMigLocal==TRUE)
					   //&& distantaVyLocal<1500.0f)
					{
						if(vyfMig<0.0f)		
							vyiMigContact=(float)((fabs(impulsMig)/m)*cos(unghiVecVitMigContactOy)); 
						else
							if(vyfMig>0.0f)		
								vyiMigContact=-(float)((fabs(impulsMig)/m)*cos(unghiVecVitMigContactOy)); 
						else
							if(vyfMig==0.0f)		
								vyiMigContact=0.0f;

						//vyfMig=0.0f;
						//vyiMig=0.0f;
						//tyMig=0.0f;
						tyMigContact=(float)(vyiMigContact*tpf)*100;//+ayMig*tpf*tpf*0.5)*100;					
					}
					else
						//vyiMigContact=0.0f;
						tyMigContact=0.0f;//tyMig;					


					//vyfMig=vyiMig+ayMig*tpf;
					//if(TablouVectoriTestati[index].vectorActual.y>0.1f)
						//tyMigContact=(float)(vyiMigContact*tpf)*100;//+ayMig*tpf*tpf*0.5)*100;					
					//else
					//	tyMigContact=0.0f;
						//vyiMig=vyfMig;

					//Oz										
					float impulsInternZ;
					if(hitVecVzfMigLocal==TRUE && (tetazGrade>3.0f || tetazGrade<-3.0f))
					   //&& distantaVzLocal<5000.0f)
					{
						if(vzfMig<0.0f)
						{
							vziMigContact=(float)((fabs(impulsMig)/m)*cos(unghiVecVitMigContactOz)); 
							impulsInternZ=10000.0f;
						}
						else
							if(vzfMig>0.0f)
							{
								vziMigContact=-(float)((fabs(impulsMig)/m)*cos(unghiVecVitMigContactOz)); 
								impulsInternZ=10000.0f;
							}
							else
								if(vzfMig==0.0f)
									vziMigContact=0.0f;

						//vzfMig=0.0f;
						//vziMig=0.0f;
						//tzMig=0.0f;
						tzMigContact=(float)(vziMigContact*tpf)*100;//+azMig*tpf*tpf*0.5)*100;								
						//Tf=0.0f;
					}
					else
						//vziMigContact=0.0f;
						tzMigContact=0.0f;//tzMig;								



						//vzfMig=vziMig+azMig*tpf;				
					//if(TablouVectoriTestati[index].vectorActual.y>0.1f)
						//tzMigContact=(float)(vziMigContact*tpf)*100;//+azMig*tpf*tpf*0.5)*100;								
					//else
					//	tzMigContact=tzMig;
						//vziMig=vzfMig;

					//if(VectorRoataFata.y>VectorCentruRoti.y && distContactVectorCentruRoti<=1.0f)
					//if(index==1)								
					//	unghiRotatieTransversalaMig=tetazRadiani;					

					rezultat=true;
					break;
				}		
				else
					index++;
			}				
					
		}
		else
		{			
			if(hitVecVxfMigLocal==TRUE)
			{
				vxfMig=0.0f;
				vxiMig=0.0f;
			}

			if(hitVecVyfMigLocal==TRUE)
			  // && distantaVyLocal<5000.0f)
			{
		
				vyfMig=0.0f;
				vyiMig=0.0f;
				//tyMig=0.0f;
			}

			if(hitVecVzfMigLocal==TRUE && (tetazGrade>3.0f || tetazGrade<-3.0f))
			   //&& distantaVzLocal<5000.0f)
			{
				vzfMig=0.0f;
				vziMig=0.0f;		
				//tzMig=0.0f;
			}

			
				if(vVertMig>=-5.0f)// && (tetayGrade<-80.0f | tetayGrade>80.0f))
				{					
					//tyMig=0.0f;
					tyMig=-(float)(tan(tetazRadiani)*fabs(tzMig));														
					//tzMig=0.0f;
				}
				else
				{
					txMig=txMigContact;
					tyMig=tyMigContact;//+5000.0f;				
					tzMig=tzMigContact;//-5000.0f;				
				}			
			

			dupaContact=false;
		}
		

	if(index>3)
			index--;
	return rezultat;
}
//----------------------------------------------------------------------------
void Fizica::InitColiziuni(LPD3DXMESH pMesh,
						   StructVectorTestat  TablouVectoriTestati[10])
{
	D3DXVECTOR3 dir;

	dir=D3DXVECTOR3(vecVxyzfMigLocalNormalizat.x,vecVxyzfMigLocalNormalizat.y,vecVxyzfMigLocalNormalizat.z);																
	D3DXVec3Normalize(&dir,&dir); 

	for(index=0;index<NrDeVectori;index++)				
			D3DXIntersect(pMesh,
						  &TablouVectoriTestati[index].vectorActual,
						  &dir,
						  &TablouVectoriTestati[index].hit,
						  &TablouVectoriTestati[index].faceIndex,
						  &TablouVectoriTestati[index].coordU,
						  &TablouVectoriTestati[index].coordV,
						  &TablouVectoriTestati[index].distanta, nullptr, nullptr);
}
//----------------------------------------------------------------------------
bool Fizica::TestColiziuniNew(D3DXMATRIX *pMatMig,
							  LPD3DXMESH pMeshDeTestat,LPD3DXMESH pMesh,
							  StructVectorTestat  TablouVectoriTestati[10])
{	
	//VectoriRotiPentruColiziune();

	bool rezultat=false;			
	int indexVecDistMin=0;
	//DWORD faceIndexInainte;
	DWORD faceIndexInapoi;			
	float distantaInainteInapoi;
	D3DXVECTOR3 vectorInainteInapoi;
	//float distantaInainte;
	float distantaInapoi;			
	D3DXVECTOR3 vectorInainteDeTest;

	//int i=0;	
	//StructVectorTestat *pStructVectorTestat;
	//pStructVectorTestat=pInceputTablouVectoriTestati[0];	
	/*LPD3DXMESH pMeshTest;
	LPDIRECT3DVERTEXBUFFER8* ppVBMeshDeTestat;
	pMeshTest=pMeshDeTestat;	
	pMeshDeTestat->GetVertexBuffer(ppVBMeshDeTestat);	
	NumVerticesMeshDeTestat=pMeshDeTestat->GetNumVertices();	
	FVFMeshDeTestat=pMeshDeTestat->GetFVF();	

	D3DXComputeBoundingSphere(ppVBMeshDeTestat,
							  NumVerticesMeshDeTestat,
							  FVFMeshDeTestat,
							  &CenterBoundSphere,
							  &RadiusBoundSphere);*/

	

	D3DXVECTOR3 dir;
	D3DXVECTOR3 dir1;
	D3DXVECTOR3 dir2;
	D3DXVECTOR3 dir3;
	D3DXVECTOR3 distantaDir=D3DXVECTOR3(0.0f,0.0f,0.0f);
	D3DXVECTOR3 distantaDir1=D3DXVECTOR3(0.0f,0.0f,0.0f);
	D3DXVECTOR3 distantaDir2=D3DXVECTOR3(0.0f,0.0f,0.0f);					
	D3DXVECTOR3 distantaDir3=D3DXVECTOR3(0.0f,0.0f,0.0f);					
	//dir=TablouVectoriTestati[i].dir;
	//dir1=TablouVectoriTestati[i].dir1;
	//dir2=TablouVectoriTestati[i].dir2;
	
	/*if(unghiRotatieDupaContact<0.0001f && unghiRotatieDupaContact>-0.0001f)
	{
		if(unghiRotatieDupaContact>0.001f)
			unghiRotatieDupaContact-=0.00001f;
		if(unghiRotatieDupaContact<-0.001f)
			unghiRotatieDupaContact+=0.00001f;
	}
	else*/
		//unghiRotatieDupaContact=0.0f;

	VectorCentruRotiVechi=VectorCentruRoti;	
	VectorCentruDeGreutateVechi=VectorCentruDeGreutate;

	
	VectorCentruRoti=D3DXVECTOR3(0.0f,-146.44f,-23.21f);
	if(takeOff==false)
		VectorRoataFata=D3DXVECTOR3(0.0f,-146.44f,453.32f);		
	else
		//VectorRoataFata=D3DXVECTOR3(0.0f,-154.44f,453.32f);
		VectorRoataFata=D3DXVECTOR3(0.0f,-146.44f,453.32f);

	VectorCentruDeGreutate=D3DXVECTOR3(-0.3f,0.0f,0.0f);
	
	D3DXVec3TransformCoord(&VectorCentruRoti,&VectorCentruRoti,pMatMig);										
	
	D3DXVec3TransformCoord(&VectorRoataFata,&VectorRoataFata,pMatMig);
	
	D3DXVec3TransformCoord(&VectorCentruDeGreutate,&VectorCentruDeGreutate,pMatMig);	


	index=0;	

	//calculam distanta pana la contact dintre VectorCentruRoti si mesha
	D3DXVECTOR3 dirContactVectorCentruRoti=D3DXVECTOR3(0.0f,-1.0f,0.0f);
	BOOL hit;
	DWORD faceIndex;
	float coordU;					
	float coordV;		

	for(index=0;index<NrDeVectori;index++)	
		D3DXVec3TransformCoord(&TablouVectoriTestati[index].vectorActual,&TablouVectoriTestati[index].vectorInitial,pMatMig);										
	
	//if(VectorCentruRoti.y+146.44>=0.0f)
	D3DXIntersect(pMesh,
				  &VectorCentruRoti,
				  &dirContactVectorCentruRoti,
				  &hit,
				  &faceIndex,
				  &coordU,
				  &coordV,
				  &distContactVectorCentruRoti, nullptr, nullptr);

	//determinam directiile pentru testul de intersectie de la vectori spre mesha
		//if(distContactVectorCentruRoti<=1.0f && (tetayGrade<-80.0f || tetayGrade>80.0f))// takeOff==false)
		/*if(altM<20.0f)// && (tetayGrade<-82.0f && tetayGrade>82.0f))
		{
			//takeOff=false;
			//landing=true;
			dir2=D3DXVECTOR3(-0.005f,-1.0f,0.0f);			
			dir=D3DXVECTOR3(0.0f,-1.0f,0.0f);			
			dir1=D3DXVECTOR3(0.0f,-1.0f,0.0f);			
			dir3=D3DXVECTOR3(0.0f,-1.0f,0.005f);				
			
			D3DXVec3Normalize(&dir2,&dir2); 
			D3DXVec3Normalize(&dir,&dir); 
			D3DXVec3Normalize(&dir1,&dir1); 
			D3DXVec3Normalize(&dir3,&dir3); 
			
			distantaDir2=D3DXVECTOR3(-0.005f,-1.0f,0.0f);			
			distantaDir=D3DXVECTOR3(0.0f,-1.0f,0.0f);			
			distantaDir1=D3DXVECTOR3(0.0f,-1.0f,0.0f);			
			distantaDir3=D3DXVECTOR3(0.0f,-1.0f,0.005f);
			
			D3DXVec3Normalize(&distantaDir1,&distantaDir1); 
			D3DXVec3Normalize(&distantaDir,&distantaDir); 
			D3DXVec3Normalize(&distantaDir2,&distantaDir2); 
			D3DXVec3Normalize(&distantaDir3,&distantaDir3);
		}
		else
		{*/
			//takeOff=true;
			//landing=false;
			dir2=D3DXVECTOR3(vecVxyzfMigLocalNormalizat.x-0.05f,vecVxyzfMigLocalNormalizat.y,vecVxyzfMigLocalNormalizat.z);						
			dir=D3DXVECTOR3(vecVxyzfMigLocalNormalizat.x,vecVxyzfMigLocalNormalizat.y,vecVxyzfMigLocalNormalizat.z);															
			dir1=D3DXVECTOR3(vecVxyzfMigLocalNormalizat.x,vecVxyzfMigLocalNormalizat.y,vecVxyzfMigLocalNormalizat.z);											
			dir3=D3DXVECTOR3(vecVxyzfMigLocalNormalizat.x,vecVxyzfMigLocalNormalizat.y,vecVxyzfMigLocalNormalizat.z+0.05f);							
			
			D3DXVec3Normalize(&dir2,&dir2); 
			D3DXVec3Normalize(&dir,&dir); 
			D3DXVec3Normalize(&dir1,&dir1); 
			D3DXVec3Normalize(&dir3,&dir3); 
			
			distantaDir2=D3DXVECTOR3(vecVxyzfMigLocalNormalizat.x-0.05f,vecVxyzfMigLocalNormalizat.y,vecVxyzfMigLocalNormalizat.z);						
			distantaDir=D3DXVECTOR3(vecVxyzfMigLocalNormalizat.x,vecVxyzfMigLocalNormalizat.y,vecVxyzfMigLocalNormalizat.z);			
			distantaDir1=D3DXVECTOR3(vecVxyzfMigLocalNormalizat.x,vecVxyzfMigLocalNormalizat.y,vecVxyzfMigLocalNormalizat.z);					
			distantaDir3=D3DXVECTOR3(vecVxyzfMigLocalNormalizat.x,vecVxyzfMigLocalNormalizat.y,vecVxyzfMigLocalNormalizat.z+0.05f);			
			
			D3DXVec3Normalize(&distantaDir1,&distantaDir1); 
			D3DXVec3Normalize(&distantaDir,&distantaDir); 
			D3DXVec3Normalize(&distantaDir2,&distantaDir2); 
			D3DXVec3Normalize(&distantaDir3,&distantaDir3);				
		//}				
		

		//test intersectie vector actual cu pMesh		
		for(index=0;index<NrDeVectori;index++)				
			//if(TablouVectoriTestati[index].distanta>0.001f)
				D3DXIntersect(pMesh,
							  &TablouVectoriTestati[index].vectorActual,
							  &dir,
							  &TablouVectoriTestati[index].hit,
							  &TablouVectoriTestati[index].faceIndex,
							  &TablouVectoriTestati[index].coordU,
							  &TablouVectoriTestati[index].coordV,
							  &TablouVectoriTestati[index].distanta, nullptr, nullptr);
		
		//determinam vectorul cel mai apropiat de mesha de contact
		int i,j;
			//while(i<7)
		i=0;
		for(j=1;j<NrDeVectori;j++)
		{
			if(TablouVectoriTestati[i].distanta<=TablouVectoriTestati[j].distanta)
				indexVecDistMin=i;
			else
			{
				i=j;
				indexVecDistMin=j;
			}
		}

		index=indexVecDistMin;
		
		distPanaLaContact=TablouVectoriTestati[index].distanta;								
	
	//if(distPanaLaContact>1.0f || dupaContact==true)
	//{
		if(dupaContact==false)// && takeOff==true)
		{											
			//reorientarea sistemului de axe
			pStackOrientareAxe->RotateAxisLocal(&D3DXVECTOR3(1.0f,0.0f,0.0f),unghiRotatieTransversalaMig);
			pStackOrientareAxe->RotateAxisLocal(&D3DXVECTOR3(0.0f,0.0f,1.0f),unghiRotatieLongitudinalaMig);	
			pStackOrientareAxe->RotateAxisLocal(&D3DXVECTOR3(0.0f,1.0f,0.0f),unghiRotatieVerticalaMig);	
			pStackOrientareAxe->RotateAxisLocal(&vectorAxaRotatieContact,unghiRotatieDupaContact);
			MatOrientareAxe=*pStackOrientareAxe->GetTop();
			
			origineAxeLocale=D3DXVECTOR3(0.0f,0.0f,0.0f);
			vectorVarfOxLocal=D3DXVECTOR3(1.0f,0.0f,0.0f);
			vectorVarfOyLocal=D3DXVECTOR3(0.0f,1.0f,0.0f);
			vectorVarfOzLocal=D3DXVECTOR3(0.0f,0.0f,1.0f);
			vectorOpusVarfOxLocal=D3DXVECTOR3(-1.0f,0.0f,0.0f);
			vectorOpusVarfOyLocal=D3DXVECTOR3(0.0f,-1.0f,0.0f);	
			vectorOpusVarfOzLocal=D3DXVECTOR3(0.0f,0.0f,-1.0f);
					
			D3DXVec3TransformCoord(&origineAxeLocale,&origineAxeLocale,pMatMig);		
			D3DXVec3TransformCoord(&vectorVarfOxLocal,&vectorVarfOxLocal,pMatMig);		
			D3DXVec3TransformCoord(&vectorVarfOyLocal,&vectorVarfOyLocal,pMatMig);		
			D3DXVec3TransformCoord(&vectorVarfOzLocal,&vectorVarfOzLocal,pMatMig);
			D3DXVec3TransformCoord(&vectorOpusVarfOxLocal,&vectorOpusVarfOxLocal,pMatMig);
			D3DXVec3TransformCoord(&vectorOpusVarfOyLocal,&vectorOpusVarfOyLocal,pMatMig);
			D3DXVec3TransformCoord(&vectorOpusVarfOzLocal,&vectorOpusVarfOzLocal,pMatMig);				
			
			D3DXVec3Subtract(&vectorOrigineVarfOxLocal,&vectorVarfOxLocal,&origineAxeLocale);
			D3DXVec3Subtract(&vectorOrigineVarfOyLocal,&vectorVarfOyLocal,&origineAxeLocale);
			D3DXVec3Subtract(&vectorOrigineVarfOzLocal,&vectorVarfOzLocal,&origineAxeLocale);
			D3DXVec3Subtract(&vectorOrigineOpusVarfOxLocal,&vectorOpusVarfOxLocal,&origineAxeLocale);
			D3DXVec3Subtract(&vectorOrigineOpusVarfOyLocal,&vectorOpusVarfOyLocal,&origineAxeLocale);
			D3DXVec3Subtract(&vectorOrigineOpusVarfOzLocal,&vectorOpusVarfOzLocal,&origineAxeLocale);
			
			D3DXVec3Normalize(&vectorOrigineVarfOxLocal,&vectorOrigineVarfOxLocal); 
			D3DXVec3Normalize(&vectorOrigineVarfOyLocal,&vectorOrigineVarfOyLocal); 
			D3DXVec3Normalize(&vectorOrigineVarfOzLocal,&vectorOrigineVarfOzLocal); 
			D3DXVec3Normalize(&vectorOrigineOpusVarfOxLocal,&vectorOrigineOpusVarfOxLocal); 
			D3DXVec3Normalize(&vectorOrigineOpusVarfOyLocal,&vectorOrigineOpusVarfOyLocal); 
			D3DXVec3Normalize(&vectorOrigineOpusVarfOzLocal,&vectorOrigineOpusVarfOzLocal); 

			//unghiurile dintre vecViteza si axele locale
			D3DXVECTOR3 vitMigVarfAxa,vitMigOpusVarfAxa;
			vitMigVarfAxa=D3DXVECTOR3(0.0f,0.0f,0.0f);
			vitMigOpusVarfAxa=D3DXVECTOR3(0.0f,0.0f,0.0f);
			
			D3DXVec3Subtract(&vitMigVarfAxa,
				&vecVxyzfMigLocalNormalizat,&vectorOrigineVarfOxLocal); 	
			D3DXVec3Subtract(&vitMigOpusVarfAxa,
				&vecVxyzfMigLocalNormalizat,&vectorOrigineOpusVarfOxLocal); 					
			
			if(D3DXVec3Length(&vitMigVarfAxa)<D3DXVec3Length(&vitMigOpusVarfAxa))
				unghiVecVitMigOxLocal=(float)(acos(D3DXVec3Dot(&vecVxyzfMigLocalNormalizat,&vectorOrigineVarfOxLocal))); 
			else
				unghiVecVitMigOxLocal=(float)(acos(D3DXVec3Dot(&vecVxyzfMigLocalNormalizat,&vectorOrigineOpusVarfOxLocal))); 

			D3DXVec3Subtract(&vitMigVarfAxa,
				&vecVxyzfMigLocalNormalizat,&vectorOrigineVarfOyLocal); 	
			D3DXVec3Subtract(&vitMigOpusVarfAxa,
				&vecVxyzfMigLocalNormalizat,&vectorOrigineOpusVarfOyLocal); 					
			
			if(D3DXVec3Length(&vitMigVarfAxa)<D3DXVec3Length(&vitMigOpusVarfAxa))
				unghiVecVitMigOyLocal=(float)(acos(D3DXVec3Dot(&vecVxyzfMigLocalNormalizat,&vectorOrigineVarfOyLocal))); 
			else
				unghiVecVitMigOyLocal=(float)(acos(D3DXVec3Dot(&vecVxyzfMigLocalNormalizat,&vectorOrigineOpusVarfOyLocal))); 

			D3DXVec3Subtract(&vitMigVarfAxa,
				&vecVxyzfMigLocalNormalizat,&vectorOrigineVarfOzLocal); 	
			D3DXVec3Subtract(&vitMigOpusVarfAxa,
				&vecVxyzfMigLocalNormalizat,&vectorOrigineOpusVarfOzLocal); 					
			
			if(D3DXVec3Length(&vitMigVarfAxa)<D3DXVec3Length(&vitMigOpusVarfAxa))
				unghiVecVitMigOzLocal=(float)(acos(D3DXVec3Dot(&vecVxyzfMigLocalNormalizat,&vectorOrigineVarfOzLocal))); 
			else
				unghiVecVitMigOzLocal=(float)(acos(D3DXVec3Dot(&vecVxyzfMigLocalNormalizat,&vectorOrigineOpusVarfOzLocal))); 

			//unghiVecVitMigOxLocal=(float)(acos(D3DXVec3Dot(&vecVxyzfMigLocalNormalizat,&vectorOrigineVarfOxLocal))); 
			//unghiVecVitMigOyLocal=(float)(acos(D3DXVec3Dot(&vecVxyzfMigLocalNormalizat,&vectorOrigineVarfOyLocal))); 
			//unghiVecVitMigOzLocal=(float)(acos(D3DXVec3Dot(&vecVxyzfMigLocalNormalizat,&vectorOrigineVarfOzLocal))); 
			
			//D3DXVec3Normalize(&vectorVarfOxLocal,&vectorVarfOxLocal); 
			//D3DXVec3Normalize(&vectorVarfOyLocal,&vectorVarfOyLocal); 
			//D3DXVec3Normalize(&vectorVarfOzLocal,&vectorVarfOzLocal); 						

			//test intersectie pe directiile vitezelor locale				
			//VectorCentruDeGreutate
			D3DXIntersect(pMesh,
						  &VectorCentruDeGreutate,
						  &vecVxfMigLocal,//este normalizat
						  &hitVecVxfMigLocal,
						  &faceIndex,
						  &coordU,
						  &coordV,
						  &distantaVxLocal, nullptr, nullptr);//neutilizat
					
			D3DXIntersect(pMesh,
						  &VectorCentruDeGreutate,
						  &vecVyfMigLocal,//este normalizat
						  &hitVecVyfMigLocal,
						  &faceIndex,
						  &coordU,
						  &coordV,
						  &distantaVyLocal, nullptr, nullptr);//neutilizat
					
			D3DXIntersect(pMesh,
						  &VectorCentruDeGreutate,
						  &vecVzfMigLocal,//este normalizat
						  &hitVecVzfMigLocal,
						  &faceIndex,
						  &coordU,
						  &coordV,
						  &distantaVzLocal, nullptr, nullptr);//neutilizat

			//matricea de transformare anticipata a vectorului testat 																																			
			pStackColiziuni->LoadMatrix(pMatMig);			
			pStackColiziuni->TranslateLocal(txMig,tyMig,tzMig);			  								
			pStackColiziuni->RotateAxisLocal(&D3DXVECTOR3(1.0f,0.0f,0.0f),unghiRotatieTransversalaMig);
			pStackColiziuni->RotateAxisLocal(&D3DXVECTOR3(0.0f,0.0f,1.0f),unghiRotatieLongitudinalaMig);
			pStackColiziuni->RotateAxisLocal(&D3DXVECTOR3(0.0f,1.0f,0.0f),unghiRotatieVerticalaMig);
			pStackColiziuni->RotateAxisLocal(&vectorAxaRotatieContact,unghiRotatieDupaContact);
			
			MatColiziuni=*pStackColiziuni->GetTop();
			
			//if(distContactVectorCentruRoti<900.0f)
			//	if(dupaContact==false)
			//	{					
					//index=0;
					

					//while(TablouVectoriTestati[index].valid==true)
					//{					
																																		
						//determinarea normalei suprafetei de contact											
						D3DXVECTOR3 vector;
						//if(distContactVectorCentruRoti<=1.0f && (tetayGrade<-82.0f || tetayGrade>82.0f))// takeOff==false)
						if(altM<=0.1f)// && (tetayGrade<-82.0f && tetayGrade>82.0f))// takeOff==false)
							vector=VectorCentruDeGreutate;
						else
							vector=TablouVectoriTestati[index].vectorActual;

						D3DXIntersect(pMesh,
									  &vector,
									  &dir1,
									  &TablouVectoriTestati[index].hit1,
									  &TablouVectoriTestati[index].faceIndex1,
									  &TablouVectoriTestati[index].coordU1,
									  &TablouVectoriTestati[index].coordV1,
									  &TablouVectoriTestati[index].distanta1, nullptr, nullptr);

						D3DXIntersect(pMesh,
									  &vector,
									  &dir2,
									  &TablouVectoriTestati[index].hit2,
									  &TablouVectoriTestati[index].faceIndex2,
									  &TablouVectoriTestati[index].coordU2,
									  &TablouVectoriTestati[index].coordV2,
									  &TablouVectoriTestati[index].distanta2, nullptr, nullptr);

						D3DXIntersect(pMesh,
									  &vector,
									  &dir3,
									  &TablouVectoriTestati[index].hit3,
									  &TablouVectoriTestati[index].faceIndex3,
									  &TablouVectoriTestati[index].coordU3,
									  &TablouVectoriTestati[index].coordV3,
									  &TablouVectoriTestati[index].distanta3, nullptr, nullptr);		

						D3DXVec3Scale(&distantaDir,&distantaDir,TablouVectoriTestati[index].distanta); 
						D3DXVec3Scale(&distantaDir1,&distantaDir1,TablouVectoriTestati[index].distanta1); 
						D3DXVec3Scale(&distantaDir2,&distantaDir2,TablouVectoriTestati[index].distanta2); 
						D3DXVec3Scale(&distantaDir3,&distantaDir3,TablouVectoriTestati[index].distanta3); 

						D3DXVECTOR3 vectorFata1=D3DXVECTOR3(0.0f,0.0f,0.0f);
						D3DXVECTOR3 vectorFata2=D3DXVECTOR3(0.0f,0.0f,0.0f);

						D3DXVec3Subtract(&vectorFata1,&distantaDir2,&distantaDir1); 	
						D3DXVec3Subtract(&vectorFata2,&distantaDir3,&distantaDir1); 		
						
						D3DXVec3Cross(&TablouVectoriTestati[index].normala,&vectorFata1,&vectorFata2); 	
						D3DXVec3Normalize(&TablouVectoriTestati[index].normala,&TablouVectoriTestati[index].normala); 						
						

						//determinarea unghiului dintre normala supraf. de cont. si axele locale
						unghiNormalaAxaOx=0.0f;//D3DXToRadian(90.0f);
						unghiNormalaAxaOy=0.0f;//D3DXToRadian(0.0f);
						unghiNormalaAxaOz=0.0f;//D3DXToRadian(90.0f);		
								
						unghiNormalaAxaOx=(float)(acos(D3DXVec3Dot(&TablouVectoriTestati[index].normala,&vectorOrigineVarfOxLocal))); 
						unghiNormalaAxaOy=(float)(acos(D3DXVec3Dot(&TablouVectoriTestati[index].normala,&vectorOrigineVarfOyLocal))); 
						unghiNormalaAxaOz=(float)(acos(D3DXVec3Dot(&TablouVectoriTestati[index].normala,&vectorOrigineVarfOzLocal))); 		
						
						//transformarea anticipata a vectorului testat 																																			
						vectorInainteDeTest=TablouVectoriTestati[index].vectorActual;				
						TablouVectoriTestati[index].vectorAnticipat=TablouVectoriTestati[index].vectorActual;
						D3DXVec3TransformCoord(&TablouVectoriTestati[index].vectorAnticipat,&TablouVectoriTestati[index].vectorInitial,&MatColiziuni);									
						
						D3DXVec3Subtract(&vectorInainteInapoi,&vectorInainteDeTest,&TablouVectoriTestati[index].vectorAnticipat); 	
						distantaInainteInapoi=D3DXVec3Length(&vectorInainteInapoi);
						
						//test pentru determinarea coliziunii
						 //1.test in directia lui vecVxyzfMigLocalNormalizat		

							//vectorAnticipat=vectorActual;
						/*D3DXIntersect(pMesh,
									 &TablouVectoriTestati[index].vectorAnticipat,
									 &TablouVectoriTestati[index].dir,
									 &hitInainte,
									 &faceIndexInainte,
									 &coordU,
									 &coordV,
									 &distantaInainte);*/
						
						//2.test in directia lui -vecVxyzfMigLocalNormalizat			
						D3DXVECTOR3 MinusvecVxyzfMigLocalNormalizat;
						MinusvecVxyzfMigLocalNormalizat=-vecVxyzfMigLocalNormalizat;//-dir;
						//dir=-dir;
						D3DXIntersect(pMesh,
									  &TablouVectoriTestati[index].vectorAnticipat,
									  &MinusvecVxyzfMigLocalNormalizat,
									  &hitInapoi,
									  &faceIndexInapoi,
									  &coordU,
									  &coordV,
									  &distantaInapoi, nullptr, nullptr);

						//obs. pista se va incarca separat ca mesha
						if(TablouVectoriTestati[index].hit==TRUE && 
						   hitInapoi==TRUE &&
						   TablouVectoriTestati[index].faceIndex==faceIndexInapoi)
						   
						{											
							distPanaLaContact=TablouVectoriTestati[index].distanta;														
							distPanaLaContact=distPanaLaContact-300.0f;//echilibrare calcul

							//calculam deplasari pana la punctul de contact
							//if(distPanaLaContact>1.0f)//pentru echilibrarea calculului
							//{
								//if(hitVecVxfMigLocal==TRUE)
								//{
								if(txMig<0.0f)	
								{								
										//if(fabs((distPanaLaContact*cos(unghiVecVitMigOxLocal)))>1.0f)				
										//if(distPanaLaContact>1.0f)				
											txMig=-(float)(distPanaLaContact*cos(unghiVecVitMigOxLocal));
										//else
										//	txMig=0.0f;//-0.1f;
								}
								else
									if(txMig>0.0f)
									{
										//if(fabs((distPanaLaContact*cos(unghiVecVitMigOxLocal)))>1.0f)
										//if(distPanaLaContact>1.0f)				
											txMig=(float)(distPanaLaContact*cos(unghiVecVitMigOxLocal));
										//else
										//	txMig=0.0f;//0.1f;
									}
									else
										if(txMig==0.0f)
											txMig=0.0f;				
								//}

								//if(hitVecVyfMigLocal==TRUE)
								//{
								if(tyMig<0.0f)		
								{
									//if(fabs((distPanaLaContact*cos(unghiVecVitMigOyLocal)))>1.0f)
									//if(distPanaLaContact>1.0f)				
										tyMig=-(float)(distPanaLaContact*cos(unghiVecVitMigOyLocal));									
									//else
									//	tyMig=0.0f;//-0.1f;
								}
								else
									if(tyMig>0.0f)
									{
										//if(fabs((distPanaLaContact*cos(unghiVecVitMigOyLocal)))>1.0f)
										//if(distPanaLaContact>1.0f)				
											tyMig=(float)(distPanaLaContact*cos(unghiVecVitMigOyLocal));										
										//else
										//	tyMig=0.0f;//0.1f;
									}
									else
										if(tyMig==0.0f)
											tyMig=0.0f;
								//}
							

							//if(hitVecVzfMigLocal==TRUE)		
							//{
							if(tzMig<0.0f)				
							{
									//if(fabs((distPanaLaContact*cos(unghiVecVitMigOzLocal)))>1.0f)				
									//if(distPanaLaContact>1.0f)				
										tzMig=-(float)(distPanaLaContact*cos(unghiVecVitMigOzLocal));
									//else
									//	tzMig=0.0f;//-0.1f;
							}
							else
								if(tzMig>0.0f)
								{
									//if(fabs((distPanaLaContact*cos(unghiVecVitMigOzLocal)))>1.0f)
									//if(distPanaLaContact>1.0f)				
										tzMig=(float)(distPanaLaContact*cos(unghiVecVitMigOzLocal));
									//else
									//	tzMig=0.0f;//0.1f;
								}
								else
									if(tzMig==0.0f)
										tzMig=0.0f;
							//}
							//}
							/*else
							{
								if(hitVecVxfMigLocal==TRUE)
									txMig=0.0f;
								if(hitVecVyfMigLocal==TRUE)
									tyMig=0.0f;
								if(hitVecVzfMigLocal==TRUE)
									tzMig=0.0f;
							}*/

							//calculam deplasarile dupa contact pe baza teoriei conservarii impulsului
							dupaContact=true;
							//1.calculam unghiul dintre vectorul viteza Mig si normala la supraf. de contact															
							OpusvecVxyzfMigLocalNormalizat=-vecVxyzfMigLocalNormalizat;
							D3DXVec3Normalize(&OpusvecVxyzfMigLocalNormalizat,&OpusvecVxyzfMigLocalNormalizat); 
							unghiVecVitMigNormala=(float)(acos(D3DXVec3Dot(&TablouVectoriTestati[index].normala,
																		   &OpusvecVxyzfMigLocalNormalizat))); 
							//2.calculam vectorul vecVxyzfMigLocalContact (de reflexie|recul) normalizat				
							//ESTE GRESIT!!!												
							D3DXVec3Cross(&VectCrossProduct,			
										  &OpusvecVxyzfMigLocalNormalizat,
										  &TablouVectoriTestati[index].normala); 
							D3DXVec3Normalize(&VectCrossProduct,&VectCrossProduct); 
							
							D3DXMatrixIdentity(&MatContact); 	
							D3DXMatrixRotationAxis(&MatContact,
												   &VectCrossProduct,
												   2*unghiVecVitMigNormala); 

							D3DXVec3Normalize(&VectCrossProduct,&VectCrossProduct); 
							D3DXVec3TransformCoord(&vecVxyzfMigLocalContact,&OpusvecVxyzfMigLocalNormalizat,&MatContact);
							
							/*pQuatRotVitContact->x=OpusvecVxyzfMigLocalNormalizat.x;
							pQuatRotVitContact->y=OpusvecVxyzfMigLocalNormalizat.y;
							pQuatRotVitContact->z=OpusvecVxyzfMigLocalNormalizat.z;
							if(D3DXVec3Length(&vecVxyzfMigLocalNormalizat)>0.0f)
								D3DXQuaternionRotationAxis(pQuatRotVitContact,
														   &pVectCrossProduct,
														   -2*unghiVecVitMigNormala); 
							vecVxyzfMigLocalContact.x=pQuatRotVitContact->x;
							vecVxyzfMigLocalContact.y=pQuatRotVitContact->y;
							vecVxyzfMigLocalContact.z=pQuatRotVitContact->z;*/


							/*if(D3DXVec3Length(&vecVxyzfMigLocalNormalizat)>0.0f)
								D3DXVec3Subtract(&vecVxyzfMigLocalContact,
												 &TablouVectoriTestati[index].normala,
												 &vecVxyzfMigLocalNormalizat);*/
							D3DXVec3Normalize(&vecVxyzfMigLocalContact,&vecVxyzfMigLocalContact); 
							unghiVecVitMigContactNormala=(float)(acos(D3DXVec3Dot(&TablouVectoriTestati[index].normala,
																		   &vecVxyzfMigLocalContact)));
							
							//3.calculam unghiurile dintre vecVxyzfMigLocalContact si axele locale
							D3DXVECTOR3 vitMigVarfAxa,vitMigOpusVarfAxa;
							vitMigVarfAxa=D3DXVECTOR3(0.0f,0.0f,0.0f);
							vitMigOpusVarfAxa=D3DXVECTOR3(0.0f,0.0f,0.0f);

							D3DXVec3Subtract(&vitMigVarfAxa,
											 &vecVxyzfMigLocalContact,&vectorOrigineVarfOxLocal); 	
							D3DXVec3Subtract(&vitMigOpusVarfAxa,
											 &vecVxyzfMigLocalContact,&vectorOrigineOpusVarfOxLocal); 					

							
							if(D3DXVec3Length(&vitMigVarfAxa)<D3DXVec3Length(&vitMigOpusVarfAxa))
								unghiVecVitMigContactOx=(float)(acos(D3DXVec3Dot(&vecVxyzfMigLocalContact,&vectorOrigineVarfOxLocal))); 
							else
								unghiVecVitMigContactOx=(float)(acos(D3DXVec3Dot(&vecVxyzfMigLocalContact,&vectorOrigineOpusVarfOxLocal))); 

							D3DXVec3Subtract(&vitMigVarfAxa,
											 &vecVxyzfMigLocalContact,&vectorOrigineVarfOyLocal); 	
							D3DXVec3Subtract(&vitMigOpusVarfAxa,
											 &vecVxyzfMigLocalContact,&vectorOrigineOpusVarfOyLocal); 					

							if(D3DXVec3Length(&vitMigVarfAxa)<D3DXVec3Length(&vitMigOpusVarfAxa))
								unghiVecVitMigContactOy=(float)(acos(D3DXVec3Dot(&vecVxyzfMigLocalContact,&vectorOrigineVarfOyLocal))); 
							else
								unghiVecVitMigContactOy=(float)(acos(D3DXVec3Dot(&vecVxyzfMigLocalContact,&vectorOrigineOpusVarfOyLocal))); 

							D3DXVec3Subtract(&vitMigVarfAxa,
											 &vecVxyzfMigLocalContact,&vectorOrigineVarfOzLocal); 	
							D3DXVec3Subtract(&vitMigOpusVarfAxa,
											 &vecVxyzfMigLocalContact,&vectorOrigineOpusVarfOzLocal); 					
							
							if(D3DXVec3Length(&vitMigVarfAxa)<D3DXVec3Length(&vitMigOpusVarfAxa))
								unghiVecVitMigContactOz=(float)(acos(D3DXVec3Dot(&vecVxyzfMigLocalContact,&vectorOrigineVarfOzLocal))); 					
							else
								unghiVecVitMigContactOz=(float)(acos(D3DXVec3Dot(&vecVxyzfMigLocalContact,&vectorOrigineOpusVarfOzLocal))); 					
							//4.determ. sensul vitezelor locale dupa contact										
							//Ox								
							if(hitVecVxfMigLocal==TRUE)
							{
								if(vxfMig<0.0f)
									vxiMigContact=(float)((fabs(impulsMig)/m)*cos(unghiVecVitMigContactOx)); 
								else
									if(vxfMig>0.0f)
										vxiMigContact=-(float)((fabs(impulsMig)/m)*cos(unghiVecVitMigContactOx)); 
									else
										if(vxfMig==0.0f)
											vxiMigContact=0.0f;

								//vxfMig=0.0f;
								//vxiMig=0.0f;
								//txMig=0.0f;
								txMigContact=(float)(vxiMigContact*tpf)*100;//+axMig*tpf*tpf*0.5)*100;					
							}
							else
								//vxiMigContact=0.0f;
								txMigContact=0.0f;//tyMig;					

								//vxfMig=vxiMig+axMig*tpf;
							//if(TablouVectoriTestati[index].vectorActual.y>0.1f)
								//txMigContact=(float)(vxiMigContact*tpf)*100;//+axMig*tpf*tpf*0.5)*100;					
							//else
							//	txMigContact=0.0f;

								//vxiMig=vxfMig;
							
							//Oy									
							if(hitVecVyfMigLocal==TRUE)
							   //&& distantaVyLocal<1500.0f)
							{
								if(vyfMig<0.0f)		
									vyiMigContact=(float)((fabs(impulsMig)/m)*cos(unghiVecVitMigContactOy)); 
								else
									if(vyfMig>0.0f)		
										vyiMigContact=-(float)((fabs(impulsMig)/m)*cos(unghiVecVitMigContactOy)); 
								else
									if(vyfMig==0.0f)		
										vyiMigContact=0.0f;

								//vyfMig=0.0f;
								//vyiMig=0.0f;
								//tyMig=0.0f;
								tyMigContact=(float)(vyiMigContact*tpf)*100;//+ayMig*tpf*tpf*0.5)*100;					
							}
							else
								//vyiMigContact=0.0f;
								tyMigContact=0.0f;//tyMig;					


							//vyfMig=vyiMig+ayMig*tpf;
							//if(TablouVectoriTestati[index].vectorActual.y>0.1f)
								//tyMigContact=(float)(vyiMigContact*tpf)*100;//+ayMig*tpf*tpf*0.5)*100;					
							//else
							//	tyMigContact=0.0f;
								//vyiMig=vyfMig;

							//Oz										
							float impulsInternZ;
							if(hitVecVzfMigLocal==TRUE && (tetazGrade>3.0f || tetazGrade<-3.0f))
							   //&& distantaVzLocal<5000.0f)
							{
								if(vzfMig<0.0f)
								{
									vziMigContact=(float)((fabs(impulsMig)/m)*cos(unghiVecVitMigContactOz)); 
									impulsInternZ=10000.0f;
								}
								else
									if(vzfMig>0.0f)
									{
										vziMigContact=-(float)((fabs(impulsMig)/m)*cos(unghiVecVitMigContactOz)); 
										impulsInternZ=10000.0f;
									}
									else
										if(vzfMig==0.0f)
											vziMigContact=0.0f;

								//vzfMig=0.0f;
								//vziMig=0.0f;
								//tzMig=0.0f;
								tzMigContact=(float)(vziMigContact*tpf)*100;//+azMig*tpf*tpf*0.5)*100;								
								//Tf=0.0f;
							}
							else
								//vziMigContact=0.0f;
								tzMigContact=0.0f;//tzMig;								



								//vzfMig=vziMig+azMig*tpf;				
							//if(TablouVectoriTestati[index].vectorActual.y>0.1f)
								//tzMigContact=(float)(vziMigContact*tpf)*100;//+azMig*tpf*tpf*0.5)*100;								
							//else
							//	tzMigContact=tzMig;
								//vziMig=vzfMig;

							//if(VectorRoataFata.y>VectorCentruRoti.y && distContactVectorCentruRoti<=1.0f)
							//if(index==1)								
							//	unghiRotatieTransversalaMig=tetazRadiani;	


						
																																			
							/*if(index==2)//roata stanga
								unghiRotLongContact=D3DXToRadian(tetaxGrade);//-0.07f;
							if(index==3)//roata dreapta
								unghiRotLongContact=D3DXToRadian(tetaxGrade);//0.07f;

							unghiRotTranContact=0.2f;
							unghiRotVertContact=0.0f;*/


							vVertMigContact=vVertMig;
							rezultat=true;
							//break;
						}		
						//else
							//index++;
					//}//end while				
			}
			else
			{	
				if(hitVecVxfMigLocal==TRUE)
				{
						vxfMig=0.0f;
						vxiMig=0.0f;
				}

				if(hitVecVyfMigLocal==TRUE)// && (tetayGrade<-80.0f || tetayGrade>80.0f))
						// && distantaVyLocal<5000.0f)
				{
					vyfMig=0.0f;
					vyiMig=0.0f;
					//tyMig=0.0f;
				}
				
				if(hitVecVzfMigLocal==TRUE && (tetazGrade>3.0f || tetazGrade<-3.0f))
						//&& distantaVzLocal<5000.0f)
				{
					vzfMig=0.0f;
					vziMig=0.0f;		
					//tzMig=0.0f;
				}
				
				
					//calculam rotatia dupa contact					
					FortaContact=m*aMig;
					D3DXVec3Subtract(&vectorBratFortaContact,&TablouVectoriTestati[index].vectorActual,&origineAxeLocale);							
					bratFortaContact=D3DXVec3Length(&vectorBratFortaContact);							
					D3DXVec3Normalize(&vectorBratFortaContact,&vectorBratFortaContact); 																
					//D3DXVec3Normalize(&vecVxyzfMigLocalContact,&vectorBratFortaContact); 																

					unghiRotatieContact=(float)(-2.0f*FortaContact*tpf*tpf/(m*bratFortaContact));
					
					/*D3DXVec3Cross(&vectorAxaRotatieContact,
								  &vecVxyzfMigLocalContact,
								  &vectorBratFortaContact);

					D3DXVec3Normalize(&vectorAxaRotatieContact,&vectorAxaRotatieContact); 																

					D3DXMatrixIdentity(&MatContact); 								
					D3DXMatrixTranslation(&MatContact,
												   vecOrigine.x,
												   vecOrigine.y,
												   vecOrigine.z);
					D3DXVec3Normalize(&vectorAxaRotatieContact,&vectorAxaRotatieContact); 																
					*/

					//D3DXVec3TransformCoord(&vectorAxaRotatieContact,&vectorAxaRotatieContact,&MatContact);																		
					//D3DXVec3TransformCoord(&vectorAxaRotatieContact,&vectorAxaRotatieContact,&MatContact);							

				if((tetaxGrade<-7.0f || tetaxGrade>7.0f )
					|| (index!=2 && index!=3))
					flagRicoseuMod=true;//sau BUUUUUM!!!				

				if(vVertMig>=-4.0f && flagRicoseuMod==false)//  && (tetayGrade<-82.0f || tetayGrade>82.0f))// && hitVecVzfMigLocal==FALSE && (index==2 || index==3))
				{					
					
					tyMig=-(float)(tan(tetazRadiani)*fabs(tzMig));																			
					flagAterizare=true;
					takeOff=false;
															
					//if(index==2 || index==3)//roata stanga || roata dreapta																			
					unghiRotatieLongitudinalaMig=tetaxRadiani;																			
					
					/*{
						
						if(index==2)//roata stanga
						{
							vectorAxaRotatieContact=D3DXVECTOR3(0.01f,0.0f,1.0f);
							unghiRotatieDupaContact=unghiRotatieContact*400;
						}

						if(index==3)//roata dreapta
						{
							vectorAxaRotatieContact=D3DXVECTOR3(0.01f,0.0f,1.0f);
							unghiRotatieDupaContact=-unghiRotatieContact*400;
						}
					}*/
										
					//primulContact=true;
				}
				else
				{					
					txMig=txMigContact;
					tyMig=tyMigContact;//+5000.0f;				
					tzMig=tzMigContact;//-5000.0f;	
					//flagRicoseuMod=true;
				}	

				if(flagRicoseuMod==true)
				{
					if(index==0)
					{
						vectorAxaRotatieContact=D3DXVECTOR3(1.0f,0.0f,0.0f);
						unghiRotatieDupaContact=unghiRotatieContact*400;
					}


					if(index==1)
					{
						vectorAxaRotatieContact=D3DXVECTOR3(1.0f,0.0f,0.0f);
						unghiRotatieDupaContact=unghiRotatieContact*400;
					}

					if(index==2)//roata stanga
					{
						vectorAxaRotatieContact=D3DXVECTOR3(0.01f,0.0f,1.0f);
						unghiRotatieDupaContact=unghiRotatieContact*800;
					}

					if(index==3)//roata dreapta
					{
						vectorAxaRotatieContact=D3DXVECTOR3(0.01f,0.0f,1.0f);
						unghiRotatieDupaContact=-unghiRotatieContact*800;
					}								

					if(index==4)
					{
						vectorAxaRotatieContact=D3DXVECTOR3(0.1f,0.0f,1.0f);
						unghiRotatieDupaContact=unghiRotatieContact*400;
					}

					if(index==5)
					{
						vectorAxaRotatieContact=D3DXVECTOR3(0.1f,0.0f,1.0f);
						unghiRotatieDupaContact=-unghiRotatieContact*400;
					}

					if(index==6)
					{
						vectorAxaRotatieContact=D3DXVECTOR3(1.0f,0.0f,0.0f);
						unghiRotatieDupaContact=unghiRotatieContact*400;
					}

					if(index==7)
					{
						vectorAxaRotatieContact=D3DXVECTOR3(1.0f,0.0f,0.0f);
						unghiRotatieDupaContact=-unghiRotatieContact*400;
					}

					if(index==8)
					{
						vectorAxaRotatieContact=D3DXVECTOR3(0.2f,0.0f,1.0f);
						unghiRotatieDupaContact=unghiRotatieContact*400;
					}

					if(index==9)
					{
						vectorAxaRotatieContact=D3DXVECTOR3(0.2f,0.0f,1.0f);
						unghiRotatieDupaContact=-unghiRotatieContact*400;
					}
				}							
							
				dupaContact=false;				
			}
	//}
	//else
		//if(primulContact==true)
		/*{			
			txMig=0.0f;
			tyMig=0.0f;
			tzMig=0.0f;				
		}*/
		

	//if(index>3)
	//		index--;
	return rezultat;
}
//----------------------------------------------------------------------------
void Fizica::BilantulFortelorOz()//T+Pf*sin(alphaAtac)-G*sin(tetazRadiani)-Rzf=m*az;
{							
	azMig=0.0f;	

	//if(altM<1.0f)
	//{
		if(Tf>=Ffrecare+Ffranare || vzfMig>0.0f)//temp		
			azMig=(float)((Tf
						  //+Pf*sin(alphaAtacRadiani)//se anuleaza de rezistenta de unda
						  +FreactiuneSol*sin(tetazRadiani)				   
						  -G*sin(tetazRadiani)						   
						  -Rzf//*cos(alphaAtacRadiani)
						  -Ffrecare*cos(tetazRadiani)
						  -Ffranare*cos(tetazRadiani)					  
						  //-Fcfy*sin(alphaAtacRadiani)
						  )*g/G);			
		/*else
		{
			vziMig=0.0f;
			tzMig=0.0f;
		}*/
	//}
	/*else
		if(Tf>=Ffrecare+Ffranare || vzfMig>0.0f)//temp		
			azMig=(float)((Tf
						  //+Pf*sin(alphaAtacRadiani)//se anuleaza de rezistenta de unda
						  +FreactiuneSol*sin(tetazRadiani)				   
						  -G*sin(tetazRadiani)						   
						  -Rzf//*cos(alphaAtacRadiani)
						  -Ffrecare*cos(tetazRadiani)
						  -Ffranare*cos(tetazRadiani)					  
						  //-Fcfy*sin(alphaAtacRadiani)
						  )*g/G);			
		else
		{
			vziMig=0.0f;
			tzMig=0.0f;
		}*/
				
	tzMig=(float)(vziMig*tpf+azMig*tpf*tpf*0.5f)*100.0f;//in System units:1m=100cm;1unit=1cm => X[m]=X*100 [units]	

	if(azMig>0.1f || azMig<-0.1f)
	{
		vzfMig=(float)(vziMig+azMig*tpf);										
		vziMig=vzfMig;		
	}	
}
//-----------------------------------------------------------------------------------
void Fizica::BilantulFortelorOy()//Pf*sin(tetayRadiani)-G*sin(tetayRadiani)-Ryf=m*ay;
{				
	ayMig=0.0f;	
	
	//if(vzfMig>0.0f)
		ayMig=(float)((Pf*cos(alphaAtacRadiani)					   
					   +FreactiuneSol*sin(tetayRadiani)
					   -G*sin(tetayRadiani)
					   -Ryf					   
					   -Fcfy
					   +Ffrecare*cos(tetayRadiani)
					   +Ffranare*cos(tetayRadiani)					  
					   )*g/G);	
	/*else
		ayMig=(float)((Pf*cos(alphaAtacRadiani)					   
					   +FreactiuneSol*sin(tetayRadiani)
					   -G*sin(tetayRadiani)
					   -Ryf
					   //+Rzf*sin(alphaAtacRadiani)
					   -Fcfy//*cos(alphaAtacRadiani)
					   )*g/G);		
	*/
					
	tyMig=(float)(vyiMig*tpf+ayMig*tpf*tpf*0.5f)*100;			

	//if(altM<0.1f)
	if(ayMig>0.1f || ayMig<-0.1f)
	{								
		vyfMig=(float)(vyiMig+ayMig*tpf);															
		vyiMig=vyfMig;	
	}	
	/*else
	{
		vyfMig=(float)(vyiMig+ayMig*tpf);															
		vyiMig=vyfMig;	
	}*/
		
	tyMigSalvat=tyMig;
	
	//Taking off
	temp1=(float)(G+Rzf*sin(tetazRadiani)+Ryf*sin(tetayRadiani));									  		
	temp2=(float)(Pf+Tf*sin(tetazRadiani));

		/*temp1=(float)(G*sin(tetayRadiani)+Ryf+Fcfy);
		temp2=(float)(Pf*cos(alphaAtacRadiani)
					  //+FreactiuneSol*sin(tetayRadiani)
					  +Ffrecare*cos(tetayRadiani)
					  +Ffranare*cos(tetayRadiani));
		*/					  					  						

	/*float intFps;
	div_t divResult;

	modff(fps,&intFps);
	divResult=div((int)intFps,10);
	fpsMediuVechi=fpsMediu;
	fpsMediu=(float)(divResult.quot*10+5);
	fpsMediu=(float)((fpsMediu+fpsMediuVechi)/2.0f);
	*/

	//secventa de decolare
		if(takeOff==false)// && altM<0.2f)//distContactVectorCentruRoti<1.0f)
		{
			vyfMig=0.0f;
			vyiMig=0.0f;
			if(temp2<=temp1)
			{
				tyMig=-(float)(tan(tetazRadiani)*fabs(tzMig))+0.02f;											
				rataDecolare=0.0f;
			}
			else
			{
				if(tetazGrade>0.0f)
					rataDecolare+=tetazGrade/4.0f*0.04f;//*110.0f/fpsMediu;
				else
					rataDecolare=0.0f;
				tyMig=-(float)(tan(tetazRadiani)*fabs(tzMig))+rataDecolare;																									
			}							
			flagDecolare=false;
			if(altM>0.1f)
				takeOff=true;
		}							
		else
			if(flagDecolare==false)// && VectorRoataFata.y>VectorCentruRoti.y)
			{	
				//if(altM>1.0f)
					takeOff=true;
				
				rataDecolare+=4.0f*tetazGrade/4.0f*0.04f;//*20.0f*tpf;				
				//rataDecolare+=(float)(altM/100.0f*110.0f/fpsMediu);//good ideea

				tyMig=-(float)(tan(tetazRadiani)*fabs(tzMig))+rataDecolare;

				//if(altM>10.0f)
				//	rataDecolare+=0.05f*20.0f*tpf;
				//	tyMig=-(float)(tan(tetazRadiani)*fabs(tzMig))+rataDecolare;	

				if(tyMigSalvat<=tyMig || tetayGrade<40.0f)				
					flagDecolare=true;
			}	
			
		//secventa aterizare
		/*if(flagAterizare==true)
		{
			tyMig=-(float)(tan(tetazRadiani)*fabs(tzMig));				
			//if(tetazGrade>-0.4f && tetazGrade<0.6f)
			//if(tetazGrade==0.0f)
			if(altM<0.2f)
			{
				flagAterizare=false;				
				takeOff=false;
			}

		}*/
		
}
//-------------------------------------------------------------------------------
void Fizica::BilantulFortelorOx()//Pf*sin(tetaxRadiani)-G*sin(tetaxRadiani)-Rxf=m*ax;
{	
	axMig=0.0f;
	axMig=(float)((G*sin(tetaxRadiani)
				   -Rxf
				   -FreactiuneSol*sin(tetaxRadiani)	
				   //+Fcfy*cos(unghiVecVitMigOxLocal)
				   )*g/G);
		

	txMig=(float)(vxiMig*tpf+axMig*tpf*tpf*0.5f)*100;

	if(axMig>0.1f || axMig<-0.1f)
	{		
		vxfMig=vxiMig+axMig*tpf;								
		vxiMig=vxfMig;
	}	
}
//----------------------------------------------------------------------------
void Fizica::CalcVectorRezultantaForte()
{
	vecRezultantaForte=D3DXVECTOR3(0.0f,0.0f,0.0f);
	RezultantaForte=0.0f;
	RezultantaX=0.0f;
	RezultantaY=0.0f;
	RezultantaZ=0.0f;
	
	RezultantaX=(float)(G*sin(tetaxRadiani)
						-FreactiuneSol*sin(tetaxRadiani)
					    -Rxf						
						);
		
	if(vzfMig>=0.0f)
		RezultantaY=(float)(Pf*cos(alphaAtacRadiani)					    
							+FreactiuneSol*sin(tetayRadiani)
							//-Fcfy
							-G*sin(tetayRadiani)
							-Ryf
							+Ffrecare*cos(tetayRadiani)
							+Ffranare*cos(tetayRadiani)							
							);
	else
		RezultantaY=(float)(Pf*cos(alphaAtacRadiani)					    
							//-Fcfy
							+FreactiuneSol*sin(tetayRadiani)
							-G*sin(tetayRadiani)
							-Ryf							
							);

	if(Tf>=Ffrecare+Ffranare || vzfMig>0.0f)//temp
		RezultantaZ=(float)(Tf
							//+Pf*sin(alphaAtacRadiani)
							+FreactiuneSol*sin(tetazRadiani)						
							-G*sin(tetazRadiani)						   
							-Rzf
							-Ffrecare*cos(tetazRadiani)
							-Ffranare*cos(tetazRadiani)							
							);

	RezultantaForte=(float)(sqrt(RezultantaZ*RezultantaZ
								+RezultantaX*RezultantaX
								+RezultantaY*RezultantaY));

	vecRezultantaForte=vecVxyzfMigLocalNormalizat;//orientare
	D3DXVec3Scale(&vecRezultantaForte,&vecRezultantaForte,RezultantaForte); 
}
//-----------------------------------------------------------------------------------
void Fizica::CalculeazaUnghiRotatieTransversalaMig()//Tangaj=Pitch
{	
	float timp;
	/*if(takeOff==false)
		timp=0.04f*25.0f*tpf;
	else
		timp=0.056f*25.0f*tpf;
	*/	

	/*float intFps;
	div_t divResult;

	modff(fps,&intFps);
	divResult=div((int)intFps,10);
	fpsMediuVechi=fpsMediu;	
	fpsMediu=(float)(divResult.quot*10+5);
	fpsMediu=(float)((fpsMediu+fpsMediuVechi)/2.0f);
	*/

	/*if(altM<0.1f)//distContactVectorCentruRoti<1.0f)//takeOff==false)
		timp=0.04f;
		//timp=(float)(0.056f*18.0f/fpsMediu);
	else
		//timp=(float)(0.056f*18.0f/fpsMediu);
		timp=0.05f;

	if(flagFlapsLanding)
		timp=0.06f;*/

	timp=tpf;
	


	T=15.04f-0.00649f*altM;
	patm=(float)(101.29f*exp(5.256f*log((T+273.1f)/288.08f)));
	roAer=(float)(patm/(0.2869f*(T+273.1f)));

	//OBS!!! Czstabilizator scade odata cu cresterea vitezei-de implementat
	//eficacitatea scade la inaltimi mici si viteze mari-de implementat
	//float CzstabilizatorMaxim; 
	//if(alphaAtacRadiani>=0.0f)
		if(unghiBracareStabilizator!=0.0f && unghiBracareStabilizator>0.0f)			
		//if(unghiBracareStabilizator>0.0f)
		{
			Czstabilizator=(float)(1.0f*unghiBracareStabilizator/unghiBracareMaxim);//se calculeaza in functie de unghiBracareStabilizator			
		}
		else
			if(unghiBracareStabilizator!=0.0f && unghiBracareStabilizator<0.0f)
			{
				Czstabilizator=(float)(-0.5f*unghiBracareStabilizator/unghiBracareMinim);				
			}
			else
				if(unghiBracareStabilizator==0.0f)
				{
					Czstabilizator=Cz;//0.0f;
					//CzstabilizatorMaxim=0.0f;
				}


	//float PfstabilizatorMaxim;
	//if(vzfMig>5.0f)
	//{
		Pfstabilizator=(float)((roAer/2)*(vzfMig*vzfMig*Sstabilizator*Czstabilizator));	
		//PfstabilizatorMaxim=(float)((roAer/2)*(vzfMig*vzfMig*Sstabilizator*CzstabilizatorMaxim));			
		//Pfstabilizator=Pfstabilizator+4000.0f;
	//}
	//else
	//{
	//	Pfstabilizator=0.0f;
		//PfstabilizatorMaxim=0.0f;
	//}
	
	float bratulFortei;
	bratulFortei=5.0f;
		
	unghiRotatieTransversalaMigAnterior=unghiRotatieTransversalaMig;
	unghiRotatieTransversalaMig=0.0f;	


	//perturbatii			
	if(altM>10.0f && flagFlapsLanding==false)		
	{				
		if(flagBracareStabilizatorDownRelease==true)
		{	
			if(unghiRotatieTransversalaMig<=0.0f)
				unghiRotatieTransversalaMig+=0.000005f;				
		}		

		if(flagBracareStabilizatorUpRelease==true)
		{
			if(unghiRotatieTransversalaMig>=0.0f)
				unghiRotatieTransversalaMig-=0.000005f;				
		}		
	}	
	else
		unghiRotatieTransversalaMig=0.0f;	
	
	
	/*if(altM<0.1)
	{
		if(unghiBracareStabilizator!=0.0f && unghiBracareStabilizator>D3DXToDegree(alphaAtacRadiani))//0.0f)			
			unghiRotatieTransversalaMig=(float)(-2.0f*Pfstabilizator*cos(alphaAtacRadiani)
												*timp*timp/(m*bratulFortei));			
	}
	else*/
		if(unghiBracareStabilizator!=0.0f && unghiBracareStabilizator>0.0f)					
			unghiRotatieTransversalaMig=(float)(-2.0f*Pfstabilizator*cos(alphaAtacRadiani)
												*timp*timp/(m*bratulFortei));			


	if(VectorRoataFata.y>VectorCentruRoti.y || altM>1.0f)//distContactVectorCentruRoti>1.0f)
		if(unghiBracareStabilizator!=0.0f && unghiBracareStabilizator<0.0f)					
			unghiRotatieTransversalaMig=(float)(2.0f*Pfstabilizator*cos(alphaAtacRadiani)
											    *timp*timp/(m*bratulFortei));	

	//if(unghiBracareStabilizator==0.0f)
	//	unghiRotatieTransversalaMig=(float)(Pfstabilizator*cos(alphaAtacRadiani)
	//										    *timp*timp/((2*m)*bratulFortei));	
			
	//}
					

	
	

	//float temp1,temp2;
	//temp1=(float)(G+Rzf*sin(tetazRadiani)+Ryf*sin(tetayRadiani));									  		
	//temp2=(float)(Pf+Tf*sin(tetazRadiani));

	
	//bratCg=1.0f;//Cg
	//bratCp=0.95f;//Cp
	
	unghiBalansForteCg=0.0f;
	unghiBalansForteCp=0.0f;

	//ForteCg=(float)(1500.0f);
	
	if(temp2<=temp1)
	{
		ForteCg=(float)(G*sin(tetayRadiani)+Ryf);
						
	
		ForteCp=(float)(Pf*cos(alphaAtacRadiani)
						+FreactiuneSol*sin(tetayRadiani)
						+Ffrecare*cos(tetayRadiani)
						+Ffranare*cos(tetayRadiani));
	}
	else
	{
		ForteCg=0.0f;
		ForteCp=0.0f;

	}

	if(flagFlapsBagat==true)
	{
		bratCg=0.47f;//Cg
		bratCp=0.5f;//Cp
	}
	
	if(flagFlapsTakeOff==true)
	{
		bratCg=0.49f;//Cg
		bratCp=0.5f;//Cp
	}

	if(flagFlapsLanding==true)
	{
		bratCg=0.45f;//Cg
		bratCp=0.5f;//Cp
	}
	
	
	if(altM<0.2f)//distContactVectorCentruRoti<1.0f)
	{				
	
		unghiBalansForteCg=(float)(2.0f*ForteCg*timp*timp*cos(alphaAtacRadiani)
								   /(m*bratCg));	
		unghiBalansForteCp=-(float)(2.0f*ForteCp*timp*timp*cos(alphaAtacRadiani)
								   /(m*bratCp));
		//if(flagBracareStabilizatorDownRelease==true)
			unghiRotatieTransversalaMig=unghiRotatieTransversalaMig+unghiBalansForteCg+unghiBalansForteCp;				
		//if(unghiRotatieTransversalaMig>0.0f &&  VectorRoataFata.y<VectorCentruRoti.y)
		//	unghiRotatieTransversalaMig=0.0f;																	

		if(unghiRotatieTransversalaMig>0.0f && tetazGrade<=0.0f)
			unghiRotatieTransversalaMig=tetazRadiani;
		
	}
	
}
//-----------------------------------------------------------------------------------
void Fizica::CalculeazaUnghiRotatieLongitudinalaMig()
{	
	//timpRotatieLongitudinala=0.11f;
	timpRotatieLongitudinala=tpf;
	
	//timp=0.035f;
	/*float intFps;
	div_t divResult;

	modff(fps,&intFps);
	divResult=div((int)intFps,10);
	fpsMediuVechi=fpsMediu;
	fpsMediu=(float)(divResult.quot*10+5);
	fpsMediu=(float)((fpsMediu+fpsMediuVechi)/2.0f);
	
	timp=(float)(0.075*18/fpsMediu);
	*/
	

	T=15.04f-0.00649f*altM;
	patm=(float)(101.29f*exp(5.256f*log((T+273.1f)/288.08f)));
	roAer=(float)(patm/(0.2869f*(T+273.1f)));

	if(unghiBracareEleroane>0.0f)
		Czeleroane=(float)(2.0f*unghiBracareEleroane/20.0f);//se calculeaza in functie de unghiBracareStabilizator
	else
		if(unghiBracareEleroane<0.0f)
			Czeleroane=(float)(-2.0f*unghiBracareEleroane/20.0f);
		else
			if(unghiBracareEleroane==0.0f)
				Czeleroane=0.0f;


	if(vzfMig>5.0f)
		Pfeleroane=(float)((roAer/2)*(vzfMig*vzfMig*Seleroane*Czeleroane));	
	else
		Pfeleroane=0.0f;
	
	float bratulFortei;
	bratulFortei=2.4f;//[m]
		
	unghiRotatieLongitudinalaMig=0.0f;	

	if(altM>0.2f)//distContactVectorCentruRoti>1.0f)
	{
		/*if(flagBracareEleroaneStangaPress==true)// || unghiBracareEleroane>0.0f)		
			unghiRotatieLongitudinalaMig=(float)(2*Pfeleroane*cos(alphaAtacRadiani)
													*timp*timp/(2*m*bratulFortei));									
				
		if(flagBracareEleroaneDreaptaPress==true)// || unghiBracareEleroane<0.0f)							
			unghiRotatieLongitudinalaMig=(float)(-2*Pfeleroane*cos(alphaAtacRadiani)
													*timp*timp/(2*m*bratulFortei));	
		*/
		
		if(unghiBracareEleroane>0.0f)		
			unghiRotatieLongitudinalaMig=(float)(2.0f*2.0f*Pfeleroane*cos(alphaAtacRadiani+D3DXToRadian(unghiBracareEleroane))
													*timpRotatieLongitudinala*timpRotatieLongitudinala/(m*bratulFortei));	

		if(unghiBracareEleroane<0.0f)							
			unghiRotatieLongitudinalaMig=(float)(-2.0f*2.0f*Pfeleroane*cos(alphaAtacRadiani+D3DXToRadian(unghiBracareEleroane))
													*timpRotatieLongitudinala*timpRotatieLongitudinala/(m*bratulFortei));	
			
		
	}

	if(unghiRotatieLongitudinalaMig==0.0f)
		flagStartPeturbatii=true;
	else
		flagStartPeturbatii=false;

	//perturbatii				
	if(altM>3.0f && flagStartPeturbatii==true)		
	{				
		//if(flagBracareEleroaneStangaRelease==true || flagBracareEleroaneDreaptaRelease==true)
		//{
			//if(unghiRotatieLongitudinalaMig==0.0f)//dreapta
			//{
				if(kLong==true)
				{
					unghiRotatieLongitudinalaMigPerturbatii-=0.00003f;	
					unghiRotatieLongitudinalaMig=unghiRotatieLongitudinalaMigPerturbatii;
				}

				if(unghiRotatieLongitudinalaMigPerturbatii<-0.0007f)				
					kLong=false;
			//}
			
			//if(unghiRotatieLongitudinalaMig==0.0f)//dreapta
			//{
				if(kLong==false)
				{
					unghiRotatieLongitudinalaMigPerturbatii+=0.00003f;				
					unghiRotatieLongitudinalaMig=unghiRotatieLongitudinalaMigPerturbatii;
				}
				
				if(unghiRotatieLongitudinalaMigPerturbatii>0.0007f)
					kLong=true;
			//}
		}
		else
			if(flagBracareEleroaneStangaPress==true || flagBracareEleroaneDreaptaPress==true)
				unghiRotatieLongitudinalaMigPerturbatii=0.0f;
					
	//}
	else
		unghiRotatieLongitudinalaMigPerturbatii=0.0f;
				
}
//-----------------------------------------------------------------------------------
void Fizica::CalculeazaUnghiRotatieVerticalaMig()
{	
	float timp;
	if(altM<0.1f && vMig<250.0f)
		timp=0.2f;
	else
		timp=0.04f;
	
	

	T=15.04f-0.00649f*altM;
	patm=(float)(101.29f*exp(5.256f*log((T+273.1f)/288.08f)));
	roAer=(float)(patm/(0.2869f*(T+273.1f)));

	if(unghiBracareAmpenaj>0.0f)
		Czampenaj=(float)(1.8f*unghiBracareAmpenaj/25.0f);//se calculeaza in functie de unghiBracareStabilizator
	else
		if(unghiBracareAmpenaj<0.0f)
			Czampenaj=(float)(-1.8f*unghiBracareAmpenaj/25.0f);
		else
			if(unghiBracareAmpenaj==0.0f)
				Czampenaj=0.0f;


	//if(vzfMig>5.0f)
		Pfampenaj=(float)((roAer/2)*(vzfMig*vzfMig*Seleroane*Czampenaj));	
	//else
	//	Pfampenaj=0.0f;
	
	float bratulFortei;
	bratulFortei=5.5f;//[m]
	
	unghiRotatieVerticalaMig=0.0f;								
		
	if(unghiBracareAmpenaj>0.0f)		
		unghiRotatieVerticalaMig=(float)(2*Pfampenaj*cos(D3DXToRadian(unghiBracareAmpenaj))
											 *timp*timp/(m*bratulFortei));	

	if(unghiBracareAmpenaj<0.0f)							
		unghiRotatieVerticalaMig=(float)(-2*Pfampenaj*cos(D3DXToRadian(unghiBracareAmpenaj))
											 *timp*timp/(m*bratulFortei));							
}
//-----------------------------------------------------------------------------------
void Fizica::CalculeazaUnghiRotatieRoti()
{
	if(altM<0.2f)//distContactVectorCentruRoti<1.0f)
	{
		vUnghiularaRoti=(float)(vMig/0.30f);
		unghiRotatieRoti=(float)(vUnghiularaRoti*tpf);
	}
	else
	{
		if(vUnghiularaRoti>=0.0f)
			vUnghiularaRoti-=5.0f;
		unghiRotatieRoti=(float)(vUnghiularaRoti*tpf);
	}
}
//-----------------------------------------------------------------------------------
void Fizica::Comenzi()
{
	//stabilizator
	if(flagJoystick==false)
	{
	if(vMig<=455.0f || (vMig>455.0f && altM>=10000.0f))
	{
		unghiBracareMinim=14.0f;
		unghiBracareMaxim=28.0f;
		rataEfortBracare=0.6f;//0.375f;
		//efort la mansa mic=>rata mare de modificare
	}
	
	if((vMig>455.0f && vMig<=992.0f) && altM<4500.0f)
	{
		unghiBracareMinim=(float)(14.0f*455.0f/vMig);
		unghiBracareMaxim=(float)(28.0f*455.0f/vMig);
		rataEfortBracare=(float)(0.375f*455.0f/vMig);
		//efort la mansa creste=>rata variata(descrescatoare) de modificare
	}

	if(vMig>992.0f) 
	{
		unghiBracareMinim=4.0f;
		unghiBracareMaxim=15.0f;
		rataEfortBracare=0.2f;
		//efort la mansa maxim=>rata minima de modificare
	}


	if(flagBracareStabilizatorDownPress==true)//&&(pFizica->tzMig!=0.0f))
	{
		rtx=1.0f;
		rty=0.0f;
		rtz=0.0f;														
		if(unghiBracareStabilizator<unghiBracareMaxim)//16.5f)			
			unghiBracareStabilizator+=rataEfortBracare;//0.375f;//16.5f/41.25f;							
		else
			unghiBracareStabilizator=unghiBracareMaxim;

	}

	if(flagBracareStabilizatorDownRelease==true)
	{
		rtx=1.0f;
		rty=0.0f;
		rtz=0.0f;
		if(unghiBracareStabilizator>-1.0f && unghiBracareStabilizator<1.0f)
			unghiBracareStabilizator=0.0f;
		else
			if(unghiBracareStabilizator<0.0f)
				unghiBracareStabilizator-=-rataEfortBracare;//-unghiBracareMinim/20.0f;//-7.5f/20.0f;
			else
				if(unghiBracareStabilizator>0.0f)
					unghiBracareStabilizator-=rataEfortBracare;//0.375f;																
	}

		
	if(flagBracareStabilizatorUpPress==true)//&&(pFizica->tzMig!=0.0f))
	{
		rtx=1.0f;
		rty=0.0f;
		rtz=0.0f;								
		if(unghiBracareStabilizator>-unghiBracareMinim)//-7.5f)					
			unghiBracareStabilizator+=-rataEfortBracare;//-unghiBracareMinim/20.0f;//-7.5f/20.0f;			
		else
			unghiBracareStabilizator=-unghiBracareMinim;
	}	
		

	if(flagBracareStabilizatorUpRelease==true)									
	{
		rtx=1.0f;
		rty=0.0f;
		rtz=0.0f;
		if(unghiBracareStabilizator>-1.0f && unghiBracareStabilizator<1.0f)
			unghiBracareStabilizator=0.0f;
		else
			if(unghiBracareStabilizator>0.0f)
				unghiBracareStabilizator-=rataEfortBracare;//0.375f;			
			else
				if(unghiBracareStabilizator<0.0f)
					unghiBracareStabilizator-=-rataEfortBracare;//-unghiBracareMinim/20.0f;//-7.5f/20.0f;
	}

	//eleroane									     		
	pasEleroaneDecrease=1.0f;pasEleroaneIncrease=2.5f;
	//pasEleroaneDecrease=0.1f;//,pasEleroaneIncrease=0.4f;

	if(flagFlapsLanding)
	{
		pasEleroaneDecrease=0.3f;
		pasEleroaneIncrease=0.6f;
	}

	if(flagBracareEleroaneDreaptaPress==true)// && pFizica->tzMig!=0.0f)
	{								
		rlx=0.0f;
		rly=0.0f;
		rlz=1.0f;					
																	
		//if(pasEleroaneIncrease<0.4f)
		//	pasEleroaneIncrease+=0.01f;
		//pasEleroaneDecrease=0.2f;//pasEleroaneIncrease/6.0f;
		
		if(unghiBracareEleroane>-20.0f)			
			if(unghiBracareEleroane>0.0f)			
				unghiBracareEleroane-=pasEleroaneDecrease;
			else
				unghiBracareEleroane-=pasEleroaneIncrease;		
		else
			unghiBracareEleroane=-20.0f;

	}

	if(flagBracareEleroaneDreaptaRelease==true)// && pFizica->tzMig!=0.0f)
	{
		rlx=0.0f;
		rly=0.0f;
		rlz=1.0f;			
		//pasEleroaneIncrease=0.0f;
		if(unghiBracareEleroane>-1.0f && unghiBracareEleroane<1.0f)
			unghiBracareEleroane=0.0f;
		else
			if(unghiBracareEleroane<0.0f)
				unghiBracareEleroane+=pasEleroaneDecrease;
			else
				if(unghiBracareEleroane>0.0f)
					unghiBracareEleroane-=pasEleroaneDecrease;//pas2;
	}
		
						
	if(flagBracareEleroaneStangaPress==true)// && pFizica->tzMig!=0.0f)
	{								
		rlx=0.0f;
		rly=0.0f;
		rlz=1.0f;										
		//if(pasEleroaneIncrease<0.4f)
		//	pasEleroaneIncrease+=0.01f;
		//pasEleroaneDecrease=0.2f;//pasEleroaneIncrease/6.0f;
		if(unghiBracareEleroane<20.0f)
			if(unghiBracareEleroane<0.0f)
				unghiBracareEleroane+=pasEleroaneDecrease;
			else
				unghiBracareEleroane+=pasEleroaneIncrease;				
		else
			unghiBracareEleroane=20.0f;
	}

	if(flagBracareEleroaneStangaRelease==true)// && pFizica->tzMig!=0.0f)
	{
		rlx=0.0f;
		rly=0.0f;
		rlz=1.0f;				
		//pasEleroaneIncrease=0.0f;
		if(unghiBracareEleroane>-1.0f && unghiBracareEleroane<1.0f)
			unghiBracareEleroane=0.0f;
		else
			if(unghiBracareEleroane>0.0f)
				unghiBracareEleroane-=pasEleroaneDecrease;			
			else
				if(unghiBracareEleroane<0.0f)
					unghiBracareEleroane+=pasEleroaneDecrease;//pas2;			
	}
	}
	
	//ampenaj
	if(flagBracareAmpenajStangaPress==true)// && pFizica->tzMig!=0.0f)
	{								
		rvx=0.0f;
		rvy=1.0f;
		rvz=0.0f;					
			//rotLongMig=(float)-D3DX_PI/25;														
		//float pas;
		//pas=float(20.0f/10.0f);
		if(unghiBracareAmpenaj>-25.0f)			
			unghiBracareAmpenaj-=0.5f;							
	}

	if(flagBracareAmpenajStangaRelease==true)// && pFizica->tzMig!=0.0f)
	{
		rvx=0.0f;
		rvy=1.0f;
		rvz=0.0f;
			//rotLongMig=0.0f;
		//float pas;
		//pas=float(20.0f/10.0f);
		if(unghiBracareAmpenaj<0.0f)
			unghiBracareAmpenaj+=1.0f;
		else
			if(unghiBracareAmpenaj>0.0f)
				unghiBracareAmpenaj-=0.5f;
	}
		
						
	if(flagBracareAmpenajDreaptaPress==true)// && pFizica->tzMig!=0.0f)
	{								
		rvx=0.0f;
		rvy=1.0f;
		rvz=0.0f;									
		//rotLongMig=(float)D3DX_PI/25;															
		//float pas;
		//pas=float(20.0f/10.0f);
		if(unghiBracareAmpenaj<25.0f)
			unghiBracareAmpenaj+=0.5f;				
		//pTransformation->MatTransformationCameraUp=*pTransformation->pStackCameraUp->GetTop();			
	}

	if(flagBracareAmpenajDreaptaRelease==true)// && pFizica->tzMig!=0.0f)
	{
		rvx=0.0f;
		rvy=1.0f;
		rvz=0.0f;
		//rotLongMig=0.0f;
		//float pas;
		//pas=float(20.0f/10.0f);
		if(unghiBracareAmpenaj>0.0f)
			unghiBracareAmpenaj-=1.0f;			
		else
			if(unghiBracareAmpenaj<0.0f)
				unghiBracareAmpenaj+=0.5f;			
	}
		
}

//CalculeazaFizicaMig
void Fizica::CalculeazaParametriAerodinamici(D3DXMATRIX *pMatMig,  LPD3DXMESH pMesh)
{	
	Comenzi();

	CalculeazaM();			
	CalculeazaDinamicaForteiDeGreutate();
	CalculeazaDinamicaForteiDeTractiune();			
	CalculeazaDinamicaForteiPortante();				
	CalculeazaDinamicaForteiDeRezistentaRx();
	CalculeazaDinamicaForteiDeRezistentaRy();
	CalculeazaDinamicaForteiDeRezistentaRz();	
	CalculeazaDinamicaForteiDeFrecare();	
	CalculeazaDinamicaForteiDeReactiuneTeren();		
	CalcVectorRezultantaForte();	
	CalculeazaDinamicaForteiCentrifuge();
	//CalculEfecteFortePeAxeleProprii();
	BilantulFortelorOz();		
	BilantulFortelorOx();			
	BilantulFortelorOy();	
	CalculeazaUnghiRotatieTransversalaMig();
	CalculeazaUnghiRotatieLongitudinalaMig();
	CalculeazaUnghiRotatieVerticalaMig();
	
	CalculeazaVectorVitezaMig(pMatMig);	
	CalculeazaAlpha();
	CalculeazaSuprasarcina();

	CalculeazaUnghiRotatieRoti();
	

	if(tzMig<=0.0f && altM<0.2f && powerUp==false)
	{
		Init();
		InitForte();
		//InitColiziuni(pMesh,
		//			  tablouVectoriTestati);
	}
}


