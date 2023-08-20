#pragma once
#include "Base.h"

namespace Tailwind {

    class Grid {
    public:
        Grid(std::vector<std::string> spacing_variants = {});
        Propriety order;
        Propriety grid_template_columns;
        Propriety grid_cols_start;
        Propriety grid_cols_span;
        Propriety grid_cols_end;

        Propriety grid_template_rows;
        Propriety grid_rows_start;
        Propriety grid_rows_span;
        Propriety grid_rows_end;
        
        Propriety grid_auto_flow;
        Propriety grid_auto_columns;
        Propriety grid_auto_rows;

        Propriety gap;
        Propriety gap_x;
        Propriety gap_y;


        Propriety place_content;
        Propriety place_items;
        Propriety place_self;

        boost::regex order_regex = boost::regex("(?<=\n| )(!)?order-(12|11|10|9|8|7|6|5|4|3|2|1|none|last|first)(?!\\w|-)");
        boost::regex grid_template_columns_regex = boost::regex("(?<=\n| )(!)?grid-cols-(12|11|10|9|8|7|6|5|4|3|2|1|none)(?!\\w|-)");
        boost::regex grid_cols_start_regex =    boost::regex("(?<=\n| )(!)?col-start-(13|12|11|10|9|8|7|6|5|4|3|2|1|full|auto)(?!\\w|-)");
        boost::regex grid_cols_span_regex =     boost::regex("(?<=\n| )(!)?col-(auto|span-(12|11|10|9|8|7|6|5|4|3|2|1|full))(?!\\w|-)");
        boost::regex grid_cols_end_regex =      boost::regex("(?<=\n| )(!)?col-end-(13|12|11|10|9|8|7|6|5|4|3|2|1|full|auto)(?!\\w|-)");

        boost::regex grid_template_rows_regex = boost::regex("(?<=\n| )(!)?grid-rows-(6|5|4|3|2|1|none)(?!\\w|-)");
        boost::regex grid_rows_start_regex =    boost::regex("(?<=\n| )(!)?row-start-(13|12|11|10|9|8|7|6|5|4|3|2|1|full|auto)(?!\\w|-)");
        boost::regex grid_rows_span_regex =     boost::regex("(?<=\n| )(!)?row-(auto|span-(12|11|10|9|8|7|6|5|4|3|2|1|full))(?!\\w|-)");
        boost::regex grid_rows_end_regex =      boost::regex("(?<=\n| )(!)?row-end-(13|12|11|10|9|8|7|6|5|4|3|2|1|full|auto)(?!\\w|-)");

        boost::regex grid_auto_flow_regex =     boost::regex("(?<=\n| )(!)?grid-flow-(row|col|dense|row-dense|col-dense)(?!\\w|-)");
        boost::regex grid_auto_columns_regex =  boost::regex("(?<=\n| )(!)?auto-cols-(auto|min|max|fr)(?!\\w|-)");
        boost::regex grid_auto_rows_regex =     boost::regex("(?<=\n| )(!)?auto-rows-(auto|min|max|fr)(?!\\w|-)");

        boost::regex gap_regex =                boost::regex("(?<=\n| )(!)?gap(-x|-y)?-(96|80|72|64|60|56|52|48|44|40|36|32|28|24|20|16|14|12|11|10|9|8|7|6|5|4|3.5|3|2.5|2|1.5|1|0.5|0|px)(?!\\w|-)");

        boost::regex place_self_regex =         boost::regex("(?<=\n| )(!)?place-self-(auto|start|end|center|stretch)(?!\\w|-)");
        boost::regex place_items_regex =        boost::regex("(?<=\n| )(!)?place-items-(start|end|center|baseline|stretch)(?!\\w|-)");
        boost::regex place_content_regex =      boost::regex("(?<=\n| )(!)?place-content-(center|start|end|between|around|evenly|baseline|stretch)(?!\\w|-)");


        std::string orderData();
        std::string gridTemplateData();
        std::string gridColsData();
        std::string gridRowsData();
        std::string gridAutoData();
        std::string gapData();
        std::string placeData();

    };

};
