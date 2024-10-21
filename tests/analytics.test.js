// tests/analytics.test.js
const { expect } = require('chai');
const DataAnalytics = artifacts.require('DataAnalytics');

contract('DataAnalytics', (accounts) => {
    let dataAnalytics;

    before(async () => {
        dataAnalytics = await DataAnalytics.new();
    });

    it('should add a data point', async () => {
        await dataAnalytics.addDataPoint(accounts[0], 100);
        const dataPoint = await dataAnalytics.dataPoints(accounts[0]);
        expect(dataPoint.toString()).to.equal('100');
    });
});
