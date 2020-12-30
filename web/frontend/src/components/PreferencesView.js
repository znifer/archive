import { Component } from "react";
import { Container, Row } from "react-bootstrap";
import ApiService from "../services/ApiService";
import AuthService from "../services/AuthService";
import AlbumCard from "./AlbumCard";
import BandCard from "./BandCard";
import Footer from "./Footer";
import { createBrowserHistory } from 'history'

export default class PreferencesView extends Component {

    apiservice = new ApiService()

    authservice = new AuthService()

    state = {
        albums: null,
        bands: null
    }

    componentDidMount() {
        if (this.authservice.isLogged()) {
            this.apiservice.getPreferences()
                .then((data) => {
                    console.log(data)
                    this.setState({
                        albums: data[0].albums,
                        bands: data[0].bands,
                    })
                })
        } else {
            const history = createBrowserHistory()
            history.push('/login')
            window.location.reload()

        }
    }

    renderAlbums(items) {
        return items.map(item => {
            return (
                <AlbumCard key={item} id={item} />
            )
        })
    }

    renderBands(items) {
        return items.map(item => {
            return (
                <BandCard id={item} ></BandCard>
            )
        })
    }

    render() {
        const { albums, bands } = this.state
        let albumItems = <div></div>
        let bandItems = <div></div>
        let message1 = <p className="h2 mt-4">Пока что тут пусто</p>
        let message2 = <p className="h2 mt-4">Пока что тут пусто</p>
        let isFixed = false
        
        if (albums) {
            message1 = <div></div>
            albumItems =
                <Container>
                    <p className="h2 mt-4">Альбомы, которые Вам понравились</p>
                    <Row>
                        {this.renderAlbums(albums)}
                    </Row>
                </Container>
        }

        if (bands) {
            bandItems = <Container>
                <p className="h2 mt-4">Исполнители, которые Вам понравились</p>
                <Row>
                    {this.renderBands(bands)}
                </Row>
            </Container>

        }
        if (!(message1 == <div></div>)) {
            message2 = <div></div>
            isFixed = true
        }



        return (
            <Container>
                {message1}
                {albumItems}
                {message2}
                {bandItems}
                <Footer fixed={isFixed} />
            </Container>
        )
    }

}