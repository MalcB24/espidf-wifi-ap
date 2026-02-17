#ifndef ACCESS_POINT_H
#define ACCESS_POINT_H

class AccessPoint {

    protected:
    char* ssid;
    char* password;
    int maxConnections;
    bool hidden;

    static constexpr const char* TAG = "ACCESS_POINT";

    public:
    virtual ~AccessPoint() = default;

    AccessPoint(char* ssid = "ESP-NET", 
                        char* password = "12345678",
                        int maxConnections = 4,
                        bool hidden = false);

    virtual void setSSID(const char* ssid);
    virtual void setPassword(const char* password);
    virtual void setMaxConnections(int maxConnections);
    virtual void setHidden(bool hidden);
    virtual void start();
    virtual void stop();

};

#endif