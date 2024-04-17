#ifndef LIB_BAGS
#define LIB_BAGS

#include <limits.h>     // for UCHAR_MAX and CHAR_BIT
#include <stddef.h>     // for size_t

#ifndef BAG_MAX         // use -DBAG_MAX=49 for other SET_MAX values (Ex.: 49)
#define BAG_MAX         UCHAR_MAX               // UCHAR_MAX = 255
#endif /* BAG_MAX */

#define BAG_DIM         BAG_MAX + 1
typedef unsigned char   Bag[BAG_DIM];
typedef unsigned char * BagPtr;
typedef size_t          Bagelem;

int     Bagisin(Bagelem x, const Bag b);
BagPtr  Bagunion(Bag b0, const Bag b1);
BagPtr  Baginter(Bag b0, const Bag b1);
BagPtr  Bagdiff(Bag b0, const Bag b1);
int     Bagissub(const Bag b0, const Bag b1);
size_t  Bagcard(const Bag b);
size_t  Bagcardu(const Bag b);
BagPtr  Bagclr(Bag b);
int     Bagisempty(const Bag b);
int     Bagisequal(const Bag b0, const Bag b1);
BagPtr  Bagcpy(Bag b0, const Bag b1);
BagPtr  Bagadd(Bag b, Bagelem x);
BagPtr  Bagrm(Bag b, Bagelem x);


#endif /* LIB_BAGS */
