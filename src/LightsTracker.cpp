/***************************************************************************************************
* This file is part of a solution for Josh.ai's coding challenge.
*
* Applicant     Damien Westerman
* Position:     C++ Developer
* File:         LightsTracker.cpp
* Description:  Class definitions to track the Lights statuses
*
***************************************************************************************************/

#include "LightsTracker.hpp"

bool LightsTracker::getLightInfo(const std::string& id) {
    return false;
}

void LightsTracker::setInitialList(const std::string& jsonList) {

}

void updateList(const std::string& jsonList) {
    
}
//             nlohmann::json jsonLightsList = nlohmann::json::parse(res->body);
//             if (jsonLightsList.is_array()) {
//                 // Successfully got a list of all lights, request info of each one and save
//                 for (auto jsonLight : jsonLightsList) {

// // Light light(jsonLight);
// // logging::logDebug("Saving light info for <" + light.getId() + ">:\n" + light.getJsonString());
//                 }
//             } else {
//                 logging::logError("Unexpected return, array expected but got: " + res->body);
//             }