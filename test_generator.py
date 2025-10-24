#!/usr/bin/env python3
"""Quick test of the map generator with different configurations."""

import subprocess
import sys

def test_generator():
    """Test the map generator with automated inputs."""
    
    test_configs = [
        # Small simple map
        ["10", "8", "3", "5", "1", "1", "1", "small_test"],
        # Medium map  
        ["20", "15", "5", "8", "2", "2", "2", "medium_test"],
        # Large complex map
        ["40", "25", "10", "15", "3", "3", "3", "large_test"]
    ]
    
    for i, config in enumerate(test_configs):
        print(f"\n🧪 Testing configuration {i+1}/3...")
        
        try:
            # Prepare input string
            input_data = "\n".join(config) + "\n"
            
            # Run the generator
            result = subprocess.run(
                [sys.executable, "map_generator.py"], 
                input=input_data, 
                text=True, 
                capture_output=True,
                timeout=30
            )
            
            if result.returncode == 0:
                print(f"✅ Configuration {i+1} succeeded!")
                print(f"   Generated: maps/{config[-1]}.ber")
            else:
                print(f"❌ Configuration {i+1} failed!")
                print(f"   Error: {result.stderr}")
                
        except subprocess.TimeoutExpired:
            print(f"⏰ Configuration {i+1} timed out!")
        except Exception as e:
            print(f"💥 Configuration {i+1} crashed: {e}")

if __name__ == "__main__":
    test_generator() 