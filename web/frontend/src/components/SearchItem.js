import { Component } from "react";
import { ListGroup, Image, Row, Col, Button } from 'react-bootstrap'
import ApiService from "../services/ApiService";

export default class SearchItem extends Component {
    apiservice = new ApiService()
    state = {
        title: null,
        cover: null,
        release_date: null,
        rating: null,
        description: null
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
                    description: data.description
                })
            })
    }

    render() {
        const { title, cover, release_date, rating } = this.state;
        return (
            <ListGroup.Item as="li" >
                <Row>
                    <Col xs="6" md="3" >
                        <Image src={cover} thumbnail />
                    </Col>
                    <Col>
                        <p className="h2 text-left">{title}</p>
                        <p className="text-left">Дата выхода: {release_date}</p>
                        <p className="text-left">Рейтинг: {rating}</p>
                        <a href={"/albums/" + this.props.id}>Посмотреть поближе</a>
                    </Col>
                </Row>
            </ListGroup.Item>
        )
    }
}