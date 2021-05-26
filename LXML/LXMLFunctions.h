#pragma once
#include <string>


namespace LXMLP { // => Light-XML-Parser

    using namespace std;

    inline void ReplaceAll(std::string& data, const std::string& toSearch, const std::string& replaceStr) {
        // Just Works from: https://stackoverflow.com/questions/5878775/how-to-find-and-replace-string/5878802
        size_t pos = data.find(toSearch);
        while (pos != std::string::npos) {
            data.replace(pos, toSearch.size(), replaceStr);
            pos = data.find(toSearch, pos + replaceStr.size());
        }
    }


    inline void ReplaceOnce(std::string& data, const std::string& toSearch, const std::string& replaceStr) {
        size_t pos = data.find(toSearch);
        if (pos != std::string::npos) {
            data.replace(pos, toSearch.size(), replaceStr);
        }
    }


    inline string CharToHex(const unsigned char& c) {
        char rawBuffer[4]{};
        char resultBuffer[3]{};
        sprintf_s(rawBuffer, "0%X", (unsigned int)c);
        size_t count = strlen(rawBuffer);
        resultBuffer[0] = rawBuffer[count - 2];
        resultBuffer[1] = rawBuffer[count - 1];
        return string(resultBuffer);
    }


    inline string StringToHexString(const string& text) {
        string result = "";
        for (auto c : text) { result += CharToHex(c); }
        return result;
    }


    inline string HexStringToString(const string& hexText) {
        string strNumber{};
        string result{};
        char c{};
        if ((hexText.length() % 2) != 0) { return ""; }
        for (size_t i = 0; i < hexText.length(); i += 2) {
            strNumber = hexText.substr(i, 2);
            int i_hex = std::stoi(strNumber, nullptr, 16);
            c = (char)i_hex;
            result += c;
        }
        return result;
    }

}