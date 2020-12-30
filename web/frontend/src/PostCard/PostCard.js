import React from 'react'
import './PostCard.css'
import {Link} from "react-router-dom";

function PostCard(props) {
    return (
        <div className="card h-100">
            <img className="post-img-top card-img-top" src={props.post_image} alt="Картинка у поста"/>
                <div className="card-body">
                    <h5 className="card-title">{props.post_title}</h5>
                    <p className="card-text">{props.post_text}</p>
                    <Link to="post" t className="btn btn-primary">Читать далее...</Link>
                </div>
        </div>
    )
}

export default PostCard;