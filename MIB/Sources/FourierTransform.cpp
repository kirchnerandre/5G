
#include <cmath>
#include <stdio.h>

#include "FourierTransform.h"


namespace
{
    constexpr float _pi = 3.14159265358979323846f;
}


namespace FourierTransform
{
    bool forward (DATAS_T& Output, DATAS_T& Input)
    {
        if (Output.size() != Input.size())
        {
            fprintf(stderr, "%s:%d:%s: Input and output buffers have different sizes\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        for (size_t k = 0u; k < Input.size(); k++)
        {
            for (size_t n = 0u; n < Input.size(); n++)
            {
                Output[k].Real      += Input[n].Real * std::cos(- 2 * _pi * k * n / Input.size()) - Input[n].Imaginary * std::sin(- 2 * _pi * k * n / Input.size());
                Output[k].Imaginary += Input[n].Real * std::sin(- 2 * _pi * k * n / Input.size()) + Input[n].Imaginary * std::cos(- 2 * _pi * k * n / Input.size());
            }
        }

        return true;
    }


    bool backward(DATAS_T& Output, DATAS_T& Input)
    {
        if (Output.size() != Input.size())
        {
            fprintf(stderr, "%s:%d:%s: Input and output buffers have different sizes\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        for (size_t k = 0u; k < Input.size(); k++)
        {
            for (size_t n = 0u; n < Input.size(); n++)
            {
                Output[k].Real      += Input[n].Real * std::cos(2 * _pi * k * n / Input.size()) - Input[n].Imaginary * std::sin(2 * _pi * k * n / Input.size());
                Output[k].Imaginary += Input[n].Real * std::sin(2 * _pi * k * n / Input.size()) + Input[n].Imaginary * std::cos(2 * _pi * k * n / Input.size());
            }

            Output[k].Real      /= Input.size();
            Output[k].Imaginary /= Input.size();
        }

        return true;
    }
}
