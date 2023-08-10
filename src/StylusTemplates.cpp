#include "include/StylusTemplates.h"
#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WPanel.h>
#include <Wt/WLineEdit.h>
#include <Wt/WMenu.h>
#include <Wt/WMenuItem.h>

#include <boost/filesystem.hpp>

StylusTemplatesWidget::StylusTemplatesWidget(std::string templatesPath, std::shared_ptr<StylusState> stylusState)
    : Wt::WTemplate(Wt::WString::tr("stylus.templates.widget")),
    stylusState_(stylusState),
    xml_folder_path(templatesPath)
{
    
    createMenu();

    // add file btn
    auto addFolderBtn = bindWidget("add-folder-btn", std::make_unique<Wt::WPushButton>());
    addFolderBtn->clicked().connect(this, [=](){ 
        std::cout << "\n\n addFolderBtn clicked \n\n";
        createFolder(); });

    // add file btn
    auto addFileBtn = bindWidget("add-xml-file-btn", std::make_unique<Wt::WPushButton>());
    addFileBtn->clicked().connect(this, [=](){ 
        std::cout << "\n\n addFileBtn clicked \n\n";
        createFile(""); } );

}

StylusTemplatesWidget::~StylusTemplatesWidget()
{

}

std::vector<FolderData> StylusTemplatesWidget::getFoldersData(std::string folderPath)
{
    std::vector<FolderData> foldersData;
    // std::cout << "\n\n getFoldersData path <" << folderPath << ">\n";
    // Iterate over each file in the directory


    // files in the root folder
    FolderData folderData;
    folderData.folderName = "";
    for (const auto& entry : boost::filesystem::directory_iterator(folderPath)) {
        if (boost::filesystem::is_regular_file(entry)) {

            // check to see if it's an xml file
            if (entry.path().extension() == ".xml") {
                // std::cout << "\n -------------------------\n";
                XmlFileData xmlFileData;
                xmlFileData.fileName = entry.path().filename().string();
                xmlFileData.messages = getXmlFileMessages(folderPath, xmlFileData.fileName);
                folderData.xmlFiles.push_back(xmlFileData);
            }
        }
    }
    // folders from root folder
    foldersData.push_back(folderData);
    for (const auto& entry : boost::filesystem::directory_iterator(folderPath)) {
        FolderData folderData;
        if (boost::filesystem::is_directory(entry)) {
            folderData.folderName = entry.path().filename().string();
            folderData.xmlFiles = getXmlFilesData(xml_folder_path + folderData.folderName + "/");
            foldersData.push_back(folderData);
        } 
    }



    // for (const auto& folder : foldersData) {
    //     std::cout << "\n\nfolder <" << folder.folderName << ">\n";
    //     for (const auto& file : folder.xmlFiles) {
    //         std::cout << " file <" << file.fileName << ">\n";
    //         for (const auto& message : file.messages) {
    //             std::cout << "  message <" << message << ">\n";
    //         }
    //     }
    //     std::cout << "\n";
    // }
    return foldersData;
}

std::vector<XmlFileData> StylusTemplatesWidget::getXmlFilesData(std::string folderPath)
{
    // std::cout << "\n std::vector<XmlFileData> StylusTemplatesWidget::getXmlFilesData(std::string folderPath) ------------------ \n";
    std::vector<XmlFileData> xmlFilesData;
    std::vector<std::string> fileNames;
    // Iterate over each file in the directory
    // std::cout << "\n\n path " << folderPath << "\n\n";
    XmlFileData xmlFileData;
    for (const auto& entry : boost::filesystem::directory_iterator(folderPath)) {
        // check to see if its an xml file or a folder
        if (boost::filesystem::is_regular_file(entry) && entry.path().extension() == ".xml") {
            fileNames.push_back(entry.path().filename().string());
            xmlFileData.fileName = entry.path().filename().string();
            xmlFileData.messages = getXmlFileMessages(folderPath, xmlFileData.fileName);
        }
        // std::cout << "\n\n file name " << xmlFileData.fileName << "\n\n";
        xmlFilesData.push_back(xmlFileData);
    }
    return xmlFilesData;
}


std::vector<std::string> StylusTemplatesWidget::getXmlFileMessages(std::string folderPath, std::string fileName)
{
    // std::cout << "\n\n std::vector<std::string> StylusTemplatesWidget::getXmlFileMessages(std::string folderPath, std::string fileName) ------------------ \n";
    std::vector<std::string> messages;
    tinyxml2::XMLDocument doc;
    auto path = folderPath + fileName;
    auto result = doc.LoadFile(path.c_str());
	if(result != tinyxml2::XML_SUCCESS){
		std::cout << "\n\n error opening document of the message template \n";
        std::cout << "path " << path << "\n\n";
	}
    tinyxml2::XMLNode* root = doc.FirstChildElement("messages");
    if(root == nullptr){
        std::cout << "\n\n error opening messages in witch the template-mesage stay \n";
        std::cout << "path " << path << "\n\n";
    }
    tinyxml2::XMLElement* message = root->FirstChildElement("message");
    while(message != nullptr){
        messages.push_back(message->Attribute("id"));
        message = message->NextSiblingElement("message");
    }
    return messages;
}

std::unique_ptr<Wt::WPanel> StylusTemplatesWidget::createPanel(std::string title)
{
    std::unique_ptr<Wt::WPanel> panel = std::make_unique<Wt::WPanel>();
    panel->setTitle(title);
    //  pl-1.5 pr-0.5 bg-neutral-700 text-neutral-200
    panel->addStyleClass("!border-x-0 !border-t-0 !border-b-2 border-neutral-900 bg-neutral-700 text-neutral-200 !border-colapse");
    panel->setCollapsible(true);
    panel->setCollapsed(true);
    return panel;
}

void StylusTemplatesWidget::setFilePanel(Wt::WPanel* panel, std::string folderName, XmlFileData fileData)
{
    auto delete_file_btn = panel->titleBarWidget()->addWidget(std::make_unique<Wt::WPushButton>(tr("svg.trash")));
    delete_file_btn->setStyleClass("p-1 m-1 ms-auto");
    delete_file_btn->setTextFormat(Wt::TextFormat::UnsafeXHTML);
    delete_file_btn->doubleClicked().connect([=](){
        deleteFile(folderName, fileData.fileName);
    });

    auto add_message_btn = panel->titleBarWidget()->addWidget(std::make_unique<Wt::WPushButton>(tr("svg.plus")));
    add_message_btn->setStyleClass("p-1 m-1");
    add_message_btn->setTextFormat(Wt::TextFormat::UnsafeXHTML);
    add_message_btn->doubleClicked().connect([=](){
        addMessageTemplate(folderName, fileData.fileName);
    });

    Wt::WAnimation animation(Wt::AnimationEffect::SlideInFromTop, Wt::TimingFunction::EaseOut, 100);
    panel->setAnimation(animation);
    
    auto messages_display = panel->setCentralWidget(std::make_unique<Wt::WContainerWidget>());
    messages_display->setStyleClass(tr("stylus-panel-content"));
    for(const auto message : fileData.messages)
    {
        auto file_item = messages_display->addWidget(std::make_unique<Wt::WTemplate>(tr("stylus.templates.folder.item")));
        file_item->bindWidget("title", std::make_unique<Wt::WText>(message));
        
        auto del_message_btn = file_item->bindWidget("svg.trash", std::make_unique<Wt::WPushButton>(tr("svg.trash")));
        del_message_btn->setTextFormat(Wt::TextFormat::UnsafeXHTML);
        del_message_btn->doubleClicked().connect([=](){
            deleteMessageTemplate(folderName, fileData.fileName, message);
        });

        auto open_edditor_btn = file_item->bindWidget("svg.pencil", std::make_unique<Wt::WPushButton>(tr("svg.pencil")));
        open_edditor_btn->setTextFormat(Wt::TextFormat::UnsafeXHTML);
        open_edditor_btn->doubleClicked().connect([=](){
            
            auto fileName = fileData.fileName;
            auto messageId = message;
            templateSelected_.emit(folderName, fileName, messageId, "template", false);
        });
    }
}


void StylusTemplatesWidget::createMenu()
{
    folders_data_ = getFoldersData(xml_folder_path);
    auto contents_folders = bindWidget("contents-folders", std::make_unique<Wt::WContainerWidget>());
    auto contents_files = bindWidget("contents-files", std::make_unique<Wt::WContainerWidget>());
    contents_folders->setStyleClass("bg-neutral-700 mb-12");
    contents_files->setStyleClass("bg-neutral-700");
    
    for(auto folderData : folders_data_)
    {
        if(folderData.folderName == "")
        {
            for(auto fileData : folderData.xmlFiles)
            {
                auto panel = contents_files->addWidget(std::move(createPanel(fileData.fileName)));
                panel->titleBarWidget()->setStyleClass(tr("stylus-panel-titlebar-file"));
                setFilePanel(panel,folderData.folderName , fileData);
            }
        }else {
            // std::cout << "\n\n folder name " << folderData.folderName << "------------------------------\n\n";
            // std::cout << "\n\n folder name " << folderData.folderName << "\n\n";
            auto panel = contents_folders->addWidget(std::move(createPanel(folderData.folderName)));
            panel->titleBarWidget()->setStyleClass(tr("stylus-panel-titlebar-folder"));
            auto delete_file_btn = panel->titleBarWidget()->addWidget(std::make_unique<Wt::WPushButton>(tr("svg.trash")));
            delete_file_btn->setStyleClass("p-1 m-1 ms-auto");
            delete_file_btn->setTextFormat(Wt::TextFormat::UnsafeXHTML);
            delete_file_btn->doubleClicked().connect([=](){
                deleteFolder(folderData.folderName);
            });

            auto addFileBtn = panel->titleBarWidget()->addWidget(std::make_unique<Wt::WPushButton>());
            addFileBtn->setStyleClass("bg-[url(resources/icons/add-file.svg)] !p-2 m-1.5 bg-cover");
            addFileBtn->setToolTip("Add File");
            addFileBtn->setTextFormat(Wt::TextFormat::UnsafeXHTML);
            addFileBtn->doubleClicked().connect([=](){
                createFile(folderData.folderName);
            });
            Wt::WAnimation animation(Wt::AnimationEffect::SlideInFromTop, Wt::TimingFunction::EaseOut, 100);
            panel->setAnimation(animation); 
            auto panel_central = panel->setCentralWidget(std::make_unique<Wt::WContainerWidget>());
            for(auto fileData : folderData.xmlFiles)
            {
                auto file_iten_panel = panel_central->addWidget(std::move(createPanel(fileData.fileName)));
                setFilePanel(file_iten_panel, folderData.folderName, fileData);
                file_iten_panel->titleBarWidget()->setStyleClass(tr("stylus-panel-titlebar-file"));
            }
          
        }

    }

}

bool StylusTemplatesWidget::checkIfFileExists(std::string folderName, std::string fileName)
{
    bool response = false;
    for(const auto fileData : folders_data_)
    {
        if(folderName == fileData.folderName){
            for(const auto xmlFileData : fileData.xmlFiles){
                // std::cout << "\n\n xmlFileData.fileName " << xmlFileData.fileName << "\n\n";
                // std::cout << "\n\n fileName " << fileName << "\n\n";
                if(fileName == xmlFileData.fileName){
                    response = true;
                }
            }
        }
    }
    return response;
}


// get the correct message from the xml file and template id (message id)
bool StylusTemplatesWidget::parseMessageAndDoc(std::string folderName, std::string fileName, std::string tempMessageId)
{
    bool response = checkIfFileExists(folderName, fileName);

    stylusState_->doc.Clear();
    stylusState_->selectedTemplate = nullptr;
    stylusState_->selectedElement = nullptr;
    

    // check if file exists
    if(!response) {
        std::cout << "\n\n StylusTemplatesWidget::parseMessageAndDoc error template does not exist \n\n";
    return response;
    }

    try{
        std::string path; 
        if(folderName == ""){
            path = xml_folder_path + fileName;
        }else {
            path = xml_folder_path + folderName + "/" + fileName;
        }
        // std::cout << "\n\n parseMessageAndDoc  " << path << "\n";
        auto result = stylusState_->doc.LoadFile(path.c_str());
        stylusState_->filePath = path;
        if(result != tinyxml2::XML_SUCCESS){
            std::cout << "\n StylusTemplatesWidget::parseMessageAndDoc error opening xml file --- ";
            return false;
        }
        tinyxml2::XMLElement* root = stylusState_->doc.RootElement();
        if(!root) {
            std::cout << "\n\n StylusTemplatesWidget::parseMessageAndDoc error getting <messages> element \n\n";
            return false;
        }
        stylusState_->selectedTemplate = root->FirstChildElement("message");
        while(stylusState_->selectedTemplate->ToElement()->Attribute("id") != tempMessageId){
            stylusState_->selectedTemplate = stylusState_->selectedTemplate->NextSiblingElement("message");
        }
        // removeTextBetweenElements(stylusState_->selectedTemplate);
        response = true;
    }catch(...){
        std::cout << "\n\n StylusTemplatesWidget::parseMessageAndDoc error \n\n";
        response = false;
    }
    // std::cout << "\n\n parse succesfull \n\n";
    return response;
}

void StylusTemplatesWidget::createFile(std::string folderName)
{
    auto dialog = addChild(std::make_unique<Wt::WDialog>("File Name ?"));
    dialog->setStyleClass("p-0");
    dialog->contents()->setStyleClass("flex flex-col text-center px-4 py-2");
    dialog->titleBar()->clear();
    dialog->setOffsets(20, Wt::Side::Top);
    // dialog->setOffsets()
    dialog->rejectWhenEscapePressed();
    auto input = dialog->contents()->addWidget(std::make_unique<Wt::WLineEdit>());
    input->setPlaceholderText("File Name");
    input->setFocus();
    input->setStyleClass("input-style-1 text-md");
    input->enterPressed().connect([=](){
        auto fileName = input->text().toUTF8() + ".xml";
        if(fileName == ""){
            input->addStyleClass("bg-red-100");
            dialog->contents()->addWidget(std::make_unique<Wt::WText>("text cannot be empty"))->setStyleClass("text-red-500");
        }else if (fileName.find(' ') != std::string::npos) {
            input->addStyleClass("bg-red-100");
            dialog->contents()->addWidget(std::make_unique<Wt::WText>("No Spaces allowed"))->setStyleClass("text-red-500");
        }else if(checkIfFileExists(folderName, fileName)){
            std::cout << "\n\n file esists from create file \n\n";
            input->addStyleClass("bg-red-100");
            dialog->contents()->addWidget(std::make_unique<Wt::WText>("File name exists"))->setStyleClass("text-red-500");
        }else {
            dialog->accept();
        }
    });

    dialog->finished().connect([=](){
        if(dialog->result() == Wt::DialogCode::Accepted){

            std::ofstream file;
            std::string filePath = xml_folder_path + folderName + "/" + input->text().toUTF8() + ".xml";
            std::cout << "\n\n filePath " << filePath << "\n\n";
            file.open(filePath);
            if(file.is_open()){
                file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
                file << "<messages>\n";
                file << "</messages>\n";
                file.close();
                createMenu();
            }else {
                std::cout << "\n\n error creating file \n\n";
            }
        }
    });
    dialog->animateShow(Wt::WAnimation(Wt::AnimationEffect::Fade, Wt::TimingFunction::EaseInOut, 200));
}

void StylusTemplatesWidget::deleteFile(std::string folderName, std::string fileName)
{
    std::string filePath = xml_folder_path + folderName + "/" + fileName;
    
    auto dialog = Wt::WApplication::instance()->root()->addChild(std::make_unique<Wt::WDialog>("Are you sure ?"));
    dialog->rejectWhenEscapePressed();
    dialog->contents()->addWidget(std::make_unique<Wt::WText>(fileName));
    auto delete_btn = dialog->contents()->addWidget(std::make_unique<Wt::WPushButton>("Delete"));
    delete_btn->setStyleClass(Wt::WString::tr("button"));
    delete_btn->clicked().connect([=](){
        dialog->accept();
    });
    delete_btn->setFocus();
    dialog->finished().connect([=](){
        if(dialog->result() == Wt::DialogCode::Accepted){
            // remove .xml from filePath end
            // auto pos = filePath.find(".xml");
            // auto newPath = filePath.substr(0, pos);


            // std::cout << "\n\n" << newPath << "\n\n";
            if (std::remove(filePath.c_str()) != 0) {
                std::cout << "\n\nFailed to delete the file\n\n";
                std::cout << "\n\n" << filePath << "\n\n";
            }
            else {
                std::cout << "\n\nFile successfully deleted\n\n";
                createMenu();
            }
        }
    });
    dialog->animateShow(Wt::WAnimation(Wt::AnimationEffect::Fade, Wt::TimingFunction::EaseInOut, 200));
}

void StylusTemplatesWidget::createFolder()
{
    std::cout << "\n createFolder \n";
    auto dialog = Wt::WApplication::instance()->root()->addChild(std::make_unique<Wt::WDialog>("Folder Name ?"));
    dialog->setStyleClass("p-0");
    dialog->contents()->setStyleClass("flex flex-col text-center px-4 py-2");
    dialog->titleBar()->clear();
    dialog->setOffsets(20, Wt::Side::Top);
    dialog->rejectWhenEscapePressed();
    auto input = dialog->contents()->addWidget(std::make_unique<Wt::WLineEdit>());
    input->setPlaceholderText("Folder Name");
    input->setFocus();
    input->setStyleClass("input-style-1 text-md");
    input->enterPressed().connect([=](){
        auto folderName = input->text().toUTF8();
        if(folderName == ""){
            input->addStyleClass("bg-red-100");
            dialog->contents()->addWidget(std::make_unique<Wt::WText>("Please enter a Folder name"))->setStyleClass("text-red-500");
        }else if(folderName.find(' ') != std::string::npos){
            input->addStyleClass("bg-red-100");
            dialog->contents()->addWidget(std::make_unique<Wt::WText>("No Spaces allowed"))->setStyleClass("text-red-500");
        }else if (boost::filesystem::exists(xml_folder_path + folderName)){
            input->addStyleClass("bg-red-100");
            dialog->contents()->addWidget(std::make_unique<Wt::WText>("Folder name exists"))->setStyleClass("text-red-500");
        }else {
            dialog->accept();
        }
    });

      dialog->finished().connect([=](){
        if(dialog->result() == Wt::DialogCode::Accepted){
            boost::filesystem::path path(xml_folder_path + input->text().toUTF8());
            boost::system::error_code error;
            bool result = boost::filesystem::create_directory(path, error);
            if (!result) {
                std::cout << "Error creating folder: " << error.message() << std::endl;
            } 
            createMenu();
        }
    });
    dialog->animateShow(Wt::WAnimation(Wt::AnimationEffect::Fade, Wt::TimingFunction::EaseInOut, 200));
}

void StylusTemplatesWidget::deleteFolder(std::string folderName)
{
    auto dialog = Wt::WApplication::instance()->root()->addChild(std::make_unique<Wt::WDialog>("Are you sure ?"));
    dialog->rejectWhenEscapePressed();
    dialog->contents()->addWidget(std::make_unique<Wt::WText>(folderName));
    auto delete_btn = dialog->contents()->addWidget(std::make_unique<Wt::WPushButton>("Delete"));
    delete_btn->setStyleClass(Wt::WString::tr("button"));
    delete_btn->clicked().connect([=](){
        dialog->accept();
    });

    delete_btn->setFocus();
    dialog->finished().connect([=](){
        if(dialog->result() == Wt::DialogCode::Accepted){
            boost::filesystem::path path(xml_folder_path + folderName);
            boost::system::error_code error;
            bool result = boost::filesystem::remove(path, error);
            if (!result) {
                auto folderWithFiles_dialog = Wt::WApplication::instance()->root()->addChild(std::make_unique<Wt::WDialog>("Folder with files, do you wish to delete all the files ?"));
                folderWithFiles_dialog->rejectWhenEscapePressed();
                folderWithFiles_dialog->contents()->setStyleClass("flex flex-col p-2");
                folderWithFiles_dialog->contents()->addWidget(std::make_unique<Wt::WText>("Folder: " + folderName));
                folderWithFiles_dialog->contents()->addWidget(std::make_unique<Wt::WText>("Files: "));
                for(auto fileData : getXmlFilesData(xml_folder_path + folderName + "/")){
                    folderWithFiles_dialog->contents()->addWidget(std::make_unique<Wt::WText>(fileData.fileName));
                }
                auto delete_btn = folderWithFiles_dialog->contents()->addWidget(std::make_unique<Wt::WPushButton>("Delete"));
                delete_btn->setStyleClass(Wt::WString::tr("button"));
                delete_btn->clicked().connect([=](){
                    folderWithFiles_dialog->accept();
                });
                delete_btn->setFocus();
                folderWithFiles_dialog->finished().connect([=](){
                    if(folderWithFiles_dialog->result() == Wt::DialogCode::Accepted){
                        deleteFolderAndFiles(folderName);
                        createMenu();
                    }
                });
                folderWithFiles_dialog->animateShow(Wt::WAnimation(Wt::AnimationEffect::Fade, Wt::TimingFunction::EaseInOut, 200));
            }else {
                createMenu();
            }
        }
    });

    dialog->animateShow(Wt::WAnimation(Wt::AnimationEffect::Fade, Wt::TimingFunction::EaseInOut, 200));
}

void StylusTemplatesWidget::deleteFolderAndFiles(std::string folderName)
{
    boost::filesystem::path folderPath(xml_folder_path + folderName);
    boost::system::error_code error;

    // Check if the folder exists
    if (!boost::filesystem::exists(folderPath)) {
        std::cout << "Folder does not exist: " << folderPath << std::endl;
        return;
    }

    // Iterate over all files and subdirectories in the folder
    for (boost::filesystem::directory_iterator it(folderPath); it != boost::filesystem::directory_iterator(); ++it) {
        boost::filesystem::path currentPath = it->path();

        // Check if it's a file
        if (boost::filesystem::is_regular_file(currentPath)) {
            // Delete the file
            boost::filesystem::remove(currentPath, error);
            if (error) {
                std::cout << "Error deleting file: " << error.message() << std::endl;
            }
        } else if (boost::filesystem::is_directory(currentPath)) {
            // Delete the subdirectory and its files recursively
            deleteFolderAndFiles(currentPath.string());
        }
    }

    // Delete the folder itself
    boost::filesystem::remove(folderPath, error);
    if (error) {
        std::cout << "Error deleting folder: " << error.message() << std::endl;
    }
}

void StylusTemplatesWidget::deleteMessageTemplate(std::string foldeName, std::string fileName, std::string tempMessageId)
{
    tinyxml2::XMLDocument doc;
    auto result = doc.LoadFile((xml_folder_path + foldeName + "/" + fileName).c_str());
    if(result != tinyxml2::XML_SUCCESS){
        std::cout << "\n\n error opening document of the message template \n\n";
        auto dialog = Wt::WApplication::instance()->root()->addChild(std::make_unique<Wt::WDialog>("Error"));
        dialog->rejectWhenEscapePressed();
        dialog->contents()->addWidget(std::make_unique<Wt::WText>("Error opening document of the message template"));
        return;
    }
    auto messages = doc.FirstChildElement("messages");
    auto messageTemplate = messages->FirstChildElement("message");
    while(messageTemplate){
        if(messageTemplate->Attribute("id") == tempMessageId){
            auto dialog = Wt::WApplication::instance()->root()->addChild(std::make_unique<Wt::WDialog>("Are you sure ?"));
            dialog->rejectWhenEscapePressed();
            dialog->contents()->addWidget(std::make_unique<Wt::WText>(tempMessageId));
            auto delete_btn = dialog->contents()->addWidget(std::make_unique<Wt::WPushButton>("Delete"));
            delete_btn->setStyleClass("btn ");
            delete_btn->clicked().connect([=](){
                dialog->accept();
            });
            delete_btn->setFocus();
            dialog->finished().connect([=](){
                if(dialog->result() == Wt::DialogCode::Accepted){
                    messages->DeleteChild(messageTemplate);
                    createMenu();
                }
            });
            doc.SaveFile((xml_folder_path + fileName).c_str());
            dialog->animateShow(Wt::WAnimation(Wt::AnimationEffect::Fade, Wt::TimingFunction::EaseInOut, 200));
            break;
        }
        messageTemplate = messageTemplate->NextSiblingElement("message");
    }
    // doc.SaveFile((xml_folder_path + fileName).c_str());
    createMenu();
}

void StylusTemplatesWidget::addMessageTemplate(std::string foldeName, std::string fileName)
{
    auto dialog = Wt::WApplication::instance()->root()->addChild(std::make_unique<Wt::WDialog>("Message Id ?"));
    dialog->rejectWhenEscapePressed();
    auto input_message_id = dialog->contents()->addWidget(std::make_unique<Wt::WLineEdit>());
    input_message_id->setPlaceholderText("Message Id");
    input_message_id->setFocus();
    input_message_id->setStyleClass("input-style-1 text-md");
    input_message_id->enterPressed().connect([=](){
        if(input_message_id->text().toUTF8() != ""){
            dialog->accept();
        }else {
            input_message_id->addStyleClass("bg-red-100");
            dialog->contents()->addWidget(std::make_unique<Wt::WText>("Please enter a message id"));
            
        }
    });

    dialog->finished().connect([=](){
        if(dialog->result() == Wt::DialogCode::Accepted){
            tinyxml2::XMLDocument doc;
            auto result = doc.LoadFile((xml_folder_path + foldeName + "/" + fileName).c_str());
            if(result != tinyxml2::XML_SUCCESS){
                std::cout << "\n\n error opening document of the message template \n\n";
                std::cout << "path " << xml_folder_path + fileName << "\n\n";
                auto dialog = Wt::WApplication::instance()->root()->addChild(std::make_unique<Wt::WDialog>("Error"));
                dialog->rejectWhenEscapePressed();
                dialog->contents()->addWidget(std::make_unique<Wt::WText>("Error opening document of the message template"));
                return;
            }
            auto messages = doc.FirstChildElement("messages");
            auto messageTemplate = messages->FirstChildElement("message");
            while(messageTemplate != nullptr){
                if(messageTemplate->Attribute("id") == input_message_id->text().toUTF8()){
                    auto dialog = Wt::WApplication::instance()->root()->addChild(std::make_unique<Wt::WDialog>("Error"));
                    dialog->rejectWhenEscapePressed();
                    dialog->contents()->addWidget(std::make_unique<Wt::WText>("Message id already exists"));
                    return;
                }
                messageTemplate = messageTemplate->NextSiblingElement("message");
            }
            auto newMessage = messages->InsertNewChildElement("message");
            newMessage->SetAttribute("id", input_message_id->text().toUTF8().c_str());
            newMessage->SetText("");
            doc.SaveFile((xml_folder_path + fileName).c_str());
            createMenu();
        }
    });
    dialog->animateShow(Wt::WAnimation(Wt::AnimationEffect::Fade, Wt::TimingFunction::EaseInOut, 200));
}



// void StylusTemplatesWidget::removeTextBetweenElements(tinyxml2::XMLNode* node) {
//     if (node == nullptr) {
//         return;
//     }

//     tinyxml2::XMLNode* child = node->FirstChild();
//     while (child != nullptr) {
//         if (child->ToElement() != nullptr) {
//             // Recursively process child elements
//             removeTextBetweenElements(child);

//             // Add class and text value if they don't exist
//             tinyxml2::XMLElement* element = child->ToElement();
//             if (element->Attribute("class") == nullptr) {
//                 element->SetAttribute("class", "");
//             }

//             if (!element->NoChildren()) {
//                 tinyxml2::XMLNode* content = element->FirstChild();
//                 if (content == nullptr) {
//                     element->InsertFirstChild(element->GetDocument()->NewText(""));
//                 }
//             }

//         } else if (child->ToText() != nullptr) {
//             // Remove the text node if it's not inside an element
//             tinyxml2::XMLNode* parent = child->Parent();
//             if (parent != nullptr && parent->ToElement() == nullptr) {
//                 parent->DeleteChild(child);
//             }
//         }
//         child = child->NextSibling();
//     }
// }