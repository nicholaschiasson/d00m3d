#ifndef DEFINES_H
#define DEFINES_H

#ifndef MyDelete
#define MyDelete(x) if(x!=0){delete x;x=0;}
#endif

#ifndef MyDeleteArray
#define MyDeleteArray(x) if(x!=0){delete[] x;x=0;}
#endif

#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

#endif // DEFINES_H
