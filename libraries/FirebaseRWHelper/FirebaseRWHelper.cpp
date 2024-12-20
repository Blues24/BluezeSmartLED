#include <Arduino.h>
#include <Firebase_ESP_Client.h>
#include "FirebaseRWHelper.h"

FirebaseRWHelper::FirebaseRWHelper(){}

bool FirebaseRWHelper::writeBoolean(FirebaseData &firebaseData, const String &path, bool value){
    if(Firebase.setBool(firebaseData, path, value)){
        return true; // success
    } else{
        Serial.print("Failed to write to ");
        Serial.print(path);
        Serial.print(": ");
        Serial.println(firebaseData.errorReason());
        return false;
    }
}

bool FirebaseRWHelper::readBoolean(FirebaseData &firebaseData, const String &path, bool &value){
    if(firebaseData.getBool(firebaseData, path)){
        if(firebaseData.dataType() == "boolean"){
            value = firebaseData.boolData();
            return true; // you are genius
        } else {
            Serial.print("Data at");
            Serial.print(path);
            Serial.print(":");
            Serial.println("Is not Boolean expression");
            return false; // you are not my type of data types
        }
    } else {
        Serial.print("Failed to read from");
        Serial.print(path);
        Serial.print(":");
        Serial.println(firebaseData.errorReason());
        return false; // you are the problem
    }
}