
#include <stdio.h>

#include "FourierTransform.h"


namespace
{
    constexpr float _max_error = 0.000100f;

    bool compare(FourierTransform::DATAS_T& Computed, FourierTransform::DATAS_T& Expected)
    {
        if (Computed.size() != Expected.size())
        {
            fprintf(stderr, "%s:%d:%s: Different buffer sizes\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        for (size_t i = 0u; i < Computed.size(); i++)
        {
            if ((Computed[i].Real      > Expected[i].Real      + _max_error) || (Computed[i].Real      < Expected[i].Real      - _max_error)
             || (Computed[i].Imaginary > Expected[i].Imaginary + _max_error) || (Computed[i].Imaginary < Expected[i].Imaginary - _max_error))
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
    FourierTransform::DATAS_T input     = { {   0.000000f,   0.000000f }, {   0.000000f,   0.000000f }, {   0.000000f,   0.000000f }, {   0.000000f,   0.000000f },
                                            {   0.000000f,   0.000000f }, {   0.000000f,   0.000000f }, {   0.000000f,   0.000000f }, {   0.000000f,   0.000000f },
                                            {   1.000000f,   0.000000f }, {   1.000000f,   0.000000f }, {   1.000000f,   0.000000f }, {   1.000000f,   0.000000f },
                                            {   1.000000f,   0.000000f }, {   1.000000f,   0.000000f }, {   1.000000f,   0.000000f }, {   1.000000f,   0.000000f },
                                            {   1.000000f,   0.000000f }, {   1.000000f,   0.000000f }, {   1.000000f,   0.000000f }, {   1.000000f,   0.000000f },
                                            {   1.000000f,   0.000000f }, {   1.000000f,   0.000000f }, {   1.000000f,   0.000000f }, {   1.000000f,   0.000000f },
                                            {   0.000000f,   0.000000f }, {   0.000000f,   0.000000f }, {   0.000000f,   0.000000f }, {   0.000000f,   0.000000f },
                                            {   0.000000f,   0.000000f }, {   0.000000f,   0.000000f }, {   0.000000f,   0.000000f }, {   0.000000f,   0.000000f } };

    FourierTransform::DATAS_T expected  = { {  16.000000f,   0.000000f }, { -10.153170f,  -1.000000f }, {   0.000000f,   0.000000f }, {   3.296557f,   1.000000f },
                                            {   0.000000f,   0.000000f }, {  -1.870869f,  -1.000000f }, {   0.000000f,   0.000000f }, {   1.218505f,   1.000000f },
                                            {   0.000000f,   0.000000f }, {  -0.820679f,  -1.000000f }, {   0.000000f,   0.000000f }, {   0.534513f,   1.000000f },
                                            {   0.000000f,   0.000000f }, {  -0.303348f,  -1.000000f }, {   0.000000f,   0.000000f }, {   0.098489f,   1.000000f },
                                            {   0.000000f,   0.000000f }, {   0.098487f,  -1.000000f }, {   0.000000f,   0.000000f }, {  -0.303355f,   1.000000f },
                                            {   0.000000f,   0.000000f }, {   0.534504f,  -1.000000f }, {   0.000000f,   0.000000f }, {  -0.820671f,   1.000000f },
                                            {   0.000000f,   0.000000f }, {   1.218513f,  -1.000000f }, {   0.000000f,   0.000000f }, {  -1.870865f,   1.000000f },
                                            {   0.000000f,   0.000000f }, {   3.296546f,  -1.000000f }, {   0.000000f,   0.000000f }, { -10.153172f,   1.000000f } };

    FourierTransform::DATAS_T output    = { {   0.000000f,   0.000000f }, {   0.000000f,   0.000000f }, {   0.000000f,   0.000000f }, {   0.000000f,   0.000000f },
                                            {   0.000000f,   0.000000f }, {   0.000000f,   0.000000f }, {   0.000000f,   0.000000f }, {   0.000000f,   0.000000f },
                                            {   0.000000f,   0.000000f }, {   0.000000f,   0.000000f }, {   0.000000f,   0.000000f }, {   0.000000f,   0.000000f },
                                            {   0.000000f,   0.000000f }, {   0.000000f,   0.000000f }, {   0.000000f,   0.000000f }, {   0.000000f,   0.000000f },
                                            {   0.000000f,   0.000000f }, {   0.000000f,   0.000000f }, {   0.000000f,   0.000000f }, {   0.000000f,   0.000000f },
                                            {   0.000000f,   0.000000f }, {   0.000000f,   0.000000f }, {   0.000000f,   0.000000f }, {   0.000000f,   0.000000f },
                                            {   0.000000f,   0.000000f }, {   0.000000f,   0.000000f }, {   0.000000f,   0.000000f }, {   0.000000f,   0.000000f },
                                            {   0.000000f,   0.000000f }, {   0.000000f,   0.000000f }, {   0.000000f,   0.000000f }, {   0.000000f,   0.000000f } };

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
