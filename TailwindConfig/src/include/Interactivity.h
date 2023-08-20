#pragma once
#include "Base.h"

namespace Tailwind {

    class Interactivity {
    public:
        Interactivity(std::vector<std::string> sizing_variants = {});
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

        // accent color
        boost::regex appearance_regex = boost::regex("(?<=\n| )(!)?appearance-none(?!\\w|-)");
        boost::regex cursor_regex = boost::regex("(?<=\n| )(!)?cursor-(auto|default|pointer|wait|text|move|help|not-allowed|none|progress|cell|crosshair|vertical-text|alias|copy|no-drop|all-scroll|col-resize|row-resize|n-resize|e-resize|s-resize|w-resize|ne-resize|nw-resize|se-resize|sw-resize|ew-resize|ns-resize|nesw-resize|nwse-resize|zoom-in|zoom-out)(?!\\w|-)");
        // carret color
        boost::regex pointer_events_regex = boost::regex("(?<=\n| )(!)?pointer-events-(none|auto)(?!\\w|-)");
        boost::regex resize_regex = boost::regex("(?<= )(?<=\n| )(!)?resize(-none|-y|-x)?(?!\\w|-)");
        boost::regex scroll_behavior_regex = boost::regex("(?<=\n| )(!)?scroll-(auto|smooth)(?!\\w|-)");
        boost::regex scroll_margin_regex = boost::regex("(?<=\n| )(!)?scroll-m(x|y|t|r|b|l|s|e)?-(96|80|72|64|60|56|52|48|44|40|36|32|28|24|20|16|14|12|11|10|9|8|7|6|5|4|3.5|3|2.5|2|1.5|1|0.5|0|px)(?!\\w|-)");
        boost::regex scroll_padding_regex = boost::regex("(?<=\n| )(!)?scroll-p(x|y|t|r|b|l|s|e)?-(96|80|72|64|60|56|52|48|44|40|36|32|28|24|20|16|14|12|11|10|9|8|7|6|5|4|3.5|3|2.5|2|1.5|1|0.5|0|px)(?!\\w|-)");
        boost::regex scroll_snap_align_regex = boost::regex("(?<=\n| )(!)?snap-(align-none|start|end|center)(?!\\w|-)");
        boost::regex scroll_snap_stop_regex = boost::regex("(?<=\n| )(!)?snap-(normal|always)(?!\\w|-)");
        boost::regex scroll_snap_type_regex = boost::regex("(?<=\n| )(!)?snap-(none|x|y|both)(?!\\w|-)");
        boost::regex scroll_snap_proximity_regex = boost::regex("(?<=\n| )(!)?snap-proximity(?!\\w|-)");
        boost::regex scroll_snap_mandatory_regex = boost::regex("(?<=\n| )(!)?snap-mandatory(?!\\w|-)");
        boost::regex touch_action_regex = boost::regex("(?<=\n| )(!)?touch-(none|manipulation|pinch-zoom|pan-down|pan-up|pan-y|pan-right|pan-left|pan-x|pan-none|auto)(?!\\w|-)");
        boost::regex user_select_regex = boost::regex("(?<=\n| )(!)?select-(none|text|all|auto)(?!\\w|-)");
        boost::regex will_change_regex = boost::regex("(?<=\n| )(!)?will-change-(auto|scroll|contents|transform)(?!\\w|-)");

    };
};

