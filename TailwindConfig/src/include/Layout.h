#pragma once
#include "Base.h"

namespace Tailwind {

    class Layout {
    public:
        Layout(std::vector<std::string> spacingScale = {});
        Propriety aspect_ratio;
        Propriety container;
        Propriety columns;
        Propriety break_after;
        Propriety break_before;
        Propriety break_inside;
        Propriety box_decoration_break;
        Propriety box_sizing;
        Propriety display;
        Propriety floats;
        Propriety clear;
        Propriety isolation;
        Propriety object_fit;
        Propriety object_position;

        Propriety overflow;
        Propriety overflow_x;
        Propriety overflow_y;
        
        Propriety overscroll_behavior;
        Propriety overscroll_behavior_x;
        Propriety overscroll_behavior_y;
        Propriety position;

        Propriety position_inset;
        Propriety position_inset_x;
        Propriety position_inset_y;
        Propriety position_top;
        Propriety position_right;
        Propriety position_bottom;
        Propriety position_left;
        Propriety position_start;
        Propriety position_end;

        Propriety visibility;
        Propriety z_index;


        std::vector<std::string> columns_variants;
        std::vector<std::string> break_before_after_variants;
        std::vector<std::string> break_inside_variants;
        std::vector<std::string> display_variants;
        std::vector<std::string> overflow_variants;
        std::vector<std::string> overscroll_variants;

        std::string AspectRatioData();
        std::string ContainerData();
        std::string ColumnsData();
        std::string BreakAfterData();
        std::string BreakBeforeData();
        std::string BreakInsideData();
        std::string BoxDecorationBreakData();
        std::string BoxSizingData();
        std::string DisplayData();
        std::string FloatsData();
        std::string ClearData();
        std::string IsolationData();
        std::string ObjectFitData();
        std::string ObjectPositionData();
        std::string OverflowData();
        std::string OverscrollBehaviorData();
        std::string PositionData();
        std::string PositionSidesData();
        std::string VisibilityData();
        std::string ZIndexData();
    };
};


