#pragma once
#include "Base.h"

namespace Tailwind {

    class Spacing {
    public:
        Spacing(std::vector<std::string> spacing_variants = {});
        Propriety margin;
        Propriety margin_x;
        Propriety margin_y;
        Propriety margin_top;
        Propriety margin_right;
        Propriety margin_bottom;
        Propriety margin_left;
        Propriety margin_start;
        Propriety margin_end;

        Propriety padding;
        Propriety padding_x;
        Propriety padding_y;
        Propriety padding_top;
        Propriety padding_right;
        Propriety padding_bottom;
        Propriety padding_left;
        Propriety padding_start;
        Propriety padding_end;

        Propriety space_x;
        Propriety space_x_reverse;
        Propriety space_y;
        Propriety space_y_reverse;


        std::string MarginData();
        std::string PaddingData();
    };
    
};

