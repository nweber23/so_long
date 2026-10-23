*This project has been created as part of the 42 curriculum by nweber.*

# So Long

## Description

A small 2D game built with [MLX42](https://github.com/codam-coding-college/MLX42).
A dolphin collects every fish on the map and then escapes through the portal.
The map is read from a `.ber` file, validated (rectangular, walled in, one `P`, one `E`, at least one `C`, and a reachable path to every `C` and the `E`) and rendered with one image per tile.

Bonus: crab patrols that kill the player on contact, sprite animation, and the move counter drawn on screen.

## Instructions

```sh
make            # clones and builds MLX42 on first run, then builds ./so_long
./so_long maps/small.ber

make bonus      # builds ./so_long_bonus
./so_long_bonus maps/bonus/patrol.ber
```

Needs `cmake`, `glfw` and its dev headers. Run from the repository root (textures are loaded by relative path).

| Key | Action |
| --- | --- |
| `W` `A` `S` `D` / arrows | move |
| `ESC` / window cross | quit |

Map characters: `0` empty, `1` wall, `C` collectible, `E` exit, `P` start, and `N` enemy (bonus only, patrols horizontally).

`make clean`, `make fclean` (also removes `MLX42`) and `make re` are available.

## Resources

- [MLX42 documentation](https://github.com/codam-coding-college/MLX42/wiki)
- [GLFW documentation](https://www.glfw.org/documentation.html)
- [Flood fill](https://en.wikipedia.org/wiki/Flood_fill)

AI use: Claude Code generated the first version of the sources, the textures (drawn procedurally with a Python script), the maps and this README. All of it was reviewed and tested by the author.
