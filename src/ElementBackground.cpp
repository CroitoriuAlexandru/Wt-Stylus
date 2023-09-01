#include "include/ElementBackground.h"
#include <regex>
#include <string>
#include <Wt/WPopupMenu.h>
#include <Wt/WMenuItem.h>

ElementBackgroundWidget::ElementBackgroundWidget(std::shared_ptr<Config> tailwindConfig)
	: tailwindConfig_(tailwindConfig),
	gradient_group(std::make_shared<Wt::WButtonGroup>()),
	attachment_group(std::make_shared<Wt::WButtonGroup>()),
	clip_group(std::make_shared<Wt::WButtonGroup>()),
	origin_group(std::make_shared<Wt::WButtonGroup>()),
	position_group(std::make_shared<Wt::WButtonGroup>()),
	repeat_group(std::make_shared<Wt::WButtonGroup>()),
	size_group(std::make_shared<Wt::WButtonGroup>())
{


	setStyleClass("min-w-fit max-w-[300px] !border-x-0 !bg-neutral-700 !text-neutral-200 !border-neutral-900 px-1.5");
	setTitle("Backgrounds");
	titleBarWidget()->setStyleClass("flex items-center space-x-3 !border-b border-solid border-neutral-900 bg-neutral-800 ");
	setCollapsible(true);
	auto centralWidget = setCentralWidget(std::make_unique<Wt::WContainerWidget>());

	auto popupMenu = std::make_unique<Wt::WPopupMenu>();
	std::string menuItemsStyles = "p-2 m-1 hover:bg-neutral-800 hover:text-neutral-200";
	popupMenu->addItem("set test classes")->setStyleClass(menuItemsStyles);
	popupMenu->addItem("reset styles")->setStyleClass(menuItemsStyles);
	popupMenu->addSeparator()->setStyleClass("border border-solid border-neutral-900");

	auto gradient_info = popupMenu->addItem("Info Gradient");
	auto attachment_info = popupMenu->addItem("Info Attachment");
	auto clip_info = popupMenu->addItem("Info Clip");
	auto origin_info = popupMenu->addItem("Info Origin");
	auto position_info = popupMenu->addItem("Info Position");
	auto repeat_info = popupMenu->addItem("Info Repeat");
	auto size_info = popupMenu->addItem("Info Size");

	gradient_info->setStyleClass(menuItemsStyles);
	attachment_info->setStyleClass(menuItemsStyles);
	clip_info->setStyleClass(menuItemsStyles);
	origin_info->setStyleClass(menuItemsStyles);
	position_info->setStyleClass(menuItemsStyles);
	repeat_info->setStyleClass(menuItemsStyles);
	size_info->setStyleClass(menuItemsStyles);

	Wt::WLink gradient_link = Wt::WLink(tailwindConfig_->backgrounds.background_image.docsLink_);
	Wt::WLink attachment_link = Wt::WLink(tailwindConfig_->backgrounds.background_attachment.docsLink_);
	Wt::WLink clip_link = Wt::WLink(tailwindConfig_->backgrounds.background_clip.docsLink_);
	Wt::WLink origin_link = Wt::WLink(tailwindConfig_->backgrounds.background_origin.docsLink_);
	Wt::WLink position_link = Wt::WLink(tailwindConfig_->backgrounds.background_position.docsLink_);
	Wt::WLink repeat_link = Wt::WLink(tailwindConfig_->backgrounds.background_repeat.docsLink_);
	Wt::WLink size_link = Wt::WLink(tailwindConfig_->backgrounds.background_size.docsLink_);

	gradient_link.setTarget(Wt::LinkTarget::NewWindow);
	attachment_link.setTarget(Wt::LinkTarget::NewWindow);
	clip_link.setTarget(Wt::LinkTarget::NewWindow);
	origin_link.setTarget(Wt::LinkTarget::NewWindow);
	position_link.setTarget(Wt::LinkTarget::NewWindow);
	repeat_link.setTarget(Wt::LinkTarget::NewWindow);
	size_link.setTarget(Wt::LinkTarget::NewWindow);
	
	gradient_info->setLink(gradient_link);
	attachment_info->setLink(attachment_link);
	clip_info->setLink(clip_link);
	origin_info->setLink(origin_link);
	position_info->setLink(position_link);
	repeat_info->setLink(repeat_link);
	size_info->setLink(size_link);
	
	popupMenu->setStyleClass("bg-neutral-700 text-neutral-200 border border-solid border-neutral-900");

	popupMenu->triggered().connect(this, [=](Wt::WMenuItem *item) {
		if(item->text().toUTF8().compare("set test classes") == 0){
			setCustomTestValues();
			styleChanged_.emit(getStyles());
		}else if(item->text().toUTF8().compare("reset styles") == 0){
			resetStyles();
			styleChanged_.emit(getStyles());
		}
	});

	auto popupBtn = titleBarWidget()->addWidget(std::make_unique<Wt::WPushButton>());
	popupBtn->setStyleClass("p-3 bg-cover bg-[url(resources/icons/hamburger.svg)] !ml-auto mr-2");
	popupBtn->setMenu(std::move(popupMenu));

	// prevent the click event from propagating to the parent because it is located in the title bar witch expands and collapse on click
	popupBtn->clicked().preventPropagation();

	centralWidget->setStyleClass("flex flex-col w-full max-w-[300px]");

	auto gratient_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto attachment_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto clip_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto origin_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto position_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto repeat_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto size_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());

	auto gradient_header = gratient_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto attachment_header = attachment_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto clip_header = clip_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto origin_header = origin_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto position_header = position_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto repeat_header = repeat_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto size_header = size_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());

	auto gradient_body = gratient_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto attachment_body = attachment_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto clip_body = clip_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto origin_body = origin_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto position_body = position_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto repeat_body = repeat_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto size_body = size_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());

	std::string wrapper_classes = "flex flex-col border border-solid pb-1 border-neutral-900";
	gratient_wrapper->setStyleClass(wrapper_classes);
	attachment_wrapper->setStyleClass(wrapper_classes);
	clip_wrapper->setStyleClass(wrapper_classes);
	origin_wrapper->setStyleClass(wrapper_classes);
	position_wrapper->setStyleClass(wrapper_classes);
	repeat_wrapper->setStyleClass(wrapper_classes);
	size_wrapper->setStyleClass(wrapper_classes);

	std::string header_classes = "flex font-bold text-neutral-400";
	gradient_header->setStyleClass(header_classes);
	attachment_header->setStyleClass(header_classes);
	clip_header->setStyleClass(header_classes);
	origin_header->setStyleClass(header_classes);
	position_header->setStyleClass(header_classes);
	repeat_header->setStyleClass(header_classes);
	size_header->setStyleClass(header_classes);


	gradient_header->addWidget(std::make_unique<Wt::WText>("Gradient"));
	attachment_header->addWidget(std::make_unique<Wt::WText>("Attachment"));
	clip_header->addWidget(std::make_unique<Wt::WText>("Clip"));
	origin_header->addWidget(std::make_unique<Wt::WText>("Origin"));
	position_header->addWidget(std::make_unique<Wt::WText>("Position"));
	repeat_header->addWidget(std::make_unique<Wt::WText>("Repeat"));
	size_header->addWidget(std::make_unique<Wt::WText>("Size"));

	attachment_header->addWidget(std::make_unique<Wt::WText>("bg-..."))->setStyleClass("ms-auto me-2");
	clip_header->addWidget(std::make_unique<Wt::WText>("bg-clip-..."))->setStyleClass("ms-auto me-2");
	origin_header->addWidget(std::make_unique<Wt::WText>("bg-origin-..."))->setStyleClass("ms-auto me-2");
	position_header->addWidget(std::make_unique<Wt::WText>("bg-..."))->setStyleClass("ms-auto me-2");
	repeat_header->addWidget(std::make_unique<Wt::WText>("bg-..."))->setStyleClass("ms-auto me-2");
	size_header->addWidget(std::make_unique<Wt::WText>("bg-..."))->setStyleClass("ms-auto me-2");

	std::string body_classes = "flex flex-wrap items-center";
	gradient_body->setStyleClass(body_classes);
	attachment_body->setStyleClass(body_classes);
	clip_body->setStyleClass(body_classes);
	origin_body->setStyleClass(body_classes);
	position_body->setStyleClass(body_classes);
	repeat_body->setStyleClass(body_classes);
	size_body->setStyleClass(body_classes);


	std::string button_styles = 
	R"(
		flex w-fit h-fit cursor-pointer m-px p-px text-neutral-950 font-bold 
		[&>span]:bg-cover [&>input]:hidden [&>span]:m-px [&>span]:rounded-md [&>span]:px-1
		[&>span]:bg-neutral-500 [&>span]:hover:bg-neutral-400 [&>input:checked_+_span]:bg-neutral-400
	)";
	// gradient buttons
	for(int index = 0; index < tailwindConfig->backgrounds.background_image.styleClasses_.size(); ++index){
		// get the text after the last -
		std::string gradient_name = tailwindConfig->backgrounds.background_image.styleClasses_[index].className_;
		std::string gradient_direction = gradient_name.substr(gradient_name.find_last_of("-")+1);

		auto btn = gradient_body->addWidget(std::make_unique<Wt::WRadioButton>(""));
		btn->setStyleClass(button_styles);

		std::string tooltip_text;
		if(gradient_direction.compare("tl") == 0){
			tooltip_text = "To Top Left";
			btn->addStyleClass("[&>span]:bg-[url(resources/icons/arrow-left-up.svg)] [&>span]:!p-2.5");
		}else if (gradient_direction.compare("tr") == 0){
			tooltip_text = "To Top Right";
			btn->addStyleClass("[&>span]:bg-[url(resources/icons/arrow-right-up.svg)] [&>span]:!p-2.5");
		}else if (gradient_direction.compare("bl") == 0){
			tooltip_text = "To Bottom Left";
			btn->addStyleClass("[&>span]:bg-[url(resources/icons/arrow-left-down.svg)] [&>span]:!p-2.5");
		}else if (gradient_direction.compare("br") == 0){
			tooltip_text = "To Bottom Right";
			btn->addStyleClass("[&>span]:bg-[url(resources/icons/arrow-right-down.svg)] [&>span]:!p-2.5");
		}else if (gradient_direction.compare("t") == 0){
			tooltip_text = "To Top";
			btn->addStyleClass("[&>span]:bg-[url(resources/icons/arrow-up.svg)] [&>span]:!p-2.5");
		}else if (gradient_direction.compare("b") == 0){
			tooltip_text = "To Bottom";
			btn->addStyleClass("[&>span]:bg-[url(resources/icons/arrow-down.svg)] [&>span]:!p-2.5");
		}else if (gradient_direction.compare("l") == 0){
			tooltip_text = "To Left";
			btn->addStyleClass("[&>span]:bg-[url(resources/icons/arrow-left.svg)] [&>span]:!p-2.5");
		}else if (gradient_direction.compare("r") == 0){
			tooltip_text = "To Right";
			btn->addStyleClass("[&>span]:bg-[url(resources/icons/arrow-right.svg)] [&>span]:!p-2.5");
		}else if (gradient_name.compare("bg-none") == 0){
			tooltip_text = "No Background";
			btn->setText("none");
			btn->addStyleClass("[&>span]:text-sm");
		}else {
			tooltip_text = "No style class applied";
			btn->addStyleClass("[&>span]:bg-[url(resources/icons/red-cross.svg)] [&>span]:!p-2.5 ");
		}
		btn->setToolTip(Wt::WString().tr("tooltip-styleClasses").arg(tooltip_text).arg(gradient_name), Wt::TextFormat::UnsafeXHTML);
		gradient_group->addButton(btn, index);
	}

	// attachment buttons
	for(int index = 0; index < tailwindConfig->backgrounds.background_attachment.styleClasses_.size(); ++index){
		auto style_class = tailwindConfig->backgrounds.background_attachment.styleClasses_[index];
		auto btn = attachment_body->addWidget(std::make_unique<Wt::WRadioButton>(""));
		
		btn->setStyleClass(button_styles);
		if(style_class.className_.compare("none") == 0){
			btn->addStyleClass("[&>span]:bg-[url(resources/icons/red-cross.svg)] [&>span]:!p-2.5");
		}else {
			// remove the first 3 characters from class for easier to understand display | Example = bg-fixed , fixed
			btn->setText(style_class.className_.substr(3));
		}

		attachment_group->addButton(btn, index);
	}

	// clip buttons
	for(int index = 0; index < tailwindConfig->backgrounds.background_clip.styleClasses_.size(); ++index){
		auto style_class = tailwindConfig->backgrounds.background_clip.styleClasses_[index];
		auto btn = clip_body->addWidget(std::make_unique<Wt::WRadioButton>(""));
		btn->setStyleClass(button_styles);
		if(style_class.className_.compare("none") == 0){
			btn->addStyleClass("[&>span]:bg-[url(resources/icons/red-cross.svg)] [&>span]:!p-2.5");
		}else {
			// remove the first 8 characters from class for easier to understand display | Example = bg-clip-border , border
			btn->setText(style_class.className_.substr(8));
		}

		clip_group->addButton(btn, index);
	}

	// origin buttons
	for(int index = 0; index < tailwindConfig->backgrounds.background_origin.styleClasses_.size(); ++index){
		auto style_class = tailwindConfig->backgrounds.background_origin.styleClasses_[index];
		auto btn = origin_body->addWidget(std::make_unique<Wt::WRadioButton>(""));
		
		btn->setStyleClass(button_styles);
		if(style_class.className_.compare("none") == 0){
			btn->addStyleClass("[&>span]:bg-[url(resources/icons/red-cross.svg)] [&>span]:!p-2.5");
		}else {
			// remove the first 10 characters from class for easier to understand display | Example = bg-origin-border , border
			btn->setText(style_class.className_.substr(10));
		}

		origin_group->addButton(btn, index);
	}

	// position buttons
	for(int index = 0; index < tailwindConfig->backgrounds.background_position.styleClasses_.size(); ++index){
		auto style_class = tailwindConfig->backgrounds.background_position.styleClasses_[index];
		auto btn = position_body->addWidget(std::make_unique<Wt::WRadioButton>(""));
		btn->setStyleClass(button_styles);
		
		// get the text after the bg- first 3 chars
		std::string position_name = style_class.className_.substr(3);

		if(position_name.compare("top") == 0){
			btn->addStyleClass("[&>span]:bg-[url(resources/icons/arrow-up.svg)] [&>span]:!p-2.5");
		}else if (position_name.compare("bottom") == 0){
			btn->addStyleClass("[&>span]:bg-[url(resources/icons/arrow-down.svg)] [&>span]:!p-2.5");
		}else if (position_name.compare("left") == 0){
			btn->addStyleClass("[&>span]:bg-[url(resources/icons/arrow-left.svg)] [&>span]:!p-2.5");
		}else if (position_name.compare("right") == 0){
			btn->addStyleClass("[&>span]:bg-[url(resources/icons/arrow-right.svg)] [&>span]:!p-2.5");
		}else if (position_name.compare("right-top") == 0){
			btn->addStyleClass("[&>span]:bg-[url(resources/icons/arrow-right-up.svg)] [&>span]:!p-2.5");
		}else if (position_name.compare("right-bottom") == 0){
			btn->addStyleClass("[&>span]:bg-[url(resources/icons/arrow-right-down.svg)] [&>span]:!p-2.5");
		}else if (position_name.compare("left-top") == 0){
			btn->addStyleClass("[&>span]:bg-[url(resources/icons/arrow-left-up.svg)] [&>span]:!p-2.5");
		}else if (position_name.compare("left-bottom") == 0){
			btn->addStyleClass("[&>span]:bg-[url(resources/icons/arrow-left-down.svg)] [&>span]:!p-2.5");
		}else if (position_name.compare("center") == 0){
			btn->addStyleClass("text-xs");
			btn->setText("center");
		}else if(style_class.className_.compare("none") == 0){
			btn->addStyleClass("[&>span]:bg-[url(resources/icons/red-cross.svg)] [&>span]:!p-2.5");
		}

		position_group->addButton(btn, index);
	}

	// repeat buttons
	for(int index = 0; index < tailwindConfig->backgrounds.background_repeat.styleClasses_.size(); ++index){
		auto style_class = tailwindConfig->backgrounds.background_repeat.styleClasses_[index];
		auto btn = repeat_body->addWidget(std::make_unique<Wt::WRadioButton>(""));
		
		btn->setStyleClass(button_styles);
		if(style_class.className_.compare("none") == 0){
			btn->addStyleClass("[&>span]:bg-[url(resources/icons/red-cross.svg)] [&>span]:!p-2.5");
		}else {
			// remove the first 3 characters from class for easier to understand display | Example = bg-repeat , repeat
			btn->setText(style_class.className_.substr(3));
			btn->addStyleClass("text-sm");
		}

		repeat_group->addButton(btn, index);
	}

	// size buttons
	for(int index = 0; index < tailwindConfig->backgrounds.background_size.styleClasses_.size(); ++index){
		auto style_class = tailwindConfig->backgrounds.background_size.styleClasses_[index];
		auto btn = size_body->addWidget(std::make_unique<Wt::WRadioButton>(""));
		
		btn->setStyleClass(button_styles);
		if(style_class.className_.compare("none") == 0){
			btn->addStyleClass("[&>span]:bg-[url(resources/icons/red-cross.svg)] [&>span]:!p-2.5");
		}else {
			// remove the first 3 characters from class for easier to understand display | Example = bg-auto , auto
			btn->setText(style_class.className_.substr(3));
		}

		size_group->addButton(btn, index);
	}

	
	gradient_group->button(0)->setChecked(true);
	attachment_group->button(0)->setChecked(true);
	clip_group->button(0)->setChecked(true);
	origin_group->button(0)->setChecked(true);
	position_group->button(0)->setChecked(true);
	repeat_group->button(0)->setChecked(true);
	size_group->button(0)->setChecked(true);

	gradient_group->checkedChanged().connect(this, [=](){ 
		int id = gradient_group->checkedId();
		gradient_class = tailwindConfig_->backgrounds.background_image.styleClasses_[id].className_;
		std::cout << "gradient_class: " << gradient_class << std::endl;
		styleChanged_.emit(getStyles()); 
	});
	attachment_group->checkedChanged().connect(this, [=](){ 
		int id = attachment_group->checkedId();
		attachment_class = tailwindConfig_->backgrounds.background_attachment.styleClasses_[id].className_;
		std::cout << "attachment_class: " << attachment_class << std::endl;
		styleChanged_.emit(getStyles()); 
	});
	clip_group->checkedChanged().connect(this, [=](){ 
		int id = clip_group->checkedId();
		clip_class = tailwindConfig_->backgrounds.background_clip.styleClasses_[id].className_;
		std::cout << "clip_class: " << clip_class << std::endl;
		styleChanged_.emit(getStyles()); 
	});
	origin_group->checkedChanged().connect(this, [=](){ 
		int id = origin_group->checkedId();
		origin_class = tailwindConfig_->backgrounds.background_origin.styleClasses_[id].className_;
		std::cout << "origin_class: " << origin_class << std::endl;
		styleChanged_.emit(getStyles()); 
	});
	position_group->checkedChanged().connect(this, [=](){ 
		int id = position_group->checkedId();
		position_class = tailwindConfig_->backgrounds.background_position.styleClasses_[id].className_;
		std::cout << "position_class: " << position_class << std::endl;
		styleChanged_.emit(getStyles()); 
	});
	repeat_group->checkedChanged().connect(this, [=](){ 
		int id = repeat_group->checkedId();
		repeat_class = tailwindConfig_->backgrounds.background_repeat.styleClasses_[id].className_;
		std::cout << "repeat_class: " << repeat_class << std::endl;
		styleChanged_.emit(getStyles()); 
	});
	size_group->checkedChanged().connect(this, [=](){ 
		int id = size_group->checkedId();
		size_class = tailwindConfig_->backgrounds.background_size.styleClasses_[id].className_;
		std::cout << "size_class: " << size_class << std::endl;
		styleChanged_.emit(getStyles()); 
	});


};

std::string ElementBackgroundWidget::getStyles()
{
	bool activeClasses = false;
	std::string elementClasses;

	if(gradient_class.compare("none") != 0){
		activeClasses = true; 
		elementClasses += gradient_class + " ";
	}
	if(attachment_class.compare("none") != 0){
		activeClasses = true; 
		elementClasses += attachment_class + " ";
	}
	if(clip_class.compare("none") != 0){
		activeClasses = true; 
		elementClasses += clip_class + " ";
	}
	if(origin_class.compare("none") != 0){
		activeClasses = true; 
		elementClasses += origin_class + " ";
	}
	if(position_class.compare("none") != 0){
		activeClasses = true; 
		elementClasses += position_class + " ";
	}
	if(repeat_class.compare("none") != 0){
		activeClasses = true; 
		elementClasses += repeat_class + " ";
	}
	if(size_class.compare("none") != 0){
		activeClasses = true; 
		elementClasses += size_class + " ";
	}


	if(activeClasses) expand();

	return elementClasses;
}

int ElementBackgroundWidget::getIndesOfStringInVector(std::string str, std::vector<StyleClass> vec){
	for(int index = 0; index < vec.size(); ++index){
		if(vec[index].className_.compare(str) == 0) return index;
	}
	return 0;
}


void ElementBackgroundWidget::setClasses(BackgroundData bgData)
{
	resetStyles();
	bool activeClasses;
	activeClasses = setGradient(bgData. gradient);
	activeClasses = setAttachment(bgData.attachment);
	activeClasses = setClip(bgData.clip);
	activeClasses = setOrigin(bgData.origin);
	activeClasses = setPosition(bgData.position);
	activeClasses = setRepeat(bgData.repeat);
	activeClasses = setSize(bgData.size);

	if(!activeClasses) collapse();
}

void ElementBackgroundWidget::resetStyles()
{
	gradient_group->setCheckedButton(gradient_group->button(0));
	attachment_group->setCheckedButton(attachment_group->button(0));
	clip_group->setCheckedButton(clip_group->button(0));
	origin_group->setCheckedButton(origin_group->button(0));
	position_group->setCheckedButton(position_group->button(0));
	repeat_group->setCheckedButton(repeat_group->button(0));
	size_group->setCheckedButton(size_group->button(0));

	gradient_class = "none";
	attachment_class = "none";
	clip_class = "none";
	origin_class = "none";
	position_class = "none";
	repeat_class = "none";
	size_class = "none";
}

void ElementBackgroundWidget::setCustomTestValues()
{
	gradient_group->setCheckedButton(gradient_group->button(3));
	attachment_group->setCheckedButton(attachment_group->button(3));
	clip_group->setCheckedButton(clip_group->button(3));
	origin_group->setCheckedButton(origin_group->button(3));
	position_group->setCheckedButton(position_group->button(3));
	repeat_group->setCheckedButton(repeat_group->button(3));
	size_group->setCheckedButton(size_group->button(3));

	gradient_group->checkedChanged().emit(gradient_group->checkedButton());
	attachment_group->checkedChanged().emit(attachment_group->checkedButton());
	clip_group->checkedChanged().emit(clip_group->checkedButton());
	origin_group->checkedChanged().emit(origin_group->checkedButton());
	position_group->checkedChanged().emit(position_group->checkedButton());
	repeat_group->checkedChanged().emit(repeat_group->checkedButton());
	size_group->checkedChanged().emit(size_group->checkedButton());
}

bool ElementBackgroundWidget::setGradient(std::string className)
{
	int gradientIndex = getIndesOfStringInVector(className, tailwindConfig_->backgrounds.background_image.styleClasses_);
	if(gradientIndex >= 0){
		gradient_group->button(gradientIndex)->setChecked(true);
		if(gradientIndex > 0) {
			expand();
			return true;
		}
	}
	return false;
}

bool ElementBackgroundWidget::setAttachment(std::string className)
{
	int attachmentIndex = getIndesOfStringInVector(className, tailwindConfig_->backgrounds.background_attachment.styleClasses_);
	if(attachmentIndex >= 0){
		attachment_group->button(attachmentIndex)->setChecked(true);
		if(attachmentIndex > 0) {
			expand();
			return true;
		}
	}
	return false;
}

bool ElementBackgroundWidget::setClip(std::string className)
{
	int clipIndex = getIndesOfStringInVector(className, tailwindConfig_->backgrounds.background_clip.styleClasses_);
	if(clipIndex >= 0){
		clip_group->button(clipIndex)->setChecked(true);
		if(clipIndex > 0) {
			expand();
			return true;
		}
	}
	return false;
}

bool ElementBackgroundWidget::setOrigin(std::string className)
{
	int originIndex = getIndesOfStringInVector(className, tailwindConfig_->backgrounds.background_origin.styleClasses_);
	if(originIndex >= 0){
		origin_group->button(originIndex)->setChecked(true);
		if(originIndex > 0) {
			expand();
			return true;
		}
	}
	return false;
}

bool ElementBackgroundWidget::setPosition(std::string className)
{
	int positionIndex = getIndesOfStringInVector(className, tailwindConfig_->backgrounds.background_position.styleClasses_);
	if(positionIndex >= 0){
		position_group->button(positionIndex)->setChecked(true);
		if(positionIndex > 0) {
			expand();
			return true;
		}
	}
	return false;
}

bool ElementBackgroundWidget::setRepeat(std::string className)
{
	int repeatIndex = getIndesOfStringInVector(className, tailwindConfig_->backgrounds.background_repeat.styleClasses_);
	if(repeatIndex >= 0){
		repeat_group->button(repeatIndex)->setChecked(true);
		if(repeatIndex > 0) {
			expand();
			return true;
		}
	}
	return false;
}

bool ElementBackgroundWidget::setSize(std::string className)
{
	int sizeIndex = getIndesOfStringInVector(className, tailwindConfig_->backgrounds.background_size.styleClasses_);
	if(sizeIndex >= 0){
		size_group->button(sizeIndex)->setChecked(true);
		if(sizeIndex > 0) {
			expand();
			return true;
		}
	}
	return false;
}