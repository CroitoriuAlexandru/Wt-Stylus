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

        std::string aspectRatioData();
        std::string containerData();
        std::string columnsData();
        std::string breakAfterData();
        std::string breakBeforeData();
        std::string breakInsideData();
        std::string boxDecorationBreakData();
        std::string boxSizingData();
        std::string displayData();
        std::string floatsData();
        std::string clearData();
        std::string isolationData();
        std::string objectFitData();
        std::string objectPositionData();
        std::string overflowData();
        std::string overscrollBehaviorData();
        std::string positionData();
        std::string positionSidesData();
        std::string visibilityData();
        std::string zIndexData();



        boost::regex aspect_ratio_regex = boost::regex("(?<=\n| )(!)?aspect-(auto|square|video)");
        boost::regex container_regex = boost::regex("(?<=\n| )(!)?container");
        boost::regex columns_regex = boost::regex("(?<=\n| )(!)?columns-(auto|3xs|2xs|xs|sm|md|lg|xl|2xl|3xl|4xl|5xl|6xl|7xl|12|11|10|9|8|7|6|5|4|3|2|1)");
        boost::regex break_after_regex = boost::regex("(?<=\n| )(!)?break-before-(avoid-page|auto|avoid|all|page|left|right|column)");
        boost::regex break_before_regex = boost::regex("(?<=\n| )(!)?break-before-(avoid-page|auto|avoid|all|page|left|right|column)");
        boost::regex break_inside_regex = boost::regex("(?<=\n| )(!)?break-inside-(avoid-page|avoid-column|auto|avoid)");
        boost::regex box_decoration_break_regex = boost::regex("box-decoration-(slice|clone)");
        boost::regex box_sizing_regex = boost::regex("(?<=\n| )(!)?box-(border|content)");
        boost::regex display_regex = boost::regex("(?<=\n| )(!)?(table-column-group|table-column|table-footer-group|table-header-group|table-row-group|inline-block|inline-flex|inline-grid|inline-table|inline|table-caption|table-cell|table-row|flow-root|list-item|block|flex|table|grid|contents|[^-]hidden)");
        boost::regex floats_regex = boost::regex("(?<=\n| )(!)?float-(right|left|none)");
        boost::regex clear_regex = boost::regex("(?<=\n| )(!)?clear-(right|left|both|none)");
        boost::regex isolation_regex = boost::regex("(?<=\n| )(!)?(isolate|isolation-auto)");
        boost::regex object_fit_regex = boost::regex("(?<=\n| )(!)?object-(contain|cover|fill|none|scale-down)");
        boost::regex object_position_regex = boost::regex("(?<=\n| )(!)?object-(left-top|right-top|left-bottom|right-bottom|top|right|bottom|left|center)");
        boost::regex overflow_regex = boost::regex("(?<=\n| )(!)?overflow-((x|y)-)?(auto|hidden|visible|scroll|clip)");
        boost::regex overscroll_behavior_regex = boost::regex("(?<=\n| )(!)?overscroll-((x|y)-)?(auto|contain|none)");
        boost::regex position_regex = boost::regex("(?<=\n| )(!)?(static|fixed|absolute|relative|sticky)");
        boost::regex position_inset_regex = boost::regex("(?<=\n| )(!)?inset-((x|y)-)?(3\\/4|2\\/4|1\\/4|2\\/3|1\\/3|1\\/2|96|80|72|64|60|56|52|48|44|40|36|32|28|24|20|16|14|12|11|10|9|8|7|6|5|4|3.5|3|2.5|2|1.5|1|0.5|0|px|full|auto)");
        boost::regex position_sides_regex = boost::regex("(?<=\n| )(!)?(top|left|bottom|right)-(3\\/4|2\\/4|1\\/4|2\\/3|1\\/3|1\\/2|96|80|72|64|60|56|52|48|44|40|36|32|28|24|20|16|14|12|11|10|9|8|7|6|5|4|3.5|3|2.5|2|1.5|1|0.5|0|px|full|auto)"); 
        boost::regex visibility_regex = boost::regex("(?<=\n| )(!)?(visible|invisible|collapse)");
        boost::regex z_index_regex = boost::regex("(?<=\n| )(!)?z-(0|10|20|30|40|50|auto)");
    };
};


  