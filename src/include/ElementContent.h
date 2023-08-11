#pragma once
#include <Wt/WTemplate.h>
#include <Wt/WString.h>
#include <vector>
#include <Wt/WComboBox.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WCheckBox.h>
#include <Wt/WTextArea.h>
#include <Wt/WSignal.h>
#include "StylusTreeView.h"

#include "StylusTemplates.h" // for FolderData

class ElementContent : public Wt::WTemplate
{
public:
    ElementContent();;
    void setFoldersData(std::vector<FolderData> foldersData);
    Wt::WPushButton* button_save;
    
    Wt::WCheckBox* toggle_variable_content;
    Wt::WTextArea* element_content_textarea;
    
    Wt::WLineEdit* lineEdit_variableName;
    Wt::WComboBox* comboBox_folderName;
    Wt::WComboBox* comboBox_fileName;
    Wt::WComboBox* comboBox_message;
    Wt::WComboBox* comboBox_widgetType;

    void resetData();
    void setData(std::string contentText);
    std::string contentText_;
    
    std::string getData();
    Wt::Signal<>& contentChanged() { return contentChanged_; }
    Wt::Signal<>& refreshDevApp() { return refreshDevApp_; }
private:
    void processChange();
    void createDialogTextToTemplate(std::string newText, bool toText);

    std::vector<FolderData> foldersData_;
    void setFileNames(Wt::WString folderName);
    void setMessages(Wt::WString fileName);
    std::regex temp_pattern = std::regex("\\$\\{[\\w\\-.]+[ ]?(class=\"[^\"]*\")+[ ]?(folderName=\"[^\"]*\")+[ ]?(fileName=\"[^\"]*\")+[ ]?(messageId=\"[^\"]*\")+[ ]?(widgetType=\"[^\"]*\")\\}");
    
    Wt::Signal<> contentChanged_; 
    Wt::Signal<> refreshDevApp_;
};