
#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <stdio.h>

#ifdef DEBUG
   #define ASSERT(x,comment) do { if(!(x)) { printf("%s:%d(%s): ASSERTION FAILED (%s): %s", __FILE__, __LINE__, __FUNCTION__, #x, comment); } } while(0)
#else    //#ifdef _DEBUG
   #define ASSERT(x,comment)
#endif   //#ifdef _DEBUG

#endif   //#ifndef __DEBUG_H__
