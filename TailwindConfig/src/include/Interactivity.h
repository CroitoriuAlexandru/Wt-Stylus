#pragma once
#include "Base.h"

namespace Tailwind {

    class Interactivity {
    public:
        Interactivity(
            std::vector<StyleClass> margin = {},
            std::vector<StyleClass> margin_x = {},
            std::vector<StyleClass> margin_y = {},
            std::vector<StyleClass> margin_top = {},
            std::vector<StyleClass> margin_right = {},
            std::vector<StyleClass> margin_bottom = {},
            std::vector<StyleClass> margin_left = {},
            std::vector<StyleClass> margin_start = {},
            std::vector<StyleClass> margin_end = {},
            std::vector<StyleClass> padding = {},
            std::vector<StyleClass> padding_x = {},
            std::vector<StyleClass> padding_y = {},
            std::vector<StyleClass> padding_top = {},
            std::vector<StyleClass> padding_right = {},
            std::vector<StyleClass> padding_bottom = {},
            std::vector<StyleClass> padding_left = {},
            std::vector<StyleClass> padding_start = {},
            std::vector<StyleClass> padding_end = {}
            );
        // Accent color will be implemented programaticaly 
        Propriety appearance;
        Propriety cursor;
        // caret color will be implemented programaticaly
        Propriety pointer_events;
        Propriety resize;
        Propriety scroll_behavior;

        Propriety scroll_margin;
        Propriety scroll_margin_x;
        Propriety scroll_margin_y;
        Propriety scroll_margin_top;
        Propriety scroll_margin_right;
        Propriety scroll_margin_bottom;
        Propriety scroll_margin_left;
        Propriety scroll_margin_start;
        Propriety scroll_margin_end;

        Propriety scroll_padding;
        Propriety scroll_padding_x;
        Propriety scroll_padding_y;
        Propriety scroll_padding_top;
        Propriety scroll_padding_right;
        Propriety scroll_padding_bottom;
        Propriety scroll_padding_left;
        Propriety scroll_padding_start;
        Propriety scroll_padding_end;
        
        Propriety scroll_snap_align;
        Propriety scroll_snap_stop;
        Propriety scroll_snap_type;
        Propriety scroll_snap_manadatory;
        Propriety scroll_snap_proximity;
        Propriety touch_action;
        Propriety user_select;
        Propriety will_change;

        std::string appearanceData();
        std::string cursorData();
        std::string pointerEventsData();
        std::string resizeData();
        std::string scrollBehaviorData();
        std::string scrollMarginData();
        std::string scrollPaddingData();
        std::string scrollSnapAlignData();
        std::string scrollSnapStopData();
        std::string scrollSnapTypeData();
        std::string touchActionData();
        std::string userSelectData();
        std::string willChangeData();

    };
};

