#include "include/Flexbox.h"

using namespace Tailwind;

Flexbox::Flexbox(std::vector<std::string> spacing_variants)
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



    // basis
    basis = Propriety({}, "https://tailwindcss.com/docs/flex-basis");
    std::vector<std::string> basis_extra_variants = {"auto", "1/2", "1/3", "2/3", "1/4", "2/4", "3/4", "1/5", "2/5", "3/5", "4/5", "1/6", "2/6", "3/6", "4/6", "5/6", "1/12", "2/12", "3/12", "4/12", "5/12", "6/12", "7/12", "8/12", "9/12", "10/12", "11/12", "full"};
    for(auto size : basis_extra_variants) {
        basis.styleClasses_.push_back(StyleClass("basis-" + size, ""));
    }
    for(auto size : spacing_variants) {
        basis.styleClasses_.push_back(StyleClass("basis-" + size, ""));
    }

    // direction
    direction = Propriety({
        StyleClass("flex-row-reverse", "flex-direction: row-reverse;"),
        StyleClass("flex-col-reverse", "flex-direction: column-reverse;"),
        StyleClass("flex-col", "flex-direction: column;"),
        StyleClass("flex-row", "flex-direction: row;")
    }, "https://tailwindcss.com/docs/flex-direction");

    // wrap
    wrap = Propriety({
        StyleClass("flex-wrap-reverse", "flex-wrap: wrap-reverse;"),
        StyleClass("flex-wrap", "flex-wrap: wrap;"),
        StyleClass("flex-nowrap", "flex-wrap: nowrap;")
    }, "https://tailwindcss.com/docs/flex-wrap");

    // flex
    flex = Propriety({
        StyleClass("flex-1", "flex: 1 1 0%;"),
        StyleClass("flex-auto", "flex: 1 1 auto;"),
        StyleClass("flex-initial", "flex: 0 1 auto;"),
        StyleClass("flex-none", "flex: none;")
    }, "https://tailwindcss.com/docs/flex");

    // grow
    grow = Propriety({
        StyleClass("grow-0", "flex-grow: 0;"),
        StyleClass("grow", "flex-grow: 1;")
    }, "https://tailwindcss.com/docs/flex-grow");

    // shrink
    shrink = Propriety({
        StyleClass("shrink-0", "flex-shrink: 0;"),
        StyleClass("shrink", "flex-shrink: 1;")
    }, "https://tailwindcss.com/docs/flex-shrink");

    // place content
    std::vector<std::string> content_variants = {"start", "end", "center", "between", "around", "evenly", "stretch"};
    std::vector<std::string> items_variants = {"start", "end", "center", "stretch"};

    std::vector<std::string> self_variants = {"auto", "start", "end", "center", "stretch"};
    justify_content = Propriety({}, "https://tailwindcss.com/docs/justify-content");
    align_content = Propriety({}, "https://tailwindcss.com/docs/align-content");
    place_content = Propriety({}, "https://tailwindcss.com/docs/place-content");

    justify_items = Propriety({}, "https://tailwindcss.com/docs/justify-items");
    align_items = Propriety({}, "https://tailwindcss.com/docs/align-items");
    place_items = Propriety({}, "https://tailwindcss.com/docs/place-items");

    justify_self = Propriety({}, "https://tailwindcss.com/docs/justify-self");
    align_self = Propriety({}, "https://tailwindcss.com/docs/align-self");
    place_self = Propriety({}, "https://tailwindcss.com/docs/place-self");

    // there are some extra style classes forsome proprieties 
    StyleClass justify_normal = StyleClass("justify-normal", "justify-content: normal;");
    StyleClass content_normal = StyleClass("content-normal", "align-content: normal;");
    StyleClass content_baseline = StyleClass("content-baseline", "align-content: baseline;");
    StyleClass place_content_baseline = StyleClass("place-content-baseline", "place-content: baseline;");
    StyleClass items_baseline = StyleClass("items-baseline", "align-items: baseline;");
    StyleClass place_items_baseline = StyleClass("place-items-baseline", "place-items: baseline;");
    StyleClass self_baseline = StyleClass("self-baseline", "align-self: baseline;");

    justify_content.styleClasses_.push_back(justify_normal);
    align_content.styleClasses_.push_back(content_normal);
    for(auto size : content_variants) {
        justify_content.styleClasses_.push_back(StyleClass("justify-" + size, "justify-content: " + size + ";"));
        align_content.styleClasses_.push_back(StyleClass("content-" + size, "align-content: " + size + ";"));
        place_content.styleClasses_.push_back(StyleClass("place-content-" + size, "place-content: " + size + ";"));
    }
    align_content.styleClasses_.push_back(content_baseline);
    place_content.styleClasses_.push_back(place_content_baseline);

    for(auto size : items_variants) {
        justify_items.styleClasses_.push_back(StyleClass("justify-items-" + size, "justify-items: " + size + ";"));
        align_items.styleClasses_.push_back(StyleClass("items-" + size, "align-items: " + size + ";"));
        place_items.styleClasses_.push_back(StyleClass("place-items-" + size, "place-items: " + size + ";"));
    }
    align_items.styleClasses_.push_back(items_baseline);
    place_items.styleClasses_.push_back(place_items_baseline);

    for(auto size : self_variants) {
        justify_self.styleClasses_.push_back(StyleClass("justify-self-" + size, "justify-self: " + size + ";"));
        align_self.styleClasses_.push_back(StyleClass("self-" + size, "align-self: " + size + ";"));
        place_self.styleClasses_.push_back(StyleClass("place-self-" + size, "place-self: " + size + ";"));
    }
    align_self.styleClasses_.push_back(self_baseline);


    
}

std::string Flexbox::basisData() {
    std::string data = "";
    for(auto styleClass : basis.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    data += "\n";
    return data;
}

std::string Flexbox::directionData() {
    std::string data = "";
    for(auto styleClass : direction.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    data += "\n";
    return data;
}

std::string Flexbox::wrapData() {
    std::string data = "";
    for(auto styleClass : wrap.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    data += "\n";
    return data;
}

std::string Flexbox::flexData() {
    std::string data = "";
    for(auto styleClass : flex.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    data += "\n";
    return data;
}

std::string Flexbox::growData() {
    std::string data = "";
    for(auto styleClass : grow.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    data += "\n";
    return data;
}

std::string Flexbox::shrinkData() {
    std::string data = "";
    for(auto styleClass : shrink.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    data += "\n";
    return data;
}

std::string Flexbox::orderData() {
    std::string data = "";
    for(auto styleClass : order.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    data += "\n";
    return data;
}

std::string Flexbox::placeData() {
    std::string data = "";
    for(auto styleClass : place_content.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    data += "\n";
    for(auto styleClass : place_items.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    data += "\n";
    for(auto styleClass : place_self.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    data += "\n";
    return data;
}

std::string Flexbox::justifyData() {
    std::string data = "";
    for(auto styleClass : justify_content.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    data += "\n";
    for(auto styleClass : justify_items.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    data += "\n";
    for(auto styleClass : justify_self.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    data += "\n";
    return data;
}

std::string Flexbox::alignData() {
    std::string data = "";
    for(auto styleClass : align_content.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    data += "\n";
    for(auto styleClass : align_items.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    data += "\n";
    for(auto styleClass : align_self.styleClasses_) {
        data += styleClass.className_ + " ";
    }
    data += "\n";
    return data;
}