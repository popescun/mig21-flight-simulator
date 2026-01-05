#include "d3d8.h"
#include "d3d8types.h"
#include "D3dx8math.h"
#include "D3dx8mesh.h"

#include <vector>

class Mesh{
//functii publice
public:
		Mesh();
		LPD3DXMESH LoadFromfile(HWND hWnd,LPSTR pFilename,DWORD Options,LPDIRECT3DDEVICE8 pDevice,
						  LPD3DXBUFFER* ppAdjacency,LPD3DXBUFFER* ppMaterials,
						  PDWORD pNumMaterials);
		void Load(HWND hWnd,LPDIRECT3DDEVICE8 pDevice,unsigned int NrMeshe);
		
		
private:
		
		
		
//date publice
public:
		LPSTR pFileNames[20];
		LPD3DXMESH pMeshes[20];
		LPD3DXMATERIAL mesh_materials_[20];
		DWORD mesh_material_number_[20];
		std::vector<LPDIRECT3DTEXTURE8> mesh_textures_[20];
						
private:
		
};