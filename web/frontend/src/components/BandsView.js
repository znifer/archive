import React, { Component } from 'react'
import { Container, Row } from 'react-bootstrap'
import ApiService from '../services/ApiService'
import BandCard from './BandCard'
import Footer from './Footer'


export default class BandsView extends Component {

    apiservice = new ApiService()

    state = {
        dataList: null,
    }

    componentDidMount() {
        this.apiservice
            .getAllbands()
            .then((dataList) => {
                this.setState(
                    { dataList }
                )
            })
    }

    renderItems(items) {
        return items.map(item => {
            return (
                <BandCard id={item.id} ></BandCard>
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
                <Footer fixed={true}></Footer>
            </Container>
        )
    }
}
