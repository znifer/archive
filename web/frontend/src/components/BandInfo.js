import React, { Component } from 'react'
import { Container, Row, Col, Card } from 'react-bootstrap'
import ApiService from '../services/ApiService'
import AlbumCard from './AlbumCard'
import Footer from './Footer';

export default class BandInfo extends Component {

    apiservice = new ApiService()

    constructor(props) {
        super(props)
        console.log(this.props)
    }

    state = {
        name: null,
        description: null,
        created: null,
        ended: null,
        logo: null,
        rating: null,
        members: null,
        albums: null
    }

    componentDidMount() {
        this.apiservice
            .getBand(this.props.match.params.id)
            .then((data) => {
                this.setState({
                    name: data.name,
                    description: data.description,
                    created: data.created,
                    ended: data.ended,
                    logo: data.logo,
                    rating: data.rating,
                    members: data.members,
                    albums: data.albums
                })
            })
    }

    renderAlbums(albums) {
        return albums.map(album => {
            return (
                <AlbumCard key={album.id} id={album.id}></AlbumCard>
            )
        })
    }

    renderDates(created, ended) {
        if (ended) {
            return (
                `${created} - ${ended}`
            )
        } else {
            return `${created} -  . . . ?`
        }

    }

    renderMembers(members) {
        return members.map(member => {
            return <p>{member.name}</p>
        })

    }

    render() {
        const { name, description, created, ended, logo, rating, members, albums } = this.state

        if (!albums) {
            return <div></div>
        }

        const albumItems = this.renderAlbums(albums)
        const dateItems = this.renderDates(created, ended)
        const memberItems = this.renderMembers(members)
        return (
            <Container className="mt-4">
                <Row>
                    <Col lg={4} md={6} xs={12}>
                        <Card >
                            <Card.Img variant="top" src={logo} />
                        </Card>
                    </Col>
                    <Col lg={8} md={6} xs={12}>
                        <p className="display-4">{name}</p>

                        <span><p>Годы активности: {dateItems}</p></span>
                        <p>Рейтинг: {rating}</p>
                        <p>{description}</p>
                        <hr></hr>
                        <p>Состав</p>
                        {memberItems}
                    </Col>
                </Row>
                <p className="h4 mt-4">Альбомы исполнителя</p>
                <hr></hr>
                <Row>
                    {albumItems}
                </Row>
                <Footer></Footer>
            </Container>
        )
    }
}