#pragma once
#include "Base.h"

namespace Tailwind {

    class Backgrounds {
    public:
        Backgrounds();
        Propriety background_attachment;
        Propriety background_clip;
        // background_color will be implemented programaticaly
        Propriety background_origin;
        Propriety background_position;
        Propriety background_repeat;
        Propriety background_size;
        Propriety background_image;
        // gradient color stops will be implemented programaticaly

        std::string BackgroundAttachmentData();
        std::string BackgroundClipData();
        std::string BackgroundOriginData();
        std::string BackgroundPositionData();
        std::string BackgroundRepeatData();
        std::string BackgroundSizeData();
        std::string BackgroundImageData();
        
    };

};
