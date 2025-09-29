#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

void print_limit(int resource, const char *name)
{
    struct rlimit limit;
    if (getrlimit(resource, &limit) == -1)
    {
        perror("getrlimit");
        exit(1);
    }
    printf("%s: soft = %lld, hard = %lld\n",
           name,
           (long long)limit.rlim_cur,
           (long long)limit.rlim_max);
}

int main()
{
    print_limit(RLIMIT_CPU, "CPU time");
    print_limit(RLIMIT_FSIZE, "File size");
    print_limit(RLIMIT_DATA, "Data segment size");
    print_limit(RLIMIT_STACK, "Stack size");
    print_limit(RLIMIT_CORE, "Core file size");
    print_limit(RLIMIT_RSS, "Resident set size");
    print_limit(RLIMIT_NOFILE, "Number of open files");
    print_limit(RLIMIT_AS, "Address space");
    print_limit(RLIMIT_NPROC, "Number of processes");
    print_limit(RLIMIT_MEMLOCK, "Locked memory");
    print_limit(RLIMIT_MSGQUEUE, "Message queue size");
    print_limit(RLIMIT_NICE, "Nice value");
    print_limit(RLIMIT_RTPRIO, "Real-time priority");
    return 0;
}