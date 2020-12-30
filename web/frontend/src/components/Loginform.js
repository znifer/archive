import { Component } from "react"
import { Card, Form, Button } from 'react-bootstrap'
import AuthService from "../services/AuthService"
import Footer from "./Footer"
import { createBrowserHistory } from 'history'

export default class LoginForm extends Component {

    authservice = new AuthService()

    constructor(props) {
        super(props)
        this.onChangeUsername = this.onChangeUsername.bind(this)
        this.onChangePassword = this.onChangePassword.bind(this)
        this.onClick = this.onClick.bind(this)
    }

    state = {
        username: null,
        password: null,
    }

    onChangeUsername(e) {
        this.setState({
            username: e.target.value
        });
    }

    onChangePassword(e) {
        this.setState({
            password: e.target.value
        });
    }

    onClick() {
        const { username, password } = this.state
        this.authservice.login(username, password)
            .then(() => {
                const history = createBrowserHistory()
                history.push('/preferences')
                window.location.reload()
            })
    }

    render() {
        return (
            <div className="my-5 col-sm-9 col-md-7 col-lg-4 mx-auto">
                <Card>
                    <Card.Body>
                        <Card.Title>Войти</Card.Title>
                        <Form>
                            <Form.Group>
                                <Form.Control
                                    placeholder="Логин"
                                    onChange={this.onChangeUsername}
                                />
                            </Form.Group>
                            <Form.Group controlId="formBasicPassword">
                                <Form.Control
                                    placeholder="Пароль"
                                    type="password"
                                    onChange={this.onChangePassword}
                                />
                            </Form.Group>
                            <Button variant="secondary" onClick={this.onClick} block>
                                Войти
                            </Button>
                            <Button variant="secondary" href="/registration" block>
                                Зарегистрироваться
                            </Button>
                        </Form>
                    </Card.Body>
                </Card>
                <Footer fixed={true}></Footer>
            </div>
        )
    }
}