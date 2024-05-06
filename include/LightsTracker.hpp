/***************************************************************************************************
* This file is part of a solution for Josh.ai's coding challenge.
*
* Applicant     Damien Westerman
* Position:     C++ Developer
* File:         LightsTracker.hpp
* Description:  Class declaration to track the Lights statuses
*
***************************************************************************************************/

#ifndef LIGHTS_TRACKER_HPP
#define LIGHTS_TRACKER_HPP

#include <unordered_map>

#include "Light.hpp"

// TODO: Doc comments
class LightsTracker {
    private:
        std::unordered_map<std::string, Light> lightsMap;
        bool getLightInfo(const std::string& id);

    public:
        void setInitialList(const std::string& jsonList);
        void updateList(const std::string& jsonList);
};


#endif //LIGHTS_TRACKER_HPP
