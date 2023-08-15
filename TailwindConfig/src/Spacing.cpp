#include "include/Spacing.h"

using namespace Tailwind;

Spacing::Spacing(std::vector<std::string> spacing_variants)
{
    margin = Propriety({}, "https://tailwindcss.com/docs/margin");
    margin_x = Propriety({}, "https://tailwindcss.com/docs/margin");
    margin_y = Propriety({}, "https://tailwindcss.com/docs/margin");
    margin_top = Propriety({}, "https://tailwindcss.com/docs/margin");
    margin_right = Propriety({}, "https://tailwindcss.com/docs/margin");
    margin_bottom = Propriety({}, "https://tailwindcss.com/docs/margin");
    margin_left = Propriety({}, "https://tailwindcss.com/docs/margin");
    margin_start = Propriety({}, "https://tailwindcss.com/docs/margin");
    margin_end = Propriety({}, "https://tailwindcss.com/docs/margin");

    padding = Propriety({}, "https://tailwindcss.com/docs/padding");
    padding_x = Propriety({}, "https://tailwindcss.com/docs/padding");
    padding_y = Propriety({}, "https://tailwindcss.com/docs/padding");
    padding_top = Propriety({}, "https://tailwindcss.com/docs/padding");
    padding_right = Propriety({}, "https://tailwindcss.com/docs/padding");
    padding_bottom = Propriety({}, "https://tailwindcss.com/docs/padding");
    padding_left = Propriety({}, "https://tailwindcss.com/docs/padding");
    padding_start = Propriety({}, "https://tailwindcss.com/docs/padding");
    padding_end = Propriety({}, "https://tailwindcss.com/docs/padding");

    space_x = Propriety({}, "https://tailwindcss.com/docs/space");
    space_y = Propriety({}, "https://tailwindcss.com/docs/space");
    
    space_x_reverse = Propriety({StyleClass("space-x-reverse", "")}, "https://tailwindcss.com/docs/space");
    space_y_reverse = Propriety({StyleClass("space-y-reverse", "")}, "https://tailwindcss.com/docs/space");

    for(auto size : spacing_variants)
    {
        margin.styleClasses_.push_back(StyleClass("m-" + size, ""));
        margin_x.styleClasses_.push_back(StyleClass("mx-" + size, ""));
        margin_y.styleClasses_.push_back(StyleClass("my-" + size, ""));
        margin_top.styleClasses_.push_back(StyleClass("mt-" + size, ""));
        margin_right.styleClasses_.push_back(StyleClass("mr-" + size, ""));
        margin_bottom.styleClasses_.push_back(StyleClass("mb-" + size, ""));
        margin_left.styleClasses_.push_back(StyleClass("ml-" + size, ""));
        margin_start.styleClasses_.push_back(StyleClass("ms-" + size, ""));
        margin_end.styleClasses_.push_back(StyleClass("me-" + size, ""));

        padding.styleClasses_.push_back(StyleClass("p-" + size, ""));
        padding_x.styleClasses_.push_back(StyleClass("px-" + size, ""));
        padding_y.styleClasses_.push_back(StyleClass("py-" + size, ""));
        padding_top.styleClasses_.push_back(StyleClass("pt-" + size, ""));
        padding_right.styleClasses_.push_back(StyleClass("pr-" + size, ""));
        padding_bottom.styleClasses_.push_back(StyleClass("pb-" + size, ""));
        padding_left.styleClasses_.push_back(StyleClass("pl-" + size, ""));
        padding_start.styleClasses_.push_back(StyleClass("ps-" + size, ""));
        padding_end.styleClasses_.push_back(StyleClass("pe-" + size, ""));

        space_x.styleClasses_.push_back(StyleClass("space-x-" + size, ""));
        space_y.styleClasses_.push_back(StyleClass("space-y-" + size, ""));
    }
}

std::string Spacing::MarginData()
{
    std::string data = "Margin ------------------------------------\n";
    data += "Margin ---------\n";
    for(auto styleClass : margin.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\nMargin x ---------\n";
    for(auto styleClass : margin_x.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\nMargin y ---------\n";
    for(auto styleClass : margin_y.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\nMargin top ---------\n";
    for(auto styleClass : margin_top.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\nMargin right ---------\n";
    for(auto styleClass : margin_right.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\nMargin bottom ---------\n";
    for(auto styleClass : margin_bottom.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\nMargin left ---------\n";
    for(auto styleClass : margin_left.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\nMargin start ---------\n";
    for(auto styleClass : margin_start.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\nMargin end ---------\n";
    for(auto styleClass : margin_end.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }

    return data;
}

std::string Spacing::PaddingData()
{
    std::string data = "Padding ------------------------------------\n";
    data += "Padding ---------\n";
    for(auto styleClass : padding.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\nPadding x ---------\n";
    for(auto styleClass : padding_x.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\nPadding y ---------\n";
    for(auto styleClass : padding_y.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\nPadding top ---------\n";
    for(auto styleClass : padding_top.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\nPadding right ---------\n";
    for(auto styleClass : padding_right.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\nPadding bottom ---------\n";
    for(auto styleClass : padding_bottom.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\nPadding left ---------\n";
    for(auto styleClass : padding_left.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\nPadding start ---------\n";
    for(auto styleClass : padding_start.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\nPadding end ---------\n";
    for(auto styleClass : padding_end.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }

    return data;
}