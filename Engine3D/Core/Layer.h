#pragma once
#include <Engine3D/Core/core.h>
#include <Engine3D/Events/Event.h>
#include <Engine3D/Core/Timestep.h>
#include <Engine3D/Core/EngineLogger.h>
#include <Engine3D/Events/ApplicationEvent.h>
#include <Engine3D/Debug/Instrumentor.h>

namespace Engine3D{

    // Layer interface
    // - Shouldn't have names (but only if its used for debugging)
    // TODO: allow enabling/disabling layers meaning not being updated or rendering (essentially hiding from layer stack)
    class ENGINE_API Layer{
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer();

        // When pushing onto the Layer Stack we attach it
        // Pop of thhe layer stack is for detaching (like shhutdown)
        virtual void onAttach() {
            coreLogInfo("Default onAttach() called instead!");
        }

        virtual void onDetach() {}

        // Updating the layer is updated when the application calls onUpdate
        virtual void onUpdate(Timestep ts){}

        virtual void onImguiRender(){}

        // Whichh is wherever events get sent to the layer, it'll know how to handle that event.
        virtual void onEvent(Event& event){}

        inline const std::string& getName() const { return _debugName; }

        friend std::ostream& operator<<(std::ostream& outs, const Layer* layer){
            return outs << layer->_debugName;
        }
    protected:
        std::string _debugName;
    };
};