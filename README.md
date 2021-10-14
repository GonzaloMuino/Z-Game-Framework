# Z Game Framework

Simple Game Framework that uses SDL2 as its base.

## Framework Setup

- Move Framework and change name of folders

- Start Visual Studio -> Open a project or Solution -> Select .sln in folder

- Rename Solution and Project Names

- For both Debug and Release

	- Project -> Properties -> Configuration Properties -> VC++ Directories -> Include Directories -> Add Local Dependencies/Includes

	- Library Directories -> Add Local Dependencies/Libraries

## Notes

- Both for Debug and Release, to try .exe it is necessary to copy Resources folder from src into Debug/Release folder

## Environment Setup From Scratch

- Download SDL 2 Development Libraries

- Install Visual Studio

- Create New Project [Visual C++ -> Empty Project]

- Create main.cpp

- Inside Project Directory create folder Dependencies

- Drag Includes folder inside Dependencies

- Create in Dependencies Libraries folder

- Drag Libraries files inside Libraries folder

- For both Debug and Release

	- Compile and execute program once

	- Inside created Folder [Debug/Release] drag all .dll files

	- Project -> Properties -> Configuration Properties -> VC++ Directories -> Include Directories -> Add Dependencies/Includes

	- Library Directories -> Add Dependencies/Libraries

	- Linker -> Input -> Additional Dependencies -> Add all .lib inside Dependencies/Libraries

	- Only in Debug: Linker -> System -> Subsystem -> Console

	- Only in Release: Linker -> System -> Subsystem -> Windows
