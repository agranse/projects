const site_url = "http://localhost:4131";

// like button
async function like(postID){
    const result = await fetch(site_url + "/addLike", {// send post id to server which updates like count in database
        method: "POST",
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({'id': postID})
    })
    const objec = await result.json();
    if (result.status == 200 || result.status == 404) {
        document.getElementById('like-'.concat(postID)).innerHTML = objec.newCount + " ❤️";// update like count physically
    }
}

// edit button
async function edit(postID){
    const result = await fetch (site_url + "/checkAuthorization", {// check authorization before allowing edit
        method: "POST",
        headers: {'Content-Type': 'application/json'},
        body: JSON.stringify({'id':postID})
    })
    const object = await result.json();
    if (result.status != 200) {
        document.getElementById('error-'.concat(postID)).innerText = "Not authorized to edit.";
    }
    else {
        // replace the text post with a text area and save button for edits
        document.getElementById('post-'.concat(postID)).innerHTML = `<textarea type="text" id = "edit-${postID}" name="post" maxlength="200">${document.getElementById('message-'.concat(postID)).innerHTML}</textarea><br/><br/><button class="generalButtons" onclick=editSave(${postID})>SAVE</button>`;
    }
}

// save button when editing post
async function editSave(postID) {
    const element_id = 'edit-'.concat(postID);
    const element = document.getElementById(element_id);
    let innerHTML = element.value;
    const result = await fetch(site_url + "/editPost", {
        method: "POST",
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({'id': postID, 'message': innerHTML})// send the new message and post id to server to update in table
    })
    const object = await result.json();
    if (result.status == 200) {
        // replace text in post with new message
        document.getElementById('post-'.concat(postID)).innerHTML = `<p class = "postText" id="message-${postID}">` + object.newMess[0].postMessage + `<p class = "postAuthor" id="author-${postID}">~ ` + object.user + `</p><br></br><div class = "buttons"><span class = "likeLabel" id = "like-${postID}"> ${object.numLikes[0].postLikeCount} ❤️</span><button class = "postButton" onclick="like(${postID})">LIKE ME</button><button class = "postButton" onclick="edit(${postID})">EDIT ME</button><button class = "postButton" onclick="deleting(${postID})">DELETE ME</button><div class ="error" "error-${postID}"></div></div>`;
    }
}

// delete button
async function deleting(postID){
    const authorizationResult = await fetch (site_url + "/checkAuthorization", {// check authorization before allowing delete
        method: "POST",
        headers: {'Content-Type': 'application/json'},
        body: JSON.stringify({'id':postID})
    })
    const object = await authorizationResult.json();
    if (authorizationResult.status != 200) {
        document.getElementById('error-'.concat(postID)).innerText = "Not authorized to delete.";
    } 
    else {
        const result = await fetch(site_url + "/deletePost", {// delete post in database
            method: "DELETE",
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({id: postID})
        })
        if (result.status == 200 || result.status == 404) {
            document.getElementById('post-'.concat(postID)).remove();// delete post physically
        }
    }
}

// alternate view button
function changeView() {
    let url = new window.URL(window.location.href);
    const sort = window.localStorage.getItem("sort"); 
    url.searchParams.delete('sort');
    if ("RECENT" === sort) {// if currently sorted by most recent, change to most likes
        url.searchParams.append("sort", "LIKES");
        window.localStorage.setItem("sort", "LIKES")
    } else {// if default or not sorted, change to most recent
        url.searchParams.append('sort', 'RECENT');
        window.localStorage.setItem("sort", "RECENT");
    }
    window.location.assign(url);
}

// next button
async function nextPage(){
    // URL manipulation: https://developer.mozilla.org/en-US/docs/Web/API/URLSearchParams
    let url = new window.URL(window.location.href);
    let page = url.searchParams.get('page');
    page = parseInt(page);
    if (isNaN(page)) {page = 1;}
    const result = await fetch(site_url + "/numPosts", {// call server to find total number of posts in database
        method: "GET",
        headers: {'Content-Type': 'application/json'}
    })
    const obj = await result.json();
    let numPosts = obj.numPosts;
    numPosts = numPosts[0].post_count;
    url.searchParams.delete('page');
    let maxPages = numPosts / page;
    if (maxPages <= 10) {page = page;}// if current page does not have full 10 posts, stay on page             
    else {page = page + 1;}
    url.searchParams.append('page', page);
    window.location.assign(url);
}

// previous button
function previousPage(){
    // URL manipulation: https://developer.mozilla.org/en-US/docs/Web/API/URLSearchParams
    let url = new window.URL(window.location.href);
    let page = url.searchParams.get('page');
    page = parseInt(page);
    if (isNaN(page)) {page = 1;}
    url.searchParams.delete('page');
    page = page - 1;
    if (page < 1) { page = 1;}// if already on page one, stay on page
    url.searchParams.append('page', page);
    window.location.assign(url);
}