#pragma once
#include "StylusTreeView.h"
#include <Wt/WMessageResourceBundle.h>

#include <Wt/WDialog.h>
#include <Wt/WTemplate.h>
#include <Wt/WSignal.h>
#include "tinyxml2.h"
#include <vector>

struct XmlFileData {
    // std::string folderName;
    std::string fileName;
    std::vector<std::string> messages;
};

struct FolderData {
    std::string folderName;
    std::vector<XmlFileData> xmlFiles;
};

class StylusTemplatesWidget : public Wt::WTemplate
{
public:
    StylusTemplatesWidget(std::string templatesPath, std::shared_ptr<StylusState> stylusState);
    ~StylusTemplatesWidget();
    Wt::Signal<std::string, std::string, std::string, std::string>& templateSelected() { return templateSelected_; };
    bool parseMessageAndDoc(std::string folderName, std::string fileName, std::string tempMessageId);
    
    std::vector<FolderData> folders_data_;
    std::string xml_folder_path;
    
private:
    std::shared_ptr<StylusState> stylusState_;
    std::unique_ptr<Wt::WPanel> createPanel(std::string title);
    void setFilePanel(Wt::WPanel* panel, std::string folderName, XmlFileData fileData);

    void createMenu();
    bool checkIfFileExists(std::string folderName, std::string fileName);
    void createFile(std::string folderName);
    void deleteFile(std::string folderName, std::string fileName);
    void createFolder();
    void deleteFolder(std::string folderName);
    void deleteFolderAndFiles(std::string folderName);
    void deleteMessageTemplate(std::string fileName, std::string tempMessageId);
    void addMessageTemplate(std::string foldeName, std::string fileName);
    void removeTextBetweenElements(tinyxml2::XMLNode* node);
    
    std::vector<FolderData> getFoldersData(std::string folderPath);
    std::vector<XmlFileData> getXmlFilesData(std::string folderPath);
    std::vector<std::string> getXmlFileMessages(std::string folderPath, std::string fileName);
    Wt::Signal<std::string, std::string, std::string, std::string> templateSelected_;

};