#include "include/Borders.h"
#include <Wt/WString.h>

using namespace Tailwind;

Borders::Borders()
{
    
    std::vector<std::string> sizes_radius = {"none", "", "sm", "md", "lg", "xl", "2xl", "3xl", "full"};
    std::string border_radius_link = "https://tailwindcss.com/docs/border-radius";
    border_radius = Propriety({}, border_radius_link);
    border_radius_s = Propriety({}, border_radius_link);
    border_radius_e = Propriety({}, border_radius_link);
    border_radius_t = Propriety({}, border_radius_link);
    border_radius_r = Propriety({}, border_radius_link);
    border_radius_b = Propriety({}, border_radius_link);
    border_radius_l = Propriety({}, border_radius_link);
    border_radius_ss = Propriety({}, border_radius_link);
    border_radius_se = Propriety({}, border_radius_link);
    border_radius_ee = Propriety({}, border_radius_link);
    border_radius_es = Propriety({}, border_radius_link);
    border_radius_tl = Propriety({}, border_radius_link);
    border_radius_tr = Propriety({}, border_radius_link);
    border_radius_br = Propriety({}, border_radius_link);
    border_radius_bl = Propriety({}, border_radius_link);
    Wt::WString className;
    Wt::WString underscore = "-";
    for(auto size : sizes_radius) {
        
        if(size.compare("") == 0) underscore = "";
        else underscore = "-";

        className = "rounded" + Wt::WString(underscore + size);
        border_radius.styleClasses_.push_back(StyleClass(className.toUTF8(),  ""));
        className = "rounded-" + Wt::WString("s" + underscore + size);
        border_radius_s.styleClasses_.push_back(StyleClass(className.toUTF8(),  ""));
        className = "rounded-" + Wt::WString("e" + underscore + size);
        border_radius_e.styleClasses_.push_back(StyleClass(className.toUTF8(),  ""));
        className = "rounded-" + Wt::WString("t" + underscore + size);
        border_radius_t.styleClasses_.push_back(StyleClass(className.toUTF8(),  ""));
        className = "rounded-" + Wt::WString("r" + underscore + size);
        border_radius_r.styleClasses_.push_back(StyleClass(className.toUTF8(),  ""));
        className = "rounded-" + Wt::WString("b" + underscore + size);
        border_radius_b.styleClasses_.push_back(StyleClass(className.toUTF8(),  ""));
        className = "rounded-" + Wt::WString("l" + underscore + size);
        border_radius_l.styleClasses_.push_back(StyleClass(className.toUTF8(),  ""));
        className = "rounded-" + Wt::WString("ss" + underscore + size);
        border_radius_ss.styleClasses_.push_back(StyleClass(className.toUTF8(),  ""));
        className = "rounded-" + Wt::WString("se" + underscore + size);
        border_radius_se.styleClasses_.push_back(StyleClass(className.toUTF8(),  ""));
        className = "rounded-" + Wt::WString("ee" + underscore + size);
        border_radius_ee.styleClasses_.push_back(StyleClass(className.toUTF8(),  ""));
        className = "rounded-" + Wt::WString("es" + underscore + size);
        border_radius_es.styleClasses_.push_back(StyleClass(className.toUTF8(),  ""));
        className = "rounded-" + Wt::WString("tl" + underscore + size);
        border_radius_tl.styleClasses_.push_back(StyleClass(className.toUTF8(),  ""));
        className = "rounded-" + Wt::WString("tr" + underscore + size);
        border_radius_tr.styleClasses_.push_back(StyleClass(className.toUTF8(),  ""));
        className = "rounded-" + Wt::WString("br" + underscore + size);
        border_radius_br.styleClasses_.push_back(StyleClass(className.toUTF8(),  ""));
        className = "rounded-" + Wt::WString("bl" + underscore + size);
        border_radius_bl.styleClasses_.push_back(StyleClass(className.toUTF8(),  ""));
    }

    std::vector<std::string> sizes_width = {"", "0", "2", "4", "8"};
    std::string border_width_link = "https://tailwindcss.com/docs/border-width";
    border_width = Propriety({}, border_width_link);
    border_width_x = Propriety({}, border_width_link);
    border_width_y = Propriety({}, border_width_link);
    border_width_t = Propriety({}, border_width_link);
    border_width_r = Propriety({}, border_width_link);
    border_width_b = Propriety({}, border_width_link);
    border_width_l = Propriety({}, border_width_link);
    border_width_s = Propriety({}, border_width_link);
    border_width_e = Propriety({}, border_width_link);
    for(auto size : sizes_width) {
        if(size.compare("") == 0) underscore = "";
        else underscore = "-";
        className = "border" + Wt::WString(underscore + size);
        border_width.styleClasses_.push_back(StyleClass(className.toUTF8(),  ""));
        className = "border-" + Wt::WString("x" + underscore + size);
        border_width_x.styleClasses_.push_back(StyleClass(className.toUTF8(),  ""));
        className = "border-" + Wt::WString("y" + underscore + size);
        border_width_y.styleClasses_.push_back(StyleClass(className.toUTF8(),  ""));
        className = "border-" + Wt::WString("t" + underscore + size);
        border_width_t.styleClasses_.push_back(StyleClass(className.toUTF8(),  ""));
        className = "border-" + Wt::WString("r" + underscore + size);
        border_width_r.styleClasses_.push_back(StyleClass(className.toUTF8(),  ""));
        className = "border-" + Wt::WString("b" + underscore + size);
        border_width_b.styleClasses_.push_back(StyleClass(className.toUTF8(),  ""));
        className = "border-" + Wt::WString("l" + underscore + size);
        border_width_l.styleClasses_.push_back(StyleClass(className.toUTF8(),  ""));
        className = "border-" + Wt::WString("s" + underscore + size);
        border_width_s.styleClasses_.push_back(StyleClass(className.toUTF8(),  ""));
        className = "border-" + Wt::WString("e" + underscore + size);
        border_width_e.styleClasses_.push_back(StyleClass(className.toUTF8(),  ""));
    }
    
    // border style
    border_style = Propriety({
        StyleClass("border-solid", "border-style: solid;"),
        StyleClass("border-dashed", "border-style: dashed;"),
        StyleClass("border-dotted", "border-style: dotted;"),
        StyleClass("border-double", "border-style: double;"),
        StyleClass("border-hidden", "border-style: hidden;"),
        StyleClass("border-none", "border-style: none;")
    }, "https://tailwindcss.com/docs/border-style");

    // divide x y
    divide_x = Propriety({
        StyleClass("divide-x-0", "border-right-width: 0px; border-left-width: 0px;"),
        StyleClass("divide-x-2", "border-right-width: 2px; border-left-width: 2px;"),
        StyleClass("divide-x-4", "border-right-width: 4px; border-left-width: 4px;"),
        StyleClass("divide-x-8", "border-right-width: 8px; border-left-width: 8px;"),
        StyleClass("divide-x", "border-right-width: 1px; border-left-width: 1px;")
    }, "https://tailwindcss.com/docs/divide-width");
    divide_y = Propriety({
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
        StyleClass("divide-solid", "border-style: solid;"),
        StyleClass("divide-dashed", "border-style: dashed;"),
        StyleClass("divide-dotted", "border-style: dotted;"),
        StyleClass("divide-double", "border-style: double;"),
        StyleClass("divide-none", "border-style: none;")
    }, "https://tailwindcss.com/docs/divide-style");

    // outline width
    outline_width = Propriety({
        StyleClass("outline-0", "outline-width: 0px;"),
        StyleClass("outline-1", "outline-width: 1px;"),
        StyleClass("outline-2", "outline-width: 2px;"),
        StyleClass("outline-4", "outline-width: 4px;"),
        StyleClass("outline-8", "outline-width: 8px;")
    }, "https://tailwindcss.com/docs/outline-style");

    // outline style

    outline_style = Propriety({
        StyleClass("outline-none", "outline: 2px solid transparent; outline-offset: 2px;"),
        StyleClass("outline-dotted", "outline-style: dotted;"),
        StyleClass("outline-dashed", "outline-style: dashed;"),
        StyleClass("outline-double", "outline-style: double;"),
        StyleClass("outline", "outline-style: solid;")
    }, "https://tailwindcss.com/docs/outline-style");

    // outline offset
    outline_offset = Propriety({
        StyleClass("outline-offset-0", "outline-offset: 0px;"),
        StyleClass("outline-offset-1", "outline-offset: 1px;"),
        StyleClass("outline-offset-2", "outline-offset: 2px;"),
        StyleClass("outline-offset-4", "outline-offset: 4px;"),
        StyleClass("outline-offset-8", "outline-offset: 8px;")
    }, "https://tailwindcss.com/docs/outline-offset");

    // ring width
    ring_width = Propriety({
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
        StyleClass("ring-offset-0", "box-shadow: none;"),
        StyleClass("ring-offset-1", "box-shadow: 0 0 0 1px;"),
        StyleClass("ring-offset-2", "box-shadow: 0 0 0 2px;"),
        StyleClass("ring-offset-4", "box-shadow: 0 0 0 4px;"),
        StyleClass("ring-offset-8", "box-shadow: 0 0 0 8px;")
    }, "https://tailwindcss.com/docs/ring-offset-width");

}


std::string Borders::BorderRadiusData()
{
    std::string data = "Border Radius ------------------------------------\n";
    data += "\nRadius ---------\n";
    for(auto border_radius : border_radius.styleClasses_) { data += border_radius.className_ + " "; }
    data += "\nRadius s ---------\n";
    for(auto border_radius : border_radius_s.styleClasses_) { data += border_radius.className_ + " "; }
    data += "\nRadius e ---------\n";
    for(auto border_radius : border_radius_e.styleClasses_) { data += border_radius.className_ + " "; }
    data += "\nRadius t ---------\n";
    for(auto border_radius : border_radius_t.styleClasses_) { data += border_radius.className_ + " "; }
    data += "\nRadius r ---------\n";
    for(auto border_radius : border_radius_r.styleClasses_) { data += border_radius.className_ + " "; }
    data += "\nRadius b ---------\n";
    for(auto border_radius : border_radius_b.styleClasses_) { data += border_radius.className_ + " "; }
    data += "\nRadius l ---------\n";
    for(auto border_radius : border_radius_l.styleClasses_) { data += border_radius.className_ + " "; }
    data += "\nRadius ss ---------\n";
    for(auto border_radius : border_radius_ss.styleClasses_) { data += border_radius.className_ + " "; }
    data += "\nRadius se ---------\n";
    for(auto border_radius : border_radius_se.styleClasses_) { data += border_radius.className_ + " "; }
    data += "\nRadius ee ---------\n";
    for(auto border_radius : border_radius_ee.styleClasses_) { data += border_radius.className_ + " "; }
    data += "\nRadius es ---------\n";
    for(auto border_radius : border_radius_es.styleClasses_) { data += border_radius.className_ + " "; }
    data += "\nRadius tl ---------\n";
    for(auto border_radius : border_radius_tl.styleClasses_) { data += border_radius.className_ + " "; }
    data += "\nRadius tr ---------\n";
    for(auto border_radius : border_radius_tr.styleClasses_) { data += border_radius.className_ + " "; }
    data += "\nRadius br ---------\n";
    for(auto border_radius : border_radius_br.styleClasses_) { data += border_radius.className_ + " "; }
    data += "\nRadius bl ---------\n";
    for(auto border_radius : border_radius_bl.styleClasses_) { data += border_radius.className_ + " "; }
    return data;
}

std::string Borders::BorderWidthData()
{
    std::string data = "Border Width ------------------------------------\n";
    data += "Width ---------\n";
    for(auto border_width : border_width.styleClasses_) { data += border_width.className_ + " "; }
    data += "\nWidth x ---------\n";
    for(auto border_width : border_width_x.styleClasses_) { data += border_width.className_ + " "; }
    data += "\nWidth y ---------\n";
    for(auto border_width : border_width_y.styleClasses_) { data += border_width.className_ + " "; }
    data += "\nWidth t ---------\n";
    for(auto border_width : border_width_t.styleClasses_) { data += border_width.className_ + " "; }
    data += "\nWidth r ---------\n";
    for(auto border_width : border_width_r.styleClasses_) { data += border_width.className_ + " "; }
    data += "\nWidth b ---------\n";
    for(auto border_width : border_width_b.styleClasses_) { data += border_width.className_ + " "; }
    data += "\nWidth l ---------\n";
    for(auto border_width : border_width_l.styleClasses_) { data += border_width.className_ + " "; }
    data += "\nWidth s ---------\n";
    for(auto border_width : border_width_s.styleClasses_) { data += border_width.className_ + " "; }
    data += "\nWidth e ---------\n";
    for(auto border_width : border_width_e.styleClasses_) { data += border_width.className_ + " "; }
    return data;
}

std::string Borders::BorderStyleData()
{
    std::string data = "Border Style ------------------------------------\n";
    for(auto border_style : border_style.styleClasses_) { data += border_style.className_ + " "; }
    return data;
}

std::string Borders::DivideData()
{
    std::string data = "Border Divide ------------------------------------\n";
    data += "\nDivide x ---------\n";
    for(auto divide_x : divide_x.styleClasses_) { data += divide_x.className_ + " "; }
    data += "\nDivide y ---------\n";
    for(auto divide_y : divide_y.styleClasses_) { data += divide_y.className_ + " "; }
    data += "\nDivide x reverse ---------\n";
    for(auto divide_x_reverse : divide_x_reverse.styleClasses_) { data += divide_x_reverse.className_ + " "; }
    data += "\nDivide y reverse ---------\n";
    for(auto divide_y_reverse : divide_y_reverse.styleClasses_) { data += divide_y_reverse.className_ + " "; }
    data += "\nDivide style ---------\n";
    for(auto divide_style : divide_style.styleClasses_) { data += divide_style.className_ + " "; }
    return data;
}

std::string Borders::OutlineData()
{
    std::string data = "Border Outline ------------------------------------\n";
    data += "\nOutline style ---------\n";
    for(auto outline_style : outline_style.styleClasses_) { data += outline_style.className_ + " "; }
    data += "\nOutline width ---------\n";
    for(auto outline_width : outline_width.styleClasses_) { data += outline_width.className_ + " "; }
    data += "\nOutline offset ---------\n";
    for(auto outline_offset : outline_offset.styleClasses_) { data += outline_offset.className_ + " "; }
    return data;
}

std::string Borders::RingData()
{
    std::string data = "Border Ring ------------------------------------\n";
    data += "\nRing width ---------\n";
    for(auto ring_width : ring_width.styleClasses_) { data += ring_width.className_ + " "; }
    data += "\nRing offset width ---------\n";
    for(auto ring_offset_width : ring_offset_width.styleClasses_) { data += ring_offset_width.className_ + " "; }

    return data;
}