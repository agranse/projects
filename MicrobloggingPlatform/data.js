const mysql = require(`mysql-await`);
var connPool = mysql.createPool({
    connectionLimit: 5,
    host: "127.0.0.1",
    user: "C4131F23U76",
    database: "C4131F23U76",
    password: "5826",
});

// post table
async function addPost(message, userid) {return await connPool.awaitQuery("INSERT INTO posts (postMessage, userID) VALUES (?, ?);", [message, userid]);}
async function deletePost(id){return await connPool.awaitQuery("DELETE FROM posts WHERE postID = ?;", [id]);}
async function editPost(data) {return await connPool.awaitQuery("UPDATE posts SET postMessage = ? WHERE postID = ?;", [data[0], data[1]]);}
async function getPostLikeCount(id) {return await connPool.awaitQuery("SELECT postLikeCount FROM posts WHERE postID = ?;", [id]);}
async function updatePostLikeCount(data) {return await connPool.awaitQuery("UPDATE posts SET postLikeCount = ? WHERE postID = ?;", [data[0], data[1]]);}
async function getPostsRecentView(limit, offset) {return await connPool.awaitQuery("SELECT posts.postID, posts.postLikeCount, posts.postMessage, users.username FROM posts INNER JOIN users on posts.userID = users.userID order by postID desc limit ? offset ?;", [limit, offset]);}
async function getPostsLikedView(limit, offset) {return await connPool.awaitQuery("SELECT posts.postID, posts.postLikeCount, posts.postMessage, users.username FROM posts INNER JOIN users on posts.userID = users.userID order by postLikeCount desc limit ? offset ?;", [limit, offset]);}
async function getNumPosts() {return await connPool.awaitQuery("SELECT count(*) as post_count from posts;")};
async function getMessage(id) {return await connPool.awaitQuery("SELECT postMessage from posts where postID = ?;", [id])};
async function getOwnerofPost(id) {return await connPool.awaitQuery("SELECT userID FROM posts where postID = ?;", [id])};

// account table
async function addUser(username, password) {return await connPool.awaitQuery("INSERT INTO users (username, pass) VALUES (?, ?);", [username, password]);}
async function getUserAccount(username) {return await connPool.awaitQuery("SELECT * FROM users WHERE username = ?", [username])};
async function getUserID(username) {return await connPool.awaitQuery("SELECT userID FROM users WHERE username = ?", [username])};
async function getUsername(id) {return await connPool.awaitQuery("SELECT username FROM users WHERE userID = ?", [id])};

module.exports = {addPost, deletePost, editPost, getPostLikeCount, updatePostLikeCount, getPostsRecentView, getPostsLikedView, getNumPosts, getMessage, getOwnerofPost, addUser, getUserAccount, getUserID, getUsername};
