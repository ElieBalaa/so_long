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

LOG_DIR="memory_test_logs"

# Print header
print_header() {
    echo -e "${WHITE}=================================================================="
    echo -e "🔍 MEMORY TEST RESULTS ANALYZER"
    echo -e "=================================================================="
    echo -e "${NC}"
}

# Analyze individual log file
analyze_log() {
    local log_file="$1"
    local test_name=$(basename "$log_file" .log | sed 's/test_[0-9]*_//')
    
    echo -e "${BLUE}📋 Analyzing: $test_name${NC}"
    echo -e "${WHITE}------------------------------------------------------------------${NC}"
    
    if [ ! -f "$log_file" ]; then
        echo -e "${RED}❌ Log file not found: $log_file${NC}"
        return 1
    fi
    
    # Extract memory summary
    local heap_summary=$(grep -A 10 "HEAP SUMMARY:" "$log_file")
    local leak_summary=$(grep -A 20 "LEAK SUMMARY:" "$log_file")
    
    # Extract specific values
    local definitely_lost=$(grep "definitely lost:" "$log_file" | grep -o "[0-9,]* bytes")
    local indirectly_lost=$(grep "indirectly lost:" "$log_file" | grep -o "[0-9,]* bytes")
    local possibly_lost=$(grep "possibly lost:" "$log_file" | grep -o "[0-9,]* bytes")
    local still_reachable=$(grep "still reachable:" "$log_file" | grep -o "[0-9,]* bytes")
    
    # Show heap usage
    if [ -n "$heap_summary" ]; then
        echo -e "${CYAN}💾 Heap Usage:${NC}"
        echo "$heap_summary" | while read line; do
            if [[ "$line" =~ "in use at exit:" ]]; then
                echo -e "   ${YELLOW}$line${NC}"
            elif [[ "$line" =~ "total heap usage:" ]]; then
                echo -e "   ${BLUE}$line${NC}"
            fi
        done
        echo ""
    fi
    
    # Show leak summary
    echo -e "${CYAN}🔍 Memory Leak Analysis:${NC}"
    if [ -n "$definitely_lost" ]; then
        echo -e "   ${RED}📉 Definitely lost: $definitely_lost${NC}"
    else
        echo -e "   ${GREEN}✅ Definitely lost: 0 bytes${NC}"
    fi
    
    if [ -n "$indirectly_lost" ]; then
        echo -e "   ${RED}📉 Indirectly lost: $indirectly_lost${NC}"
    else
        echo -e "   ${GREEN}✅ Indirectly lost: 0 bytes${NC}"
    fi
    
    if [ -n "$possibly_lost" ]; then
        echo -e "   ${YELLOW}⚠️  Possibly lost: $possibly_lost${NC}"
    else
        echo -e "   ${GREEN}✅ Possibly lost: 0 bytes${NC}"
    fi
    
    if [ -n "$still_reachable" ]; then
        echo -e "   ${YELLOW}📌 Still reachable: $still_reachable${NC}"
    else
        echo -e "   ${GREEN}✅ Still reachable: 0 bytes${NC}"
    fi
    
    # Show error summary
    local error_summary=$(grep "ERROR SUMMARY:" "$log_file")
    if [ -n "$error_summary" ]; then
        echo -e "${CYAN}⚠️  Error Summary:${NC}"
        echo -e "   $error_summary"
    fi
    
    # Show specific leak details if any
    local leak_details=$(grep -A 30 "definitely lost" "$log_file" | grep -E "(at 0x|by 0x)")
    if [ -n "$leak_details" ]; then
        echo -e "${RED}🚨 Leak Location Details:${NC}"
        echo "$leak_details" | head -10 | while read line; do
            echo -e "   ${RED}$line${NC}"
        done
        echo -e "   ${YELLOW}... (see full log for complete stack trace)${NC}"
    fi
    
    echo ""
}

# Generate visual summary
generate_visual_summary() {
    echo -e "${WHITE}=================================================================="
    echo -e "📊 VISUAL MEMORY TEST SUMMARY"
    echo -e "=================================================================="
    echo -e "${NC}"
    
    if [ ! -f "${LOG_DIR}/summary.txt" ]; then
        echo -e "${RED}❌ Summary file not found. Run memory test first.${NC}"
        return 1
    fi
    
    # Read summary data
    local total_tests=$(grep "Total tests:" "${LOG_DIR}/summary.txt" | grep -o '[0-9]*')
    local passed=$(grep "Passed:" "${LOG_DIR}/summary.txt" | grep -o '[0-9]*')
    local failed=$(grep "Failed:" "${LOG_DIR}/summary.txt" | grep -o '[0-9]*')
    local memory_leaks=$(grep "Memory leaks:" "${LOG_DIR}/summary.txt" | grep -o '[0-9]*')
    
    # Create visual bar
    local bar_length=50
    local passed_length=$((passed * bar_length / total_tests))
    local failed_length=$((failed * bar_length / total_tests))
    
    echo -e "${WHITE}Test Results Overview:${NC}"
    echo -e "Total Tests: $total_tests"
    echo ""
    
    # Visual progress bar
    printf "Progress: ["
    printf "${GREEN}%*s${NC}" $passed_length | tr ' ' '='
    printf "${RED}%*s${NC}" $failed_length | tr ' ' '='
    printf "%*s" $((bar_length - passed_length - failed_length)) | tr ' ' '-'
    printf "]\n"
    echo ""
    
    echo -e "${GREEN}✅ Passed: $passed tests ($(( passed * 100 / total_tests ))%)${NC}"
    echo -e "${RED}❌ Failed: $failed tests ($(( failed * 100 / total_tests ))%)${NC}"
    echo -e "${RED}🔴 Memory Leaks: $memory_leaks tests${NC}"
    echo ""
    
    # Overall status
    if [ "$memory_leaks" -eq 0 ]; then
        echo -e "${GREEN}🎉 OVERALL STATUS: EXCELLENT - NO MEMORY LEAKS!${NC}"
        echo -e "${GREEN}✅ Your project is memory-safe and ready for evaluation!${NC}"
    else
        echo -e "${RED}⚠️  OVERALL STATUS: NEEDS ATTENTION - MEMORY LEAKS DETECTED${NC}"
        echo -e "${RED}❌ Please fix memory leaks before evaluation${NC}"
    fi
    echo ""
}

# List all failed tests
list_failed_tests() {
    echo -e "${WHITE}=================================================================="
    echo -e "❌ FAILED TESTS DETAILS"
    echo -e "=================================================================="
    echo -e "${NC}"
    
    local failed_count=0
    
    for log_file in ${LOG_DIR}/test_*.log; do
        if [ -f "$log_file" ]; then
            # Check if this test had memory leaks
            local definitely_lost=$(grep "definitely lost:" "$log_file" | grep -o "[0-9,]* bytes" | head -1 | tr -d ',')
            local indirectly_lost=$(grep "indirectly lost:" "$log_file" | grep -o "[0-9,]* bytes" | head -1 | tr -d ',')
            local possibly_lost=$(grep "possibly lost:" "$log_file" | grep -o "[0-9,]* bytes" | head -1 | tr -d ',')
            
            local definitely_lost_bytes=$(echo "$definitely_lost" | grep -o '[0-9]*' | head -1)
            local indirectly_lost_bytes=$(echo "$indirectly_lost" | grep -o '[0-9]*' | head -1)
            local possibly_lost_bytes=$(echo "$possibly_lost" | grep -o '[0-9]*' | head -1)
            
            definitely_lost_bytes=${definitely_lost_bytes:-0}
            indirectly_lost_bytes=${indirectly_lost_bytes:-0}
            possibly_lost_bytes=${possibly_lost_bytes:-0}
            
            if [ "$definitely_lost_bytes" -gt 0 ] || [ "$indirectly_lost_bytes" -gt 0 ] || [ "$possibly_lost_bytes" -gt 0 ]; then
                failed_count=$((failed_count + 1))
                local test_name=$(basename "$log_file" .log | sed 's/test_[0-9]*_//')
                echo -e "${RED}❌ Test: $test_name${NC}"
                echo -e "   Log: $log_file"
                echo -e "   Leaks: definitely=$definitely_lost_bytes, indirectly=$indirectly_lost_bytes, possibly=$possibly_lost_bytes bytes"
                echo ""
            fi
        fi
    done
    
    if [ "$failed_count" -eq 0 ]; then
        echo -e "${GREEN}🎉 No failed tests! All tests passed memory checks.${NC}"
    else
        echo -e "${RED}Total failed tests: $failed_count${NC}"
        echo -e "${YELLOW}💡 Use 'analyze' command to see detailed analysis of each test${NC}"
    fi
    echo ""
}

# Interactive mode
interactive_mode() {
    while true; do
        echo -e "${WHITE}=================================================================="
        echo -e "🔍 INTERACTIVE MEMORY ANALYSIS"
        echo -e "=================================================================="
        echo -e "${NC}"
        echo "Available commands:"
        echo "1. summary    - Show visual summary"
        echo "2. failed     - List all failed tests"
        echo "3. analyze    - Analyze specific test"
        echo "4. list       - List all test logs"
        echo "5. quit       - Exit"
        echo ""
        
        read -p "Enter command: " command
        
        case $command in
            1|summary)
                generate_visual_summary
                ;;
            2|failed)
                list_failed_tests
                ;;
            3|analyze)
                echo "Available test logs:"
                ls -1 ${LOG_DIR}/test_*.log 2>/dev/null | nl
                echo ""
                read -p "Enter test number or log file name: " test_input
                
                if [[ "$test_input" =~ ^[0-9]+$ ]]; then
                    # User entered a number
                    log_file=$(ls -1 ${LOG_DIR}/test_*.log 2>/dev/null | sed -n "${test_input}p")
                    if [ -n "$log_file" ]; then
                        analyze_log "$log_file"
                    else
                        echo -e "${RED}❌ Invalid test number${NC}"
                    fi
                else
                    # User entered a filename
                    if [ -f "${LOG_DIR}/$test_input" ]; then
                        analyze_log "${LOG_DIR}/$test_input"
                    elif [ -f "$test_input" ]; then
                        analyze_log "$test_input"
                    else
                        echo -e "${RED}❌ Log file not found: $test_input${NC}"
                    fi
                fi
                ;;
            4|list)
                echo -e "${CYAN}📂 Available test logs:${NC}"
                ls -la ${LOG_DIR}/test_*.log 2>/dev/null | nl
                echo ""
                ;;
            5|quit|exit)
                echo -e "${GREEN}👋 Goodbye!${NC}"
                break
                ;;
            *)
                echo -e "${RED}❌ Unknown command: $command${NC}"
                ;;
        esac
        
        echo ""
        read -p "Press Enter to continue..."
        clear
    done
}

# Main function
main() {
    print_header
    
    if [ ! -d "$LOG_DIR" ]; then
        echo -e "${RED}❌ Memory test logs directory not found: $LOG_DIR${NC}"
        echo -e "${YELLOW}Please run ./memory_test.sh first${NC}"
        exit 1
    fi
    
    case "${1:-interactive}" in
        summary)
            generate_visual_summary
            ;;
        failed)
            list_failed_tests
            ;;
        analyze)
            if [ -n "$2" ]; then
                analyze_log "$2"
            else
                echo -e "${RED}❌ Please specify a log file to analyze${NC}"
                echo -e "${YELLOW}Usage: $0 analyze <log_file>${NC}"
            fi
            ;;
        list)
            echo -e "${CYAN}📂 Available test logs:${NC}"
            ls -la ${LOG_DIR}/ 2>/dev/null
            ;;
        interactive|*)
            interactive_mode
            ;;
    esac
}

# Run main function
main "$@" 