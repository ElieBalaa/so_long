#include <stdio.h>
#include <string.h>
#include "libft.h"

// A simple implementation based on the man page description
size_t strlcat_manual(char *dst, const char *src, size_t size)
{
    size_t dst_len = 0;
    while (dst_len < size && dst[dst_len] != '\0')
        dst_len++;
    
    size_t src_len = strlen(src);
    
    if (dst_len == size)
        return size + src_len;
    
    size_t i = 0;
    while (src[i] && dst_len + i < size - 1)
    {
        dst[dst_len + i] = src[i];
        i++;
    }
    dst[dst_len + i] = '\0';
    
    return dst_len + src_len;
}

int main(void)
{
    // Case from Python test: empty buffer size 3, source "hello", size 3
    char buf1[3] = {0};
    const char *src = "hello";
    size_t size = 3;
    
    // Test our implementation
    size_t result1 = ft_strlcat(buf1, src, size);
    
    // Test manual implementation
    char buf2[3] = {0};
    size_t result2 = strlcat_manual(buf2, src, size);
    
    printf("Test with empty buffer size 3, src 'hello', size 3:\n");
    printf("ft_strlcat result: %zu, buf: '%s'\n", result1, buf1);
    printf("manual strlcat result: %zu, buf: '%s'\n", result2, buf2);
    
    // Reset buffers with contents
    char buf3[3] = {'a', 'b', 0}; // Buffer with "ab"
    char buf4[3] = {'a', 'b', 0}; // Buffer with "ab"
    
    // Test both implementations
    size_t result3 = ft_strlcat(buf3, src, size);
    size_t result4 = strlcat_manual(buf4, src, size);
    
    printf("\nTest with buffer 'ab', src 'hello', size 3:\n");
    printf("ft_strlcat result: %zu, buf: '%s'\n", result3, buf3);
    printf("manual strlcat result: %zu, buf: '%s'\n", result4, buf4);
    
    return 0;
} 