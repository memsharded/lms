#ifndef LMS_EXTRA_STRING_H
#define LMS_EXTRA_STRING_H

#include <string>

namespace lms {
namespace extra {

/**
 * Remove surrounding whitespace from a std::string.
 * @param s The string to be modified.
 * @param t The set of characters to delete from each end
 * of the string.
 * @return trimmed string
 */
std::string trim(const std::string& str, const std::string &delims = " \t\n\r\f\v");

} // namespace extra
} // namespace lms

#endif /* LMS_EXTRA_STRING_H */