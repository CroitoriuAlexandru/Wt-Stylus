#include <Wt/WTemplate.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WComboBox.h>
#include "ComboBoxClassChanger.h"
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
    Wt::Signal<std::string>& styleChanged() { return styleChanged_; }
	std::string getStyles();
	void resetStyles();


	bool setMarginAll(std::string className);
	bool setMarginY(std::string className);
	bool setMarginX(std::string className);
	bool setMarginTop(std::string className);
	bool setMarginRight(std::string className);
	bool setMarginBottom(std::string className);
	bool setMarginLeft(std::string className);

	bool setPaddingAll(std::string className);
	bool setPaddingY(std::string className);
	bool setPaddingX(std::string className);
	bool setPaddingTop(std::string className);
	bool setPaddingRight(std::string className);
	bool setPaddingBottom(std::string className);
	bool setPaddingLeft(std::string className);
	
	bool setSpaceX(std::string className);
	bool setSpaceY(std::string className);

	bool setSpaceXReverse(bool reverse);
	bool setSpaceYReverse(bool reverse);

private:
	ComboBoxClassChanger* margin_all_widget_;
    ComboBoxClassChanger* margin_y_widget_;
    ComboBoxClassChanger* margin_x_widget_;
    ComboBoxClassChanger* margin_top_widget_;
    ComboBoxClassChanger* margin_right_widget_;
    ComboBoxClassChanger* margin_bottom_widget_;
    ComboBoxClassChanger* margin_left_widget_;

    ComboBoxClassChanger* padding_all_widget_;
    ComboBoxClassChanger* padding_y_widget_;
    ComboBoxClassChanger* padding_x_widget_;
    ComboBoxClassChanger* padding_top_widget_;
    ComboBoxClassChanger* padding_right_widget_;
    ComboBoxClassChanger* padding_bottom_widget_;
    ComboBoxClassChanger* padding_left_widget_;

	ComboBoxClassChanger* space_x_widget_;
	ComboBoxClassChanger* space_y_widget_;

	Wt::WCheckBox* checkbox_space_x_reverse_;
	Wt::WCheckBox* checkbox_space_y_reverse_;


	std::string margin_all_class = "none";
	std::string margin_y_class = "none";
	std::string margin_x_class = "none";
	std::string margin_top_class = "none";
	std::string margin_right_class = "none";
	std::string margin_bottom_class = "none";
	std::string margin_left_class = "none";

	std::string padding_all_class = "none";
	std::string padding_y_class = "none";
	std::string padding_x_class = "none";
	std::string padding_top_class = "none";
	std::string padding_right_class = "none";
	std::string padding_bottom_class = "none";
	std::string padding_left_class = "none";

	std::string space_x_class = "none";
	std::string space_y_class = "none";


	void setCustomTestValues();

	std::shared_ptr<Config> tailwindConfig_;

	Wt::Signal<std::string> styleChanged_;

	std::regex regex_custom_padding =  std::regex("p[x,y,l,r,t,b]?-\\[[\\S]*\\]"); 
	std::regex regex_custom_margin =  std::regex("-?m[x,y,l,r,t,b]?-\\[[\\S]*\\]");
	std::regex regex_custom_space =  std::regex("space-[x|y]?-\\[[\\S]*\\]");
};
