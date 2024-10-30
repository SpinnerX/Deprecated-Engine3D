#pragma once
#include <Engine3D/Core/Layer.h>
#include <Engine3D/OpenGL/OpenGLTexture.h>
#include <Engine3D/Renderer2D/OrthographicCameraController.h>
#include <Engine3D/OpenGL/OpenGLBuffer.h>
#include <Engine3D/OpenGL/OpenGLVertexArray.h>
#include <Engine3D/OpenGL/OpenGLShader.h>

class ExampleLayer2D : public Engine3D::Layer{
public:
	ExampleLayer2D();

	virtual ~ExampleLayer2D() = default;

	virtual void onAttach() override;

	virtual void onDetach() override;

	virtual void onUpdate(Engine3D::Timestep ts) override;

	virtual void onImguiRender() override;

	virtual void onEvent(Engine3D::Event& e) override;

private:
	Engine3D::OrthographicCameraController camController;
	Engine3D::Ref<Engine3D::VertexArray> vertexArr;
	Engine3D::Ref<Engine3D::Shader> shader;

	Engine3D::Ref<Engine3D::Texture2D> checkboardTexture;
	glm::vec4 squareColor = {0.2f, 0.3f, 0.8f, 1.0f};
};
