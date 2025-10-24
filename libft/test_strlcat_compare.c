#include <stdio.h>
#include <string.h>
#include <bsd/string.h>
#include "libft.h"

int main(void)
{
    // Test case from Python test: create buffer of size 3, src "hello", size 3
    char dest1[3] = {0}; // Empty buffer of size 3 for ft_strlcat
    char dest2[3] = {0}; // Empty buffer of size 3 for system strlcat
    const char *src = "hello";
    size_t size = 3;
    
    // Test our implementation
    size_t result1 = ft_strlcat(dest1, src, size);
    
    // Test system implementation
    size_t result2 = strlcat(dest2, src, size);
    
    printf("Test with empty buffer size 3, src 'hello', size 3:\n");
    printf("ft_strlcat result: %zu, dest: '%s'\n", result1, dest1);
    printf("sys strlcat result: %zu, dest: '%s'\n", result2, dest2);
    
    // Test with non-empty buffer
    char dest3[3] = {'a', 'b', 0}; // Buffer with content "ab"
    char dest4[3] = {'a', 'b', 0}; // Buffer with content "ab"
    
    // Test our implementation
    size_t result3 = ft_strlcat(dest3, src, size);
    
    // Test system implementation
    size_t result4 = strlcat(dest4, src, size);
    
    printf("\nTest with buffer containing 'ab', src 'hello', size 3:\n");
    printf("ft_strlcat result: %zu, dest: '%s'\n", result3, dest3);
    printf("sys strlcat result: %zu, dest: '%s'\n", result4, dest4);
    
    return 0;
} 