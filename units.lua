
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
  Name = "minseq",
  Sources = {
      "main.cpp",
  },
  Depends = {
      "defaultConfiguration",
  },
  Env = {
      CPPDEFS = {
      },
      CPPPATH = {
        "extlibs/",
      },
   },
  Libs = {Config="win32-*-*"; "Comdlg32.lib", "Ole32.lib" },
}
Default "minseq"
