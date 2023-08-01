#pragma once
#include <Wt/WApplication.h>
#include "Stylus.h"

class App : public Wt::WApplication
{
public:
    App(const Wt::WEnvironment &env);
private:
    StylusEdditor* stylus_edditor;
    std::string appDevId;
};