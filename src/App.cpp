#include "include/App.h"
#include "include/Stylus.h"
#include "include/StylusTemplates.h"
#include <Wt/WPushButton.h>
#include <Wt/WTemplate.h>
#include <Wt/DomElement.h>

#include "include/TailwindTheme.h"
#include <Wt/WBootstrap5Theme.h>
#include <Wt/WBootstrap2Theme.h>
#include <Wt/WTimer.h>

App::App(const Wt::WEnvironment &env)
	: Wt::WApplication(env)
{
	setTitle("Starter Wt Application");
	// messageResourceBundle().use(appRoot() + "resources/xmlTest/Defoult-Styles/Elements");
	// messageResourceBundle().use(appRoot() + "resources/xmlTest/StylusUi");


	auto defStyles = Wt::WLink("resources/themes/someDefaultStyles.css");

	setCssTheme("default");
	useStyleSheet(defStyles);

	globalKeyWentDown().preventDefaultAction(true);
	
	// add custom javascript files
	// require("https://cdn.jsdelivr.net/npm/alpinejs@3.x.x/dist/cdn.min.js"); // testing for future integration with stylus
	require("https://cdn.tailwindcss.com");
	require("resources/Js/Utility.js"); // tailwind theme styles customize from here

	// add mesage resource bundle from templates
	auto stylus_edditor = root()->addWidget(std::make_unique<StylusEdditor>("resources/xmlTest/"));

	stylus_edditor->setTemplate("templates", "Application.xml", "app-root", "template");



}

