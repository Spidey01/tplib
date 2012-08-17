#ifndef TPLIB_RUNTIMECONFIGURATION_HH
#define TPLIB_RUNTIMECONFIGURATION_HH

#include <tplib/common.hh>

#include <fstream>
#include <map>
#include <string>

namespace tplib {

    /** Class for manipulating a simple RC file.
     *
     * The file format is simple:
     *
     * <pre>
     *      # comment
     *      name = value
     *      multi word name = some value
     *      dotted.name = some value
     *</pre>
     *
     * <ol>
     *  <li>Leading and trailing spaces are ignored.</li>
     *  <li>Comments can not be inline!</li>
     *  <li>The file will be rewritten from scratch on every write().</li>
     * </ol>
     */
    class tplib_export RuntimeConfiguration {
      public:

        /** Creates a blank RuntimeConfiguration */
        RuntimeConfiguration();

        /** Loads a configuration from a file.
         *
         * @param path the file path to read().
         */
        RuntimeConfiguration(const char* path);

        /** Populate configuration from a file.
         *
         * @param path the file to read.
         */
        bool read(const char* path);

        /** Destructively write configuration to a file.
         *
         * The files contents will be erased.
         *
         * @param path where to save file.
         */
        bool write(const char* path);


        const std::string& get(const std::string& name);
        void put(const std::string& name, const std::string& value);

      private:
        void parse_line(const std::string& s);
        typedef std::map<std::string, std::string> map_t;
        std::map<std::string, std::string> m_map;
    };
}

#endif

