#include "include/ElementEffects.h"
#include <regex>
#include <string>

ElementEffectsWidget::ElementEffectsWidget(std::shared_ptr<Config> tailwindConfig)
	: tailwindConfig_(tailwindConfig)
{

	setStyleClass("min-w-fit max-w-[300px] !border-x-0 text-center !bg-neutral-700 !text-neutral-200 !border-neutral-900");
	setTitle("Effects");
	titleBarWidget()->setStyleClass("flex items-center space-x-3 !border-b border-solid border-neutral-900");
	setCollapsible(true);
	content_temp = setCentralWidget(std::make_unique<Wt::WTemplate>(tr("stylus-effects-template")));

	auto resetBtn = titleBarWidget()->addWidget(std::make_unique<Wt::WText>());
	auto testBtn = titleBarWidget()->addWidget(std::make_unique<Wt::WText>());

	std::string buttons_styles ="p-2 m-px bg-cover ";
	
	resetBtn->setStyleClass(buttons_styles + "bg-[url(resources/icons/refresh.svg)] !ml-auto");
	testBtn->setStyleClass(buttons_styles + "bg-[url(resources/icons/experimental-glass.svg)] !mr-2");

	resetBtn->clicked().connect([=](){ resetStyles(); styleChanged_.emit(); isCollapsed() ? expand() : collapse();});
	testBtn->clicked().connect([=](){ setCustomTestValues(); styleChanged_.emit(); isCollapsed() ? expand() : collapse(); });


	comboBox_box_shadow = content_temp->bindWidget("combobox-box-shadow", std::make_unique<StyleClassComboBox>(tailwindConfig->effects.box_shadow));
	checkBox_box_shadow_inner = content_temp->bindWidget("checkbox-box-shadow-inset", std::make_unique<Wt::WCheckBox>("Shaddow Inset"));
	// box_shadow_color = content_temp->bindWidget("combobox-box-shadow-color", std::make_unique<ColorsComboBox>(tailwindConfig->effects.box_shadow_color));
	comboBox_opacity = content_temp->bindWidget("combobox-opacity", std::make_unique<StyleClassComboBox>(tailwindConfig->effects.opacity));
	comboBox_mix_blend_mode = content_temp->bindWidget("combobox-mix-blend-mode", std::make_unique<StyleClassComboBox>(tailwindConfig->effects.mix_blend_mode)); 
	comboBox_bg_blend_mode = content_temp->bindWidget("combobox-bg-blend-mode", std::make_unique<StyleClassComboBox>(tailwindConfig->effects.background_blend_mode));

	comboBox_box_shadow->setCustomValueString("shadow-");
	// box_shadow_color->setCustomValueString("shadow-");
	comboBox_mix_blend_mode->setCustomValueString("mix-blend-");
	comboBox_bg_blend_mode->setCustomValueString("bg-blend-");


	// // deactivate custom checkbox
	comboBox_box_shadow->checkBox_custom_value_->hide();
	// box_shadow_color->checkBox_custom_value_->hide();
	comboBox_mix_blend_mode->checkBox_custom_value_->hide();
	comboBox_opacity->checkBox_custom_value_->hide();
	comboBox_bg_blend_mode->checkBox_custom_value_->hide();
	// checkBox_box_shadow_inner->setChecked(false);



	// signals for default classes for tailwind
	comboBox_box_shadow->classChanged().connect([=](){ styleChanged_.emit(); });
	checkBox_box_shadow_inner->changed().connect([=](){ styleChanged_.emit(); });
	// box_shadow_color->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_opacity->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_mix_blend_mode->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_bg_blend_mode->classChanged().connect([=](){ styleChanged_.emit(); });



};

std::string ElementEffectsWidget::getStyles()
{
	std::string elementClasses;

	if(comboBox_box_shadow->getValue().compare("none") != 0){ elementClasses += comboBox_box_shadow->getValue() + " "; }
	if(checkBox_box_shadow_inner->isChecked()){ elementClasses += "shadow-inner "; }
	if(comboBox_opacity->getValue().compare("none") != 0){ elementClasses += comboBox_opacity->getValue() + " "; }
	// if(box_shadow_color->getValue().compare("none") != 0){ elementClasses += box_shadow_color->getValue() + " "; }
	if(comboBox_mix_blend_mode->getValue().compare("none") != 0){ elementClasses += comboBox_mix_blend_mode->getValue() + " "; }
	if(comboBox_bg_blend_mode->getValue().compare("none") != 0){ elementClasses += comboBox_bg_blend_mode->getValue() + " "; }
	return elementClasses;
}

void ElementEffectsWidget::setClasses(EffectsData effectsData)
{
	resetStyles();

	comboBox_box_shadow->setValue(effectsData.boxShadow);
	checkBox_box_shadow_inner->setChecked(effectsData.boxShadowInner);
	comboBox_opacity->setValue(effectsData.opacity);
	// box_shadow_color->setValue(effectsData.boxShadowColor);
	comboBox_mix_blend_mode->setValue(effectsData.mixBlendMode);
	comboBox_bg_blend_mode->setValue(effectsData.backgroundBlendMode);
}

void ElementEffectsWidget::resetStyles()
{
	comboBox_box_shadow->setValue("none");
	checkBox_box_shadow_inner->setChecked(false);
	// box_shadow_color->setValue("none");
	comboBox_opacity->setValue("none");
	comboBox_mix_blend_mode->setValue("none");
	comboBox_bg_blend_mode->setValue("none");
}

void ElementEffectsWidget::setCustomTestValues()
{
	comboBox_box_shadow->setValue("shadow-md");
	checkBox_box_shadow_inner->setChecked(true);
	// box_shadow_color->setValue("shadow-red-500/40");
	comboBox_opacity->setValue("opacity-50");
	comboBox_mix_blend_mode->setValue("mix-blend-color");
	comboBox_bg_blend_mode->setValue("bg-blend-color");
}
