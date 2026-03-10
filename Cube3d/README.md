# Cube3D

Raycasting 3D game (Cub3D-style) using MiniLibX.

## Build

```bash
make
```

Produces `cube3d`. On macOS the Makefile uses MiniLibX with OpenGL/AppKit; on Linux it uses X11.

## Run

```bash
./cube3d maps/Mine.cub
./cube3d maps/Lab.cub
./cube3d maps/door.cub   # map with a door (D) – use E to open/close
./cube3d maps/empty.cub
```

## .cub format

The map file must have extension `.cub` and contain, in order:

1. **Identifiers** (one per line, any order before the map):
   - `NO path` – North texture (XPM) – default: `./textures/north.xpm` (warm brick)
   - `SO path` – South texture – default: `./textures/south.xpm` (cool slate)
   - `EA path` – East texture – default: `./textures/east.xpm` (dark wood)
   - `WE path` – West texture – default: `./textures/west.xpm` (mossy stone)
   - `F R,G,B` or `F R G B` – Floor colour (0–255)
   - `C R,G,B` or `C R G B` – Ceiling colour (0–255)

2. **Map** (after all 6 identifiers):
   - Lines made only of: `0` (empty), `1` (wall), `D` (door, bonus), ` ` (space, treated as wall), and exactly one spawn:
     - `N` – North
     - `S` – South
     - `E` – East
     - `W` – West
   - The map must be closed (no holes to the outside).

Empty lines are allowed; the first line that looks like map content (only 0/1/N/S/E/W/space) after all identifiers are set is the start of the map.

## Controls

- **W / S** – Forward / Back
- **A / D** – Strafe left / right
- **Left / Right** – Turn
- **ESC** – Quit

### Bonus

- **Mouse** – Look / rotate view
- **M** – Toggle minimap (top-left corner)
- **E** – Open/close door when facing a door (map character `D`). Run `maps/door.cub` to see a door (drawn with a brown tint).

## Dependencies

- MiniLibX (included: `minilibx/`)
- macOS: OpenGL, AppKit  
- Linux: X11, Xext
