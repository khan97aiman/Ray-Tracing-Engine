#include "VulkanAssetLoader.h"
#include "VulkanTexture.h"
#include "VulkanMesh.h"
#include "VulkanShader.h"
#include "VulkanShaderBuilder.h"
#include "VulkanRenderer.h"

using namespace NCL;
using namespace Assets;

TextureBase* VulkanAssetLoader::LoadTexture(const std::string& name) {
	VulkanTexture* t = new VulkanTexture(name);
	((VulkanRenderer*)renderer)->WriteTextureToDescriptorSet(t);
	return t;
}

MeshGeometry* VulkanAssetLoader::LoadMesh(const string& name) {
	VulkanMesh* mesh = new VulkanMesh(name);
	mesh->SetPrimitiveType(GeometryPrimitive::Triangles);
	mesh->SetDebugName(name);
	mesh->UploadToGPU(renderer);
	return mesh;
}

MeshGeometry* VulkanAssetLoader::LoadMesh(const MeshType& meshType) {
	switch (meshType) {
	case MeshType::Quad:
		return VulkanMesh::GenerateQuad(renderer).get();
	default:
		return nullptr;
	}
}

ShaderBase* VulkanAssetLoader::LoadShader(const string& vertex, const string& fragment) {
	return VulkanShaderBuilder("Shader!")
		.WithVertexBinary(vertex + ".spv")
		.WithFragmentBinary(fragment + ".spv")
		.Build(((VulkanRenderer*)renderer)->GetDevice()).release();
	return nullptr;
}

MeshGeometry* VulkanAssetLoader::LoadFlatMesh(int hVertexCount, int wVertexCount) {
	return VulkanMesh::GenerateFlatMesh(renderer, hVertexCount, wVertexCount).get();
}

MeshGeometry* VulkanAssetLoader::LoadHeightMap(const std::string& filename, int heightMultiplier) {
	return VulkanMesh::GenerateHeightMap(renderer, filename, heightMultiplier).get();
}
