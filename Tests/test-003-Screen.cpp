
#include <thread>

#include "Base/Screen.h"
#include "Base/UtilsPgm.h"


bool test_pattern_horizontal_static()
{
    constexpr uint32_t  screen_width    = 512u;
    constexpr uint32_t  screen_height   = 512u;
    std::string         screen_title    = "test_pattern_horizontal_static";

    uint8_t             data_gray[screen_width * screen_height]{};

    bool                ret_val         = true;
    Screen::Screen      screen;

    if (!screen.initialize(screen_width, screen_height, screen_title))
    {
        fprintf(stderr, "%s:%d:%s: Failed to initialize screen\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    for (uint32_t i = 0u; i < 100u; i++)
    {
        for (uint32_t y = 0u; y < screen_height; y++)
        {
            for (uint32_t x = 0u; x < screen_width; x++)
            {
                uint32_t offset = y * screen_width + x;

                if (((0   <= y) && (y < 128u))
                ||  ((256 <= y) && (y < 382u)))
                {
                    data_gray[offset] = 0x00;
                }
                else
                {
                    data_gray[offset] = x / 2u;
                }
            }
        }

        if (!screen.display_image(data_gray))
        {
            fprintf(stderr, "%s:%d:%s: Failed to display image\n", __FILE__, __LINE__, __FUNCTION__);
            ret_val = false;
            goto terminate;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100u));
    }

terminate:
    screen.deinitialize();

    return ret_val;
}


bool test_pattern_vertical_static()
{
    constexpr uint32_t  screen_width    = 512u;
    constexpr uint32_t  screen_height   = 512u;
    std::string         screen_title    = "test_pattern_vertical_static";

    uint8_t             data_gray[screen_width * screen_height]{};

    bool                ret_val         = true;
    Screen::Screen      screen;

    if (!screen.initialize(screen_width, screen_height, screen_title))
    {
        fprintf(stderr, "%s:%d:%s: Failed to initialize screen\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    for (uint32_t i = 0u; i < 100u; i++)
    {
        for (uint32_t y = 0u; y < screen_height; y++)
        {
            for (uint32_t x = 0u; x < screen_width; x++)
            {
                uint32_t offset = y * screen_width + x;

                if (((0   <= x) && (x < 128u))
                ||  ((256 <= x) && (x < 382u)))
                {
                    data_gray[offset] = 0x00;
                }
                else
                {
                    data_gray[offset] = y / 2u;
                }
            }
        }

        if (!screen.display_image(data_gray))
        {
            fprintf(stderr, "%s:%d:%s: Failed to display image\n", __FILE__, __LINE__, __FUNCTION__);
            ret_val = false;
            goto terminate;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100u));
    }

terminate:
    screen.deinitialize();

    return ret_val;
}


bool test_pattern_horizontal()
{
    constexpr uint32_t  screen_width    = 512u;
    constexpr uint32_t  screen_height   = 512u;
    std::string         screen_title    = "test_pattern_horizontal";

    uint8_t             data_gray[screen_width * screen_height]{};

    bool                ret_val         = true;
    uint8_t             value           = 0u;
    Screen::Screen      screen;

    if (!screen.initialize(screen_width, screen_height, screen_title))
    {
        fprintf(stderr, "%s:%d:%s: Failed to initialize screen\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    for (uint32_t i = 0u; i < 100u; i++)
    {
        for (uint32_t y = 0u; y < screen_height; y++)
        {
            for (uint32_t x = 0u; x < screen_width; x++)
            {
                uint32_t offset = y * screen_width + x;

                if (((y >= 0u)   && (y < 128u))
                ||  ((y >= 256u) && (y < 382u)))
                {
                    data_gray[offset] = 0x00;
                }
                else
                {
                    data_gray[offset] = value;
                }
            }
        }

        value++;

        if (!screen.display_image(data_gray))
        {
            fprintf(stderr, "%s:%d:%s: Failed to display image\n", __FILE__, __LINE__, __FUNCTION__);
            ret_val = false;
            goto terminate;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100u));
    }

terminate:
    screen.deinitialize();

    return ret_val;
}


bool test_pattern_vertical()
{
    constexpr uint32_t  screen_width    = 512u;
    constexpr uint32_t  screen_height   = 512u;
    std::string         screen_title    = "test_pattern_vertical";

    uint8_t             data_gray[screen_width * screen_height]{};

    bool                ret_val         = true;
    uint8_t             value           = 0u;
    Screen::Screen      screen;

    if (!screen.initialize(screen_width, screen_height, screen_title))
    {
        fprintf(stderr, "%s:%d:%s: Failed to initialize screen\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    for (uint32_t i = 0u; i < 100u; i++)
    {
        for (uint32_t y = 0u; y < screen_height; y++)
        {
            for (uint32_t x = 0u; x < screen_width; x++)
            {
                uint32_t offset = y * screen_width + x;

                if (((x >= 0u)   && (x < 128u))
                ||  ((x >= 256u) && (x < 382u)))
                {
                    data_gray[offset] = 0x00;
                }
                else
                {
                    data_gray[offset] = value;
                }
            }
        }

        value++;

        if (!screen.display_image(data_gray))
        {
            fprintf(stderr, "%s:%d:%s: Failed to display image\n", __FILE__, __LINE__, __FUNCTION__);
            ret_val = false;
            goto terminate;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100u));
    }

terminate:
    screen.deinitialize();

    return ret_val;
}


bool test_single_image()
{
    constexpr uint32_t  screen_width    = 512u;
    constexpr uint32_t  screen_height   = 512u;
    std::string         screen_title    = "test_single_image";

    bool                ret_val         = true;
    std::string         filename        = "./Data/Input/barbara.pgm";
    uint32_t            width           = 0u;
    uint32_t            height          = 0u;
    uint32_t            maximum         = 0u;
    uint8_t*            data_gray       = nullptr;
    Screen::Screen      screen;

    if (!screen.initialize(screen_width, screen_height, screen_title))
    {
        fprintf(stderr, "%s:%d:%s: Failed to initialize screen\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!UtilsPgm::read(&data_gray, height, width, maximum, nullptr, filename))
    {
        fprintf(stderr, "%s:%d:%s: Failed to open file\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (screen_width != width)
    {
        fprintf(stderr, "%s:%d:%s: Invalid width\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (screen_height != height)
    {
        fprintf(stderr, "%s:%d:%s: Invalid height\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!screen.display_image(data_gray))
    {
        fprintf(stderr, "%s:%d:%s: Failed to display image\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(10000u));

terminate:
    screen.deinitialize();

    if (data_gray)
    {
        delete[] data_gray;
    }

    return ret_val;
}


bool test_multiple_images()
{
    constexpr uint32_t  screen_width    = 320u;
    constexpr uint32_t  screen_height   = 240u;
    std::string         screen_title    = "test_multiple_images";

    bool                ret_val         = true;
    std::string         filename        = "Data/Input/Frames-0320x0240/frame-0320x0240-";
    uint32_t            width           = 0u;
    uint32_t            height          = 0u;
    uint32_t            maximum         = 0u;
    uint8_t*            data_gray       = nullptr;
    char                number[5u]      {};
    Screen::Screen      screen;

    if (!screen.initialize(screen_width, screen_height, screen_title))
    {
        fprintf(stderr, "%s:%d:%s: Failed to initialize screen\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    for (uint32_t i = 0u; i < 100u; i++)
    {
        std::sprintf(number, "%04u", i);

        std::string valid_filename = filename + number + ".pgm";

        if (!UtilsPgm::read(&data_gray, height, width, maximum, nullptr, valid_filename))
        {
            fprintf(stderr, "%s:%d:%s: Failed to open file\n", __FILE__, __LINE__, __FUNCTION__);
            ret_val = false;
            goto terminate;
        }

        if (screen_width != width)
        {
            fprintf(stderr, "%s:%d:%s: Invalid width\n", __FILE__, __LINE__, __FUNCTION__);
            ret_val = false;
            goto terminate;
        }

        if (screen_height != height)
        {
            fprintf(stderr, "%s:%d:%s: Invalid height\n", __FILE__, __LINE__, __FUNCTION__);
            ret_val = false;
            goto terminate;
        }

        if (!screen.display_image(data_gray))
        {
            fprintf(stderr, "%s:%d:%s: Failed to display image\n", __FILE__, __LINE__, __FUNCTION__);
            ret_val = false;
            goto terminate;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100u));
    }

terminate:
    screen.deinitialize();

    if (data_gray)
    {
        delete[] data_gray;
    }

    return ret_val;
}


int main()
{
    if (!test_pattern_horizontal_static())
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    if (!test_pattern_vertical_static())
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    if (!test_pattern_horizontal())
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    if (!test_pattern_vertical())
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    if (!test_single_image())
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    if (!test_multiple_images())
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    return 0;
}
