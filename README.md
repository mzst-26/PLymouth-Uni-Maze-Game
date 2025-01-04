# PLymouth-Uni-Maze-Game
This repository contains the maze game code for the 1000 coursework.
I am using Mac VS code as VS is no longer available for Mac. I tried to put as much information as I can to make it easier to run this code.

# Game Overview
This code is for a maze game where a player must navigate through a procedurally generated maze to reach an exit door while avoiding enemies. The game features:

- **Maze Generation**: A maze is generated with walls, a player starting position, an exit door, and enemy positions. some walls are randomly removed for easier navigation in the game and avoiding one path to the exit/player.
- **Player Movement**: The player can move up, down, left, or right using keyboard input.
- **Enemy AI**: Enemies move towards the player using a A* pathfinding algorithm.
- **Apples**: Apples are scattered throughout the maze, and collecting them rewards the player.Apples also stop enemies for 8 seconds.
- **Time Limit**: The player must complete the level within a time limit.
- **Difficulty Levels**: The game has multiple difficulty levels, which affect the maze size, enemy speed, and time limit.
- **Game Over**: The game ends if the player is caught by an enemy or the time limit expires.
- **Level Completion**: The player completes a level by reaching the exit door, and their progress is saved and are reworded based on the time of completion and amount of apples eaten.
- **Main Menu**: The game has a main menu with options to start a new game, resume a saved game, change difficulty or quit.

---

## Gameplay Preview

Below is a short preview of the gameplay:




https://github.com/user-attachments/assets/5cd0aee3-5260-488f-ae04-d1cd94358a9b

# Maze Game - Installation and Running Guide
This is a university game project that can be set up and run on Windows or Mac using Visual Studio or VS Code. This guide provides detailed instructions for configuring the project and running it successfully.

## Table of Contents
- [Windows Instructions](#windows-instructions)
  - [Using Visual Studio](#using-visual-studio-on-windows)
  - [Using VS Code](#using-vs-code-on-windows)
- [Mac Instructions](#mac-instructions)
  - [Using VS Code](#using-vs-code-on-mac)
- [Troubleshooting](#troubleshooting)

---

## Windows Instructions

### Using Visual Studio on Windows

1. ### Install SFML :
   - Download the [SFML SDK for Windows](https://www.sfml-dev.org/download.php).
   - Extract the zip file to a directory, e.g., `C:\SFML`.
   - Add `C:\SFML\bin` to your system's PATH:
     1. Right-click on "This PC" or "Computer" and select **Properties**.
     2. Go to **Advanced system settings > Environment Variables**.
     3. Under **System Variables**, edit the `Path` variable:
        - Click **New** and add `C:\SFML\bin`.
        - Click **OK** to save.

2. **Install Visual Studio**:
   - Download and install [Visual Studio](https://visualstudio.microsoft.com/).

3. **Clone the Repository**:
   - Open Visual Studio and select **Clone a repository**.
   - Enter the repository URL:
     ```bash
     https://github.com/mzst-26/PLymouth-Uni-Maze-Game
     ```

4. **Create a New Project**:
   - Go to **File > New > Project...**.
   - Choose **Visual C++ > Empty Project**, and name it (e.g., `Maze Escape`).

5. **Add SFML to the Project**:
   - In Solution Explorer, right-click the project and select **Properties**.
   - Configure the following:
     - **C/C++ > General**: Add the include path:
       ```
       C:\SFML\include
       ```
     - **Linker > General**: Add the library path:
       ```
       C:\SFML\lib
       ```

6. **Build and Run**:
   - Right-click the project in Solution Explorer and select **Build**.
   - Once built, select **Debug > Start Debugging** to run the game.

---

### Using VS Code on Windows

1. **Install SFML**:
   - Follow the steps in the [Install SFML](#install-sfml) section.

2. **Install the C/C++ Extension**:
   - Open VS Code and click on the **Extensions** view (or press `Ctrl+Shift+X`).
   - Search for **C/C++** and click **Install**.

3. **Clone the Repository**:
   - Open a terminal in VS Code (press `` Ctrl+` ``) and run:
     ```bash
     git clone https://github.com/mzst-26/PLymouth-Uni-Maze-Game
     cd PLymouth-Uni-Maze-Game
     ```

4. **Configure Build Tasks**:
   - Open the Command Palette (`Ctrl+Shift+P`) and select **Configure Build Task**.
   - Edit `tasks.json` as follows:
     ```json
     {
       "version": "2.0.0",
       "tasks": [
         {
           "label": "Build Maze Escape",
           "type": "shell",
           "command": "g++",
           "args": [
             "-o", "${fileDirname}/${fileBasenameNoExtension}",
             "${file}",
             "-I", "C:/SFML/include",
             "-L", "C:/SFML/lib",
             "-lsfml-graphics", "-lsfml-window", "-lsfml-system"
           ],
           "group": { "kind": "build", "isDefault": true },
           "problemMatcher": ["$gcc"]
         }
       ]
     }
     ```

5. **Build and Run**:
   - Open `main.cpp`, then press `Ctrl+Shift+B` to build.
   - Run the executable from the terminal:
     ```bash
     ./main.exe
     ```
     or your own build file name
      ```bash
     ./myBuildFileName.exe
     ```

---

## Mac Instructions

### Using VS Code on Mac

1. **Install SFML**:
   - Run the following command:
     ```bash
     brew install sfml
     ```

2. **Install the C/C++ Extension**:
   - Search C++ Extension on the apps within VS code.

3. **Clone the Repository**:
   - Open a terminal in VS Code and run:
     ```bash
     git clone https://github.com/mzst-26/PLymouth-Uni-Maze-Game
     cd PLymouth-Uni-Maze-Game
     ```

4. **Configure Build Tasks**:
   - Edit `tasks.json` as follows:
     ```json
     {
       "version": "2.0.0",
       "tasks": [
         {
           "label": "Build Maze Escape",
           "type": "shell",
           "command": "g++",
           "args": [
             "-o", "${fileDirname}/${fileBasenameNoExtension}",
             "${file}",
             "-I", "/usr/local/include",
             "-L", "/usr/local/lib",
             "-lsfml-graphics", "-lsfml-window", "-lsfml-system"
           ],
           "group": { "kind": "build", "isDefault": true },
           "problemMatcher": ["$gcc"]
         }
       ]
     }
     ```
    - Here is my example of `tasks.json`:
      ```json
            {
            "version": "2.0.0",
            "tasks": [
                {
                    "label": "build",
                    "type": "shell",
                    "command": "g++",
                    "args": [
                        "-std=c++17",
                        "-g",
                        "-I/opt/homebrew/include",
                        "-L/opt/homebrew/lib",
                        "-lsfml-graphics",
                        "-lsfml-window",
                        "-lsfml-system",
                        "-lsfml-audio",
                        "src/maze.cpp",
                        "src/main.cpp",
                        "src/player.cpp",
                        "src/enemy.cpp",
                        "src/a_star.cpp",
                        "src/game.cpp",
                        "src/button.cpp",
                        "src/settingsPopup.cpp",
                        "src/escapeDoor.cpp",
                        "src/levelManager.cpp",
                        "src/winOrLooseWindow.cpp",
                        "src/home.cpp",
                        "src/stars.cpp",
                        "src/scoreBoard.cpp",
                        "src/modules.cpp",
                        "src/apples.cpp",
                        "-o",
                        "build/MysteryMaze"
                    ],
                    "group": {
                        "kind": "build",
                        "isDefault": true
                    },
                    "problemMatcher": ["$gcc"],
                    "detail": "Compile all source files with SFML"
                }
            ]
        }

      ```

     - And this is  my example of `c_cpp_properties.json`:
      ```json
        {
        "version": 4,
        "configurations": [
            {
            "name": "macos-clang-arm64",
            "includePath": [
                "${workspaceFolder}/**"
            ],
            "defines": [],
            "compilerPath": "/usr/bin/clang",
            "intelliSenseMode": "macos-clang-arm64",
            "browse": {
                "path": [
                "${workspaceFolder}",
                "/opt/homebrew/include",
                "/opt/homebrew/include/SFML"
                ],
                "limitSymbolsToIncludedHeaders": true
            },
            "cStandard": "${default}",
            "cppStandard": "${default}"
            }
        ]
        }
      ```
      - And `c_cpp_properties`:
      ```json
        {
            "version": "0.2.0",
            "configurations": [
                {
                "type": "lldb",
                "request": "launch",
                "name": "Debug",
                "program": "${workspaceFolder}/build/MysteryMaze",
                "args": [],
                "cwd": "${workspaceFolder}",
                "preLaunchTask": "build"
                },
                {
                "name": "C/C++ Runner: Debug Session",
                "type": "lldb",
                "request": "launch",
                "args": [],
                "cwd": "/Users/mobinzaki/Documents/GitHub/PLymouth-Uni-Maze-Game/src",
                "program": "/Users/mobinzaki/Documents/GitHub/PLymouth-Uni-Maze-Game/src/build/Debug/outDebug"
                }
            ]
        }
        
    ```

    - All of this configuration files would be in .vscode directory.


5. **Build and Run**:
   - Open `main.cpp`, then press `Ctrl+Shift+B` to build.
   - Run the executable from the terminal:
     ```bash
     ./main
     ```
     or ./yourOwnBuildFileName

---

## Troubleshooting

- **SFML Issues**: Verify that the paths to SFML libraries and headers are correctly set.
- **Compilation Errors**: Ensure the g++ command or project settings match your setup.
- **Additional Help**: Refer to the [SFML documentation](https://www.sfml-dev.org/documentation.php).

