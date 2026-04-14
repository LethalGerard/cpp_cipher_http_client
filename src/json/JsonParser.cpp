#include "json/JsonParser.h"
#include <string>
#include <optional>

JsonParser::JsonParser(const std::string& json) : json_(json) {}

/**
 * Very simple json-parser that only handles key value strings. 
 */
std::optional<std::string> JsonParser::get(const std::string& field) const {
    // Build the search token:  "fieldName"
    std::string token = "\"" + field + "\"";

    size_t keyPos = json_.find(token);
    if (keyPos == std::string::npos) {
        return std::nullopt;
    }

    // Move past the field name token.
    size_t pos = keyPos + token.size();

    // Skip whitespace and the colon separator.
    while (pos < json_.size() && (json_[pos] == ' ' || json_[pos] == '\t' || json_[pos] == ':')) {
        ++pos;
    }

    // The value must start with a quote.
    if (pos >= json_.size() || json_[pos] != '"') {
        return std::nullopt;
    }
    ++pos; // step past the opening quote

    // Read until the closing (unescaped) quote.
    std::string value;
    while (pos < json_.size()) {
        char c = json_[pos];
        if (c == '\\' && pos + 1 < json_.size()) {
            // Pass through the escape sequence as-is for simplicity.
            value += c;
            value += json_[pos + 1];
            pos += 2;
        } else if (c == '"') {
            break; // closing quote
        } else {
            value += c;
            ++pos;
        }
    }

    return value;
}
