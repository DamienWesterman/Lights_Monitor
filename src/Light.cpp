/***************************************************************************************************
* This file is part of a solution for Josh.ai's coding challenge.
*
* Applicant     Damien Westerman
* Position:     C++ Developer
* File:         Light.cpp
* Description:  Class definition for all light device info
*
***************************************************************************************************/

#include "Light.hpp"

#include "logging.hpp"
#include "defines.hpp"

Light::Light(const std::string& id, const std::string& name, const std::string& room,
             const uint8_t brightness, const bool on) :
    id(id), name(name), room(room), brightness(brightness), on(on) { }

Light::Light(const std::string& id) : id(id) {
    this->name = "";
    this->room = "";
    this->brightness = 0;
    this->on = false;
}

Light::Light(const nlohmann::json& json) {
    int brightnessTemp = 0;
    (void)brightnessTemp;

    if (json.empty()) {
        //Set to defaults if empty
        logging::logError("Json passed to constructor is empty");
        Light(std::string(INVALID_ID));
        return;
    }

    if (json.contains(JSON_KEY_ID) && json[JSON_KEY_ID].is_string()) {
        this->id = json[JSON_KEY_ID];
    } else {
        logging::logError("Key not present or is invalid during initialization");
        this->id = INVALID_ID;
    }

    if (json.contains(JSON_KEY_NAME) && json[JSON_KEY_NAME].is_string()) {
        this->name = json[JSON_KEY_NAME];
    } else {
        logging::logError("Name not present or is invalid during initialization of " + id);
        this->name = "";
    }

    if (json.contains(JSON_KEY_ROOM) && json[JSON_KEY_ROOM].is_string()) {
        this->room = json[JSON_KEY_ROOM];
    } else {
        logging::logError("Room not present or is invalid during initialization of " + id);
        this->room = "";
    }


    if (json.contains(JSON_KEY_BRIGHTNESS) && json[JSON_KEY_BRIGHTNESS].is_number()) {
        brightnessTemp = json[JSON_KEY_BRIGHTNESS];
        if (0 <= brightnessTemp && 255 >= brightnessTemp) {
            this->brightness = brightnessTemp;
        } else {
            logging::logError("Brightness <" + std::to_string(brightnessTemp) + "> is invalid, setting to 0 for " + id);
            this->brightness = 0;
        }
    } else {
        logging::logError("Brightness not present or is invalid during initialization of " + id);
        this->brightness = 0;
    }

    if (json.contains(JSON_KEY_ON) && json[JSON_KEY_ON].is_boolean()) {
        this->on = json[JSON_KEY_ON];
    } else {
        logging::logError("On not present or is invalid during initialization of " + id);
        this->on = false;
    }
}

bool Light::applyPrintChanges(Light& newLight) {
    bool ret = false;

    if (newLight.getId() != this->id) {
        return ret;
    }

    if (newLight.getName() != this->name) {
        this->name = newLight.getName();
        nlohmann::json json = {
            {JSON_KEY_ID, this->id},
            {JSON_KEY_NAME, this->name}
        };
        logging::logJsonInfo(json);
        ret = true;
    }

    if (newLight.getRoom() != this->room) {
        this->room = newLight.getRoom();
        nlohmann::json json = {
            {JSON_KEY_ID, this->id},
            {JSON_KEY_ROOM, this->room}
        };
        logging::logJsonInfo(json);
        ret = true;
    }

    if (newLight.getBrightness() != this->brightness) {
        this->brightness = newLight.getBrightness();
        nlohmann::json json = {
            {JSON_KEY_ID, this->id},
            {JSON_KEY_BRIGHTNESS, this->brightness}
        };
        logging::logJsonInfo(json);
        ret = true;
    }

    if (newLight.getOn() != this->on) {
        this->on = newLight.getOn();
        nlohmann::json json = {
            {JSON_KEY_ID, this->id},
            {JSON_KEY_ON, this->on}
        };
        logging::logJsonInfo(json);
        ret = true;
    }

    return ret;
}

nlohmann::json Light::getJson(void) {
    nlohmann::json json = {
        {JSON_KEY_ID, this->id},
        {JSON_KEY_NAME, this->name},
        {JSON_KEY_ROOM, this->room},
        {JSON_KEY_BRIGHTNESS, this->brightness},
        {JSON_KEY_ON, this->on}
    };

    return json;
}

std::string Light::getJsonString(void) {
    return getJson().dump();
}
