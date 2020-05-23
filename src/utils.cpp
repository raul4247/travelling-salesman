#include "../lib/utils.hpp"

namespace traveling_salesman
{
    int *Utils::copy_arr(int *src, int size)
    {
        int *dest = new int[size];
        for (int i = 0; i < size; i++)
            dest[i] = src[i];
        return dest;
    }
}