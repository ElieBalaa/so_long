#!/bin/bash

# Colors for visual output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
WHITE='\033[1;37m'
NC='\033[0m' # No Color

# Test counters
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0
MEMORY_LEAKS=0

# Create log directory
mkdir -p memory_test_logs
LOG_DIR="memory_test_logs"

# Print header
print_header() {
    echo -e "${WHITE}=================================================================="
    echo -e "🧪 COMPREHENSIVE MEMORY LEAK TEST SUITE FOR SO_LONG"
    echo -e "=================================================================="
    echo -e "${NC}"
    echo -e "${CYAN}Testing all possible scenarios for memory leaks and reachable memory${NC}"
    echo -e "${YELLOW}Logs will be saved in: ${LOG_DIR}/${NC}"
    echo ""
}

# Print test section
print_section() {
    echo -e "${WHITE}------------------------------------------------------------------${NC}"
    echo -e "${PURPLE}📋 $1${NC}"
    echo -e "${WHITE}------------------------------------------------------------------${NC}"
}

# Run valgrind test
run_valgrind_test() {
    local test_name="$1"
    local command="$2"
    local expected_exit="$3"
    local timeout_duration="$4"
    
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    echo -e "${BLUE}🔍 Test $TOTAL_TESTS: $test_name${NC}"
    echo -e "   Command: $command"
    
    local log_file="${LOG_DIR}/test_${TOTAL_TESTS}_$(echo $test_name | tr ' ' '_' | tr '/' '_').log"
    
    # Run with valgrind
    if [ -n "$timeout_duration" ]; then
        timeout $timeout_duration valgrind --tool=memcheck \
            --leak-check=full \
            --show-leak-kinds=all \
            --track-origins=yes \
            --verbose \
            --log-file="$log_file" \
            $command > /dev/null 2>&1
        local exit_code=$?
    else
        valgrind --tool=memcheck \
            --leak-check=full \
            --show-leak-kinds=all \
            --track-origins=yes \
            --verbose \
            --log-file="$log_file" \
            $command > /dev/null 2>&1
        local exit_code=$?
    fi
    
    # Check for memory leaks in log
    local definitely_lost=$(grep "definitely lost:" "$log_file" | grep -o "[0-9,]* bytes" | head -1 | tr -d ',')
    local indirectly_lost=$(grep "indirectly lost:" "$log_file" | grep -o "[0-9,]* bytes" | head -1 | tr -d ',')
    local possibly_lost=$(grep "possibly lost:" "$log_file" | grep -o "[0-9,]* bytes" | head -1 | tr -d ',')
    local still_reachable=$(grep "still reachable:" "$log_file" | grep -o "[0-9,]* bytes" | head -1 | tr -d ',')
    
    # Extract numeric values
    definitely_lost_bytes=$(echo "$definitely_lost" | grep -o '[0-9]*' | head -1)
    indirectly_lost_bytes=$(echo "$indirectly_lost" | grep -o '[0-9]*' | head -1)
    possibly_lost_bytes=$(echo "$possibly_lost" | grep -o '[0-9]*' | head -1)
    still_reachable_bytes=$(echo "$still_reachable" | grep -o '[0-9]*' | head -1)
    
    # Default to 0 if empty
    definitely_lost_bytes=${definitely_lost_bytes:-0}
    indirectly_lost_bytes=${indirectly_lost_bytes:-0}
    possibly_lost_bytes=${possibly_lost_bytes:-0}
    still_reachable_bytes=${still_reachable_bytes:-0}
    
    local total_leaked=$((definitely_lost_bytes + indirectly_lost_bytes + possibly_lost_bytes))
    
    # Print results
    echo -e "   📊 Memory Analysis:"
    if [ $definitely_lost_bytes -eq 0 ] && [ $indirectly_lost_bytes -eq 0 ] && [ $possibly_lost_bytes -eq 0 ]; then
        echo -e "   ${GREEN}✅ NO MEMORY LEAKS DETECTED${NC}"
        PASSED_TESTS=$((PASSED_TESTS + 1))
    else
        echo -e "   ${RED}❌ MEMORY LEAKS DETECTED${NC}"
        echo -e "   ${RED}   - Definitely lost: $definitely_lost_bytes bytes${NC}"
        echo -e "   ${RED}   - Indirectly lost: $indirectly_lost_bytes bytes${NC}"
        echo -e "   ${RED}   - Possibly lost: $possibly_lost_bytes bytes${NC}"
        FAILED_TESTS=$((FAILED_TESTS + 1))
        MEMORY_LEAKS=$((MEMORY_LEAKS + 1))
    fi
    
    if [ $still_reachable_bytes -gt 0 ]; then
        echo -e "   ${YELLOW}⚠️  Still reachable: $still_reachable_bytes bytes${NC}"
    else
        echo -e "   ${GREEN}✅ No reachable memory${NC}"
    fi
    
    echo -e "   📄 Detailed log: $log_file"
    echo ""
}

# Create test maps
create_test_maps() {
    print_section "CREATING TEST MAPS"
    
    mkdir -p test_maps
    
    # Valid small map
    cat > test_maps/valid_small.ber << 'EOF'
1111111111
1P0C000001
1000011001
1C00E00001
1111111111
EOF
    
    # Empty file
    touch test_maps/empty.ber
    
    # Invalid characters
    cat > test_maps/invalid_chars.ber << 'EOF'
1111111111
1P0C0X0001
1000011001
1C00E00001
1111111111
EOF
    
    # No player
    cat > test_maps/no_player.ber << 'EOF'
1111111111
100C000001
1000011001
1C00E00001
1111111111
EOF
    
    # Multiple players
    cat > test_maps/multiple_players.ber << 'EOF'
1111111111
1P0C0P0001
1000011001
1C00E00001
1111111111
EOF
    
    # No exit
    cat > test_maps/no_exit.ber << 'EOF'
1111111111
1P0C000001
1000011001
1C0000001
1111111111
EOF
    
    # Multiple exits
    cat > test_maps/multiple_exits.ber << 'EOF'
1111111111
1P0C0E0001
1000011001
1C00E00001
1111111111
EOF
    
    # No collectibles
    cat > test_maps/no_collectibles.ber << 'EOF'
1111111111
1P00000001
1000011001
100E000001
1111111111
EOF
    
    # Not rectangular
    cat > test_maps/not_rectangular.ber << 'EOF'
1111111111
1P0C00001
1000011001
1C00E00001
1111111111
EOF
    
    # Open borders
    cat > test_maps/open_borders.ber << 'EOF'
0111111111
1P0C000001
1000011001
1C00E00001
1111111111
EOF
    
    # Unreachable collectible
    cat > test_maps/unreachable.ber << 'EOF'
1111111111
1P00000001
1111111001
1C00E00001
1111111111
EOF
    
    # Unreachable exit
    cat > test_maps/unreachable_exit.ber << 'EOF'
1111111111
1P0C000001
1000011111
100001E001
1111111111
EOF
    
    # Too small
    cat > test_maps/too_small.ber << 'EOF'
111
1P1
111
EOF
    
    # Very large map (for timeout testing)
    echo "Creating large map for timeout testing..."
    {
        for i in $(seq 1 50); do
            if [ $i -eq 1 ] || [ $i -eq 50 ]; then
                printf "1%.0s" $(seq 1 50)
            elif [ $i -eq 2 ]; then
                printf "1P"
                printf "0%.0s" $(seq 1 46)
                printf "C1"
            elif [ $i -eq 49 ]; then
                printf "1C"
                printf "0%.0s" $(seq 1 46)
                printf "E1"
            else
                printf "1"
                printf "0%.0s" $(seq 1 48)
                printf "1"
            fi
            echo ""
        done
    } > test_maps/large_valid.ber
    
    echo -e "${GREEN}✅ Test maps created${NC}"
    echo ""
}

# Test invalid arguments
test_invalid_arguments() {
    print_section "TESTING INVALID ARGUMENTS"
    
    run_valgrind_test "No arguments" "./so_long" 1
    run_valgrind_test "Too many arguments" "./so_long map1.ber map2.ber" 1
    run_valgrind_test "Non-existent file" "./so_long nonexistent.ber" 1
    run_valgrind_test "Directory instead of file" "./so_long ." 1
    run_valgrind_test "Permission denied" "sudo touch /root/test.ber && ./so_long /root/test.ber" 1
}

# Test invalid maps
test_invalid_maps() {
    print_section "TESTING INVALID MAPS"
    
    run_valgrind_test "Empty file" "./so_long test_maps/empty.ber" 1
    run_valgrind_test "Invalid characters" "./so_long test_maps/invalid_chars.ber" 1
    run_valgrind_test "No player" "./so_long test_maps/no_player.ber" 1
    run_valgrind_test "Multiple players" "./so_long test_maps/multiple_players.ber" 1
    run_valgrind_test "No exit" "./so_long test_maps/no_exit.ber" 1
    run_valgrind_test "Multiple exits" "./so_long test_maps/multiple_exits.ber" 1
    run_valgrind_test "No collectibles" "./so_long test_maps/no_collectibles.ber" 1
    run_valgrind_test "Not rectangular" "./so_long test_maps/not_rectangular.ber" 1
    run_valgrind_test "Open borders" "./so_long test_maps/open_borders.ber" 1
    run_valgrind_test "Unreachable collectible" "./so_long test_maps/unreachable.ber" 1
    run_valgrind_test "Unreachable exit" "./so_long test_maps/unreachable_exit.ber" 1
    run_valgrind_test "Too small map" "./so_long test_maps/too_small.ber" 1
}

# Test valid maps with timeout
test_valid_maps() {
    print_section "TESTING VALID MAPS (WITH TIMEOUT)"
    
    run_valgrind_test "Valid small map (3s timeout)" "./so_long test_maps/valid_small.ber" 0 "3s"
    run_valgrind_test "Large valid map (5s timeout)" "./so_long test_maps/large_valid.ber" 0 "5s"
    
    # Test with existing maps if they exist
    if [ -d "maps" ]; then
        for map_file in maps/*.ber; do
            if [ -f "$map_file" ] && [[ "$map_file" != *"invalid"* ]] && [[ "$map_file" != *"empty"* ]] && [[ "$map_file" != *"blocked"* ]] && [[ "$map_file" != *"no_exit"* ]]; then
                map_name=$(basename "$map_file")
                run_valgrind_test "Existing map: $map_name (3s timeout)" "./so_long $map_file" 0 "3s"
            fi
        done
    fi
}

# Test memory with different scenarios
test_memory_edge_cases() {
    print_section "TESTING MEMORY EDGE CASES"
    
    # Test rapid successive calls
    echo -e "${BLUE}🔍 Testing rapid successive calls${NC}"
    for i in {1..5}; do
        run_valgrind_test "Rapid call #$i" "./so_long test_maps/invalid_chars.ber" 1
    done
    
    # Test with different file descriptors
    run_valgrind_test "Stdin redirection" "echo 'invalid' | ./so_long" 1
    
    # Test with very long filename
    long_name="a"
    for i in {1..100}; do
        long_name="${long_name}a"
    done
    run_valgrind_test "Very long filename" "./so_long ${long_name}.ber" 1
}

# Generate summary report
generate_summary() {
    print_section "MEMORY TEST SUMMARY"
    
    echo -e "${WHITE}📊 TEST STATISTICS:${NC}"
    echo -e "   Total tests run: ${TOTAL_TESTS}"
    echo -e "   ${GREEN}✅ Passed (no leaks): ${PASSED_TESTS}${NC}"
    echo -e "   ${RED}❌ Failed (memory leaks): ${FAILED_TESTS}${NC}"
    echo -e "   ${RED}🔴 Total tests with memory leaks: ${MEMORY_LEAKS}${NC}"
    echo ""
    
    if [ $MEMORY_LEAKS -eq 0 ]; then
        echo -e "${GREEN}🎉 EXCELLENT: NO MEMORY LEAKS DETECTED IN ANY TEST!${NC}"
        echo -e "${GREEN}✅ Your so_long project is memory-safe and ready for evaluation!${NC}"
    else
        echo -e "${RED}⚠️  WARNING: Memory leaks detected in $MEMORY_LEAKS test(s)${NC}"
        echo -e "${RED}❌ Please fix memory leaks before evaluation${NC}"
        echo ""
        echo -e "${YELLOW}📝 Check the detailed logs in ${LOG_DIR}/ for more information${NC}"
    fi
    
    echo ""
    echo -e "${CYAN}📄 Detailed logs saved in: ${LOG_DIR}/${NC}"
    echo -e "${CYAN}🔍 To view a specific log: cat ${LOG_DIR}/test_X_description.log${NC}"
    echo ""
    
    # Create summary file
    {
        echo "MEMORY TEST SUMMARY"
        echo "==================="
        echo "Date: $(date)"
        echo "Total tests: $TOTAL_TESTS"
        echo "Passed: $PASSED_TESTS"
        echo "Failed: $FAILED_TESTS"
        echo "Memory leaks: $MEMORY_LEAKS"
        echo ""
        if [ $MEMORY_LEAKS -eq 0 ]; then
            echo "RESULT: PASS - No memory leaks detected"
        else
            echo "RESULT: FAIL - Memory leaks detected"
        fi
    } > "${LOG_DIR}/summary.txt"
    
    echo -e "${GREEN}✅ Summary saved to: ${LOG_DIR}/summary.txt${NC}"
}

# Main execution
main() {
    print_header
    
    # Check if so_long exists
    if [ ! -f "./so_long" ]; then
        echo -e "${RED}❌ Error: ./so_long not found. Please compile the project first.${NC}"
        echo -e "${YELLOW}Run: make${NC}"
        exit 1
    fi
    
    # Check if valgrind is installed
    if ! command -v valgrind &> /dev/null; then
        echo -e "${RED}❌ Error: valgrind not found. Please install valgrind.${NC}"
        echo -e "${YELLOW}Ubuntu/Debian: sudo apt-get install valgrind${NC}"
        echo -e "${YELLOW}macOS: brew install valgrind${NC}"
        exit 1
    fi
    
    create_test_maps
    test_invalid_arguments
    test_invalid_maps
    test_valid_maps
    test_memory_edge_cases
    generate_summary
}

# Run main function
main "$@" 