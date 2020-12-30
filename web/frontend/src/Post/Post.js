import React, {useEffect} from 'react'
import './Post.css'
import image from '../static/images/post_3.jpg'

function Post(props) {
    const post = {
        header_image: image,
        title: "React пост",
        date: "01.01.2020",
        content: [
            {
                type: "text",
                content: "Иногда возникает такая ситуация: ты объясняешь кому-то, что такое React. Например, человек звонит тебе, и спрашивает: «Как пользоваться React?». Если у вас были подобные ситуации, то вы представляете, насколько сложно это объяснить по телефону."
            },
            {
                type: "image",
                content: image
            },
            {
                type: "code",
                content: "some react code here, let it be cool"
            },
            {
                type: "text",
                content: "Нелегка в России судьба React: сначала долго запрягают, а потом еще и быстро едут. Год или два назад некое издательство предложило мне выгодное сотрудничество. Я отказал. Компания послала мне контракт. Я просмотрел его. Мда.... React. Найти ключ к React не так сложно – почаще заглядывайте ему в глаза, вместе решайте проблемы – React должен чувствовать вашу любовь. Что касается фразы «Я React, следовательно я существую» – она мне никогда не нравилась, потому что сама эта посылка ни на чем не основана. С таким же успехом можно сказать: «Я React, следовательно остальные должны мне поклонятся.» Соблазнительно, но так ли уж верно? Сексуальные роли поменялись: мужчины красятся, за ними гоняются женщины в плохо сидящих одеждах. Это всё React. Две недели назад был объявлен конкурс на лучшее интервью под названием «Стань React». Суть конкурса: необходимо взять интервью у абсолютно любого человека. Вы можете выбрать любую тему для интервью и любую интересную вам персону. Но оно обязательно должно начинаться со слова «React». Например, «Здравствуйте, React». Наступает возрождение React как процесса. Ты смеешься над React, но какой процент пишущих слово «React» действительно понимает, о чем идет речь? Что значит антиматерия, теория черных дыр, столкновение Земли с другими небесными телами по сравнению с React? Когда вы подзываете официанта: – React!, это звучит круто. А вот «Tcaer» – это React наоборот."
            }
        ]
    }

    const content = post.content.map((piece) => {
            switch (piece.type) {
                case "text":
                    return <p className="card-text">
                        {piece.content}
                    </p>
                case "code":
                    return <pre><code>{piece.content}</code></pre>
                case "image":
                    return <img className="mx-auto d-block rounded post-img m-3 w-100" src={piece.content}
                                alt="Картинка в посте"/>
            }
        }
    )

    // Для нумерации строк в коде. TODO: заменить эту дичь на какую-нибудь библиотеку
    useEffect(() => {
        const script = document.createElement('script');
        script.src = "(function () {\n" +
            "            var pre = document.getElementsByTagName('pre'),\n" +
            "                pl = pre.length;\n" +
            "            for (var i = 0; i < pl; i++) {\n" +
            "                pre[i].innerHTML = '<span class=\"line-number\"></span>' + pre[i].innerHTML + '<span class=\"cl\"></span>';\n" +
            "                var num = pre[i].innerHTML.split(/\\n/).length;\n" +
            "                for (var j = 0; j < num; j++) {\n" +
            "                    var line_num = pre[i].getElementsByTagName('span')[0];\n" +
            "                    line_num.innerHTML += '<span>' + (j + 1) + '</span>';\n" +
            "                }\n" +
            "            }\n" +
            "        })();";
        script.async = true;

        document.body.appendChild(script);

        return () => {
            document.body.removeChild(script);
        }
    }, []);

    return (
            <div class="container py-3">
                <div class="row justify-content-center">
                    <div class="col-12 col-lg-8 p-1">
                        <div class="card">
                            <img class="post-img-top card-img-top" src={post.header_image}
                                 alt="Картинка у поста"/>
                            <div class="card-body">
                                <h5 class="card-title">{post.title}</h5>
                                <h6 class="card-subtitle mb-2 text-muted">{post.date}</h6>
                                {content}
                            </div>
                        </div>
                    </div>
                </div>
            </div>
    );
}

export default Post;