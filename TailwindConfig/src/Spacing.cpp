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

    // iterate in reverse over spacing_variants
    for(auto size : spacing_variants)
    {
        margin.styleClasses_.push_back(StyleClass("-m-" + size, ""));
        margin_x.styleClasses_.push_back(StyleClass("-mx-" + size, ""));
        margin_y.styleClasses_.push_back(StyleClass("-my-" + size, ""));
        margin_top.styleClasses_.push_back(StyleClass("-mt-" + size, ""));
        margin_right.styleClasses_.push_back(StyleClass("-mr-" + size, ""));
        margin_bottom.styleClasses_.push_back(StyleClass("-mb-" + size, ""));
        margin_left.styleClasses_.push_back(StyleClass("-ml-" + size, ""));
        margin_start.styleClasses_.push_back(StyleClass("-ms-" + size, ""));
        margin_end.styleClasses_.push_back(StyleClass("-me-" + size, ""));
    }
    margin.styleClasses_.push_back(StyleClass("none", ""));
    margin_x.styleClasses_.push_back(StyleClass("none", ""));
    margin_y.styleClasses_.push_back(StyleClass("none", ""));
    margin_top.styleClasses_.push_back(StyleClass("none", ""));
    margin_right.styleClasses_.push_back(StyleClass("none", ""));
    margin_bottom.styleClasses_.push_back(StyleClass("none", ""));
    margin_left.styleClasses_.push_back(StyleClass("none", ""));
    margin_start.styleClasses_.push_back(StyleClass("none", ""));
    margin_end.styleClasses_.push_back(StyleClass("none", ""));

    margin.styleClasses_.push_back(StyleClass("m-auto", ""));
    margin_x.styleClasses_.push_back(StyleClass("mx-auto", ""));
    margin_y.styleClasses_.push_back(StyleClass("my-auto", ""));
    margin_top.styleClasses_.push_back(StyleClass("mt-auto", ""));
    margin_right.styleClasses_.push_back(StyleClass("mr-auto", ""));
    margin_bottom.styleClasses_.push_back(StyleClass("mb-auto", ""));
    margin_left.styleClasses_.push_back(StyleClass("ml-auto", ""));
    margin_start.styleClasses_.push_back(StyleClass("ms-auto", ""));
    margin_end.styleClasses_.push_back(StyleClass("me-auto", ""));
    
    padding.styleClasses_.push_back(StyleClass("none", ""));
    padding_x.styleClasses_.push_back(StyleClass("none", ""));
    padding_y.styleClasses_.push_back(StyleClass("none", ""));
    padding_top.styleClasses_.push_back(StyleClass("none", ""));
    padding_right.styleClasses_.push_back(StyleClass("none", ""));
    padding_bottom.styleClasses_.push_back(StyleClass("none", ""));
    padding_left.styleClasses_.push_back(StyleClass("none", ""));
    padding_start.styleClasses_.push_back(StyleClass("none", ""));
    padding_end.styleClasses_.push_back(StyleClass("none", ""));

    space_x.styleClasses_.push_back(StyleClass("none", ""));
    space_y.styleClasses_.push_back(StyleClass("none", ""));

    for( int i = spacing_variants.size() - 1; i >= 0; i--)
    {
        margin.styleClasses_.push_back(StyleClass("m-" + spacing_variants[i], ""));
        margin_x.styleClasses_.push_back(StyleClass("mx-" + spacing_variants[i], ""));
        margin_y.styleClasses_.push_back(StyleClass("my-" + spacing_variants[i], ""));
        margin_top.styleClasses_.push_back(StyleClass("mt-" + spacing_variants[i], ""));
        margin_right.styleClasses_.push_back(StyleClass("mr-" + spacing_variants[i], ""));
        margin_bottom.styleClasses_.push_back(StyleClass("mb-" + spacing_variants[i], ""));
        margin_left.styleClasses_.push_back(StyleClass("ml-" + spacing_variants[i], ""));
        margin_start.styleClasses_.push_back(StyleClass("ms-" + spacing_variants[i], ""));
        margin_end.styleClasses_.push_back(StyleClass("me-" + spacing_variants[i], ""));

        padding.styleClasses_.push_back(StyleClass("p-" + spacing_variants[i], ""));
        padding_x.styleClasses_.push_back(StyleClass("px-" + spacing_variants[i], ""));
        padding_y.styleClasses_.push_back(StyleClass("py-" + spacing_variants[i], ""));
        padding_top.styleClasses_.push_back(StyleClass("pt-" + spacing_variants[i], ""));
        padding_right.styleClasses_.push_back(StyleClass("pr-" + spacing_variants[i], ""));
        padding_bottom.styleClasses_.push_back(StyleClass("pb-" + spacing_variants[i], ""));
        padding_left.styleClasses_.push_back(StyleClass("pl-" + spacing_variants[i], ""));
        padding_start.styleClasses_.push_back(StyleClass("ps-" + spacing_variants[i], ""));
        padding_end.styleClasses_.push_back(StyleClass("pe-" + spacing_variants[i], ""));

        space_x.styleClasses_.push_back(StyleClass("space-x-" + spacing_variants[i], ""));
        space_y.styleClasses_.push_back(StyleClass("space-y-" + spacing_variants[i], ""));
    }
}

std::vector<std::string> Spacing::search_data()
{
    std::vector<std::string> data = {};
    for(auto styleClass : margin.styleClasses_) data.push_back("spacing/" + styleClass.className_);
    for(auto styleClass : margin_x.styleClasses_) data.push_back("spacing/" + styleClass.className_);
    for(auto styleClass : margin_y.styleClasses_) data.push_back("spacing/" + styleClass.className_);
    for(auto styleClass : margin_top.styleClasses_) data.push_back("spacing/" + styleClass.className_);
    for(auto styleClass : margin_right.styleClasses_) data.push_back("spacing/" + styleClass.className_);
    for(auto styleClass : margin_bottom.styleClasses_) data.push_back("spacing/" + styleClass.className_);
    for(auto styleClass : margin_left.styleClasses_) data.push_back("spacing/" + styleClass.className_);
    // for(auto styleClass : margin_start.styleClasses_) data.push_back("spacing/" + styleClass.className_);
    // for(auto styleClass : margin_end.styleClasses_) data.push_back("spacing/" + styleClass.className_);

    for(auto styleClass : padding.styleClasses_) data.push_back("spacing/" + styleClass.className_); 
    for(auto styleClass : padding_x.styleClasses_) data.push_back("spacing/" + styleClass.className_);
    for(auto styleClass : padding_y.styleClasses_) data.push_back("spacing/" + styleClass.className_);
    for(auto styleClass : padding_top.styleClasses_) data.push_back("spacing/" + styleClass.className_);
    for(auto styleClass : padding_right.styleClasses_) data.push_back("spacing/" + styleClass.className_);
    for(auto styleClass : padding_bottom.styleClasses_) data.push_back("spacing/" + styleClass.className_);
    for(auto styleClass : padding_left.styleClasses_) data.push_back("spacing/" + styleClass.className_);
    // for(auto styleClass : padding_start.styleClasses_) data.push_back("spacing/" + styleClass.className_);
    // for(auto styleClass : padding_end.styleClasses_) data.push_back("spacing/" + styleClass.className_);

    for(auto styleClass : space_x.styleClasses_) data.push_back("spacing/" + styleClass.className_);
    for(auto styleClass : space_y.styleClasses_) data.push_back("spacing/" + styleClass.className_);
    for(auto styleClass : space_x_reverse.styleClasses_) data.push_back("spacing/" + styleClass.className_);
    for(auto styleClass : space_y_reverse.styleClasses_) data.push_back("spacing/" + styleClass.className_);
return data;
}


std::string Spacing::marginData()
{
    std::string data = " ";
    for(auto styleClass : margin.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    for(auto styleClass : margin_x.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    for(auto styleClass : margin_y.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    for(auto styleClass : margin_top.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    for(auto styleClass : margin_right.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    for(auto styleClass : margin_bottom.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    for(auto styleClass : margin_left.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    for(auto styleClass : margin_start.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    for(auto styleClass : margin_end.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    return data;
}

std::string Spacing::paddingData()
{
    std::string data = " ";
    for(auto styleClass : padding.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    for(auto styleClass : padding_x.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    for(auto styleClass : padding_y.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    for(auto styleClass : padding_top.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    for(auto styleClass : padding_right.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    for(auto styleClass : padding_bottom.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    for(auto styleClass : padding_left.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    for(auto styleClass : padding_start.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    for(auto styleClass : padding_end.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    return data;
}

std::string Spacing::spaceData()
{
    std::string data = " ";
    for(auto styleClass : space_x.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    for(auto styleClass : space_y.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    for(auto styleClass : space_x_reverse.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    for(auto styleClass : space_y_reverse.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    return data;
}