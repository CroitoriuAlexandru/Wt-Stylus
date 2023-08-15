#include "include/Layout.h"

using namespace Tailwind;


Layout::Layout(std::vector<std::string> spacingScale)
{
    // Aspect Ratio
    aspect_ratio = Propriety({
    StyleClass("aspect-auto", "aspect-ratio: auto;"),
    StyleClass("aspect-square", "aspect-ratio: 1 / 1;"),
    StyleClass("aspect-video", "aspect-ratio: 16 / 9;")
    }, "https://tailwindcss.com/docs/aspect-ratio");

    // Container
    container = Propriety({StyleClass("container", "None, sm (640px), md (768px), lg (1024px), xl (1280px), 2xl (1536px)")}, "https://tailwindcss.com/docs/container");

    // Columns
    columns_variants = {"auto", "3xs", "2xs", "xs", "sm", "md", "lg", "xl", "2xl", "3xl", "4xl", "5xl", "6xl", "7xl", "12", "11", "10", "9", "8", "7", "6", "5", "4", "3", "2", "1"};
    columns = Propriety({}, "https://tailwindcss.com/docs/columns");
    for(auto col_variant : columns_variants) {
        columns.styleClasses_.push_back(StyleClass("columns-" + col_variant, ""));
    }

    // Break After
    break_before_after_variants = {"avoid-page", "auto", "avoid", "all", "page", "left", "right", "column"};
    break_after = Propriety({}, "https://tailwindcss.com/docs/break-after");
    for(auto break_variant : break_before_after_variants) {
        break_after.styleClasses_.push_back(StyleClass("break-after-" + break_variant, "break-before: " + break_variant + ";"));
    }

    // Break Before
    break_before = Propriety({}, "https://tailwindcss.com/docs/break-before");
    for(auto break_variant : break_before_after_variants) {
        break_before.styleClasses_.push_back(StyleClass("break-before-" + break_variant, "break-before: " + break_variant + ";"));
    }

    // Break Inside
    break_inside_variants = {"avoid-page", "avoid-column", "auto", "avoid"};
    break_inside = Propriety({}, "https://tailwindcss.com/docs/break-inside");
    for(auto break_variant : break_inside_variants) {
        break_inside.styleClasses_.push_back(StyleClass("break-inside-" + break_variant, "break-inside: " + break_variant + ";"));
    }

    // Box Decoration Break
    box_decoration_break = Propriety({
        StyleClass("box-decoration-clone", "box-decoration-break: clone;"),
        StyleClass("box-decoration-slice", "box-decoration-break: slice;")
    }, "https://tailwindcss.com/docs/box-decoration-break");

    // Box Sizing
    box_sizing = Propriety({
        StyleClass("box-border", "box-sizing: border-box;"),
        StyleClass("box-content", "box-sizing: content-box;")
    }, "https://tailwindcss.com/docs/box-sizing");

    // Display
    display_variants = {"inline-block", "inline-flex", "inline-grid", "inline-table", "inline", "table-caption", "table-cell", "table-column", "table-column-group", "table-footer-group", "table-header-group", "table-row-group", "table-row", "flow-root", "list-item", "block", "flex", "table", "grid", "contents", "hidden"};
    for(auto variant : display_variants) {
        if(variant.compare("none") == 0)
            display.styleClasses_.push_back(StyleClass(variant, "display: none;"));
        else 
            display.styleClasses_.push_back(StyleClass(variant, "display: " + variant + ";"));

    }

    // Floats
    floats = Propriety({
        StyleClass("float-none", "float: none;"),
        StyleClass("float-right", "float: right;"),
        StyleClass("float-left", "float: left;")
    }, "https://tailwindcss.com/docs/float");

    // Clear
    clear = Propriety({
        StyleClass("clear-none", "clear: none;"),
        StyleClass("clear-right", "clear: right;"),
        StyleClass("clear-left", "clear: left;"),
        StyleClass("clear-both", "clear: both;")
    }, "https://tailwindcss.com/docs/clear");

    // Isolation
    isolation = Propriety({
        StyleClass("isolate", "isolation: isolate;"),
        StyleClass("isolation-auto", "isolation: auto;")
    }, "https://tailwindcss.com/docs/isolation");
    
    // Object Fit
    object_fit = Propriety({
        StyleClass("object-contain", "object-fit: contain;"),
        StyleClass("object-cover", "object-fit: cover;"),
        StyleClass("object-fill", "object-fit: fill;"),
        StyleClass("object-none", "object-fit: none;"),
        StyleClass("object-scale-down", "object-fit: scale-down;")
    }, "https://tailwindcss.com/docs/object-fit");

    // Object Position
    object_position = Propriety({
        StyleClass("object-left-top", "object-position: left top;"),
        StyleClass("object-right-top", "object-position: right top;"),
        StyleClass("object-left-bottom", "object-position: left bottom;"),
        StyleClass("object-right-bottom", "object-position: right bottom;"),
        StyleClass("object-top", "object-position: top;"),
        StyleClass("object-right", "object-position: right;"),
        StyleClass("object-bottom", "object-position: bottom;"),
        StyleClass("object-left", "object-position: left;"),
        StyleClass("object-center", "object-position: center;")
    }, "https://tailwindcss.com/docs/object-position");

    // Overflow
    overflow_variants = {"auto", "hidden", "clip", "scroll", "visible"};
    overflow = Propriety({}, "https://tailwindcss.com/docs/overflow");
    overflow_x = Propriety({}, "https://tailwindcss.com/docs/overflow");
    overflow_y = Propriety({}, "https://tailwindcss.com/docs/overflow");

    for(auto variant : overflow_variants) {
        overflow.styleClasses_.push_back(StyleClass("overflow-" + variant, "overflow: " + variant + ";"));
        overflow_x.styleClasses_.push_back(StyleClass("overflow-x-" + variant, "overflow-x: " + variant + ";"));
        overflow_y.styleClasses_.push_back(StyleClass("overflow-y-" + variant, "overflow-y: " + variant + ";"));
    }

    // Overscroll Behavior
    overscroll_variants = {"auto", "contain", "none"};
    for(auto variant : overscroll_variants) {
        overscroll_behavior.styleClasses_.push_back(StyleClass("overscroll-" + variant, "overscroll-behavior: " + variant + ";"));
        overscroll_behavior_x.styleClasses_.push_back(StyleClass("overscroll-x-" + variant, "overscroll-behavior-x: " + variant + ";"));
        overscroll_behavior_y.styleClasses_.push_back(StyleClass("overscroll-y-" + variant, "overscroll-behavior-y: " + variant + ";"));
    }

    // Position
    position = Propriety({
        StyleClass("static", "position: static;"),
        StyleClass("fixed", "position: fixed;"),
        StyleClass("absolute", "position: absolute;"),
        StyleClass("relative", "position: relative;"),
        StyleClass("sticky", "position: sticky;")
    }, "https://tailwindcss.com/docs/position");

    // Position inset, inset_x, inset_y, start, end, top, right, bottom, left
    std::vector<std::string> position_side_extra_variants = {"full", "auto", "1/2", "1/3", "2/3", "1/4", "2/4", "3/4"};
    for(auto size : spacingScale) {
        position_inset.styleClasses_.push_back(StyleClass("inset-" + size, ""));
        position_inset_x.styleClasses_.push_back(StyleClass("inset-x-" + size, ""));
        position_inset_y.styleClasses_.push_back(StyleClass("inset-y-" + size, ""));
        position_start.styleClasses_.push_back(StyleClass("start-" + size, ""));
        position_end.styleClasses_.push_back(StyleClass("end-" + size, ""));
        position_top.styleClasses_.push_back(StyleClass("top-" + size, ""));
        position_right.styleClasses_.push_back(StyleClass("right-" + size, ""));
        position_bottom.styleClasses_.push_back(StyleClass("bottom-" + size, ""));
        position_left.styleClasses_.push_back(StyleClass("left-" + size, ""));
    }
    for(auto extra_variant : position_side_extra_variants) {
        position_inset.styleClasses_.push_back(StyleClass("inset-" + extra_variant, ""));
        position_inset_x.styleClasses_.push_back(StyleClass("inset-x-" + extra_variant, ""));
        position_inset_y.styleClasses_.push_back(StyleClass("inset-y-" + extra_variant, ""));
        position_start.styleClasses_.push_back(StyleClass("start-" + extra_variant, ""));
        position_end.styleClasses_.push_back(StyleClass("end-" + extra_variant, ""));
        position_top.styleClasses_.push_back(StyleClass("top-" + extra_variant, ""));
        position_right.styleClasses_.push_back(StyleClass("right-" + extra_variant, ""));
        position_bottom.styleClasses_.push_back(StyleClass("bottom-" + extra_variant, ""));
        position_left.styleClasses_.push_back(StyleClass("left-" + extra_variant, ""));
    }

    // Visibility
    visibility = Propriety({
        StyleClass("visible", "visibility: visible;"),
        StyleClass("invisible", "visibility: hidden;"),
        StyleClass("collapse", "visibility: collapse;")
    }, "https://tailwindcss.com/docs/visibility");

    // Z Index
    std::vector<std::string> z_index_variants = {"0", "10", "20", "30", "40", "50", "auto"};
    for(auto variant : z_index_variants) {
        z_index.styleClasses_.push_back(StyleClass("z-" + variant, "z-index: " + variant + ";"));
    }
};


std::string Layout::AspectRatioData() {
    std::string data = "Aspect Ratio ------------------------------------\n";
    for(auto styleClass : aspect_ratio.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Layout::ContainerData() {
    std::string data = "Container ------------------------------------\n";
    for(auto styleClass : container.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Layout::ColumnsData() {
    std::string data = "Columns ------------------------------------\n";
    for(auto styleClass : columns.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Layout::BreakAfterData() {
    std::string data = "Break After ------------------------------------\n";
    for(auto styleClass : break_after.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Layout::BreakBeforeData() {
    std::string data = "Break Before ------------------------------------\n";
    for(auto styleClass : break_before.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Layout::BreakInsideData() {
    std::string data = "Break Inside ------------------------------------\n";
    for(auto styleClass : break_inside.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Layout::BoxDecorationBreakData() {
    std::string data = "Box Decoration Break ------------------------------------\n";
    for(auto styleClass : box_decoration_break.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    return data;

}

std::string Layout::BoxSizingData() {
    std::string data = "Box Sizing ------------------------------------\n";
    for(auto styleClass : box_sizing.styleClasses_) {
        data += styleClass.className_ + " ";
    }

    return data;
}

std::string Layout::DisplayData() {
    std::string data = "Display ------------------------------------\n";
    for(auto styleClass : display.styleClasses_) {
        data += styleClass.className_ + " ";
    }

    return data;
}

std::string Layout::FloatsData() {
    std::string data = "Floats ------------------------------------\n";
    for(auto styleClass : floats.styleClasses_) {
        data += styleClass.className_ + " ";
    }

    return data;
}

std::string Layout::ClearData() {
    std::string data = "Clear ------------------------------------\n";
    for(auto styleClass : clear.styleClasses_) {
        data += styleClass.className_ + " ";
    }

    return data;
}

std::string Layout::IsolationData() {
    std::string data = "Isolation ------------------------------------\n";
    for(auto styleClass : isolation.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Layout::ObjectFitData() {
    std::string data = "Object Fit ------------------------------------\n";
    for(auto styleClass : object_fit.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Layout::ObjectPositionData() {
    std::string data = "Object Position ------------------------------------\n";
    for(auto styleClass : object_position.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Layout::OverflowData() {
    std::string data = "Overflow ------------------------------------\n";
    for(auto styleClass : overflow.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    data += "\n";
    for(auto styleClass : overflow_x.styleClasses_){
        data += styleClass.className_ + " ";
    }
    data += "\n";
    for(auto styleClass : overflow_y.styleClasses_){
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Layout::OverscrollBehaviorData() {
    std::string data = "Overscroll Behavior ------------------------------------\n";
    for(auto styleClass : overscroll_behavior.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    data += "\n";
    for(auto styleClass : overscroll_behavior_x.styleClasses_){
        data += styleClass.className_ + " ";
    }
    data += "\n";
    for(auto styleClass : overscroll_behavior_y.styleClasses_){
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Layout::PositionData() {
    std::string data = "Position ------------------------------------\n";
    for(auto styleClass : position.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Layout::PositionSidesData(){
    std::string data = "Position Sides ------------------------------------\n";
    for(auto styleClass : position_inset.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    data += "\n";
    for(auto styleClass : position_inset_x.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    data += "\n";
    for(auto styleClass : position_inset_y.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    data += "\n";
    for(auto styleClass : position_start.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    data += "\n";
    for(auto styleClass : position_end.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    data += "\n";
    for(auto styleClass : position_top.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    data += "\n";
    for(auto styleClass : position_right.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    data += "\n";
    for(auto styleClass : position_bottom.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    data += "\n";
    for(auto styleClass : position_left.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Layout::VisibilityData() {
    std::string data = "Visibility ------------------------------------\n";
    for(auto styleClass : visibility.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Layout::ZIndexData() {
    std::string data = "Z Index ------------------------------------\n";
    for(auto styleClass : z_index.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    return data;
}

