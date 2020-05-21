#include "../lib/Utils.hpp"

using Utils = TravelingSalesman::Utils;

int *Utils::copyArr(int *src, int size)
{
    int *dest = new int[size];
    for (int i = 0; i < size; i++)
        dest[i] = src[i];
    return dest;
}
