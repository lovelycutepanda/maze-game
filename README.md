# Overview
This is a maze game application made with C++ and wxWidgets framework. The user can create a new maze and play with it, or have a search agent solve it automatically.


# Objective
In this project, I wish to achieve three main goals:
1. Familiarize myself with OOP (Object-Oriented Programming) features of C++
2. Gain experience in building GUI application
3. Demonstrate my abilities in algorithm design and implementation


# How to run
An executable file is included in the sample folder. You can simply run that file to run the program.
Alternative, you may also open Visual Studio through the .sln file, and build the code.
You may need to include the files in sample (except the .exe file) in the folder which contains the built program.


# Features
In this maze game, there are 3 menu bar functions: New maze, Solve and Help.

Each option under New maze stands for the respective algorithm for creating the maze board. 
Upon clicking, you will need to specify the number of rows and columns for the board to be generated.
It will then generate a playable board without loop, where you need to control the panda character using WASD control.
To win this game, you need to go from top-left grid (yellow) to bottom-right grid (green).

When a maze game is generated, you can also choose to solve the maze board using the Solve function.
Each option under Solve stands for the respective algorithm for solving the maze board. 
You can understand visually what each algorithm does and how it works, as the agent's search sequence will be shown using blue color.

Note that you can only use Solve functions after a board is created. 
You can also Solve multiple times using different algorithms for comparison.

There is an About option under Help. You may click to see some information about this game.
