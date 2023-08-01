#include "include/AppDev.h"

std::vector<std::string> getWidgets(std::string messageId)
{
    std::vector<std::string> tempVariables;
    std::regex template_pattern = std::regex("[\\w\\-.]+[ ]?(class=\"[^\"]*\")+[ ]?(folderName=\"[^\"]*\")+[ ]?(fileName=\"[^\"]*\")+[ ]?(messageId=\"[^\"]*\")+[ ]?(widgetType=\"[^\"]*\")");
    
    auto text = Wt::WString::tr(messageId);
    // get the template variables
    
    auto pos = text.toUTF8().find("${");
    auto pos2 = text.toUTF8().find("}");
    while(pos != std::string::npos){
        // get the variable
        std::string variable = text.toUTF8().substr(pos+2, pos2-pos-2);
        // check the variable with regex

        std::smatch match;
        auto result = std::regex_search(variable, match, template_pattern);
        if(result){ tempVariables.push_back(variable); }
        else { std::cout << "\n\n AppDev.cpp - getWidgets() no match: " << variable << "\n\n"; }

        // remove text until pos2+1
        text = text.toUTF8().substr(pos2+1);
        // find the next variable
        pos = text.toUTF8().find("${");
        pos2 = text.toUTF8().find("}");
    }

    return tempVariables;
}

AppDev::AppDev(std::string templateId)
    : WTemplate(tr(templateId))
{
    auto tempVariables = getWidgets(templateId);
    // std::cout << "\n\n";

    for(auto variable : tempVariables){
        std::string variableName = variable.substr(0, variable.find(" "));
        std::string variableType = variable.substr(variable.find("widgetType=\"") + 12, variable.find("\"", variable.find("widgetType=\"") + 12) - variable.find("widgetType=\"") - 12);
        std::string variableMessageId = variable.substr(variable.find("messageId=\"") + 11, variable.find("\"", variable.find("messageId=\"") + 11) - variable.find("messageId=\"") - 11);


        if(variableType.compare("template") == 0){
            bindWidget(variableName, std::make_unique<AppDev>(variableMessageId));
            // std::cout << "variable: " << variable << "\n";
            // std::cout << "variableName: " << variableName << "\n";
            // std::cout << "variableType: " << variableType << "\n";
            // std::cout << "variableMessageId: " << variableMessageId << "\n";
            continue;
        }   
    }
    // std::cout << "\n\n";
}
