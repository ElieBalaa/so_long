import os
import subprocess
import glob
import re

def run_command(cmd, timeout=5):
    try:
        result = subprocess.run(cmd, shell=True, capture_output=True, text=True, timeout=timeout)
        return result.returncode, result.stdout, result.stderr
    except subprocess.TimeoutExpired:
        return -1, '', 'Timeout'

def check_compilation():
    print("Checking compilation and executable name...")
    ret, out, err = run_command("make re")
    if ret != 0:
        print("❌ Compilation failed.")
        return False
    if not os.path.isfile("so_long"):
        print("❌ Executable 'so_long' not found.")
        return False
    print("✅ Compilation and executable name OK.")
    return True

def test_map_reading():
    print("Testing map reading with various maps...")
    test_maps = glob.glob("test_maps/*.ber") + glob.glob("maps/*.ber")
    valid = 0
    invalid = 0
    for map_file in test_maps:
        ret, out, err = run_command(f"./so_long {map_file}", timeout=3)
        if ret == 0:
            print(f"  ✅ {map_file}: OK")
            valid += 1
        else:
            print(f"  ⚠️  {map_file}: Error (expected for invalid maps)")
            invalid += 1
    print(f"Tested {valid} valid and {invalid} invalid maps.")

def test_invalid_maps():
    print("Testing error handling for misconfigured maps...")
    # Try a non-existent file
    ret, out, err = run_command("./so_long doesnotexist.ber")
    if ret != 0:
        print("  ✅ Non-existent file: Error as expected.")
    else:
        print("  ❌ Non-existent file: Should have failed.")

    # Try a directory
    ret, out, err = run_command("./so_long .")
    if ret != 0:
        print("  ✅ Directory as file: Error as expected.")
    else:
        print("  ❌ Directory as file: Should have failed.")

def test_counter_output():
    print("Testing for movement counter output...")
    # Use a valid map and simulate a few moves (manual check, or parse stdout)
    ret, out, err = run_command("./so_long test_maps/valid_small.ber", timeout=2)
    # Look for a number in stdout that could be a move counter
    if re.search(r"([Mm]oves?|[Cc]ounter):?\s*\d+", out):
        print("  ✅ Movement counter found in output.")
    else:
        print("  ⚠️  Movement counter not found in output (manual check may be needed).")

def check_mlx_put_image():
    print("Checking for use of mlx_put_image_to_window in code...")
    found = False
    for root, dirs, files in os.walk("src"):
        for file in files:
            if file.endswith(".c"):
                with open(os.path.join(root, file)) as f:
                    if "mlx_put_image_to_window" in f.read():
                        found = True
                        break
    if found:
        print("  ✅ mlx_put_image_to_window found in code.")
    else:
        print("  ❌ mlx_put_image_to_window not found in code.")

def main():
    print("=== so_long Automated Evaluation Script ===")
    if not check_compilation():
        return
    test_map_reading()
    test_invalid_maps()
    test_counter_output()
    check_mlx_put_image()
    print("=== End of Automated Checks ===")
    print("Some checks (window display, keypresses, animations) require manual testing.")

if __name__ == "__main__":
    main()