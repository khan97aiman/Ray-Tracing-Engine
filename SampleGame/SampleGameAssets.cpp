#include "SampleGameAssets.h"

using namespace NCL;
using namespace Assets;

void SampleGameAssets::LoadMeshes() {
	meshes.insert(std::make_pair("floorMesh", loader->LoadMesh("BasicLVL1.msh")));
	meshes.insert(std::make_pair("cubeMesh", loader->LoadMesh("cube.msh")));
	meshes.insert(std::make_pair("mainChar", loader->LoadMesh("Aj_TPose.msh")));
	meshes.insert(std::make_pair("sphereMesh", loader->LoadMesh("sphere.msh")));
	meshes.insert(std::make_pair("capsuleMesh", loader->LoadMesh("capsule.msh")));
	meshes.insert(std::make_pair("gunMesh", loader->LoadMesh("PaintingGun.msh")));
	meshes.insert(std::make_pair("quadMesh", loader->LoadMesh(MeshType::Quad)));

	meshes.insert(std::make_pair("AiMesh", loader->LoadMesh("X_Bot.msh")));
}

void SampleGameAssets::LoadMeshMaterials() {
	meshMaterials.insert(std::make_pair("redMainCharMat", loader->LoadMeshMaterial("red_Aj_TPose.mat")));
}

void SampleGameAssets::LoadMeshAnimations() {
	meshAnimations.insert(std::make_pair("mainCharTauntAnim", std::make_unique<MeshAnimation>("Taunt.anm")));
	meshAnimations.insert(std::make_pair("mainCharIdleAnim", std::make_unique<MeshAnimation>("AJIdle.anm")));
	meshAnimations.insert(std::make_pair("mainCharRunAnim", std::make_unique<MeshAnimation>("AJRun.anm")));
}

void SampleGameAssets::LoadTextures() {
	textures.insert(std::make_pair("basicTex", loader->LoadTexture("checkerboard.png")));
	textures.insert(std::make_pair("loadingTex", loader->LoadTexture("loadingSprites.png")));
	textures.insert(std::make_pair("gunFocusTex", loader->LoadTexture("gunFocusPoint.png")));
	textures.insert(std::make_pair("splashScreenTex", loader->LoadTexture("Screens/bg.png"))); 
	textures.insert(std::make_pair("mainMenuScreenTex", loader->LoadTexture("Screens/bg2.png")));
	textures.insert(std::make_pair("gameOverScreenTex", loader->LoadTexture("Screens/bg3.jpg")));
}

void SampleGameAssets::LoadShaders() {
#ifdef _WIN32
	shaders.insert(std::make_pair("basicShader", loader->LoadShader("scene.vert", "scene.frag")));
	shaders.insert(std::make_pair("terrainShader", loader->LoadShader("terrain.vert", "terrain.frag")));
	shaders.insert(std::make_pair("skinningShader", loader->LoadShader("skinning.vert", "character.frag")));
	shaders.insert(std::make_pair("SecondskinningShader", loader->LoadShader("skinning.vert", "character.frag")));
	shaders.insert(std::make_pair("THIRDskinningShader", loader->LoadShader("skinning.vert", "character.frag")));
	shaders.insert(std::make_pair("screenShader", loader->LoadShader("screen.vert", "screen.frag")));
	shaders.insert(std::make_pair("inkShader", loader->LoadShader("ink.vert", "ink.frag")));
	shaders.insert(std::make_pair("debugShader", loader->LoadShader("Debug.vert", "Debug.frag")));
	shaders.insert(std::make_pair("hudShader", loader->LoadShader("hud.vert", "hud.frag")));
#endif // _WIN32
#ifdef __ORBIS__
	shaders.insert(std::make_pair("basicShader", loader->LoadShader("VertexShader_vv.sb", "PixelShader_p.sb")));
	shaders.insert(std::make_pair("skinningShader", loader->LoadShader("VertexShader_vv.sb", "PixelShader_p.sb")));
	shaders.insert(std::make_pair("SecondskinningShader", loader->LoadShader("VertexShader_vv.sb", "PixelShader_p.sb")));
	shaders.insert(std::make_pair("THIRDskinningShader", loader->LoadShader("VertexShader_vv.sb", "PixelShader_p.sb")));
	shaders.insert(std::make_pair("screenShader", loader->LoadShader("screen_vv.sb", "simplePixel_p.sb")));
	shaders.insert(std::make_pair("inkShader", loader->LoadShader("VertexShader_vv.sb", "PixelShader_p.sb")));
	shaders.insert(std::make_pair("debugShader", loader->LoadShader("screen_vv.sb", "simplePixel_p.sb")));
	shaders.insert(std::make_pair("hudShader", loader->LoadShader("hud_vv.sb", "simplePixel_p.sb")));
#endif // __ORBIS__
}