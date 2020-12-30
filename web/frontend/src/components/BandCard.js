import { Component } from 'react'
import { Card, Col, Button } from 'react-bootstrap'
import ApiService from '../services/ApiService';

export default class BandCard extends Component {

    apiservice = new ApiService();

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
            .getBand(this.props.id)
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

    renderItems(items) {
        return items.map((item) => {
            return (
                <span key={item.id}>{item.name} </span>
            )
        })
    }



    render() {
        const { name, description, logo, rating } = this.state

        return (
            <Col className="mt-4 align-items-stretch" xs={12} md={4} lg={3} xl={3} >
                <Card>
                    <Card.Img variant="top" src={logo} />
                    <Card.Body>
                        <Card.Title>{name}</Card.Title>
                        <Card.Text>{description}</Card.Text>
                        <Card.Text>Рейтинг: {rating}</Card.Text>
                    </Card.Body>
                    <Button variant="link" type="submit" block href={"/bands/" + this.props.id}>
                        Посмотреть поближе
                    </Button>
                </Card>
            </Col>
        )
    }
}

