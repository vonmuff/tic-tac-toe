# Console Tic-Tac-Toe
### :video_game: Overview

![tictactoe](https://github.com/user-attachments/assets/b637cd26-0bc4-46d0-8f84-58aa4fccb0ca)

### :star: Features

#### :game_die: Game modes
* Local game for two players on one computer
* Playing against AI
#### :robot: Advanced AI
* The computer can block the player's winning moves.
* Seeking his own path to victory
* Imitates the process of ‘thinking through’ a move
#### :zap: Interface and UX
* The game graphics are drawn using ASCII
* Intuitive position selection with Numpad (1-9)
* Robust Input Validation
#### :hammer_and_wrench: Technical implementation
* Using modern C++20 standards
* Using of STL algorithms

### :computer: Technology stack 
* C++20
* CMake
* Git / GitHub 

### :file_folder: Project structure 
```
tictactoe/
├── CMakeLists.txt         
├── app/
│   ├── CMakeLists.txt
│   └── main.cpp
└── Game/
    ├── CMakeLists.txt
    ├── include/
    │   └── Game/
    │       └── Game.h
    └── source/
        └── Game.cpp
```

### :zap: How to run
#### Option 1: CMake

  1. Clone a remote repository:
```
git clone https://github.com/vonmuff/tic-tac-toe.git
```

  2. Create a folder for the build:
```
mkdir build
cd build
```

  3. Generate build files:
```
cmake ..
```

  4. Compile the project:
```
cmake --build .
```

  5. Run (the file will appear inside the app or Debug folder, depending on your OS):
```
./app/tictactoe.exe
```
#### Option 2: Manual Compilation (g++)

 1. Clone a remote repository:
```
git clone https://github.com/vonmuff/tic-tac-toe.git
```

 2. Ensure you are in the root folder of tictactoe
 3. Enter this command:
```
g++ -std=c++20 app/main.cpp Game/source/Game.cpp -o tictactoe -IGame/include
```

 4. Run the file:
```
./tictactoe.exe
```

### :thought_balloon: Learning Outcomes

I developed this project to practice skills in C++, Git, and CMake. Working on this example highlighted the importance of clean code structure and helped me understand the complexity behind writing high-quality software.
