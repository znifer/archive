import React from 'react'
import './App.css';
import Header from "../Header/Header";
import Footer from "../Footer/Footer";
import {
    BrowserRouter,
    Switch,
    Route
} from 'react-router-dom'
import MainView from "../MainView/MainView";
import ContentView from "../ContentView/ContentView";
import LoginView from "../LoginView/LoginView";

function App() {
  return (
      <BrowserRouter>
        <div className="App">
            <Header/>
            <Switch>
                <Route exact path="/" component={MainView}/>
                <Route path="/post" component={ContentView}/>
                <Route path="/login" component={LoginView}/>
            </Switch>
        </div>
        <Footer/>
      </BrowserRouter>
  );
}

export default App;
