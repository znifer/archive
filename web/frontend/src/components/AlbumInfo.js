import React, { Component } from 'react'
import { Container, Row, Col, Card, Button } from 'react-bootstrap'
import ApiService from '../services/ApiService'
import Footer from "./Footer"
export default class AlbumInfo extends Component {

    apiservice = new ApiService();
    constructor(props) {
        super(props)
        console.log(this.props)
    }

    state = {
        title: null,
        cover: null,
        rating: null,
        release_date: null,
        band: null,
        genres_id: null,
        genres: null,
        band_id: null,
        tracks: null
    }


    componentDidMount() {
        this.apiservice
            .getAlbum(this.props.match.params.id)
            .then((data) => {
                this.setState({
                    title: data.title,
                    cover: data.cover,
                    release_date: data.release_date,
                    rating: data.rating,
                    band: data.band.name,
                    band_id: data.band.id,
                    genres: data.genres,
                    tracks: data.tracks
                })
            })
    }

    renderItems(items) {
        return items.map(item => {
            return (
                <span>{item.name} </span>
            )
        })
    }

    renderTracks(tracks) {
        return tracks.map(track => {
            return (
                <Row>
                    <Col lg={11} md={10} xs={10} ><p className="text-start">{track.title}</p></Col>
                    <Col lg={1} md={1} xs={1}><p className="text-end">{track.duration}</p></Col>
                </Row>
            )
        })
    }

    render() {
        const { title, cover, rating, release_date, band, band_id, genres, tracks } = this.state

        if (!genres || !tracks) {
            return <div></div>
        }
        console.log(band_id,)
        const genreItems = this.renderItems(genres)
        const trackItems = this.renderTracks(tracks)
        return (
            <Container className="mt-4">
                <Row>
                    <Col lg={4} md={6} xs={12}>
                        <Card >
                            <Card.Img variant="top" src={cover} />
                        </Card>
                        <hr></hr>
                        <Button variant="secondary" type="submit" block >
                            Добавить к себе
                        </Button>
                        <Button href={"/bands/" + band_id} variant="secondary" type="submit" block>
                            Информация об исполнителе
                        </Button>
                        <hr></hr>
                    </Col>
                    <Col lg={8} md={6} xs={12}>
                        <p className="display-4">{title}</p>
                        <p>{" " + band}</p>
                        <p>Дата выхода: {release_date}</p>
                        <p>Рейтинг: {rating}</p>
                        <p>Жанры: {genreItems}</p>
                        <hr></hr>
                        <p className="h4">Треклист</p>
                        <p>{trackItems}</p>
                    </Col>
                </Row>
                <Footer></Footer>
            </Container>
        )
    }
}