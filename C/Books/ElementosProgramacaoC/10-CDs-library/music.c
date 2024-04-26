// Compile command: gcc music.c lib/utils.c lib/data_base.c lib/data_base_io.c lib/dialogs.c -o music.out
#include "lib/utils.h"          // My own library
#include "lib/data_base.h"
#include "lib/data_base_io.h"
#include "lib/dialogs.h"
#include "lib/int_util.h"

#define UNABLE_TO_WRITE "Unable to write file. "
#define UNABLE_TO_READ  "Unable to read file. "

Menu mainMenu;
Menu fileMenu;
Menu diskMenu;
Menu styleMenu;
Menu searchMenu;
Menu selectMenu;

int dbOpen;
char dbName[64];
int searchApprox = 0;

typedef void (*fRestrict)(const char *);
fRestrict RestrictByArtist[2]   = {RestrictByArtistFull, RestrictByArtistApprox};
fRestrict RestrictByTitle[2]    = {RestrictByTitleFull, RestrictByTitleApprox};
fRestrict RestrictBySong[2]     = {RestrictBySongFull, RestrictBySongApprox};

int main(int argc, char *argv[])
{
    printf("Total arguments: %d\n", argc);
    printf("Arguments:");
    for (int i = 0; i < argc; i++)
        printf(" %s", argv[i]);
    printf("\n");


    int i;
    CreateMenu(&styleMenu, "Style: ", "");
    
    return 0;
}
