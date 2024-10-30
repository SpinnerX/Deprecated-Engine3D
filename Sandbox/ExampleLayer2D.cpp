#include "ExampleLayer2D.h"
#include <Engine3D/Core/Application.h>
#include <Engine3D/OpenGL/OpenGLFramebuffer.h>
#include <Engine3D/Renderer2D/RenderCommand.h>
#include <Engine3D/Renderer2D/Renderer2D.h>
#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace Engine3D;



ExampleLayer2D::ExampleLayer2D() : Layer("Layer #1"), camController(1280.0f/720.0f){
}

void ExampleLayer2D::onAttach(){
	checkboardTexture = Texture2D::Create("assets/Checkerboard.png");
	camController.setZoomLevel(5.0f); // @note Higher the offset, the wider we zoom outwards.
	FrameBufferSpecifications frameBufferData{};
	frameBufferData.width = 1280;
	frameBufferData.height = 720;
}

void ExampleLayer2D::onDetach(){
}


void ExampleLayer2D::onUpdate(Engine3D::Timestep ts){
	camController.onUpdate(ts);
	
	Renderer2D::setClearColor();

	Renderer2D::beginScene(camController.getCamera());

	static float  rotation = 0.0f;
	rotation += ts * 50.0f;

	// @note format of the parameters
	//						pos				size			color (r, g, b, a)
	/* Renderer2D::drawQuad({0.0f, 0.0f}, {5.f, 5.f}, {0.8, 0.2f, 0.3f, 1.0f}); */ // @note Rendering a red square
	Renderer2D::drawRotatedQuad({ -2.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, glm::radians(rotation), checkboardTexture, 20.0f); //@note Checkerboard texture shape (and making this texture specifically rotate)

	// @note This will draw tiles squares as color gradients
	for(float y = -5.0f; y < 5.0f; y += 0.5f){
		for(float x = -5.0f; x < 5.0f; x += 0.5f){
			glm::vec4 color = { (x + 0.5f) / 10.f, 0.4f, (y + 5.0f) / 10.0f, 0.7f};
			Renderer2D::drawQuad({x, y}, {0.45f, 0.45f}, color);
		}
	}
	Renderer2D::endScene();
}

void ExampleLayer2D::onImguiRender(){
	/* ImGui::Begin("Settings"); */

	/* auto stats = Renderer2D::getStats(); */
	/* ImGui::Text("Renderer2D Stats"); */
	/* ImGui::Text("Draw Calls %d", stats.drawCalls); */
	/* ImGui::Text("Quads: %d", stats.quadCount); */
	/* ImGui::Text("Vertices: %d", stats.getTotalVertexCount()); */
	/* ImGui::Text("Indices: %d", stats.getTotalIndexCount()); */

	/* ImGui::ColorEdit4("Square Color", glm::value_ptr(squareColor)); */

	/* ImGui::End(); */
}

void ExampleLayer2D::onEvent(Engine3D::Event& e){
	
	if(InputPoll::isKeyPressed(ENGINE_KEY_ESCAPE)){
		Application::Get().close();
	}

	camController.onEvent(e);
}
