#include <Engine3D/Engine3DPrecompiledHeader.h>
#include <OpenGL/OpenGLTexture3D.h>
#include <Engine3D/image/stb_image.h>

namespace Engine3D{
	OpenGLTexture3D::OpenGLTexture3D(uint32_t w, uint32_t h) : _width(w), _height(h) {
		_internalFormat = GL_RGBA8;
		_formatData = GL_RGBA;

		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLTexture3D::OpenGLTexture3D(const std::string& filepath) : _filepath(filepath) {
		int width, height, channels;
		stbi_set_flip_vertically_on_load_thread(1);

		stbi_uc* data = nullptr;

		{
			data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);
		}

		if(data == nullptr){
			coreLogError("Failed to load image!");
		}
		else{
			coreLogInfo("Image Data was not nullptr meaning was valid!");
		}

		_width = width;
		_height = height;

		GLenum internalData=0, formatData=0;

		if(channels == 4){
            internalData = GL_RGBA8;
            formatData = GL_RGBA;
		
		}
		else if(channels == 3){
            internalData = GL_RGB8;
            formatData = GL_RGB;
		}

		_internalFormat = internalData, _formatData = formatData;

		glGenTextures(1, &_rendererID);
		glActiveTexture(GL_TEXTURE_3D);
        glBindTexture(GL_TEXTURE_2D, _rendererID);

		
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		// Since we segfault using glTextureParameteri, we'll use this for now
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		/* glTextureParameteri(_rendererID, GL_TEXTURE_WRAP_S, GL_REPEAT); */
		/* glTextureParameteri(_rendererID, GL_TEXTURE_WRAP_T, GL_REPEAT); */

        glTexImage2D(GL_TEXTURE_3D, 0, internalData, _width, _height, 0, formatData, GL_UNSIGNED_BYTE, data); // same thing as doing: glTextureSubImage2D

        glGenerateMipmap(GL_TEXTURE_3D);

		stbi_image_free(data); // free image data stored in CPU

        glBindTexture(GL_TEXTURE_3D, 0);
	}

	OpenGLTexture3D::~OpenGLTexture3D(){
		glDeleteTextures(1, &_rendererID);
	}

	void OpenGLTexture3D::bind(GLenum slot) const {
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_3D, _rendererID);
	}

	void OpenGLTexture3D::setData(void* data, uint32_t size){
		uint32_t bpp = _formatData == GL_RGBA ? 4 : 3;
		render_core_assert(size == _width * _height * bpp, "Data must be an entire texture"); // Make sure that the textures are fine for rn
        glTexImage3D(GL_TEXTURE_3D, 0, _internalFormat, _width, _height, 0, 0, _formatData, GL_UNSIGNED_BYTE, data); // same thing as doing: glTextureSubImage2D

	}
};
