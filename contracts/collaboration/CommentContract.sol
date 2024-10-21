// contracts/collaboration/CommentContract.sol
pragma solidity ^0.8.0;

contract CommentContract {
    mapping (address => string) public comments;

    function addComment(address user, string memory comment) public {
        comments[user] = comment;
    }

    function getComments() public view returns (string[] memory) {
        // Logic to return comments
    }
}
