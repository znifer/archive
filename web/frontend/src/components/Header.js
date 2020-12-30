import { Component } from 'react'
import { Navbar, Nav, Button } from 'react-bootstrap'
import AuthService from '../services/AuthService'

export default class Header extends Component {

    constructor(props) {
        super(props)
        this.onClick = this.onClick.bind(this)
    }
    
    authservice = new AuthService()

    onClick() {
        this.authservice.logout()
    }

    getLoginLink() {
        if (localStorage.getItem("access")) {
            return (<Button variant="link" href="/login" onClick={this.onClick}>Выйти</Button>)
        } else {
            return (<Button variant="link" href="/login">Войти</Button>)
        }
    }

    render() {

        const logButton = this.getLoginLink()

        return (
            <Navbar bg="light" expand="lg">
                <Navbar.Brand>Че послушать?</Navbar.Brand>
                <Nav className="mr-auto">
                    <Nav.Link href="/albums">Альбомы</Nav.Link>
                    <Nav.Link href="/bands">Исполнители</Nav.Link>
                    <Nav.Link href="/search">Поиск</Nav.Link>
                    <Nav.Link href="/top">Лучшее</Nav.Link>
                    <Nav.Link href="/preferences">Мой профиль</Nav.Link>
                </Nav>
                {logButton}
            </Navbar>
        )
    }
}

