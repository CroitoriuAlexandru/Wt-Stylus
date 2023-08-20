#include <Wt/WTemplate.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WComboBox.h>
#include "ComboBoxes.h"
#include <Wt/WDialog.h>
#include <Wt/WPanel.h>

struct TransformsData
{
	std::vector<std::string> scale;
	std::string rotate;
	std::vector<std::string> translate;
	std::vector<std::string> skew;
	std::string transform_origin;
};


class ElementTransformsWidget : public Wt::WPanel
{
public:
	ElementTransformsWidget(std::shared_ptr<Config> tailwindConfig);
	// margin and padding at the moment


	void setClasses(TransformsData transformsData);
    Wt::Signal<>& styleChanged() { return styleChanged_; };
	std::string getStyles();
	void resetStyles();
private:
	void setCustomTestValues();
	
	Wt::WTemplate* 				content_temp;
	std::shared_ptr<Config> 	tailwindConfig_;
	
	StyleClassComboBox* 		comboBox_scale_;
	StyleClassComboBox* 		comboBox_scale_x_;
	StyleClassComboBox* 		comboBox_scale_y_;
	StyleClassComboBox* 		comboBox_rotate_;
	StyleClassComboBox* 		comboBox_translate_x_;
	StyleClassComboBox* 		comboBox_translate_y_;
	StyleClassComboBox* 		comboBox_skew_x_;
	StyleClassComboBox* 		comboBox_skew_y_;
	StyleClassComboBox* 		comboBox_transform_origin_;

	Wt::Signal<> styleChanged_;
};