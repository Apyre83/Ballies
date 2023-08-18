# Ballies

Welcome to the "Ballies" game repository. This is a physics-based game where users can interact with bouncing balls and can also draw obstacles to influence the movement of these balls.

## Features

- **Move the Balls**: Click and drag a ball to move it wherever you desire.
- **Draw Obstacles**: Click and drag your mouse to draw obstacles which will influence the ball movements.
- **Collision Handling**: Balls bounce realistically off the window borders and against obstacles.
- **Switch Modes**: Press the "M" key to switch between "Sandbox" and "Race" modes.
  - **Sandbox Mode**: Freely move balls and create obstacles as you wish.
  - **Race Mode**: In this mode, balls aim to touch the bottom of the screen as quickly as possible. Once they reach the bottom, they are numbered according to their order of arrival and turn green.
- **Reset Game**: Press the "R" key to reset the game.
- **Delete Obstacles**: Press the "D" key to clear all drawn obstacles.
- **Pause the Game**: Press the "SPACE" key to pause or unpause the game.

## Compilation and Execution

You can compile and run the game using the provided `Makefile`. Here's how you can do it:

```bash
$ make
$ ./Ballies
```

## Dependencies

- [SFML](https://www.sfml-dev.org/): A simple and fast multimedia library for C++.

## Configuration

You can configure the initial obstacles by editing the `conf` file.

## Contribution

If you wish to contribute to the project, please open an issue or submit a pull request.
