#include <gtest/gtest.h>
#include "security_protocols.h" // Include the security protocol system header
#include "integration_test_utils.h" // Include utility functions for integration testing

class IntegrationTest : public ::testing::Test {
protected:
    SecurityManager securityManager;

    virtual void SetUp() {
        // Create some security protocols for testing
        SecurityProtocol securityProtocol1 = {"AES-256", "AES", "my_aes_key", "my_aes_iv", ""};
        SecurityProtocol securityProtocol2 = {"RSA-2048", "RSA", "", "", "my_rsa_certificate"};

        // Add the security protocols to the system
        securityManager.addSecurityProtocol(securityProtocol1);
        securityManager.addSecurityProtocol(securityProtocol2);
    }
};

TEST_F(IntegrationTest, EndToEndEncryption_AES) {
    // Test end-to-end encryption using AES
    std::string data = "Hello, World!";
    std::string encryptedData = securityManager.encryptData("AES-256", data);
    std::string decryptedData = securityManager.decryptData("AES-256", encryptedData);
    EXPECT_EQ(decryptedData, data);
}

TEST_F(IntegrationTest, EndToEndEncryption_RSA) {
    // Test end-to-end encryption using RSA
    std::string data = "Hello, World!";
    std::string encryptedData = securityManager.encryptData("RSA-2048", data);
    std::string decryptedData = securityManager.decryptData("RSA-2048", encryptedData);
    EXPECT_EQ(decryptedData, data);
}

TEST_F(IntegrationTest, MultipleEncryption_AES) {
    // Test encrypting data multiple times using AES
    std::string data = "Hello, World!";
    std::string encryptedData1 = securityManager.encryptData("AES-256", data);
    std::string encryptedData2 = securityManager.encryptData("AES-256", encryptedData1);
    std::string decryptedData = securityManager.decryptData("AES-256", encryptedData2);
    EXPECT_EQ(decryptedData, data);
}

TEST_F(IntegrationTest, MultipleEncryption_RSA) {
    // Test encrypting data multiple times using RSA
    std::string data = "Hello, World!";
    std::string encryptedData1 = securityManager.encryptData("RSA-2048", data);
    std::string encryptedData2 = securityManager.encryptData("RSA-2048", encryptedData1);
    std::string decryptedData = securityManager.decryptData("RSA-2048", encryptedData2);
    EXPECT_EQ(decryptedData, data);
}

TEST_F(IntegrationTest, ConcurrentEncryption_AES) {
    // Test concurrent encryption using AES
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; i++) {
        threads.emplace_back([this]() {
            std::string data = "Hello, World!";
            std::string encryptedData = securityManager.encryptData("AES-256", data);
            std::string decryptedData = securityManager.decryptData("AES-256", encryptedData);
            EXPECT_EQ(decryptedData, data);
        });
    }
    for (auto& thread : threads) {
        thread.join();
    }
}

TEST_F(IntegrationTest, ConcurrentEncryption_RSA) {
    // Test concurrent encryption using RSA
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; i++) {
        threads.emplace_back([this]() {
            std::string data = "Hello, World!";
            std::string encryptedData = securityManager.encryptData("RSA-2048", data);
            std::string decryptedData = securityManager.decryptData("RSA-2048", encryptedData);
            EXPECT_EQ(decryptedData, data);
        });
    }
    for (auto& thread : threads) {
        thread.join();
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
