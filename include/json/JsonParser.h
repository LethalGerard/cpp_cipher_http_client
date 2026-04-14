#pragma once
#include <string>
#include <optional>

// Simple JSON parser for the cipher server response format:
//   { "key": "<value>", "cipherText": "<value>" }
//
// This is NOT a general-purpose JSON parser — it only handles flat
// string fields, which is all the cipher server ever returns.
class JsonParser {
public:
    explicit JsonParser(const std::string& json);

    // Returns the value of a top-level string field, or std::nullopt if
    // the field is not found. Example: get("key"), get("cipherText").
    std::optional<std::string> get(const std::string& field) const;

private:
    std::string json_;
};
