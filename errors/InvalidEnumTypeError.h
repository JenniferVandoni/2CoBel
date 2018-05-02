//
// Created by jennifer on 12/04/18.
//

#ifndef PROJECT_INVALIDENUMTYPEERROR_H
#define PROJECT_INVALIDENUMTYPEERROR_H


#include <stdexcept>

/**
 * @class InvalidEnumTypeError
 * Error in the type that is not in the enum.
 */
class InvalidEnumTypeError : public std::runtime_error {
public:
    explicit InvalidEnumTypeError(const char *msg) : runtime_error(msg) {}

};


#endif //PROJECT_INVALIDENUMTYPEERROR_H
