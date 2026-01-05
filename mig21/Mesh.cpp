#include "Mesh.h"

#include <string>
#include <unordered_map>

Mesh::Mesh()
{
	ZeroMemory(pFileNames,sizeof(pFileNames));
	ZeroMemory(pMeshes,sizeof(pMeshes));

}


LPD3DXMESH Mesh::LoadFromfile(HWND hWnd,LPSTR pFilename,DWORD Options,LPDIRECT3DDEVICE8 pDevice,
						  LPD3DXBUFFER* ppAdjacency,LPD3DXBUFFER* ppMaterials,
						  PDWORD pNumMaterials)
{				
	    	
	 LPD3DXMESH pMesh=NULL;

	 if(!FAILED(D3DXLoadMeshFromX(pFilename,
								Options,
								pDevice,
								ppAdjacency,
								ppMaterials,
								pNumMaterials,
								&pMesh)))	
	 {
		 //D3DXComputeNormals(pMesh);
		 //pMesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT|D3DXMESHOPT_COMPACT ,
		 //					  NULL,NULL,NULL,NULL);		 
	 }	
	 else
		 MessageBox(hWnd,"Nu este bine!!!", NULL, MB_OK);

	 return pMesh;
}

//HRESULT LoadMeshFromAFile()
//{
//	LPD3DXBUFFER materials_buffer;
//	std::unordered_map<std::string, LPDIRECT3DTEXTURE8> texture_map;
//
//	//Load
//	LPSTR filePath;
//	//filePath="mig21remodelat.x";
//	filePath = "meshes/new_mig21.x";
//	if (FAILED(D3DXLoadMeshFromX(filePath,
//		D3DXMESH_SYSTEMMEM | D3DXMESH_DYNAMIC | D3DXMESH_DONOTCLIP,
//		g_pd3dDevice,
//		NULL,
//		&materials_buffer,
//		&num_materials,
//		&texMesh))) {
//		return E_FAIL;
//	}
//
//	materials = (D3DXMATERIAL*)materials_buffer->GetBufferPointer();
//
//	textures.resize(num_materials);
//
//	texMesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT, NULL, NULL, NULL, NULL);
//
//	for (UINT i = 0; i < num_materials; ++i)
//	{
//		auto it = texture_map.find(materials[i].pTextureFilename);
//		if (it != texture_map.end()) {
//			textures[i] = it->second;
//			continue;
//		}
//
//		LPDIRECT3DTEXTURE8 texture;
//		if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice,
//			materials[i].pTextureFilename,
//			&texture))) {
//			textures[i] = nullptr;
//			continue;
//		}
//		texture_map[materials[i].pTextureFilename] = texture;
//		textures[i] = texture;
//	}
//
//	return S_OK;
//}

void Mesh::Load(HWND hWnd,LPDIRECT3DDEVICE8 pDevice,unsigned int NrMeshe)							   							   
{					    	
	DWORD Options=D3DXMESH_MANAGED|D3DXMESH_SYSTEMMEM|D3DXMESH_DYNAMIC|D3DXMESH_DONOTCLIP;	
	//D3DXMESH_DYNAMIC|D3DXMESH_DONOTCLIP|
	LPD3DXBUFFER* ppAdjacency=NULL;
	LPD3DXBUFFER* ppMaterials=NULL;
	DWORD material_number;

	LPD3DXBUFFER materials_buffer;
	std::unordered_map<std::string, LPDIRECT3DTEXTURE8> texture_map;

	for(unsigned int i=0;i<=NrMeshe-1;i++)
		if((pMeshes[i]=LoadFromfile(hWnd,pFileNames[i],
							Options,
							pDevice,
							ppAdjacency,
							&materials_buffer,
							&material_number
							)) != nullptr)
		 {
			 /*pMeshes[i]->OptimizeInplace(D3DXMESHOPT_COMPACT|D3DXMESHOPT_ATTRSORT,
								  NULL,NULL,NULL,NULL);	*/	

			mesh_material_number_[i] = material_number;

			 mesh_materials_[i] = (D3DXMATERIAL*)materials_buffer->GetBufferPointer();

			 mesh_textures_[i].resize(material_number);

			 pMeshes[i]->OptimizeInplace(D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT, NULL, NULL, NULL, NULL);

			 if (i != 1) {
				 continue;
			 }

			 // for orginal models
			 //continue;

			 for (UINT j = 0; j < material_number; ++j)
			 {
				 auto it = texture_map.find(mesh_materials_[i][j].pTextureFilename);
				 if (it != texture_map.end()) {
					 mesh_textures_[i][j] = it->second;
					 continue;
				 }

				 LPDIRECT3DTEXTURE8 texture;
				 if (FAILED(D3DXCreateTextureFromFile(pDevice,
					 mesh_materials_[i][j].pTextureFilename,
					 &texture))) {
					 mesh_textures_[i][j] = nullptr;
					 continue;
				 }
				 texture_map[mesh_materials_[i][j].pTextureFilename] = texture;
				 mesh_textures_[i][j] = texture;
			 }
		 }		 
}