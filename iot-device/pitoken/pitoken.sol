pragma solidity ^0.8.0;

import "https://github.com/OpenZeppelin/openzeppelin-solidity/contracts/token/ERC20/SafeERC20.sol";
import "https://github.com/OpenZeppelin/openzeppelin-solidity/contracts/math/SafeMath.sol";
import "https://github.com/OpenZeppelin/openzeppelin-solidity/contracts/utils/Address.sol";

contract PiToken {
    // Mapping of addresses to balances
    mapping (address => uint256) public balances;

    // Mapping of addresses to allowances
    mapping (address => mapping (address => uint256)) public allowances;

    // Total supply of PiToken
    uint256 public totalSupply;

    // Name of the token
    string public name;

    // Symbol of the token
    string public symbol;

    // Decimals of the token
    uint8 public decimals;

    // Event emitted when tokens are transferred
    event Transfer(address indexed from, address indexed to, uint256 value);

    // Event emitted when an approval is made
    event Approval(address indexed owner, address indexed spender, uint256 value);

    // Event emitted when tokens are burned
    event Burn(address indexed from, uint256 value);

    // Event emitted when tokens are minted
    event Mint(address indexed to, uint256 value);

    // Constructor function
    constructor() public {
        name = "PiToken";
        symbol = "PTK";
        decimals = 18;
        totalSupply = 100000000 * (10 ** decimals);
        balances[msg.sender] = totalSupply;
    }

    // Function to transfer tokens
    function transfer(address to, uint256 value) public returns (bool) {
        require(balances[msg.sender] >= value, "Insufficient balance");
        balances[msg.sender] -= value;
        balances[to] += value;
        emit Transfer(msg.sender, to, value);
        return true;
    }

    // Function to approve token spending
    function approve(address spender, uint256 value) public returns (bool) {
        allowances[msg.sender][spender] = value;
        emit Approval(msg.sender, spender, value);
        return true;
    }

    // Function to transfer tokens from one address to another
    function transferFrom(address from, address to, uint256 value) public returns (bool) {
        require(allowances[from][msg.sender] >= value, "Insufficient allowance");
        require(balances[from] >= value, "Insufficient balance");
        balances[from] -= value;
        balances[to] += value;
        allowances[from][msg.sender] -= value;
        emit Transfer(from, to, value);
        return true;
    }

    // Function to burn tokens
    function burn(uint256 value) public {
        require(balances[msg.sender] >= value, "Insufficient balance");
        balances[msg.sender] -= value;
        totalSupply -= value;
        emit Burn(msg.sender, value);
    }

    // Function to mint tokens
    function mint(address to, uint256 value) public {
        totalSupply += value;
        balances[to] += value;
        emit Mint(to, value);
    }
}
