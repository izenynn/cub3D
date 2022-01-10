# cub3D

## Info

This project is inspired by the world-famous Wolfenstein 3D game. which was the first FPS ever. Working with ray-casting the goal is to make a dynamic view inside a maze, in which you'll have to find your way.

- Status: on development
- Result: n/a
- Observations:
	- It is compatible with Linux and Mac OS.

*developed by: [izenynn](https://github.com/izenynn) and [0xk0sta](https://github.com/0xk0sta)*

## How to use

### Clone repo and submodules

```sh
git clone --recurse-submodules https://github.com/0xk0sta/cub3D.git
```

### Linux extra steps

- If you are using Linux, firts you will need to install a few dependencies

```sh
sudo apt-get update && sudo apt-get install xorg libxext-dev zlib1g-dev libbsd-dev
```

- Also, give execution permissions to the file `./lib/mlx_linux/configure`

```sh
chmod +x ./lib/mlx_linux/configure
```

### Change window resolution

Open the `Makefile`, go to line 53 and change WIN_H value to you desire windows height, and WIN_W value to the window width :)

- For Full HD example:

```make
CCFLAGS += -D WIN_H=1080 -D WIN_W=1920
```

## Compile

- Run `make` (make rules: `all`, `clean`, `fclean` and `re`)

```sh
make all clean
```

- Run `./cub3D` with a map as an argument (test maps on the `test_maps` folder)

```sh
./cub3D ./test_maps/labyrinth.cub
```

## If the program is closing instantly

I do not know for sure if this bug is related with minilibx, linux, or wsl.

This is because of ESC key ghosting. to fix this comment the lines that close the program when ESC key is pressed.

TODO: change the line below to the actual line

Go to `src/mlx_hook.c` and comment line 25 and 26:

```c
//if (keycode == KEY_ESC)
//	close_win(vars);
```

You will stil be able to exit either closing the window or by pressing CTRL + C on the terminal.

## MAC OS alternative version

If you have any issues on MAC OS, an alternative minilibx is included in the repo, just uncomment the lines 122 and 123, and comment lines 125 and 126 of the `Makefile` :)

- Before

```diff
ifeq ($(UNAME_S),Darwin)
	CFLAGS += -D OSX
#	########## SHARED VARS       ##########
	CCFLAGS += -framework OpenGL -framework AppKit
	LDLIBS = -lft -lmlx
#	########## mlx_mms           ##########
#	LMLX_NAME = $(LMLX_NAME_MMS)
#	LMLX_DIR = $(LMLX_DIR_MMS)
#	########## mlx_macos_sierra  ##########
	LMLX_NAME = $(LMLX_NAME_MACOS_SIERRA)
	LMLX_DIR = $(LMLX_DIR_MACOS_SIERRA)
endif
```

- After

```make
ifeq ($(UNAME_S),Darwin)
	CFLAGS += -D OSX
#	########## SHARED VARS       ##########
	CCFLAGS += -framework OpenGL -framework AppKit
	LDLIBS = -lft -lmlx
#	########## mlx_mms           ##########
	LMLX_NAME = $(LMLX_NAME_MMS)
	LMLX_DIR = $(LMLX_DIR_MMS)
#	########## mlx_macos_sierra  ##########
#	LMLX_NAME = $(LMLX_NAME_MACOS_SIERRA)
#	LMLX_DIR = $(LMLX_DIR_MACOS_SIERRA)
endif
```

## Screenshots

##
[![forthebadge](https://forthebadge.com/images/badges/made-with-c.svg)](https://forthebadge.com)
[![forthebadge](https://forthebadge.com/images/badges/compatibility-club-penguin.svg)](https://forthebadge.com)
