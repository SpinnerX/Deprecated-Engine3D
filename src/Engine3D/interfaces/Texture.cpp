#include <Engine3D/Engine3DPrecompiledHeader.h>
#include <Engine3D/interfaces/Texture.h>
#include <Engine3D/Renderer2D/Renderer.h>
#include <OpenGL/OpenGLTexture.h>
#include <OpenGL/OpenGLTexture3D.h>

namespace Engine3D{

    Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height){
		switch (Renderer::getAPI()) {
			case RendererAPI::API::None:
				render_assert(false, "RendererAPI::None is currently not supported!");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return CreateRef<OpenGLTexture2D>(width, height);
		}
	}

    Ref<Texture2D> Texture2D::Create(const std::string& filepath){
        switch (RendererAPI::getAPI()){
        case RendererAPI::API::None:
            render_core_assert(false, "RenderAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLTexture2D>(filepath);
        }

        render_core_assert(false, "Unknown renderer API");
        return nullptr;
    }

	Ref<Texture3D> Texture3D::Create(uint32_t width, uint32_t height){
		switch (Renderer::getAPI()) {
		case Engine3D::RendererAPI::API::None:
			coreLogError("RenderAPI::None not supported!");
			assert(false);
			break;
		case Engine3D::RendererAPI::API::OpenGL:
			return CreateRef<OpenGLTexture3D>(width, height);
		default: return nullptr;
		}

		return nullptr;
	}

	Ref<Texture3D> Texture3D::Create(const std::string& filepath){
		switch (Renderer::getAPI()) {
		case Engine3D::RendererAPI::API::None:
			coreLogError("RenderAPI::None not supported!");
			assert(false);
			break;
		case Engine3D::RendererAPI::API::OpenGL:
			return CreateRef<OpenGLTexture3D>(filepath);
		default: return nullptr;
		}

		return nullptr;
	}
};
