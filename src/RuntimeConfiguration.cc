
#include <tplib/RuntimeConfiguration.hh>

#include <ios>
#include <stdexcept>

namespace tplib {
    RuntimeConfiguration::RuntimeConfiguration()
    {
    }

    RuntimeConfiguration::RuntimeConfiguration(const char* path)
    {
        read(path);
    }

    bool RuntimeConfiguration::read(const char* path)
    {
        std::ifstream f(path);
        if (!f.is_open()) {
            return true;
        }

        std::string s;
        while (f.good()) {
            std::getline(f, s);
            parse_line(s);
        }
        return false;
    }

    bool RuntimeConfiguration::write(const char* path)
    {
        std::ofstream f(path, std::ios::out|std::ios::trunc);
        if (!f.is_open()) {
            return false;
        }

        for (map_t::const_iterator it=m_map.begin(); it != m_map.end(); ++it) {
            f << it->first << " = " << it->second << std::endl;
        }
        return true;
    }

    // More or less equal to this in concept:
    //
    //  s.split('=', 2).for_each.strip()
    //
    void RuntimeConfiguration::parse_line(const std::string& s)
    {
        bool found_equals = false;
        std::string::const_iterator name_start = s.end();
        std::string::const_iterator name_end = s.end();
        std::string::const_iterator value_start = s.end();
        // std::string name, value;
        for (std::string::const_iterator it = s.begin(); it != s.end(); ++it) {

            if (std::isspace(*it) && value_start == s.end()) {
                /*
                 * Values don't start with spaces. Skip until we find non-whitespace.
                 */
                continue;
            }

            if (*it == '#' && name_start == s.end()) {
                // s is a comment!
                return;
            }

            if (*it == '=') {
                found_equals = true;
                continue;
            }

            if (found_equals) {
                if (value_start == s.end() && !std::isspace(*it)) {
                    value_start = it;
                }
                continue;
            }

            // fall through and find the 
            name_end = it+1;

            if (name_start == s.end()) {
                name_start = it;
                continue;
            }
        }

        m_map[std::string(name_start, name_end)] = std::string(value_start, s.end());
    }

    const std::string& RuntimeConfiguration::get(const std::string& name)
    {
        return m_map[name];
    }

    void RuntimeConfiguration::put(const std::string& name, const std::string& value)
    {
        m_map[name] = value;
    }
}


