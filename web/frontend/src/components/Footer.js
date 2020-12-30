import { Component } from 'react'
import { Container, Navbar } from 'react-bootstrap'

export default class Footer extends Component {
    render() {
        if (this.props.fixed) {
            return (
                <Navbar fixed="bottom">
                    <Container className="text-center text-muted">
                        © 2020 Ковалёв Илья
                <a href="https://github.com/znifer/" className="text-muted text-center"> Умеет делать ссылки серым!</a>
                    </Container>
                </Navbar>
            )
        } else {
            return (
                <Navbar sticky="bottom">
                    <Container className="text-center text-muted">
                        © 2020 Ковалёв Илья
                        <a href="https://github.com/znifer/" className="text-muted text-center"> Умеет делать ссылки серым!</a>
                    </Container>
                </Navbar>
            )
        }
    }
}

