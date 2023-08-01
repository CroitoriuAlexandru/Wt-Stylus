#include <Wt/WTemplate.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WComboBox.h>
#include "ComboBoxes.h"
#include <Wt/WDialog.h>
#
struct BackgroundStyleClasses {
	std::vector<std::string> color_classes_;
	std::vector<std::string> color_intensity;
	std::vector<std::string> opacity;
	
	BackgroundStyleClasses();
};

struct ColorsData
{
	std::string color_class;
	std::string color_intensity;
	std::string color_opacity;
};


class ElementBackgroundWidget : public Wt::WDialog
{
public:
	ElementBackgroundWidget(std::string templateName = "stylus.background.template");
	// margin and padding at the moment

	void setClasses(std::vector<std::string> styleClasses);
    Wt::Signal<>& styleChanged() { return styleChanged_; }
	std::string getStyles();
	void resetStyles();

private:

	ComboBoxColors *comboBox_color;

	Wt::Signal<> styleChanged_;

	// sizing custom regexp
	std::regex regex_custom_sizing =  std::regex("bg-\\[[\\S]*\\]");

};

