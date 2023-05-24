#include "GameAssets.h"
#include "Assets.h"

using namespace NCL;
using namespace Assets;

GameAssets::GameAssets(Assets::AssetLoader* loader) {
	this->loader = loader;
}

void GameAssets::Load()
{
	// Clear just in case
	meshes.clear();
	meshAnimations.clear();
	meshMaterials.clear();
	shaders.clear();
	textures.clear();

	LoadTextures();
	LoadMeshes();
	LoadMeshMaterials();
	LoadMeshAnimations();
	LoadShaders();
}

MeshGeometry* NCL::GameAssets::GetMesh(const std::string& identifier) const {
	return meshes.count(identifier) ? meshes.at(identifier).get() : nullptr;
}

MeshMaterial* NCL::GameAssets::GetMeshMaterial(const std::string& identifier) const {
	return meshMaterials.count(identifier) ? meshMaterials.at(identifier).get() : nullptr;
}

MeshAnimation* NCL::GameAssets::GetMeshAnimation(const std::string& identifier) const {
	return meshAnimations.count(identifier) ? meshAnimations.at(identifier).get() : nullptr;
}

TextureBase* NCL::GameAssets::GetTexture(const std::string& identifier) const {
	return textures.count(identifier) ? textures.at(identifier).get() : nullptr;
}

ShaderBase* NCL::GameAssets::GetShader(const std::string& identifier) const {
	return shaders.count(identifier) ? shaders.at(identifier).get() : nullptr;
}