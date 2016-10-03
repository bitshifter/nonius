// Nonius - C++ benchmarking tool
//
// Written in 2014- by the nonius contributors <nonius@rmf.io>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>

// Run configuration

#ifndef NONIUS_CONFIGURATION_HPP
#define NONIUS_CONFIGURATION_HPP

#include <nonius/param.h++>
#include <string>
#include <vector>

#include <cassert>

namespace nonius {

    namespace detail {
        template <typename T>
        class optional {
            // Note that this doesn't handle aligned types
            uint8_t storage[sizeof(T)];
            bool initialized;
            T* address() {
                return reinterpret_cast<T*>(storage);
            }
        public:
            optional() : initialized(false) {}
            optional(T&& value) : initialized(false) {
                new (storage) T(std::move(value));
                initialized = true;
            }
            ~optional() {
                if (initialized) {
                    address()->~T();
                    initialized = false;
                }
            }
            T* operator->() {
                assert(initialized);
                return address();
            }
            T& operator*() {
                assert(initialized);
                return *address();
            }
            explicit operator bool() const {
                return initialized;
            }
            bool operator!() const {
                return !initialized;
            }
        };
    } // namespace detail

    struct run_configuration {
        std::string name;
        std::string op;
        param init;
        param step;
        std::size_t count;
    };

    struct param_configuration {
        parameters map;
        detail::optional<run_configuration> run;
    };

    struct configuration {
    public:
        int samples = 100;
        double confidence_interval = 0.95;
        int resamples = 100000;
        std::string title = "benchmarks";
        std::string output_file;
        std::string reporter;
        std::string filter_pattern = ".*";
        bool list_benchmarks = false;
        bool list_params = false;
        bool list_reporters = false;
        bool no_analysis = false;
        bool verbose = false;
        bool summary = false;
        bool help = false;
        param_configuration params;
    };
} // namespace nonius

#endif // NONIUS_CONFIGURATION_HPP
