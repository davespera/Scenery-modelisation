
no_project = true
dofile "./premake4.lua"

l2_lifgraphique_dir = path.getabsolute(".")
	
l2_lifgraphique_files = {	l2_lifgraphique_dir .. "/src/l2_lifgraphique/AnimationCurve.cpp", 
				l2_lifgraphique_dir .. "/src/l2_lifgraphique/AnimationCurve.h",
				l2_lifgraphique_dir .. "/src/l2_lifgraphique/Viewer.cpp",
				l2_lifgraphique_dir .. "/src/l2_lifgraphique/Viewer.h",
				l2_lifgraphique_dir .. "/src/l2_lifgraphique/Viewer_etudiant.cpp",
				l2_lifgraphique_dir .. "/src/l2_lifgraphique/Viewer_etudiant.h"}	
	
project("l2_lifgraphique")
    language "C++"
    kind "ConsoleApp"
    targetdir ( l2_lifgraphique_dir .. "/bin" )
    includedirs { l2_lifgraphique_dir .. "/src/l2_lifgraphique/" }
    files ( gkit_files )
    files ( l2_lifgraphique_files )
