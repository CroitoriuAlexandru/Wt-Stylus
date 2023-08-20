#include "include/Interactivity.h"

using namespace Tailwind;

Interactivity::Interactivity(std::vector<std::string> sizing_variants)
{
    // Appearance
    appearance = Propriety({
        StyleClass("appearance-none", "appearance: none;"),
    }, "https://tailwindcss.com/docs/appearance");

    // Cursor
    // auto|default|pointer|wait|text|move|help|not-allowed|none|progress|cell|crosshair|vertical-text|alias|copy|no-drop|all-scroll|col-resize|row-resize|n-resize|e-resize|s-resize|w-resize|ne-resize|nw-resize|se-resize|sw-resize|ew-resize|ns-resize|nesw-resize|nwse-resize|zoom-in|zoom-out
    cursor = Propriety({
        StyleClass("none", ""),
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
        StyleClass("cursor-zoom-out", "cursor: zoom-out;"),
    }, "https://tailwindcss.com/docs/cursor");

    // Pointer Events
    pointer_events = Propriety({
        StyleClass("none", ""),
        StyleClass("pointer-events-none", "pointer-events: none;"),
        StyleClass("pointer-events-auto", "pointer-events: auto;"),
    }, "https://tailwindcss.com/docs/pointer-events");

    // Resize 
    resize = Propriety({
        StyleClass("none", ""),
        StyleClass("resize-none", "resize: none;"),
        StyleClass("resize-y", "resize: vertical;"),
        StyleClass("resize-x", "resize: horizontal;"),
        StyleClass("resize", "resize: both;"),
    }, "https://tailwindcss.com/docs/resize");

    // Scroll Behavior
    scroll_behavior = Propriety({
        StyleClass("none", ""),
        StyleClass("scroll-auto", "scroll-behavior: auto;"),
        StyleClass("scroll-smooth", "scroll-behavior: smooth;"),
    }, "https://tailwindcss.com/docs/scroll-behavior");

    // Scroll Margin
    scroll_margin = Propriety({StyleClass("none", "")}, "https://tailwindcss.com/docs/scroll-margin");
    scroll_margin_x = Propriety({StyleClass("none", "")}, "https://tailwindcss.com/docs/scroll-margin");
    scroll_margin_y = Propriety({StyleClass("none", "")}, "https://tailwindcss.com/docs/scroll-margin");
    scroll_margin_top = Propriety({StyleClass("none", "")}, "https://tailwindcss.com/docs/scroll-margin");
    scroll_margin_right = Propriety({StyleClass("none", "")}, "https://tailwindcss.com/docs/scroll-margin");
    scroll_margin_bottom = Propriety({StyleClass("none", "")}, "https://tailwindcss.com/docs/scroll-margin");
    scroll_margin_left = Propriety({StyleClass("none", "")}, "https://tailwindcss.com/docs/scroll-margin");
    scroll_margin_start = Propriety({StyleClass("none", "")}, "https://tailwindcss.com/docs/scroll-margin");
    scroll_margin_end = Propriety({StyleClass("none", "")}, "https://tailwindcss.com/docs/scroll-margin");

    // Scroll Padding
    scroll_padding = Propriety({StyleClass("none", "")}, "https://tailwindcss.com/docs/scroll-padding");
    scroll_padding_x = Propriety({StyleClass("none", "")}, "https://tailwindcss.com/docs/scroll-padding");
    scroll_padding_y = Propriety({StyleClass("none", "")}, "https://tailwindcss.com/docs/scroll-padding");
    scroll_padding_top = Propriety({StyleClass("none", "")}, "https://tailwindcss.com/docs/scroll-padding");
    scroll_padding_right = Propriety({StyleClass("none", "")}, "https://tailwindcss.com/docs/scroll-padding");
    scroll_padding_bottom = Propriety({StyleClass("none", "")}, "https://tailwindcss.com/docs/scroll-padding");
    scroll_padding_left = Propriety({StyleClass("none", "")}, "https://tailwindcss.com/docs/scroll-padding");
    scroll_padding_start = Propriety({StyleClass("none", "")}, "https://tailwindcss.com/docs/scroll-padding");
    scroll_padding_end = Propriety({StyleClass("none", "")}, "https://tailwindcss.com/docs/scroll-padding");

    for(auto sizing : sizing_variants) {
        scroll_margin.styleClasses_.push_back(StyleClass("scroll-m-" + sizing, "" ));
        scroll_margin_x.styleClasses_.push_back(StyleClass("scroll-mx-" + sizing, "" ));
        scroll_margin_y.styleClasses_.push_back(StyleClass("scroll-my-" + sizing, "" ));
        scroll_margin_top.styleClasses_.push_back(StyleClass("scroll-mt-" + sizing, "" ));
        scroll_margin_right.styleClasses_.push_back(StyleClass("scroll-mr-" + sizing, "" ));
        scroll_margin_bottom.styleClasses_.push_back(StyleClass("scroll-mb-" + sizing, "" ));
        scroll_margin_left.styleClasses_.push_back(StyleClass("scroll-ml-" + sizing, "" ));
        scroll_margin_start.styleClasses_.push_back(StyleClass("scroll-ms-" + sizing, "" ));
        scroll_margin_end.styleClasses_.push_back(StyleClass("scroll-me-" + sizing, "" ));

        scroll_padding.styleClasses_.push_back(StyleClass("scroll-p-" + sizing, "" ));
        scroll_padding_x.styleClasses_.push_back(StyleClass("scroll-px-" + sizing, "" ));
        scroll_padding_y.styleClasses_.push_back(StyleClass("scroll-py-" + sizing, "" ));
        scroll_padding_top.styleClasses_.push_back(StyleClass("scroll-pt-" + sizing, "" ));
        scroll_padding_right.styleClasses_.push_back(StyleClass("scroll-pr-" + sizing, "" ));
        scroll_padding_bottom.styleClasses_.push_back(StyleClass("scroll-pb-" + sizing, "" ));
        scroll_padding_left.styleClasses_.push_back(StyleClass("scroll-pl-" + sizing, "" ));
        scroll_padding_start.styleClasses_.push_back(StyleClass("scroll-ps-" + sizing, "" ));
        scroll_padding_end.styleClasses_.push_back(StyleClass("scroll-pe-" + sizing, "" ));
    }


    // Scroll Snap Align
    scroll_snap_align = Propriety({
        StyleClass("none", ""),
        StyleClass("snap-start", "scroll-snap-align: start;"),
        StyleClass("snap-end", "scroll-snap-align: end;"),
        StyleClass("snap-center", "scroll-snap-align: center;"),
        StyleClass("snap-align-none", "scroll-snap-align: none;"),
    }, "https://tailwindcss.com/docs/scroll-snap-align");

    // Scroll Snap Stop
    scroll_snap_stop = Propriety({
        StyleClass("none", ""),
        StyleClass("snap-normal", "scroll-snap-stop: normal;"),
        StyleClass("snap-always", "scroll-snap-stop: always;"),
    }, "https://tailwindcss.com/docs/scroll-snap-stop");

    // Scroll Snap Type
    scroll_snap_type = Propriety({
        StyleClass("none", ""),
        StyleClass("snap-none", "scroll-snap-type: none;"),
        StyleClass("snap-y", "scroll-snap-type: y;"),
        StyleClass("snap-x", "scroll-snap-type: x;"),
        StyleClass("snap-both", "scroll-snap-type: both;"),
    }, "https://tailwindcss.com/docs/scroll-snap-type");

    // Scroll Snap Mandatory
    scroll_snap_manadatory = Propriety({
        StyleClass("none", ""),
        StyleClass("snap-mandatory", "scroll-snap-type: mandatory;"),
    }, "https://tailwindcss.com/docs/scroll-snap-type");

    // Scroll Snap Proximity
    scroll_snap_proximity = Propriety({
        StyleClass("none", ""),
        StyleClass("snap-proximity", "scroll-snap-type: proximity;"),
    }, "https://tailwindcss.com/docs/scroll-snap-type");

    // Touch Action
    // manipulation|pinch-zoom|pan-down|pan-up|pan-y|pan-right|pan-left|pan-x|pan-none|auto
    touch_action = Propriety({
        StyleClass("none", ""),
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
        StyleClass("none", ""),
        StyleClass("select-none", "user-select: none;"),
        StyleClass("select-text", "user-select: text;"),
        StyleClass("select-all", "user-select: all;"),
        StyleClass("select-auto", "user-select: auto;"),
    }, "https://tailwindcss.com/docs/user-select");

    // Will Change
    will_change = Propriety({
        StyleClass("none", ""),
        StyleClass("will-change-auto", "will-change: auto;"),
        StyleClass("will-change-scroll", "will-change: scroll-position;"),
        StyleClass("will-change-contents", "will-change: contents;"),
        StyleClass("will-change-transform", "will-change: transform;")
    }, "https://tailwindcss.com/docs/will-change");

}

std::string Interactivity::appearanceData()
{
    std::string data = " ";
    for(auto styleClass : appearance.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    return data;
}

std::string Interactivity::cursorData()
{
    std::string data = " ";
    for(auto styleClass : cursor.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    return data;
}

std::string Interactivity::pointerEventsData()
{
    std::string data = " ";
    for(auto styleClass : pointer_events.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    return data;
}

std::string Interactivity::resizeData()
{
    std::string data = " ";
    for(auto styleClass : resize.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    return data;
}

std::string Interactivity::scrollBehaviorData()
{
    std::string data = " ";
    for(auto styleClass : scroll_behavior.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    return data;
}

std::string Interactivity::scrollMarginData()
{
    std::string data = " ";
    for(auto styleClass : scroll_margin.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    for(auto styleClass : scroll_margin_x.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    for(auto styleClass : scroll_margin_y.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    for(auto styleClass : scroll_margin_top.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    for(auto styleClass : scroll_margin_right.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    for(auto styleClass : scroll_margin_bottom.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    for(auto styleClass : scroll_margin_left.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    for(auto styleClass : scroll_margin_start.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    for(auto styleClass : scroll_margin_end.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    return data;
}

std::string Interactivity::scrollPaddingData()
{
    std::string data = " ";
    for(auto styleClass : scroll_padding.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    for(auto styleClass : scroll_padding_x.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    for(auto styleClass : scroll_padding_y.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    for(auto styleClass : scroll_padding_top.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    for(auto styleClass : scroll_padding_right.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    for(auto styleClass : scroll_padding_bottom.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    for(auto styleClass : scroll_padding_left.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    for(auto styleClass : scroll_padding_start.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    for(auto styleClass : scroll_padding_end.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    return data;
}

std::string Interactivity::scrollSnapAlignData()
{
    std::string data = " ";
    for(auto styleClass : scroll_snap_align.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    return data;
}

std::string Interactivity::scrollSnapStopData()
{
    std::string data = " ";
    for(auto styleClass : scroll_snap_stop.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    return data;
}

std::string Interactivity::scrollSnapTypeData()
{
    std::string data = " ";
    for(auto styleClass : scroll_snap_type.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    for(auto styleClass : scroll_snap_manadatory.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    for(auto styleClass : scroll_snap_proximity.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    return data;
}

std::string Interactivity::touchActionData()
{
    std::string data = " ";
    for(auto styleClass : touch_action.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    return data;
}

std::string Interactivity::userSelectData()
{
    std::string data = " ";
    for(auto styleClass : user_select.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    return data;
}

std::string Interactivity::willChangeData()
{
    std::string data = " ";
    for(auto styleClass : will_change.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    return data;
}



