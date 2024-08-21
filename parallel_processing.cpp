#include "parallel_processing.h"
#include "preimage_attack.h"
#include <iostream>
#include <omp.h> // OpenMP ile paralel işlem

std::string parallel_preimage_attack(const std::string& target_hash) {
    std::string found_preimage;
    bool preimage_found = false;

    // Belirtilen aralıkta paralel işlem
    uint64_t start = 0x1000000000000000;
    uint64_t end = 0xffffffffffffffff;
    uint64_t range_per_thread = (end - start) / 8; // 8 thread için aralığı böl

    #pragma omp parallel for
    for (int t = 0; t < 8; ++t) {
        uint64_t thread_start = start + t * range_per_thread;
        uint64_t thread_end = (t == 7) ? end : thread_start + range_per_thread - 1;

        std::string result = find_preimage_in_range(target_hash, thread_start, thread_end);
        if (!result.empty()) {
            #pragma omp critical
            {
                if (!preimage_found) {
                    found_preimage = result;
                    preimage_found = true;
                    std::cout << "Thread " << t << " preimage buldu: " << result << std::endl;
                }
            }
        }
    }

    if (!preimage_found) {
        std::cout << "Preimage bulunamadı." << std::endl;
    }

    return found_preimage;
}
