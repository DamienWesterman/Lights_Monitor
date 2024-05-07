/***************************************************************************************************
* This file is part of a solution for Josh.ai's coding challenge.
*
* Applicant     Damien Westerman
* Position:     C++ Developer
* File:         LightsManager.cpp
* Description:  Class definitions to track the Lights statuses
*
***************************************************************************************************/

#include "ServerClient.hpp"

#include "httplib.h"

#include "logging.hpp"
#include "defines.hpp"

nlohmann::json ServerClient::getOneLight(const std::string& id) {
    nlohmann::json retJson;
    std::string getUrl = LIGHTS_ENDPOINT;

    getUrl.append("/");
    getUrl.append(id);

    httplib::Client client(this->serverUrl);
    if (auto res = client.Get(getUrl)) {
        if (httplib::StatusCode::OK_200 == res->status) {
            logging::logDebug("Light request returned:\n" + res->body);
            retJson = nlohmann::json::parse(res->body);
        } else if (httplib::StatusCode::NotFound_404 == res->status) {
            logging::logError("Server could not find id <" + id + ">");
        } else {
            logging::logError("Received unexpected status <" + std::to_string(res->status) + ">");
        }
    } else {
        auto err = res.error();
        logging::logError(httplib::to_string(err));
    }

    return retJson;
}

std::vector<std::string> ServerClient::getAllLights(void) {
    std::vector<std::string> retList;
    httplib::Client client(this->serverUrl);
    nlohmann::json jsonLightsList;

    if (auto res = client.Get(LIGHTS_ENDPOINT)) {
        if (httplib::StatusCode::OK_200 == res->status) {
            logging::logDebug("All lights request returned:\n" + res->body);
            jsonLightsList = nlohmann::json::parse(res->body);

            if (jsonLightsList.is_array()) {
                // Successfully got a list of all lights, save their IDs
                for (auto jsonLight : jsonLightsList) {
                    if (jsonLight.contains(JSON_KEY_ID) && jsonLight[JSON_KEY_ID].is_string()) {
                        std::string id(jsonLight[JSON_KEY_ID]);
                        retList.push_back(id);
                        logging::logDebug("Adding ID to list: " + id);
                    } else {
                        logging::logError("Key not present or is invalid during initialization");
                    }
                }
            } else {
                logging::logError("Unexpected return, array expected but got: " + jsonLightsList.dump());
            }
        } else {
            logging::logError("Received unexpected status <" + std::to_string(res->status) + ">");
        }
    } else {
        auto err = res.error();
        logging::logError(httplib::to_string(err));
    }

    return retList;
}
