#pragma once
#include "AssetLoader.h"

namespace NCL::Assets {
	class VulkanAssetLoader : public AssetLoader {
	public:
		VulkanAssetLoader(RendererBase* renderer) : AssetLoader(renderer) {};
		virtual TextureBase* LoadTexture(const std::string& name) override;
		virtual MeshGeometry* LoadMesh(const string& name) override;
		virtual MeshGeometry* LoadMesh(const MeshType& meshType) override;
		virtual ShaderBase* LoadShader(const string& vertex, const string& fragment) override;
		virtual MeshGeometry* LoadFlatMesh(int hVertexCount = 128, int wVertexCount = 128) override;
		virtual MeshGeometry* LoadHeightMap(const std::string& filename, int heightMultiplier = 10) override;
	};

	// Concrete factory for creating OpenGL Asset Loader
	class VulkanAssetLoaderFactory : public AssetLoaderFactory {
	public:
		AssetLoader* CreateAssetLoader(RendererBase* renderer) override {
			return new VulkanAssetLoader(renderer);
		}
	};


}