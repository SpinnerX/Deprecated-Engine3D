include_directories(
	Engine3D
	../
)

set(
	INCLUDE_DIR
	Engine3D	
)

set(
  all_src


  Engine3D/Core/EntryPoint.cpp
  Engine3D/Core/Application.cpp
  Engine3D/Core/EngineLogger.cpp
  Engine3D/Events/InputPoll.cpp
  Engine3D/Core/Layer.cpp
  Engine3D/Core/LayerStack.cpp

  Engine3D/Imgui/ImGuiLayer.cpp

  Engine3D/OpenGL/OpenGLContext.cpp
  Engine3D/interfaces/Shader.cpp
  Engine3D/interfaces/Buffer.cpp
  Engine3D/OpenGL/OpenGLBuffer.cpp
  Engine3D/Renderer2D/Renderer.cpp
  Engine3D/interfaces/VertexArray.cpp
  Engine3D/OpenGL/OpenGLVertexArray.cpp
  Engine3D/interfaces/RendererAPI.cpp
  Engine3D/Renderer2D/RendererCommand.cpp
  Engine3D/OpenGL/OpenGLRendererAPI.cpp
  Engine3D/Renderer2D/OrthographicCamera.cpp
  Engine3D/OpenGL/OpenGLShader.cpp
  Engine3D/interfaces/Texture.cpp
  Engine3D/OpenGL/OpenGLTexture.cpp
  Engine3D/Renderer2D/OrthographicCameraController.cpp

  Engine3D/OpenGL/OpenGLInputPoll.cpp
  
  Engine3D/OpenGL/OpenGLWindow.cpp
  Engine3D/Renderer2D/Renderer2D.cpp
  Engine3D/interfaces/SubTexture2D.cpp
  Engine3D/interfaces/Framebuffer.cpp
  Engine3D/OpenGL/OpenGLFramebuffer.cpp
  Engine3D/Scene2D/Scene.cpp
  Engine3D/Scene2D/Entity.cpp
  Engine3D/Scene2D/SceneCamera.cpp
  Engine3D/Scene2D/SceneSerializer.cpp
  Engine3D/image/stb_image.cpp

  Engine3D/platforms/Mac/MacPlatformUtils.cpp
  Engine3D/Math/Math.cpp
  Engine3D/Renderer2D/EditorCamera.cpp
  Engine3D/interfaces/UniformBuffer.cpp
  Engine3D/OpenGL/OpenGLUniformBuffer.cpp

  Engine3D/Renderer3D/Renderer3D.cpp
  Engine3D/OpenGL/OpenGLBuffer3D.cpp
  Engine3D/OpenGL/OpenGLTexture3D.cpp
)

# For Mac, linking AppKit only and only needing nfd_cocoa.m
if(APPLE)
  # For setting the filter list, macOS introduced allowedContentTypes in version 11.0 and deprecated allowedFileTypes in 12.0.
  # By default (set to ON), NFDe will use allowedContentTypes when targeting macOS >= 11.0.
  # Set this option to OFF to always use allowedFileTypes regardless of the target macOS version.
  # This is mainly needed for applications that are built on macOS >= 11.0 but should be able to run on lower versions
  # and should not be used otherwise.
  option(NFD_USE_ALLOWEDCONTENTTYPES_IF_AVAILABLE "Use allowedContentTypes for filter lists on macOS >= 11.0" ON)

  find_library(APPKIT_LIBRARY AppKit)
  if(NFD_USE_ALLOWEDCONTENTTYPES_IF_AVAILABLE)
    include(CheckCXXSourceCompiles)
    check_cxx_source_compiles(
      "
      #include <Availability.h>
      #if !defined(__MAC_OS_X_VERSION_MIN_REQUIRED) || !defined(__MAC_11_0) || __MAC_OS_X_VERSION_MIN_REQUIRED < __MAC_11_0
      static_assert(false);
      #endif
      int main() { return 0; }
      "
      NFD_USE_ALLOWEDCONTENTTYPES
    )
    if(NFD_USE_ALLOWEDCONTENTTYPES)
      find_library(UNIFORMTYPEIDENTIFIERS_LIBRARY UniformTypeIdentifiers)
      if(NOT UNIFORMTYPEIDENTIFIERS_LIBRARY)
        message(FATAL_ERROR "UniformTypeIdentifiers framework is not available even though we are targeting macOS >= 11.0")
      endif()
    endif()
  endif()
  list(APPEND all_src Engine3D/platforms/Mac/nfd_cocoa.m)
endif()

set(
  all_headers
  ../${INCLUDE_DIR}/Core/Application.h
  ../${INCLUDE_DIR}/Core/core.h
  ../${INCLUDE_DIR}/Core/EngineLogger.h
  ../${INCLUDE_DIR}/Core/EntryPoint.h
#   ../${INCLUDE_DIR}/Core/GameEngine.h
  ../${INCLUDE_DIR}/Events/InputPoll.h
  ../${INCLUDE_DIR}/Core/Window.h
  ../${INCLUDE_DIR}/Core/Layer.h
  ../${INCLUDE_DIR}/Core/LayerStack.h
  ../${INCLUDE_DIR}/Core/Timer.h
  ../${INCLUDE_DIR}/Core/Timestep.h
  ../${INCLUDE_DIR}/Entt/entt.h
  ../${INCLUDE_DIR}/Imgui/ImGuiLayer.h

  ../${INCLUDE_DIR}/OpenGL/OpenGLContext.h
  ../${INCLUDE_DIR}/interfaces/Shader.h
  ../${INCLUDE_DIR}/interfaces/Buffer.h
  ../${INCLUDE_DIR}/OpenGL/OpenGLBuffer.h
  ../${INCLUDE_DIR}/Renderer2D/Renderer.h
  ../${INCLUDE_DIR}/interfaces/VertexArray.h
  ../${INCLUDE_DIR}/OpenGL/OpenGLVertexArray.h
  ../${INCLUDE_DIR}/interfaces/RendererAPI.h
  ../${INCLUDE_DIR}/Renderer2D/RenderCommand.h
  ../${INCLUDE_DIR}/OpenGL/OpenGLRendererAPI.h
  ../${INCLUDE_DIR}/Renderer2D/OrthographicCamera.h
  ../${INCLUDE_DIR}/OpenGL/OpenGLShader.h
  ../${INCLUDE_DIR}/interfaces/Texture.h
  ../${INCLUDE_DIR}/OpenGL/OpenGLTexture.h
  ../${INCLUDE_DIR}/Renderer2D/OrthographicCameraController.h

  ../${INCLUDE_DIR}/platforms/PlatformUtils.h

  ../${INCLUDE_DIR}/Events/ApplicationEvent.h
  ../${INCLUDE_DIR}/Events/Event.h
  ../${INCLUDE_DIR}/Events/KeyEvent.h
  ../${INCLUDE_DIR}/Events/MouseEvent.h
  ../${INCLUDE_DIR}/OpenGL/OpenGLInputPoll.h
  ../${INCLUDE_DIR}/image/stb_image.h

  ../${INCLUDE_DIR}/Renderer3D/Renderer3D.h
  ../${INCLUDE_DIR}/OpenGL/OpenGLTexture3D.h
)

if(APPLE)
list(APPEND all_headers ../${INCLUDE_DIR}/platforms/Mac/nfd.h ../${INCLUDE_DIR}/platforms/Mac/nfd.hpp)
endif(APPLE)

include(CMakeFindDependencyMacro)


add_library( ${PROJECT_NAME} ${all_src} ${all_headers} )

# NOTE: Using {OPENGL_gl_LIBRARY}, if compiling on Apple.
target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../${INCLUDE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)


source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "src" FILES ${all_src})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/../${INCLUDE_DIR}" PREFIX "include" FILES ${all_headers})

install(
	TARGETS ${PROJECT_NAME}
	EXPORT ${PROJECT_NAME}Config
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(
	EXPORT ${PROJECT_NAME}Config
	NAMESPACE Engine3D::
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  COMPATIBILITY SameMajorVersion
)

install(
	FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)
