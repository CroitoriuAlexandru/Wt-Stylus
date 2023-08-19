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
        

        std::string transitionPropertyData();
        std::string transitionDurationData();
        std::string transitionTimingFunctionData();
        std::string transitionDelayData();
        std::string animationData();

        boost::regex transition_property_regex = boost::regex("(?<=\n| )(!)?transition(-none|-all|-colors|-opacity|-shadow|-transform)?");
        boost::regex transition_duration_regex = boost::regex("(?<=\n| )(!)?duration-(1000|700|500|300|200|150|100|75|0)");
        boost::regex transition_timing_function_regex = boost::regex("(?<=\n| )(!)?ease-(linear|in-out|in|out)");
        boost::regex transition_delay_regex = boost::regex("(?<=\n| )(!)?delay-(1000|700|500|300|200|150|100|75|0)");
        boost::regex animation_regex = boost::regex("(?<=\n| )(!)?animate-(none|spin|ping|pulse|bounce)");
    };

};
