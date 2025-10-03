#include "kernel/types.h"
#include "user/user.h"

int main()
{
    printf("Testing if we can allocate more than 128MB...\n");
    
    // Try to allocate 150MB total (more than original 128MB limit)
    if (sbrk(150 * 1024 * 1024) == (char*)-1) {
        printf("FAILED: Cannot allocate 150MB - RAM likely not increased\n");
    } else {
        printf("SUCCESS: Allocated 150MB - RAM increase confirmed!\n");
    }
    
    exit(0);
}
