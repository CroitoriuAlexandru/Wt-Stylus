#include "include/Borders.h"

using namespace Tailwind;

Borders::Borders()
{
    
    std::vector<std::string> sizes_radius = {"none", "", "sm", "md", "lg", "xl", "2xl", "3xl", "full"};
    std::string border_radius_link = "https://tailwindcss.com/docs/border-radius";
    border_radius = Propriety({StyleClass("none", "")}, border_radius_link);
    border_radius_s = Propriety({StyleClass("none", "")}, border_radius_link);
    border_radius_e = Propriety({StyleClass("none", "")}, border_radius_link);
    border_radius_t = Propriety({StyleClass("none", "")}, border_radius_link);
    border_radius_r = Propriety({StyleClass("none", "")}, border_radius_link);
    border_radius_b = Propriety({StyleClass("none", "")}, border_radius_link);
    border_radius_l = Propriety({StyleClass("none", "")}, border_radius_link);
    border_radius_ss = Propriety({StyleClass("none", "")}, border_radius_link);
    border_radius_se = Propriety({StyleClass("none", "")}, border_radius_link);
    border_radius_ee = Propriety({StyleClass("none", "")}, border_radius_link);
    border_radius_es = Propriety({StyleClass("none", "")}, border_radius_link);
    border_radius_tl = Propriety({StyleClass("none", "")}, border_radius_link);
    border_radius_tr = Propriety({StyleClass("none", "")}, border_radius_link);
    border_radius_br = Propriety({StyleClass("none", "")}, border_radius_link);
    border_radius_bl = Propriety({StyleClass("none", "")}, border_radius_link);
    std::string className;
    std::string underscore = "-";
    for(auto size : sizes_radius) {
         
        if(size.compare("") == 0) underscore = "";
        else underscore = "-";

        className = "rounded" + std::string(underscore + size);
        border_radius.styleClasses_.push_back(StyleClass(className,  ""));
        className = "rounded-" + std::string("s" + underscore + size);
        border_radius_s.styleClasses_.push_back(StyleClass(className,  ""));
        className = "rounded-" + std::string("e" + underscore + size);
        border_radius_e.styleClasses_.push_back(StyleClass(className,  ""));
        className = "rounded-" + std::string("t" + underscore + size);
        border_radius_t.styleClasses_.push_back(StyleClass(className,  ""));
        className = "rounded-" + std::string("r" + underscore + size);
        border_radius_r.styleClasses_.push_back(StyleClass(className,  ""));
        className = "rounded-" + std::string("b" + underscore + size);
        border_radius_b.styleClasses_.push_back(StyleClass(className,  ""));
        className = "rounded-" + std::string("l" + underscore + size);
        border_radius_l.styleClasses_.push_back(StyleClass(className,  ""));
        className = "rounded-" + std::string("ss" + underscore + size);
        border_radius_ss.styleClasses_.push_back(StyleClass(className,  ""));
        className = "rounded-" + std::string("se" + underscore + size);
        border_radius_se.styleClasses_.push_back(StyleClass(className,  ""));
        className = "rounded-" + std::string("ee" + underscore + size);
        border_radius_ee.styleClasses_.push_back(StyleClass(className,  ""));
        className = "rounded-" + std::string("es" + underscore + size);
        border_radius_es.styleClasses_.push_back(StyleClass(className,  ""));
        className = "rounded-" + std::string("tl" + underscore + size);
        border_radius_tl.styleClasses_.push_back(StyleClass(className,  ""));
        className = "rounded-" + std::string("tr" + underscore + size);
        border_radius_tr.styleClasses_.push_back(StyleClass(className,  ""));
        className = "rounded-" + std::string("br" + underscore + size);
        border_radius_br.styleClasses_.push_back(StyleClass(className,  ""));
        className = "rounded-" + std::string("bl" + underscore + size);
        border_radius_bl.styleClasses_.push_back(StyleClass(className,  ""));
    }
 
    std::vector<std::string> sizes_width = {"", "0", "2", "4", "8"};
    std::string border_width_link = "https://tailwindcss.com/docs/border-width";
    border_width = Propriety({StyleClass("none", "")}, border_width_link);
    border_width_x = Propriety({StyleClass("none", "")}, border_width_link);
    border_width_y = Propriety({StyleClass("none", "")}, border_width_link);
    border_width_t = Propriety({StyleClass("none", "")}, border_width_link);
    border_width_r = Propriety({StyleClass("none", "")}, border_width_link);
    border_width_b = Propriety({StyleClass("none", "")}, border_width_link);
    border_width_l = Propriety({StyleClass("none", "")}, border_width_link);
    border_width_s = Propriety({StyleClass("none", "")}, border_width_link);
    border_width_e = Propriety({StyleClass("none", "")}, border_width_link);
    for(auto size : sizes_width) {
        if(size.compare("") == 0) underscore = "";
        else underscore = "-";
        className = "border" + std::string(underscore + size);
        border_width.styleClasses_.push_back(StyleClass(className,  ""));
        className = "border-" + std::string("x" + underscore + size);
        border_width_x.styleClasses_.push_back(StyleClass(className,  ""));
        className = "border-" + std::string("y" + underscore + size);
        border_width_y.styleClasses_.push_back(StyleClass(className,  ""));
        className = "border-" + std::string("t" + underscore + size);
        border_width_t.styleClasses_.push_back(StyleClass(className,  ""));
        className = "border-" + std::string("r" + underscore + size);
        border_width_r.styleClasses_.push_back(StyleClass(className,  ""));
        className = "border-" + std::string("b" + underscore + size);
        border_width_b.styleClasses_.push_back(StyleClass(className,  ""));
        className = "border-" + std::string("l" + underscore + size);
        border_width_l.styleClasses_.push_back(StyleClass(className,  ""));
        className = "border-" + std::string("s" + underscore + size);
        border_width_s.styleClasses_.push_back(StyleClass(className,  ""));
        className = "border-" + std::string("e" + underscore + size);
        border_width_e.styleClasses_.push_back(StyleClass(className,  ""));
    }
    
    // border style
    border_style = Propriety({
        StyleClass("none", ""),
        StyleClass("border-solid", "border-style: solid;"),
        StyleClass("border-dashed", "border-style: dashed;"),
        StyleClass("border-dotted", "border-style: dotted;"),
        StyleClass("border-double", "border-style: double;"),
        StyleClass("border-hidden", "border-style: hidden;"),
        StyleClass("border-none", "border-style: none;")
    }, "https://tailwindcss.com/docs/border-style");

    // divide x y
    divide_x = Propriety({
        StyleClass("none", ""),
        StyleClass("divide-x-0", "border-right-width: 0px; border-left-width: 0px;"),
        StyleClass("divide-x-2", "border-right-width: 2px; border-left-width: 2px;"),
        StyleClass("divide-x-4", "border-right-width: 4px; border-left-width: 4px;"),
        StyleClass("divide-x-8", "border-right-width: 8px; border-left-width: 8px;"),
        StyleClass("divide-x", "border-right-width: 1px; border-left-width: 1px;")
    }, "https://tailwindcss.com/docs/divide-width");
    divide_y = Propriety({
        StyleClass("none", ""),
        StyleClass("divide-y-0", "border-top-width: 0px; border-bottom-width: 0px;"),
        StyleClass("divide-y-2", "border-top-width: 2px; border-bottom-width: 2px;"),
        StyleClass("divide-y-4", "border-top-width: 4px; border-bottom-width: 4px;"),
        StyleClass("divide-y-8", "border-top-width: 8px; border-bottom-width: 8px;"),
        StyleClass("divide-y", "border-top-width: 1px; border-bottom-width: 1px;")
    }, "https://tailwindcss.com/docs/divide-width");
    
    divide_x_reverse = Propriety({StyleClass("divide-x-reverse", "border-left-width: 0px; border-right-width: 0px;")}, "https://tailwindcss.com/docs/divide-width");
    divide_y_reverse = Propriety({StyleClass("divide-y-reverse", "border-bottom-width: 0px; border-top-width: 0px;")}, "https://tailwindcss.com/docs/divide-width");

    // divide style
    divide_style = Propriety({
        StyleClass("none", ""),
        StyleClass("divide-solid", "border-style: solid;"),
        StyleClass("divide-dashed", "border-style: dashed;"),
        StyleClass("divide-dotted", "border-style: dotted;"),
        StyleClass("divide-double", "border-style: double;"),
        StyleClass("divide-none", "border-style: none;")
    }, "https://tailwindcss.com/docs/divide-style");

    // outline width
    outline_width = Propriety({
        StyleClass("none", ""),
        StyleClass("outline-0", "outline-width: 0px;"),
        StyleClass("outline-1", "outline-width: 1px;"),
        StyleClass("outline-2", "outline-width: 2px;"),
        StyleClass("outline-4", "outline-width: 4px;"),
        StyleClass("outline-8", "outline-width: 8px;")
    }, "https://tailwindcss.com/docs/outline-style");

    // outline style

    outline_style = Propriety({
        StyleClass("none", ""),
        StyleClass("outline-none", "outline: 2px solid transparent; outline-offset: 2px;"),
        StyleClass("outline-dotted", "outline-style: dotted;"),
        StyleClass("outline-dashed", "outline-style: dashed;"),
        StyleClass("outline-double", "outline-style: double;"),
        StyleClass("outline", "outline-style: solid;")
    }, "https://tailwindcss.com/docs/outline-style");

    // outline offset
    outline_offset = Propriety({
        StyleClass("none", ""),
        StyleClass("outline-offset-0", "outline-offset: 0px;"),
        StyleClass("outline-offset-1", "outline-offset: 1px;"),
        StyleClass("outline-offset-2", "outline-offset: 2px;"),
        StyleClass("outline-offset-4", "outline-offset: 4px;"),
        StyleClass("outline-offset-8", "outline-offset: 8px;")
    }, "https://tailwindcss.com/docs/outline-offset");

    // ring width
    ring_width = Propriety({
        StyleClass("none", ""),
        StyleClass("ring-0", "box-shadow: none;"),
        StyleClass("ring-1", "box-shadow: 0 0 0 1px;"),
        StyleClass("ring-2", "box-shadow: 0 0 0 2px;"),
        StyleClass("ring-4", "box-shadow: 0 0 0 4px;"),
        StyleClass("ring-8", "box-shadow: 0 0 0 8px;"),
        StyleClass("ring-inset", "box-shadow: inset 0 0 0 1px;"),
        StyleClass("ring", "box-shadow: 0 0 0 3px;")
    }, "https://tailwindcss.com/docs/ring-width");

    // ring offset width
    ring_offset_width = Propriety({
        StyleClass("none", ""),
        StyleClass("ring-offset-0", "box-shadow: none;"),
        StyleClass("ring-offset-1", "box-shadow: 0 0 0 1px;"),
        StyleClass("ring-offset-2", "box-shadow: 0 0 0 2px;"),
        StyleClass("ring-offset-4", "box-shadow: 0 0 0 4px;"),
        StyleClass("ring-offset-8", "box-shadow: 0 0 0 8px;")
    }, "https://tailwindcss.com/docs/ring-offset-width");

}


std::string Borders::borderRadiusData()
{
    std::string data = "";
    for(auto border_radius : border_radius.styleClasses_) { data += border_radius.className_ + " "; }
    data += "\n";
    for(auto border_radius : border_radius_s.styleClasses_) { data += border_radius.className_ + " "; }
    data += "\n";
    for(auto border_radius : border_radius_e.styleClasses_) { data += border_radius.className_ + " "; }
    data += "\n";
    for(auto border_radius : border_radius_t.styleClasses_) { data += border_radius.className_ + " "; }
    data += "\n";
    for(auto border_radius : border_radius_r.styleClasses_) { data += border_radius.className_ + " "; }
    data += "\n";
    for(auto border_radius : border_radius_b.styleClasses_) { data += border_radius.className_ + " "; }
    data += "\n";
    for(auto border_radius : border_radius_l.styleClasses_) { data += border_radius.className_ + " "; }
    data += "\n";
    for(auto border_radius : border_radius_ss.styleClasses_) { data += border_radius.className_ + " "; }
    data += "\n";
    for(auto border_radius : border_radius_se.styleClasses_) { data += border_radius.className_ + " "; }
    data += "\n";
    for(auto border_radius : border_radius_ee.styleClasses_) { data += border_radius.className_ + " "; }
    data += "\n";
    for(auto border_radius : border_radius_es.styleClasses_) { data += border_radius.className_ + " "; }
    data += "\n";
    for(auto border_radius : border_radius_tl.styleClasses_) { data += border_radius.className_ + " "; }
    data += "\n";
    for(auto border_radius : border_radius_tr.styleClasses_) { data += border_radius.className_ + " "; }
    data += "\n";
    for(auto border_radius : border_radius_br.styleClasses_) { data += border_radius.className_ + " "; }
    data += "\n";
    for(auto border_radius : border_radius_bl.styleClasses_) { data += border_radius.className_ + " "; }
    data += "\n";
    return data;
}

std::string Borders::borderWidthData()
{
    std::string data = "";
    for(auto border_width : border_width.styleClasses_) { data += border_width.className_ + " "; }
    data += "\n";
    for(auto border_width : border_width_x.styleClasses_) { data += border_width.className_ + " "; }
    data += "\n";
    for(auto border_width : border_width_y.styleClasses_) { data += border_width.className_ + " "; }
    data += "\n";
    for(auto border_width : border_width_t.styleClasses_) { data += border_width.className_ + " "; }
    data += "\n";
    for(auto border_width : border_width_r.styleClasses_) { data += border_width.className_ + " "; }
    data += "\n";
    for(auto border_width : border_width_b.styleClasses_) { data += border_width.className_ + " "; }
    data += "\n";
    for(auto border_width : border_width_l.styleClasses_) { data += border_width.className_ + " "; }
    data += "\n";
    for(auto border_width : border_width_s.styleClasses_) { data += border_width.className_ + " "; }
    data += "\n";
    for(auto border_width : border_width_e.styleClasses_) { data += border_width.className_ + " "; }
    data += "\n";
    return data;
}

std::string Borders::borderStyleData()
{
    std::string data = "";
    for(auto border_style : border_style.styleClasses_) { data += border_style.className_ + " "; }
    data += "\n";
    return data;
}

std::string Borders::divideData()
{
    std::string data = "";
    for(auto divide_x : divide_x.styleClasses_) { data += divide_x.className_ + " "; }
    data += "\n";
    for(auto divide_y : divide_y.styleClasses_) { data += divide_y.className_ + " "; }
    data += "\n";
    for(auto divide_x_reverse : divide_x_reverse.styleClasses_) { data += divide_x_reverse.className_ + " "; }
    data += "\n";
    for(auto divide_y_reverse : divide_y_reverse.styleClasses_) { data += divide_y_reverse.className_ + " "; }
    data += "\n";
    for(auto divide_style : divide_style.styleClasses_) { data += divide_style.className_ + " "; }
    data += "\n";
    return data;
}

std::string Borders::outlineData()
{
    std::string data = "";
    for(auto outline_style : outline_style.styleClasses_) { data += outline_style.className_ + " "; }
    data += "\n";
    for(auto outline_width : outline_width.styleClasses_) { data += outline_width.className_ + " "; }
    data += "\n";
    for(auto outline_offset : outline_offset.styleClasses_) { data += outline_offset.className_ + " "; }
    data += "\n";
    return data;
}

std::string Borders::ringData()
{
    std::string data = "";
    for(auto ring_width : ring_width.styleClasses_) { data += ring_width.className_ + " "; }
    data += "\n";
    for(auto ring_offset_width : ring_offset_width.styleClasses_) { data += ring_offset_width.className_ + " "; }
    data += "\n";
    return data;
}