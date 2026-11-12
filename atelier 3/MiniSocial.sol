// SPDX-License-Identifier: MIT
pragma solidity 0.8.26;

contract MiniSocial {
    struct Post {
        string message;
        address author;
    }
    

    Post[] public posts;
    function publishPost(string memory _message) public {
        posts.push(Post({
            message: _message,
             author: msg.sender
        }));
    }


    function getPost(uint index ) public view returns ( string memory , address) {
        require(index < posts.length, "index out of bounds");
        Post memory p = posts[index];
        return (p.message, p.author);
    }

    function getTotalPosts() public view returns (uint) {
        return posts.length;
    }
}
    