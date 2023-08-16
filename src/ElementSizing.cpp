#include "include/ElementSizing.h"
#include <regex>

ElementSizingWidget::ElementSizingWidget(std::shared_ptr<Config> tailwindConfig)
	: tailwindConfig_(tailwindConfig)
{
	setStyleClass("min-w-fit max-w-[300px] !border-x-0 text-center !bg-neutral-700 !text-neutral-200");
	setTitle("Sizing");
	titleBarWidget()->setStyleClass("flex items-center space-x-3 !border-b border-solid border-neutral-500");
	setCollapsible(true);
	content_temp = setCentralWidget(std::make_unique<Wt::WTemplate>(tr("stylus-sizing-template")));

	auto resetBtn = titleBarWidget()->addWidget(std::make_unique<Wt::WText>());
	auto testBtn = titleBarWidget()->addWidget(std::make_unique<Wt::WText>());

	std::string buttons_styles ="p-2 m-px bg-cover ";
	
	resetBtn->setStyleClass(buttons_styles + "bg-[url(resources/icons/refresh.svg)] !ml-auto");
	testBtn->setStyleClass(buttons_styles + "bg-[url(resources/icons/experimental-glass.svg)] !mr-2");

	resetBtn->clicked().connect([=](){ resetStyles(); styleChanged_.emit(); isCollapsed() ? expand() : collapse();});
	testBtn->clicked().connect([=](){ setCustomTestValues(); styleChanged_.emit(); isCollapsed() ? expand() : collapse(); });




	width_widget_ = content_temp->bindWidget("width.control", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig_->sizing.width));
	height_widget_ = content_temp->bindWidget("height.control", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig_->sizing.height));

	minWidth_widget_ = content_temp->bindWidget("width.min.control", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig_->sizing.min_width));
	minHeight_widget_ = content_temp->bindWidget("height.min.control", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig_->sizing.min_height));

	maxWidth_widget_ = content_temp->bindWidget("width.max.control", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig_->sizing.max_width));
	maxHeight_widget_ = content_temp->bindWidget("height.max.control", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig_->sizing.max_height));

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
	std::string elementClasses;

	if(width_widget_->getValue().compare("none") != 0){ elementClasses += width_widget_->getValue() + " "; }
	if(minWidth_widget_->getValue().compare("none") != 0){ elementClasses += minWidth_widget_->getValue() + " "; }
	if(maxWidth_widget_->getValue().compare("none") != 0){ elementClasses += maxWidth_widget_->getValue() + " "; }
	 
	if(height_widget_->getValue().compare("none") != 0){ elementClasses += height_widget_->getValue() + " "; }
	if(minHeight_widget_->getValue().compare("none") != 0){ elementClasses += minHeight_widget_->getValue() + " "; }
	if(maxHeight_widget_->getValue().compare("none") != 0){ elementClasses += maxHeight_widget_->getValue() + " "; }

	return elementClasses;
}

void ElementSizingWidget::setClasses(SizingData sizing)
{
	resetStyles();
	// std::cout << "Element S I Z I N G Widget setStyleClasses -----------------------------------------\n";
	if(sizing.width.compare("") != 0) width_widget_->setValue(sizing.width);
	if(sizing.minWidth.compare("") != 0) minWidth_widget_->setValue(sizing.minWidth);
	if(sizing.maxWidth.compare("") != 0) maxWidth_widget_->setValue(sizing.maxWidth);

	if(sizing.height.compare("") != 0) height_widget_->setValue(sizing.height);
	if(sizing.minHeight.compare("") != 0) minHeight_widget_->setValue(sizing.minHeight);
	if(sizing.maxHeight.compare("") != 0) maxHeight_widget_->setValue(sizing.maxHeight);
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
