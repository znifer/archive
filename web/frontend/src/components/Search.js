import { Component } from 'react'
import { Container, ListGroup, InputGroup, FormControl, Button } from 'react-bootstrap'
import ApiService from '../services/ApiService'
import Footer from './Footer';
import SearchItem from './SearchItem'

export default class Search extends Component {

    apiservice = new ApiService();

    state = {
        searchRequest: "",
        searchResults: null
    }

    constructor(props) {
        super(props)
        this.onClick = this.onClick.bind(this)
    }

    onClick() {
        const { searchRequest } = this.state
        if (searchRequest) {
            this.apiservice
                .searchAlbum(searchRequest)
                .then((searchResults) => {
                    this.setState({
                        searchResults
                    })
                })
        }

    }

    renderItems(items) {
        console.log(items)
        if (items) {
            return items.map(item => {
                return (
                    <SearchItem id={item.id} />
                )
            })
        } else {
            return <div className="text-center">Ничего не нашлось. А вы искали?</div>
        }

    }

    render() {
        const { searchResults } = this.state

        const items = this.renderItems(searchResults)

        

        return (
            <Container className="mt-3">
                <InputGroup className="mb-3">
                    <FormControl
                        placeholder="Кого ищем?"
                        onChange={e => this.setState({ searchRequest: e.target.value })}
                    />
                    <InputGroup.Append>
                        <Button onClick={this.onClick} variant="outline-primary">Найти</Button>
                    </InputGroup.Append>
                </InputGroup>
                <hr></hr>
                <ListGroup as="ul">
                    {items}
                </ListGroup>
                <Footer fixed={true}></Footer>
            </Container>
        )
    }
}