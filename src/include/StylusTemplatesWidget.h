#pragma once
#include "StylusTreeView.h"

#include <Wt/WDialog.h>
#include <Wt/WTemplate.h>
#include <Wt/WSignal.h>
#include "tinyxml2.h"
#include <vector>

struct XmlFileData {
    std::string fileName;
    std::vector<std::string> messages;
};

class StylusTemplatesWidget : public Wt::WTemplate
{
public:
    StylusTemplatesWidget(std::shared_ptr<StylusState> stylusState);
    ~StylusTemplatesWidget();
    Wt::Signal<std::string, std::string>& templateSelected() { return templateSelected_; };
    bool checkIfTemplateExists(std::string fileName, std::string templateName);
    bool parseMessageAndDoc(std::string fileName, std::string tempMessageId);
private:
    std::string xml_folder_path = "resources/xml/";
    std::shared_ptr<StylusState> stylusState_;
    void createMenu();
    void createFile();
    void deleteFile(std::string fileName);
    void deleteMessageTemplate(std::string fileName, std::string tempMessageId);
    void addMessageTemplate(std::string fileName);
    void removeTextBetweenElements(tinyxml2::XMLNode* node);

    std::vector<XmlFileData> getXmlFilesData(const std::string& path);
    std::vector<std::string> getXmlFileMessages(const std::string& path);
    std::vector<XmlFileData> xml_files_data_;

    Wt::Signal<std::string, std::string> templateSelected_;

};