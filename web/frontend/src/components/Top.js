import { Component } from "react"
import { Container } from "react-bootstrap"
import AlbumsView from "./AlbumsView"
import Footer from "./Footer"

export default class Top extends Component {
    render() {
        return (
            <Container>
                <AlbumsView isBest="true" title="Лучшее за все время" />
                <Footer fixed={false}></Footer>
            </Container>
        )
    }
}
