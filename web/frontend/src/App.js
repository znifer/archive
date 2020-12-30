import 'bootstrap/dist/css/bootstrap.min.css'
import './index.css'
import { BrowserRouter, Route, Switch } from 'react-router-dom'

import Header from "./components/Header"
import LoginForm from "./components/Loginform"
import RegistrationForm from "./components/Registrationform"
import Search from "./components/Search"
import Top from "./components/Top"
import AlbumInfo from './components/AlbumInfo'
import BandInfo from './components/BandInfo'
import BandsView from './components/BandsView'
import { Component } from 'react'
import AlbumsView from './components/AlbumsView'
import PreferencesView from './components/PreferencesView'
import createHistory from 'history/createBrowserHistory';
const history = createHistory()

export default class App extends Component {
	render() {
		return (
			<BrowserRouter history={history}>
				<Header></Header>
				<Switch>
					<Route exact path="/login" component={LoginForm} />
					<Route exact path="/registration" component={RegistrationForm} />

					<Route exact path="/top" component={Top} />
					<Route exact path="/search" component={Search} />

					<Route exact path="/albums" component={AlbumsView} />
					<Route path="/albums/:id" component={AlbumInfo} />

					<Route exact path="/bands" component={BandsView} />
					<Route path="/bands/:id" component={BandInfo} />

					<Route exact path="/preferences" component={PreferencesView} />
				</Switch>
        </BrowserRouter >
		)
	}
}

