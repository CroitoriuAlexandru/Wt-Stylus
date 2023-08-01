#pragma once
#include <Wt/WTemplate.h>
#include <Wt/WString.h>
#include <vector>
#include <Wt/WComboBox.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>

#include "StylusTemplates.h" // for FolderData

class VariableConfigurationWidget : public Wt::WTemplate
{
public:
    VariableConfigurationWidget(std::vector<FolderData> foldersData);
    
    Wt::WPushButton* button_save;
    Wt::WLineEdit* lineEdit_variableName;
    Wt::WComboBox* comboBox_folderName;
    Wt::WComboBox* comboBox_fileName;
    Wt::WComboBox* comboBox_message;
    Wt::WComboBox* comboBox_widgetType;

    void setData(std::string variableText);
    void resetData();
    Wt::Signal<>& variableSaved() { return variableSaved_; }
    std::string getData();
private:
    std::vector<FolderData> foldersData_;
    void setFileNames(Wt::WString folderName);
    void setMessages(Wt::WString fileName);
    
    Wt::Signal<> variableSaved_;
};