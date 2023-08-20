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