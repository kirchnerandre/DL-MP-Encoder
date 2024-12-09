
#ifndef _SCREEN_H_
#define _SCREEN_H_

#include <stdint.h>
#include <string>

#include "Private/PrivateScreen.h"

namespace Screen
{
    class Screen : public PrivateScreen
    {
    public:
        Screen(){};
       ~Screen(){};

        bool initialize(uint32_t ScreenWidth, uint32_t ScreenHeight, std::string& Title);

        bool display_image(uint8_t* ImageData);

        void deinitialize();
    };
}

#endif // _SCREEN_H_
