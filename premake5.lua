workspace "ikea"
   architecture "x64"

   configurations {
      "Debug",
      "Release"
   }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


project "IKEA"
   location "IKEA"
   kind "ConsoleApp"

   language "C++"
   cppdialect "C++17"

   targetdir("bin/".. outputdir .. "/%{prj.name}")
   objdir("bin-int/".. outputdir .. "/%{prj.name}")

   files {
      "%{prj.name}/src/**.h",
      "%{prj.name}/src/**.cpp",
   }

   includedirs {
      "%{prj.name}/src",
   }


   filter "system:linux"
      buildoptions { "-std=c++17" } 

      defines {
         "IKEA_PLATFORM_LINUX"
      }

      staticruntime "On"

   filter "configurations:Debug"
      defines "IKEA_DEBUG"
      symbols "On"

   filter "configurations:Release"
      defines "IKEA_RELEASE"
      optimize "On"
