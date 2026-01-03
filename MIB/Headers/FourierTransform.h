
#include <vector>

namespace FourierTransform
{
    struct DATA_T
    {
        float   Real;
        float   Imaginary;
    };

    typedef std::vector<DATA_T> DATAS_T;
    typedef DATAS_T::iterator   IDATA_T;

    bool forward (DATAS_T& Output, DATAS_T& Input);
    bool backward(DATAS_T& Output, DATAS_T& Input);
}
