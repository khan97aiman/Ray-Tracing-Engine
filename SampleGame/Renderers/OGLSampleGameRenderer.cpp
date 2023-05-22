#ifdef _WIN32
#include "OGLSampleGameRenderer.h"
#include <Win32Window.h>
#include "GameWorld.h"
#include <OGLTexture.h>
#include "OGLShader.h"
#include "Camera.h"
#include "Debug.h"

using namespace NCL;
using namespace CSC8599;

OGLSampleGameRenderer::OGLSampleGameRenderer(Window& w) : OGLRenderer(w) {
	//Set up the light properties
	lightColour = Vector4(0.8f, 0.8f, 0.5f, 1.0f);
	lightRadius = 1000.0f;
	lightPosition = Vector3(0.0f, 20.0f, 0.0f);
	SetDebugRenderers();
}


void OGLSampleGameRenderer::SetDebugRenderers() {
	debugLineRenderer = new DebugLinesRenderer();
	debugTextRenderer = new DebugTextRenderer();

	SetDebugStringBufferSizes(10000);
	SetDebugLineBufferSizes(1000);
}

void OGLSampleGameRenderer::RenderFrame() {
	
	if (boundScreen) {
		if (boundScreen->GetScreenType() == ScreenType::GameScreen) {
			BuildObjectList();
			SortObjectList();
			RenderGameScreen();

			NewRenderLines();
			NewRenderText();
		}
		else {
			RenderBasicScreen();
		}
	}
}

void OGLSampleGameRenderer::RenderBasicScreen() { //change this to render static obj
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glViewport(0, 0, windowWidth, windowHeight);
	RenderObject* r = boundScreen->GetSceneNode()->GetRenderObject();
	BindShader(r->GetShader());
	BindMesh(r->GetMesh());
	BindTextureToShader(r->GetDefaultTexture(), "mainTex", 0);
	DrawBoundMesh();
	//boundScreen->RenderMenu();
	// guiInterface->Render(boundScreen->GetGuiFrame());
}
void OGLSampleGameRenderer::RenderGameScreen() { //change this to RenderScreen
	rendererStartTime = std::chrono::high_resolution_clock::now();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//send camera things and light things to shader
	boundScreen->GetSceneNode()->OperateOnCameras(
		[&](Camera* cam) {
			cam->SetPerspectiveCameraParameters(Window::GetWindow()->GetScreenAspect() * cam->GetAspectMultiplier());
			glViewport(cam->GetVpStartPos().x * windowWidth, cam->GetVpStartPos().y * windowWidth, windowWidth * cam->GetVpSize().x, windowHeight * cam->GetVpSize().y);
			Matrix4 viewMatrix = cam->BuildViewMatrix();
			Matrix4 projMatrix = cam->BuildProjectionMatrix();
			Vector3 camPos = cam->GetPosition();
			ShaderVariablesLocations locations;
			OGLShader* activeShader = nullptr;
			for (const auto& i : activeObjects) {
				if (i->GetIsOccluded()) {
					glEnable(GL_CULL_FACE);
					glCullFace(GL_BACK);
					glEnable(GL_DEPTH_TEST);
				}
				else {
					glDisable(GL_CULL_FACE);
					glDisable(GL_DEPTH_TEST);
				}
				OGLShader* shader = (OGLShader*)(i)->GetShader();
				BindShader(shader);
				if (activeShader != shader) {
					locations.projLocation = glGetUniformLocation(shader->GetProgramID(), "projMatrix");
					locations.viewLocation = glGetUniformLocation(shader->GetProgramID(), "viewMatrix");
					locations.shadowLocation = glGetUniformLocation(shader->GetProgramID(), "shadowMatrix");
					locations.colourLocation = glGetUniformLocation(shader->GetProgramID(), "objectColour");
					locations.hasVColLocation = glGetUniformLocation(shader->GetProgramID(), "hasVertexColours");
					locations.hasTexLocation = glGetUniformLocation(shader->GetProgramID(), "hasTexture");
					locations.useFogLocation = glGetUniformLocation(shader->GetProgramID(), "useFog");
					locations.fogColourLocation = glGetUniformLocation(shader->GetProgramID(), "fogColour");
					locations.skyboxTexLocation = glGetUniformLocation(shader->GetProgramID(), "skyboxTex");
					locations.lightPosLocation = glGetUniformLocation(shader->GetProgramID(), "lightPos");
					locations.lightColourLocation = glGetUniformLocation(shader->GetProgramID(), "lightColour");
					locations.lightRadiusLocation = glGetUniformLocation(shader->GetProgramID(), "lightRadius");
					locations.cameraLocation = glGetUniformLocation(shader->GetProgramID(), "cameraPos");
					locations.jointsLocation = glGetUniformLocation(shader->GetProgramID(), "joints");
					locations.shadowTexLocation = glGetUniformLocation(shader->GetProgramID(), "shadowTex");


					glUniform3fv(locations.cameraLocation, 1, camPos.array);
					glUniformMatrix4fv(locations.projLocation, 1, false, (float*)&projMatrix);
					glUniformMatrix4fv(locations.viewLocation, 1, false, (float*)&viewMatrix);
					glUniform3fv(locations.lightPosLocation, 1, (float*)&lightPosition);
					glUniform4fv(locations.lightColourLocation, 1, (float*)&lightColour);
					glUniform1f(locations.lightRadiusLocation, lightRadius);
			
					activeShader = shader;
				}

				SendModelMatrices(shader, i);

				Vector4 colour = i->GetColour();
				glUniform4fv(locations.colourLocation, 1, colour.array);

				glUniform1i(locations.hasVColLocation, !(*i).GetMesh()->GetColourData().empty());

				if (i->isSingleTextured()) {
					RenderWithDefaultTexture(locations, i);
				}
				else {
					RenderWithMultipleTexture(locations, i);
				}
				if (i->IsRigged()) {
					vector<Matrix4> frameMatrices;
					i->GetFrameMatrices(frameMatrices);
					glUniformMatrix4fv(locations.jointsLocation, frameMatrices.size(), false, (float*)frameMatrices.data());
				}
			}
		}
	);

	RenderDebugInformation();
	boundScreen->RenderMenu();
}


void OGLSampleGameRenderer::BuildObjectList() {
	activeObjects.clear();

	boundScreen->GetSceneNode()->GetWorld()->OperateOnContents(
		[&](GameObject* o) {
			if (o->IsActive()) {
				const RenderObject* g = o->GetRenderObject();
				if (g) {
					activeObjects.emplace_back(g);
				}
			}
		}
	);
}

void OGLSampleGameRenderer::SortObjectList() {

}

void OGLSampleGameRenderer::SendModelMatrices(OGLShader* shader, const RenderObject* r) {
	unsigned int numInstances = r->GetInstanceCount();
	if (r->GetIsInstanced()) {
		if (numInstances == 0) {
			return;
		}
		std::vector<Transform*> transforms = r->GetTransforms();
		for (int i = 0; i < numInstances; i++) {
			std::string index = std::to_string(i);
			Matrix4 modelMatrix = transforms[i]->GetMatrix();
			int modelArrayLocation = glGetUniformLocation(shader->GetProgramID(), ("modelMatrices[" + index + "]").c_str());
			glUniformMatrix4fv(modelArrayLocation, 1, false, (float*)&modelMatrix);
		}
	}
	else {
		Matrix4 modelMatrix = r->GetTransform()->GetMatrix();
		int modelLocation = glGetUniformLocation(shader->GetProgramID(), "modelMatrix");
		glUniformMatrix4fv(modelLocation, 1, false, (float*)&modelMatrix);
	}
}

void OGLSampleGameRenderer::RenderWithDefaultTexture(const ShaderVariablesLocations& locations, const RenderObject* r) {
	unsigned int numInstances = r->GetInstanceCount();
	glUniform1i(locations.hasTexLocation, r->GetDefaultTexture() ? 1 : 0);
	BindMesh(r->GetMesh());
	BindTextureToShader(r->GetDefaultTexture(), "mainTex", 0);
	int layercount = r->GetMesh()->GetSubMeshCount();
	int index = 0;
	do {
		DrawBoundMesh(index++, numInstances);
	} while (index < layercount);
}

void OGLSampleGameRenderer::RenderWithMultipleTexture(const ShaderVariablesLocations& locations, const RenderObject* r) {
	unsigned int numInstances = r->GetInstanceCount();
	BindMesh(r->GetMesh());
	int layercount = r->GetMesh()->GetSubMeshCount();
	int index = 0;
	int texunit = 0;
	do {
		glUniform1i(locations.hasTexLocation, r->GetTextures(index).size() ? 1 : 0);
		//for the current submesh, get the vector of textures and send them to shader
		std::vector<std::pair<std::string, TextureBase*>> submeshtextures = r->GetTextures(index);
		
		for (const auto& texturepairs : submeshtextures) {
			BindTextureToShader(texturepairs.second, texturepairs.first, texunit);
			texunit++;
		}
		DrawBoundMesh(index++, numInstances);
	} while (index < layercount);
}

//Debug methods

void OGLSampleGameRenderer::RenderDebugInformation() const {
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	if (boundScreen->GetSceneNode()->GetPhysicsWorld() && boundScreen->GetSceneNode()->GetPhysicsWorld()->getIsDebugRenderingEnabled() )  {
		reactphysics3d::DebugRenderer* debugRenderer = &boundScreen->GetSceneNode()->GetPhysicsWorld()->getDebugRenderer();

		//render triangles
		int numTri = debugRenderer->getNbTriangles();
		if (numTri) {
			const reactphysics3d::DebugRenderer::DebugTriangle* tri = debugRenderer->getTrianglesArray();
			for (int i = 0; i < numTri; i++) {
				Debug::DrawTriangle(tri->point1, tri->point2, tri->point3, Debug::YELLOW);
				tri++;
			}
		}

		//render lines
		int numLines = debugRenderer->getNbLines();
		if (numLines) {
			const reactphysics3d::DebugRenderer::DebugLine* line = debugRenderer->getLinesArray();
			for (int i = 0; i < numLines; i++) {
				Debug::DrawLine(line->point1, line->point2, Debug::CYAN);
				line++;
			}
		}
	}
}

void OGLSampleGameRenderer::NewRenderText() {
	glDisable(GL_CULL_FACE); //Todo - text indices are going the wrong way...
	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	const std::vector<Debug::DebugStringEntry>& strings = Debug::GetDebugStrings();
	if (strings.empty()) {
		return;
	}

	BindShader(debugShader);

	OGLTexture* t = (OGLTexture*)Debug::GetDebugFont()->GetTexture();

	if (t) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, t->GetObjectID());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glBindTexture(GL_TEXTURE_2D, 0);
		BindTextureToShader(t, "mainTex", 0);
	}
	Matrix4 proj = Matrix4::Orthographic(0.0, 100.0f, 100, 0, -1.0f, 1.0f);

	int matSlot = glGetUniformLocation(((OGLShader*)debugShader)->GetProgramID(), "viewProjMatrix");
	glUniformMatrix4fv(matSlot, 1, false, (float*)proj.array);

	GLuint texSlot = glGetUniformLocation(((OGLShader*)debugShader)->GetProgramID(), "useTexture");
	glUniform1i(texSlot, 1);

	debugTextPos.clear();
	debugTextColours.clear();
	debugTextUVs.clear();

	int frameVertCount = 0;
	for (const auto& s : strings) {
		frameVertCount += Debug::GetDebugFont()->GetVertexCountForString(s.data);
	}
	SetDebugStringBufferSizes(frameVertCount);

	for (const auto& s : strings) {
		float size = 20.0f;
		Debug::GetDebugFont()->BuildVerticesForString(s.data, s.position, s.colour, size, debugTextPos, debugTextUVs, debugTextColours);
	}


	glBindBuffer(GL_ARRAY_BUFFER, debugTextRenderer->vertVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, frameVertCount * sizeof(Vector3), debugTextPos.data());
	glBindBuffer(GL_ARRAY_BUFFER, debugTextRenderer->colourVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, frameVertCount * sizeof(Vector4), debugTextColours.data());
	glBindBuffer(GL_ARRAY_BUFFER, debugTextRenderer->texCoordVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, frameVertCount * sizeof(Vector2), debugTextUVs.data());

	glBindVertexArray(debugTextRenderer->vao);
	glDrawArrays(GL_TRIANGLES, 0, frameVertCount);
	glBindVertexArray(0);
}

void OGLSampleGameRenderer::NewRenderLines() {
	if (!debugShader) return;
	const std::vector<Debug::DebugLineEntry>& lines = Debug::GetDebugLines();
	if (lines.empty()) {
		return;
	}

	boundScreen->GetSceneNode()->OperateOnCameras(
		[&](Camera* cam) {
			cam->SetPerspectiveCameraParameters(Window::GetWindow()->GetScreenAspect() * cam->GetAspectMultiplier());
			glViewport(cam->GetVpStartPos().x * windowWidth, cam->GetVpStartPos().y * windowWidth, windowWidth * cam->GetVpSize().x, windowHeight * cam->GetVpSize().y);
			Matrix4 viewMatrix = cam->BuildViewMatrix();
			Matrix4 projMatrix = cam->BuildProjectionMatrix();

			Matrix4 viewProj = projMatrix * viewMatrix;
			BindShader(debugShader);
			int matSlot = glGetUniformLocation(((OGLShader*)debugShader)->GetProgramID(), "viewProjMatrix");
			GLuint texSlot = glGetUniformLocation(((OGLShader*)debugShader)->GetProgramID(), "useTexture");
			glUniform1i(texSlot, 0);

			glUniformMatrix4fv(matSlot, 1, false, (float*)viewProj.array);

			debugLineData.clear();

			int frameLineCount = lines.size() * 2;

			SetDebugLineBufferSizes(frameLineCount);

			glBindBuffer(GL_ARRAY_BUFFER, debugLineRenderer->vertVbo);
			glBufferSubData(GL_ARRAY_BUFFER, 0, lines.size() * sizeof(Debug::DebugLineEntry), lines.data());


			glBindVertexArray(debugLineRenderer->vao);
			glDrawArrays(GL_LINES, 0, frameLineCount);
			glBindVertexArray(0);
		});
}

void OGLSampleGameRenderer::SetDebugStringBufferSizes(size_t newVertCount) {
	if (newVertCount > debugTextRenderer->count) {
		debugTextRenderer->count = newVertCount;

		glBindBuffer(GL_ARRAY_BUFFER, debugTextRenderer->vertVBO);
		glBufferData(GL_ARRAY_BUFFER, debugTextRenderer->count * sizeof(Vector3), nullptr, GL_DYNAMIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, debugTextRenderer->colourVBO);
		glBufferData(GL_ARRAY_BUFFER, debugTextRenderer->count * sizeof(Vector4), nullptr, GL_DYNAMIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, debugTextRenderer->texCoordVBO);
		glBufferData(GL_ARRAY_BUFFER, debugTextRenderer->count * sizeof(Vector2), nullptr, GL_DYNAMIC_DRAW);

		debugTextPos.reserve(debugTextRenderer->count);
		debugTextColours.reserve(debugTextRenderer->count);
		debugTextUVs.reserve(debugTextRenderer->count);

		glBindVertexArray(debugTextRenderer->vao);

		glVertexAttribFormat(0, 3, GL_FLOAT, false, 0);
		glVertexAttribBinding(0, 0);
		glBindVertexBuffer(0, debugTextRenderer->vertVBO, 0, sizeof(Vector3));

		glVertexAttribFormat(1, 4, GL_FLOAT, false, 0);
		glVertexAttribBinding(1, 1);
		glBindVertexBuffer(1, debugTextRenderer->colourVBO, 0, sizeof(Vector4));

		glVertexAttribFormat(2, 2, GL_FLOAT, false, 0);
		glVertexAttribBinding(2, 2);
		glBindVertexBuffer(2, debugTextRenderer->texCoordVBO, 0, sizeof(Vector2));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		glBindVertexArray(0);
	}
}

void OGLSampleGameRenderer::SetDebugLineBufferSizes(size_t newVertCount) {
	if (newVertCount > debugLineRenderer->count) {
		debugLineRenderer->count = newVertCount;

		glBindBuffer(GL_ARRAY_BUFFER, debugLineRenderer->vertVbo);
		glBufferData(GL_ARRAY_BUFFER, debugLineRenderer->count * sizeof(Debug::DebugLineEntry), nullptr, GL_DYNAMIC_DRAW);

		debugLineData.reserve(debugLineRenderer->count);

		glBindVertexArray(debugLineRenderer->vao);

		int realStride = sizeof(Debug::DebugLineEntry) / 2;

		glVertexAttribFormat(0, 3, GL_FLOAT, false, offsetof(Debug::DebugLineEntry, start));
		glVertexAttribBinding(0, 0);
		glBindVertexBuffer(0, debugLineRenderer->vertVbo, 0, realStride);

		glVertexAttribFormat(1, 4, GL_FLOAT, false, offsetof(Debug::DebugLineEntry, colourA));
		glVertexAttribBinding(1, 0);
		glBindVertexBuffer(1, debugLineRenderer->vertVbo, sizeof(Vector4), realStride);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
	}
}
#endif