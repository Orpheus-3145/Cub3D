# Cub3d
The aim of this project is to create a simpler clone of the 90' famous first person shooter [Wolfenstein](http://users.atw.hu/wolf3d/).

Cub3d was a project developed by my team-partner Choko ( <--- many thanks for the cooperation!) and me.

# Overview
The underlying goal of this project is to create and use a ray-casting algorithm able to render a sandobox environment where the player can move inside of it, even though it won't be able to shoot at spawning NPCs.

# Approach
## Parsing
First, because an evironment is rendered a configuration file needs to be parsed, to gather informations regarding:
- **graphic**: textures to apply on thes (4 are needed, for walls facing respectively North, South, East, West);
- **graphic**: colors (RGB) of the ceiling and the floor;
- **map**: a map is required to render the environment (see the subject for guidelines about how to draw a valid map).

**N.B.** for all rules regarding the format of the input file see the [subject](https://cdn.intra.42.fr/pdf/pdf/82527/en.subject.pdf);

**N.B.** there's another check performed by the parser and not required by the subject, that is done by a flood fill algorithm that ensures that no inaccessible rooms are admitted, i.e. the player can reach *every* empty spot inside the map.

## Ray Casting
Once the parsing is done, it is finally possible to render an image on the screen, as said before, the ray casting algorithm ([see that](https://lodev.org/cgtutor/raycasting.html)) is used: the view of the player is considered to be a range of rays projected from the position of the player on a straight line, because the map (and so the player) is surrounded by walls, the longer every ray travels before hitting a wall, the smaller that portion of wall (i.e. column of pixels) will be drawn.

# Playing
Once the game is running the following keys are available:
- **ESC** -> closes the game
- **W**, **A**, **S** and **D** -> allow the player to move
- **left arrow** and **right arrow** -> move the view on the left or right respectively
- **left key mouse** and drag -> moves the view depending on the direction of the dragging

A set of textures is already provided to enjoy the game, but it is still possibile to use some custom ones, their path must be written inside the parsed/input file and they *must* have a .png extension.

# Code
## Compiling and running
The project relies on the following submodules:
- [Libft](https://github.com/Orpheus-3145/Libft) for low level C operations;
- [MLX42](https://github.com/codam-coding-college/MLX42) graphical library which in turn depends on MiniLibX.

1. `make`    creates the executable;
1. `make run`    calls `make` and runs the executable with the default arguments;
1. `make clean`    removes object files;
1. `make fclean`    calls `make clean` and removes the executable;
1. `make re`    calls `make fclean` and then `make`;

To execute the project without using `make run` is necessary to provide an argument that represent the path of the input/parsed file.

## Structure
	include/			<- header file
	libft/  			<- auxiliary submodule 
	MLX42/  			<- auxiliary submodule 
	objects/			<- object files
	sources/			<- source C files
		app/			<- handling of the MLX42 API
		check_map/		<- specific checks on the input map
		init/			<- constructors
		main/			<- main function
		parser/			<- parsing of the input file to gather info
		render/			<- low level rendering done with ray-casting
		tools/			<- generic functions

# References
- 42 project: [cub3d](https://cdn.intra.42.fr/pdf/pdf/82527/en.subject.pdf)
- By: [Francesco Aru](https://github.com/Orpheus-3145) and [Itopchu](https://github.com/Am0rA), francesco.aru25@gmail.com, intra42/slack nickname: @faru, Codam, Amsterdam