#include "public.h"

XCLOG_ENABLE_ASYNCZMQLOGSUBMITSTREAM("tcp://127.0.0.1:5555")

int main(int argc, char **argv) {
    XLOG(0, envman, main) << "START APP";
    return 0;
}