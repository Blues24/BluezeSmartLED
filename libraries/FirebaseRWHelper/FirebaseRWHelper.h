#ifndef FirebaseRWHelper_h
#define FirebaseRWHelper_h

#include <FirebaseESP8266.h>

class FirebaseRWHelper{
    public:
        FirebaseRWHelper();
        bool writeBoolean(FirebaseData &firebaseData,const String &path, bool value);
        bool readBoolean(FirebaseData &firebaseData,const String &path, bool &value);

    private:
        FirebaseData firebaseData;

};

#endif