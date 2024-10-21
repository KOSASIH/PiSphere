// contracts/gamification/LeaderboardContract.sol
pragma solidity ^0.8.0;

contract LeaderboardContract {
    mapping (address => uint256) public leaderboard;

    function updateLeaderboard(address user, uint256 points) public {
        leaderboard[user] = points;
    }

    function getLeaderboard() public view returns (uint256[] memory) {
        // Logic to return leaderboard
    }
}
