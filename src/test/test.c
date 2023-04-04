#include "test_core.h"
#include "test_utils.h"

int main()
{
    test_info *info = create_test_info();
    int before = clock();

    int end = clock();
    info->time = clock_ticks_to_seconds(end - before);
    print_test_info(info);
    destroy_test_info(info);
}