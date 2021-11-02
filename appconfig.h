#ifndef APPCONFIG_H
#define APPCONFIG_H


class AppConfig
{
public:

    static AppConfig* GetInstance();
    int GetValue();

    AppConfig(AppConfig &other) = delete;
    void operator=(const AppConfig &) = delete;

private:

    AppConfig();

    static AppConfig* appConfig_;
    int value;

    void TrackUse();

};



#endif // APPCONFIG_H
