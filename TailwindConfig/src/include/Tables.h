#pragma once
#include "Base.h"

namespace Tailwind {

    class Tables {
    public:
        Tables(std::vector<std::string> spacing_variants = {});
        Propriety border_collapse;
        Propriety border_spacing;
        Propriety border_spacing_x;
        Propriety border_spacing_y;
        Propriety table_layout;
        Propriety caption_side;

        std::string borderCollapseData();
        std::string borderSpacingData();
        std::string tableLayoutData();
        std::string captionSideData();

        boost::regex border_collapse_regex = boost::regex("(?<=\n| )(!)?border-(collapse|separate)");
        boost::regex border_spacing_regex = boost::regex("(?<=\n| )(!)?border-spacing-(96|80|72|64|60|56|52|48|44|40|36|32|28|24|20|16|14|12|11|10|9|8|7|6|5|4|3.5|3|2.5|2|1.5|1|0.5|0|px)");
        boost::regex border_spacing_x_regex = boost::regex("(?<=\n| )(!)?border-spacing-x-(96|80|72|64|60|56|52|48|44|40|36|32|28|24|20|16|14|12|11|10|9|8|7|6|5|4|3.5|3|2.5|2|1.5|1|0.5|0|px)");
        boost::regex border_spacing_y_regex = boost::regex("(?<=\n| )(!)?border-spacing-y-(96|80|72|64|60|56|52|48|44|40|36|32|28|24|20|16|14|12|11|10|9|8|7|6|5|4|3.5|3|2.5|2|1.5|1|0.5|0|px)");
        boost::regex table_layout_regex = boost::regex("(?<=\n| )(!)?table-(auto|fixed)");
        boost::regex caption_side_regex = boost::regex("(?<=\n| )(!)?caption-(top|bottom)");
    };

};
