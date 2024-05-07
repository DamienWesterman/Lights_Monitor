/***************************************************************************************************
* This file is part of a solution for Josh.ai's coding challenge.
*
* Applicant     Damien Westerman
* Position:     C++ Developer
* File:         logging.hpp
* Description:  Logging utility funcitons
*
***************************************************************************************************/

#ifndef LOGGING_HPP
#define LOGGING_HPP

#include <string>
#include <iostream>
#include <iomanip>
#include <ctime>

#include "json.hpp"

namespace logging {
    /**
     * \brief   Logs an informational message to the console
     * \param   message String message to print
     * \return  void
    */
    inline void logInfo(const std::string& message) {
        std::time_t now = std::time(nullptr);
        std::tm* time = std::localtime(&now);
        std::cout << "[INFO]  " << std::setfill('0') << std::setw(2) << time->tm_mon + 1
                  << "/" << std::setw(2) << time->tm_mday << "/" << time->tm_year + 1900
                  << " " << std::setw(2) << time->tm_hour << ":" << std::setw(2)
                  << time->tm_min << ":" << std::setw(2) << time->tm_sec << " - "
                  << message << std::endl;
    }

    /**
     * \brief   Logs an informational message to the console
     * \param   json Json object to print
     * \return  void
    */
    inline void logJsonInfo(const nlohmann::json& json) {
        std::time_t now = std::time(nullptr);
        std::tm* time = std::localtime(&now);
        std::cout << "[INFO]  " << std::setfill('0') << std::setw(2) << time->tm_mon + 1
                  << "/" << std::setw(2) << time->tm_mday << "/" << time->tm_year + 1900
                  << " " << std::setw(2) << time->tm_hour << ":" << std::setw(2)
                  << time->tm_min << ":" << std::setw(2) << time->tm_sec << " - \n"
                  << std::setw(4) << std::setfill(' ') << json << std::endl;
    }

    /**
     * \brief   Logs a debug message to the console
     * \param   message String message to print
     * \return  void
    */
    inline void logDebug(const std::string& message) {
#ifdef DEBUG
        std::time_t now = std::time(nullptr);
        std::tm* time = std::localtime(&now);
        std::cout << "[DEBUG] " << std::setfill('0') << std::setw(2) << time->tm_mon + 1
                  << "/" << std::setw(2) << time->tm_mday << "/" << time->tm_year + 1900
                  << " " << std::setw(2) << time->tm_hour << ":" << std::setw(2)
                  << time->tm_min << ":" << std::setw(2) << time->tm_sec << " - "
                  << message << std::endl;
#endif // DEBUG
    }

    /**
     * \brief   Logs an error message to the console
     * \param   message String message to print
     * \return  void
    */
    inline void logError(const std::string& message) {
        std::time_t now = std::time(nullptr);
        std::tm* time = std::localtime(&now);
        std::cout << "\033[1;31m[ERROR] " << std::setfill('0') << std::setw(2) << time->tm_mon + 1
                  << "/" << std::setw(2) << time->tm_mday << "/" << time->tm_year + 1900
                  << " " << std::setw(2) << time->tm_hour << ":" << std::setw(2)
                  << time->tm_min << ":" << std::setw(2) << time->tm_sec << " - "
                  << message << "\033[0m" << std::endl;
    }
}

#endif // LOGGING_HPP
