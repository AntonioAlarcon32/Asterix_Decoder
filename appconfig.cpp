#include "appconfig.h"

AppConfig::AppConfig()
{
    this->value = 0;
}

AppConfig* AppConfig::GetInstance() {

    if(appConfig_==nullptr){
            appConfig_ = new AppConfig();
        }
        return appConfig_;
}

void AppConfig::TrackUse() {
    this->value++;
}

int AppConfig::GetValue() {
    this->TrackUse();
    return this->value;
}

AppConfig* AppConfig::appConfig_ = nullptr;;
