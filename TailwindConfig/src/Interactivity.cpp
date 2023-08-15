#include "include/Interactivity.h"

using namespace Tailwind;

Interactivity::Interactivity(
 std::vector<StyleClass> margin,
 std::vector<StyleClass> margin_x,
 std::vector<StyleClass> margin_y,
 std::vector<StyleClass> margin_top,
 std::vector<StyleClass> margin_right,
 std::vector<StyleClass> margin_bottom,
 std::vector<StyleClass> margin_left,
 std::vector<StyleClass> margin_start,
 std::vector<StyleClass> margin_end,
 std::vector<StyleClass> padding,
 std::vector<StyleClass> padding_x,
 std::vector<StyleClass> padding_y,
 std::vector<StyleClass> padding_top,
 std::vector<StyleClass> padding_right,
 std::vector<StyleClass> padding_botto,
 std::vector<StyleClass> padding_left ,
 std::vector<StyleClass> padding_start,
 std::vector<StyleClass> padding_end
)
{
    // Appearance
    appearance = Propriety({
        StyleClass("appearance-none", "appearance: none;"),
    }, "https://tailwindcss.com/docs/appearance");

    // Cursor
    cursor = Propriety({
        StyleClass("cursor-auto", "cursor: auto;"),
        StyleClass("cursor-default", "cursor: default;"),
        StyleClass("cursor-pointer", "cursor: pointer;"),
        StyleClass("cursor-wait", "cursor: wait;"),
        StyleClass("cursor-text", "cursor: text;"),
        StyleClass("cursor-move", "cursor: move;"),
        StyleClass("cursor-help", "cursor: help;"),
        StyleClass("cursor-not-allowed", "cursor: not-allowed;"),
        StyleClass("cursor-none", "cursor: none;"),
        StyleClass("cursor-progress", "cursor: progress;"),
        StyleClass("cursor-cell", "cursor: cell;"),
        StyleClass("cursor-crosshair", "cursor: crosshair;"),
        StyleClass("cursor-vertical-text", "cursor: vertical-text;"),
        StyleClass("cursor-alias", "cursor: alias;"),
        StyleClass("cursor-copy", "cursor: copy;"),
        StyleClass("cursor-no-drop", "cursor: no-drop;"),
        StyleClass("cursor-all-scroll", "cursor: all-scroll;"),
        StyleClass("cursor-col-resize", "cursor: col-resize;"),
        StyleClass("cursor-row-resize", "cursor: row-resize;"),
        StyleClass("cursor-n-resize", "cursor: n-resize;"),
        StyleClass("cursor-e-resize", "cursor: e-resize;"),
        StyleClass("cursor-s-resize", "cursor: s-resize;"),
        StyleClass("cursor-w-resize", "cursor: w-resize;"),
        StyleClass("cursor-ne-resize", "cursor: ne-resize;"),
        StyleClass("cursor-nw-resize", "cursor: nw-resize;"),
        StyleClass("cursor-se-resize", "cursor: se-resize;"),
        StyleClass("cursor-sw-resize", "cursor: sw-resize;"),
        StyleClass("cursor-ew-resize", "cursor: ew-resize;"),
        StyleClass("cursor-ns-resize", "cursor: ns-resize;"),
        StyleClass("cursor-nesw-resize", "cursor: nesw-resize;"),
        StyleClass("cursor-nwse-resize", "cursor: nwse-resize;"),
        StyleClass("cursor-zoom-in", "cursor: zoom-in;"),
    }, "https://tailwindcss.com/docs/cursor");

    // Pointer Events
    pointer_events = Propriety({
        StyleClass("pointer-events-none", "pointer-events: none;"),
        StyleClass("pointer-events-auto", "pointer-events: auto;"),
    }, "https://tailwindcss.com/docs/pointer-events");

    // Resize 
    resize = Propriety({
        StyleClass("resize-none", "resize: none;"),
        StyleClass("resize-y", "resize: vertical;"),
        StyleClass("resize-x", "resize: horizontal;"),
        StyleClass("resize", "resize: both;"),
    }, "https://tailwindcss.com/docs/resize");

    // Scroll Behavior
    scroll_behavior = Propriety({
        StyleClass("scroll-auto", "scroll-behavior: auto;"),
        StyleClass("scroll-smooth", "scroll-behavior: smooth;"),
    }, "https://tailwindcss.com/docs/scroll-behavior");

    // Scroll Margin
    scroll_margin = Propriety({}, "https://tailwindcss.com/docs/scroll-margin");
    for(auto variant : margin) scroll_margin.styleClasses_.push_back(StyleClass("scroll-" + variant.className_, "scroll-" + variant.propriety_));
    scroll_margin_x = Propriety({}, "https://tailwindcss.com/docs/scroll-margin");
    for(auto variant : margin_x) scroll_margin_x.styleClasses_.push_back(StyleClass("scroll-" + variant.className_, "scroll-" + variant.propriety_));
    scroll_margin_y = Propriety({}, "https://tailwindcss.com/docs/scroll-margin");
    for(auto variant : margin_y) scroll_margin_y.styleClasses_.push_back(StyleClass("scroll-" + variant.className_, "scroll-" + variant.propriety_));
    scroll_margin_top = Propriety({}, "https://tailwindcss.com/docs/scroll-margin");
    for(auto variant : margin_top) scroll_margin_top.styleClasses_.push_back(StyleClass("scroll-" + variant.className_, "scroll-" + variant.propriety_));
    scroll_margin_right = Propriety({}, "https://tailwindcss.com/docs/scroll-margin");
    for(auto variant : margin_right) scroll_margin_right.styleClasses_.push_back(StyleClass("scroll-" + variant.className_, "scroll-" + variant.propriety_));
    scroll_margin_bottom = Propriety({}, "https://tailwindcss.com/docs/scroll-margin");
    for(auto variant : margin_bottom) scroll_margin_bottom.styleClasses_.push_back(StyleClass("scroll-" + variant.className_, "scroll-" + variant.propriety_));
    scroll_margin_left = Propriety({}, "https://tailwindcss.com/docs/scroll-margin");
    for(auto variant : margin_left) scroll_margin_left.styleClasses_.push_back(StyleClass("scroll-" + variant.className_, "scroll-" + variant.propriety_));
    scroll_margin_start = Propriety({}, "https://tailwindcss.com/docs/scroll-margin");
    for(auto variant : margin_start) scroll_margin_start.styleClasses_.push_back(StyleClass("scroll-" + variant.className_, "scroll-" + variant.propriety_));
    scroll_margin_end = Propriety({}, "https://tailwindcss.com/docs/scroll-margin");
    for(auto variant : margin_end) scroll_margin_end.styleClasses_.push_back(StyleClass("scroll-" + variant.className_, "scroll-" + variant.propriety_));

    // Scroll Padding
    scroll_padding = Propriety({}, "https://tailwindcss.com/docs/scroll-padding");
    for(auto variant : padding) scroll_padding.styleClasses_.push_back(StyleClass("scroll-" + variant.className_, "scroll-" + variant.propriety_));
    scroll_padding_x = Propriety({}, "https://tailwindcss.com/docs/scroll-padding");
    for(auto variant : padding_x) scroll_padding_x.styleClasses_.push_back(StyleClass("scroll-" + variant.className_, "scroll-" + variant.propriety_));
    scroll_padding_y = Propriety({}, "https://tailwindcss.com/docs/scroll-padding");
    for(auto variant : padding_y) scroll_padding_y.styleClasses_.push_back(StyleClass("scroll-" + variant.className_, "scroll-" + variant.propriety_));
    scroll_padding_top = Propriety({}, "https://tailwindcss.com/docs/scroll-padding");
    for(auto variant : padding_top) scroll_padding_top.styleClasses_.push_back(StyleClass("scroll-" + variant.className_, "scroll-" + variant.propriety_));
    scroll_padding_right = Propriety({}, "https://tailwindcss.com/docs/scroll-padding");
    for(auto variant : padding_right) scroll_padding_right.styleClasses_.push_back(StyleClass("scroll-" + variant.className_, "scroll-" + variant.propriety_));
    scroll_padding_bottom = Propriety({}, "https://tailwindcss.com/docs/scroll-padding");
    for(auto variant : padding_botto) scroll_padding_bottom.styleClasses_.push_back(StyleClass("scroll-" + variant.className_, "scroll-" + variant.propriety_));
    scroll_padding_left = Propriety({}, "https://tailwindcss.com/docs/scroll-padding");
    for(auto variant : padding_left) scroll_padding_left.styleClasses_.push_back(StyleClass("scroll-" + variant.className_, "scroll-" + variant.propriety_));
    scroll_padding_start = Propriety({}, "https://tailwindcss.com/docs/scroll-padding");
    for(auto variant : padding_start) scroll_padding_start.styleClasses_.push_back(StyleClass("scroll-" + variant.className_, "scroll-" + variant.propriety_));
    scroll_padding_end = Propriety({}, "https://tailwindcss.com/docs/scroll-padding");
    for(auto variant : padding_end) scroll_padding_end.styleClasses_.push_back(StyleClass("scroll-" + variant.className_, "scroll-" + variant.propriety_));




    // Scroll Snap Align
    scroll_snap_align = Propriety({
        StyleClass("snap-start", "scroll-snap-align: start;"),
        StyleClass("snap-end", "scroll-snap-align: end;"),
        StyleClass("snap-center", "scroll-snap-align: center;"),
        StyleClass("snap-align-none", "scroll-snap-align: none;"),
    }, "https://tailwindcss.com/docs/scroll-snap-align");

    // Scroll Snap Stop
    scroll_snap_stop = Propriety({
        StyleClass("snap-normal", "scroll-snap-stop: normal;"),
        StyleClass("snap-always", "scroll-snap-stop: always;"),
    }, "https://tailwindcss.com/docs/scroll-snap-stop");

    // Scroll Snap Type
    scroll_snap_type = Propriety({
        StyleClass("snap-none", "scroll-snap-type: none;"),
        StyleClass("snap-y", "scroll-snap-type: y;"),
        StyleClass("snap-x", "scroll-snap-type: x;"),
        StyleClass("snap-both", "scroll-snap-type: both;"),
    }, "https://tailwindcss.com/docs/scroll-snap-type");

    // Scroll Snap Mandatory
    scroll_snap_manadatory = Propriety({
        StyleClass("snap-mandatory", "scroll-snap-type: mandatory;"),
    }, "https://tailwindcss.com/docs/scroll-snap-type");

    // Scroll Snap Proximity
    scroll_snap_proximity = Propriety({
        StyleClass("snap-proximity", "scroll-snap-type: proximity;"),
    }, "https://tailwindcss.com/docs/scroll-snap-type");

    // Touch Action
    touch_action = Propriety({
        StyleClass("touch-auto", "touch-action: auto;"),
        StyleClass("touch-none", "touch-action: none;"),
        StyleClass("touch-pan-x", "touch-action: pan-x;"),
        StyleClass("touch-pan-left", "touch-action: pan-left;"),
        StyleClass("touch-pan-right", "touch-action: pan-right;"),
        StyleClass("touch-pan-y", "touch-action: pan-y;"),
        StyleClass("touch-pan-up", "touch-action: pan-up;"),
        StyleClass("touch-pan-down", "touch-action: pan-down;"),
        StyleClass("touch-pinch-zoom", "touch-action: pinch-zoom;"),
        StyleClass("touch-manipulation", "touch-action: manipulation;"),
    }, "https://tailwindcss.com/docs/touch-action");

    // User Select
    user_select = Propriety({
        StyleClass("select-none", "user-select: none;"),
        StyleClass("select-text", "user-select: text;"),
        StyleClass("select-all", "user-select: all;"),
        StyleClass("select-auto", "user-select: auto;"),
    }, "https://tailwindcss.com/docs/user-select");

    // Will Change
    will_change = Propriety({
        StyleClass("will-auto", "will-change: auto;"),
    }, "https://tailwindcss.com/docs/will-change");

}

std::string Interactivity::appearanceData()
{
    std::string data = "Appearance ------------------------------------\n";
    for(auto styleClass : appearance.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Interactivity::cursorData()
{
    std::string data = "Cursor ------------------------------------\n";
    for(auto styleClass : cursor.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Interactivity::pointerEventsData()
{
    std::string data = "Pointer Events ------------------------------------\n";
    for(auto styleClass : pointer_events.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Interactivity::resizeData()
{
    std::string data = "Resize ------------------------------------\n";
    for(auto styleClass : resize.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Interactivity::scrollBehaviorData()
{
    std::string data = "Scroll Behavior ------------------------------------\n";
    for(auto styleClass : scroll_behavior.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Interactivity::scrollMarginData()
{
    std::string data = "Scroll Margin ------------------------------------\n";
    data += "Scroll Margin ---------\n";
    for(auto styleClass : scroll_margin.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\nScroll Margin X ---------\n";
    for(auto styleClass : scroll_margin_x.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\nScroll Margin Y ---------\n";
    for(auto styleClass : scroll_margin_y.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\nScroll Margin Top ---------\n";
    for(auto styleClass : scroll_margin_top.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\nScroll Margin Right ---------\n";
    for(auto styleClass : scroll_margin_right.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\nScroll Margin Bottom ---------\n";
    for(auto styleClass : scroll_margin_bottom.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\nScroll Margin Left ---------\n";
    for(auto styleClass : scroll_margin_left.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\nScroll Margin Start ---------\n";
    for(auto styleClass : scroll_margin_start.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\nScroll Margin End ---------\n";
    for(auto styleClass : scroll_margin_end.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Interactivity::scrollPaddingData()
{
    std::string data = "Scroll Padding ------------------------------------\n";
    data += "Scroll Padding ---------\n";
    for(auto styleClass : scroll_padding.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\nScroll Padding X ---------\n";
    for(auto styleClass : scroll_padding_x.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\nScroll Padding Y ---------\n";
    for(auto styleClass : scroll_padding_y.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\nScroll Padding Top ---------\n";
    for(auto styleClass : scroll_padding_top.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\nScroll Padding Right ---------\n";
    for(auto styleClass : scroll_padding_right.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\nScroll Padding Bottom ---------\n";
    for(auto styleClass : scroll_padding_bottom.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\nScroll Padding Left ---------\n";
    for(auto styleClass : scroll_padding_left.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\nScroll Padding Start ---------\n";
    for(auto styleClass : scroll_padding_start.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\nScroll Padding End ---------\n";
    for(auto styleClass : scroll_padding_end.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Interactivity::scrollSnapAlignData()
{
    std::string data = "Scroll Snap Align ------------------------------------\n";
    for(auto styleClass : scroll_snap_align.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Interactivity::scrollSnapStopData()
{
    std::string data = "Scroll Snap Stop ------------------------------------\n";
    for(auto styleClass : scroll_snap_stop.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Interactivity::scrollSnapTypeData()
{
    std::string data = "Scroll Snap Type ---------\n";
    for(auto styleClass : scroll_snap_type.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\nScroll Snap Mandatory ---------\n";
    for(auto styleClass : scroll_snap_manadatory.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\nScroll Snap Proximity ---------\n";
    for(auto styleClass : scroll_snap_proximity.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Interactivity::touchActionData()
{
    std::string data = "Touch Action ------------------------------------\n";
    for(auto styleClass : touch_action.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Interactivity::userSelectData()
{
    std::string data = "User Select ------------------------------------\n";
    for(auto styleClass : user_select.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Interactivity::willChangeData()
{
    std::string data = "Will Change ------------------------------------\n";
    for(auto styleClass : will_change.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}



