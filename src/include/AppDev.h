#pragma once
#include <Wt/WTemplate.h>
#include <Wt/WString.h>
#include <vector>
#include <regex>
#include <string>

// this gets a template message id and returns all of his variables
std::vector<std::string> getWidgets(std::string messageId, std::regex template_pattern);


// this datastructure is for all the children or children of children
struct WidgetData {
    std::string variable;
    std::vector<WidgetData> children;
};

// main app dev
class AppDev : public Wt::WTemplate
{
public:
    AppDev(std::string templateId);
private:
    WidgetData widgetData_;

};
