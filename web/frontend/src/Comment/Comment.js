import React from 'react'
import './Comment.css'

function Comment (props) {
    return (
        <div className="container">
            <div className="row">
                <div className="col-2">
                    <img className="img-thumbnail" src={props.user_picture}
                         alt="Не загружено"/>
                </div>
                <div className="col-10">
                    <div className="text-inline justify-content-between d-flex">
                        <a href="#" className="">{props.user_name}</a>
                        <div className="comments-date">{props.comment_date}</div>
                    </div>
                    <hr/>
                    <div className="text-inline">
                        {props.comment_text}
                    </div>
                </div>
            </div>
        </div>
    )
}

export default Comment;