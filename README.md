## Сonsole game tic-tac-toe
### :video_game: Game review

![game](https://github.com/user-attachments/assets/a92cff77-5c55-419c-ba6e-b544fbe7c517)

### :star: Features

* The game graphics are drawn using ASCII
* Using modern C++20 standards
* Use of STL algorithms
* Protection from incorrect data entry
* Functions include turn selection, win/draw detection, and replayability without restarting the application

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
#### CMAke method

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
#### Manual method

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

### :heavy_exclamation_mark: My opinion

I wrote this game to practice my skills of C++, Git, and CMake. This simple example made me realize how complex it is to write high-quality programs.
