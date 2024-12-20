#include <Arduino.h>
#include "FirebaseHelper.h"
#include <Firebase_ESP_Client.h>

FirebaseHelper::FirebaseHelper() {}

bool FirebaseHelper::writeBoolean(FirebaseData &firebaseData, const String &path, bool value){
    if(Firebase.RTDB.setBool(&firebaseData, path.c_str(), value)){
        return true;
    }else {
        Serial.print("Failed to write to ");
        Serial.print(path);
        Serial.print(": ");
        Serial.println(firebaseData.errorReason().c_str());
        return false; // Failure
    }
}

bool FirebaseHelper::readBoolean(FirebaseData &firebaseData, const String &path, bool &value){
    if(Firebase.RTDB.getBool(&firebaseData, path.c_str())){
        value = firebaseData.boolData();
        return true;
    }else{
        Serial.print("Failed to read from ");
        Serial.print(path);
        Serial.print(": ");
        Serial.println(firebaseData.errorReason().c_str());
        return false; // Failure
    }
}