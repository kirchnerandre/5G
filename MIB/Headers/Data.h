
#pragma once

#include <vector>

namespace Data
{
    struct DATA_T
    {
        float   Real;
        float   Imaginary;
        float   Time;
    };

    typedef std::vector<DATA_T> DATAS_T;
    typedef DATAS_T::iterator   IDATA_T;
}
