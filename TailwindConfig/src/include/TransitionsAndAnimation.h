#pragma once
#include "Base.h"

namespace Tailwind {

    class TransitionsAndAnimation {
    public:
        TransitionsAndAnimation();
        Propriety transition_property;
        Propriety transition_duration;
        Propriety transition_timing_function;
        Propriety transition_delay;
        Propriety animation;
        

        std::string TransitionPropertyData();
        std::string TransitionDurationData();
        std::string TransitionTimingFunctionData();
        std::string TransitionDelayData();
        std::string AnimationData();
    };

};
