#include "std_casted.h"

uint8_t *strstr_u8(uint8_t *haystack, uint8_t *needle)
{
        char* ptr;
        ptr = strstr( (char*) haystack,  (char*)needle); 
        return (uint8_t * )ptr;
}

size_t strlen_u8( uint8_t *s)
{
       return strlen((char *)s);
}

uint8_t atoi_u8( uint8_t* nptr)
{
    int n ;
    n = atoi((char *)nptr);
    return (uint8_t) n;
}

uint32_t atoi_u32( uint8_t* str)
{
    uint32_t number = 0;
    uint8_t i = 0; 

    while (str[i] == ' ') 
    {
        i++;
    }

    while (str[i] >= '0' && str[i] <= '9') 
    {
        number = 10 * number +  (uint32_t)(str[i++] - '0'); 
    }  

    return number;
}

/* reverse:  reverse string s in place */
static void reverse(uint8_t s[])
{
    int i, j;
    uint8_t c;

    for (i = 0, j = strlen(s)-1; i<j; i++, j--) 
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}


/* itoa:  convert n to characters in s */
void itoa_u32(uint32_t n, uint8_t s[])
{
    uint32_t i;

    i = 0;
    do {       /* generate digits in reverse order */
        s[i++] = n % 10 + '0';   /* get next digit */
    } while ((n /= 10) > 0);     /* delete it */

    s[i] = '\0';
    reverse(s);
}
