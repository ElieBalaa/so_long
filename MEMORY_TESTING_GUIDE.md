# 🧪 Comprehensive Memory Leak Testing Guide for so_long

This guide provides a complete memory testing suite for your so_long project, ensuring **zero memory leaks** for 42 evaluation.

## 📋 Overview

The testing suite includes:
- **Comprehensive test coverage** for all possible scenarios
- **Visual output** with colors and progress indicators
- **Detailed analysis** of memory leaks and reachable memory
- **Interactive analysis tools** for detailed debugging

## 🚀 Quick Start

### 1. Run the Memory Test Suite
```bash
./memory_test.sh
```

### 2. Analyze Results
```bash
./memory_analyzer.sh
```

## 📊 Test Coverage

### ❌ Invalid Arguments Testing
- No arguments provided
- Too many arguments
- Non-existent files
- Directory instead of file
- Permission denied scenarios

### 🗺️ Invalid Maps Testing
- Empty files
- Invalid characters in map
- Missing player (P)
- Multiple players
- Missing exit (E)
- Multiple exits
- Missing collectibles (C)
- Non-rectangular maps
- Open borders (not enclosed by walls)
- Unreachable collectibles
- Unreachable exit
- Maps too small

### ✅ Valid Maps Testing
- Small valid maps with timeout
- Large valid maps with timeout
- All existing valid maps in your `maps/` directory

### 🔬 Memory Edge Cases
- Rapid successive calls
- Different file descriptors
- Very long filenames
- Stress testing scenarios

## 🔧 Tools Included

### 1. `memory_test.sh` - Main Test Suite
Runs comprehensive memory leak testing using valgrind.

**Features:**
- Creates test maps automatically
- Tests all scenarios with valgrind
- Generates detailed logs
- Provides visual progress and results
- Creates summary reports

**Usage:**
```bash
./memory_test.sh
```

### 2. `memory_analyzer.sh` - Results Analyzer
Interactive tool for analyzing memory test results.

**Features:**
- Visual summary with progress bars
- Detailed analysis of individual tests
- Interactive mode for exploration
- Failed tests identification
- Heap usage analysis

**Usage:**
```bash
# Interactive mode (default)
./memory_analyzer.sh

# Quick summary
./memory_analyzer.sh summary

# List failed tests
./memory_analyzer.sh failed

# Analyze specific test
./memory_analyzer.sh analyze test_5_invalid_chars.log

# List all logs
./memory_analyzer.sh list
```

## 📁 Output Structure

```
memory_test_logs/
├── summary.txt                    # Overall test summary
├── test_1_No_arguments.log        # Individual test logs
├── test_2_Too_many_arguments.log
├── test_3_Non-existent_file.log
├── ...
└── test_N_description.log
```

## 🔍 Understanding Results

### ✅ Perfect Result
```
✅ NO MEMORY LEAKS DETECTED
✅ No reachable memory
```

### ⚠️ Warning (Still Acceptable)
```
✅ NO MEMORY LEAKS DETECTED
⚠️  Still reachable: X bytes
```
*Note: "Still reachable" memory is usually from system libraries and is acceptable.*

### ❌ Memory Leak (Must Fix)
```
❌ MEMORY LEAKS DETECTED
   - Definitely lost: X bytes
   - Indirectly lost: Y bytes
   - Possibly lost: Z bytes
```

## 🐛 Debugging Memory Leaks

### 1. Identify the Problem
Use the analyzer to find which test failed:
```bash
./memory_analyzer.sh failed
```

### 2. Analyze Specific Test
```bash
./memory_analyzer.sh analyze test_X_description.log
```

### 3. Review Stack Trace
Look for lines like:
```
at 0x4C2FB0F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
by 0x108A2B: your_function_name (your_file.c:line_number)
```

### 4. Common Memory Leak Sources
- **Malloc without free**: Every `malloc()` must have a corresponding `free()`
- **Image cleanup**: MLX images must be destroyed with `mlx_destroy_image()`
- **Map cleanup**: 2D arrays need proper deallocation
- **Early exits**: Ensure cleanup on all exit paths

## 🛠️ Prerequisites

### Install Valgrind
```bash
# Ubuntu/Debian
sudo apt-get install valgrind

# macOS (requires Homebrew)
brew install valgrind
```

### Compile Your Project
```bash
make
```

## 📋 Checklist for 42 Evaluation

- [ ] Run complete memory test suite
- [ ] Zero "definitely lost" bytes
- [ ] Zero "indirectly lost" bytes
- [ ] Zero "possibly lost" bytes
- [ ] "Still reachable" is acceptable (usually system memory)
- [ ] All test scenarios pass
- [ ] No compilation warnings
- [ ] Game functionality verified

## 🎯 Expected Results for 42 Projects

For a **perfect 42 score**, you should see:
```
🎉 EXCELLENT: NO MEMORY LEAKS DETECTED IN ANY TEST!
✅ Your so_long project is memory-safe and ready for evaluation!
```

## 🔧 Advanced Usage

### Custom Test Maps
Add your own test maps to the `test_maps/` directory and they'll be included in testing.

### Continuous Testing
Run tests periodically during development:
```bash
# Run tests every time you make changes
./memory_test.sh && ./memory_analyzer.sh summary
```

### CI/CD Integration
The scripts can be integrated into continuous integration:
```bash
# Returns 0 if no memory leaks, 1 if leaks detected
./memory_test.sh
exit_code=$?
if [ $exit_code -eq 0 ]; then
    echo "✅ Memory tests passed"
else
    echo "❌ Memory tests failed"
    ./memory_analyzer.sh failed
fi
```

## 🚨 Common Issues and Solutions

### Issue: "valgrind: command not found"
**Solution:** Install valgrind (see Prerequisites section)

### Issue: "so_long not found"
**Solution:** Compile your project first with `make`

### Issue: Tests timing out
**Solution:** This is expected for valid maps. The timeout prevents infinite loops.

### Issue: False positives from system libraries
**Solution:** Focus on "definitely lost" and "indirectly lost" bytes. "Still reachable" from system libraries is usually acceptable.

## 📞 Support

If you encounter issues:
1. Check the detailed logs in `memory_test_logs/`
2. Use the interactive analyzer: `./memory_analyzer.sh`
3. Review this guide's debugging section
4. Ensure all MLX resources are properly cleaned up

---

**Happy coding and good luck with your 42 evaluation! 🎉** 