#include <Engine3D/Core/Application.h>
#include "ExampleLayer2D.h"
#include <Engine3D/Core/EntryPoint.h>

class ExampleApp : public Engine3D::Application{
public:
	ExampleApp() : Application(){
		pushLayer(new ExampleLayer2D());
	}
};

Engine3D::Application* Engine3D::CreateApplication(Engine3D::ApplicationCommandLineArgs args){
	return new ExampleApp();
}
