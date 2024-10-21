// tests/collaboration.test.js
const { expect } = require('chai');
const CommentContract = artifacts.require('CommentContract');

contract('CommentContract', (accounts) => {
    let commentContract;

    before(async () => {
        commentContract = await CommentContract.new();
    });

    it('should add a comment', async () => {
        await commentContract.addComment(accounts[0], 'Hello World');
        const comment = await commentContract.comments(accounts[0]);
        expect(comment).to.equal('Hello World');
    });
});
