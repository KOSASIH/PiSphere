#include <benchmark/benchmark.h>
#include "security_protocols.h" // Include the security protocol system header
#include "benchmark_utils.h" // Include utility functions for benchmarking

void BM_AES_Encryption(benchmark::State& state) {
    SecurityManager securityManager;
    SecurityProtocol securityProtocol = {"AES-256", "AES", "my_aes_key", "my_aes_iv", ""};
    securityManager.addSecurityProtocol(securityProtocol);

    std::string data = "Hello, World!";
    for (auto _ : state) {
        securityManager.encryptData("AES-256", data);
    }
}

void BM_RSA_Encryption(benchmark::State& state) {
    SecurityManager securityManager;
    SecurityProtocol securityProtocol = {"RSA-2048", "RSA", "", "", "my_rsa_certificate"};
    securityManager.addSecurityProtocol(securityProtocol);

    std::string data = "Hello, World!";
    for (auto _ : state) {
        securityManager.encryptData("RSA-2048", data);
    }
}

void BM_AES_Decryption(benchmark::State& state) {
    SecurityManager securityManager;
    SecurityProtocol securityProtocol = {"AES-256", "AES", "my_aes_key", "my_aes_iv", ""};
    securityManager.addSecurityProtocol(securityProtocol);

    std::string data = "Hello, World!";
    std::string encryptedData = securityManager.encryptData("AES-256", data);
    for (auto _ : state) {
        securityManager.decryptData("AES-256", encryptedData);
    }
}

void BM_RSA_Decryption(benchmark::State& state) {
    SecurityManager securityManager;
    SecurityProtocol securityProtocol = {"RSA-2048", "RSA", "", "", "my_rsa_certificate"};
    securityManager.addSecurityProtocol(securityProtocol);

    std::string data = "Hello, World!";
    std::string encryptedData = securityManager.encryptData("RSA-2048", data);
    for (auto _ : state) {
        securityManager.decryptData("RSA-2048", encryptedData);
    }
}

BENCHMARK(BM_AES_Encryption);
BENCHMARK(BM_RSA_Encryption);
BENCHMARK(BM_AES_Decryption);
BENCHMARK(BM_RSA_Decryption);

int main(int argc, char **argv) {
    ::benchmark::Initialize(&argc, argv);
    ::benchmark::RunSpecifiedBenchmarks();
    return 0;
}
