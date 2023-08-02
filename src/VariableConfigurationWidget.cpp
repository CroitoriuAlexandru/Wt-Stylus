#include "include/VariableConfigurationWidget.h"

VariableConfigurationWidget::VariableConfigurationWidget(std::vector<FolderData> foldersData)
    : WTemplate(tr("stylus.variable.configuration.template")),
    foldersData_(foldersData)
{
    lineEdit_variableName = bindWidget("variable.name", std::make_unique<Wt::WLineEdit>());
    comboBox_folderName = bindWidget("folder.name", std::make_unique<Wt::WComboBox>());
    comboBox_fileName = bindWidget("file.name", std::make_unique<Wt::WComboBox>());
    comboBox_message = bindWidget("message.id", std::make_unique<Wt::WComboBox>());
    comboBox_widgetType = bindWidget("widget.type", std::make_unique<Wt::WComboBox>());
    button_save = bindWidget("submit-btn", std::make_unique<Wt::WPushButton>("Save"));
    button_save->clicked().connect([=](){ variableSaved_.emit(); });
    button_save->setStyleClass(tr("button-dark"));

    // set combo box values
    auto widgetTypes = { "template" };
    for(auto folders : foldersData_){
        // std::cout << "\n\nfolderName :<" << folders.folderName << ">\n\n";
        comboBox_folderName->addItem(folders.folderName);
    }

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
}

void VariableConfigurationWidget::setData(std::string variableText)
{
    std::size_t lastPos = 0;
	std::string variableName;
	std::string folderName;
	std::string fileName;
	std::string messageId;
	std::string widgetType;
	// ${test.test class="text-center p-2 m-2" fileName="fileName.xml" messageId="templateId"}
	// get  variableName + test.test
	std::size_t pos = std::string(variableText).find("${");
	variableName = std::string(variableText).substr(pos + 2, std::string(variableText).find(" ", pos) - pos - 2);
	// remove variableName from text
	std::string text = std::string(variableText).substr(pos + 2 + variableName.length() + 1);
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


void VariableConfigurationWidget::setFileNames(Wt::WString folderName)
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

void VariableConfigurationWidget::setMessages(Wt::WString fileName)
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

void VariableConfigurationWidget::resetData()
{
    lineEdit_variableName->setText("");
    comboBox_folderName->setCurrentIndex(0);
    comboBox_fileName->setCurrentIndex(0);
    comboBox_message->setCurrentIndex(0);
    comboBox_widgetType->setCurrentIndex(0);
}

std::string VariableConfigurationWidget::getData()
{
    std::string variableText = "${" + lineEdit_variableName->text().toUTF8() + " ";
    variableText += "class=\"\" ";
    variableText += "folderName=\"" + comboBox_folderName->currentText().toUTF8() + "\" ";
    variableText += "fileName=\"" + comboBox_fileName->currentText().toUTF8() + "\" ";
    variableText += "messageId=\"" + comboBox_message->currentText().toUTF8() + "\" ";
    variableText += "widgetType=\"" + comboBox_widgetType->currentText().toUTF8() + "\"}";
    return variableText;
}


    
    // Wt::WLineEdit* lineEdit_variableName;
    // Wt::WComboBox* comboBox_folderName;
    // Wt::WComboBox* comboBox_fileName;
    // Wt::WComboBox* comboBox_message;
    // Wt::WComboBox* comboBox_widgetType;
    