// tests/mobile.test.js
const { expect } = require('chai');
const MobileOptimizationContract = artifacts.require('MobileOptimizationContract');

contract('MobileOptimizationContract', (accounts) => {
    let mobileOptimization;

    before(async () => {
        mobileOptimization = await MobileOptimizationContract.new();
    });

    it('should enable mobile optimization', async () => {
        await mobileOptimization.enableMobileOptimization(accounts[0]);
        const isOptimized = await mobileOptimization.mobileOptimization(accounts[0]);
        expect(isOptimized).to.be.true;
    });
});
