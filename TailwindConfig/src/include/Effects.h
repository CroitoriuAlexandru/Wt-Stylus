#pragma once
#include "Base.h"

namespace Tailwind {

    class Effects {
    public:
        Effects();
        Propriety box_shadow;
        Propriety box_shadow_inset;
        // box shadow color will be implemented programaticaly
        Propriety opacity;
        Propriety mix_blend_mode;
        Propriety background_blend_mode;


        std::string BoxShadowData();
        std::string OpacityData();
        std::string MixBlendModeData();

        
    };

};
