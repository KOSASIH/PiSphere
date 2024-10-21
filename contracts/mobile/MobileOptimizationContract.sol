// contracts/mobile/MobileOptimizationContract.sol
pragma solidity ^0.8.0;

contract MobileOptimizationContract {
    mapping (address => bool) public mobileOptimization;

    function enableMobileOptimization(address user) public {
        mobileOptimization[user] = true;
    }

    function disableMobileOptimization(address user) public {
        mobileOptimization[user] = false;
    }
}
