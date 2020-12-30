import React from 'react'
import './Login.css'

function Login(props) {
    return (
        <div className="container text-center">
            <form className="form-signin">
                <h1 className="h3 mb-3 font-weight-normal">Вход в систему</h1>
                <label htmlFor="inputEmail" className="sr-only">E-Mail</label>
                <input type="email" id="inputEmail" className="form-control" placeholder="E-Mail" required autoFocus/>
                <label htmlFor="inputPassword" className="sr-only">Password</label>
                <input type="password" id="inputPassword" className="form-control" placeholder="Пароль" required/>
                <div className="checkbox mb-3">
                    <label>
                        <input type="checkbox" value="remember-me"/> Запомнить меня
                    </label>
                </div>
                <button className="btn btn-lg btn-dark btn-block" type="submit">Войти</button>
            </form>
        </div>
    );
}

export default Login;