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

        std::string OrderData();
        std::string GridTemplateData();
        std::string GridColsData();
        std::string GridRowsData();
        std::string GridAutoData();
        std::string GapData();

    };

};
