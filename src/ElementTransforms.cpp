#include "include/ElementTransforms.h"
#include <regex>
#include <string>

ElementTransformsWidget::ElementTransformsWidget(std::shared_ptr<Config> tailwindConfig)
	: tailwindConfig_(tailwindConfig)
{

	setStyleClass("min-w-fit max-w-[300px] !border-x-0 text-center !bg-neutral-700 !text-neutral-200 !border-neutral-900");
	setTitle("Transforms");
	titleBarWidget()->setStyleClass("flex items-center space-x-3 !border-b border-solid border-neutral-900");
	setCollapsible(true);
	content_temp = setCentralWidget(std::make_unique<Wt::WTemplate>(tr("stylus-transform-template")));

	auto resetBtn = titleBarWidget()->addWidget(std::make_unique<Wt::WText>());
	auto testBtn = titleBarWidget()->addWidget(std::make_unique<Wt::WText>());

	std::string buttons_styles ="p-2 m-px bg-cover hover:bg-neutral-900 rounded-md ";
	
	resetBtn->setStyleClass(buttons_styles + "bg-[url(resources/icons/refresh.svg)] !ml-auto");
	testBtn->setStyleClass(buttons_styles + "bg-[url(resources/icons/experimental-glass.svg)] !mr-2");

	resetBtn->clicked().connect([=](){ resetStyles(); styleChanged_.emit(); isCollapsed() ? expand() : collapse();});
	testBtn->clicked().connect([=](){ setCustomTestValues(); styleChanged_.emit(); isCollapsed() ? expand() : collapse(); });

	comboBox_scale_ = content_temp->bindWidget("combobox-scale", std::make_unique<StyleClassComboBox>(tailwindConfig->transforms.scale));
	comboBox_scale_x_ = content_temp->bindWidget("combobox-scale-x", std::make_unique<StyleClassComboBox>(tailwindConfig->transforms.scale_x));
	comboBox_scale_y_ = content_temp->bindWidget("combobox-scale-y", std::make_unique<StyleClassComboBox>(tailwindConfig->transforms.scale_y));
	comboBox_rotate_ = content_temp->bindWidget("combobox-rotate", std::make_unique<StyleClassComboBox>(tailwindConfig->transforms.rotate));
	comboBox_translate_x_ = content_temp->bindWidget("combobox-translate-x", std::make_unique<StyleClassComboBox>(tailwindConfig->transforms.translate_x));
	comboBox_translate_y_ = content_temp->bindWidget("combobox-translate-y", std::make_unique<StyleClassComboBox>(tailwindConfig->transforms.translate_y));
	comboBox_skew_x_ = content_temp->bindWidget("combobox-skew-x", std::make_unique<StyleClassComboBox>(tailwindConfig->transforms.skew_x));
	comboBox_skew_y_ = content_temp->bindWidget("combobox-skew-y", std::make_unique<StyleClassComboBox>(tailwindConfig->transforms.skew_y));
	comboBox_transform_origin_ = content_temp->bindWidget("combobox-transform-origin", std::make_unique<StyleClassComboBox>(tailwindConfig->transforms.transform_origin));


	// comboBox_scale_->setCustomValueString("scale-");
	// comboBox_scale_x_->setCustomValueString("scale-x-");
	// comboBox_scale_y_->setCustomValueString("scale-y-");
	// comboBox_rotate_->setCustomValueString("rotate-");
	// comboBox_translate_x_->setCustomValueString("translate-x-");
	// comboBox_translate_y_->setCustomValueString("translate-y-");
	// comboBox_skew_x_->setCustomValueString("skew-x-");
	// comboBox_skew_y_->setCustomValueString("skew-y-");
	// comboBox_transform_origin_->setCustomValueString("origin-");

	
	// signals for default classes for tailwind
	comboBox_scale_->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_scale_x_->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_scale_y_->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_rotate_->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_translate_x_->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_translate_y_->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_skew_x_->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_skew_y_->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_transform_origin_->classChanged().connect([=](){ styleChanged_.emit(); });

};

std::string ElementTransformsWidget::getStyles()
{
	std::string elementClasses;

	if(comboBox_scale_->getValue().compare("none") != 0){ elementClasses += comboBox_scale_->getValue() + " "; }
	if(comboBox_scale_x_->getValue().compare("none") != 0){ elementClasses += comboBox_scale_x_->getValue() + " "; }
	if(comboBox_scale_y_->getValue().compare("none") != 0){ elementClasses += comboBox_scale_y_->getValue() + " "; }
	if(comboBox_rotate_->getValue().compare("none") != 0){ elementClasses += comboBox_rotate_->getValue() + " "; }
	if(comboBox_translate_x_->getValue().compare("none") != 0){ elementClasses += comboBox_translate_x_->getValue() + " "; }
	if(comboBox_translate_y_->getValue().compare("none") != 0){ elementClasses += comboBox_translate_y_->getValue() + " "; }
	if(comboBox_skew_x_->getValue().compare("none") != 0){ elementClasses += comboBox_skew_x_->getValue() + " "; }
	if(comboBox_skew_y_->getValue().compare("none") != 0){ elementClasses += comboBox_skew_y_->getValue() + " "; }
	if(comboBox_transform_origin_->getValue().compare("none") != 0){ elementClasses += comboBox_transform_origin_->getValue() + " "; }

	return elementClasses;
}

void ElementTransformsWidget::setClasses(TransformsData transformsData)
{
	resetStyles();
	for(auto& scale_class : transformsData.scale){
		if(scale_class.find("scale-x-") != std::string::npos){
			comboBox_scale_x_->setValue(scale_class);
		}else if(scale_class.find("scale-y-") != std::string::npos){
			comboBox_scale_y_->setValue(scale_class);
		}else if(scale_class.find("scale-") != std::string::npos){
			comboBox_scale_->setValue(scale_class);
		}
	}
	
	comboBox_rotate_->setValue(transformsData.rotate);
	for(auto& translate_class : transformsData.translate){
		if(translate_class.find("translate-x-") != std::string::npos){
			comboBox_translate_x_->setValue(translate_class);
		}else if(translate_class.find("translate-y-") != std::string::npos){
			comboBox_translate_y_->setValue(translate_class);
		}
	}
	for(auto& skew_class : transformsData.skew){
		if(skew_class.find("skew-x-") != std::string::npos){
			comboBox_skew_x_->setValue(skew_class);
		}else if(skew_class.find("skew-y-") != std::string::npos){
			comboBox_skew_y_->setValue(skew_class);
		}
	}
	comboBox_transform_origin_->setValue(transformsData.transform_origin);

}

void ElementTransformsWidget::resetStyles()
{
	comboBox_scale_->setValue("none");
	comboBox_scale_x_->setValue("none");
	comboBox_scale_y_->setValue("none");
	comboBox_rotate_->setValue("none");
	comboBox_translate_x_->setValue("none");
	comboBox_translate_y_->setValue("none");
	comboBox_skew_x_->setValue("none");
	comboBox_skew_y_->setValue("none");
	comboBox_transform_origin_->setValue("none");
}

void ElementTransformsWidget::setCustomTestValues()
{
	comboBox_scale_->setValue("scale-50");
	comboBox_scale_x_->setValue("scale-x-50");
	comboBox_scale_y_->setValue("scale-y-50");
	comboBox_rotate_->setValue("rotate-45");
	comboBox_translate_x_->setValue("translate-x-52");
	comboBox_translate_y_->setValue("translate-y-52");
	comboBox_skew_x_->setValue("skew-x-50");
	comboBox_skew_y_->setValue("skew-y-50");
	comboBox_transform_origin_->setValue("origin-center");
}
