// tests/dashboard.test.js
const { expect } = require('chai');
const CustomizableDashboard = artifacts.require('CustomizableDashboard');

contract('CustomizableDashboard', (accounts) => {
    let dashboard;

    before(async () => {
        dashboard = await CustomizableDashboard.new();
    });

    it('should create a dashboard', async () => {
        await dashboard.createDashboard(accounts[0]);
        const dashboardId = await dashboard.dashboards(accounts[0]);
        expect(dashboardId.toString()).to.equal('1');
    });
});
