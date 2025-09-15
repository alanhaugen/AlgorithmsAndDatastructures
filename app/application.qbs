import "../solid/solid.qbs" as solid

solid {
    Application {
        name: "App"
        cpp.cxxLanguageVersion: "c++23"

        files: [
            "data/BackgroundImage.png",
            "data/BlackCursor.png",
            "data/BoardScene.pdn",
            "data/BoardScene.png",
            "data/Button-2_Player.png",
            "data/Button-Audio.png",
            "data/Button-Graphics.png",
            "data/Button-Load_Replay.png",
            "data/Button-Play_Against_AI.png",
            "data/Button-Play_Game.png",
            "data/Button-Quit_to_Menu.png",
            "data/Button-Settings.png",
            "data/MainMenuScene.pdn",
            "data/MainMenuScene.png",
            "data/Title.png",
            "data/WhiteCursor.png",
            "data/cubemap.frag",
            "data/cubemap.vert",
            "data/gui.frag",
            "data/gui.vert",
            "data/icon.png",
            "data/level1.json",
            "data/logo.png",
            "data/logo_inv.png",
            "data/phong.frag",
            "data/phong.vert",
            "data/project.json",
            "data/sheet.png",
            "data/simple.frag",
            "data/simple.vert",
            "data/solid.ico",
            "data/stdButton.png",
            "data/vertexanimation.frag",
            "data/vertexanimation.vert",
            "source/aiplayer.cpp",
            "source/aiplayer.h",
            "source/autochess.cpp",
            "source/autochess.h",
            "source/board.cpp",
            "source/board.h",
            "source/button.cpp",
            "source/button.h",
            "source/checkbox.cpp",
            "source/checkbox.h",
            "source/cursor.cpp",
            "source/cursor.h",
            "source/gamesettings.cpp",
            "source/gamesettings.h",
            "source/gamesettingsmenu.cpp",
            "source/gamesettingsmenu.h",
            "source/main.cpp",
            "source/main.h",
            "source/mainmenu.cpp",
            "source/mainmenu.h",
            "source/menu.cpp",
            "source/menu.h",
            "source/minimax.cpp",
            "source/minimax.h",
            "source/move.cpp",
            "source/move.h",
            "source/piece.cpp",
            "source/piece.h",
            "source/player.cpp",
            "source/player.h",
            "source/popup.cpp",
            "source/popup.h",
            "source/rangeinput.cpp",
            "source/rangeinput.h",
            "source/replay.cpp",
            "source/replay.h",
            "source/replaynew.cpp",
            "source/replaynew.h",
            "source/replayscene.cpp",
            "source/replayscene.h",
            "source/rulebook.cpp",
            "source/rulebook.h",
            "source/settings.cpp",
            "source/settings.h",
            "source/shop.cpp",
            "source/shop.h",
            "source/tile.cpp",
            "source/tile.h",
            "source/tree.h",
        ]

        property stringList includePaths: "../solid/source"

        Depends { name: "cpp" }
        Depends { name: "core" }
        Depends { name: "nullrenderer"  }
        Depends { name: "nullphysics"  }
        Depends { name: "nullaudio"  }
        Depends { name: "nullphysics"  }
        Depends { name: "nullfilesystem"  }
        Depends { name: "nullscript" }
        Depends { name: "vulkanrenderer"  }
        Depends { name: "stdfilesystem"  }
        Depends { name: "portaudioaudio"  }
        Depends { name: "nullphysics" }
        Depends { name: "bouncephysics" }

        Properties {
            condition: qbs.targetOS.contains("macos")

            cpp.frameworks: {
                if (qbs.architecture.includes("arm64"))
                    return macosFrameworks.concat(
                           "CoreHaptics",
                           "MediaPlayer",
                           "GameController",
                           "QuartzCore",
                           "IOSurface")
                return macosFrameworks
            }

            cpp.dynamicLibraries: macosSharedLibs
            cpp.staticLibraries: staticLibs.concat("SDL2", "MoltenVK")

            cpp.libraryPaths: [project.buildDirectory, "../solid/lib/debug/darwin/" + qbs.architecture]
            cpp.includePaths: includePaths.concat("../solid/include/darwin")
            cpp.defines: project.defines.concat(project.sdlDefines)
        }

        Properties {
            condition: qbs.targetOS.contains("linux")

            cpp.dynamicLibraries: linuxSharedLibs
            cpp.staticLibraries: staticLibs.concat("glfw3")

            cpp.libraryPaths: [project.buildDirectory, "../solid/lib/debug/linux" + qbs.architecture]
            cpp.includePaths: includePaths.concat("../solid/include/linux")
            cpp.defines: project.defines.concat(project.glfwDefines)
        }

        Properties {
            condition: qbs.targetOS.contains("windows")

            cpp.dynamicLibraries: windowsSharedLibs
            cpp.staticLibraries: staticLibs

            cpp.libraryPaths: [project.buildDirectory, "../../solid/lib/debug/mingw32/x86_64"]
            cpp.includePaths: includePaths.concat("../../solid/include/mingw32")
            cpp.defines: project.defines.concat(project.windowsDefines)
        }
    }
}
