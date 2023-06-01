# Pong Prototype (Raylib C / C++)

A simple Pong prototype created with Raylib C / C++ for a university project.

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

- version –> Outputs the build version of the project and exits.
- preclear –> Clears the terminal before execution.
- postclear –> Clears the terminal after execution. (Only functions if game has been run)
- enabledebug –> Enables Debug mode, displaying game and object information.
- disableaudio –> Disables the game’s audio system, may throw errors in console.
- fullscreen –> Applies fullscreen mode if applicable, will upscale / downscale the window to the resolution you’re currently using on your primary monitor if necessary.

## Acknowledgements

 - [Raylib C / C++ Library](https://github.com/raysan5/raylib/tree/master)
 - [Raylib C / C++ Header](https://github.com/raysan5/raylib/blob/master/src/raylib.h)

## Copyright Information
Please refer to the "AudioCopyright.txt" file within the repository to learn more information regarding the usage of audio in this project, if you have any concerns regarding the audio usage and or licensing, then please don't hesitate to reach out and request further action to be taken.

## Building / Compiling

To use this project, you must have Visual Studio installed with C / C++ development tools and this github project cloned in order to build and compile your own variant of this project!
Basically your typical C / C++ Visual Studio project, that's all you really need to know besides the useage of Raylib's C / C++ Header.
