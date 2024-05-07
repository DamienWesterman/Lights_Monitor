/***************************************************************************************************
* This file is part of a solution for Josh.ai's coding challenge.
*
* Applicant     Damien Westerman
* Position:     C++ Developer
* File:         main.cpp
* Description:  Logging utility funcitons
*
***************************************************************************************************/

#include <unordered_map>
#include <csignal>
#include <atomic>

#include "cmdparser.hpp"

#include "logging.hpp"
#include "Light.hpp"
#include "ServerClient.hpp"
#include "defines.hpp"

static std::atomic<bool> userExit(false);

static void signalHandler(int signal) {
    std::cout << "INTERRUPT DETECTED" << std::endl;
    userExit = true;
}

int main(int argc, char **argv) {
    cli::Parser parser(argc, argv);
    std::string serverUrl;
    int interval = 1;
    int num_retries = 0;
    std::unordered_map<std::string, Light> lightsMap;

    logging::logInfo("Damien Westerman's solution for Josh.ai C++ coding challenge");

    signal(SIGINT, signalHandler);

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
        logging::logError("Must provide valid URL, using \"" + std::string(LOCALHOST_URL) + "\"");
    }
    if (0 >= interval) {
        interval = 1;
        logging::logError("Interval must be greater than 0, setting to 1");
    }
    logging::logDebug("Arguments: serverUrl <\"" + serverUrl + "\"> interval <" +
            std::to_string(interval) + ">");

    logging::logInfo("Starting lights_monitor...");
    logging::logInfo("Press CTRL+C to exit");

    // Initialize map with values from server
    ServerClient serverClient(serverUrl);

    do {
        std::vector<std::string> idList;

        if (serverClient.getAllLights(&idList)) {
            for (std::string id : idList) {
                Light light(serverClient.getOneLight(id));
                if (INVALID_ID != light.getId()) {
                    // Save to map
                    lightsMap.insert(std::make_pair(id, light));
                    logging::logJsonInfo(light.getJson());
                } else {
                    logging::logError("Issue saving returned light");
                }
            }

            // Successfully saved all lights, break out of do/while
            break;
        } else {
            // Already logged in getAllLights(), intentionally left empty. Continue
        }

        logging::logInfo("Retrying get request...");
        num_retries++;

        sleep(1);
    } while(MAX_RETRIES > num_retries);

    if (MAX_RETRIES == num_retries) {
        logging::logError("Max number of retries exceeded. Please check server is up or double check your URL:PORT <"
                          + serverUrl + ">. Continuing...");
    }

    // Check server every 'interval' seconds and prints updates
    while (!userExit) {
        sleep(interval);

        std::vector<std::string> idList;

        if (serverClient.getAllLights(&idList)) {
            std::unordered_map<std::string, Light> tempMap;
            lightsMap.swap(tempMap);

            for (std::string id : idList) {
                Light light(serverClient.getOneLight(id));
                if (INVALID_ID != id) {
                    if (tempMap.find(id) != tempMap.end()) {
                        // Light exists, add to lightsMap and check for updates
                        lightsMap.insert(std::make_pair(id, tempMap.at(id)));
                        tempMap.erase(id);
                        lightsMap.at(id).applyPrintChanges(light);
                    } else {
                        // Light does not exist, add and log it
                        lightsMap.insert(std::make_pair(id, light));
                        logging::logJsonInfo(light.getJson());
                    }
                } else {
                    logging::logError("Issue retrieving light");
                }
            }

            // Any remaining lights have since been deleted
            if (0 < tempMap.size()) {
                for (auto& pair : tempMap) {
                    logging::logInfo(pair.second.getName() + " (" + pair.second.getId()
                                    + ") has been removed");
                }
            }
        } else {
            // Already logged in getAllLights(), intentionally left empty. Continue
        }
    } // while(!userExit)

    logging::logInfo("Exiting lights_monitor...");
    return 0;
}
