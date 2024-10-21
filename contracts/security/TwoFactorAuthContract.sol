// contracts/security/TwoFactorAuthContract.sol
pragma solidity ^0.8.0;

contract TwoFactorAuthContract {
    mapping (address => bool) public twoFactorAuth;

    function enableTwoFactorAuth(address user) public {
        twoFactorAuth[user] = true;
    }

    function disableTwoFactorAuth(address user) public {
        twoFactorAuth[user] = false;
    }
}
