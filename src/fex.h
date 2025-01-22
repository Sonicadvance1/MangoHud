#pragma once
#ifdef HAVE_FEX
#ifndef MANGOHUD_FEX_H
#define MANGOHUD_FEX_H
#include <cstdint>
#include <vector>
#include <string>

namespace fex {
bool is_fex_capable();
bool is_fex_pid_found();
const char* get_fex_app_type();

extern const char* fex_status;
extern std::string fex_version;

extern std::vector<float> fex_load_data;

struct fex_event_counts {
    public:
        void account(uint64_t total, std::chrono::time_point<std::chrono::steady_clock> now) {
            if (max < total || (now - last_chrono) >= std::chrono::seconds(10)) {
                max = total;
                last_chrono = now;
            }
            count = total;
        }

        void account_time(std::chrono::time_point<std::chrono::steady_clock> now) {
            last_chrono = now;
        }
        uint64_t Count() const { return count; }
        uint64_t Max() const { return max; }
    private:
        uint64_t count;
        uint64_t max;
        std::chrono::time_point<std::chrono::steady_clock> last_chrono;
};
extern fex_event_counts sigbus_counts;
extern fex_event_counts smc_counts;

extern std::vector<float> fex_max_thread_loads;
void update_fex_stats();
}

#endif //MANGOHUD_FEX_H
#endif //HAVE_FEX
