#include <Wt/WTemplate.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WComboBox.h>
#include "ComboBoxes.h"
#include <Wt/WDialog.h>
#include <Wt/WPanel.h>
struct SpacingData
{
	std::vector<std::string> padding;
	std::vector<std::string> margin;
	std::vector<std::string> space;
};

class ElementSpacingWidget : public Wt::WPanel
{
public:
	ElementSpacingWidget(std::shared_ptr<Config> tailwindConfig);
	// margin and padding at the moment

	void setClasses(SpacingData spacing);
    Wt::Signal<>& styleChanged() { return styleChanged_; }
	std::string getStyles();
	void resetStyles();

private:
	void setCustomTestValues();

	std::shared_ptr<Config> tailwindConfig_;
	Wt::WTemplate* content_temp;

	ComboBoxClassWithCustoms* margin_all_widget_;
    ComboBoxClassWithCustoms* margin_horizontal_widget_;
    ComboBoxClassWithCustoms* margin_vertical_widget_;
    ComboBoxClassWithCustoms* margin_top_widget_;
    ComboBoxClassWithCustoms* margin_right_widget_;
    ComboBoxClassWithCustoms* margin_bottom_widget_;
    ComboBoxClassWithCustoms* margin_left_widget_;

    ComboBoxClassWithCustoms* padding_all_widget_;
    ComboBoxClassWithCustoms* padding_horizontal_widget_;
    ComboBoxClassWithCustoms* padding_vertical_widget_;
    ComboBoxClassWithCustoms* padding_top_widget_;
    ComboBoxClassWithCustoms* padding_right_widget_;
    ComboBoxClassWithCustoms* padding_bottom_widget_;
    ComboBoxClassWithCustoms* padding_left_widget_;

	ComboBoxClassWithCustoms* space_vertical_widget_;
	ComboBoxClassWithCustoms* space_horizontal_widget_;

	Wt::Signal<> styleChanged_;

	Wt::WCheckBox* checkbox_space_x_reverse_;
	Wt::WCheckBox* checkbox_space_y_reverse_;

	std::regex regex_custom_padding =  std::regex("p[x,y,l,r,t,b]?-\\[[\\S]*\\]"); 
	std::regex regex_custom_margin =  std::regex("-?m[x,y,l,r,t,b]?-\\[[\\S]*\\]");
	std::regex regex_custom_space =  std::regex("space-[x|y]?-\\[[\\S]*\\]");
};
