// tests/integrations.test.js
const { expect } = require('chai');
const JupyterIntegrationContract = artifacts.require('JupyterIntegrationContract');

contract('JupyterIntegrationContract', (accounts) => {
    let jupyterIntegration;

    before(async () => {
        jupyterIntegration = await JupyterIntegrationContract.new();
    });

    it('should enable Jupyter integration', async () => {
        await jupyterIntegration.integrateWithJupyter(accounts[0]);
        const isIntegrated = await jupyterIntegration.jupyterIntegration(accounts[0]);
        expect(isIntegrated).to.be.true;
    });
});
