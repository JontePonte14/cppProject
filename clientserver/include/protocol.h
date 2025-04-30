/*
* Protocol: definitions of command and error codes
* for the messaging protocol used in the news system project,
* C++ Programming course.
*/

#ifndef PROTOCOL_H
#define PROTOCOL_H
 
#include <array>
#include <string_view>

using code = unsigned char;

enum class Protocol : code {
        UNDEFINED = 0, // not used in protocol

        /* Command codes, client -> server */
        COM_LIST_NG    = 1, // list newsgroups
        COM_CREATE_NG  = 2, // create newsgroup
        COM_DELETE_NG  = 3, // delete newsgroup
        COM_LIST_ART   = 4, // list articles
        COM_CREATE_ART = 5, // create article
        COM_DELETE_ART = 6, // delete article
        COM_GET_ART    = 7, // get article
        COM_END        = 8, // command end

        /* Answer codes, server -> client */
        ANS_LIST_NG    = 20, // answer list newsgroups
        ANS_CREATE_NG  = 21, // answer create newsgroup
        ANS_DELETE_NG  = 22, // answer delete newsgroup
        ANS_LIST_ART   = 23, // answer list articles
        ANS_CREATE_ART = 24, // answer create article
        ANS_DELETE_ART = 25, // answer delete article
        ANS_GET_ART    = 26, // answer get article
        ANS_END        = 27, // answer end
        ANS_ACK        = 28, // acknowledge
        ANS_NAK        = 29, // negative acknowledge

        /* Parameters */
        PAR_STRING = 40, // string
        PAR_NUM    = 41, // number

        /* Error codes */
        ERR_NG_ALREADY_EXISTS  = 50, // newsgroup already exists
        ERR_NG_DOES_NOT_EXIST  = 51, // newsgroup does not exist
        ERR_ART_DOES_NOT_EXIST = 52  // article does not exist
};

constexpr std::array<std::pair<Protocol, code>, 24> protocol_to_code = {{
        {Protocol::UNDEFINED, 0},
        {Protocol::COM_LIST_NG, 1},
        {Protocol::COM_CREATE_NG, 2},
        {Protocol::COM_DELETE_NG, 3},
        {Protocol::COM_LIST_ART, 4},
        {Protocol::COM_CREATE_ART, 5},
        {Protocol::COM_DELETE_ART, 6},
        {Protocol::COM_GET_ART, 7},
        {Protocol::COM_END, 8},
        {Protocol::ANS_LIST_NG, 20},
        {Protocol::ANS_CREATE_NG, 21},
        {Protocol::ANS_DELETE_NG, 22},
        {Protocol::ANS_LIST_ART, 23},
        {Protocol::ANS_CREATE_ART, 24},
        {Protocol::ANS_DELETE_ART, 25},
        {Protocol::ANS_GET_ART, 26},
        {Protocol::ANS_END, 27},
        {Protocol::ANS_ACK, 28},
        {Protocol::ANS_NAK, 29},
        {Protocol::PAR_STRING, 40},
        {Protocol::PAR_NUM, 41},
        {Protocol::ERR_NG_ALREADY_EXISTS, 50},
        {Protocol::ERR_NG_DOES_NOT_EXIST, 51},
        {Protocol::ERR_ART_DOES_NOT_EXIST, 52}
}};

[[nodiscard]] constexpr auto to_code(const Protocol protocol) noexcept -> code {
        for (const auto& entry : protocol_to_code) {
                if(entry.first == protocol) {
                        return entry.second;
                }
        }

        return 0;
}

[[nodiscard]] constexpr auto from_code(const code code) noexcept -> Protocol {
        for (const auto& entry : protocol_to_code) {
                if(entry.second == code) {
                        return entry.first;
                }
        }

        return Protocol::UNDEFINED;
}
    
constexpr std::array<std::pair<Protocol, std::string_view>, 24> protocol_to_string = {{
        {Protocol::UNDEFINED, "UNDEFINED"},
        {Protocol::COM_LIST_NG, "COM_LIST_NG"},
        {Protocol::COM_CREATE_NG, "COM_CREATE_NG"},
        {Protocol::COM_DELETE_NG, "COM_DELETE_NG"},
        {Protocol::COM_LIST_ART, "COM_LIST_ART"},
        {Protocol::COM_CREATE_ART, "COM_CREATE_ART"},
        {Protocol::COM_DELETE_ART, "COM_DELETE_ART"},
        {Protocol::COM_GET_ART, "COM_GET_ART"},
        {Protocol::COM_END, "COM_END"},
        {Protocol::ANS_LIST_NG, "ANS_LIST_NG"},
        {Protocol::ANS_CREATE_NG, "ANS_CREATE_NG"},
        {Protocol::ANS_DELETE_NG, "ANS_DELETE_NG"},
        {Protocol::ANS_LIST_ART, "ANS_LIST_ART"},
        {Protocol::ANS_CREATE_ART, "ANS_CREATE_ART"},
        {Protocol::ANS_DELETE_ART, "ANS_DELETE_ART"},
        {Protocol::ANS_GET_ART, "ANS_GET_ART"},
        {Protocol::ANS_END, "ANS_END"},
        {Protocol::ANS_ACK, "ANS_ACK"},
        {Protocol::ANS_NAK, "ANS_NAK"},
        {Protocol::PAR_STRING, "PAR_STRING"},
        {Protocol::PAR_NUM, "PAR_NUM"},
        {Protocol::ERR_NG_ALREADY_EXISTS, "ERR_NG_ALREADY_EXISTS"},
        {Protocol::ERR_NG_DOES_NOT_EXIST, "ERR_NG_DOES_NOT_EXIST"},
        {Protocol::ERR_ART_DOES_NOT_EXIST, "ERR_ART_DOES_NOT_EXIST"}
}};

[[nodiscard]] constexpr auto to_string(const Protocol protocol) noexcept -> std::string_view {
        for (const auto& entry : protocol_to_string) {
                if(entry.first == protocol) {
                        return entry.second;
                }
        }

        return "UNDEFINED";
}

[[nodiscard]] constexpr auto from_string(const std::string_view string) noexcept -> Protocol {
        for (const auto& entry : protocol_to_string) {
                if(entry.second == string) {
                        return entry.first;
                }
        }

        return Protocol::UNDEFINED;
}

#endif