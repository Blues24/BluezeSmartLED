#ifndef FirebaseHelper_h
#define FirebaseHelper_h
#include <Firebase_ESP_Client.h>
#include <Arduino.h>

class FirebaseHelper{
    public:
        FirebaseHelper();
        bool writeBoolean(FirebaseData &firebaseData, const String &path, bool value);
        bool readBoolean(FirebaseData &firebaseData, const String &path, bool &value);
};

#endif