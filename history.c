#include "types.h"
#include "stat.h"
#include "user.h"

#define MAX_HISTORY 16
#define MAX_BUFFER 128

int main(int argc, char* argv[])
{
    char buffer[MAX_BUFFER];
    int rv = 0;     // return value from syscall
    for (int i = 0; i < MAX_HISTORY && rv == 0; i++) {
        memset(buffer, 0, 128*sizeof(char));
        rv = history(buffer, i);
        if (rv == 0) {
            printf(1, "%s\n", buffer);
        }
    }

    exit();
}