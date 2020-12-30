import { Component } from "react"
import { Card, Form, Button } from 'react-bootstrap'
import AuthService from "../services/AuthService"
import Footer from "./Footer"
export default class RegistrationForm extends Component {

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

    }

    render() {
        return (
            <div className="my-5 col-sm-9 col-md-7 col-lg-4 mx-auto">
                <Card>
                    <Card.Body>
                        <Card.Title>Регистрация</Card.Title>
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
                                    onChange={this.onChangePassword}
                                />
                                <Form.Control className="mt-3"
                                    placeholder="Еще разок"
                                    onChange={this.onChangePassword}
                                />
                            </Form.Group>
                            <Button variant="secondary" type="submit" onClick={this.onClick} block>
                                Зарегистрироваться
                                </Button>
                            <hr></hr>
                            <Form.Check className="mt-2"
                                type="checkbox"
                                label="Получать спам на почту"
                            ></Form.Check>
                            <Form.Check className="mt-2"
                                type="checkbox"
                                label="Я умею читать и сделал вид, что прочитал правила"
                            ></Form.Check>
                            <div className="mt-2">
                                <div className="text-center">
                                    С правилами можно ознакомиться
                                <a href="https://www.youtube.com/watch?v=dQw4w9WgXcQ"> тут</a>
                                </div>
                            </div>

                        </Form>
                    </Card.Body>
                </Card>
                <Footer fixed={true}></Footer>
            </div>
            			
        )
    }
}



