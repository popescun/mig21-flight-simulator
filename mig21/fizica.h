#include "d3d8.h"
#include "d3d8types.h"
#include "D3dx8math.h"

class Fizica{
								
//date globale
public:				
		DWORD NumVerticesMeshDeTestat;
		DWORD FVFMeshDeTestat;
		D3DXVECTOR3 CenterBoundSphere;
		FLOAT RadiusBoundSphere;
		
		//coliziuni	
		//this strucuture is declared here for beeing visible in the functions
		typedef struct _structVectorTestat
		{
			D3DXVECTOR3 vectorInitial;			
			D3DXVECTOR3 vectorActual;			
			D3DXVECTOR3 vectorAnticipat;			
			D3DXVECTOR3 dir;
			D3DXVECTOR3 dir1;
			D3DXVECTOR3 dir2;
			D3DXVECTOR3 dir3;
			//D3DXVECTOR3 dirContact;
			BOOL hit;
			BOOL hit1;
			BOOL hit2;
			BOOL hit3;
			DWORD faceIndex;
			DWORD faceIndex1;
			DWORD faceIndex2;
			DWORD faceIndex3;
			FLOAT coordU;
			FLOAT coordV;
			FLOAT coordU1;
			FLOAT coordV1;
			FLOAT coordU2;
			FLOAT coordV2;
			FLOAT coordU3;
			FLOAT coordV3;
			FLOAT distanta;
			FLOAT distanta1;
			FLOAT distanta2;
			FLOAT distanta3;
			D3DXVECTOR3 normala;//suprafata de contact
			FLOAT Freactiune;			
			bool valid;
		} StructVectorTestat;
		
		StructVectorTestat tablouVectoriTestati[10];
		int NrDeVectori;
		int index;
		int indexVecDistMin;
		float temp1,temp2;

		typedef struct _fortaReactiuneContact
		{
			float compX;
			float compY;
			float compZ;
		} FortaReactiuneContact;

		FortaReactiuneContact Freactiune;
		float distPanaLaContact;

		float FortaContact,bratFortaContact,unghiRotatieContact,unghiRotatieDupaContact;
		D3DXVECTOR3 vectorBratFortaContact,vectorAxaRotatieContact;
		
		float unghiNormalaAxaOx,unghiNormalaAxaOy,unghiNormalaAxaOz;
		float unghiVecVitMigNormala;
		//vitezele dupa contact
		float unghiVecVitMigContactNormala;
		float unghiVecVitMigContactOx,unghiVecVitMigContactOy,unghiVecVitMigContactOz;
		D3DXVECTOR3 vecVxyzfMigLocalContact;
		D3DXVECTOR3 OpusvecVxyzfMigLocalNormalizat;				
		D3DXVECTOR3 VectCrossProduct;					
		D3DXMATRIX MatContact;
		D3DXQUATERNION* pQuatRotVitContact;
		float vxfMigContact,vxiMigContact,
			  vyfMigContact,vyiMigContact,
			  vzfMigContact,vziMigContact,
			  vVertMigContact; 
		float txMigContact,tyMigContact,tzMigContact,
			  unghiRotLongContact,unghiRotTranContact,unghiRotVertContact; 				
		bool dupaContact,primulContact;
		bool takeOff,landing;
		bool flagRicoseuMod;
		
		

		D3DXVECTOR3 origineAxeLocale,
					vectorVarfOxLocal,vectorVarfOyLocal,vectorVarfOzLocal,
					vectorOpusVarfOxLocal,vectorOpusVarfOyLocal,vectorOpusVarfOzLocal,
					vectorOrigineVarfOxLocal,vectorOrigineVarfOyLocal,vectorOrigineVarfOzLocal,
					vectorOrigineOpusVarfOxLocal,vectorOrigineOpusVarfOyLocal,vectorOrigineOpusVarfOzLocal;
		D3DXMATRIX MatOrientareAxe;
		LPD3DXMATRIXSTACK pStackOrientareAxe;
		BOOL hitVecVxfMigLocal,hitVecVyfMigLocal,hitVecVzfMigLocal;			
		float distantaVxLocal,distantaVyLocal,distantaVzLocal;

		BOOL hitInainte;						
		BOOL hitInapoi;						
		
		D3DXMATRIX MatColiziuni;
		LPD3DXMATRIXSTACK pStackColiziuni;		

		//parametri testati		
		D3DXVECTOR3 VectorCentruRotiTest;//se testeaza anticipat-ptr. exeprimentare
		D3DXVECTOR3 VectorCentruRoti;//este valoarea randata normal odata cu mesha mig-ului		
		D3DXVECTOR3 VectorCentruRotiVechi;		
		D3DXVECTOR3 VectorRoataFata;
		D3DXVECTOR3 VectorCentruDeGreutate;
		D3DXVECTOR3 VectorCentruDeGreutateVechi;
		
		float distContactVectorCentruRoti;
		
		float txMigSalvat;	 
		float tyMigSalvat;				
		float tzMigSalvat;

		float vxfMigSalvat;
		float vxiMigSalvat;
		float vyfMigSalvat;
		float vyiMigSalvat;
		float vzfMigSalvat;
		float vziMigSalvat;
		
		//sistem
		float tpf;// [s] TimpPeFrame
		float fps;// [s] FramesPeSecunda				
		float fpsMediu;// [s] FramesPeSecunda				
		float fpsMediuVechi;// [s] FramesPeSecunda				
		//------------------------------------------------
		//Forta de tractiurne
		float Tmax;// [kgf] FortaDeTractiuneMaxima
		float Tinstant;// [kgf] FortaDeTractiuneInstantanee
		float Tf;// [kgf] FortaDeTractiuneFinala
		
		float STOP,RALANTI,MAXIM_ASL,MAXIM,
			  FORTAJ_MINIM,FORTAJ_MAXIM;		
		
		float TimpPartialAcceleratie;//[s] al Mig-ului
		float TimpTotalAcceleratie;//[s] al Mig-ului
				
		//throttle
		bool powerUp;
		bool powerDown;
		//-----------------------------------------------
		//Forta de greutate
		float m;// [kg] masa 
		float g;// [m/s*s] AcceleratiaGravitationala		
		float G;// [kgf] Greutate
		float vfG;// [m/s] VitezaForteiDeGreutateFinala
		float viG;// [m/s] VitezaForteiDeGreutateInitiala				
		float N;//[]kgfForta de reactiune normala (efectul pamantului asupra mig-ului atras de G)
		float vfN;// [m/s] 
		float viN;// [m/s] 
		float aN;//[m/s*s]	
		//-----------------------------------------------
		//Forta de reactiune a terenului
		float FreactiuneSol;
		bool flagDecolare;
		float rataDecolare;
		bool flagAterizare;
		float rataAterizare;
		//-----------------------------------------------
		//Forta portanta aripa
		float Pf;// [kgf] FortaPortantaFinala
		float Pfaripa;// [kgf] FortaPortantaFinala
		//float Pi;// [kgf] FortaPortantaInitiala
		float vfPf;//[m/s]
		float viPf;//[m/s]
		float aPf;//[m/s*s]
		float ny;//suprasarcina

		float Saripa;//[m*m] suprafata portanta a aripii		
		float SxMig;//[m*m] suprafata in sectiune longitudinala pe Ox
		float SyMig;//[m*m] suprafata in sectiune longitudinala pe Oy
		float vs;//[m/s] Viteza sunetului	
		float Cz;//coeficientul de portanta
		

		//-----------------------------------------------
		//Forta portanta stabilizator
		float Pfstabilizator;// [kgf] 
		float Sstabilizator;//[m*m] suprafata portanta a stabilizatorului
		float Czstabilizator;//coeficientul de portanta stabilizator
		//-----------------------------------------------
		//Forta portanta eleroane
		float Pfeleroane;// [kgf] 
		float Seleroane;//[m*m] suprafata portanta a stabilizatorului
		float Czeleroane;//coeficientul de portanta stabilizator
		//-----------------------------------------------
		//-----------------------------------------------
		//Forta portanta ampenaj vertical
		float Pfampenaj;// [kgf] 
		float Sampenaj;//[m*m] suprafata portanta a stabilizatorului
		float Czampenaj;//coeficientul de portanta stabilizator
		//-----------------------------------------------
		
		//Forte de rezistenta
		float Rxf;// [kgf] FortaDeRezistentaFinalaX
		float Rxi;// [kgf] FortaDeRezistentaInitialaX
		float vfRxf;//[m/s]
		float viRxf;//[m/s]
		float aRxf;//[m/s*s]
		float Crx;//coeficientul de rezistenta 

		float Ryf;// [kgf] FortaDeRezistentaFinalaY
		float Ryi;// [kgf] FortaDeRezistentaInitialaY
		float vfRyf;//[m/s]
		float viRyf;//[m/s]
		float aRyf;//[m/s*s]
		float Cry;//coeficientul de rezistenta 

		float Rzf;// [kgf] FortaDeRezistentaFinalaZ
		float Rzi;// [kgf] FortaDeRezistentaInitialaZ
		float vfRzf;//[m/s]
		float viRzf;//[m/s]
		float aRzf;//[m/s*s]
		float Crz;//coeficientul de rezistenta la inaintare
		
		//-------------------------------------------------
		//Forta de frecare
		float Ffrecare;//[kgf] forta de frecre cu PDA
		float vfFfrecare;//[m/s]
		float viFfrecare;//[m/s]
		float aFfrecare;//[m/s*s]
		float Cfrrepaus;//coeficientul de frecare de repaus
		float Cfr;//coeficientul de frecare

		//-------------------------------------------------
		//Forta de franare
		float Ffranare;//[kgf] forta de franare
		float vfFfranare;//[m/s]
		float viFfranare;//[m/s]
		float aFfranare;//[m/s*s]

		//-------------------------------------------------
		//Forta centrifuga
		float Fcfx;//[kgf]
		float Fcfy;//[kgf]
		float Fcfz;//[kgf]
		float razaFcf;
		//-----------------------------------------------
		//Rezultante		
		float RezultantaForte,RezultantaX,RezultantaY,RezultantaZ;
		float impulsMig,impulsMigX,impulsMigY,impulsMigZ;
		D3DXVECTOR3 vecRezultantaForte;
		//-----------------------------------------------
		//Parametri finali
		float tetaxRadiani;//[radiani] unghiul de inclinare a axei transversale orizontala (Ox) a
						   //mig-ului fata de planul orizontal		
		float tetayRadiani;//[radiani] unghiul de inclinare a axei transversale verticala (Oy) a
						   //mig-ului fata de planul orizontal		
		float tetazRadiani;//[radiani] unghiul de inclinare a axei longitudinale (Oz) a
						   //mig-ului fata de planul orizontal	
		
		//unghiuri de atitudine
		float unghiInclinare;

		float alphaAtacGrade;//[grade] 
		float alphaAtacRadiani;//[radiani] 
		float alphaAtacRotatieInFileuGrade;//[grade] 
		float alphaAtacRotatieInFileuRadiani;//[radiani] 
		float timpVirareInFileuri;
		float unghiRotireInFileu;

		float tetaxGrade;//[grade] 
		float tetayGrade;//[grade] 
		float tetazGrade;//[grade] 
				
		float gamaRadiani;//[radiani] unghiul de inclinare al mig-ului fata de planul 
		                  // longitudinal orizontal
		float gamaGrade;//[grade] unghiul de inclinare al mig-ului fata de planul 
		                // longitudinal orizontal

		//comenzi
		bool flagJoystick;
		bool flagStartEngine;
		bool flagStopEngine;
		
		bool flagBracareStabilizatorUpPress;
		bool flagBracareStabilizatorDownPress;
		bool flagBracareStabilizatorUpRelease;
		bool flagBracareStabilizatorDownRelease;

		bool flagBracareEleroaneStangaPress;
		bool flagBracareEleroaneDreaptaPress;
		bool flagBracareEleroaneStangaRelease;
		bool flagBracareEleroaneDreaptaRelease;

		bool flagBracareAmpenajStangaPress;
		bool flagBracareAmpenajDreaptaPress;
		bool flagBracareAmpenajStangaRelease;
		bool flagBracareAmpenajDreaptaRelease;

		bool flagFlapsBagat;
		bool flagFlapsTakeOff;			
		bool flagFlapsLanding;					
		bool sensFlapsDown;


		float unghiBracareStabilizator;//unghiul de bracare al stabilizatorului comandat
		float unghiBracareMinim;
		float unghiBracareMaxim;
		float rataEfortBracare;
		//float unghiBracareStabilizatorMaxim;//unghiul de bracare al stabilizatorului comandat maxim
		float unghiBracareEleroane;//unghiul de bracare al stabilizatorului comandat
		float pasEleroaneDecrease,pasEleroaneIncrease;
		float timpRotatieLongitudinala;
		float unghiBracareAmpenaj;//unghiul de bracare al stabilizatorului comandat
		float unghiRotatieTransversalaMig;//unghiul de bracare al mig-ului 
		float unghiRotatieTransversalaMigAnterior;//unghiul de bracare al mig-ului 
		//float unghiRotatieTransversalaMigMaxim;//unghiul de bracare al mig-ului 
		float unghiRotatieLongitudinalaMig;//unghiul de  rotatie long. al mig-ului
		float unghiRotatieVerticalaMig;//unghiul de  rotatie long. al mig-ului
		float rtx,rty,rtz,rlx,rly,rlz,rvx,rvy,rvz;

		float bratCg,bratCp;
		float unghiBalansForteCg,unghiBalansForteCp;
		float ForteCg,ForteCp;

		//roti
		float unghiRotatieRoti,vUnghiularaRoti;

		//perturbatii
		bool kLong;		
		float unghiRotatieLongitudinalaMigPerturbatii;
		bool kTran;
		bool flagStartPeturbatii;
		

		float axMig; //[m/s*s]acceleratia pe axa Ox a Mig-ului
		float ayMig; //[m/s*s]acceleratia pe axa Oy a Mig-ului
		float azMig; //[m/s*s]acceleratia de traiectorie, pe axa Oz a Mig-ului
		float aVertMig;//[m/s*s] AcceleratiaVerticalaMig
		float aMig;
		
		float vxfMig; //[m/s]viteza finala pe axa Ox a Mig-ului
		float vxiMig; //[m/s]viteza initiala pe axa Ox a Mig-ului
		float vyfMig; //[m/s]viteza finala pe axa Oy a Mig-ului
		float vyiMig; //[m/s]viteza initiala pe axa Oy a Mig-ului
		float vzfMig; //[m/s]viteza de traiectorie finala, pe axa Oz a Mig-ului
		float vziMig; //[m/s]viteza de traiectorie initiala, pe axa Oz a Mig-ului	

		D3DXVECTOR3 vecOrigine;
		D3DXVECTOR3 vecVxfMig;
		D3DXVECTOR3 vecVyfMig;
		D3DXVECTOR3 vecVzfMig;

		D3DXVECTOR3 vecVxfMigLocal;
		D3DXVECTOR3 vecVyfMigLocal;
		D3DXVECTOR3 vecVzfMigLocal;

		D3DXVECTOR3 vecVxyfMigLocal;
		D3DXVECTOR3 vecVxyzfMigLocal;
		D3DXVECTOR3 vecVxyzfMigLocalVechi;
		D3DXVECTOR3 vecVxyzfMigLocalNormalizat;
		float unghiVitezeLocale;

		float unghiVecVitMigOxLocal;
		float unghiVecVitMigOyLocal;
		float unghiVecVitMigOzLocal;
		float viMig;
		float vMig;
		float vVertMig;//[m/s] VitezaVerticalaMig

		float M;//[m/s]
		float altM;//[m] altitudinea in metri		
		float altUnitWorld;//altitudinea in unitati World=VectorCentruRoti.y =VectorCentruRoti.y		
		float T;//[C]
		float patm;//[pound/feet*feet] presiunea atmosferica
		float roAer;//[Kg/m*m*m] densitatea aerului

		float txMig; //[m]deplasare pe axa Ox a Mig-ului
		float tyMig; //[m]deplasare pe axa Oy a Mig-ului
		float tzMig; //[m]deplasare longitudinala Mig (pe axa Oz)


		D3DXVECTOR3 origG;// OrigineFortaDeGreutate
		D3DXVECTOR3 varfG;// VarfFortaDeGreutate
		D3DXVECTOR3 origT;// OrigineFortaDeTractiune
		D3DXVECTOR3 varfT;// VarfFortaDeTractiune
		D3DXVECTOR3 origP;// OrigineFortaPortanta
		D3DXVECTOR3 varfP;// VarfFortaPortanta

//functii publice
public:
		Fizica();

		void Init();
		void InitForte();
		void InitComenzi();

		void CalculeazaDinamicaForteiDeTractiune();		
		void CalculeazaDinamicaForteiDeGreutate();
		void CalculeazaDinamicaForteiDeFrecare();
		void CalculeazaDinamicaForteiDeReactiuneTeren();
		void CalculeazaDinamicaForteiPortante();		
		void CalculeazaDinamicaForteiCentrifuge();
		void CalculeazaDinamicaForteiDeRezistentaRx();
		void CalculeazaDinamicaForteiDeRezistentaRy();
		void CalculeazaDinamicaForteiDeRezistentaRz();		
		void CalculeazaAlpha();
		void CalculeazaCzInfunctieDeMSiAlpha();
		void CalculeazaM();				
		void CalculeazaSuprasarcina();
				
		void SalvezaMarimiInainteDeTestColiziuni();				
		void VectoriTestatiPentruColiziune();
		void VectoriRotiPentruColiziune();
		//bool TestColiziuni(LPD3DXBASEMESH pMesh,D3DXMATRIX *matMig);
		bool TestColiziuni(D3DXMATRIX *pMatMig,
						   LPD3DXMESH pMeshDeTestat,LPD3DXMESH pMesh,
						   StructVectorTestat  TablouVectoriTestati[10]);

		void InitColiziuni(LPD3DXMESH pMesh,
						   StructVectorTestat  TablouVectoriTestati[10]);

		bool TestColiziuniNew(D3DXMATRIX *pMatMig,
							  LPD3DXMESH pMeshDeTestat,LPD3DXMESH pMesh,
							  StructVectorTestat  TablouVectoriTestati[10]);

		void BilantulFortelorOx();
		void BilantulFortelorOy();
		void BilantulFortelorOz();	
		
		void CalculeazaVectorVitezaMig(D3DXMATRIX *pMatMig);
		void CalcVectorRezultantaForte();		

		void CalculeazaUnghiRotatieTransversalaMig();
		void CalculeazaUnghiRotatieLongitudinalaMig();
		void CalculeazaUnghiRotatieVerticalaMig();
		void CalculeazaUnghiRotatieRoti();
		void Comenzi();

		void CalculeazaParametriAerodinamici(D3DXMATRIX *pMatMig,
											 LPD3DXMESH pMesh);
		
		
		
		
private:
		
		
		
//date publice
public:	
	
private:
		
};

