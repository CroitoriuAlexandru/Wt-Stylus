#include "include/Grid.h"

using namespace Tailwind;

Grid::Grid(std::vector<std::string> spacing_variants)
{
    // order
    order = Propriety({}, "https://tailwindcss.com/docs/order");
    std::vector<std::string> flex_order_number_variants = {"12", "11", "10", "9", "8", "7", "6", "5", "4", "3", "2", "1"};
    StyleClass order_first = StyleClass("order-first", "order: -9999;");
    StyleClass order_last = StyleClass("order-last", "order: 9999;");
    StyleClass order_none = StyleClass("order-none", "order: 0;");
    for(auto size : flex_order_number_variants) {
        order.styleClasses_.push_back(StyleClass("order-" + size, "order: " + size + ";"));
    }
    order.styleClasses_.push_back(order_first);
    order.styleClasses_.push_back(order_last);
    order.styleClasses_.push_back(order_none);

    // grid-template-columns 
    std::vector<std::string> grid_template_variants = {"none", "12", "11", "10", "9", "8", "7", "6", "5", "4", "3", "2", "1"};
    grid_template_columns = Propriety({}, "https://tailwindcss.com/docs/grid-template-columns");
    for(auto size : grid_template_variants) {
        if(size.compare("none") == 0){
            grid_template_columns.styleClasses_.push_back(StyleClass("grid-cols-" + size, "grid-template-columns: none;"));
            grid_template_rows.styleClasses_.push_back(StyleClass("grid-rows-" + size, "grid-template-rows: none;"));
        }else{
            grid_template_columns.styleClasses_.push_back(StyleClass("grid-cols-" + size, "grid-template-columns: repeat(" + size + ", minmax(0, 1fr));"));
            grid_template_rows.styleClasses_.push_back(StyleClass("grid-rows-" + size, "grid-template-rows: repeat(" + size + ", minmax(0, 1fr));"));
        }
    }

    // grid cols / rows , start / end / span
    std::vector<std::string> grid_span_start_end_variants = {"auto", "13", "12", "11", "10", "9", "8", "7", "6", "5", "4", "3", "2", "1"};
    StyleClass grid_col_span_full = StyleClass("col-span-full", "grid-column: 1 / -1;");
    StyleClass grid_row_span_full = StyleClass("row-span-full", "grid-row: 1 / -1;");
    grid_cols_start = Propriety({}, "https://tailwindcss.com/docs/grid-column");
    grid_cols_span = Propriety({grid_col_span_full}, "https://tailwindcss.com/docs/grid-column");
    grid_cols_end = Propriety({}, "https://tailwindcss.com/docs/grid-column");
    grid_rows_start = Propriety({}, "https://tailwindcss.com/docs/grid-row");
    grid_rows_span = Propriety({grid_row_span_full}, "https://tailwindcss.com/docs/grid-row");
    grid_rows_end = Propriety({}, "https://tailwindcss.com/docs/grid-row");

    for(auto size : grid_span_start_end_variants) {
        if(size.compare("auto") == 0){
            grid_cols_start.styleClasses_.push_back(StyleClass("col-start-" + size, "grid-column-start: auto;"));
            grid_cols_span.styleClasses_.push_back(StyleClass("col-" + size, "grid-column-end: auto;"));
            grid_cols_end.styleClasses_.push_back(StyleClass("col-end-" + size, "grid-column-end: auto;"));
            grid_rows_start.styleClasses_.push_back(StyleClass("row-start-" + size, "grid-row-start: auto;"));
            grid_rows_span.styleClasses_.push_back(StyleClass("row-" + size, "grid-row-end: auto;"));
            grid_rows_end.styleClasses_.push_back(StyleClass("row-end-" + size, "grid-row-end: auto;"));
        }else if (size.compare("13") == 0){
            grid_cols_start.styleClasses_.push_back(StyleClass("col-start-" + size, "grid-column-start: " + size + ";"));
            grid_cols_end.styleClasses_.push_back(StyleClass("col-end-" + size, "grid-column-end: " + size + ";"));
            grid_rows_start.styleClasses_.push_back(StyleClass("row-start-" + size, "grid-row-start: " + size + ";"));
            grid_rows_end.styleClasses_.push_back(StyleClass("row-end-" + size, "grid-row-end: " + size + ";"));
        }else {
            grid_cols_start.styleClasses_.push_back(StyleClass("col-start-" + size, "grid-column-start: " + size + ";"));
            grid_cols_span.styleClasses_.push_back(StyleClass("col-span-" + size, "grid-column-end: span " + size + ";"));
            grid_cols_end.styleClasses_.push_back(StyleClass("col-end-" + size, "grid-column-end: " + size + ";"));
            grid_rows_start.styleClasses_.push_back(StyleClass("row-start-" + size, "grid-row-start: " + size + ";"));
            grid_rows_span.styleClasses_.push_back(StyleClass("row-span-" + size, "grid-row-end: span " + size + ";"));
            grid_rows_end.styleClasses_.push_back(StyleClass("row-end-" + size, "grid-row-end: " + size + ";"));
        }

    }

    // grid auto flow
    grid_auto_flow = Propriety({
        StyleClass("grid-flow-row-dense", "grid-auto-flow: row dense;"),
        StyleClass("grid-flow-col-dense", "grid-auto-flow: column dense;"),
        StyleClass("grid-flow-dense", "grid-auto-flow: row dense;"),
        StyleClass("grid-flow-row", "grid-auto-flow: row;"),
        StyleClass("grid-flow-col", "grid-auto-flow: column;")
    }, "https://tailwindcss.com/docs/grid-auto-flow");

    // grid auto cols
    grid_auto_columns = Propriety({
        StyleClass("auto-cols-auto", "grid-auto-columns: auto;"),
        StyleClass("auto-cols-min", "grid-auto-columns: min-content;"),
        StyleClass("auto-cols-max", "grid-auto-columns: max-content;"),
        StyleClass("auto-cols-fr", "grid-auto-columns: minmax(0, 1fr);")
    }, "https://tailwindcss.com/docs/grid-auto-columns");

    // grid auto rows
    grid_auto_rows = Propriety({
        StyleClass("auto-rows-auto", "grid-auto-rows: auto;"),
        StyleClass("auto-rows-min", "grid-auto-rows: min-content;"),
        StyleClass("auto-rows-max", "grid-auto-rows: max-content;"),
        StyleClass("auto-rows-fr", "grid-auto-rows: minmax(0, 1fr);")
    }, "https://tailwindcss.com/docs/grid-auto-rows");
    
    // grid gap gap_x gap_y
    gap = Propriety({}, "https://tailwindcss.com/docs/gap");
    gap_x = Propriety({}, "https://tailwindcss.com/docs/gap");
    gap_y = Propriety({}, "https://tailwindcss.com/docs/gap");

    for(auto size : spacing_variants) {
        gap.styleClasses_.push_back(StyleClass("gap-" + size, "gap: " + size + ";"));
        gap_x.styleClasses_.push_back(StyleClass("gap-x-" + size, "column-gap: " + size + ";"));
        gap_y.styleClasses_.push_back(StyleClass("gap-y-" + size, "row-gap: " + size + ";"));
    }



}

std::string Grid::orderData()
{
    std::string data = "";
    for(auto styleClass : order.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    data += "\n";
    return data;
}

std::string Grid::gridTemplateData()
{
    std::string data = "";
    for(auto styleClass : grid_template_columns.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    data += "\n";
    for(auto styleClass : grid_template_rows.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    data += "\n";
    return data;
}

std::string Grid::gridColsData()
{
    std::string data = "1";
    for(auto styleClass : grid_cols_start.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    data += "\n";
    for(auto styleClass : grid_cols_span.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    data += "\n";
    for(auto styleClass : grid_cols_end.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    data += "\n";
    return data;
}

std::string Grid::gridRowsData()
{
    std::string data = "";
    for(auto styleClass : grid_rows_start.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    data += "\n";
    for(auto styleClass : grid_rows_span.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    data += "\n";
    for(auto styleClass : grid_rows_end.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    data += "\n";
    return data;
}

std::string Grid::gapData()
{
    std::string data = "";
    for(auto styleClass : gap.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    data += "\n";
    for(auto styleClass : gap_x.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    data += "\n";
    for(auto styleClass : gap_y.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    data += "\n";
    return data;
}

std::string Grid::gridAutoData()
{
    std::string data = "";
    for(auto styleClass : grid_auto_flow.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    data += "\n";
    for(auto styleClass : grid_auto_columns.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    data += "\n";
    for(auto styleClass : grid_auto_rows.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    data += "\n";
    return data;
}