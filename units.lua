
require "tundra.syntax.glob"
require "tundra.syntax.files"
local native = require "tundra.native"

ExternalLibrary {
    Name = "defaultConfiguration",
    Pass = "CompileGenerator",
    Propagate = {
        Libs = {Config="win32-*-*"; "User32.lib", "Gdi32.lib", "Ws2_32.lib", "shell32.lib", "winmm.lib"},
    },
}  

Program {
  Name = "mgrorganizer",
  Sources = {
      "mgrorganizer.cpp",
      "thirdparty/imgui/imgui.cpp",
      "thirdparty/imgui/imgui_draw.cpp",
      "thirdparty/imgui/imgui_widgets.cpp",
      "thirdparty/imgui/imgui_stdlib.cpp",
  },
  Depends = {
      "defaultConfiguration",
  },
   Env = {
      CPPDEFS = {
         "SOKOL_GLCORE33",
      },
      CPPPATH = {
        "utils",
        "thirdparty/",
        "thirdparty/imgui/",
        "thirdparty/sokol/",
        "thirdparty/sokol/util/",
      },
   },
  Libs = {Config="win32-*-*"; "Comdlg32.lib", "Ole32.lib" },
}
Default "mgrorganizer"
