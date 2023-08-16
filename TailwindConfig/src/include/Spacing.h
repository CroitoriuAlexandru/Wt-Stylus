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


        std::regex padding_regexp = std::regex("(?![\n| ])[!]?p[x,y,t,r,b,l]?-(?:96|80|72|64|56|52|48|44|40|36|32|28|24|20|16|14|12|11|10|9|8|7|6|5|4|3\\.5|3|2\\.5|2|1\\.5|1|0\\.5|0|px|[\\[\\S]*\\])");
        std::regex margin_regexp =  std::regex("(?![\n| ])[!]?-?m[x,y,t,r,b,l]?-(?:auto|96|80|72|64|56|52|48|44|40|36|32|28|24|20|16|14|12|11|10|9|8|7|6|5|4|3\\.5|3|2\\.5|2|1\\.5|1|0\\.5|0|px|[\\[\\S]*\\])");
        std::regex space_regexp = std::regex("(?![\n| ])[!]?space-[x|y]?-(?:reverse|96|80|72|64|56|52|48|44|40|36|32|28|24|20|16|14|12|11|10|9|8|7|6|5|4|3\\.5|3|2\\.5|2|1\\.5|1|0\\.5|0|px|[\\[\\S]*\\])");


        
        
    };
    
};

