import React from 'react'
import './Header.css'
import logo from '../static/images/logo.png'
import {Link} from "react-router-dom";

function Header(props) {
    return (
        <header>
            <nav className="site-header sticky-top py-1">
                <div className="container d-flex flex-column flex-md-row justify-content-left">
                    <Link className="p-2" to="/">
                        <img className="rounded-circle border mx-3" width="30" height="30" src={logo} alt="Логотип"/>
                            <strong>МойбЛог</strong>
                    </Link>
                    <Link className="p-2 d-none d-md-inline-block" to="#">О себе</Link>
                    <Link className="p-2 d-none d-md-inline-block" to="#">Навигация</Link>
                    <Link className="p-2 d-none d-md-inline-block" to="login">Вход</Link>
                </div>
            </nav>
        </header>
    );
}

export default Header;