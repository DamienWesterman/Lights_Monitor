/***************************************************************************************************
* This file is part of a solution for Josh.ai's coding challenge.
*
* Applicant     Damien Westerman
* Position:     C++ Developer
* File:         LightsManager.cpp
* Description:  Class definitions to track the Lights statuses
*
***************************************************************************************************/

#include "LightsManager.hpp"

#include "httplib.h"

#include "logging.hpp"
#include "defines.hpp"

bool LightsManager::getLightInfo(const std::string& id) {
    bool ret = false;
    std::string getUrl = LIGHTS_ENDPOINT;

    getUrl.append("/");
    getUrl.append(id);

    httplib::Client client(this->serverUrl);
    if (auto res = client.Get(getUrl)) {
        if (httplib::StatusCode::OK_200 == res->status) {
            logging::logDebug("Light request returned:\n" + res->body);
            nlohmann::json lightJson = nlohmann::json::parse(res->body);
            Light light(lightJson);
            if (INVALID_ID != light.getId()) {
                // Save to map
                this->lightsMap.insert(std::make_pair(id, light));
                logging::logDebug("Saved light info for <" + light.getId() + ">");
                ret = true;
            } else {
                logging::logError("Issue saving returned light");
            }
        } // TODO: Other possible return types?
    } else {
        auto err = res.error();
        logging::logError(httplib::to_string(err));
        logging::logInfo("Retrying get request...");
    }

    return ret;
}

void LightsManager::setInitialList(const std::string& jsonList) {
    nlohmann::json jsonLightsList = nlohmann::json::parse(jsonList);
    if (jsonLightsList.is_array()) {
        // Successfully got a list of all lights, request info of each one and save
        for (auto jsonLight : jsonLightsList) {
            if (jsonLight.contains(JSON_KEY_ID) && jsonLight[JSON_KEY_ID].is_string()) {
                getLightInfo(jsonLight[JSON_KEY_ID]);
                // TODO: print the light stuff
            } else {
                logging::logError("Key not present or is invalid during initialization");
            }
        }
    } else {
        logging::logError("Unexpected return, array expected but got: " + jsonList);
    }

}

void LightsManager::updateList(const std::string& jsonList) {
    for (auto light : this->lightsMap) {
        light.second.applyPrintChanges(light.second);
    }
}
