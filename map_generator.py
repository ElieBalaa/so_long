#!/usr/bin/env python3
"""
So Long Map Generator
Professional map generator for the so_long game following 42 school norms.
Created for automatic generation of valid .ber map files.

Author: AI Assistant
Version: 1.0
"""

import os
import sys
import random
from typing import List, Tuple, Optional
from dataclasses import dataclass
from enum import Enum


class MapElement(Enum):
    """Map element types with their character representations."""
    WALL = '1'
    FLOOR = '0'
    PLAYER = 'P'
    EXIT = 'E'
    COLLECTIBLE = 'C'
    STATIC_ENEMY = 'T'
    PATROL_ENEMY = 'M'


@dataclass
class MapConfig:
    """Configuration for map generation."""
    width: int
    height: int
    min_collectibles: int
    max_collectibles: int
    static_enemies: int
    patrol_enemies: int
    complexity: str  # 'simple', 'medium', 'complex'
    filename: str


class Color:
    """ANSI color codes for terminal output."""
    RED = '\033[91m'
    GREEN = '\033[92m'
    YELLOW = '\033[93m'
    BLUE = '\033[94m'
    MAGENTA = '\033[95m'
    CYAN = '\033[96m'
    WHITE = '\033[97m'
    BOLD = '\033[1m'
    END = '\033[0m'


class MapGenerator:
    """Professional map generator for so_long game."""
    
    def __init__(self):
        self.map_grid: List[List[str]] = []
        self.config: Optional[MapConfig] = None
        self.player_pos: Optional[Tuple[int, int]] = None
        self.exit_pos: Optional[Tuple[int, int]] = None
        self.collectibles: List[Tuple[int, int]] = []
        
    def print_header(self):
        """Print professional header."""
        print(f"\n{Color.CYAN}{'='*60}{Color.END}")
        print(f"{Color.BOLD}{Color.CYAN}🎮 SO LONG MAP GENERATOR 🎮{Color.END}")
        print(f"{Color.CYAN}Professional Map Generator for 42 School Project{Color.END}")
        print(f"{Color.CYAN}{'='*60}{Color.END}\n")
    
    def print_rules(self):
        """Display map validation rules."""
        print(f"{Color.YELLOW}📋 MAP VALIDATION RULES:{Color.END}")
        print(f"   • Rectangular shape (all lines same length)")
        print(f"   • Surrounded by walls (1)")
        print(f"   • Exactly 1 player (P) and 1 exit (E)")
        print(f"   • At least 1 collectible (C)")
        print(f"   • Valid characters: 0,1,C,E,P,T,M")
        print(f"   • All collectibles and exit must be reachable\n")
    
    def get_user_input(self) -> MapConfig:
        """Get user preferences with comprehensive validation."""
        self.print_header()
        self.print_rules()
        
        print(f"{Color.BOLD}🛠️  MAP CONFIGURATION{Color.END}")
        
        # Get map dimensions
        width = self._get_integer_input(
            "Map width (minimum 5, maximum 30): ",
            min_val=5, max_val=30, default=20
        )
        
        height = self._get_integer_input(
            "Map height (minimum 5, maximum 17): ",
            min_val=5, max_val=17, default=15
        )
        
        # Calculate reasonable collectible range
        max_possible = max(1, (width - 2) * (height - 2) // 4)
        
        min_collectibles = self._get_integer_input(
            "Minimum collectibles (at least 1): ",
            min_val=1, max_val=max_possible, default=3
        )
        
        max_collectibles = self._get_integer_input(
            f"Maximum collectibles (max {max_possible}): ",
            min_val=min_collectibles, max_val=max_possible, 
            default=min(min_collectibles + 5, max_possible)
        )
        
        # Get enemy counts
        max_enemies = max(0, (width - 2) * (height - 2) // 8)
        
        static_enemies = self._get_integer_input(
            f"Static enemies (T) [0-{max_enemies}]: ",
            min_val=0, max_val=max_enemies, default=2
        )
        
        patrol_enemies = self._get_integer_input(
            f"Patrol enemies (M) [0-{max_enemies - static_enemies}]: ",
            min_val=0, max_val=max(0, max_enemies - static_enemies), default=2
        )
        
        # Get complexity level
        complexity = self._get_choice_input(
            "Map complexity",
            ["simple", "medium", "complex"],
            descriptions=[
                "Simple: Open layout, few walls",
                "Medium: Some rooms and corridors", 
                "Complex: Multiple rooms, challenging layout"
            ],
            default="medium"
        )
        
        # Get filename
        filename = self._get_filename_input()
        
        return MapConfig(
            width=width,
            height=height,
            min_collectibles=min_collectibles,
            max_collectibles=max_collectibles,
            static_enemies=static_enemies,
            patrol_enemies=patrol_enemies,
            complexity=complexity,
            filename=filename
        )
    
    def _get_integer_input(self, prompt: str, min_val: int, max_val: int, 
                          default: int) -> int:
        """Get validated integer input from user."""
        while True:
            try:
                user_input = input(f"{Color.BLUE}{prompt}{Color.END}").strip()
                if not user_input:
                    print(f"{Color.GREEN}Using default: {default}{Color.END}")
                    return default
                
                value = int(user_input)
                if min_val <= value <= max_val:
                    return value
                else:
                    print(f"{Color.RED}❌ Value must be between {min_val} and {max_val}{Color.END}")
            except ValueError:
                print(f"{Color.RED}❌ Please enter a valid number{Color.END}")
    
    def _get_choice_input(self, prompt: str, choices: List[str], 
                         descriptions: List[str], default: str) -> str:
        """Get validated choice input from user."""
        print(f"\n{Color.BOLD}{prompt}:{Color.END}")
        for i, (choice, desc) in enumerate(zip(choices, descriptions), 1):
            marker = "👉" if choice == default else "  "
            print(f"{marker} {i}. {choice.title()}: {desc}")
        
        while True:
            try:
                user_input = input(f"\n{Color.BLUE}Choose (1-{len(choices)}) [default: {default}]: {Color.END}").strip()
                if not user_input:
                    return default
                
                choice_num = int(user_input)
                if 1 <= choice_num <= len(choices):
                    return choices[choice_num - 1]
                else:
                    print(f"{Color.RED}❌ Please choose between 1 and {len(choices)}{Color.END}")
            except ValueError:
                print(f"{Color.RED}❌ Please enter a valid number{Color.END}")
    
    def _get_filename_input(self) -> str:
        """Get validated filename input."""
        while True:
            filename = input(f"{Color.BLUE}Output filename (without .ber extension): {Color.END}").strip()
            
            if not filename:
                filename = "generated_map"
            
            # Sanitize filename
            filename = "".join(c for c in filename if c.isalnum() or c in "._-")
            
            if not filename:
                print(f"{Color.RED}❌ Invalid filename. Using 'generated_map'{Color.END}")
                filename = "generated_map"
            
            full_path = f"maps/{filename}.ber"
            
            if os.path.exists(full_path):
                overwrite = input(f"{Color.YELLOW}⚠️  File exists. Overwrite? (y/N): {Color.END}").strip().lower()
                if overwrite in ['y', 'yes']:
                    return filename
                else:
                    continue
            
            return filename
    
    def generate_map(self, config: MapConfig) -> bool:
        """Generate a valid map based on configuration."""
        self.config = config
        
        print(f"\n{Color.BOLD}🔧 GENERATING MAP...{Color.END}")
        
        max_attempts = 50
        for attempt in range(max_attempts):
            try:
                print(f"Attempt {attempt + 1}/{max_attempts}", end="\r")
                
                # Initialize empty map
                self._initialize_map()
                
                # Add borders
                self._add_borders()
                
                # Place player and exit
                if not self._place_player_and_exit():
                    continue
                
                # Add complexity-based walls
                self._add_internal_walls()
                
                # Place collectibles
                if not self._place_collectibles():
                    continue
                
                # Validate connectivity before placing enemies
                if not self._validate_map():
                    continue
                
                # Place enemies (this method now ensures they don't block paths)
                self._place_enemies()
                
                # Final validation after enemy placement
                if self._validate_final_map():
                    print(f"\n{Color.GREEN}✅ Valid map generated successfully!{Color.END}")
                    return True
                
            except Exception as e:
                print(f"\n{Color.RED}❌ Error in attempt {attempt + 1}: {e}{Color.END}")
                continue
        
        print(f"\n{Color.RED}❌ Failed to generate valid map after {max_attempts} attempts{Color.END}")
        return False
    
    def _initialize_map(self):
        """Initialize empty map with floors."""
        self.map_grid = [[MapElement.FLOOR.value for _ in range(self.config.width)] 
                        for _ in range(self.config.height)]
        self.player_pos = None
        self.exit_pos = None
        self.collectibles = []
    
    def _add_borders(self):
        """Add wall borders around the map."""
        # Top and bottom borders
        for x in range(self.config.width):
            self.map_grid[0][x] = MapElement.WALL.value
            self.map_grid[self.config.height - 1][x] = MapElement.WALL.value
        
        # Left and right borders
        for y in range(self.config.height):
            self.map_grid[y][0] = MapElement.WALL.value
            self.map_grid[y][self.config.width - 1] = MapElement.WALL.value
    
    def _place_player_and_exit(self) -> bool:
        """Place player and exit in valid positions."""
        available_positions = self._get_available_positions()
        
        if len(available_positions) < 2:
            return False
        
        # Place player (preferably in top-left area)
        player_candidates = [pos for pos in available_positions 
                           if pos[0] < self.config.height // 2 and pos[1] < self.config.width // 2]
        
        if not player_candidates:
            player_candidates = available_positions
        
        self.player_pos = random.choice(player_candidates)
        self.map_grid[self.player_pos[0]][self.player_pos[1]] = MapElement.PLAYER.value
        
        # Place exit (preferably in bottom-right area, away from player)
        exit_candidates = [pos for pos in available_positions 
                          if pos != self.player_pos and
                          abs(pos[0] - self.player_pos[0]) + abs(pos[1] - self.player_pos[1]) > 3]
        
        if not exit_candidates:
            exit_candidates = [pos for pos in available_positions if pos != self.player_pos]
        
        if not exit_candidates:
            return False
        
        self.exit_pos = random.choice(exit_candidates)
        self.map_grid[self.exit_pos[0]][self.exit_pos[1]] = MapElement.EXIT.value
        
        return True
    
    def _add_internal_walls(self):
        """Add internal walls based on complexity."""
        if self.config.complexity == "simple":
            self._add_simple_walls()
        elif self.config.complexity == "medium":
            self._add_medium_walls()
        else:
            self._add_complex_walls()
    
    def _add_simple_walls(self):
        """Add minimal internal walls."""
        wall_count = max(1, (self.config.width * self.config.height) // 20)
        self._place_random_walls(wall_count)
    
    def _add_medium_walls(self):
        """Add moderate internal walls with some structure."""
        # Add some rooms
        self._create_rooms(2)
        # Add random walls
        wall_count = (self.config.width * self.config.height) // 15
        self._place_random_walls(wall_count)
    
    def _add_complex_walls(self):
        """Add complex wall patterns with multiple rooms."""
        # Add multiple rooms
        self._create_rooms(4)
        # Add corridors
        self._create_corridors()
        # Add random walls
        wall_count = (self.config.width * self.config.height) // 12
        self._place_random_walls(wall_count)
    
    def _create_rooms(self, room_count: int):
        """Create rectangular rooms."""
        for _ in range(room_count):
            # Ensure minimum room size and proper bounds
            max_room_width = max(3, min(8, self.config.width // 3))
            max_room_height = max(3, min(6, self.config.height // 3))
            
            room_width = random.randint(3, max_room_width)
            room_height = random.randint(3, max_room_height)
            
            # Ensure there's space for the room
            max_start_x = max(2, self.config.width - room_width - 2)
            max_start_y = max(2, self.config.height - room_height - 2)
            
            if max_start_x < 2 or max_start_y < 2:
                continue  # Skip if map is too small for rooms
            
            start_x = random.randint(2, max_start_x)
            start_y = random.randint(2, max_start_y)
            
            # Create room outline
            for y in range(start_y, min(start_y + room_height, self.config.height - 1)):
                for x in range(start_x, min(start_x + room_width, self.config.width - 1)):
                    if (y == start_y or y == start_y + room_height - 1 or
                        x == start_x or x == start_x + room_width - 1):
                        if (self.map_grid[y][x] == MapElement.FLOOR.value and
                            (y, x) != self.player_pos and (y, x) != self.exit_pos):
                            self.map_grid[y][x] = MapElement.WALL.value
            
            # Add door (only if room is large enough)
            if room_width > 3 and room_height > 3:
                if random.choice([True, False]):  # Horizontal door
                    door_x = random.randint(start_x + 1, min(start_x + room_width - 2, self.config.width - 2))
                    door_y = start_y if random.choice([True, False]) else start_y + room_height - 1
                    if 0 < door_y < self.config.height - 1:
                        self.map_grid[door_y][door_x] = MapElement.FLOOR.value
    
    def _create_corridors(self):
        """Create corridor connections."""
        corridor_count = random.randint(1, 3)
        for _ in range(corridor_count):
            if random.choice([True, False]):  # Horizontal corridor
                y = random.randint(2, self.config.height - 3)
                start_x = random.randint(1, self.config.width // 2)
                end_x = random.randint(self.config.width // 2, self.config.width - 2)
                for x in range(start_x, end_x):
                    if (y, x) != self.player_pos and (y, x) != self.exit_pos:
                        self.map_grid[y][x] = MapElement.FLOOR.value
            else:  # Vertical corridor
                x = random.randint(2, self.config.width - 3)
                start_y = random.randint(1, self.config.height // 2)
                end_y = random.randint(self.config.height // 2, self.config.height - 2)
                for y in range(start_y, end_y):
                    if (y, x) != self.player_pos and (y, x) != self.exit_pos:
                        self.map_grid[y][x] = MapElement.FLOOR.value
    
    def _place_random_walls(self, count: int):
        """Place random walls without blocking paths."""
        placed = 0
        attempts = 0
        max_attempts = count * 10
        
        while placed < count and attempts < max_attempts:
            attempts += 1
            y = random.randint(1, self.config.height - 2)
            x = random.randint(1, self.config.width - 2)
            
            if (self.map_grid[y][x] == MapElement.FLOOR.value and
                (y, x) != self.player_pos and (y, x) != self.exit_pos):
                
                # Temporarily place wall and check if paths remain valid
                original = self.map_grid[y][x]
                self.map_grid[y][x] = MapElement.WALL.value
                
                if self._check_basic_connectivity():
                    placed += 1
                else:
                    self.map_grid[y][x] = original
    
    def _place_collectibles(self) -> bool:
        """Place collectibles in valid positions."""
        available_positions = self._get_available_positions()
        
        collectible_count = random.randint(self.config.min_collectibles, 
                                         self.config.max_collectibles)
        
        if len(available_positions) < collectible_count:
            return False
        
        selected_positions = random.sample(available_positions, collectible_count)
        
        for pos in selected_positions:
            self.map_grid[pos[0]][pos[1]] = MapElement.COLLECTIBLE.value
            self.collectibles.append(pos)
        
        return True
    
    def _place_enemies(self):
        """Place enemies in valid positions without blocking critical paths."""
        available_positions = self._get_available_positions()
        
        # Remove positions that are critical for path connectivity
        safe_positions = self._filter_safe_enemy_positions(available_positions)
        
        # Place static enemies
        static_count = min(self.config.static_enemies, len(safe_positions))
        if static_count > 0:
            static_positions = random.sample(safe_positions, static_count)
            for pos in static_positions:
                # Test if placing enemy here blocks any paths
                if self._can_place_enemy_at(pos):
                    self.map_grid[pos[0]][pos[1]] = MapElement.STATIC_ENEMY.value
                    safe_positions.remove(pos)
        
        # Place patrol enemies
        patrol_count = min(self.config.patrol_enemies, len(safe_positions))
        if patrol_count > 0:
            patrol_positions = random.sample(safe_positions, patrol_count)
            for pos in patrol_positions:
                # Test if placing enemy here blocks any paths
                if self._can_place_enemy_at(pos):
                    self.map_grid[pos[0]][pos[1]] = MapElement.PATROL_ENEMY.value
    
    def _filter_safe_enemy_positions(self, positions: List[Tuple[int, int]]) -> List[Tuple[int, int]]:
        """Filter positions to avoid critical path areas."""
        safe_positions = []
        
        for pos in positions:
            y, x = pos
            
            # Don't place enemies too close to player or exit
            if (abs(y - self.player_pos[0]) + abs(x - self.player_pos[1]) < 3 or
                abs(y - self.exit_pos[0]) + abs(x - self.exit_pos[1]) < 2):
                continue
            
            # Don't place enemies adjacent to collectibles
            is_near_collectible = False
            for cy, cx in self.collectibles:
                if abs(y - cy) + abs(x - cx) <= 1:
                    is_near_collectible = True
                    break
            
            if not is_near_collectible:
                safe_positions.append(pos)
        
        return safe_positions
    
    def _can_place_enemy_at(self, pos: Tuple[int, int]) -> bool:
        """Test if placing an enemy at position doesn't block critical paths."""
        y, x = pos
        
        # Temporarily place enemy
        original = self.map_grid[y][x]
        self.map_grid[y][x] = MapElement.STATIC_ENEMY.value
        
        # Check if all collectibles are still reachable and exit accessible after collecting all
        is_valid = self._check_path_connectivity()
        
        # Restore original
        self.map_grid[y][x] = original
        
        return is_valid
    
    def _get_available_positions(self) -> List[Tuple[int, int]]:
        """Get list of available floor positions."""
        positions = []
        for y in range(1, self.config.height - 1):
            for x in range(1, self.config.width - 1):
                if self.map_grid[y][x] == MapElement.FLOOR.value:
                    positions.append((y, x))
        return positions
    
    def _check_basic_connectivity(self) -> bool:
        """Quick connectivity check without full flood fill."""
        if not self.player_pos or not self.exit_pos or not self.collectibles:
            return False
        
        # Use the same sophisticated check as the main validation
        return self._check_path_connectivity()
    
    def _validate_map(self) -> bool:
        """Comprehensive map validation following so_long rules."""
        try:
            # Check rectangular shape
            if not self._check_rectangular():
                return False
            
            # Check borders
            if not self._check_borders():
                return False
            
            # Check required elements
            if not self._check_required_elements():
                return False
            
            # Check path connectivity (flood fill)
            if not self._check_path_connectivity():
                return False
            
            return True
            
        except Exception:
            return False
    
    def _check_rectangular(self) -> bool:
        """Check if map is perfectly rectangular."""
        if not self.map_grid:
            return False
        
        expected_width = len(self.map_grid[0])
        return all(len(row) == expected_width for row in self.map_grid)
    
    def _check_borders(self) -> bool:
        """Check if map is surrounded by walls."""
        # Top and bottom borders
        for x in range(self.config.width):
            if (self.map_grid[0][x] != MapElement.WALL.value or
                self.map_grid[self.config.height - 1][x] != MapElement.WALL.value):
                return False
        
        # Left and right borders
        for y in range(self.config.height):
            if (self.map_grid[y][0] != MapElement.WALL.value or
                self.map_grid[y][self.config.width - 1] != MapElement.WALL.value):
                return False
        
        return True
    
    def _check_required_elements(self) -> bool:
        """Check required elements count."""
        player_count = 0
        exit_count = 0
        collectible_count = 0
        
        for row in self.map_grid:
            for cell in row:
                if cell == MapElement.PLAYER.value:
                    player_count += 1
                elif cell == MapElement.EXIT.value:
                    exit_count += 1
                elif cell == MapElement.COLLECTIBLE.value:
                    collectible_count += 1
        
        return (player_count == 1 and exit_count == 1 and collectible_count >= 1)
    
    def _check_path_connectivity(self) -> bool:
        """Check if all collectibles can be collected and exit is reachable after collecting all."""
        if not self.player_pos or not self.exit_pos:
            return False
        
        # First, check if all collectibles are individually reachable from player
        for collectible_pos in self.collectibles:
            if not self._can_reach_position(self.player_pos, collectible_pos):
                return False
        
        # Then, check if exit is reachable after collecting all collectibles
        # This simulates the game flow: collect all items, then reach exit
        return self._can_reach_exit_after_collecting_all()
    
    def _can_reach_position(self, start_pos: Tuple[int, int], target_pos: Tuple[int, int]) -> bool:
        """Check if target position is reachable from start position using BFS."""
        from collections import deque
        
        queue = deque([start_pos])
        visited = {start_pos}
        
        directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]
        
        while queue:
            y, x = queue.popleft()
            
            if (y, x) == target_pos:
                return True
            
            for dy, dx in directions:
                ny, nx = y + dy, x + dx
                
                if (0 <= ny < self.config.height and 0 <= nx < self.config.width and
                    (ny, nx) not in visited and 
                    self._is_walkable(ny, nx)):
                    
                    visited.add((ny, nx))
                    queue.append((ny, nx))
        
        return False
    
    def _can_reach_exit_after_collecting_all(self) -> bool:
        """Check if exit is reachable from any collectible position."""
        # Check if exit is reachable from player position
        if self._can_reach_position(self.player_pos, self.exit_pos):
            return True
        
        # Check if exit is reachable from any collectible position
        # This ensures that after collecting items, player can still reach exit
        for collectible_pos in self.collectibles:
            if self._can_reach_position(collectible_pos, self.exit_pos):
                return True
        
        return False
    
    def _is_walkable(self, y: int, x: int) -> bool:
        """Check if a position is walkable (not a wall)."""
        if (y < 0 or y >= self.config.height or x < 0 or x >= self.config.width):
            return False
        
        cell = self.map_grid[y][x]
        # Player can walk on floors, collectibles, exit, and through enemies
        return cell != MapElement.WALL.value
    
    def _flood_fill(self, test_map: List[List[str]], y: int, x: int):
        """Flood fill algorithm for connectivity check."""
        if (y < 0 or y >= self.config.height or x < 0 or x >= self.config.width or
            test_map[y][x] == MapElement.WALL.value or test_map[y][x] == 'X'):
            return
        
        # Mark as visited
        test_map[y][x] = 'X'
        
        # Recursively fill adjacent cells
        self._flood_fill(test_map, y + 1, x)
        self._flood_fill(test_map, y - 1, x)
        self._flood_fill(test_map, y, x + 1)
        self._flood_fill(test_map, y, x - 1)
    
    def _validate_final_map(self) -> bool:
        """Final validation after enemy placement."""
        try:
            # Check path connectivity (flood fill)
            if not self._check_path_connectivity():
                return False
            
            return True
            
        except Exception:
            return False
    
    def save_map(self) -> bool:
        """Save the generated map to file."""
        try:
            # Ensure maps directory exists
            os.makedirs("maps", exist_ok=True)
            
            filepath = f"maps/{self.config.filename}.ber"
            
            with open(filepath, 'w') as f:
                for row in self.map_grid:
                    f.write(''.join(row) + '\n')
            
            print(f"\n{Color.GREEN}✅ Map saved successfully to: {filepath}{Color.END}")
            return True
            
        except Exception as e:
            print(f"\n{Color.RED}❌ Error saving map: {e}{Color.END}")
            return False
    
    def display_map_preview(self):
        """Display a preview of the generated map."""
        print(f"\n{Color.BOLD}🗺️  MAP PREVIEW:{Color.END}")
        print(f"{Color.BLUE}{'─' * (self.config.width + 2)}{Color.END}")
        
        for row in self.map_grid:
            line = "│"
            for cell in row:
                if cell == MapElement.PLAYER.value:
                    line += f"{Color.GREEN}P{Color.END}"
                elif cell == MapElement.EXIT.value:
                    line += f"{Color.MAGENTA}E{Color.END}"
                elif cell == MapElement.COLLECTIBLE.value:
                    line += f"{Color.YELLOW}C{Color.END}"
                elif cell == MapElement.STATIC_ENEMY.value:
                    line += f"{Color.RED}T{Color.END}"
                elif cell == MapElement.PATROL_ENEMY.value:
                    line += f"{Color.RED}M{Color.END}"
                elif cell == MapElement.WALL.value:
                    line += "█"
                else:
                    line += " "
            line += "│"
            print(f"{Color.BLUE}{line}{Color.END}")
        
        print(f"{Color.BLUE}{'─' * (self.config.width + 2)}{Color.END}")
        
        # Display statistics
        collectible_count = sum(row.count(MapElement.COLLECTIBLE.value) for row in self.map_grid)
        static_enemy_count = sum(row.count(MapElement.STATIC_ENEMY.value) for row in self.map_grid)
        patrol_enemy_count = sum(row.count(MapElement.PATROL_ENEMY.value) for row in self.map_grid)
        
        print(f"\n{Color.BOLD}📊 MAP STATISTICS:{Color.END}")
        print(f"   📏 Dimensions: {self.config.width} x {self.config.height}")
        print(f"   🎯 Collectibles: {collectible_count}")
        print(f"   👤 Static Enemies: {static_enemy_count}")
        print(f"   🚶 Patrol Enemies: {patrol_enemy_count}")
        print(f"   🎮 Complexity: {self.config.complexity.title()}")


def main():
    """Main function to run the map generator."""
    try:
        generator = MapGenerator()
        
        # Get user configuration
        config = generator.get_user_input()
        
        # Generate map
        if generator.generate_map(config):
            # Display preview
            generator.display_map_preview()
            
            # Save map
            if generator.save_map():
                print(f"\n{Color.GREEN}🎉 SUCCESS! Your map is ready to use!{Color.END}")
                print(f"{Color.CYAN}Run: ./so_long maps/{config.filename}.ber{Color.END}")
            else:
                print(f"\n{Color.RED}❌ Failed to save map{Color.END}")
        else:
            print(f"\n{Color.RED}❌ Failed to generate valid map{Color.END}")
            print(f"{Color.YELLOW}💡 Try adjusting your parameters (reduce enemies or complexity){Color.END}")
    
    except KeyboardInterrupt:
        print(f"\n\n{Color.YELLOW}⚠️  Operation cancelled by user{Color.END}")
        sys.exit(0)
    except Exception as e:
        print(f"\n{Color.RED}❌ Unexpected error: {e}{Color.END}")
        sys.exit(1)


if __name__ == "__main__":
    main() 