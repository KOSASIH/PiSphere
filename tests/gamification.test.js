// tests/gamification.test.js
const { expect } = require('chai');
const LeaderboardContract = artifacts.require('LeaderboardContract');

contract('LeaderboardContract', (accounts) => {
    let leaderboard;

    before(async () => {
        leaderboard = await LeaderboardContract.new();
    });

    it('should update the leaderboard', async () => {
        await leaderboard.updateLeaderboard(accounts[0], 50);
        const points = await leaderboard.leaderboard(accounts[0]);
        expect(points.toString()).to.equal('50');
    });
});
