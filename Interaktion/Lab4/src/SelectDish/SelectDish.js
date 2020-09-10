import React, { Component } from "react";
import Sidebar from "../Sidebar/Sidebar";
import Dishes from "../Dishes/Dishes";
import Details from "../Details/Details";
import "./SelectDish.css";

class SelectDish extends Component {
  constructor(props) {
    super(props);
    this.state = {
      status: this.props.state
    };
  }

  render() {
    switch(this.state.status){
      case "SEARCH":
        return (
          <div className="SelectDish">
            <Sidebar model={this.props.model}/>
            <Dishes />
          </div>
        );
      case "DETAILS":
        return (
          <div className="SelectDish">
            <Sidebar model={this.props.model}/>
            <Details model={this.props.model}/>
          </div>
        );
      default:
        return ( 
        <div className="SelectDish">
          <h1>Something is horribly wrong</h1>
        </div>
        );
    }

  }
}

export default SelectDish;
