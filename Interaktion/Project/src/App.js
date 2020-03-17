import React, { Component } from "react";
import { Route } from "react-router-dom";
import modelInstance from "./data/WeatherModel";
import "./App.css";

class App extends Component{
    constructor(props){
        super(props);
        this.state = {
            title: "PROJECT"
        };
    }

    componentDidMount(){
        console.log(modelInstance.getCurrentWeather());
    }

    render(){
        return (
            <div className="App">
                <header className="App-header">
                    <h1 className="App-title">{this.state.title}</h1>
                </header>
            </div>
        );
    }
}
export default App;