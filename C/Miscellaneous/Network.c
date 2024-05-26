// https://github.com/mirror/dd-wrt/blob/2b1f6c6e5b156c6a082dc0eaaac17a00dc77db72/src/router/busybox/networking/nslookup.c#L67
// ./toolchain-mips_34kc_gcc-4.8-linaro_musl-1.1.2/bin/mips-openwrt-linux-gcc getaddr.c -DNEED_PRINTF -o getaddr_tplink
// ./getaddr_tplink `hostname`

#include <stdlib.h>
#include <stdio.h>
#include <resolv.h>
#include <netdb.h>
#include <string.h>

int main(int argc, char *argv[])
{
        struct addrinfo *result = NULL;
        int rc;
        struct addrinfo hint;

         if (argc < 2)
        {
                printf ("Usage: %s hostname\n", argv[0]);
                exit(1);
        }
        printf ("Resolving \"%s\"... ", argv[1]);

        memset(&hint, 0 , sizeof (hint));
        hint.ai_socktype = SOCK_STREAM;
        rc = getaddrinfo (argv[1], NULL, &hint, &result);
        printf ("result: %d\n", rc);
}
