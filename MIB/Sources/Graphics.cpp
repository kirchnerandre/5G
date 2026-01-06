
#include <cmath>
#include <stdio.h>
#include <stdint.h>

#include "Graphics.h"


namespace
{
    constexpr uint32_t  _x_length   = 1900u;
    constexpr uint32_t  _x_border   = 50u;
    constexpr uint32_t  _y_length   = 900u;
    constexpr uint32_t  _y_border   = 50u;
    constexpr float     _phy        = 1.0f;


    float get_modulus(Data::DATA_T& Data)
    {
        return std::sqrtf(std::powf(Data.Real, 2.0f) + std::powf(Data.Imaginary, 2.0f));
    }


    void plot_line(uint8_t* Buffer, uint32_t XPrevious, uint32_t YPrevious, uint32_t XCurrent, uint32_t YCurrent)
    {
        YPrevious   = _y_length - YPrevious;
        YCurrent    = _y_length - YCurrent;

        float m = (static_cast<float>(YCurrent) - static_cast<float>(YPrevious))
                / (static_cast<float>(XCurrent) - static_cast<float>(XPrevious) + _phy);

        if (std::abs(static_cast<int32_t>(YCurrent) - static_cast<int32_t>(YPrevious)) >= std::abs(static_cast<int32_t>(XCurrent) - static_cast<int32_t>(XPrevious)))
        {
            if (YCurrent >= YPrevious)
            {
                for (uint32_t y = YPrevious; y <= YCurrent; y++)
                {
                    uint32_t x = XPrevious + static_cast<uint32_t>((static_cast<float>(y) - static_cast<float>(YPrevious)) / m + 0.5f);

                    Buffer[y * (_x_border + _x_length + _x_border) + x + _x_border] = 0xff;
                }
            }
            else
            {
                for (uint32_t y = YCurrent; y <= YPrevious; y++)
                {
                    uint32_t x = XPrevious + static_cast<uint32_t>((static_cast<float>(y) - static_cast<float>(YPrevious)) / m + 0.5f);

                    Buffer[y * (_x_border + _x_length + _x_border) + x + _x_border] = 0xff;
                }
            }
        }
        else
        {
            for (uint32_t x = XPrevious; x <= XCurrent; x++)
            {
                uint32_t y = YPrevious + static_cast<uint32_t>((x - XPrevious) * m + 0.5f);

                Buffer[y * (_x_border + _x_length + _x_border) + x + _x_border] = 0xff;
            }
        }
    }


    void plot_modules(uint8_t* Buffer, Data::DATAS_T& Datas)
    {
        float x_min = Datas[0u].TimeFrequency;
        float x_max = Datas[0u].TimeFrequency;

        for (size_t i = 1u; i < Datas.size(); i++)
        {
            x_min = x_min < Datas[i].TimeFrequency ? x_min : Datas[i].TimeFrequency;
            x_max = x_max > Datas[i].TimeFrequency ? x_max : Datas[i].TimeFrequency;
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

        uint32_t x_previous = static_cast<uint32_t>(x_scale * (Datas[0u].TimeFrequency - x_min));
        uint32_t y_previous = static_cast<uint32_t>(y_scale * (get_modulus(Datas[0u])  - y_min));

        for (size_t i = 1u; i < Datas.size(); i++)
        {
            uint32_t x_current = static_cast<uint32_t>(x_scale * (Datas[i].TimeFrequency - x_min));
            uint32_t y_current = static_cast<uint32_t>(y_scale * (get_modulus(Datas[i])  - y_min));

            plot_line(Buffer, x_previous, y_previous, x_current, y_current);

            x_previous = x_current;
            y_previous = y_current;
        }
    }


    void plot_reals(uint8_t* Buffer, Data::DATAS_T& Datas)
    {
        float x_min = Datas[0u].TimeFrequency;
        float x_max = Datas[0u].TimeFrequency;

        for (size_t i = 1u; i < Datas.size(); i++)
        {
            x_min = x_min < Datas[i].TimeFrequency ? x_min : Datas[i].TimeFrequency;
            x_max = x_max > Datas[i].TimeFrequency ? x_max : Datas[i].TimeFrequency;
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

        uint32_t x_previous = static_cast<uint32_t>(x_scale * (Datas[0u].TimeFrequency - x_min));
        uint32_t y_previous = static_cast<uint32_t>(y_scale * (Datas[0u].Real          - y_min));

        for (size_t i = 1u; i < Datas.size(); i++)
        {
            uint32_t x_current = static_cast<uint32_t>(x_scale * (Datas[i].TimeFrequency - x_min));
            uint32_t y_current = static_cast<uint32_t>(y_scale * (Datas[i].Real          - y_min));

            plot_line(Buffer, x_previous, y_previous, x_current, y_current);

            x_previous = x_current;
            y_previous = y_current;
        }
    }


    void plot_imaginaries(uint8_t* Buffer, Data::DATAS_T& Datas)
    {
        float x_min = Datas[0u].TimeFrequency;
        float x_max = Datas[0u].TimeFrequency;

        for (size_t i = 1u; i < Datas.size(); i++)
        {
            x_min = x_min < Datas[i].TimeFrequency ? x_min : Datas[i].TimeFrequency;
            x_max = x_max > Datas[i].TimeFrequency ? x_max : Datas[i].TimeFrequency;
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

        uint32_t x_previous = static_cast<uint32_t>(x_scale * (Datas[0u].TimeFrequency - x_min));
        uint32_t y_previous = static_cast<uint32_t>(y_scale * (Datas[0u].Imaginary     - y_min));

        for (size_t i = 1u; i < Datas.size(); i++)
        {
            uint32_t x_current = static_cast<uint32_t>(x_scale * (Datas[i].TimeFrequency - x_min));
            uint32_t y_current = static_cast<uint32_t>(y_scale * (Datas[i].Real          - y_min));

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
        fprintf(file, "%d %d\n", _x_border + _x_length + _x_border, (_y_border + _y_length + _y_border) * 3u);
        fprintf(file, "%d\n", 255);

        for (size_t i = 0u; i < (_x_border + _x_length + _x_border) * (_y_border + _y_length + _y_border) * 3u; i++)
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
        uint8_t*    buffer  = new uint8_t[(_y_border + _y_length + _y_border) * (_x_border + _x_length + _x_border) * 3u]{};

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

//      plot_modules    (&buffer[(_y_border + _y_length + _y_border) * (_x_border + _x_length + _x_border) * 0u], Datas);
        plot_reals      (&buffer[(_y_border + _y_length + _y_border) * (_x_border + _x_length + _x_border) * 1u], Datas);
//      plot_imaginaries(&buffer[(_y_border + _y_length + _y_border) * (_x_border + _x_length + _x_border) * 2u], Datas);

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
