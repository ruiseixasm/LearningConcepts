// Compile command: gcc music.c lib/utils.c lib/data_base.c lib/data_base_io.c lib/dialogs.c -o music.out
#include "lib/utils.h"          // My own library
#include "lib/data_base.h"
#include "lib/data_base_io.h"
#include "lib/dialogs.h"


int main(int argc, char *argv[])
{
    printf("Total arguments: %d\n", argc);
    printf("Arguments: ");
    for (int i = 0; i < argc; i++)
        printf("%s", argv[i]);
    printf("\n");
    
    return 0;
}
