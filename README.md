# So Long

A 2D game project developed as part of the 42 curriculum, built using the MiniLibX graphics library.

## Description

So Long is a simple 2D game where the player must collect all collectibles and reach the exit to win. The game features:

- Player movement with arrow keys
- Collectible items to gather
- Exit door to reach
- Wall boundaries
- Enemy entities (bonus feature)
- Path validation to ensure all collectibles are reachable

## Features

- **Player Movement**: Navigate using arrow keys (↑↓←→)
- **Collectibles**: Gather all 'C' items on the map
- **Exit**: Reach the 'E' tile to win
- **Walls**: '1' characters create impassable boundaries
- **Enemies**: 'M' characters that move around the map (bonus)
- **Map Validation**: Ensures the map is solvable and valid

## Installation

### Prerequisites
- macOS or Linux system
- GCC compiler
- Make utility
- MiniLibX library (included in project)

### Building the Project

```bash
# Clone the repository
git clone https://github.com/ElieBalaa/so_long.git
cd so_long

# Compile the project
make

# Run the game with a map file
./so_long maps/test_map.ber
```

## Usage

### Running the Game

```bash
./so_long <map_file.ber>
```

### Controls
- **Arrow Keys**: Move the player
- **ESC**: Close the game
- **X (window close)**: Close the game

### Map Format

Maps are `.ber` files with the following characters:
- `1`: Wall (impassable)
- `0`: Empty space (walkable)
- `C`: Collectible item
- `E`: Exit
- `P`: Player starting position
- `M`: Enemy (bonus feature)

### Example Map Structure
```
1111111111
1C000000E1
1P00000001
1111111111
```

## Map Requirements

- Must be rectangular
- Must be surrounded by walls (`1`)
- Must contain exactly one player (`P`)
- Must contain at least one collectible (`C`)
- Must contain exactly one exit (`E`)
- All collectibles must be reachable
- Exit must be reachable

## Project Structure

```
so_long/
├── includes/          # Header files
├── src/              # Source code files
├── libft/            # Custom library functions
├── mlx/              # MiniLibX graphics library
├── maps/             # Map files for testing
├── textures/         # Game textures and sprites
├── get_next_line/    # Line reading utility
├── Makefile          # Build configuration
└── README.md         # This file
```

## Testing

The project includes various test maps in the `maps/` directory:
- `test_map.ber`: Basic test map
- `big_map.ber`: Large map for performance testing
- `complex_test.ber`: Complex map with multiple paths
- `invalid_map.ber`: Example of invalid map structure

## Memory Management

The project includes memory testing utilities:
- `memory_test.sh`: Automated memory leak testing
- `memory_analyzer.sh`: Memory analysis script

## Development

### Code Style
This project follows the 42 coding standards:
- Snake_case naming convention
- Maximum 25 lines per function
- Maximum 4 parameters per function
- Tab indentation
- 80 character line limit

### Building
```bash
make          # Build the project
make clean    # Clean object files
make fclean   # Clean everything including executable
make re       # Rebuild from scratch
```

## Author

**ElieBalaa** - [GitHub](https://github.com/ElieBalaa)

## License

This project is part of the 42 curriculum and follows their academic guidelines.

## Acknowledgments

- 42 School for the project requirements
- MiniLibX library for graphics functionality
- Libft library for utility functions
