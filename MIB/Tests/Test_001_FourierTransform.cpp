
#include <stdio.h>

#include "FourierTransform.h"


namespace
{
    constexpr float _max_error = 0.001f;

    bool compare(FourierTransform::DATAS_T& Computed, FourierTransform::DATAS_T& Expected)
    {
        if (Computed.size() != Expected.size())
        {
            fprintf(stderr, "%s:%d:%s: Different buffer sizes\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        for (size_t i = 0u; i < Computed.size(); i++)
        {
            float delta_real        = _max_error * std::abs(Expected[i].Real);
            float delta_imaginary   = _max_error * std::abs(Expected[i].Imaginary);

            if ((Computed[i].Real > Expected[i].Real      + delta_real)      || (Computed[i].Real < Expected[i].Real      - delta_real)
             || (Computed[i].Real > Expected[i].Imaginary + delta_imaginary) || (Computed[i].Real < Expected[i].Imaginary - delta_imaginary))
            {
                fprintf(stderr, "%s:%d:%s: Incorrected value computed\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }
        }

        return true;
    }
}


bool test_forward()
{
    FourierTransform::DATAS_T input     = { { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f },
                                            { 1.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 0.0f },
                                            { 1.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 0.0f },
                                            { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f } };

    FourierTransform::DATAS_T expected  = { { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f },
                                            { 1.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 0.0f },
                                            { 1.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 0.0f },
                                            { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f } };

    FourierTransform::DATAS_T output    = { { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f },
                                            { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f },
                                            { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f },
                                            { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f } };

    if (!FourierTransform::forward(output, input))
    {
        fprintf(stderr, "%s:%d:%s: Failed to compute forward Fourier Transform\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (!compare(output, expected))
    {
        fprintf(stderr, "%s:%d:%s: Incorrect computed forward Fourier Transform\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    return true;
}


int main(int argc, char** argv)
{
    if (!test_forward())
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    return 0;
}
