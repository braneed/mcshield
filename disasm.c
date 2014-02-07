#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#define MAX_BYTES 15 // Define max bytes for each line

// Print message
static void croak(const char *msg) {
    fprintf(stderr, "%s\n", msg);
    fflush(stderr);
}
static void usage(const char *prgnam) {
    fprintf(stderr, "\nExecute code : %s -e \n", prgnam);
    fprintf(stderr, "Convert code : %s -p \n", prgnam);
    fflush(stderr);
    exit(1);
}
/*
 * Signal error and bail out.
 */
static void
barf(const char *msg) {
    perror(msg);
    exit(1);
}

/*
 * Main code starts here
 */

int
main(int argc, char **argv) {
    FILE        *fp;
    void        *code;
    int         arg;
    int         i;
    int         l;
//    int     m = 15; // Max bytes on one line

    struct stat sbuf;
    long        flen;   /* Note: assume files are < 2**32 bytes long ;-) */
    void        (*fptr)(void);

    if(argc < 3) usage(argv[0]);
    if(stat(argv[2], &sbuf)) barf("failed to stat file");
    flen = (long) sbuf.st_size;
    if(!(code = malloc(flen))) barf("failed to grab required memeory");
    if(!(fp = fopen(argv[2], "rb"))) barf("failed to open file");
    if(fread(code, 1, flen, fp) != flen) barf("failed to slurp file");
    if(fclose(fp)) barf("failed to close file");

    while ((arg = getopt (argc, argv, "e:p:")) != -1){
      switch (arg){
      case 'e':
        croak("Calling code ...");
        fptr = (void (*)(void)) code;
        (*fptr)();
        break;
      case 'p':
        printf("\n\nchar shellcode[] =\n");
        l = MAX_BYTES;
        for(i = 0; i < flen; ++i) {
          if(l >= MAX_BYTES) {
            if(i) printf("\n");
            printf("\t");
            l = 0;
          }
          ++l;
          printf("\\x%02x", ((unsigned char *)code)[i]);
        }
        printf("\";\n\n\n");

        break;
      default :
        usage(argv[0]);
      }
    }


    return 0;
}
