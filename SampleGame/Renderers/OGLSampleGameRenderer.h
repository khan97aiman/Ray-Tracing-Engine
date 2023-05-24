#pragma once
#ifdef _WIN32
#include <OGLRenderer.h>
#include <glad/gl.h>
#include "ScreenManager.h"

namespace NCL {
	namespace CSC8599 {
		struct ShaderVariablesLocations {
			int projLocation = 0;
			int viewLocation = 0;
			int colourLocation = 0;
			int hasVColLocation = 0;
			int hasTexLocation = 0;
			int useFogLocation = 0;
			int fogColourLocation = 0;
			int skyboxTexLocation = 0;
			int shadowLocation = 0;
			int shadowTexLocation = 0;
			int jointsLocation = 0;

			int lightPosLocation = 0;
			int lightColourLocation = 0;
			int lightRadiusLocation = 0;

			int cameraLocation = 0;
		};
		class RenderObject;
		struct DebugLinesRenderer {
			GLuint vao;
			GLuint vertVbo;
			size_t count = 0;

			DebugLinesRenderer() {
				glGenVertexArrays(1, &vao);
				glGenBuffers(1, &vertVbo);
			}
			~DebugLinesRenderer() {
				glDeleteVertexArrays(1, &vao);			//Delete our VAO
				glDeleteBuffers(1, &vertVbo);			//Delete our VBO
			}
		};
		struct DebugTextRenderer {
			GLuint vao;
			GLuint vertVBO;
			GLuint colourVBO;
			GLuint texCoordVBO;
			size_t count = 0;

			DebugTextRenderer() {
				glGenVertexArrays(1, &vao);
				glGenBuffers(1, &vertVBO);
				glGenBuffers(1, &colourVBO);
				glGenBuffers(1, &texCoordVBO);

			}
			~DebugTextRenderer() {
				glDeleteVertexArrays(1, &vao);			//Delete our VAO
				glDeleteBuffers(1, &vertVBO);			//Delete our VBO
				glDeleteBuffers(1, &colourVBO);			//Delete our VBO
				glDeleteBuffers(1, &texCoordVBO);		//Delete our VBO
			}
		};
		class OGLSampleGameRenderer : public OGLRenderer {
		#define ATOMIC_COUNT 3
		public:
			OGLSampleGameRenderer(Window& w);
			void BindDebugShader(ShaderBase* dShader) { debugShader = dShader; }

			void SetDebugRenderers();

		protected:
			void RenderFrame()	override;

			void RenderBasicScreen();
			void RenderGameScreen();	

			void BuildObjectList();
			void SortObjectList();

			void SendModelMatrices(OGLShader* shader, const RenderObject* r);
			void RenderWithDefaultTexture(const ShaderVariablesLocations& locations, const RenderObject* r);
			void RenderWithMultipleTexture(const ShaderVariablesLocations& locations, const RenderObject* r);

			//Debug methods
			void RenderDebugInformation() const;
			void NewRenderLines();
			void NewRenderText();
			void SetDebugStringBufferSizes(size_t newVertCount);
			void SetDebugLineBufferSizes(size_t newVertCount);


			vector<const RenderObject*> activeObjects;
			Vector4		lightColour;
			float		lightRadius;
			Vector3		lightPosition; 
			ShaderBase* debugShader = nullptr;

			//Debug data storage things
			vector<Vector3> debugLineData;
			vector<Vector3> debugTextPos;
			vector<Vector4> debugTextColours;
			vector<Vector2> debugTextUVs;

			DebugTextRenderer* debugTextRenderer = nullptr;
			DebugLinesRenderer* debugLineRenderer = nullptr;
		};
		
		// Concrete factory for creating Painting Game OpenGL renderer
		class OGLSampleGameRendererFactory : public OGLRendererFactory {
		public:
			RendererBase* createRenderer(Window& w) override {
				return new OGLSampleGameRenderer(w);
			}
		};
	}
}
#endif
