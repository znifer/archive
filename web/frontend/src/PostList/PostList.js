import React from 'react'
import './PostList.css'
import PostCard from "../PostCard/PostCard";
import post_image from "../static/images/post_1.png";

function PostList(props) {
    const posts = [
        {
            post_image: post_image,
            post_title: "Linux",
            post_text: "В начале месяца некоторые горожане получили квитанции за коммунальные услуги, в графах которых были проставлены нули. Забавно, что они были проставлены и в графе «количество проживающих в квартире». Думаю, что именно в этом случае, Linux тут ни при чём.",
            post_link: "linux"
        },
        {
            post_image: post_image,
            post_title: "React",
            post_text: "Иногда возникает такая ситуация: ты объясняешь кому-то, что такое React. Например, человек звонит тебе, и спрашивает: «Как пользоваться React?». Если у вас были подобные ситуации, то вы представляете, насколько сложно это объяснить по телефону.",
            post_link: "react"
        },
        {
            post_image: post_image,
            post_title: "Django",
            post_text: "Когда тебе приснится Django, ты поймешь, как приятно быть просто программой. Даже с глюками. Вот уже семь лет, и ни одного дня без весточки от Django.",
            post_link: "django"
        },
        {
            post_image: post_image,
            post_title: "Django",
            post_text: "Когда тебе приснится Django, ты поймешь, как приятно быть просто программой. Даже с глюками. Вот уже семь лет, и ни одного дня без весточки от Django.",
            post_link: "django"
        },
        {
            post_image: post_image,
            post_title: "Django",
            post_text: "Когда тебе приснится Django, ты поймешь, как приятно быть просто программой. Даже с глюками. Вот уже семь лет, и ни одного дня без весточки от Django.",
            post_link: "django"
        },
        {
            post_image: post_image,
            post_title: "Django",
            post_text: "Когда тебе приснится Django, ты поймешь, как приятно быть просто программой. Даже с глюками. Вот уже семь лет, и ни одного дня без весточки от Django.",
            post_link: "django"
        },
        {
            post_image: post_image,
            post_title: "Django",
            post_text: "Когда тебе приснится Django, ты поймешь, как приятно быть просто программой. Даже с глюками. Вот уже семь лет, и ни одного дня без весточки от Django.",
            post_link: "django"
        },
    ]
    // elementary, Watson
    const evenPosts = posts.filter((post, index) => index % 2 === 0 && index !== 0)
    const oddPosts = posts.filter((post, index) => index % 2 === 1)
    const betterPosts = evenPosts.map((p, i) => [p, oddPosts[i]])
    betterPosts.unshift(posts[0])
    console.log(betterPosts)
    const listPosts = betterPosts.map((postSet, index)=> {
            if (index === 0) {
                return  <div className="row justify-content-center">
                            <div className="col-12 col-md-8 my-3">
                                <PostCard post_image={postSet.post_image} post_text={postSet.post_text}
                                          post_title={postSet.post_title} post_link={postSet.post_link}/>
                            </div>
                        </div>
            }
            return  <div className="row justify-content-center">
                {
                    postSet.map((post) =>
                        <div className="col-12 col-md-4 my-3">
                            <PostCard
                                post_image={post.post_image}
                                post_text={post.post_text}
                                post_title={post.post_title}
                                post_link={post.post_link}
                            />
                        </div>
                    )
                }
                </div>
        }
    )
    return (
        <div>
            <div className="container">
                <div className="row justify-content-center">
                    {listPosts}
                </div>
            </div>
        </div>
    );
}

export default PostList;