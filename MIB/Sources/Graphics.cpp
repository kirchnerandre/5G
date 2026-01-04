
#include <cmath>
#include <stdio.h>
#include <stdint.h>

#include "Graphics.h"


namespace
{
    constexpr uint32_t  _x_length   = 2000u;
    constexpr uint32_t  _y_length   = 900u;
    constexpr uint32_t  _y_border   = 50u;
    constexpr uint8_t   _magic[]    = { 'P', '5' };


    float get_modulus(Data::DATA_T& Data)
    {
        return std::sqrtf(std::powf(Data.Real, 2.0f) + std::powf(Data.Imaginary, 2.0f));
    }


    void plot_line(uint8_t* Buffer, uint32_t XPrevious, uint32_t YPrevious, uint32_t XCurrent, uint32_t YCurrent)
    {
        int32_t x_min = static_cast<int32_t>(XPrevious < XCurrent ? XPrevious : XCurrent);
        int32_t x_max = static_cast<int32_t>(XPrevious > XCurrent ? XPrevious : XCurrent);
        int32_t y_min = static_cast<int32_t>(YPrevious < YCurrent ? YPrevious : YCurrent);
        int32_t y_max = static_cast<int32_t>(YPrevious > YCurrent ? YPrevious : YCurrent);

        if (x_min == x_max)
        {
            for (int32_t y = y_min; y <= y_max; y++)
            {
                Buffer[y * _x_length + x_min] = 0xff;
            }
        }
        else if (y_max - y_min >= x_max - x_min)
        {
            float m = static_cast<float>(y_max - y_min) / static_cast<float>(x_max - x_min);

            for (int32_t y = y_min; y <= y_max; y++)
            {
                int32_t x = x_min + static_cast<int32_t>((y - y_min) / m + 0.5f);

                Buffer[y * _x_length + x] = 0xff;
            }
        }
        else
        {
            float m = static_cast<float>(y_max - y_min) / static_cast<float>(x_max - x_min);

            for (int32_t x = x_min; x <= x_max; x++)
            {
                int32_t y = y_min + static_cast<int32_t>((x - x_min) * m + 0.5f);

                Buffer[y * _x_length + x] = 0xff;
            }
        }
    }


    void plot_modules(uint8_t* Buffer, Data::DATAS_T& Datas)
    {
        float x_min = Datas[0u].Time;
        float x_max = Datas[0u].Time;

        for (size_t i = 1u; i < Datas.size(); i++)
        {
            x_min = x_min < Datas[i].Time ? x_min : Datas[i].Time;
            x_max = x_max > Datas[i].Time ? x_max : Datas[i].Time;
        }

        float y_min = get_modulus(Datas[0u]);
        float y_max = get_modulus(Datas[0u]);

        for (size_t i = 1u; i < Datas.size(); i++)
        {
            y_min = y_min < get_modulus(Datas[i]) ? y_min : get_modulus(Datas[i]);
            y_max = y_max > get_modulus(Datas[i]) ? y_max : get_modulus(Datas[i]);
        }

        float x_scale = static_cast<float>(_x_length) / (x_max - x_min);
        float y_scale = static_cast<float>(_y_length) / (y_max - y_min);

        uint32_t x_previous = static_cast<uint32_t>(x_scale * (Datas[0u].Time         - x_min));
        uint32_t y_previous = static_cast<uint32_t>(y_scale * (get_modulus(Datas[0u]) - y_min));

        for (size_t i = 1u; i < Datas.size(); i++)
        {
            uint32_t x_current = static_cast<uint32_t>(x_scale * (Datas[i].Time         - x_min));
            uint32_t y_current = static_cast<uint32_t>(y_scale * (get_modulus(Datas[i]) - y_min));

            plot_line(Buffer, x_previous, y_previous, x_current, y_current);

            x_previous = x_current;
            y_previous = y_current;
        }
    }


    void plot_reals(uint8_t* Buffer, Data::DATAS_T& Datas)
    {
        float x_min = Datas[0u].Time;
        float x_max = Datas[0u].Time;

        for (size_t i = 1u; i < Datas.size(); i++)
        {
            x_min = x_min < Datas[i].Time ? x_min : Datas[i].Time;
            x_max = x_max > Datas[i].Time ? x_max : Datas[i].Time;
        }

        float y_min = Datas[0u].Real;
        float y_max = Datas[0u].Real;

        for (size_t i = 1u; i < Datas.size(); i++)
        {
            y_min = y_min < Datas[i].Real ? y_min : Datas[i].Real;
            y_max = y_max > Datas[i].Real ? y_max : Datas[i].Real;
        }

        float x_scale = static_cast<float>(_x_length) / (x_max - x_min);
        float y_scale = static_cast<float>(_y_length) / (y_max - y_min);

        uint32_t x_previous = static_cast<uint32_t>(x_scale * (Datas[0u].Time - x_min));
        uint32_t y_previous = static_cast<uint32_t>(y_scale * (Datas[0u].Real - y_min));

        for (size_t i = 1u; i < Datas.size(); i++)
        {
            uint32_t x_current = static_cast<uint32_t>(x_scale * (Datas[i].Time - x_min));
            uint32_t y_current = static_cast<uint32_t>(y_scale * (Datas[i].Real - y_min));

            plot_line(Buffer, x_previous, y_previous, x_current, y_current);

            x_previous = x_current;
            y_previous = y_current;
        }
    }


    void plot_imaginaries(uint8_t* Buffer, Data::DATAS_T& Datas)
    {
        float x_min = Datas[0u].Time;
        float x_max = Datas[0u].Time;

        for (size_t i = 1u; i < Datas.size(); i++)
        {
            x_min = x_min < Datas[i].Time ? x_min : Datas[i].Time;
            x_max = x_max > Datas[i].Time ? x_max : Datas[i].Time;
        }

        float y_min = Datas[0u].Imaginary;
        float y_max = Datas[0u].Imaginary;

        for (size_t i = 1u; i < Datas.size(); i++)
        {
            y_min = y_min < Datas[i].Real ? y_min : Datas[i].Real;
            y_max = y_max > Datas[i].Real ? y_max : Datas[i].Real;
        }

        float x_scale = static_cast<float>(_x_length) / (x_max - x_min);
        float y_scale = static_cast<float>(_y_length) / (y_max - y_min);

        uint32_t x_previous = static_cast<uint32_t>(x_scale * (Datas[0u].Time      - x_min));
        uint32_t y_previous = static_cast<uint32_t>(y_scale * (Datas[0u].Imaginary - y_min));

        for (size_t i = 1u; i < Datas.size(); i++)
        {
            uint32_t x_current = static_cast<uint32_t>(x_scale * (Datas[i].Time - x_min));
            uint32_t y_current = static_cast<uint32_t>(y_scale * (Datas[i].Real - y_min));

            plot_line(Buffer, x_previous, y_previous, x_current, y_current);

            x_previous = x_current;
            y_previous = y_current;
        }
    }


    uint32_t make_big_endian(uint32_t Value)
    {
        uint32_t a      = 1u;
        uint8_t* p      = reinterpret_cast<uint8_t*>(&a);
        uint32_t value  = 0u;

        if (*p) // little endian
        {
            value = ((Value & 0x000000ff) << 24u)
                  + ((Value & 0x0000ff00) <<  8u)
                  + ((Value & 0x00ff0000) >>  8u)
                  + ((Value & 0xff000000) >> 24u);
        }
        else // big endian
        {
            value = Value;
        }

        return value;
    }


    bool print(uint8_t* Buffer, std::string& Filename)
    {
        FILE* file = nullptr;

        if (fopen_s(&file, Filename.c_str(), "w"))
        {
            fprintf(stderr, "%s:%d:%s: Failed to create file\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        fprintf(file, "P5\n");
        fprintf(file, "%d %d\n", _x_length, _y_length);
        fprintf(file, "%d\n", 255);

        for (size_t i = 0u; i < (_y_border + _y_length + _y_border) * _x_length * 3u; i++)
        {
            fprintf(file, "%c", Buffer[i]);
        }

        fclose(file);

        return true;
    }
}


namespace Graphics
{
    bool plot(Data::DATAS_T& Datas, std::string& Filename)
    {
        bool        retval  = true;
        uint8_t*    buffer  = new uint8_t[(_y_border + _y_length + _y_border) * _x_length * 3u]{};

        if (Datas.size() == 0u)
        {
            fprintf(stderr, "%s:%d:%s: No Data\n", __FILE__, __LINE__, __FUNCTION__);
            retval = false;
            goto terminate;
        }

        if (buffer == nullptr)
        {
            fprintf(stderr, "%s:%d:%s: Failed to allocate buffer\n", __FILE__, __LINE__, __FUNCTION__);
            retval = false;
            goto terminate;
        }

        plot_modules    (&buffer[(_y_border + _y_length + _y_border) * _x_length * 0u], Datas);
        plot_reals      (&buffer[(_y_border + _y_length + _y_border) * _x_length * 1u], Datas);
        plot_imaginaries(&buffer[(_y_border + _y_length + _y_border) * _x_length * 2u], Datas);

        if (!print(buffer, Filename))
        {
            fprintf(stderr, "%s:%d:%s: Failed to create file\n", __FILE__, __LINE__, __FUNCTION__);
            retval = false;
            goto terminate;
        }

    terminate:
        if (buffer)
        {
            delete[] buffer;
        }

        return true;
    }
}
