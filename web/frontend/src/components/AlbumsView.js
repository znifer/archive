import React, { Component } from 'react'
import { Container, Row } from 'react-bootstrap'
import AlbumCard from './AlbumCard'
import ApiService from '../services/ApiService'
import Footer from './Footer'

export default class AlbumsView extends Component {

    apiservice = new ApiService()

    state = {
        dataList: null,
    }

    componentDidMount() {
        if (this.props.isBest) {
            this.apiservice
                .getBestAlbums()
                .then((dataList) => {
                    this.setState(
                        { dataList }
                    )
                })
        } else {
            this.apiservice
                .getAllAlbums()
                .then((dataList) => {
                    this.setState(
                        { dataList }
                    )
                })
        }

    }

    renderItems(items) {
        return items.map(item => {
            return (
                <AlbumCard key={item.id} id={item.id} ></AlbumCard>
            )
        })
    }

    render() {
        const { dataList } = this.state

        if (!dataList) {
            return <div></div>
        }

        const items = this.renderItems(dataList)

        return (
            <Container>
                <p className="h2 my-4">{this.props.title}</p>
                <Row>
                    {items}
                </Row>
                <Footer />
            </Container>
            
        )
    }
}
