#ifndef _DEF_H_
#define _DEF_H_


#ifdef TEST
#define STATIC
#else
#define STATIC static
#endif

#ifdef TEST
#define uart_debug(...)  
#endif


#endif /* _DEF_H_ */
