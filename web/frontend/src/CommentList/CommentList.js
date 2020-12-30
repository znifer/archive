import React from 'react';
import './CommentList.css';
import Comment from "../Comment/Comment";
import logo from "../static/images/logo.png";

function CommentList(props) {
    const comments = [
        {
            user_name: "User 1",
            user_picture: logo,
            comment_text: "Не читал, но осуждаю",
            comment_date: "20.01.2020"
        },
        {
            user_name: "User 2",
            user_picture: logo,
            comment_text: "Прочитал, все равно осуждаю",
            comment_date: "21.01.2020"
        }
    ]
    const listComments = comments.map((comment) =>
        <li className="list-group-item d-flex">
            <Comment user_name={comment.user_name} user_picture={comment.user_picture} comment_text={comment.comment_text} comment_date={comment.comment_date}/>
        </li>
    );
    return (
        <div className="container px-0 mb-3">
            <div className="row justify-content-center">
                <div className="col-12 col-md-8">
                    <ul className="list-group w-100">
                        {listComments}
                    </ul>
                </div>
            </div>
        </div>
    );
}

export default CommentList;