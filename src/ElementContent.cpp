#include "include/ElementContent.h"
#include <Wt/WApplication.h>
#include <Wt/WString.h>

ElementContent::ElementContent()
    : WTemplate(tr("stylus.variable.configuration.template"))
{
    element_content_textarea = bindWidget("content-textarea", std::make_unique<Wt::WTextArea>());

    button_save = bindWidget("submit-btn", std::make_unique<Wt::WPushButton>("Save"));
    button_save->clicked().connect(this, &ElementContent::processChange);
    button_save->setStyleClass(Wt::WString::tr("button-dark"));

    bindEmpty("folder.name");
    bindEmpty("file.name");
    bindEmpty("message.id");
    bindEmpty("widget.type");
    bindEmpty("toggle-variable-content");
}


void ElementContent::setFoldersData(std::vector<FolderData> foldersData)
{
    foldersData_ = foldersData;
    toggle_variable_content = bindWidget("toggle-variable-content", std::make_unique<Wt::WCheckBox>("Toggle Variable Content"));
    
    lineEdit_variableName = bindWidget("variable.name", std::make_unique<Wt::WLineEdit>());
    comboBox_folderName = bindWidget("folder.name", std::make_unique<Wt::WComboBox>());
    comboBox_widgetType = bindWidget("widget.type", std::make_unique<Wt::WComboBox>());
    comboBox_fileName = bindWidget("file.name", std::make_unique<Wt::WComboBox>());
    comboBox_message = bindWidget("message.id", std::make_unique<Wt::WComboBox>());


     // set combo box values
    auto widgetTypes = { "template" };
    std::cout << "\n\n folders names";
    for(auto folders : foldersData){
        std::cout << "\n\nfolderName :<" << folders.folderName << ">\n\n";
        comboBox_folderName->addItem(folders.folderName);
    }
    std::cout << "end\n\n";

    for(auto files : foldersData[0].xmlFiles){
        comboBox_fileName->addItem(files.fileName);
    }
    for(auto message : foldersData[0].xmlFiles[0].messages){
        comboBox_message->addItem(message);
    }

    // widget type
    for(auto widgetType : widgetTypes){
        comboBox_widgetType->addItem(widgetType);
    }

    // signals
    comboBox_folderName->changed().connect([=](){ setFileNames(comboBox_folderName->currentText()); });
    comboBox_fileName->changed().connect([=](){ setMessages(comboBox_fileName->currentText()); });

    // set default values
    comboBox_folderName->setCurrentIndex(0);
    comboBox_folderName->changed().emit();

    toggle_variable_content->changed().connect(this, [=](){
        if(toggle_variable_content->isChecked()){
            setCondition("custom-template", true);
            element_content_textarea->setHidden(true);
        }else{
            setCondition("custom-template", false);
            element_content_textarea->setHidden(false);
        }
    });
}

void ElementContent::processChange()
{
    // std::cout << "\n\n ElementContent::processChange() --- \n";
    // std::cout << "ElementContent::processChange() --- contentText_ :<" << contentText_ << ">\n";
    // std::cout << "ElementContent::processChange() --- getData() :<" << getData() << ">\n\n";
    auto textData = getData();

    if(textData.compare(contentText_) == 0){
        std::cout << "\n\n ElementContent::processChange() --- no changes done ... \n\n";
        return;
    }

    // variable content else text content
    if(toggle_variable_content->isChecked()){
        // variable content was not a template
        if(lineEdit_variableName->text().empty() || textData.find(" ") == std::string::npos){
            std::cout << "\n\n ElementContent::processChange() --- variable name is empty \n\n";
            lineEdit_variableName->toggleStyleClass("bg-red-300", true, true);
            lineEdit_variableName->toggleStyleClass("text-black", true, true);
            lineEdit_variableName->setPlaceholderText("Variable name is required and canot have spaces");
            return;
        }else {
            lineEdit_variableName->toggleStyleClass("text-black", false, true);
            lineEdit_variableName->toggleStyleClass("bg-red-300", false, true);
            lineEdit_variableName->setPlaceholderText("");
        }
        if(!std::regex_match(contentText_, temp_pattern)){
            std::cout << "\n\n ElementContent::processChange() --- text to template \n\n";
            createDialogTextToTemplate(textData, true);
        }else {
            std::cout << "\n\n ElementContent::processChange() --- template to template \n\n";
            contentChanged_.emit();
            refreshDevApp_.emit();
        }
    }else {
        // text content was not a template
        if(std::regex_match(contentText_, temp_pattern)){
            std::cout << "\n\n ElementContent::processChange() --- template to text \n\n";
            createDialogTextToTemplate(textData, false);
        }else if(std::regex_match(textData, temp_pattern)){
            std::cout << "\n\n ElementContent::processChange() --- text to template - from  \n\n";
            createDialogTextToTemplate(textData, true);
        } else {
            std::cout << "\n\n ElementContent::processChange() --- text to text \n\n";
            contentChanged_.emit();
        } 
    }

}

void ElementContent::setData(std::string contentText)
{
    resetData();
    contentText_ = contentText;
    if(!std::regex_match(contentText, temp_pattern)){
        element_content_textarea->setText(contentText);
        toggle_variable_content->setChecked(false);
        toggle_variable_content->changed().emit();
        return;
    }else
    toggle_variable_content->setChecked(true);
    toggle_variable_content->changed().emit();

    std::size_t lastPos = 0;
	std::string variableName;
	std::string folderName;
	std::string fileName;
	std::string messageId;
	std::string widgetType;
	// ${test.test class="text-center p-2 m-2" fileName="fileName.xml" messageId="templateId"}
	// get  variableName + test.test
	std::size_t pos = std::string(contentText).find("${");
	variableName = std::string(contentText).substr(pos + 2, std::string(contentText).find(" ", pos) - pos - 2);
	// remove variableName from text
	std::string text = std::string(contentText).substr(pos + 2 + variableName.length() + 1);
	// remove class="" argument
	pos = text.find("class=\"");
	if(pos != std::string::npos){
		text = text.substr(0, pos) + text.substr(text.find("\"", pos + 7) + 2);
	}
	// remove folderName="" argument and place the value between "" in folderName
	pos = text.find("folderName=\"");
	if(pos != std::string::npos){
		folderName = text.substr(pos + 12, text.find("\"", pos + 12) - pos - 12);
		text = text.substr(0, pos) + text.substr(text.find("\"", pos + 12) + 2);
	}
	// remove fileName="" argument and place the value between "" in fileName
	pos = text.find("fileName=\"");
	if(pos != std::string::npos){
		fileName = text.substr(pos + 10, text.find("\"", pos + 10) - pos - 10);
		text = text.substr(0, pos) + text.substr(text.find("\"", pos + 10) + 2);
	}
	// remove messageId="" argument and place the value between "" in messageId
	pos = text.find("messageId=\"");
	if(pos != std::string::npos){
		messageId = text.substr(pos + 11, text.find("\"", pos + 11) - pos - 11);
		text = text.substr(0, pos) + text.substr(text.find("\"", pos + 11) + 2);
	}
	// remove widgetType="" argument and place the value between "" in widgetType
	pos = text.find("widgetType=\"");
	if(pos != std::string::npos){
		widgetType = text.substr(pos + 12, text.find("\"", pos + 12) - pos - 12);
		text = text.substr(0, pos) + text.substr(text.find("\"", pos + 12) + 2);
	}

    // std::cout << "\n\ntext :<" << text << ">\n\n";
	// std::cout << "\n\n variableName :<" << variableName << ">\n\n";
	// std::cout << "\n\n text :<" << text << ">\n\n";
	// std::cout << "\n\n folderName :<" << folderName << ">\n\n";
	// std::cout << "\n\n fileName :<" << fileName << ">\n\n";		
	// std::cout << "\n\n messageId :<" << messageId << ">\n\n";
	// std::cout << "\n\n widgetType :<" << widgetType << ">\n\n";

    lineEdit_variableName->setText(variableName);
    comboBox_folderName->setCurrentIndex(comboBox_folderName->findText(folderName));
    comboBox_fileName->setCurrentIndex(comboBox_fileName->findText(fileName));
    comboBox_message->setCurrentIndex(comboBox_message->findText(messageId));
    comboBox_widgetType->setCurrentIndex(comboBox_widgetType->findText(widgetType));

    // lineEdit_variableName->enterPressed().connect([=](){ variableChanged_.emit(getData()); });
    // comboBox_folderName->sactivated().connect([=](){ variableChanged_.emit(getData()); });
    // comboBox_fileName->sactivated().connect([=](){ variableChanged_.emit(getData()); });
    // comboBox_message->sactivated().connect([=](){ variableChanged_.emit(getData()); });
    // comboBox_widgetType->sactivated().connect([=](){ variableChanged_.emit(getData()); });

}


void ElementContent::setFileNames(Wt::WString folderName)
{
    // get the folder data
    FolderData folderData;
    for(auto folder : foldersData_){
        if(folder.folderName.compare(folderName.toUTF8().c_str()) == 0){
            folderData = folder;
            break;
        }
    }

    // set the file names
    comboBox_fileName->clear();
    for(auto fileData : folderData.xmlFiles){
        comboBox_fileName->addItem(fileData.fileName);
    }
}

void ElementContent::setMessages(Wt::WString fileName)
{
    // get the folder data
    FolderData folderData;
    for(auto folder : foldersData_){
        if(folder.folderName.compare(comboBox_folderName->currentText().toUTF8().c_str()) == 0){
            folderData = folder;
            break;
        }
    }

    // get the file data
    XmlFileData fileData;
    for(auto file : folderData.xmlFiles){
        if(file.fileName.compare(fileName.toUTF8().c_str()) == 0){
            fileData = file;
            break;
        }
    }

    // set the message ids
    comboBox_message->clear();
    for(auto message : fileData.messages){
        comboBox_message->addItem(message);
    }
}

void ElementContent::resetData()
{
    toggle_variable_content->setChecked(true);
    toggle_variable_content->changed().emit();
    element_content_textarea->setText("");
    lineEdit_variableName->setText("");
    comboBox_folderName->setCurrentIndex(0);
    comboBox_fileName->setCurrentIndex(0);
    comboBox_message->setCurrentIndex(0);
    comboBox_widgetType->setCurrentIndex(0);
}

std::string ElementContent::getData()
{
    std::string variableText;
    
    if(!toggle_variable_content->isChecked()){
        variableText = element_content_textarea->text().toUTF8();
    }else {
        variableText = "${" + lineEdit_variableName->text().toUTF8() + " ";
        variableText += "class=\"\" ";
        variableText += "folderName=\"" + comboBox_folderName->currentText().toUTF8() + "\" ";
        variableText += "fileName=\"" + comboBox_fileName->currentText().toUTF8() + "\" ";
        variableText += "messageId=\"" + comboBox_message->currentText().toUTF8() + "\" ";
        variableText += "widgetType=\"" + comboBox_widgetType->currentText().toUTF8() + "\"}";
    }
    return variableText;
}

void ElementContent::createDialogTextToTemplate(std::string newText, bool toText)
{
	auto dialog = Wt::WApplication::instance()->root()->addChild(std::make_unique<Wt::WDialog>());
	dialog->setModal(false);
	dialog->setMovable(false);
	dialog->setResizable(false);
	dialog->setTitleBarEnabled(false);
	dialog->contents()->setStyleClass("flex flex-col justify-center items-center p-2");
	dialog->setOffsets(Wt::WLength::Auto, Wt::Side::Top | Wt::Side::Right | Wt::Side::Bottom | Wt::Side::Left);
	dialog->rejectWhenEscapePressed();

	if(toText){
		dialog->contents()->addWidget(std::make_unique<Wt::WText>("Are you sure tou want to change ?"));
        dialog->contents()->addWidget(std::make_unique<Wt::WText>("text --> template"));
	}else {
		dialog->contents()->addWidget(std::make_unique<Wt::WText>("Are you sure tou want to change ?"));
        dialog->contents()->addWidget(std::make_unique<Wt::WText>("template --> text"));
	}
    dialog->footer()->setStyleClass("flex justify-between");

	auto no_btn = dialog->footer()->addWidget(std::make_unique<Wt::WPushButton>("No"));
	auto yes_btn = dialog->footer()->addWidget(std::make_unique<Wt::WPushButton>("Yes"));

    yes_btn->setStyleClass(tr("button"));
    no_btn->setStyleClass(tr("button"));

	yes_btn->clicked().connect(dialog, &Wt::WDialog::accept);
	no_btn->clicked().connect(dialog, &Wt::WDialog::reject);

	dialog->finished().connect(this, [=](Wt::DialogCode code){
		if(code == Wt::DialogCode::Accepted){
			std::cout << "\n\n StylusEdditor::createDialogVariableToText --- accepted \n\n";
            contentChanged_.emit();
            refreshDevApp_.emit();

		}else {
			std::cout << "\n\n StylusEdditor::createDialogVariableToText --- rejected \n\n";
		}
	});
	dialog->animateShow(Wt::WAnimation(Wt::AnimationEffect::Fade, Wt::TimingFunction::Linear, 350));

}
    
