
#pragma once

#include "Data.h"

namespace FourierTransform
{
    bool forward (Data::DATAS_T& Output, Data::DATAS_T& Input);
    bool backward(Data::DATAS_T& Output, Data::DATAS_T& Input);
}
