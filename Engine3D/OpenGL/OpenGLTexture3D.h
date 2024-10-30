#pragma once
#include <Engine3D/Core/core.h>
#include <Engine3D/interfaces/Texture.h>

namespace Engine3D{
	class OpenGLTexture3D : public Texture3D{
	public:
		OpenGLTexture3D(uint32_t width, uint32_t height);
		OpenGLTexture3D(const std::string& filepath);

		virtual ~OpenGLTexture3D();

		virtual uint32_t getRendererID() const override { return _rendererID; }

		virtual uint32_t getWidth() const override { return _width; }
		virtual uint32_t getHeight() const override { return _height; }

		virtual void setData(void* data, uint32_t size) override;

		virtual void bind(GLenum bind = GL_TEXTURE_3D) const override;

		virtual bool operator==(const Texture& other) const override{
			return _rendererID == ((OpenGLTexture3D &)other)._rendererID;
		}

	private:
		std::string _filepath;
		uint32_t _width;
		uint32_t _height;
		uint32_t _rendererID;
		GLenum _internalFormat, _formatData;
	};
};
