# Pong Prototype (Raylib C / C++)

A simple pong prototype done with Raylib C / C++ for a school project.
There's not really much else to it honestly.

# Keybindings

> Player 1:
```
Q = Move Up
A = Move Down
Left ALT = Speed Up
```

> Player 2:
```
P = Move Up
L = Move Down
Right ALT = Speed Up
```

> Shared:
```
Tab = Pause the current Game Session, Will enable pressing "Backspace" to Exit
Backspace = Exit to Title Screen (Only works during Gameplay!)
Enter = Continue / Rematch (Only works during Gameplay!)
```

## Console Commands
Seeing as running the program within a console is recommended, I've taken the liberty to create some commands that you can use after typing the application name out in the console! Here's the ones that are valid to use:

- version | Prints out the Version identifier of the Project and closes.
- preclear | Clears all output of the console before execution (Windows only for now!)
- postclear | Clears all output of the console after execution (Windows only for now!)
- enabldedebug | Enables Debug Mode, which allows you to see player, ball and frametime information.
- disableaudio | Disables all Audio, muting the game if that's what you would prefer.
- fullscreen | Resizes the Window to your monitor's maximum resolution and Fullscreens the window.

## Acknowledgements

 - [Raylib C/C++ Library](https://github.com/raysan5/raylib/tree/master)
 - [Raylib C/C++ Header](https://github.com/raysan5/raylib/blob/master/src/raylib.h)

## Building / Compiling

To use this project, you must have Visual Studio installed with C / C++ development tools and this github project cloned in order to build and compile your own variant of this project!
Basically your typical C / C++ Visual Studio project, that's all you really need to know besides the useage of Raylib's C / C++ Header.

test edit
