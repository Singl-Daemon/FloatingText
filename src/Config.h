#pragma once

#include <ll/api/Config.h>

namespace FloatingText {

struct Config {
    int         version  = 1;
    std::string language = "en_US";
};

inline std::string defaultStaticFile = R"([
    {
        "Text": "Example Static Text 1",
        "Position": {
            "x": -5,
            "y": 90,
            "z": -5,
            "dim": 0
        }
    },
    {
        "Text": "Example\nStatic\nText 2",
        "Position": {
            "x": -5,
            "y": 95,
            "z": -5,
            "dim": 0
        }
    }
])";

inline std::string defaultDynamicFile = R"([
    {
        "Text": "Player Name: %player_realname%\nServer Mspt: %server_mspt%",
        "UpdateRate": 1,
        "Position": {
            "x": 5,
            "y": 90,
            "z": 5,
            "dim": 0
        }
    },
    {
        "Text": "Player Ping: %player_ping%ms\nServer Tps: %server_tps%",
        "UpdateRate": 2,
        "Position": {
            "x": 5,
            "y": 95,
            "z": 5,
            "dim": 0
        }
    }
])";
} // namespace FloatingText