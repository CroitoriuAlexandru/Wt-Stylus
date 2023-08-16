#include "include/StylusTreeView.h"

TreeNode::TreeNode(const Wt::WString& labelText, std::unique_ptr<Wt::WIconPair> labelIcon)
	: Wt::WTreeNode(labelText, std::move(labelIcon))
{
	setCanReceiveFocus(true);
	setSelectable(true);
	setLoadPolicy(Wt::ContentLoading::NextLevel);
	label()->setTextFormat(Wt::TextFormat::Plain);
	expand();

	labelArea()->setStyleClass("flex flex-row items-center justify-center text-neutral-300");

	// auto labelAreaStart = labelArea()->insertAfter(std::make_unique<Wt::WContainerWidget>(), label());
	auto labelAreaStart = labelArea()->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto labelAreaEnd = labelArea()->addWidget(std::make_unique<Wt::WContainerWidget>());

	remove_btn = labelArea()->insertBefore(std::make_unique<Wt::WText>(""), label());
	move_right_btn = labelAreaStart->addWidget(std::make_unique<Wt::WText>(""));
	move_up_btn = labelAreaEnd->addWidget(std::make_unique<Wt::WText>(""));
	move_down_btn = labelAreaEnd->addWidget(std::make_unique<Wt::WText>(""));
	add_child_first_btn = labelAreaEnd->addWidget(std::make_unique<Wt::WText>(""));
	add_child_last_btn = labelAreaEnd->addWidget(std::make_unique<Wt::WText>(""));
	add_sibling_before_btn = labelAreaEnd->addWidget(std::make_unique<Wt::WText>(""));
	add_sibling_after_btn = labelAreaEnd->addWidget(std::make_unique<Wt::WText>(""));
	open_template_btn = labelAreaEnd->addWidget(std::make_unique<Wt::WText>("Open Temp"));

	open_template_btn->setHidden(true);
	open_template_btn->setStyleClass("mr-2.5 ml-1");
	labelAreaEnd->setStyleClass("ms-auto flex items-center");
	labelAreaStart->setStyleClass("me-auto flex items-center");
	Wt::WString btns_styles = "!p-[7px] !my-0 !ms-0 bg-cover bg-no-repeat inline  cursor-pointer";
	remove_btn->addStyleClass(btns_styles + " bg-[url(resources/icons/trash.svg)] me-0 sticky left-0");
	move_right_btn->addStyleClass(btns_styles + " bg-[url(resources/icons/arrow-right-down.svg)] bg-neutral-300 rounded-full");
	move_up_btn->addStyleClass(btns_styles + " bg-[url(resources/icons/arrow-up.svg)] me-2 bg-neutral-300 rounded-full");
	move_down_btn->addStyleClass(btns_styles + " bg-[url(resources/icons/arrow-down.svg)] me-2 bg-neutral-300 rounded-full");
	add_sibling_after_btn->addStyleClass(btns_styles + " bg-[url(resources/icons/parent.svg)] me-2");
	add_sibling_before_btn->addStyleClass(btns_styles + " bg-[url(resources/icons/parent.svg)] me-2");
	add_child_first_btn->addStyleClass(btns_styles + " bg-[url(resources/icons/kid.svg)] me-2");
	add_child_last_btn->addStyleClass(btns_styles + " bg-[url(resources/icons/kid.svg)] me-2");

}

void TreeNode::setTemplateNode(bool isTemplateNode)
{
	if(isTemplateNode){
		// remove_btn->setHidden(true);
		move_right_btn->setHidden(true);
		move_up_btn->setHidden(true);
		move_down_btn->setHidden(true);
		add_child_first_btn->setHidden(true);
		add_child_last_btn->setHidden(true);
		add_sibling_before_btn->setHidden(true);
		add_sibling_after_btn->setHidden(true);
		open_template_btn->setHidden(false);
	}else {
		// remove_btn->setHidden(false);
		move_right_btn->setHidden(false);
		move_up_btn->setHidden(false);
		move_down_btn->setHidden(false);
		add_child_first_btn->setHidden(false);
		add_child_last_btn->setHidden(false);
		add_sibling_before_btn->setHidden(false);
		add_sibling_after_btn->setHidden(false);
		open_template_btn->setHidden(true);
	}
}

StylusTreeView::StylusTreeView(std::shared_ptr<StylusState> stylusState)
    : Wt::WTree(),
    stylusState_(stylusState)
{
    // set defaults
	setSelectionMode(Wt::SelectionMode::Single);
	addStyleClass("w-auto h-fit");
}

StylusTreeView::~StylusTreeView()
{
	// std::cout << "\n\n StylusTreeView destructor called \n\n";
}

void StylusTreeView::createTree()
{
	selectedTreeNode = nullptr;
	// tree root node
	auto rootNode = std::make_unique<TreeNode>(stylusState_->selectedTemplate->ToElement()->Attribute("id"));
	rootNode->move_up_btn->addStyleClass("hidden");
	rootNode->move_down_btn->addStyleClass("hidden");
	rootNode->move_right_btn->addStyleClass("hidden");
	rootNode->add_sibling_before_btn->addStyleClass("hidden");
	rootNode->add_sibling_after_btn->addStyleClass("hidden");
	rootNode->remove_btn->addStyleClass("hidden");
	auto rootNode_ = rootNode.get(); 

	rootNode->add_child_first_btn->doubleClicked().connect(this, [=](){
		addChildElementFirst(stylusState_->selectedTemplate->ToElement());
		createTree();
	});
	rootNode->add_child_last_btn->doubleClicked().connect(this, [=](){
		addChildElementLast(stylusState_->selectedTemplate->ToElement());
		createTree();
	});
	auto rootNodePtr = rootNode.get();
    setTreeRoot(std::move(rootNode));

    auto element = stylusState_->selectedTemplate->FirstChildElement();
    while(element){
		selectedNodeFound = false;
        if(element->Attribute("class") == NULL){
            element->SetAttribute("class", "");
        }
		if(element->GetText() == NULL){
			element->SetText("");
		}
        treeRoot()->addChildNode(createNodeTree(element));
		selectedNodeFound = false;
        element = element->NextSiblingElement();
    }

	if(selectedTreeNode != nullptr){
		// std::cout << "\n selectedTreeNode found \n";
		select(selectedTreeNode, true);
	}else if(treeRoot()->childNodes().size() > 0) {
		// std::cout << "\n\n selectedTreeNode not found \n\n";
		select(treeRoot()->childNodes()[0],  true);
		stylusState_->selectedElement = stylusState_->selectedTemplate->FirstChildElement();
		selectionChanged_.emit(stylusState_->selectedElement->ToElement());
	}else {
		select(treeRoot(), true);
		stylusState_->selectedElement = stylusState_->selectedTemplate->ToElement();
	}

}

std::unique_ptr<TreeNode> StylusTreeView::createNodeTree(tinyxml2::XMLElement* element)
{
	// std::cout << "\n StylusTreeView::createNodeTree \n";
	auto node = std::make_unique<TreeNode>(element->Name());

	// create template widget node if the element has a template text inside it
	if(	element->FirstChild() && 
		element->FirstChild()->ToText() &&
		std::regex_search(element->FirstChild()->ToText()->Value(), template_regexp))
	{
		// std::cout << "\n\n template found \n\n";
		node->addChildNode(createTemplateNode(element->FirstChild()));
	}

	auto nodePtr = node.get();
	node->selected().connect(this, [=](bool selectedBool){
		if(selectedBool){
			selectionChanged_.emit(element);
			nodePtr->expand();
		}
	});
	if(!element->Attribute("class")){
		element->SetAttribute("class", "");
	}
	if(!element->GetText()){
		element->SetText("");
	}
	// signal connections for controling element
    node->move_up_btn->clicked().connect(this, [=](){
        moveElementUp(element);
		createTree();
    });
    node->move_down_btn->clicked().connect(this, [=](){
        moveElementDown(element);
		createTree();
    });
    node->add_sibling_after_btn->clicked().connect(this, [=](){
        addSiblingElementAfter(element);
		createTree();
    });
    node->add_sibling_before_btn->clicked().connect(this, [=](){
        addSiblingElementBefore(element);
		createTree();
    });
    node->add_child_first_btn->clicked().connect(this, [=](){
        addChildElementFirst(element);
		createTree();
    });
    node->add_child_last_btn->clicked().connect(this, [=](){
        addChildElementLast(element);
		createTree();
    });
    node->remove_btn->doubleClicked().connect(this, [=](){
        removeElement(element);
		createTree();
    });

    if(element->NextSiblingElement()){
        if(element->NextSiblingElement()->FirstChildElement()){
            node->move_right_btn->clicked().connect(this, [=](){
                moveElementRight(element);
				createTree();
            });
        }else {
            node->move_right_btn->addStyleClass("hidden");
        }
    }else {
        node->move_right_btn->addStyleClass("hidden");
    }

	auto elementClass = element->Attribute("class");
	bool hasQuestionmark = std::string(elementClass).find("?") != std::string::npos;
	if(hasQuestionmark){
		selectedTreeNode = node.get();
		stylusState_->selectedElement = element;
		selectedNodeFound = true;
	}

	// Check if the element has child elements
	tinyxml2::XMLElement* child = element->FirstChildElement();
	while (child) {
		node->addChildNode(createNodeTree(child));
		child = child->NextSiblingElement();
	}

	if(!selectedNodeFound)
		node->collapse();

	return node;
}

std::unique_ptr<TreeNode> StylusTreeView::createTemplateNode(tinyxml2::XMLNode* textNode)
{
	// std::cout << "\n\n temp[late node creation gere --------------------------------\n\n";
	auto node = std::make_unique<TreeNode>("temp");
	auto nodePtr = node.get();
	node->setTemplateNode(true);

	std::size_t lastPos = 0;
	std::string variableName;
	std::string styleClasses;
	std::string folderName;
	std::string fileName;
	std::string messageId;
	std::string widgetType;
	// ${test.test class="text-center p-2 m-2" fileName="fileName.xml" messageId="templateId"}
	// get  variableName + test.test
	std::size_t pos = std::string(textNode->Value()).find("${");
	variableName = std::string(textNode->Value()).substr(pos + 2, std::string(textNode->Value()).find(" ", pos) - pos - 2);
	// remove variableName from text
	std::string text = std::string(textNode->Value()).substr(pos + 2 + variableName.length() + 1);
	// remove class="" argument
	pos = text.find("class=\"");
	if(pos != std::string::npos){
		styleClasses = text.substr(pos + 7, text.find("\"", pos + 7) - pos - 7);
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
		text = text.substr(0, pos) + text.substr(text.find("\"", pos + 12) + 2);}

	// set node found if template node has ? in class
	if(styleClasses.find("?") != std::string::npos){
		selectedTreeNode = node.get();
		stylusState_->selectedElement = textNode;
		selectedNodeFound = true;
		selectedTreeNode = node.get();
	}

	// std::cout << "\n\n";
	// std::cout << "text :<" << textNode->Value() << ">\n";
	// std::cout << "text :<" << text << ">\n";
	// std::cout << "variableName :<" << variableName << ">\n";
	// std::cout << "styleClasses :<" << styleClasses << ">\n";
	// std::cout << "folderName :<" << folderName << ">\n";
	// std::cout << "fileName :<" << fileName << ">\n";		
	// std::cout << "messageId :<" << messageId << "\n";
	// std::cout << "widgetType :<" << widgetType << ">\n";
	// std::cout << "\n\n";

	node->label()->setText(variableName);
	node->open_template_btn->doubleClicked().connect(this, [=](){		
		openTemplate_.emit(folderName, fileName, messageId, widgetType, true);
	});

	node->selected().connect(this, [=](bool selectedNode){
		if(selectedNode){
			selectionChanged_.emit(textNode);
		}
	});

	return node;
}


// handle adding and removing elements
void StylusTreeView::moveElementUp(tinyxml2::XMLElement* element)
{
	std::cout << "\n StylusTreeView::moveElementUp \n";
	auto newElement = element->DeepClone(&stylusState_->doc);

	if(element->PreviousSiblingElement()){
		std::cout << "\n ----- Prev sibling valid \n\n";
		if(element->PreviousSiblingElement()->PreviousSiblingElement()){
			std::cout << "\n ----- Prev Prev sibling valid" << element->PreviousSiblingElement()->PreviousSiblingElement()->GetText() << "\n\n";
			element->Parent()->InsertAfterChild(element->PreviousSibling()->PreviousSibling(), newElement);
		}else {
			std::cout << "\n ----- Prev Prev sibling NOT valid " << " \n\n";
			element->Parent()->InsertFirstChild(newElement);
		}
	}else if(element->Parent() != stylusState_->selectedTemplate){
		std::cout << "\n ----- np previus siblings and Parent is temp message NOT \n\n";

		if(element->Parent()->PreviousSiblingElement()){
			std::cout << "\n ----- Parent has previus sibling \n\n";
			element->Parent()->Parent()->InsertAfterChild(element->Parent()->PreviousSibling(), newElement);
		}else {
			std::cout << "\n ----- Parent has NO previus sibling \n\n";
			element->Parent()->Parent()->InsertFirstChild(newElement);
		}
	}else {
		std::cout << "\n ----- no previus siblings and Parent is temp message \n\n";
		return;
	}

	removeElement(element);
}

void StylusTreeView::moveElementDown(tinyxml2::XMLElement* element)
{
	std::cout << "\n StylusTreeView::moveElementDown \n";
	auto newElement = element->DeepClone(&stylusState_->doc);

	if(!element->NextSiblingElement() && element->Parent() == stylusState_->selectedTemplate)
		return;
	else if(element->NextSiblingElement()){
		element->Parent()->InsertAfterChild(element->NextSiblingElement(), newElement);
	} else {
		element->Parent()->Parent()->InsertAfterChild(element->Parent(), newElement);
	}
	removeElement(element);
}

void StylusTreeView::moveElementRight(tinyxml2::XMLElement* element)
{
	std::cout << "\n StylusTreeView::moveElementRight \n";
	auto newElement = element->DeepClone(&stylusState_->doc);
	if(!element->NextSiblingElement()){
		std::cout << "\n StylusTreeView::moveElementRight but no next sibling \n";
		return;
	}
	if(!element->NextSiblingElement()->FirstChildElement()){
		std::cout << "\n\n StylusTreeView::moveElementRight but next sibling has no child \n\n";
		return;
	}
	
	element->NextSiblingElement()->InsertFirstChild(newElement);
	stylusState_->selectedElement = newElement->ToElement();	
	removeElement(element);
	
}

void StylusTreeView::addSiblingElementBefore(tinyxml2::XMLElement* element, tinyxml2::XMLElement* newElement)
{
	std::cout << "\n StylusTreeView::addSiblingElementBefore \n";
	if(newElement == nullptr){
		newElement = stylusState_->doc.NewElement("div");
		newElement->SetAttribute("class", "");
		newElement->SetText("siblings before");
	}

	// add it to the selected element
	if(element->PreviousSiblingElement())
		element->Parent()->InsertAfterChild(element->PreviousSiblingElement(), newElement);
	else
		element->Parent()->InsertFirstChild(newElement);
}

void StylusTreeView::addSiblingElementAfter(tinyxml2::XMLElement* element, tinyxml2::XMLElement* newElement)
{
	std::cout << "\n StylusTreeView::addSiblingElementAfter \n";
	if(newElement == nullptr){
		// create element <div class="text-center">header</div>
		newElement = stylusState_->doc.NewElement("div");
		newElement->SetAttribute("class", "");
		newElement->SetText("siblings after");
	}
	// add it to the selected element
	stylusState_->selectedElement->Parent()->InsertAfterChild(element, newElement);
}

void StylusTreeView::addChildElementFirst(tinyxml2::XMLElement* element, tinyxml2::XMLElement* newElement)
{
	std::cout << "\nStylusTreeView::addChildElementFirst\n";
	if(newElement == nullptr){
		// create element <div class="text-center">header</div>
		newElement = stylusState_->doc.NewElement("div");
		newElement->SetAttribute("class", "");
		newElement->SetText("child before");
	}
	// add it to the selected element
	element->SetText("");
	element->InsertFirstChild(newElement);

	if(element == stylusState_->selectedTemplate->ToElement()){
		stylusState_->selectedElement = newElement;
	}
}

void StylusTreeView::addChildElementLast(tinyxml2::XMLElement* element, tinyxml2::XMLElement* newElement)
{
	std::cout << "\nStylusTreeView::addChildElementLast\n";	
	if(newElement == nullptr){
		// create element <div class="text-center">header</div>
		newElement = stylusState_->doc.NewElement("div");
		newElement->SetAttribute("class", "");
		newElement->SetText("child after");
	}
	element->SetText("");
	element->InsertEndChild(newElement);

	if(element == stylusState_->selectedTemplate->ToElement()){
		stylusState_->selectedElement = newElement;
	}

}

void StylusTreeView::removeElement(tinyxml2::XMLElement* element)
{
	std::cout << "\n StylusTreeView::removeElement \n";
    stylusState_->doc.DeleteNode(element);
	stylusState_->doc.SaveFile(stylusState_->filePath.c_str());
	stylusState_->selectedElement = stylusState_->selectedTemplate->ToElement();
}