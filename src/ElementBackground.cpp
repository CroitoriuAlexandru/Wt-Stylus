#include "include/ElementBackground.h"
#include <regex>
#include <string>
#include <Wt/WPopupMenu.h>
#include <Wt/WMenuItem.h>

ElementBackgroundWidget::ElementBackgroundWidget(std::shared_ptr<Config> tailwindConfig)
	: tailwindConfig_(tailwindConfig)
{


	setStyleClass("min-w-fit max-w-[300px] !border-x-0 !bg-neutral-700 !text-neutral-200 !border-neutral-900 px-1.5");
	setTitle("Backgrounds");
	titleBarWidget()->setStyleClass("flex items-center space-x-3 !border-b border-solid border-neutral-900 bg-neutral-800 ");
	setCollapsible(true);
	auto centralWidget = setCentralWidget(std::make_unique<Wt::WContainerWidget>());
	centralWidget->setStyleClass("flex flex-col w-full max-w-[300px]");

	{

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

	}

	gradient_widget_ = centralWidget->addWidget(std::make_unique<SelectionGroupClassChanger>(tailwindConfig_->backgrounds.background_image.styleClasses_, "Gradient" , "bg-"));
	attachment_widget_ = centralWidget->addWidget(std::make_unique<SelectionGroupClassChanger>(tailwindConfig_->backgrounds.background_attachment.styleClasses_, "Attachment" , "bg-"));
	clip_widget_ = centralWidget->addWidget(std::make_unique<SelectionGroupClassChanger>(tailwindConfig_->backgrounds.background_clip.styleClasses_, "Clip" , "bg-clip-"));
	origin_widget_ = centralWidget->addWidget(std::make_unique<SelectionGroupClassChanger>(tailwindConfig_->backgrounds.background_origin.styleClasses_, "Origin" , "bg-origin-"));
	position_widget_ = centralWidget->addWidget(std::make_unique<SelectionGroupClassChanger>(tailwindConfig_->backgrounds.background_position.styleClasses_, "Position" , "bg-"));
	repeat_widget_ = centralWidget->addWidget(std::make_unique<SelectionGroupClassChanger>(tailwindConfig_->backgrounds.background_repeat.styleClasses_, "Repeat" , "bg-"));
	size_widget_ = centralWidget->addWidget(std::make_unique<SelectionGroupClassChanger>(tailwindConfig_->backgrounds.background_size.styleClasses_, "Size" , "bg-"));


	// Signals
	gradient_widget_->classChanged().connect(this, [=](std::string className) {gradient_class = className; styleChanged_.emit(getStyles()); });
	attachment_widget_->classChanged().connect(this, [=](std::string className) {attachment_class = className; styleChanged_.emit(getStyles()); });
	clip_widget_->classChanged().connect(this, [=](std::string className) {clip_class = className; styleChanged_.emit(getStyles()); });
	origin_widget_->classChanged().connect(this, [=](std::string className) {origin_class = className; styleChanged_.emit(getStyles()); });
	position_widget_->classChanged().connect(this, [=](std::string className) {position_class = className; styleChanged_.emit(getStyles()); });
	repeat_widget_->classChanged().connect(this, [=](std::string className) {repeat_class = className; styleChanged_.emit(getStyles()); });
	size_widget_->classChanged().connect(this, [=](std::string className) {size_class = className; styleChanged_.emit(getStyles()); });


};

std::string ElementBackgroundWidget::getStyles()
{
	bool activeClasses = false;
	std::string elementClasses;

	if(gradient_class.compare("none") != 0){
		if(!activeClasses) activeClasses = true; 
		elementClasses += gradient_class + " ";
	}
	if(attachment_class.compare("none") != 0){
		if(!activeClasses) activeClasses = true; 
		elementClasses += attachment_class + " ";
	}
	if(clip_class.compare("none") != 0){
		if(!activeClasses) activeClasses = true; 
		elementClasses += clip_class + " ";
	}
	if(origin_class.compare("none") != 0){
		if(!activeClasses) activeClasses = true; 
		elementClasses += origin_class + " ";
	}
	if(position_class.compare("none") != 0){
		if(!activeClasses) activeClasses = true; 
		elementClasses += position_class + " ";
	}
	if(repeat_class.compare("none") != 0){
		if(!activeClasses) activeClasses = true; 
		elementClasses += repeat_class + " ";
	}
	if(size_class.compare("none") != 0){
		if(!activeClasses) activeClasses = true; 
		elementClasses += size_class + " ";
	}


	if(activeClasses) expand();

	return elementClasses;
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
	gradient_class = "none";
	attachment_class = "none";
	clip_class = "none";
	origin_class = "none";
	position_class = "none";
	repeat_class = "none";
	size_class = "none";

	gradient_widget_->setValue(gradient_class);
	attachment_widget_->setValue(attachment_class);
	clip_widget_->setValue(clip_class);
	origin_widget_->setValue(origin_class);
	position_widget_->setValue(position_class);
	repeat_widget_->setValue(repeat_class);
	size_widget_->setValue(size_class);

}


void ElementBackgroundWidget::setCustomTestValues()
{
	setGradient("bg-gradient-to-r");
	setAttachment("bg-fixed");
	setClip("bg-clip-padding");
	setOrigin("bg-origin-border");
	setPosition("bg-top");
	setRepeat("bg-repeat");
	setSize("bg-auto");
}

bool ElementBackgroundWidget::setGradient(std::string className)
{
	gradient_widget_->setValue(className);
	gradient_class = gradient_widget_->getValue(); 
	if(className.compare("none") == 0) return false;
	else {expand();return true;}
}

bool ElementBackgroundWidget::setAttachment(std::string className)
{
	attachment_widget_->setValue(className);
	attachment_class = attachment_widget_->getValue(); 
	if(className.compare("none") == 0) return false;
	else {expand();return true;}
}

bool ElementBackgroundWidget::setClip(std::string className)
{
	clip_widget_->setValue(className);
	clip_class = clip_widget_->getValue(); 
	if(className.compare("none") == 0) return false;
	else {expand();return true;}
}

bool ElementBackgroundWidget::setOrigin(std::string className)
{
	origin_widget_->setValue(className);
	origin_class = origin_widget_->getValue(); 
	if(className.compare("none") == 0) return false;
	else {expand();return true;}
}

bool ElementBackgroundWidget::setPosition(std::string className)
{
	position_widget_->setValue(className);
	position_class = position_widget_->getValue(); 
	if(className.compare("none") == 0) return false;
	else {expand();return true;}
}

bool ElementBackgroundWidget::setRepeat(std::string className)
{
	repeat_widget_->setValue(className);
	repeat_class = repeat_widget_->getValue(); 
	if(className.compare("none") == 0) return false;
	else {expand();return true;}
}

bool ElementBackgroundWidget::setSize(std::string className)
{
	size_widget_->setValue(className);
	size_class = size_widget_->getValue(); 
	if(className.compare("none") == 0) return false;
	else {expand();return true;}
}