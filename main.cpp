#include <iostream>
#include "parallel_processing.h"
#include <chrono> // Zamanı ölçmek için

int main() {
    std::string target_hash = "30d45a6a762535700ce9e0b216e31994335db8a5"; // Örnek hedef hash
    std::cout << "Preimage saldırısı başlatılıyor..." << std::endl;
    std::cout << "Hedef hash: " << target_hash << std::endl;
    std::cout << "Kullanılan hash fonksiyonu: RIPEMD-160" << std::endl;

    auto start_time = std::chrono::high_resolution_clock::now();

    // Paralel işlemi başlat
    std::string preimage = parallel_preimage_attack(target_hash);

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count();

    if (!preimage.empty()) {
        std::cout << "Başarılı! Preimage bulundu: " << preimage << std::endl;
    } else {
        std::cout << "Preimage bulunamadı." << std::endl;
    }

    // Toplam işlem sayısını ve hızı yazdır
    uint64_t total_operations = 0xffffffffffffffff - 0x1000000000000000; // Tarama aralığı
    double operations_per_second = static_cast<double>(total_operations) / duration;
    
    std::cout << "Toplam çalışma süresi: " << duration << " saniye." << std::endl;
    std::cout << "Saniyede yapılan işlem sayısı: " << operations_per_second << std::endl;

    return 0;
}
