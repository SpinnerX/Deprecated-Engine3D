cmake_minimum_required(VERSION 3.15)

project(Engine3D VERSION 1.0)
set(CMAKE_CXX_STANDARD 20)

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "") # works (in creating the compile_commands.json file)

include(GNUInstallDirs)
include_directories(
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/include/Engine3D
)


add_subdirectory(Sandbox)
add_subdirectory(src)


# target_precompile_headers(${PROJECT_NAME} PUBLIC
# 	"$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_INSTALL_PREFIX}/include/GameEngine/GameEnginePrecompiledHeader.h>"
# )

set(PRECOMPILED_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include/Engine3D/Engine3DPrecompiledHeader.h>")
set(INSTALLED_PRECOMPILED_PATH "${CMAKE_INSTALL_PREFIX}/include/Engine3D/Engine3DPrecompiledHeader.h>")

if(EXISTS ${INSTALLED_PRECOMPILED_PATH})
	set(PATH ${INSTALLED_PRECOMPILED_PATH})
elseif(EXISTS ${PRECOMPILED_PATH})
	set(PATH ${PRECOMPILED_PATH})
endif()

# @note find_dependency is how you can specify what dependencies will be shipped with Engine3D
# @note When users try to find this packages.

# find_package(glfw3 REQUIRED)
find_dependency(glfw3 REQUIRED)

# find_package(OpenGL REQUIRED)
# find_package(GLEW REQUIRED)
find_dependency(OpenGL REQUIRED)
if(APPLE)
find_dependency(GLEW REQUIRED)
endif(APPLE)
# find_package(imgui REQUIRED)
# find_package(ImGuizmo REQUIRED)
find_dependency(imgui REQUIRED)
find_dependency(ImGuizmo REQUIRED)

# find_package(fmt REQUIRED)
# find_package(spdlog REQUIRED)
# find_package(glad REQUIRED)
# find_package(glm REQUIRED)

find_dependency(fmt REQUIRED)
find_dependency(spdlog REQUIRED)
find_dependency(glad REQUIRED)
find_dependency(glm REQUIRED)

find_dependency(box2d REQUIRED)
find_dependency(yaml-cpp REQUIRED)

# target_precompile_headers(${PROJECT_NAME} PUBLIC
# 	"$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/include/Engine3D/Engine3DPrecompiledHeader.h>"
# )

target_precompile_headers(${PROJECT_NAME} PUBLIC
	"$<$<COMPILE_LANGUAGE:CXX>:>"
)
if(UNIX AND NOT APPLE)
	target_link_libraries(
		${PROJECT_NAME}
		glfw
		# ${OPENGL_gl_LIBRARY}
		OpenGL::GL
		# Vulkan::Vulkan
		imgui::imgui
		fmt::fmt
		glm::glm
		spdlog::spdlog
		glad::glad
		box2d::box2d
		yaml-cpp::yaml-cpp
	)
endif(UNIX AND NOT APPLE)

if(APPLE)
target_link_libraries(
	${PROJECT_NAME}
	PUBLIC
	glfw
	"-framework Cocoa"
	"-framework OpenGL"
	"-framework IOKit"
	${APPKIT_LIBRARY} ${UNIFORMTYPEIDENTIFIERS_LIBRARY} # Note as TODO: Probably should put this somewhere else, since it relies on nfd.cmake...
	imgui::imgui
	ImGuizmo::ImGuizmo
	fmt::fmt
	glm::glm
	spdlog::spdlog
	glad::glad
	GLEW::GLEW
	box2d::box2d
	yaml-cpp::yaml-cpp
	${APPKIT_LIBRARY} ${UNIFORMTYPEIDENTIFIERS_LIBRARY} # Note as TODO: Probably should put this somewhere else, since it relies on nfd.cmake...
)
endif(APPLE)

set_target_properties(${PROJECT_NAME} PROPERTIES
	CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)

if(MSVC)
	set_target_properties(${PROJECT_NAME} PROPERTIES
    COMPILE_PDB_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
	COMPILE_PDB_NAME ${PROJECT_NAME}
  )

  install(
	  FILES "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/${PROJECT_NAME}.pdb"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
    OPTIONAL
  )
endif()

if (BUILD_SHARED_LIBS)
	target_compile_definitions(${PROJECT_NAME}
    PUBLIC
	${PROJECT_NAME}_SHARED
  )
endif()

# install(
# 	DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Engine3D"
#   DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
# )

# Installing to /usr/local/public/GameEngine/
# install(
#   DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/assets"
#   DESTINATION "${CMAKE_INSTALL_LIBDIR}/GameEngine"
# )
