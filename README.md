[![Build Status](https://travis-ci.com/Clownacy/CSE2EX.svg?branch=portable)](https://travis-ci.com/Clownacy/CSE2EX)

# CSE2EX

CSE2EX is my personal build of CSE2, which features some enhancements:
* Widescreen
* Options menu:
  * Control remapping (keyboard and gamepad)
  * Soundtrack selection
  * V-sync toggle
  * 50FPS/60FPS toggle
  * Option to disable the design choice that locks sprites to a 320x240 grid when drawn, making them move smoother
* Bugfixes

Supported platforms include...
* Windows
* Linux
* macOS
* Wii U
* 3DS
* RISC OS

Some of the above features will be axed soon, as the project completes its transition from CSE2's old enhanced branch to my personal build.

![Screenshot](images/screenshot.png)

## Dependencies

* SDL2 (if `BACKEND_AUDIO` or `BACKEND_PLATFORM` are set to `SDL2`)
* SDL (if `BACKEND_AUDIO` or `BACKEND_PLATFORM` are set to `SDL1`)
* GLFW3 (if `BACKEND_PLATFORM` is set to `GLFW3`)
* FreeType (if `FREETYPE_FONTS` is enabled)

If these are not found, they will be built locally (with the exception of SDL).

In addition, `pkg-config` is required for builds that require static-linkage.

A list of dependencies for specific platforms can be found [on the wiki](https://github.com/Clownacy/CSE2/wiki/Dependency-lists).

## Building

This project uses CMake, allowing it to be built with a range of compilers.

(A beginner-friendly guide can be found in [VISUAL_STUDIO_2019_GUIDE.md](VISUAL_STUDIO_2019_GUIDE.md))

Switch to the terminal (Visual Studio users should open the [Developer Command Prompt](https://docs.microsoft.com/en-us/dotnet/framework/tools/developer-command-prompt-for-vs))
and `cd` into this folder. After that, generate the files for your build system
with:

```
cmake -B build -DCMAKE_BUILD_TYPE=Release
```

MSYS2 users should append `-G"MSYS Makefiles" -DPKG_CONFIG_STATIC_LIBS=ON` to
this command, also.

You can also add the following flags:

Name | Function
--------|--------
`-DJAPANESE=ON` | Enable the Japanese-language build (instead of the unofficial Aeon Genesis English translation)
`-DFIX_BUGS=ON` | Enabled by default - Fix various bugs in the game
`-DDEBUG_SAVE=ON` | Re-enable the ability to drag-and-drop save files onto the window
`-DLANCZOS_RESAMPLER=ON` | Use Lanczos filtering for audio resampling instead of linear-interpolation (Lanczos is more performance-intensive, but higher quality)
`-DFREETYPE_FONTS=ON` | Enabled by default - Use FreeType2 to render the DejaVu Mono (English) or Migu1M (Japanese) fonts, instead of using pre-rendered copies of Courier New (English) and MS Gothic (Japanese)
`-DBACKEND_RENDERER=OpenGL3` | Render with OpenGL 3.2 (hardware-accelerated)
`-DBACKEND_RENDERER=OpenGLES2` | Render with OpenGL ES 2.0 (hardware-accelerated)
`-DBACKEND_RENDERER=SDLTexture` | (Default) Render with SDL2's Texture API (hardware-accelerated) (note: requires `-DBACKEND_PLATFORM=SDL2`)
`-DBACKEND_RENDERER=WiiU` | Render with the Wii U's GX2 API (hardware-accelerated)
`-DBACKEND_RENDERER=3DS` | Render with the 3DS's Citro2D/Citro3D API (hardware-accelerated)
`-DBACKEND_RENDERER=Software` | Render with a handwritten software-renderer
`-DBACKEND_AUDIO=SDL2` | (Default) Deliver audio with SDL2 (software-mixer)
`-DBACKEND_AUDIO=miniaudio` | Deliver audio with miniaudio (software-mixer)
`-DBACKEND_AUDIO=WiiU-Hardware` | Deliver audio with Wii U's AXVoice API (hardware-accelerated) (WARNING - currently broken: voices randomly disappear for unknown reasons)
`-DBACKEND_AUDIO=WiiU-Software` | Deliver audio with Wii U's AXVoice API (software-mixer)
`-DBACKEND_AUDIO=3DS-Hardware` | Deliver audio with 3DS's NDSP API (hardware-accelerated)
`-DBACKEND_AUDIO=3DS-Software` | Deliver audio with 3DS's NDSP API (software-mixer)
`-DBACKEND_AUDIO=Null` | Don't deliver audio at all (WARNING - game will have no audio)
`-DBACKEND_PLATFORM=SDL2` | (Default) Use SDL2 for miscellaneous platform-dependant operations
`-DBACKEND_PLATFORM=GLFW3` | Use GLFW3 for miscellaneous platform-dependant operations
`-DBACKEND_PLATFORM=WiiU` | Use the Wii U's native APIs for miscellaneous platform-dependant operations
`-DBACKEND_PLATFORM=3DS` | Use the 3DS's native APIs for miscellaneous platform-dependant operations
`-DBACKEND_PLATFORM=Null` | Don't do platform-dependant operations at all (WARNING - game will have no video or input)
`-DLTO=ON` | Enable link-time optimisation
`-DPKG_CONFIG_STATIC_LIBS=ON` | On platforms with pkg-config, static-link the dependencies (good for Windows builds, so you don't need to bundle DLL files)
`-DMSVC_LINK_STATIC_RUNTIME=ON` | Link the static MSVC runtime library, to reduce the number of required DLL files (Visual Studio only)
`-DFORCE_LOCAL_LIBS=ON` | Compile the built-in versions of SDL2, GLFW3, and FreeType instead of using the system-provided ones
`-DEXTRA_SOUND_FORMATS=ON` | Enable support for alternate music/SFX formats, include Ogg Vorbis, FLAC, and PxTone (not to be confused with PixTone)
`-DCLOWNAUDIO_STB_VORBIS=ON` | Enable support for Ogg Vorbis music/SFX
`-DCLOWNAUDIO_DR_FLAC=ON` | Enable support for FLAC music/SFX
`-DCLOWNAUDIO_LIBXMPLITE=ON` | Enable support for .it, .xm, .mod, .s3m music/SFX
`-DCLOWNAUDIO_PXTONE=ON` | Enable support for PxTone music/SFX (not to be confused with PixTone)

You can pass your own compiler flags with `-DCMAKE_C_FLAGS` and `-DCMAKE_CXX_FLAGS`.

You can then compile CSE2 with this command:

```
cmake --build build --config Release
```

If you're a Visual Studio user, you can open the generated `CSE2.sln` file
instead, which can be found in the `build` folder.

Once built, the executables can be found in the `game_english`/`game_japanese`
folder, depending on the selected language.

### Building for the Wii U

To target the Wii U, you'll need devkitPro, devkitPPC, and WUT.

First, add the devkitPPC tools directory to your PATH (because WUT's CMake
support is broken, as of writing):

```
PATH=$PATH:$DEVKITPPC/bin
```

Then, generate the build files with this command:

```
cmake -B buildwiiu -DCMAKE_BUILD_TYPE=Release -DFORCE_LOCAL_LIBS=ON -DBACKEND_PLATFORM=WiiU -DBACKEND_RENDERER=WiiU -DBACKEND_AUDIO=WiiU-Software -DCMAKE_TOOLCHAIN_FILE=$DEVKITPRO/wut/share/wut.toolchain.cmake
```

Finally, build the game with this command:

```
cmake --build buildwiiu
```

This will build a binary, but you still need to convert it to an `.rpx` file
that can be ran on your Wii U.

First, we need to strip the binary:

```
powerpc-eabi-strip -g game_english/CSE2
```

Then, we convert it to an `.rpx`:
```
elf2rpl game_english/CSE2 game_english/CSE2.rpx
```

`game_english/CSE2.rpx` is now ready to be ran on your Wii U. This port expects
the data folder to be in a folder called `CSE2-enhanced-en`/`CSE2-enhanced-jp`
on the root of your SD card.

### Building for the 3DS

To target the 3DS, you'll need devkitPro, devkitARM, Citro2D, Citro3D, libctru,
and bannertool, along with the `3dstools` and `devkitpro-pkgbuild-helpers`
packages.

Open a terminal, and `cd` into the CSE2 directory. Then execute this command:

```
cmake -B build3ds -DCMAKE_BUILD_TYPE=Release -DFORCE_LOCAL_LIBS=ON -DBACKEND_PLATFORM=3DS -DBACKEND_RENDERER=3DS -DBACKEND_AUDIO=3DS-Software -DFREETYPE_FONTS=ON -DCMAKE_TOOLCHAIN_FILE=$DEVKITPRO/3ds.cmake
```

(Note that `FREETYPE_FONTS` is enabled. If you're creating a Japanese build,
it's best to disable this, as the FreeType font is unreadable at 320x240).

This will create the build files. To build CSE2, run:

```
cmake --build build3ds
```

This will create an elf file. Before we can create a `.3dsx` file from it, we
need to make an `.smdh` file:

```
bannertool makesmdh -i $DEVKITPRO/libctru/default_icon.png -s "CSE2" -l "Port of Cave Story" -p "Clownacy" -o build3ds/smdh.smdh
```

We can finally generate a `.3dsx` file:

```
3dsxtool game_english/CSE2 game_english/CSE2.3dsx --romfs=game_english/data --smdh=build3ds/smdh.smdh
```
## Licensing

Being a decompilation, the majority of the code in this project is proprietary
and belongs to Daisuke "Pixel" Amaya.

Modifications and custom code are made available under the MIT licence. See
`LICENCE.txt` for details.
