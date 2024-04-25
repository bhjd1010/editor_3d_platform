#pragma once

#include <string>
#include "math/common/define.h"

namespace gmv {
    class ElementId {
    public:
        explicit ElementId(int64_t id = -1) : _id(id) {}

        ~ElementId() {}

        static ElementId InvalidId() { return InvalidID; }

        ElementId(const ElementId &other) : _id(other._id) {}

        ElementId &operator=(const ElementId &other) {
            _id = other._id;
            return *this;
        }

        bool IsValid() const { return _id >= 0; }

        int64_t AsInt64() const { return _id; }

        std::string ToString() const { return std::to_string(_id); }

        bool operator==(const ElementId &elementId) const { return _id == elementId._id; }

        bool operator!=(const ElementId &elementId) const { return _id != elementId._id; }

        bool operator>(const ElementId &elementId) const { return _id > elementId._id; }

        bool operator<(const ElementId &elementId) const { return _id < elementId._id; }

        bool EqualTo(const ElementId &elementId) const { return _id == elementId._id; }

    public:
        static ElementId InvalidID;
    private:
        int64_t _id;
    };

    struct ElementIdHash {
        std::size_t operator()(const ElementId &key) const {
            return std::hash<int64_t>()(key.AsInt64());
        }
    };
}