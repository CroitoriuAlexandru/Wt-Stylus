#include "include/Tables.h"

using namespace Tailwind;

Tables::Tables(std::vector<std::string> spacing_variants)
{
    // border collapse
    border_collapse = Propriety({
        StyleClass("none", ""),
        StyleClass("border-collapse", "border-collapse: collapse;"),
        StyleClass("border-separate", "border-collapse: separate;")
    }, "https://tailwindcss.com/docs/border-collapse");

    // table layout
    table_layout = Propriety({
        StyleClass("none", ""),
        StyleClass("table-auto", "table-layout: auto;"),
        StyleClass("table-fixed", "table-layout: fixed;")
    }, "https://tailwindcss.com/docs/table-layout");

    // caption side
    caption_side = Propriety({
        StyleClass("none", ""),
        StyleClass("caption-top", "caption-side: top;"),
        StyleClass("caption-bottom", "caption-side: bottom;")
    }, "https://tailwindcss.com/docs/caption-side");

    // border spacing 
    border_spacing = Propriety({StyleClass("none", "")}, "https://tailwindcss.com/docs/border-spacing");
    border_spacing_x = Propriety({StyleClass("none", "")}, "https://tailwindcss.com/docs/border-spacing");
    border_spacing_y = Propriety({StyleClass("none", "")}, "https://tailwindcss.com/docs/border-spacing");
    for(auto variant : spacing_variants)
    {
        border_spacing.styleClasses_.push_back(StyleClass("border-spacing-" + variant, ";"));
        border_spacing_x.styleClasses_.push_back(StyleClass("border-spacing-x-" + variant, ";"));
        border_spacing_y.styleClasses_.push_back(StyleClass("border-spacing-y-" + variant, ";"));
    }
}

std::vector<std::string> Tables::search_data()
{
    std::vector<std::string> data = {};
    for(auto border_collapse_class : border_collapse.styleClasses_){
        data.push_back("tables/" + border_collapse_class.className_);
    }
    for(auto border_spacing_class : border_spacing.styleClasses_){
        data.push_back("tables/" + border_spacing_class.className_);
    }
    for(auto border_spacing_x_class : border_spacing_x.styleClasses_){
        data.push_back("tables/" + border_spacing_x_class.className_);
    }
    for(auto border_spacing_y_class : border_spacing_y.styleClasses_){
        data.push_back("tables/" + border_spacing_y_class.className_);
    }
    for(auto table_layout_class : table_layout.styleClasses_){
        data.push_back("tables/" + table_layout_class.className_);
    }
    for(auto caption_side_class : caption_side.styleClasses_){
        data.push_back("tables/" + caption_side_class.className_);
    }
return data;
}


std::string Tables::borderCollapseData()
{
    std::string data = " ";
    for(auto styleClass : border_collapse.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data +="\n ";
    return data;
}

std::string Tables::tableLayoutData()
{
    std::string data = " ";
    for(auto styleClass : table_layout.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data +="\n ";
    return data;
}

std::string Tables::captionSideData()
{
    std::string data = " ";
    for(auto styleClass : caption_side.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data +="\n ";
    return data;
}

std::string Tables::borderSpacingData()
{
    std::string data = " ";
    for(auto styleClass : border_spacing.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data +="\n ";
    for(auto styleClass : border_spacing_x.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data +="\n ";
    for(auto styleClass : border_spacing_y.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data +="\n ";
    return data;
}