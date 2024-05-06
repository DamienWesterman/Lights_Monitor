/***************************************************************************************************
* This file is part of a solution for Josh.ai's coding challenge.
*
* Applicant     Damien Westerman
* Position:     C++ Developer
* File:         main.cpp
* Description:  Logging utility funcitons
*
***************************************************************************************************/

#include "cmdparser.hpp"
#include "httplib.h"

#include "logging.hpp"
#include "Light.hpp"
#include "LightsTracker.hpp"
#include "defines.hpp"

// TODO: FIXME:
    // Finish setting up light.cpp
    // test connection to the server
    // set up and test signal handler
    // License stuff in each header file
    // If http request is not found or whatever, output message to user saying check url
    // REEAALLY go back through trying to find possible error conditions

int main(int argc, char **argv) {
    cli::Parser parser(argc, argv);
    std::string serverUrl;
    int interval;
    LightsTracker tracker;

    // Get command line arguments
    parser.set_optional<std::string>("s", "server-url", LOCALHOST_URL,
            "URL of the server, including port");
    parser.set_optional<int>("i", "interval", 1,
            "Interval (in seconds) to query the server");
    parser.run_and_exit_if_error();
    serverUrl = parser.get<std::string>("s");
    interval = parser.get<int>("i");
    if (serverUrl.empty()) {
        serverUrl = LOCALHOST_URL;
        logging::logError("Must provide valid URL, using \"localhost:8080\"");
    }
    if (0 >= interval) {
        interval = 1;
        logging::logError("Interval must be greater than 0, setting to 1");
    }
    logging::logDebug("Arguments: serverUrl <\"" + serverUrl + "\"> interval <" +
            std::to_string(interval) + ">");

    logging::logInfo("Starting lights_monitor...");

    // Initialize map with values from server
    httplib::Client client(serverUrl);
    // TODO: Implement a retry mechanism here with a timeout, maybe do while
    if (auto res = client.Get(LIGHTS_ENDPOINT)) {
        if (httplib::StatusCode::OK_200 == res->status) {
            logging::logDebug("All lights request returned:\n" + res->body);
        } // Other possible return types?
    } else {
        auto err = res.error();
        logging::logError(httplib::to_string(err));
        logging::logInfo("Retrying get request...");
    }

    logging::logInfo("Exiting lights_monitor...");
    return 0;
}
