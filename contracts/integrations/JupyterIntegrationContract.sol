// contracts/integrations/JupyterIntegrationContract.sol
pragma solidity ^0.8.0;

contract JupyterIntegrationContract {
    mapping (address => bool) public jupyterIntegration;

    function integrateWithJupyter(address user) public {
        jupyterIntegration[user] = true;
    }

    function disableJupyterIntegration(address user) public {
        jupyterIntegration[user] = false;
    }
}
