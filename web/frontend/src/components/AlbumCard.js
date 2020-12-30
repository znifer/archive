import { Component } from 'react'
import { Card, Col, Button } from 'react-bootstrap'
import ApiService from '../services/ApiService';

export default class AlbumCard extends Component {
    
    apiservice = new ApiService();
    
    state = {
        title: null,
        cover: null,
        rating: null,
        release_date: null,
        band: null,
        genres_id: null,
        genres: null,
        band_id: null
    }

    componentDidMount() {
        this.apiservice
            .getAlbum(this.props.id)
            .then((data) => {
                this.setState({
                    title: data.title,
                    cover: data.cover,
                    release_date: data.release_date,
                    rating: data.rating,
                    band: data.band.name,
                    band_id: data.band.id,
                    genres: data.genres,
                })
            })
    }

    renderItems(items) {
        return items.map((item) => {
            return (
                <span key={item.id}>{item.name} </span>
            )
        })
    }

    renderButton() {
        if (!this.props.isInBand) {
            return (
            <Button variant="link" type="submit" block href={"/albums/" + this.props.id}>
                Посмотреть поближе
            </Button>
            )}
    }

    render() {
        const { title, cover, rating, release_date, band, band_id, genres } = this.state

        if (!genres) {
            return <div></div>
        }

        const genreItems = this.renderItems(genres)

        return (
            <Col className="mt-4 align-items-stretch" xs={12} md={4} lg={3} xl={3} >
                <Card>
                    <Card.Img variant="top" src={cover} />
                    <Card.Body>
                        <Card.Title>
                            {title}
                        </Card.Title>
                        <Card.Text>
                            Исполнитель: <a href = {"bands/" + band_id}>{" " + band}</a>
                        </Card.Text>
                        <Card.Text>
                            Дата выхода: {release_date}
                        </Card.Text>
                        <Card.Text>
                            Рейтинг: {rating}
                        </Card.Text>
                        <Card.Text>
                            Жанры: {genreItems}
                        </Card.Text>
                    </Card.Body>
                    {this.renderButton()}
                </Card>
            </Col>
        )
    }
}

