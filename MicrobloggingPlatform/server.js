// flower.png sourced from:          https://www.pinterest.com/pin/peony-line-art-drawing--683350943450682281/

// server set up
const express = require("express");
const app = express();
var session = require('express-session');
const port = 4131;
const bodyParser = require('body-parser');
const data = require('./data');
const page_size = 10;
var bcrypt = require('bcrypt');

app.use(express.json());
app.use(bodyParser.urlencoded({ extended: true }));
app.use(session({
    secret: 'kl;fja;giujvaeww23f3v',
    resave: false,
    saveUninitialized: true
  }))
app.use('/images', express.static('resources/images'));
app.use("/static/css", express.static("resources/css"));
app.use("/static/js", express.static("resources/js"));
app.set("views", "templates");
app.set("view engine", "pug");

// helper function for viewing posts
async function getPosts(req, res) {
    const user = req.session.user;
    let page = req.query.page ?? 1;// get requested page, if no req provided default page 1
    page = parseInt(page);
    if(isNaN(page) || page < 1 || !Number.isInteger(page))  page = 1;// if issue with req, default page 1
    const offset = (page - 1) * page_size;// calculate offset for query, page 1 = 0
    const viewing = req.query.sort;// chosen viewing, most liked vs most recent
    let posts;
    if ("LIKES" === viewing) {posts = await (await data.getPostsLikedView(page_size, offset));}// posts gotten from sql table in most liked view
    else {posts = await (await data.getPostsRecentView(page_size, offset));}// posts gotten from sql table in most recent view
    res.status(200).set({'Content-Type': 'text/html'}).render('posts.pug', { posts: posts, user: user});
}

// helper function for checking if user is logged in
function loggedIn (req, res, next) {
    if (req.session.user) next();
    else {return res.set({"Content-Type": "text/html"}).render("home.pug", {error : "Please login first."});}
}

// Static files
app.get('/static/css/main.css', (req, res) => {res.set({'Content-Type': 'text/css'}).sendFile('/main.css')});
app.get('/static/js/viewPostsButtons.js', (req, res) => {res.set({'Content-Type': 'text/javascript'}).sendFile('/viewPostsButtons.js')});
app.get('/static/images/flower.png', (req, res) => {res.set({'Content-Type': 'image/png'}).sendFile('/flower.png')});

// Login & account pages
app.get('/', (req, res) => {
    const user = req.session.user;
    res.set({'Content-Type': 'text/html'}).render('home.pug', {user: user})
});
app.get('/home', (req, res) => {
    const user = req.session.user;
    res.set({'Content-Type': 'text/html'}).render('home.pug', {user: user})
});
app.get('/createAccount', (req, res) => {
    const user = req.session.user;
    res.set({'Content-Type': 'text/html'}).render('createAccount.pug', {user: user})
});
app.post('/createAccount', async (req, res) => {
    const username = req.body.newUser;
    const password = req.body.newPass;
    if (username == null) {return res.set({"Content-Type": "text/html"}).render("createAccount.pug", {error : "No username provided."});}
    if (password == null) {return res.set({"Content-Type": "text/html"}).render("createAccount.pug", {error : "No password provided."});}
    const result = await data.getUserAccount(username);//check if chosen username already in database
    if (result[0]) {return res.set({"Content-Type": "text/html"}).render("createAccount.pug", {error : "Username already in use."});}
    bcrypt.hash(password, 10, function(err, hash) {data.addUser(username, hash);});// hash pasword and add user to table
    res.status(200).set({'Content-Type': 'text/html'}).render('createConfirmation.pug');
});
app.post('/login', async (req, res) => {
    // https://expressjs.com/en/resources/middleware/session.html
    const username = req.body.user;
    const password = req.body.pass;
    if (!username) {return res.set({"Content-Type": "text/html"}).render("home.pug", {error : "No username provided."});}
    if (!password) {return res.set({"Content-Type": "text/html"}).render("home.pug", {error : "No password provided." });}
    const result = await data.getUserAccount(username);// check for username in database
    if (!result[0]) { return res.set({"Content-Type": "text/html"}).render("home.pug", {error : "Username or password incorrect." });}
    const databasePassword = result[0].pass;
    const match = await bcrypt.compare(password, databasePassword);// compare password entered with password in database
    if(match) {
        // if they match, start session
        req.session.regenerate(function (err) {
            if (err) next(err);
            req.session.user = username;
        });
        req.session.save(function (err) {
            if (err) return next(err);
            return getPosts(req, res);// and render posts page
        })
    } 
    else {
        return res.set({"Content-Type": "text/html"}).render("home.pug", { error: "Username or password incorrect." });
    }
});
app.get('/logout', function (req, res, next) {
    // https://www.npmjs.com/package/express-session
    // end session and render home page
    req.session.user = null;
    req.session.save(function (err) {
      if (err) next(err);
      req.session.regenerate(function (err) {
        if (err) next(err);
        res.redirect('/');
      })
    })
})

// Post pages
app.get('/posts', async (req, res) => { return getPosts(req, res); });
app.post('/posts', loggedIn, async (req, res) => {
    const user = req.session.user;
    let userID = await(await data.getUserID(user));//if user logged in, get userID and associate with new post
    let newPost = await (await data.addPost(req.body.post, userID[0].userID));// add new post to sql table
    return getPosts(req, res);
});

// Post interactions
app.get('/numPosts', async (req, res) => {
    let numPosts = await (await data.getNumPosts());// get number of posts in sql table
    res.status(200).set({'Content-Type': "application/json"}).send({numPosts : numPosts});
})
app.post('/addLike', async (req, res) => {
    let count = await (await data.getPostLikeCount(req.body.id));// get current like count from sql table
    let result = await (await data.updatePostLikeCount([count[0].postLikeCount+1, req.body.id]));// update like count of post by 1 in sql table
    res.status(200).set({'Content-Type': "application/json"}).send({newCount : count[0].postLikeCount+1});
});
app.post('/editPost', loggedIn, async (req, res) => {
    const user = req.session.user;
    let messList = [];
    messList.push(req.body.message);
    messList.push(req.body.id);
    let updatePost = await (await data.editPost(messList));// update post message in table
    let newMess = await (await data.getMessage(req.body.id));// get new message from table
    let numLikes = await (await data.getPostLikeCount(req.body.id));// get number of likes from table
    res.status(200).set({'Content-Type': "application/json"}).send({newMess: newMess, numLikes: numLikes, user: user});
});
app.delete('/deletePost', loggedIn, async (req, res) => {
    const user = req.session.user;
    if (req.body["id"] == null) {res.status(400).set({'Content-Type': "application/json"}).send("No post id provided.");}
    let deleting = await (await data.deletePost(req.body["id"]));// delete post from sql table
    res.status(200).set({'Content-Type': "application/json"}).send("Successfully deleted.");
});
app.post('/checkAuthorization', async (req, res) => {// check if user is owner of post they are trying to edit / delete
    const user = req.session.user;
    const postID = req.body.id;
    const postOwner = await (await data.getOwnerofPost(postID));// returns userID of post
    const postUsername = await (await data.getUsername(postOwner[0].userID));// get username of account associated with post
    if (user != postUsername[0].username) {
        return res.status(201).set({'Content-Type': "application/json"}).send({error: "Not authorized." });
    } else {
        return res.status(200).set({'Content-Type': "application/json"}).send({error: "Authorized" });
    }
});

app.use((req, res) => {res.status(404).set({'Content-Type': 'text/html'}).render('404.pug');});

app.listen(port, () => {console.log(`NOW COMING TO YOU LIVE FROM PORT: ${port}`);});