#include <Engine3D/Engine3DPrecompiledHeader.h>
#include <Engine3D/Renderer3D/Renderer3D.h>
#include <Engine3D/Renderer2D/RenderCommand.h>
/* #include <Engine3D/OpenGL/OpenGLTexture3D.h */
#include <Engine3D/interfaces/Texture.h>
#include <Engine3D/interfaces/Shader.h>
#include <glm/glm.hpp>

namespace Engine3D{

	struct quadVertex{
		glm::vec3 pos;
		glm::vec4 color;
		glm::vec2 texCpprd;
		float texIndex;
		float tilingFactor;

		int entityID = 0;
	};

	struct Renderer3DData{
		static const uint32_t maxQuads = 10000;
		static const uint32_t maxVertices = maxQuads * 4;
		static const uint32_t maxIndices = maxQuads * 6;
		static const uint32_t maxTextureSlots = 16;
		Ref<VertexArray> quadVertexArray;
		Ref<VertexBuffer> quadVertexBuffer;
		Ref<Shader> textureShader;
		Ref<Texture3D> whiteTexture;

		uint32_t quadIndexCount = 0;
		quadVertex* quadVertexBufferBase = nullptr;
		quadVertex* quadVertexBufferPtr = nullptr;

		std::array<Ref<Texture3D>, maxTextureSlots> textureSlots;
		uint32_t textureSlotIndex = 1; // @note 0 = white texture
		std::array<glm::vec4, 4> quadVertexPositions;

		Renderer3D::Statistics stats;
	};

	static Renderer3DData _data;
	
	void Renderer3D::init(){

		// @note Setting up our vertex arrays and vertex buffers for our renderer data.
		_data.quadVertexArray = VertexArray::Create();
		_data.quadVertexBuffer = VertexBuffer::Create(_data.maxVertices * sizeof(quadVertex));

		_data.quadVertexBuffer->setLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" },
			{ ShaderDataType::Float3, "a_TexCoord" },
			{ ShaderDataType::Float, "a_TexIndex" },
			{ ShaderDataType::Float, "a_TilingFactor" },
			{ ShaderDataType::Int, "a_EntityID" }
		});

		_data.quadVertexArray->addVertexBuffer(_data.quadVertexBuffer);
		
		_data.quadVertexBufferBase = new quadVertex[_data.maxVertices * sizeof(quadVertex)];

		uint32_t* quadIndices = new uint32_t[_data.maxIndices];
		
		uint32_t offset = 0;
		for(uint32_t i = 0; i < _data.maxIndices; i += 6){
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 3;
			quadIndices[i + 4] = offset + 4;
			quadIndices[i + 5] = offset + 5;

			offset += 4;
		}

		Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, _data.maxIndices);
		_data.quadVertexArray->setIndexBuffer(quadIB);

		delete[] quadIndices;

		_data.whiteTexture = Texture3D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff; // four f's for every channel
		
		_data.whiteTexture->setData(&whiteTextureData, sizeof(uint32_t));

		int32_t samplers[_data.maxTextureSlots];

		for(uint32_t i = 0; i < _data.maxTextureSlots; i++)
			samplers[i] = i;

		// _data.textureShader = Shader::CreateShader("assets/shaders/texture.glsl");
		_data.textureShader = Shader::CreateShader("/usr/local/public/GameEngine/assets/shaders/texture3d.glsl");
		_data.textureShader->bind();
		_data.textureShader->setIntArray("u_Textures", samplers, _data.maxTextureSlots);

		// Texture slot at 0 to white texture
		_data.textureSlots[0] = _data.whiteTexture;
		_data.quadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f};
		_data.quadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f};
		_data.quadVertexPositions[2] = { 0.5f, 0.5f, 0.0f, 1.0f};
		_data.quadVertexPositions[3] = { -0.5f, 0.5f, 0.0f, 1.0f};

	}
	
	void Renderer3D::begin(Ref<Camera>& camera, glm::mat4& transform){
		glm::mat4 viewProjection = camera->getProjection() * glm::inverse(transform);
		
		_data.textureShader->bind();
		_data.textureShader->setMat4("u_ViewProjection", viewProjection);
		
		_data.quadIndexCount = 0;
		_data.quadVertexBufferPtr = _data.quadVertexBufferBase; // Keeping track o our base memory allocations
		
		_data.textureSlotIndex = 1;
	}

	void Renderer3D::end(){
		uint32_t dataSize = (uint8_t *)_data.quadVertexBufferPtr - (uint8_t *)_data.quadVertexBufferBase;
		_data.quadVertexBuffer->setData(_data.quadVertexBufferBase, dataSize);

		flush();
	}
	
	void Renderer3D::initializeCore(){}

	void Renderer3D::shutdown(){}


	void Renderer3D::flush(){
		// @note Binding all of our texture slots submitted with a renderer id (that is i).
		// @note Essentially uploading data to the GPU
		// @note Executing the actual rendering.
		for(uint32_t i = 0; i < _data.textureSlotIndex; i++)
			_data.textureSlots[i]->bind(i);
		
		RendererCommand::drawIndexed(_data.quadVertexArray, _data.quadIndexCount);
		_data.stats.drawCalls++;
		
	}

	void Renderer3D::resetStats(){
		end();
		_data.quadIndexCount = 0;
		_data.quadVertexBufferPtr = _data.quadVertexBufferBase; // Keeping track o our base memory allocations
		
		_data.textureSlotIndex = 1;
		
	}
};
