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

        std::string BorderCollapseData();
        std::string BorderSpacingData();
        std::string TableLayoutData();
        std::string CaptionSideData();
    };

};
