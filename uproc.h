// user defined proc structure

struct uproc {
    int pid;    // process id
    int ppid;   // parent process id
    uint sz;    // process memory size (bytes)
    char state[16];  // process state
    char name[16];
};