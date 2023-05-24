#pragma once
#include <GameAssets.h>

namespace NCL {
	using namespace Rendering;
	class SampleGameAssets : public GameAssets {
	public:
		SampleGameAssets(Assets::AssetLoader* loader) : GameAssets(loader) { Load(); }
	protected:
		virtual void LoadMeshes() override;
		virtual void LoadMeshMaterials() override;
		virtual void LoadMeshAnimations() override;
		virtual void LoadTextures() override;
		virtual void LoadShaders() override;
	};
}