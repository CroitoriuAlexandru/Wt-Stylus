#include "include/StylusTemplatesWidget.h"
#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WPanel.h>
#include <Wt/WLineEdit.h>
#include <Wt/WMenu.h>
#include <Wt/WMenuItem.h>

#include <boost/filesystem.hpp>


StylusTemplatesWidget::StylusTemplatesWidget(std::shared_ptr<StylusState> stylusState)
    : Wt::WTemplate(Wt::WString::tr("stylus.templates.widget")),
    stylusState_(stylusState)
{
    
    setStyleClass("overflow-y-scroll");


    // add file btn
    auto add_xml_file_btn = bindWidget("add-xml-file-btn", std::make_unique<Wt::WPushButton>(tr("svg.plus") + " Add File"));
    add_xml_file_btn->setTextFormat(Wt::TextFormat::UnsafeXHTML);
    add_xml_file_btn->clicked().connect(this, &StylusTemplatesWidget::createFile);
    add_xml_file_btn->setStyleClass(Wt::WString::tr("button-dark") + "flex items-center justify-center bg-neutral-700 hover:bg-heutral-800");

    

    createMenu();
}

StylusTemplatesWidget::~StylusTemplatesWidget()
{

}


std::vector<XmlFileData> StylusTemplatesWidget::getXmlFilesData(const std::string& path)
{
    std::vector<XmlFileData> xmlFilesData;
    std::vector<std::string> fileNames;
    // Iterate over each file in the directory
    XmlFileData xmlFileData;
    for (const auto& entry : boost::filesystem::directory_iterator(path)) {
        if (boost::filesystem::is_regular_file(entry)) {
            fileNames.push_back(entry.path().filename().string());
            xmlFileData.fileName = entry.path().filename().string();
            xmlFileData.messages = getXmlFileMessages(xml_folder_path + xmlFileData.fileName);
        }
        xmlFilesData.push_back(xmlFileData);
    }
    return xmlFilesData;
}

std::vector<std::string> StylusTemplatesWidget::getXmlFileMessages(const std::string& path)
{
    std::vector<std::string> messages;

    tinyxml2::XMLDocument doc;
    auto result = doc.LoadFile(path.c_str());
	if(result != tinyxml2::XML_SUCCESS){
		std::cout << "\n\n error opening document of the message template \n\n";
	}
    tinyxml2::XMLNode* root = doc.FirstChildElement("messages");
    if(root == nullptr){
        std::cout << "\n\n error opening messages in witch the template-mesage stay \n\n";
    }
    tinyxml2::XMLElement* message = root->FirstChildElement("message");
    while(message != nullptr){
        messages.push_back(message->Attribute("id"));
        message = message->NextSiblingElement("message");
    }
    return messages;
}

void StylusTemplatesWidget::createMenu()
{
    xml_files_data_ = getXmlFilesData(xml_folder_path);
    auto menu_content = bindWidget("contents", std::make_unique<Wt::WContainerWidget>());
    // iterate overvector xml_files_data_
    for(const auto fileData : xml_files_data_)
    {
        auto panel = menu_content->addWidget(std::make_unique<Wt::WPanel>());
        panel->setTitle(fileData.fileName);
        panel->addStyleClass("border border-solid border-gray-100 rounded-md m-1");
        panel->setCollapsible(true);
        panel->setCollapsed(true);
        panel->titleBarWidget()->setStyleClass(tr("stylus-panel-titlebar"));
        auto delete_file_btn = panel->titleBarWidget()->addWidget(std::make_unique<Wt::WPushButton>(tr("svg.trash")));
        delete_file_btn->setStyleClass("btn p-1 m-1 ms-auto");
        delete_file_btn->setTextFormat(Wt::TextFormat::UnsafeXHTML);
        delete_file_btn->doubleClicked().connect([=](){
            deleteFile(fileData.fileName);
        });

        auto add_message_btn = panel->titleBarWidget()->addWidget(std::make_unique<Wt::WPushButton>(tr("svg.plus")));
        add_message_btn->setStyleClass("btn p-1 m-1");
        add_message_btn->setTextFormat(Wt::TextFormat::UnsafeXHTML);
        add_message_btn->doubleClicked().connect([=](){
            addMessageTemplate(fileData.fileName);
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
                deleteMessageTemplate(fileData.fileName, message);
            });

            auto open_edditor_btn = file_item->bindWidget("svg.pencil", std::make_unique<Wt::WPushButton>(tr("svg.pencil")));
            open_edditor_btn->setTextFormat(Wt::TextFormat::UnsafeXHTML);
            open_edditor_btn->doubleClicked().connect([=](){

            auto fileName = fileData.fileName;
            auto messageId = message;
            templateSelected_.emit(fileName, messageId);

            });

        }
    }
}

bool StylusTemplatesWidget::checkIfTemplateExists(std::string fileName, std::string templateName)
{
    bool exists = false;
    std::cout << "\n\n" << fileName << "\n\n";
    std::cout << "\n\n" << templateName << "\n\n";
    for(const auto fileData : xml_files_data_)
    {
        if(fileData.fileName == fileName){
            for(const auto message : fileData.messages)
            {
                if(message == templateName){
                    return true;
                }
            }
        }
    }


    return exists;
}

// get the correct message from the xml file and template id (message id)
bool StylusTemplatesWidget::parseMessageAndDoc(std::string fileName, std::string tempMessageId)
{
    bool response = false;
    if(checkIfTemplateExists(fileName, tempMessageId) == false){
        std::cout << "\n\n StylusTemplatesWidget::parseMessageAndDoc error template does not exist \n\n";
        return false;
    }
    try{

        std::string path = xml_folder_path + fileName;
        std::cout << "\n StylusTemplatesWidget::parseMessageAndDoc with path " << path << "\n";
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
        removeTextBetweenElements(stylusState_->selectedTemplate);
        response = true;
    }catch(...){
        std::cout << "\n\n StylusTemplatesWidget::parseMessageAndDoc error \n\n";
        response = false;
    }
    return response;
}

void StylusTemplatesWidget::createFile()
{
    auto dialog = Wt::WApplication::instance()->root()->addChild(std::make_unique<Wt::WDialog>("File Name ?"));
    dialog->setStyleClass("p-0");
    dialog->contents()->setStyleClass("flex");
    dialog->titleBar()->clear();
    dialog->setOffsets(20, Wt::Side::Top);
    dialog->rejectWhenEscapePressed();
    auto input = dialog->contents()->addWidget(std::make_unique<Wt::WLineEdit>());
    input->setPlaceholderText("File Name");
    input->setFocus();
    input->setStyleClass("input-style-1 text-md");
    input->enterPressed().connect([=](){
        if(input->text().toUTF8() != ""){
            dialog->accept();
        }else {
            input->addStyleClass("bg-red-100");
            dialog->contents()->addWidget(std::make_unique<Wt::WText>("Please enter a file name"));
            
        }
    });

    dialog->finished().connect([=](){
        if(dialog->result() == Wt::DialogCode::Accepted){
            std::ofstream file;
            std::string filePath = xml_folder_path + input->text().toUTF8() + ".xml";
            file.open(filePath);
            if(file.is_open()){
                file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
                file << "<messages>\n";
                file << "</messages>\n";
                file.close();
                xml_files_data_ = getXmlFilesData(xml_folder_path);
                createMenu();
            }else {
                std::cout << "\n\n error creating file \n\n";
            }
        }
    });
    dialog->animateShow(Wt::WAnimation(Wt::AnimationEffect::Fade, Wt::TimingFunction::EaseInOut, 200));
}

void StylusTemplatesWidget::deleteFile(std::string fileName)
{
    std::string filePath = xml_folder_path + fileName;
    
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
            std::cout << "\n\n" << filePath << "\n\n";
            if (std::remove(filePath.c_str()) != 0) {
                std::cout << "\n\nFailed to delete the file\n\n";
            }
            else {
                std::cout << "\n\nFile successfully deleted\n\n";
                createMenu();
            }
        }
    });
    dialog->animateShow(Wt::WAnimation(Wt::AnimationEffect::Fade, Wt::TimingFunction::EaseInOut, 200));
}

void StylusTemplatesWidget::deleteMessageTemplate(std::string fileName, std::string tempMessageId)
{
    tinyxml2::XMLDocument doc;
    auto result = doc.LoadFile((xml_folder_path + fileName).c_str());
    if(result != tinyxml2::XML_SUCCESS){
        std::cout << "\n\n error opening document of the message template \n\n";
        auto dialog = Wt::WApplication::instance()->root()->addChild(std::make_unique<Wt::WDialog>("Error"));
        dialog->rejectWhenEscapePressed();
        dialog->contents()->addWidget(std::make_unique<Wt::WText>("Error opening document of the message template"));
        return;
    }
    auto messages = doc.FirstChildElement("messages");
    auto messageTemplate = messages->FirstChildElement("message");
    while(messageTemplate != nullptr){
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
    doc.SaveFile((xml_folder_path + fileName).c_str());
    createMenu();
}

void StylusTemplatesWidget::addMessageTemplate(std::string fileName)
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
            auto result = doc.LoadFile((xml_folder_path + fileName).c_str());
            if(result != tinyxml2::XML_SUCCESS){
                std::cout << "\n\n error opening document of the message template \n\n";
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


void StylusTemplatesWidget::removeTextBetweenElements(tinyxml2::XMLNode* node) {
    if (node == nullptr) {
        return;
    }

    tinyxml2::XMLNode* child = node->FirstChild();
    while (child != nullptr) {
        if (child->ToElement() != nullptr) {
            // Recursively process child elements
            removeTextBetweenElements(child);

            // Add class and text value if they don't exist
            tinyxml2::XMLElement* element = child->ToElement();
            if (element->Attribute("class") == nullptr) {
                element->SetAttribute("class", "");
           }

            // Add content if the element is not self-closing
            // if (!element->NoChildren()) {
            //     tinyxml2::XMLNode* content = element->FirstChild();
            //     if (content == nullptr) {
            //         element->InsertFirstChild(element->GetDocument()->NewText(""));
            //     }
            // }
        } else if (child->ToText() != nullptr) {
            // Remove the text node if it's not inside an element
            tinyxml2::XMLNode* parent = child->Parent();
            if (parent != nullptr && parent->ToElement() == nullptr) {
                parent->DeleteChild(child);
            }
        }
        child = child->NextSibling();
    }
}
