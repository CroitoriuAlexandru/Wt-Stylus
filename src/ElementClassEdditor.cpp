#include "include/ElementClassEdditor.h"
#include "include/TailwindRegexp.h"
#include <Wt/WApplication.h>
#include <Wt/WAnimation.h>

std::vector<std::string> ElementClassEdditor::findAndRemoveMatches(std::regex regex, std::string& str) {
    
    std::regex_iterator<std::string::iterator> it(str.begin(), str.end(), regex);
    std::regex_iterator<std::string::iterator> end;
    std::string result = "";

    std::vector<std::string> matches;

    size_t lastPos = 0;
    while (it != end) {
        result += str.substr(lastPos, it->position() - lastPos);
        matches.push_back(it->str()); // Store deleted value in vector
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
        return match;
}


ElementClassEdditor::ElementClassEdditor(std::string templateName)
    : WTemplate(tr(templateName))
{

    Wt::WAnimation animation = Wt::WAnimation(Wt::AnimationEffect::SlideInFromBottom, Wt::TimingFunction::EaseInOut, 300);

    spacing_btn_display = bindWidget("spacing-display-button", std::make_unique<Wt::WPushButton>("Spacing"));
    sizing_btn_display = bindWidget("sizing-display-button", std::make_unique<Wt::WPushButton>("Sizing"));
    background_btn_display = bindWidget("background-display-button", std::make_unique<Wt::WPushButton>("Background"));

    auto btns_styles = "w-full text-center p-2 bg-neutral-800 text-neutral-200 rounded border-1 border-solid my-1 hover:bg-neutral-900 border-r-8 border-neutral-900 ";
    spacing_btn_display->setStyleClass(btns_styles);
    sizing_btn_display->setStyleClass(btns_styles);
    background_btn_display->setStyleClass(btns_styles);


    
    spacingWidget_ = Wt::WApplication::instance()->root()->addChild(std::make_unique<ElementSpacingWidget>());
    sizingWidget_ = Wt::WApplication::instance()->root()->addChild(std::make_unique<ElementSizingWidget>());
    backgroundWidget_ = Wt::WApplication::instance()->root()->addChild(std::make_unique<ElementBackgroundWidget>());

    spacingWidget_->addStyleClass("w-[300px]");
    sizingWidget_->addStyleClass("w-[300px]");
    backgroundWidget_->addStyleClass("w-[300px]");


	spacingWidget_->setOffsets(0, Wt::Side::Bottom);
	spacingWidget_->setOffsets(300, Wt::Side::Right);

    sizingWidget_->setOffsets(0, Wt::Side::Bottom);
    sizingWidget_->setOffsets(600, Wt::Side::Right);

    backgroundWidget_->setOffsets(0, Wt::Side::Bottom);
    backgroundWidget_->setOffsets(900, Wt::Side::Right);

    spacingWidget_->animateShow(animation);
    backgroundWidget_->animateShow(animation);
    sizingWidget_->animateShow(animation);

    spacing_btn_display->toggleStyleClass("!bg-neutral-900", true);
    sizing_btn_display->toggleStyleClass("!bg-neutral-900", true);
    background_btn_display->toggleStyleClass("!bg-neutral-900", true);

    spacingWidget_->styleChanged().connect(this, [=](){
        std::string newStyles = notFoundClasses + " ";
        spacingClasses = spacingWidget_->getStyles();
        newStyles += backgroundClasses + " ";
        newStyles += sizingClasses + " ";
        newStyles += spacingClasses + " ";
        styleChanged_.emit(newStyles); 
    });

    sizingWidget_->styleChanged().connect(this, [=](){
        std::string newStyles = notFoundClasses + " ";
        sizingClasses = sizingWidget_->getStyles();
        newStyles += backgroundClasses + " ";
        newStyles += sizingClasses + " ";
        newStyles += spacingClasses + " ";
        styleChanged_.emit(newStyles);
    });

    backgroundWidget_->styleChanged().connect(this, [=](){
        std::string newStyles = notFoundClasses + " ";
        backgroundClasses = backgroundWidget_->getStyles();
        newStyles += backgroundClasses + " ";
        newStyles += sizingClasses + " ";
        newStyles += spacingClasses + " ";
        styleChanged_.emit(newStyles);
    });

    // buttons to toggle element controls from display
    spacing_btn_display->clicked().connect(spacingWidget_, [=](){
        if(spacingWidget_->isVisible()){
            spacing_btn_display->toggleStyleClass("!bg-neutral-900", false, true);
            spacingWidget_->animateHide(animation);
        }else{
            spacing_btn_display->toggleStyleClass("!bg-neutral-900", true, true);
            spacingWidget_->animateShow(animation);
        }
    });

    sizing_btn_display->clicked().connect(sizingWidget_, [=](){
        if(sizingWidget_->isVisible()){
            sizing_btn_display->toggleStyleClass("!bg-neutral-900", false, true);
            sizingWidget_->animateHide(animation);
        }else{
            sizing_btn_display->toggleStyleClass("!bg-neutral-900", true, true);
            sizingWidget_->animateShow(animation);
        }
    });

    background_btn_display->clicked().connect(backgroundWidget_, [=](){
        if(backgroundWidget_->isVisible()){
            background_btn_display->toggleStyleClass("!bg-neutral-900", false, true);
            backgroundWidget_->animateHide(animation);
        }else{
            background_btn_display->toggleStyleClass("!bg-neutral-900", true, true);
            backgroundWidget_->animateShow(animation);
        }
    });

}

void ElementClassEdditor::setStyleClasses(std::string classes)
{
    // clean any multiple whitespaces from the string
    // classes = std::regex_replace(classes, std::regex("\\s+"), " ");
    // std::cout << "\n\n classes from Element Class Edditor :" << classes << "\n\n";
    // create vector of classes for spacing
        // create vector of classes for background
    auto save = classes;
    resetStyles();

    // std::cout << "\n\n\n before background removal - <" << classes << ">\n";
    BackgroundData bgData;
    bgData.bg_image = findAndRemoveMatche(background_image_regex, classes);
    if(bgData.bg_image != ""){
        bgData.bg_color_class = findAndRemoveMatche(background_color_from_regex, classes);
        // std::cout << "classes before-from-step: <" << classes << ">\n";
        bgData.bg_color_from_step = findAndRemoveMatche(background_color_from_step, classes);
        // std::cout << "classes after-from-step: <" << classes << ">\n";
        bgData.bg_color_via = findAndRemoveMatche(background_color_via_regex, classes);
        bgData.bg_color_via_step = findAndRemoveMatche(background_color_via_step, classes);
        bgData.bg_color_to = findAndRemoveMatche(background_color_to_regex, classes);
        bgData.bg_color_to_step = findAndRemoveMatche(background_color_to_step, classes);
    }else {
        bgData.bg_color_class = findAndRemoveMatche(background_color_regexp, classes);
    }
    bgData.bg_attachment = findAndRemoveMatche(background_attachment_regex, classes);
    bgData.bg_clip = findAndRemoveMatche(background_clip_regex, classes);
    bgData.bg_origin = findAndRemoveMatche(background_origin_regex, classes);
    bgData.bg_position = findAndRemoveMatche(background_position_regex, classes);
    bgData.bg_repeat = findAndRemoveMatche(background_repeat_regex, classes);
    bgData.bg_size = findAndRemoveMatche(background_size_regex, classes);


    // std::cout << "\n\n\n before spacing removal - <" << classes << ">\n";

    SpacingData spacing;
    spacing.padding = findAndRemoveMatches(padding_regexp, classes);
    spacing.margin = findAndRemoveMatches(margin_regexp, classes);
    spacing.space = findAndRemoveMatches(space_regexp, classes);

    // create vector of classes for sizing
    SizingData sizing;
    sizing.width = findAndRemoveMatche(width_regexp, classes);
    sizing.minWidth = findAndRemoveMatche(minWidth_regex, classes);
    sizing.maxWidth = findAndRemoveMatche(maxWidth_regex, classes);
    sizing.height = findAndRemoveMatche(height_regexp, classes);
    sizing.minHeight = findAndRemoveMatche(minHeight_regex, classes);
    sizing.maxHeight = findAndRemoveMatche(maxHeight_regex, classes);

    // bool spacing_has
    

    // remove whitespace from start of classes string and store it in notFoundClasses
    // std::cout << "\n\n classes from Element Class Edditor not found classes :" << notFoundClasses << "\n\n";
    // std::cout << "background classes :\n";
    
    // std::cout << bgData.bg_attachment << "\n";
    // std::cout << bgData.bg_clip << "\n";
    // std::cout << bgData.bg_origin << "\n";
    // std::cout << bgData.bg_position << "\n";
    // std::cout << bgData.bg_repeat << "\n";
    // std::cout << bgData.bg_size << "\n";
    // std::cout << "<" << bgData.bg_image << ">\n";
   
   
   
   
    // std::cout << "<" << bgData.bg_color_class << ">\n";
    // std::cout << "<" << bgData.bg_color_via << ">\n";
    // std::cout << "<" << bgData.bg_color_to << ">\n";
    // std::cout << "<" << bgData.bg_color_from_step << ">\n";
    // std::cout << "<" << bgData.bg_color_via_step << ">\n";
    // std::cout << "<" << bgData.bg_color_to_step << ">\n";



    // std::cout << "\n\n"; 
    // resetStyles();
    
    spacingWidget_->setClasses(spacing);
    sizingWidget_->setClasses(sizing);
    backgroundWidget_->setClasses(bgData);

    spacingClasses = spacingWidget_->getStyles();
    sizingClasses = sizingWidget_->getStyles();
    backgroundClasses = backgroundWidget_->getStyles();

    notFoundClasses = std::regex_replace(classes, std::regex("^\\s+"), "");


}

std::string ElementClassEdditor::getStyles()
{
    std::string styles = "";
    styles += backgroundWidget_->getStyles() + " ";
    styles += sizingWidget_->getStyles() + " ";
    styles += spacingWidget_->getStyles() + " ";
    styles += notFoundClasses;
    return styles;
}

void ElementClassEdditor::resetStyles()
{
    backgroundWidget_->resetStyles();
    sizingWidget_->resetStyles();
    spacingWidget_->resetStyles();
}
