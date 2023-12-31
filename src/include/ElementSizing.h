#include <Wt/WTemplate.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WComboBox.h>
#include "ComboBoxes.h"
#include <Wt/WDialog.h>
#include <Wt/WPanel.h>

struct SizingData
{
	std::string width = "none";
	std::string minWidth = "none";
	std::string maxWidth = "none";

	std::string height = "none";
	std::string minHeight = "none";
	std::string maxHeight = "none";
};


class ElementSizingWidget : public Wt::WPanel
{
public:
	ElementSizingWidget(std::shared_ptr<Config> tailwindConfig);
	// margin and padding at the moment

	void setClasses(SizingData sizing);
    Wt::Signal<>& styleChanged() { return styleChanged_; }
	std::string getStyles();
	void resetStyles();

	StyleClassComboBox* width_widget_;
	StyleClassComboBox* minWidth_widget_;
	StyleClassComboBox* maxWidth_widget_;

	StyleClassComboBox* height_widget_;
	StyleClassComboBox* minHeight_widget_;
	StyleClassComboBox* maxHeight_widget_;
private:
	void setCustomTestValues();
	
    std::shared_ptr<Config> tailwindConfig_;

	Wt::Signal<> styleChanged_;

	// sizing custom regexp
	std::regex regex_custom_sizing =  std::regex("[!]?[w|h]-\\[[\\S]*\\]");
	std::regex regex_custom_min_max_sizing =  std::regex("[!]?[min|max]-w-\\[[\\S]*\\]");

};

