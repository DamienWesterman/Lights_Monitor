/***************************************************************************************************
* This file is part of a solution for Josh.ai's coding challenge.
*
* Applicant     Damien Westerman
* Position:     C++ Developer
* File:         LightsManager.hpp
* Description:  Class declaration to track the Lights statuses
*
***************************************************************************************************/

#ifndef LIGHTS_TRACKER_HPP
#define LIGHTS_TRACKER_HPP

#include <unordered_map>

#include "Light.hpp"

// TODO: Doc comments
class LightsManager {
    private:
        std::unordered_map<std::string, Light> lightsMap;
        std::string serverUrl;
        bool getLightInfo(const std::string& id);

    public:
        LightsManager(std::string serverUrl) : serverUrl(serverUrl) { }
        void setInitialList(const std::string& jsonList);
        void updateList(const std::string& jsonList);
};


#endif //LIGHTS_TRACKER_HPP
