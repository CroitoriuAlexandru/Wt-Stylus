#include "include/ElementClassEdditor.h"
#include "include/TailwindRegexp.h"
#include <Wt/WApplication.h>
#include <Wt/WAnimation.h>

ElementClassEdditor::ElementClassEdditor()
    : WTemplate(tr("stylus-element-edditor"))
{
    tailwindConfig_ = std::make_shared<Config>();

    effectsWidget_ = bindWidget("effects-controls", std::make_unique<ElementEffectsWidget>(tailwindConfig_));
    spacingWidget_ = bindWidget("spacing-controls", std::make_unique<ElementSpacingWidget>(tailwindConfig_));
    sizingWidget_ = bindWidget("sizing-controls", std::make_unique<ElementSizingWidget>(tailwindConfig_));
    backgroundWidget_ = bindWidget("background-controls", std::make_unique<ElementBackgroundWidget>(tailwindConfig_));
    transformsWidget_ = bindWidget("transforms-controls", std::make_unique<ElementTransformsWidget>(tailwindConfig_));
    layoutWidget_ = bindWidget("layout-controls", std::make_unique<ElementLayoutWidget>(tailwindConfig_));

    // sizingWidget_->collapse();
    // spacingWidget_->collapse();
    // backgroundWidget_->collapse();
    effectsWidget_->collapse();
    transformsWidget_->collapse();
    layoutWidget_->collapse();

    layoutWidget_->styleChanged().connect(this, [=](){
        std::string newStyles = notFoundClasses + " ";
        layoutClasses = layoutWidget_->getStyles();
        if(layoutClasses != ""){ newStyles += layoutClasses + " "; }
        if(sizingClasses != ""){ newStyles += sizingClasses + " "; }
        if(spacingClasses != ""){ newStyles += spacingClasses + " "; }
        if(backgroundClasses != ""){ newStyles += backgroundClasses + " "; }
        if(effectsClasses != ""){ newStyles += effectsClasses + " "; }
        if(transformsClasses != ""){ newStyles += transformsClasses + " "; }
        styleChanged_.emit(newStyles);
    });

    transformsWidget_->styleChanged().connect(this, [=](){
        std::string newStyles = notFoundClasses + " ";
        transformsClasses = transformsWidget_->getStyles();
        if(layoutClasses != ""){ newStyles += layoutClasses + " "; }
        if(sizingClasses != ""){ newStyles += sizingClasses + " "; }
        if(spacingClasses != ""){ newStyles += spacingClasses + " "; }
        if(backgroundClasses != ""){ newStyles += backgroundClasses + " "; }
        if(effectsClasses != ""){ newStyles += effectsClasses + " "; }
        if(transformsClasses != ""){ newStyles += transformsClasses + " "; }
        styleChanged_.emit(newStyles);
    });

    effectsWidget_->styleChanged().connect(this, [=](){
        std::string newStyles = notFoundClasses + " ";
        effectsClasses = effectsWidget_->getStyles();
        if(layoutClasses != ""){ newStyles += layoutClasses + " "; }
        if(sizingClasses != ""){ newStyles += sizingClasses + " "; }
        if(spacingClasses != ""){ newStyles += spacingClasses + " "; }
        if(backgroundClasses != ""){ newStyles += backgroundClasses + " "; }
        if(effectsClasses != ""){ newStyles += effectsClasses + " "; }
        if(transformsClasses != ""){ newStyles += transformsClasses + " "; }
        styleChanged_.emit(newStyles);
    });

    spacingWidget_->styleChanged().connect(this, [=](){
        std::string newStyles = notFoundClasses + " ";
        spacingClasses = spacingWidget_->getStyles();
        if(layoutClasses != ""){ newStyles += layoutClasses + " "; }
        if(sizingClasses != ""){ newStyles += sizingClasses + " "; }
        if(spacingClasses != ""){ newStyles += spacingClasses + " "; }
        if(backgroundClasses != ""){ newStyles += backgroundClasses + " "; }
        if(effectsClasses != ""){ newStyles += effectsClasses + " "; }
        if(transformsClasses != ""){ newStyles += transformsClasses + " "; }
        styleChanged_.emit(newStyles);
    });

    sizingWidget_->styleChanged().connect(this, [=](){
        std::string newStyles = notFoundClasses + " ";
        sizingClasses = sizingWidget_->getStyles();
        if(layoutClasses != ""){ newStyles += layoutClasses + " "; }
        if(sizingClasses != ""){ newStyles += sizingClasses + " "; }
        if(spacingClasses != ""){ newStyles += spacingClasses + " "; }
        if(backgroundClasses != ""){ newStyles += backgroundClasses + " "; }
        if(effectsClasses != ""){ newStyles += effectsClasses + " "; }
        if(transformsClasses != ""){ newStyles += transformsClasses + " "; }
        styleChanged_.emit(newStyles);
    });

    backgroundWidget_->styleChanged().connect(this, [=](){
        std::string newStyles = notFoundClasses + " ";
        backgroundClasses = backgroundWidget_->getStyles();
        if(layoutClasses != ""){ newStyles += layoutClasses + " "; }
        if(sizingClasses != ""){ newStyles += sizingClasses + " "; }
        if(spacingClasses != ""){ newStyles += spacingClasses + " "; }
        if(backgroundClasses != ""){ newStyles += backgroundClasses + " "; }
        if(effectsClasses != ""){ newStyles += effectsClasses + " "; }
        if(transformsClasses != ""){ newStyles += transformsClasses + " "; }
        styleChanged_.emit(newStyles);
    });

}

void ElementClassEdditor::setStyleClasses(std::string classes)
{
    resetStyles();
    classes = " " + classes;
    std::cout << "\n\n classes : <" << classes << ">\n\n";
        
    LayoutData layout;
    layout.aspect_ratio = findAndRemoveMatche(tailwindConfig_->layout.aspect_ratio_regex, classes);
    if(findAndRemoveMatche(tailwindConfig_->layout.container_regex, classes) != ""){
        layout.container = true;
    }
    layout.columns = findAndRemoveMatche(tailwindConfig_->layout.columns_regex, classes);
    layout.break_after = findAndRemoveMatche(tailwindConfig_->layout.break_after_regex, classes);
    layout.break_before = findAndRemoveMatche(tailwindConfig_->layout.break_before_regex, classes);
    layout.break_inside = findAndRemoveMatche(tailwindConfig_->layout.break_inside_regex, classes);
    layout.box_decoration_break = findAndRemoveMatche(tailwindConfig_->layout.box_decoration_break_regex, classes);
    layout.box_sizing = findAndRemoveMatche(tailwindConfig_->layout.box_sizing_regex, classes);
    layout.display = findAndRemoveMatche(tailwindConfig_->layout.display_regex, classes);
    layout.floats = findAndRemoveMatche(tailwindConfig_->layout.floats_regex, classes);
    layout.clear = findAndRemoveMatche(tailwindConfig_->layout.clear_regex, classes);
    layout.isolation = findAndRemoveMatche(tailwindConfig_->layout.isolation_regex, classes);
    layout.object_fit = findAndRemoveMatche(tailwindConfig_->layout.object_fit_regex, classes);
    layout.object_position = findAndRemoveMatche(tailwindConfig_->layout.object_position_regex, classes);
    layout.overflow = findAndRemoveMatches(tailwindConfig_->layout.overflow_regex, classes);
    layout.overscroll_behavior = findAndRemoveMatches(tailwindConfig_->layout.overscroll_behavior_regex, classes);
    // std::cout << "\n\n classes : <" << classes << ">" << "\n\n";
    // for(auto overscroll : layout.overscroll_behavior){
        // std::cout << "\n\n overscroll : <" << overscroll << ">" << "\n\n";
    // }
    layout.position = findAndRemoveMatche(tailwindConfig_->layout.position_regex, classes);
    layout.inset = findAndRemoveMatches(tailwindConfig_->layout.position_inset_regex, classes);
    layout.top_left_bottom_right = findAndRemoveMatches(tailwindConfig_->layout.position_sides_regex, classes);
    layout.visibility = findAndRemoveMatche(tailwindConfig_->layout.visibility_regex, classes);
    layout.z_index = findAndRemoveMatche(tailwindConfig_->layout.z_index_regex, classes);


    TransformsData transforms;
    transforms.scale = findAndRemoveMatches(tailwindConfig_->transforms.scale_regex, classes);
    transforms.rotate = findAndRemoveMatche(tailwindConfig_->transforms.rotate_regex, classes);
    transforms.translate = findAndRemoveMatches(tailwindConfig_->transforms.translate_regex, classes);
    transforms.skew = findAndRemoveMatches(tailwindConfig_->transforms.skew_regex, classes);
    transforms.transform_origin = findAndRemoveMatche(tailwindConfig_->transforms.origin_regex, classes);

    EffectsData effects;
    auto boxShadowVec = findAndRemoveMatches(tailwindConfig_->effects.box_shadow_regex, classes);
	for(auto& boxShadow : boxShadowVec)
	{
		if(boxShadow.find("inner") != std::string::npos)
			effects.boxShadowInner = true;
		else 
            effects.boxShadow = boxShadow;
	}
    effects.opacity = findAndRemoveMatche(tailwindConfig_->effects.opacity_regex, classes);
    effects.boxShadowColor = findAndRemoveMatche(tailwindConfig_->effects.box_shadow_color_regex, classes);
    effects.mixBlendMode = findAndRemoveMatche(tailwindConfig_->effects.mix_blend_mode_regex, classes);
    effects.backgroundBlendMode = findAndRemoveMatche(tailwindConfig_->effects.bg_blend_mode_regex, classes);


    BackgroundData bgData;
    bgData.bg_image = findAndRemoveMatche(tailwindConfig_->backgrounds.background_image_regex, classes);

    bgData.bg_color_from = findAndRemoveMatche(tailwindConfig_->backgrounds.background_color_from_regex, classes);
    bgData.bg_color_from_step = findAndRemoveMatche(tailwindConfig_->backgrounds.background_color_from_step, classes);
    bgData.bg_color_via = findAndRemoveMatche(tailwindConfig_->backgrounds.background_color_via_regex, classes);
    bgData.bg_color_via_step = findAndRemoveMatche(tailwindConfig_->backgrounds.background_color_via_step, classes);
    bgData.bg_color_to = findAndRemoveMatche(tailwindConfig_->backgrounds.background_color_to_regex, classes);
    bgData.bg_color_to_step = findAndRemoveMatche(tailwindConfig_->backgrounds.background_color_to_step, classes);
    // std::cout << "\n --- bg color should be taken out \n at the moment classes <" << classes << ">\n";
    bgData.bg_color = findAndRemoveMatche(tailwindConfig_->backgrounds.background_color_regex, classes);
    // std::cout << "\n --- bg color should be taken out \n at the moment classes <" << classes << ">\n";

    bgData.bg_attachment = findAndRemoveMatche(tailwindConfig_->backgrounds.background_attachment_regex, classes);
    bgData.bg_clip = findAndRemoveMatche(tailwindConfig_->backgrounds.background_clip_regex, classes);
    bgData.bg_origin = findAndRemoveMatche(tailwindConfig_->backgrounds.background_origin_regex, classes);
    bgData.bg_position = findAndRemoveMatche(tailwindConfig_->backgrounds.background_position_regex, classes);
    bgData.bg_repeat = findAndRemoveMatche(tailwindConfig_->backgrounds.background_repeat_regex, classes);
    bgData.bg_size = findAndRemoveMatche(tailwindConfig_->backgrounds.background_size_regex, classes);

    SpacingData spacing;
    spacing.padding = findAndRemoveMatches(tailwindConfig_->spacing.padding_regex, classes);
    spacing.margin = findAndRemoveMatches(tailwindConfig_->spacing.margin_regex, classes);
    spacing.space = findAndRemoveMatches(tailwindConfig_->spacing.space_regex, classes);

    SizingData sizing;
    sizing.minWidth = findAndRemoveMatche(tailwindConfig_->sizing.min_width_regex, classes);
    sizing.maxWidth = findAndRemoveMatche(tailwindConfig_->sizing.max_width_regex, classes);
    sizing.minHeight = findAndRemoveMatche(tailwindConfig_->sizing.min_height_regex, classes);
    sizing.maxHeight = findAndRemoveMatche(tailwindConfig_->sizing.max_height_regex, classes);
    sizing.width = findAndRemoveMatche(tailwindConfig_->sizing.width_regex, classes);
    sizing.height = findAndRemoveMatche(tailwindConfig_->sizing.height_regex, classes);

    layoutWidget_->setClasses(layout);
    spacingWidget_->setClasses(spacing);
    sizingWidget_->setClasses(sizing);
    backgroundWidget_->setClasses(bgData);
    effectsWidget_->setClasses(effects);
    transformsWidget_->setClasses(transforms);

    layoutClasses = layoutWidget_->getStyles();
    spacingClasses = spacingWidget_->getStyles();
    sizingClasses = sizingWidget_->getStyles();
    backgroundClasses = backgroundWidget_->getStyles();
    effectsClasses = effectsWidget_->getStyles();
    transformsClasses = transformsWidget_->getStyles();

    notFoundClasses = std::regex_replace(classes, std::regex("^\\s+"), "");
    std::cout << "\n\n notFoundClasses : " << notFoundClasses << "\n\n";
}

std::string ElementClassEdditor::getStyles()
{
    std::string styles = "";
    styles += layoutWidget_->getStyles() + " ";
    styles += backgroundWidget_->getStyles() + " ";
    styles += sizingWidget_->getStyles() + " ";
    styles += spacingWidget_->getStyles() + " ";
    styles += effectsWidget_->getStyles() + " ";
    styles += transformsWidget_->getStyles() + " ";
    styles += notFoundClasses;
    return styles;
}

void ElementClassEdditor::resetStyles()
{
    notFoundClasses = "";
    backgroundWidget_->resetStyles();
    sizingWidget_->resetStyles();
    spacingWidget_->resetStyles();
    effectsWidget_->resetStyles();
    transformsWidget_->resetStyles();
    layoutWidget_->resetStyles();
}

std::vector<std::string> ElementClassEdditor::findAndRemoveMatches(std::regex regex, std::string& str) {
    
    std::regex_iterator<std::string::iterator> it(str.begin(), str.end(), regex);
    std::regex_iterator<std::string::iterator> end;
    std::string result = "";

    std::vector<std::string> matches;

    size_t lastPos = 0;
    while (it != end) {
        result += str.substr(lastPos, it->position() - lastPos);
        auto match = it->str();
        if(match == ""){ match = "none"; }
        matches.push_back(match); // Store deleted value in vector
        lastPos = it->position() + it->length();
        ++it;
    }
    // remove padding classes from classes string
    str = result + str.substr(lastPos, str.length() - lastPos);

    return matches;
}
std::vector<std::string> ElementClassEdditor::findAndRemoveMatches(boost::regex regex, std::string& str) {
    boost::regex_iterator<std::string::iterator> it(str.begin(), str.end(), regex);
    boost::regex_iterator<std::string::iterator> end;
    std::string result = "";

    std::vector<std::string> matches;

    size_t lastPos = 0;
    while (it != end) {
        result += str.substr(lastPos, it->position() - lastPos);
        auto match = it->str();
        if(match == ""){ match = "none"; }
        matches.push_back(match); // Store deleted value in vector
        lastPos = it->position() + it->length();
        ++it;
    }
    // remove padding classes from classes string
    str = result + str.substr(lastPos, str.length() - lastPos);
    return matches;
}

std::string ElementClassEdditor::findAndRemoveMatche(std::regex regex, std::string& str) {
        
        std::regex_iterator<std::string::iterator> it(str.begin(), str.end(), regex);
        std::regex_iterator<std::string::iterator> end;
        std::string result = "";
    
        std::string match = "";
    
        size_t lastPos = 0;
        while (it != end) {
            result += str.substr(lastPos, it->position() - lastPos);
            match = it->str(); // Store deleted value in vector
            lastPos = it->position() + it->length();
            ++it;
        }
        // remove padding classes from classes string
        str = result + str.substr(lastPos, str.length() - lastPos);
        // clean start whitespace from match
        match = std::regex_replace(match, std::regex("^\\s+"), "");
        if(match == ""){ match = "none"; }
        return match;
}
std::string ElementClassEdditor::findAndRemoveMatche(boost::regex regex, std::string& str) {
    boost::regex_iterator<std::string::iterator> it(str.begin(), str.end(), regex);
    boost::regex_iterator<std::string::iterator> end;
    std::string result = "";

    std::string match = "";

    size_t lastPos = 0;
    while (it != end) {
        result += str.substr(lastPos, it->position() - lastPos);
        match = it->str(); // Store deleted value in vector
        lastPos = it->position() + it->length();
        ++it;
    }
    // remove padding classes from classes string
    str = result + str.substr(lastPos, str.length() - lastPos);
    // clean start whitespace from match
    match = boost::regex_replace(match, boost::regex("^\\s+"), "");
    if(match == ""){ match = "none"; }
    return match;
}