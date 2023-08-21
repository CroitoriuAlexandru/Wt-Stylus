#pragma once
#include "Base.h"

namespace Tailwind {

    class Svg {
    public:
        Svg();
        // fill will be implemented programaticaly
        // stroke will be implemented programaticaly
        Propriety stroke_width;
        
        std::vector<std::string> search_data();

        std::string strokeWidthData();

        boost::regex stroke_width_regex = boost::regex("(?<=\n| )(!)?stroke-(0|1|2)(?!\\w|-)");
    };

};
