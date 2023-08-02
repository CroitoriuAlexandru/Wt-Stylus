#include "include/ElementClassEdditor.h"
#include "include/TailwindRegexp.h"
#include <Wt/WApplication.h>
#include <Wt/WAnimation.h>

std::vector<std::string> findAndRemoveMatches(std::regex regex, std::string& str) {
    
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

std::string findAndRemoveMatche(std::regex regex, std::string& str) {
        
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

    auto spacing_btn_display = bindWidget("spacing-display-button", std::make_unique<Wt::WPushButton>("Spacing"));
    auto sizing_btn_display = bindWidget("sizing-display-button", std::make_unique<Wt::WPushButton>("Sizing"));
    auto background_btn_display = bindWidget("background-display-button", std::make_unique<Wt::WPushButton>("Background"));

    auto btns_styles = Wt::WString::tr("button-stylus-display");
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
    
    spacingWidget_->styleChanged().connect(this, [=](){ styleChanged_.emit(getStyles()); });
    sizingWidget_->styleChanged().connect(this, [=](){ styleChanged_.emit(getStyles()); });
    backgroundWidget_->styleChanged().connect(this, [=](){ styleChanged_.emit(getStyles());});

    spacing_btn_display->clicked().connect(spacingWidget_, [=](){
        if(spacingWidget_->isVisible()){
            spacingWidget_->animateHide(animation);
        }else{
            spacingWidget_->animateShow(animation);
        }
    });

    sizing_btn_display->clicked().connect(sizingWidget_, [=](){
        if(sizingWidget_->isVisible()){
            sizingWidget_->animateHide(animation);
        }else{
            sizingWidget_->animateShow(animation);
        }
    });

    background_btn_display->clicked().connect(backgroundWidget_, [=](){
        if(backgroundWidget_->isVisible()){
            backgroundWidget_->animateHide(animation);
        }else{
            backgroundWidget_->animateShow(animation);
        }
    });

}

void ElementClassEdditor::setStyleClasses(std::string classes)
{
    // clean any multiple whitespaces from the string
    classes = std::regex_replace(classes, std::regex("\\s+"), " ");
    // std::cout << "\n\n classes from Element Class Edditor :" << classes << "\n\n";
    // create vector of classes for spacing
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

    // create vector of classes for background
    BackgroundData bgData;
    bgData.bg_attachment = findAndRemoveMatche(background_attachment_regex, classes);
    bgData.bg_clip = findAndRemoveMatche(background_clip_regex, classes);
    bgData.bg_origin = findAndRemoveMatche(background_origin_regex, classes);
    bgData.bg_position = findAndRemoveMatche(background_position_regex, classes);
    bgData.bg_repeat = findAndRemoveMatche(background_repeat_regex, classes);
    bgData.bg_size = findAndRemoveMatche(background_size_regex, classes);

    
    bgData.bg_image = findAndRemoveMatche(background_image_regex, classes);
    if(bgData.bg_image != ""){
        bgData.bg_image = findAndRemoveMatche(background_color_from_regex, classes);
        bgData.bg_color_via = findAndRemoveMatche(background_color_via_regex, classes);
        bgData.bg_color_to = findAndRemoveMatche(background_color_to_regex, classes);
    }else {
        bgData.bg_color_class = findAndRemoveMatche(background_color_regexp, classes);
    }
    
    // remove whitespace from start of classes string and store it in notFoundClasses
    notFoundClasses = std::regex_replace(classes, std::regex("^\\s+"), "");

    // console values
    // std::cout << "padding classes: <";
    // for (auto& paddingClass : spacing.padding) {
    //     std::cout << paddingClass << ",";
    // }
    // std::cout << ">\nmargin classes: <";
    // for (auto& marginClass : spacing.margin) {
    //     std::cout << marginClass << ",";
    // }
    // std::cout << ">\nspacing classes: <";
    // for (auto& spacingClass : spacing.space) {
    //     std::cout << spacingClass << ",";
    // }
    // std::cout << ">\nwidth: <" << sizing.width << ">\n";
    // std::cout << "min width: <" << sizing.minWidth << ">\n";
    // std::cout << "max width: <" << sizing.maxWidth << ">\n";
    // std::cout << "height: <" << sizing.height << ">\n";
    // std::cout << "min height: <" << sizing.minHeight << ">\n";
    // std::cout << "max height: <" << sizing.maxHeight << ">\n";
    // std::cout << "\n\n";
    // std::cout << "\n remaining classes :"<< notFoundClasses << "\n\n -------------------";


    resetStyles();

    spacingWidget_->setClasses(spacing);
    sizingWidget_->setClasses(sizing);
    backgroundWidget_->setClasses(bgData);

}

std::string ElementClassEdditor::getStyles()
{
    std::string styles = spacingWidget_->getStyles() + " ";
    styles += sizingWidget_->getStyles() + " ";
    styles += backgroundWidget_->getStyles() + " ";
    styles += notFoundClasses;
    return styles;
}

void ElementClassEdditor::resetStyles()
{
    sizingWidget_->resetStyles();
    spacingWidget_->resetStyles();
    backgroundWidget_->resetStyles();
}
