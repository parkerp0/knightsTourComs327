This is a solution to the knights tour problem written in C. 
This implementation uses graph to map all of the knights moves so that it doesn't need to calculate which moves are valid more than once.
Algorithmically I uses the standard recursive approach of checking depth first.
The function edgebuilder sets up the structs to build the graph.
The function solver is the main recursive function that checks each possible path and steps back if there are no available moves.
The function nodeTest is an old function that was used to test that the graph was being built correctly and all the edges were correct.
The program is scalable to any rectangular size of board however I didn't not impliment argument parsing so it needs to be changed inside of #define at the top of main.c