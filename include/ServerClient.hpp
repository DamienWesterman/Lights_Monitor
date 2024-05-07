/***************************************************************************************************
* This file is part of a solution for Josh.ai's coding challenge.
*
* Applicant     Damien Westerman
* Position:     C++ Developer
* File:         LightsManager.hpp
* Description:  Class declaration to track the Lights statuses
*
***************************************************************************************************/

#ifndef SERVER_CLIENT_HPP
#define SERVER_CLIENT_HPP

#include "Light.hpp"

class ServerClient {
    private:
        std::string serverUrl;

    public:
        /**
         * \brief   Constructor
         * \param   serverUrl url and port of server
        */
        ServerClient(std::string serverUrl) : serverUrl(serverUrl) { }

        /**
         * \brief   Retrieve one light's information from the server
         * \param   id string id
         * \return  true/false based on if information was saved successfully
        */
        nlohmann::json getOneLight(const std::string& id);

        /**
         * \brief   Retrieve the IDs of all lights
         * \param   void
         * \return  vector of string IDs
        */
        std::vector<std::string> getAllLights(void);

        void setServerUrl(const std::string serverUrl) { this->serverUrl = serverUrl; }
        std::string getServerUrl(void) { return this->serverUrl; }
};


#endif //SERVER_CLIENT_HPP
