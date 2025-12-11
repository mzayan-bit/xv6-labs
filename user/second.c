
#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int main()
{
    
    int free = kmemfree();
    printf("free memore , %d \n",free);
}