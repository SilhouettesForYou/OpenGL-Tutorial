set_project("OpenGL Tutorial")
set_languages("c++23")
add_rules("mode.debug", "mode.releasedbg")

target("HelloOpenGL")
    set_kind("binary")
    add_files("src/*.cpp")
    add_includedirs("src")
    add_includedirs("/dependence")
    add_includedirs("/dependence/glfw-3.4.bin.WIN64/include")
    add_includedirs("/dependence/glew-2.1.0/include")
    add_linkdirs("/dependence/glfw-3.4.bin.WIN64/lib-vc2022")
    add_linkdirs("/dependence/glew-2.1.0/lib/Release/x64")
    add_linkdirs("/dependence/glew-2.1.0/bin/Release/x64")
    add_links("glfw3dll", "glew32")
    add_syslinks("opengl32")
