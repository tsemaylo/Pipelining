/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file PipelineException.h
 *
 * Definition of PipelineException class.
 *
 * @since 28.03.2018
 * @author tsemaylo
 */

#ifndef PIPELINEEXCEPTION_H
#define PIPELINEEXCEPTION_H

#include <exception>

/**
 * Exception type for pipeline errors.
 */
class PipelineException : public std::exception {
public:
    PipelineException(const char* msg);

    const char* what() const noexcept override;

private:
    const char *msg;
};

#endif /* PIPELINEEXCEPTION_H */

