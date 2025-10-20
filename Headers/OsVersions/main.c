#define SVEN_LINUX
#if defined SVEN_WIN32
   #include "hello_win.h"
#elif defined SVEN_LINUX
   #include "hello_lnx.h"
#else
   #error only windows and linux supported
#endif

int main (void) {
   hello();
   return 0;
}
