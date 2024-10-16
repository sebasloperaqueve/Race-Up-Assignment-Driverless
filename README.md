# Race-Up-Assignment-Driverless
Here's a more concise version of the **README.md** file, keeping only the essential information:

---

# Maze Solver Program

## Description

This program solves a maze using the **Breadth-First Search (BFS)** algorithm. The maze is read from a `.txt` file, with:
- **`S`** as the starting point,
- **`E`** as the exit,
- **`.`** as open paths, and
- **`#`** as walls.

The program outputs the shortest path from `S` to `E` as a series of moves (UP, DOWN, LEFT, RIGHT). If no path exists, it will print "No solution found."

## How to Compile and Run

### 1. Create a Maze File

Example `maze.txt`:

```
S....
.###.
..E..
.#.#.
.....
```

### 2. Compile the Program

Run this command to compile:

```bash
gcc -o maze maze_solver.c
```

### 3. Execute the Program

Run the program by passing the maze file as an argument:

```bash
./maze maze.txt
```

Example output:

```
Solution: DOWN, DOWN, RIGHT
```

If no solution exists:

```
No solution found.
```

---

This version keeps the essential details while ensuring clarity on usage and functionality.
