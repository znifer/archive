import React from 'react'
import Post from "../Post/Post";
import CommentList from "../CommentList/CommentList";

function ContentView(props) {
    return (
        <main>
            <Post/>
            <CommentList/>
        </main>
    )
}

export default ContentView;