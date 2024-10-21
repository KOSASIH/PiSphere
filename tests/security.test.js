// tests/security.test.js
const { expect } = require('chai');
const TwoFactorAuthContract = artifacts.require('TwoFactorAuthContract');

contract('TwoFactorAuthContract', (accounts) => {
    let twoFactorAuth;

    before(async () => {
        twoFactorAuth = await TwoFactorAuthContract.new();
    });

    it('should enable two-factor authentication', async () => {
        await twoFactorAuth.enableTwoFactorAuth(accounts[0]);
        const isEnabled = await twoFactorAuth.twoFactorAuth(accounts[0]);
        expect(isEnabled).to.be.true;
    });
});
