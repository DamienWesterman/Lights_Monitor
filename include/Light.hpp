/***************************************************************************************************
* This file is part of a solution for Josh.ai's coding challenge.
*
* Applicant     Damien Westerman
* Position:     C++ Developer
* File:         Light.hpp
* Description:  Class declaration for all light device info
*
***************************************************************************************************/

#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <string>

#include "json.hpp"

class Light {
    private:
        std::string id;
        std::string name;
        std::string room;
        /** In the range of 0-255 */
        uint8_t brightness;
        /** true=light is on */
        bool on;

    public:
        /**
         * \brief   Fully parameterized constructor
         * \param   id string id
         * \param   name string name
         * \param   room string room
         * \param   brightness int 0-255 range
         * \param   on bool true=light is on
        */
        Light(const std::string& id, const std::string& name, const std::string& room,
              const uint8_t brightness, const bool on);

        /**
         * \brief   "Default" constructor
         * \param   id string id
        */
        Light(const std::string& id);

        /**
         * \brief   Constructor that uses json object to initialize values
         * \param   json nholmann::json object
        */
        Light(const nlohmann::json& json);

        /**
         * \brief   Check this Light for changes. Updates and prints anything that changed
         * \param   newLight Most recent Light object information
         * \return  true/false if anything changed
        */
        bool applyPrintChanges(Light& newLight);

        /**
         * \brief   Return a json string representation of this object
         * \param   void
         * \return  json string of object
        */
        std::string getJsonString(void);

        /**
         * \brief   Return a json representation of this object
         * \param   void
         * \return  json
        */
        nlohmann::json getJson(void);

        std::string getId(void) { return this->id; }
        void setName(const std::string name) { this->name = name; }
        std::string getName(void) { return this->name; }
        void setRoom(const std::string room) { this->room = room; }
        std::string getRoom(void) { return this->room; }

        /**
         * \brief   Set the brightness of this light 0-255
         * \param   brightness int 0-255
         * \return  void
        */
        void setBrightness(const uint8_t brightness) { this->brightness = brightness; };

        uint8_t getBrightness(void) { return this->brightness; }
        void setOn(const bool on) { this->on = on; }
        bool getOn(void) { return this->on; }
};

#endif // LIGHT_HPP
