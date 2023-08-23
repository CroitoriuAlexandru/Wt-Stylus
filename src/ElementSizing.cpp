#include "include/ElementSizing.h"
#include <regex>

ElementSizingWidget::ElementSizingWidget(std::shared_ptr<Config> tailwindConfig)
	: tailwindConfig_(tailwindConfig)
{
	setStyleClass("min-w-fit max-w-[300px] !border-x-0 text-center !bg-neutral-700 !text-neutral-200 !border-neutral-900 px-1.5");
	setTitle("Sizing");
	titleBarWidget()->setStyleClass("flex items-center space-x-3 !border-b border-solid border-neutral-900");
	setCollapsible(true);

	auto resetBtn = titleBarWidget()->addWidget(std::make_unique<Wt::WText>());
	auto testBtn = titleBarWidget()->addWidget(std::make_unique<Wt::WText>());

	std::string buttons_styles ="p-2 m-px bg-cover ";
	
	resetBtn->setStyleClass(buttons_styles + "bg-[url(resources/icons/refresh.svg)] !ml-auto");
	testBtn->setStyleClass(buttons_styles + "bg-[url(resources/icons/experimental-glass.svg)] !mr-2");

	resetBtn->clicked().connect([=](){ resetStyles(); styleChanged_.emit(); isCollapsed() ? expand() : collapse();});
	testBtn->clicked().connect([=](){ setCustomTestValues(); styleChanged_.emit(); isCollapsed() ? expand() : collapse(); });


	auto centralWidget = setCentralWidget(std::make_unique<Wt::WContainerWidget>());
	auto width_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto height_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());

	centralWidget->setStyleClass("flex w-full max-w-[300px] space-x-2 p-1.5");
	width_wrapper->setStyleClass("flex flex-col w-1/2 items-stretch");
	height_wrapper->setStyleClass("flex flex-col w-1/2 items-stretch");

	width_wrapper->addWidget(std::make_unique<Wt::WText>("Width"))->setStyleClass("font-bold text-center text-neutral-400");
	height_wrapper->addWidget(std::make_unique<Wt::WText>("Height"))->setStyleClass("font-bold text-center text-neutral-400");

	width_widget_ = width_wrapper->addWidget(std::make_unique<StyleClassComboBox>(tailwindConfig_->sizing.width));
	minWidth_widget_ = width_wrapper->addWidget(std::make_unique<StyleClassComboBox>(tailwindConfig_->sizing.min_width));
	maxWidth_widget_ = width_wrapper->addWidget(std::make_unique<StyleClassComboBox>(tailwindConfig_->sizing.max_width));

	height_widget_ = height_wrapper->addWidget(std::make_unique<StyleClassComboBox>(tailwindConfig_->sizing.height));
	minHeight_widget_ = height_wrapper->addWidget(std::make_unique<StyleClassComboBox>(tailwindConfig_->sizing.min_height));
	maxHeight_widget_ = height_wrapper->addWidget(std::make_unique<StyleClassComboBox>(tailwindConfig_->sizing.max_height));


	// set regular expresion for custom value w-[10px]
	width_widget_->setCustomValueString("w-");
	height_widget_->setCustomValueString("h-");

	minWidth_widget_->setCustomValueString("min-w-");
	minHeight_widget_->setCustomValueString("min-h-");

	maxWidth_widget_->setCustomValueString("max-w-");
	maxHeight_widget_->setCustomValueString("max-h-");


	// signals for default classes for tailwind
	width_widget_->classChanged().connect(this, [=]() { styleChanged_.emit(); });
	height_widget_->classChanged().connect(this, [=]() { styleChanged_.emit(); });

	minWidth_widget_->classChanged().connect(this, [=]() { styleChanged_.emit(); });
	minHeight_widget_->classChanged().connect(this, [=]() { styleChanged_.emit(); });

	maxWidth_widget_->classChanged().connect(this, [=]() { styleChanged_.emit(); });
	maxHeight_widget_->classChanged().connect(this, [=]() { styleChanged_.emit(); });
};

std::string ElementSizingWidget::getStyles()
{
	bool activeClasses = false;
	std::string elementClasses;

	if(width_widget_->getValue().compare("none") != 0){ elementClasses += width_widget_->getValue() + " "; activeClasses = true; }
	if(minWidth_widget_->getValue().compare("none") != 0){ elementClasses += minWidth_widget_->getValue() + " "; activeClasses = true; }
	if(maxWidth_widget_->getValue().compare("none") != 0){ elementClasses += maxWidth_widget_->getValue() + " "; activeClasses = true; }
	 
	if(height_widget_->getValue().compare("none") != 0){ elementClasses += height_widget_->getValue() + " "; activeClasses = true; }
	if(minHeight_widget_->getValue().compare("none") != 0){ elementClasses += minHeight_widget_->getValue() + " "; activeClasses = true; }
	if(maxHeight_widget_->getValue().compare("none") != 0){ elementClasses += maxHeight_widget_->getValue() + " "; activeClasses = true; }

	if(activeClasses) expand();
	else collapse();

	return elementClasses;
}

void ElementSizingWidget::setClasses(SizingData sizing)
{
	bool activeClasses = false;
	resetStyles();
	// std::cout << "Element S I Z I N G Widget setStyleClasses -----------------------------------------\n";

	if(sizing.width.compare("none") != 0){ width_widget_->setValue(sizing.width); activeClasses = true; }
	if(sizing.minWidth.compare("none") != 0){ minWidth_widget_->setValue(sizing.minWidth); activeClasses = true; }
	if(sizing.maxWidth.compare("none") != 0){ maxWidth_widget_->setValue(sizing.maxWidth); activeClasses = true; }

	if(sizing.height.compare("none") != 0){ height_widget_->setValue(sizing.height); activeClasses = true; }
	if(sizing.minHeight.compare("none") != 0){ minHeight_widget_->setValue(sizing.minHeight); activeClasses = true; }
	if(sizing.maxHeight.compare("none") != 0){ maxHeight_widget_->setValue(sizing.maxHeight); activeClasses = true; }
	
	if(activeClasses) expand(); 
	else collapse();
}

void ElementSizingWidget::resetStyles()
{
	width_widget_->setValue("none");
	minWidth_widget_->setValue("none");
	maxWidth_widget_->setValue("none");

	height_widget_->setValue("none");
	minHeight_widget_->setValue("none");
	maxHeight_widget_->setValue("none");
}

void ElementSizingWidget::setCustomTestValues()
{
	width_widget_->setValue("w-1/2");
	minWidth_widget_->setValue("min-w-full");
	maxWidth_widget_->setValue("max-w-[300px]");
	height_widget_->setValue("h-1/2");
	minHeight_widget_->setValue("min-h-full");
	maxHeight_widget_->setValue("max-h-[300px]");
}
