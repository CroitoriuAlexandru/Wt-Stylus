#include "include/ElementSizing.h"
#include <regex>
#include <Wt/WPopupMenu.h>
#include <Wt/WMenuItem.h>
#include <Wt/WLink.h>

ElementSizingWidget::ElementSizingWidget(std::shared_ptr<Config> tailwindConfig)
	: tailwindConfig_(tailwindConfig)
{
	setStyleClass("min-w-fit max-w-[300px] !border-x-0 text-center !bg-neutral-700 !text-neutral-200 !border-neutral-900 px-1.5");
	setTitle("Sizing");
	titleBarWidget()->setStyleClass("flex items-center space-x-3 !border-b border-solid border-neutral-900 bg-neutral-800");
	setCollapsible(true);
	
	auto popupMenu = std::make_unique<Wt::WPopupMenu>();
	std::string menuItemsStyles = "p-2 m-1 hover:bg-neutral-800 hover:text-neutral-200";
	popupMenu->addItem("Set test classes")->setStyleClass(menuItemsStyles);
	popupMenu->addItem("Reset styles")->setStyleClass(menuItemsStyles);
	popupMenu->addSeparator()->setStyleClass("border border-solid border-neutral-900");

	auto width_info = popupMenu->addItem("Info Width");
	auto min_width_info = popupMenu->addItem("Info Min width");
	auto max_width_info = popupMenu->addItem("Info Max width");
	auto height_info = popupMenu->addItem("Info Height");
	auto min_height_info = popupMenu->addItem("Info Min height");
	auto max_height_info = popupMenu->addItem("Info Max height");

	Wt::WLink width_link = Wt::WLink(tailwindConfig_->sizing.width.docsLink_);
	Wt::WLink max_width_link = Wt::WLink(tailwindConfig_->sizing.max_width.docsLink_);
	Wt::WLink min_width_link = Wt::WLink(tailwindConfig_->sizing.min_width.docsLink_);
	Wt::WLink height_link = Wt::WLink(tailwindConfig_->sizing.height.docsLink_);
	Wt::WLink max_height_link = Wt::WLink(tailwindConfig_->sizing.max_height.docsLink_);
	Wt::WLink min_height_link = Wt::WLink(tailwindConfig_->sizing.min_height.docsLink_);

	width_link.setTarget(Wt::LinkTarget::NewWindow);
	max_width_link.setTarget(Wt::LinkTarget::NewWindow);
	min_width_link.setTarget(Wt::LinkTarget::NewWindow);
	height_link.setTarget(Wt::LinkTarget::NewWindow);
	max_height_link.setTarget(Wt::LinkTarget::NewWindow);
	min_height_link.setTarget(Wt::LinkTarget::NewWindow);

	width_info->setLink(width_link);
	max_width_info->setLink(max_width_link);
	min_width_info->setLink(min_width_link);
	height_info->setLink(height_link);
	max_height_info->setLink(max_height_link);
	min_height_info->setLink(min_height_link);

	width_info->setStyleClass(menuItemsStyles);
	max_width_info->setStyleClass(menuItemsStyles);
	min_width_info->setStyleClass(menuItemsStyles);
	height_info->setStyleClass(menuItemsStyles);
	max_height_info->setStyleClass(menuItemsStyles);
	min_height_info->setStyleClass(menuItemsStyles);

	
	popupMenu->setStyleClass("bg-neutral-700 text-neutral-200 border border-solid border-neutral-900");

	popupMenu->triggered().connect(this, [=](Wt::WMenuItem *item) {
		if(item->text().toUTF8().compare("Set test classes") == 0){
			std::cout << "set test classes" << std::endl;
			setCustomTestValues();
			styleChanged_.emit(getStyles());
		}else if(item->text().toUTF8().compare("Reset styles") == 0){
			resetStyles();
			styleChanged_.emit(getStyles());
		}
	});

	auto popupBtn = titleBarWidget()->addWidget(std::make_unique<Wt::WPushButton>());
	popupBtn->setStyleClass("p-3 bg-cover bg-[url(resources/icons/hamburger.svg)] !ml-auto mr-2 ");
	popupBtn->setMenu(std::move(popupMenu));
	
	// prevent the click event from propagating to the parent because it is located in the title bar witch expands and collapse on click
	popupBtn->clicked().preventPropagation();


	auto centralWidget = setCentralWidget(std::make_unique<Wt::WContainerWidget>());
	auto width_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto height_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());

	centralWidget->setStyleClass("flex w-full max-w-[300px] space-x-2 p-1.5");
	width_wrapper->setStyleClass("flex flex-col w-1/2 items-stretch");
	height_wrapper->setStyleClass("flex flex-col w-1/2 items-stretch");

	width_wrapper->addWidget(std::make_unique<Wt::WText>("Width"))->setStyleClass("font-bold text-center text-neutral-400");
	height_wrapper->addWidget(std::make_unique<Wt::WText>("Height"))->setStyleClass("font-bold text-center text-neutral-400");

	width_widget_ = width_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig_->sizing.width));
	minWidth_widget_ = width_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig_->sizing.min_width));
	maxWidth_widget_ = width_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig_->sizing.max_width));

	height_widget_ = height_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig_->sizing.height));
	minHeight_widget_ = height_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig_->sizing.min_height));
	maxHeight_widget_ = height_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig_->sizing.max_height));


	// set regular expresion for custom value w-[10px]
	width_widget_->setCustomValueString("w-");
	height_widget_->setCustomValueString("h-");

	minWidth_widget_->setCustomValueString("min-w-");
	minHeight_widget_->setCustomValueString("min-h-");

	maxWidth_widget_->setCustomValueString("max-w-");
	maxHeight_widget_->setCustomValueString("max-h-");

	// signals for default classes for tailwind
	width_widget_->classChanged().connect(this, [=](std::string className) { width_class = className; styleChanged_.emit(getStyles()); });
	height_widget_->classChanged().connect(this, [=](std::string className) { height_class = className; styleChanged_.emit(getStyles()); });

	minWidth_widget_->classChanged().connect(this, [=](std::string className) { minWidth_class = className; styleChanged_.emit(getStyles()); });
	minHeight_widget_->classChanged().connect(this, [=](std::string className) { minHeight_class = className; styleChanged_.emit(getStyles()); });

	maxWidth_widget_->classChanged().connect(this, [=](std::string className) { maxWidth_class = className; styleChanged_.emit(getStyles()); });
	maxHeight_widget_->classChanged().connect(this, [=](std::string className) { maxHeight_class = className; styleChanged_.emit(getStyles()); });
};

std::string ElementSizingWidget::getStyles()
{
	bool activeClasses = false;
	std::string elementClasses;

	if(width_class.compare("none") != 0){ elementClasses += width_class + " "; activeClasses = true; }
	if(minWidth_class.compare("none") != 0){ elementClasses += minWidth_class + " "; activeClasses = true; }
	if(maxWidth_class.compare("none") != 0){ elementClasses += maxWidth_class + " "; activeClasses = true; }
	
	if(height_class.compare("none") != 0){ elementClasses += height_class + " "; activeClasses = true; }
	if(minHeight_class.compare("none") != 0){ elementClasses += minHeight_class + " "; activeClasses = true; }
	if(maxHeight_class.compare("none") != 0){ elementClasses += maxHeight_class + " "; activeClasses = true; }


	if(activeClasses && isCollapsed()) expand();

	return elementClasses;
}

void ElementSizingWidget::setClasses(SizingData sizing)
{
	resetStyles();
	bool activeClasses;
	activeClasses = setWidth(sizing.width);
	activeClasses = setHeight(sizing.height);
	activeClasses = setMinWidth(sizing.minWidth);
	activeClasses = setMinHeight(sizing.minHeight);
	activeClasses = setMaxWidth(sizing.maxWidth);
	activeClasses = setMaxHeight(sizing.maxHeight);

	if(!activeClasses) collapse();
}


void ElementSizingWidget::resetStyles()
{
	setWidth("none");
	setHeight("none");
	setMinWidth("none");
	setMinHeight("none");
	setMaxWidth("none");
	setMaxHeight("none");
}

void ElementSizingWidget::setCustomTestValues()
{
	setWidth("w-1/2");
	setHeight("h-1/2");
	setMinWidth("min-w-full");
	setMinHeight("min-h-full");
	setMaxWidth("max-w-[300px]");
	setMaxHeight("max-h-[300px]");
}



bool ElementSizingWidget::setWidth(std::string className)
{

	width_class = className;
	width_widget_->setValue(width_class);

	if(className.compare("none") == 0) return false;
	else {
		expand();
		return true;
	}
}

bool ElementSizingWidget::setHeight(std::string className)
{
	height_class = className;
	height_widget_->setValue(height_class);

	if(className.compare("none") == 0) return false;
	else {
		expand();
		return true;
	}
}

bool ElementSizingWidget::setMinWidth(std::string className)
{
	minWidth_class = className;
	minWidth_widget_->setValue(minWidth_class);

	if(className.compare("none") == 0) return false;
	else {
		expand();
		return true;
	}
}

bool ElementSizingWidget::setMinHeight(std::string className)
{
	minHeight_class = className;
	minHeight_widget_->setValue(minHeight_class);

	if(className.compare("none") == 0) return false;
	else {
		expand();
		return true;
	}
}

bool ElementSizingWidget::setMaxWidth(std::string className)
{
	maxWidth_class = className;
	maxWidth_widget_->setValue(maxWidth_class);

	if(className.compare("none") == 0) return false;
	else {
		expand();
		return true;
	}
}

bool ElementSizingWidget::setMaxHeight(std::string className)
{
	maxHeight_class = className;
	maxHeight_widget_->setValue(maxHeight_class);

	if(className.compare("none") == 0) return false;
	else {
		expand();
		return true;
	}
}

