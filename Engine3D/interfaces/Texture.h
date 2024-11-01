#pragma once
#include <Engine3D/Core/core.h>
#include <GLFW/glfw3.h>
#include <string>

namespace Engine3D{


    /**
     * @brief 
     * 
     * @class Texture (class) - Pure virtual class representing the texture
     * @class Texture2D - Represents our actual 2D texture pure virtual class interface for different platforms to impl
     */
    class Texture{
    public:
        virtual ~Texture() = default;

        virtual uint32_t getWidth() const = 0;
        virtual uint32_t getHeight() const = 0;
		
		virtual uint32_t getRendererID() const = 0;

		// @setData simply will take in a block of data in memory, and upload that data to the GPU
		virtual void setData(void* data, uint32_t size) = 0;

        virtual void bind(GLenum slot=GL_TEXTURE_2D) const = 0;

		virtual bool operator==(const Texture& other) const = 0;
    };


    class Texture2D : public Texture{
    public:
        Texture2D() = default;
        Texture2D(const std::string& filepath);

        static Ref<Texture2D> Create(uint32_t width, uint32_t height);
        static Ref<Texture2D> Create(const std::string& filepath);
    };

	class Texture3D : public Texture{
	public:
		Texture3D() = default;
		Texture3D(const std::string& filepath);

		static Ref<Texture3D> Create(uint32_t width, uint32_t height);
		static Ref<Texture3D> Create(const std::string& filepath);
	};
};
