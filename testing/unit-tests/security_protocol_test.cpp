#include <gtest/gtest.h>
#include "security_protocols.h" // Include the security protocol system header

class SecurityProtocolTest : public ::testing::Test {
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

TEST_F(SecurityProtocolTest, AddSecurityProtocol) {
    // Test adding a new security protocol
    SecurityProtocol securityProtocol3 = {"AES-128", "AES", "my_aes_key_2", "my_aes_iv_2", ""};
    securityManager.addSecurityProtocol(securityProtocol3);
    EXPECT_EQ(securityManager.securityProtocols.size(), 3);
}

TEST_F(SecurityProtocolTest, RemoveSecurityProtocol) {
    // Test removing a security protocol
    securityManager.removeSecurityProtocol("AES-256");
    EXPECT_EQ(securityManager.securityProtocols.size(), 1);
}

TEST_F(SecurityProtocolTest, EncryptData_AES) {
    // Test encrypting data using AES
    std::string data = "Hello, World!";
    std::string encryptedData = securityManager.encryptData("AES-256", data);
    EXPECT_NE(encryptedData, data);
}

TEST_F(SecurityProtocolTest, DecryptData_AES) {
    // Test decrypting data using AES
    std::string data = "Hello, World!";
    std::string encryptedData = securityManager.encryptData("AES-256", data);
    std::string decryptedData = securityManager.decryptData("AES-256", encryptedData);
    EXPECT_EQ(decryptedData, data);
}

TEST_F(SecurityProtocolTest, EncryptData_RSA) {
    // Test encrypting data using RSA
    std::string data = "Hello, World!";
    std::string encryptedData = securityManager.encryptData("RSA-2048", data);
    EXPECT_NE(encryptedData, data);
}

TEST_F(SecurityProtocolTest, DecryptData_RSA) {
    // Test decrypting data using RSA
    std::string data = "Hello, World!";
    std::string encryptedData = securityManager.encryptData("RSA-2048", data);
    std::string decryptedData = securityManager.decryptData("RSA-2048", encryptedData);
    EXPECT_EQ(decryptedData, data);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
