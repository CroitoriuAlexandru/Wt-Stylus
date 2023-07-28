#pragma once
#include "StylusTreeView.h"
#include "ElementClassEdditor.h"
#include "StylusTemplatesWidget.h"

#include <Wt/WTextArea.h>
#include <Wt/WLineEdit.h>
#include <Wt/WString.h>
#include <Wt/WTreeNode.h>
#include <Wt/WTemplate.h>
#include "tinyxml2.h"
#include <Wt/WDialog.h>
#include <fstream>
#include <iostream>

class StylusEdditor : public Wt::WDialog
{
public:
    StylusEdditor();
    ~StylusEdditor();
    std::string cleanStringStartEnd(const std::string& input);
    void setTemplate(std::string fileName, std::string messageId);
private:
    std::shared_ptr<StylusState> stylusState_;
    ElementClassEdditor* elementClassEdditor_;
    StylusTemplatesWidget* stylus_templates_;
    Wt::WTextArea* element_content_textarea_;

    // Wt::WString sourcePath_ = "resources/xml/";

    // Wt::WString templateName_ = "";
    Wt::WTemplate* edditor_temp_;

    void createTitleBarControls();
    void createDialogTreeView();
    
    void nodeSelected(tinyxml2::XMLNode* node);
    void tempNodeSelected(tinyxml2::XMLNode* node);
    void updateDisplayElement(std::string classes, std::string content);
    
    void toggleOutline(bool on = true);
    bool outline_selected_on = true;    

    void saveStyles(std::string newStyles);

    void updateFile();
    void updateView();
    void dialogResized(int width, int height);
    int applicationWidthClass;
    std::unique_ptr<Wt::WPushButton> createThemeSwitcher();
};